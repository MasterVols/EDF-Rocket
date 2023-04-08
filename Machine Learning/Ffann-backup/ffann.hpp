// ffann.hpp
// Contributro: Phillip Graham
// Time Started: March, 27, 2023
// Last Edited: April, 08, 2023
// Description: This file contains the initilization of the classes which will be used 
// 		for my implementation of a feed forward, artificial, neural network.
// 		It will initialize our neuron, synapse, and ffann classes.

#include <vector>
#include <string> 

using namespace std;

class neuron;

class synapse
{
	friend class neuron;
	public:
		synapse(int);
		~synapse();
		bool propigate(int);
		void set_post(neuron*);
	private:
		int weight;
		neuron * post_neuron;
};

class neuron
{
	friend class ffann;
	public:
		neuron(int);
		~neuron();
		bool set_and_fire (int);
		void generate_post_synapse (vector<int>);
	private:
		int threshold;
		int state;					// The state represents the accumulation of a neurons inputs
		vector <synapse*> outputs;
};

class ffann
{
	public:
		ffann(int,int,int,string);
		~ffann();
		vector<int> evaluate_network(vector<int>);
		void generate_network (string);
	private:
		vector<neuron*> network;
		int num_input;
		int num_output;
		int num_hidden_layer;
		int num_neurons;
};
