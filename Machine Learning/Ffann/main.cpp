// main.cpp
// Contributor: Phillip Graham
// Start Time: March 05, 2023
// Last Edited: May, 08 2023
// Purpose: This is the file which I use to actually allow the physics script to run a simulation using a specific
//          neural network. This file works by reading in a network description from a networkXXX.txt file.
//          It then constructs this network and uses it to determine what it should output when promped with input
//          from the physics simulator script.

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string> 

using namespace std;

// This structure is primarily used just to help better organize the code.
// these all could have been held in vectors in the main body of the program,
// but my using this structure I can make it more compact and only handle one
// vector
struct neuron
{
    neuron ();
    float threshold;
    float bias;
    bool refractory; // This was not used, but I left it in in the event I would like to try and modify the network
    float state;
    vector <neuron*> post_neurons; // Contaisn the destination of every "synapse" that leaves this neuron
    vector <float> weights; // contains every weight associated with every "synapse"
};


int main ()
{
    // Here we just handle input and construction of the network. As mentioned in comments for
    // gennet.cppm, the repnum.txt file just contains the number which designates our respective
    // network file. By using this common file, we allow our main to be called systematically
    // without having to handle the name of the fiel we are using for the network description.
    vector <vector<neuron*>> slices;
    int num_input, num_output, num_hidden, num_per_hidden;
    ifstream inputrepnum("repnum.txt");
    int file_num;
    inputrepnum >> file_num;
    inputrepnum.close();
	ifstream input_file("./networks/network" + to_string(file_num-1) + ".txt");
	if (!input_file.is_open())
	{
		cout << "ERROR: Could not open file: network.txt" << endl;
	}
    else
    {
        // Handel the construction of the network.
        // The network has 2 + num_hidden slices, and each slice has
        // a certain number of neurons. For the input/output slices,
        // this number is represented by the respective variable.
        num_input = 0;
        num_output = 0;
        num_hidden = 0;
        num_per_hidden = 0;
        input_file >> num_input >> num_output >> num_hidden >> num_per_hidden;

        slices.resize(2+num_hidden);
        slices[0].resize(num_input);
        for (int i = 0; i < num_hidden; i++) slices[i+1].resize(num_per_hidden);
        slices[1 + num_hidden].resize(num_output);

        // Initialize 2D vector of neurons with default constructor
        for (unsigned int i = 0; i < slices.size(); i++)
        {
            for (unsigned int j = 0; j < slices[i].size(); j++)
            {
                slices[i][j] = new neuron();
            }
        }
        for (int i = 0; i < (2 + num_hidden); i++) // Each iteration represents a slice
        {
            int slice_height;
            int post_per_node;
            if (i == 0)
            {
                slice_height = num_input;
                post_per_node = num_per_hidden;
            }
            else if (i < num_hidden + 1)
            {
                slice_height = num_per_hidden;
                if (i == num_hidden) post_per_node = num_output;
                else post_per_node = num_per_hidden;
            }
            else
            {
                slice_height = num_output;
                post_per_node = 0;
            }
            for (int j = 0; j < slice_height; j++) // Each iteration represents a neuron in a slice
            {
                // For each node output the threshold, bias, and weights
                float thresh_val;
                float bias_val;
                input_file >> thresh_val;
                input_file >> bias_val;
                slices[i][j]->threshold = thresh_val;
                slices[i][j]->bias = bias_val;
                slices[i][j]->state = bias_val; // set the initial state
                vector<float> weights;
                vector<neuron*> posts;
                for (int k = 0; k < post_per_node; k++)
                {
                    float weight_val;
                    input_file >> weight_val;
                    weights.push_back(weight_val);
                    posts.push_back(slices[i+1][k]);
                }
                slices[i][j]->weights = weights;
                slices[i][j]->post_neurons = posts;
            }
        }
    }

    string input;
    while (getline(cin,input))
    {
        istringstream ist;
        ist.str(input);

        // Adjust the input for each parameter. The goal is for each input to fall between -1 and 1
        for (int i = 0; i < num_input; i++)
        {
            float in;
            ist >> in;
            if (i < 3)
            {
                slices[0][i]->state = in / 100;
            }
            if (i > 2 && i < 6)
            {
                if (in < 0)
                {
                    in = in * -1;
                    in = in - (360 * (((int)in) / 360));
                    in = in  * -1;
                }
                else
                {
                    in = in - (360 * (((int)in) / 360));
                }
                slices[0][i]->state = in / 360;
            }
            else
            {
                slices[0][i]->state = in / 100;
            }
        }
        
        // Propogate the signal trhough each singal.
        // If a neuron does not fire, then its state is retained.
        // If a neuron does fire, then its current state is set to its respective bias
        for (unsigned int i = 0; i < slices.size() - 1; i++)
        {
            for (unsigned int j = 0; j < slices[i].size(); j++)
            {
                if (slices[i][j]->state >= slices[i][j]->threshold)
                {
                    for (unsigned int k = 0; k < slices[i][j]->post_neurons.size(); k ++)
                    {
                        slices[i][j]->post_neurons[k]->state += slices[i][j]->weights[k] * slices[i][j]->state;
                    }
                    slices[i][j]->state = slices[i][j]->bias;
                }
            }
        }
        
        // Handel interpreting output
        for (unsigned int i = 0; i < slices[1+num_hidden].size(); i++)
        {
            if (i != 0) cout << " ";
            float val = slices[1+num_hidden][i]->state;
            if (i < 2)
            {
                if (slices[1+num_hidden][i]->state >= slices[1+num_hidden][i]->threshold)
                {
                    val = val * 90;
                    if (val < -90) val = -90;
                    else if (val > 90) val = 90;
                    cout << val;
                    slices[1+num_hidden][i]->state = slices[1+num_hidden][i]->bias;
                }
                else cout << 0;
            } 
            else
            {
                if (slices[1+num_hidden][i]->state >= slices[1+num_hidden][i]->threshold)
                {
                    val = val * 2;
                    if (val < 0) val = 0;
                    else if (val > 2) val = 2;
                    cout << val;
                    slices[1+num_hidden][i]->state = slices[1+num_hidden][i]->bias;
                }
                else cout << 0;
            }
        }
        cout << endl;
    }
    // clean up the vector of pointers
    for (unsigned int i = 0; i < slices.size(); i++)
    {
        for (unsigned int j = 0; j < slices[i].size(); j++) delete slices[i][j];
    }    
    return 0;
}

neuron::neuron()
{
    refractory = false; // This is not used.
    state = 0;
    threshold = 0;
    bias = 0;
}