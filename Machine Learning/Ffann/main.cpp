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

void print_net(vector<neuron>);

const bool print_mode = false;
const bool enable_thresholds = false;

int main ()
{
    ifstream inputrepnum("repnum.txt");
    int file_num;
    inputrepnum >> file_num;
    inputrepnum.close();
	ifstream input_file("./networks/network" + to_string(file_num-1) + ".txt");
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
        for (unsigned int i = 0; i < nv.size(); i++) nv[i].state = 0;
        for (int i = 0; i < num_input; i++) ist >> nv[i].state;
        for (int i = 3; i < 6; i++) nv[i].state = nv[i].state/360;
        int i = 0;
        for (i=i;i < num_input; i++)
        {
            if (nv[i].state < nv[i].threshold) continue;
            for (unsigned int j = 0; j < nv[i].weights.size(); j++)
            {
                nv[num_input + j].state += (nv[i].state * nv[i].weights[j]);
            }
        }
        for (i=i;i < num_input + (num_hidden * num_per_hidden); i++)
        {
            if ((nv[i].state) < (nv[i].threshold)) continue;
            for (unsigned int j = 0; j < nv[i].weights.size(); j++)
            {
                nv[(i - (i%num_per_hidden))+num_per_hidden+j].state += (nv[i].state * nv[i].weights[j]);
            }
        }
    
        float rota = nv[i].state * 90;
        if (rota > 90) rota = 90;
        else if (rota < -90) rota = -90;
        cout << rota;
        i++;
        float rotb = nv[i].state * 90;
        if (rotb > 90) rotb = 90;
        else if (rotb < -90) rotb = -90;
        cout << " " << rotb;
        i++;
        float thrust = nv[i].state * 2;
        if (thrust > 2) thrust = 2;
        else if (thrust < 0) thrust = 0;
        cout << " " << thrust << endl;
        if (print_mode) print_net(nv);
    }
    return 0;
}

neuron::neuron(float t,vector<float> v)
{
    threshold = t;
    weights = v;
    state = 0;
}

void print_net (vector<neuron> nv)
{
    for (unsigned int i = 0; i < nv.size(); i++)
    {
        cout << "[" << i << "] " << "state:" << nv[i].state << " thresh:" << nv[i].threshold;
        for (unsigned int j = 0; j < nv[i].weights.size(); j++) cout << " weight" << j << ":" << nv[i].weights[j];
        cout << endl;
    }
}
