// gennet.cpp
// Contributor: Phillip Graham
// Start Time: April, 25, 2023
// Last Edited: April, 08, 2023
// Logged Time: 0:05

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <random>
using namespace std;

float ranf(float,float);

int main()
{
    // time for random numbers
    srand(time(0));

    // variables that define our network
    int num_in, num_out, num_hidden, num_per_hidden;
    float thresh_min, thresh_max, weight_min, weight_max;
    num_in = 9;
    num_out = 3;
    num_hidden = 2;
    num_per_hidden = 9;
    thresh_min = -1;
    thresh_max = 1;
    weight_min = -1;
    weight_max = 1;

    // This file is used to determine what to number the network generated
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
    if (outputFile.is_open())
    {
        outputFile << num_in << " " << num_out << " " << num_hidden << " " << num_per_hidden << endl;
        for (int i = 0; i < num_in; i++)
        {
            outputFile << ranf(thresh_min,thresh_max);
            for (int j = 0; j < num_per_hidden; j++) outputFile << " " << ranf(weight_min,weight_max);
            outputFile << endl;
        }
        for (int i = 0; i < (num_hidden - 1) * num_per_hidden; i++)
        {
            outputFile << ranf(thresh_min,thresh_max);;
            for (int j = 0; j < num_per_hidden; j++) outputFile << " " << ranf(weight_min,weight_max);
            outputFile << endl;
        }
        for (int i = 0; i < num_per_hidden; i++)
        {
            outputFile << ranf(thresh_min,thresh_max);
            for (int j = 0;j<num_out;j++) outputFile << " " << ranf(weight_min,weight_max);
            outputFile << endl;
        }
        for (int i = 0; i < num_out; i++)
        {
            outputFile << ranf(thresh_min,thresh_max);
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

float ranf(float min,float max)
{
    mt19937 gen(random_device{}());
    uniform_real_distribution<float> distr(min,max);
    return distr(gen);
}
