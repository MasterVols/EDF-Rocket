// gennet.cpp
// Contributor: Phillip Graham
// Start Time: April, 25, 2023
// Last Edited: May, 08, 2023
// Purpose: This file is used to create the inital batch of randomly genereted neural networks required
//          for the operation of the prune_select_propogate script. This file works simply by constructing
//          and outputing text which matches my requirements for the network structure.

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <random>
using namespace std;

// The function I used to create random numbers. Employees repeated calls of std's random distrubtion
float ranf(float,float);

int main()
{
    // time for random numbers
    srand(time(0));

    // variables that define my network
    int num_in, num_out, num_hidden, num_per_hidden;
    float thresh_min, thresh_max, bias_min, bias_max, weight_min, weight_max;
    num_in = 9;
    num_out = 3;
    num_hidden = 9;
    num_per_hidden = 9;
    thresh_min = -1;
    thresh_max = 1;
    bias_min = -.25;
    bias_max = .25;
    weight_min = -1;
    weight_max = 1;

    // This file is used to determine what to number the network generated.
    // There is probably a more elegant aproach to this, but this was the
    // get-er-done aproach which came to my mind. This repnum.txt file
    // allows for my different c++ executables to communicate and synchronize
    // the network number. This allows for these executables to be
    // called in the python scripts without having to handle of this.
    ifstream inputrepnum("repnum.txt");
    int file_num;
    inputrepnum >> file_num;
    inputrepnum.close();
    ofstream orepn("repnum.txt");
    orepn << file_num + 1;
    orepn.close();
    // Create the appropriately named network text file
    std::ofstream outputFile("./networks/network" + to_string(file_num) + ".txt");

    // Output the network description to the file
    // Each new line should describe a neuron and contains its threshold and
    // all post synapses to the following slice.
    // Every neuron will have a threshold and a bias. The number of weights depends on the
    // connectivity of the concerned neuron
    if (outputFile.is_open())
    {
        outputFile << num_in << " " << num_out << " " << num_hidden << " " << num_per_hidden << endl;
        for (int i = 0; i < num_in; i++)
        {
            outputFile << ranf(thresh_min,thresh_max);
            outputFile << " " << ranf(bias_min,bias_max);
            for (int j = 0; j < num_per_hidden; j++) outputFile << " " << ranf(weight_min,weight_max);
            outputFile << endl;
        }
        for (int i = 0; i < (num_hidden - 1) * num_per_hidden; i++)
        {
            outputFile << ranf(thresh_min,thresh_max);
            outputFile << " " << ranf(bias_min,bias_max);
            for (int j = 0; j < num_per_hidden; j++) outputFile << " " << ranf(weight_min,weight_max);
            outputFile << endl;
        }
        for (int i = 0; i < num_per_hidden; i++)
        {
            outputFile << ranf(thresh_min,thresh_max);
            outputFile << " " << ranf(bias_min,bias_max);
            for (int j = 0;j<num_out;j++) outputFile << " " << ranf(weight_min,weight_max);
            outputFile << endl;
        }
        for (int i = 0; i < num_out; i++)
        {
            outputFile << ranf(thresh_min,thresh_max);
            outputFile <<  " " << ranf(bias_min,bias_max);
            outputFile << endl;
        }
        outputFile.close();
        cout << "Random numbers generated and written to network.txt" << std::endl;
    }
    else {
        std::cout << "Unable to open output file" << std::endl;
        return 1;
    }

    return 0;
}

// I found this solution using ChatGPT
// Originally I had issues with the random numbers I was producing because
// they had very little variation. I am not certain why this aproach
// produces a better distribution, but I find that this has been very good
// at produceing very even distributions of random numbers.
float ranf(float min,float max)
{
    mt19937 gen(random_device{}());
    uniform_real_distribution<float> distr(min,max);
    return distr(gen);
}
