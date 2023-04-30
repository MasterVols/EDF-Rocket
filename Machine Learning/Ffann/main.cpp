// main.cpp
// Contributor: Phillip Graham
// Start Time: March 05, 2023
// Last Edited: April, 25, 2023

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string> 

using namespace std;

struct neuron
{
    neuron (float,vector<float>);
    float threshold;
    float state;
    vector<float> weights;
};

const bool print_mode = true;
const bool enable_thresholds = false;

int main ()
{
	ifstream input_file("network.txt");
	if (!input_file.is_open())
	{
		cout << "ERROR: Could not open file: network.txt" << endl;
		return 1;
	}
    int num_input = 0, num_output = 0, num_hidden = 0, num_per_hidden = 0;
    vector <neuron> nv;
    input_file >> num_input >> num_output >> num_hidden >> num_per_hidden;
    for (int i = 0; i < (2 + num_hidden); i++)
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
        for (int j = 0; j < slice_height; j++)
        {
            float thresh_val;
            vector<float> weights;
            input_file >> thresh_val;
            for (int k = 0; k < post_per_node; k++)
            {
                float weight_val;
                input_file >> weight_val;
                weights.push_back(weight_val);
            }
            nv.push_back(neuron(thresh_val,weights));
        }
    }

    string input;
    while (getline(cin,input))
    {
        istringstream ist;
        ist.str(input);
        for (int i = 0; i < num_input; i++) ist >> nv[i].state;
        int i = 0;
        for (i=i;i < num_input; i++)
        {
            if ((nv[i].state * nv[i].state) < (nv[i].threshold * nv[i].threshold))
            {
                nv[i].state = 0;
            }
            for (unsigned int j = 0; j < nv[i].weights.size(); j++)
            {
                nv[num_input + j].state += nv[i].state * nv[i].weights[j];
            }
            nv[i].state = 0;
        }
        for (i=i;i < num_input + (num_hidden * num_per_hidden); i++)
        {
            if ((nv[i].state * nv[i].state) < (nv[i].threshold * nv[i].threshold))
            {
                nv[i].state = 0;
            }
            for (unsigned int j = 0; j < nv[i].weights.size(); j++)
            {
                nv[i+num_per_hidden+j].state += nv[i].state * nv[i].weights[j];
            }
            nv[i].state = 0;
        }
        cout << nv[i].state;
        nv[i].state = 0;
        i++;
        for (i=i;i < num_input + num_output + (num_hidden * num_per_hidden);i++)
        {
            cout << " " << nv[i].state;
            nv[i].state = 0;
        }
    }
    return 0;
}

neuron::neuron(float t,vector<float> v)
{
    threshold = t;
    weights = v;
    state = 0;
}
