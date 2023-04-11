// ffann.cpp
// Contributor: Phillip Graham
// Time Started: March, 05, 2023
// Last Edited: April, 10, 2023
// Description: This file is made to act as the main file for describing
//              our objecy ffann. This object is used to implement a
//              neuralnetwork of my design. This file will be used by my
//              main which will use the structures and functions declared
//              in this file to create a neural network. It will then
//              output these networks to the user.

using namespace std;
#include <string>
#include <vector>
#include "ffann.hpp"
#include <sstream>
#include <iostream>

#include <vector>
#include <string> 

using namespace std;


ffann::ffann (int num_input_param,int num_output_param,int num_hidden_layer_param,string network_param)
{
    num_input = num_input_param;
	num_output = num_output_param;
    num_hidden_layer = num_hidden_layer_param;
    num_neurons = num_input + num_output + (num_input + num_output) * num_hidden_layer_param;
    states.resize(2+num_hidden_layer);
    weights.resize(2+num_hidden_layer);
    thresholds.resize(2+num_hidden_layer);

    istringstream istr (network_param);
    for (int i = 0; i < (2 + num_hidden_layer); i++)
    {
        int slice_height;
        int post_per_node;

        if (i == 0)
        {
            slice_height = num_input;
            post_per_node = num_input + num_output;
        }
        else if (i < num_hidden_layer + 1)
        {
            slice_height = num_input + num_output;
            if (i == num_hidden_layer) post_per_node = num_output;
            else post_per_node = num_output + num_input;
        }
        else
        {
            slice_height = num_output;
            post_per_node = 0;
        }

        thresholds[i].resize(slice_height,0);
        states[i].resize(slice_height,0);
        weights[i].resize(slice_height);
        for (int j = 0; j < slice_height; j++)
        {
            weights[i][j].resize(post_per_node,0);
        }
        

        for (int j = 0; j < slice_height; j++)
        {
            int thresh_val;
            istr >> thresh_val;
            thresholds[i][j] = thresh_val;
            for (int k = 0; k < post_per_node; k++)
            {
                int weight_val;
                istr >> weight_val;
                weights[i][j][k] = weight_val;
            }
        }
    }
}

vector <int> ffann::evaluate_network(vector<int> inp_param)
{
    vector <int> out_vect;
    
    for (int i = 0; i < num_input; i++)
    {
        states[0][i] = inp_param[i];
    }
    
    // Propigate the signals
    for (unsigned int i = 0; i < states.size() - 1; i++)
    {
        for (unsigned int j = 0; j < states[i].size(); j++)
        {
            if (states[i][j] >= thresholds[i][j])
            {
                for (unsigned int k = 0; k < weights[i][j].size(); k++)
                {
                    states[i+1][k] += states[i][j] * weights[i][j][k];
                }
            }
        }
        for (unsigned int j = 0; j < states[i].size(); j++)
        {
            states[i][j] = 0;
        }
    }
    
    for (int i = 0; i < num_output; i++)
    {
        out_vect.push_back(states[num_hidden_layer + 1][i]);
        states[num_hidden_layer + 1][i] = 0;
    }
    
    

    return out_vect;
}

void ffann::print_network()
{
    for (int i = 0; i < num_hidden_layer + 2; i++)
    {
        for (unsigned int j = 0; j < states[i].size(); j++)
        {
            cout << "S=" << states[i][j] << " T=" << thresholds[i][j];
            for (unsigned int k = 0; k < weights[i][j].size();k++)
            {
                cout << " W=" << weights[i][j][k];
            }
            if (j != states[i].size() - 1) cout << "___";
        }
        if (i != states.size() - 1) cout << "\n";
    }
}