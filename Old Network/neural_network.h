#ifndef NEURAL_NETWORK
#define NEURAL_NETWORK

#include "neuron.h"
#include <vector>

class Neural_Network {

    public:

        Neural_Network(int, int, std::vector<int>);
        ~Neural_Network();

        // need a function to train the network and access a set of training data
        // need a backpropagation function for training

        void randomize();

        // uses command line for input and output; most likely bad setup for training
        void calculate();

        void print();


    private:

        std::vector<Neuron> input_layer;
        std::vector<Neuron> output_layer;
        std::vector<std::vector<Neuron>> hidden_layer;
        int hidden_layers;

};

#endif