// stepbrain.cpp
// Contributor: Phillip Graham
// Time Started: March, 05, 2023 @ 10:00 pm
// Last Edited: March, 05, 2023 @ 11:00 pm
// Logged time: 1:00
// Description: This file is made to act as the main file for describing
//              our objece stepbrain. This object is used to implement a
//              neuralnetwork of my design. This file will be used by my
//              main which will use the structures and functions declared
//              in this file to create a neural network. It will then
//              output these networks to the user.


using namespace std;
#include <string>
#include <vector>
#include "stepbrain.hpp"

stepbrain::stepbrain (int num_input_param,int num_output_param,int num_hidden_layer_param)
{
        num_input = num_input_param;
        num_output = num_output_param;
        num_hidden_layer = num_hidden_layer_param;
        num_neurons = num_input + num_output + ((num_hidden_layer * (num_hidden_layer + 1)) / 2) + (num_hidden_layer * num_input);

}

stepbrain::~stepbrain ()
{
        // TODO: Create the deconstructor for this class
}

void stepbrain::generate_brain ()
{
        // TODO: Create code to generate a brain
}

vector <int> stepbrain::evaluate_brain (vector <int> input_vector_param)
{
        vector <int> evaluation_vector;
	// TODO: Create the neccessary code for this function
	return evaluation_vector;
}
