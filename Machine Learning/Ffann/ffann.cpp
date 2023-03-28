// ffann.cpp
// Contributor: Phillip Graham
// Time Started: March, 05, 2023
// Last Edited: March, 27, 2023
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

synapse::synapse(int weight_param,neuron* pre_param,neuron* post_param)
{
	pre_neuron = pre_param;
	post_neuron = post_param;
	weight = weight_param;
}

synapse::~synapse()
{
	if (post_neuron != NULL)
	{
		delete post_neuron;
	}
}

bool synapse::propigate(int spike_param)
{
	spike_param = spike_param * weight;
	return this->post_neuron->set_and_fire(spike_param);
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
		for (size_t i = 0; i < outputs.size(); i++)
		{
			outputs[i]->propigate(state);
		}
		state = 0;
		return true;
	}
	return false;
}

ffann::ffann (int num_input_param,int num_output_param,int num_hidden_layer_param)
{
        num_input = num_input_param;
        num_output = num_output_param;
        num_hidden_layer = num_hidden_layer_param;
        num_neurons = num_input + num_output + (num_input + num_output) * num_hidden_layer_param;
}

ffann::~ffann ()
{
	for (size_t i = 0; i < input.size(); i++) delete input[i];
}

void ffann::generate_network ()
{
        // TODO: Create code to generate a brain
}

vector <int> ffann::evaluate_network (vector <int> input_vector_param)
{
        vector <int> evaluation_vector;
	// TODO: Create the neccessary code for this function
	return evaluation_vector;
}
