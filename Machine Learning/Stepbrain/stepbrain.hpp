// stepbrain.hpp
// Contributor: Phillip Graham
// Time Started: March, 05, 2023 @ 6:30 pm
// Last Edited: March, 05, 2023 @ 10:00 pm
// Logged Time: 2:00 
// Description: This file is made to act as a header file to describe the object called
//              step brain. This object is used to implement a neuralnetwrok of my design.
//              This file will be used by stepbrain.cpp which will describe the functions
//              of all of the proceeding initialized functions and objects. It will also
//              be used by main.cpp which will creae stepbrains and then output them to
//              the user for later use in scripts
#ifndef STEP_BRAIN
#define STEP_BRAIN

using namespace std;
#include <string>
#include <vector>

class stepbrain
{
	public:
		stepbrain(int num_input_param,int num_output_param, int num_hidden_layer_param);
		~stepbrain();
		vector <int> evaluate_brain (vector <int>);	// For a given vector of inputs, get a vector of outs 
	private:
	        void generate_brain();
	        		 
		vector <char> neuron_class_vector;
		vector <vector<int>> pre_neuron_vector_vector;
		vector <vector<int>> pre_weights_vector_vector;
		vector <int> firing_threshold_vector;
		vector <bool> neuron_evaluation_vector;
		int num_input;
		int num_output;
		int num_hidden_layer;
		int num_neurons;
};
#endif
