// ffann.cpp
// Contributor: Phillip Graham
// Time Started: March, 05, 2023
// Last Edited: April, 08, 2023
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

synapse::synapse(int weight_param)
{
	post_neuron = NULL;
	weight = weight_param;
}

synapse::~synapse()
{
	if (post_neuron != NULL)
	{
		delete post_neuron;
	}
}

// Propigation will involve a synapse reading in a spike parameter, and then propigating
// that spike to its post-neuron after applying its weight to the spike
bool synapse::propigate(int spike_param)
{
	spike_param = spike_param * weight;
	return this->post_neuron->set_and_fire(spike_param);
}

void synapse::set_post (neuron* post_param)
{
	this->post_neuron = post_param;
}

neuron::neuron(int threshold_param)
{
	threshold = threshold_param;
	state = 0;
}

neuron::~neuron()
{
	for (size_t i = 0; i < outputs.size(); i++)
	{
		if (outputs[i] != NULL) delete outputs[i];
	}
}

bool neuron::set_and_fire(int state_param)
{
	state += state_param;
	if (state >= threshold)
	{
		for (size_t i = 0; i < outputs.size(); i++) outputs[i]->propigate(state);
		state = 0;
		return true;
	}
	return false;
}

ffann::ffann (int num_input_param,int num_output_param,int num_hidden_layer_param,string network_param)
{
	cout << "Begin to generate ffann\n";
    num_input = num_input_param;
	num_output = num_output_param;
    num_hidden_layer = num_hidden_layer_param;
    num_neurons = num_input + num_output + (num_input + num_output) * num_hidden_layer_param;
	network.resize(num_neurons);
	generate_network(network_param);
}

ffann::~ffann ()
{
	for (size_t i = 0; i < num_input; i++) delete network[i];
}

// TODO: Identify the error causing this to fail
void ffann::generate_network (string net_param)
{
	istringstream istr;
	istr.str(net_param);
	for (int i = 0; i < num_neurons; i++)
	{
		if (i < num_input) // If we are reading in input
		{
			int threshold;
			istr >> threshold;
			neuron* n_ptr = new neuron (threshold);
			n_ptr->outputs.resize(num_input + num_output);
			for (int j = 0; j > num_input + num_output; j++)
			{
				int weight;
				istr >> weight;
				synapse* s_ptr = new synapse(weight);
				n_ptr->outputs[j] = s_ptr;
			}
			network.push_back(n_ptr);
		}
		else if (i < (num_neurons - num_output)) // If we are reading in a hidden layer
		{
			int threshold;
			istr >> threshold;
			neuron* n_ptr = new neuron (threshold);
			if (num_input <= i && (i < (num_input * 2 + num_output)))
			{
				for (int j = 0; j < num_input; j++)
				{
					network[j]->outputs[i % num_input]->set_post(n_ptr);
				}
			}
			else
			{
				for (int j = 0; j < num_input + num_output; j++)
				{
					network[i - num_input - num_output + j]->outputs[(i - num_input) % (num_input + num_output)]->set_post(n_ptr);
				}
			}

			if (i + num_input + num_output < (num_neurons - num_output))
			{
				n_ptr->outputs.resize(num_input + num_output);
				for (int j = 0; j < num_input + num_output; j++)
				{
					int weight;
					istr >> weight;
					synapse* s_ptr = new synapse(weight);
					n_ptr->outputs[j] = s_ptr;
				}
			}
			else
			{
				n_ptr->outputs.resize(num_output);
				for (int j = 0; j < num_output; j++)
				{
					int weight;
					istr >> weight;
					synapse* s_ptr = new synapse(weight);
					n_ptr->outputs[j] = s_ptr;
				}
			}
			cout << "Made it to the end of the second\n";
		}
		else if (false) // If we are reading in an output layer
		{
			int threshold;
			istr >> threshold;
			neuron* n_ptr = new neuron (threshold);
			n_ptr->outputs.resize(0);
			for (int j = 0; j < num_input + num_output; j++)
			{
				network[network.size() - (num_output * 2) - num_input + j]->outputs[i - (num_input + (num_input + num_output) * num_hidden_layer)]->set_post(n_ptr);
			}
		}
	}
}

vector <int> ffann::evaluate_network (vector <int> input_vector_param)
{
    vector <int> evaluation_vector;
	for (size_t i = 0; i < input_vector_param.size(); i++)
	{
		network[i]->set_and_fire(input_vector_param[i]);
	}

	for (int i = 0; i < num_output; i++)
	{
		evaluation_vector.push_back(network[num_neurons - num_output + i]->state);
	}	
	return evaluation_vector;
}
