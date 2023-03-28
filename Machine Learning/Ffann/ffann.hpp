// ffann.hpp
// Contributro: Phillip Graham
// Time Started: March, 27, 2023
// Last Edited: March, 27, 2023
// Description: This file contains the initilization of the classes which will be used 
// 		for my implementation of a feed forward, artificial, neural network.
// 		It will initialize our neuron, synapse, and ffann classes.

#include <vector>

using namespace std;

class neuron;

class synapse
{
	friend class neuron;
	public:
		synapse(int,neuron*, neuron*);
		~synapse();
		bool propigate(int);
	private:
		int weight;
		neuron * pre_neuron;
		neuron * post_neuron;
};

class neuron
{
	friend class ffann;
	public:
		neuron(int);
		~neuron();
		bool set_and_fire (int);
	private:
		int threshold;
		int state;
		vector <synapse*> inputs;
		vector <synapse*> outputs;
};

class ffann
{
	public:
		ffann(int,int,int);
		~ffann();
		vector<int> evaluate_network(vector<int>);
		void generate_network ();
	private:
		vector<neuron*> input;
		vector<neuron*> output;
		int num_input;
		int num_output;
		int num_hidden_layer;
		int num_neurons;
};
