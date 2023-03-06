#include "neural_network.h"
#include <stdlib.h>
#include <time.h>

using namespace std;

Neural_Network::Neural_Network(int in, int out, vector<int> hidden) {

    // create input layer
    for(int i = 0; i < in; i++) {

        input_layer.push_back(Neuron());

    }

    // create output layer
    for(int i = 0; i < out; i++) {

        output_layer.push_back(Neuron());

    }

    // create hidden layer
    for(int i = 0; i < hidden.size(); i++) {

        for(int j = 0; j < hidden.at(i); j++) {

            hidden_layer.at(i).push_back(Neuron());

        }

    }

    int hidden_layers = hidden.size();

}

// deconstructor not done
Neural_Network::~Neural_Network() {



}

void Neural_Network::randomize() {

    // randomize rand() seed
    srand(time(NULL));

    // randomize weights and biases in input layer
    for(int i = 0; i < input_layer.size(); i++) {

        for(int j = 0; j < input_layer.at(i).getConnections(); j++) {
            
            input_layer.at(i).setBias(j, rand());
            input_layer.at(i).setWeight(j, rand());

        }

    }

    // randomize weights and biases in hidden layers
    for(int i = 0; i < hidden_layer.size(); i++) {

        for(int j = 0; j < hidden_layer.at(i).size(); j++) {

            for(int k = 0; k < hidden_layer.at(i).at(j).getConnections(); k++) {

                hidden_layer.at(i).at(j).setBias(k, rand());
                hidden_layer.at(i).at(j).setWeight(k, rand());

            }

        }

    }

}

void Neural_Network::calculate() {

    

}