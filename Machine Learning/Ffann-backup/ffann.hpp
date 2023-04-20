// ffann.hpp
// Contributro: Phillip Graham
// Time Started: March, 27, 2023
// Last Edited: April, 11, 2023
// Description: This file contains the initilization of the classes which will be used 
// 		for my implementation of a feed forward, artificial, neural network.
// 		It will initialize our neuron, synapse, and ffann classes.

#include <vector>
#include <string> 

using namespace std;

class ffann
{
	public:
		ffann(int,int,int,string);
		vector<int> evaluate_network(vector<int>);
		void print_network ();
	private:
		vector<vector<int>> states;
		vector<vector<int>> thresholds;
		vector<vector<vector<int>>> weights;
		int num_input;
		int num_output;
		int num_hidden_layer;
		int num_neurons;
};
