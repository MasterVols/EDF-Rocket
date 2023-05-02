#include "neural_network.h"
#include "time.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

Neural_Network::Neural_Network(int input_layer_size, vector<int> hidden_layer_sizes, int output_layer_size) {

    cout << "Starting Constructor" << endl;

    num_hidden_layers = hidden_layer_sizes.size();
    num_layers = num_hidden_layers + 2;

    // fill layer_sizes vector

    layer_sizes.push_back(input_layer_size);
    
    for(long unsigned int i = 0; i < hidden_layer_sizes.size(); i++) {

        layer_sizes.push_back(hidden_layer_sizes.at(i));

    }

    cout << "Filled Layer Sizes" << endl;

    layer_sizes.push_back(output_layer_size);

    // properly size activations vector

    activations.resize(num_layers);

    for(int i = 0; i < num_layers; i++) {

        activations.at(i).resize(layer_sizes.at(i));

    }

    cout << "Filled Activations" << endl;

    // properly size weights vector

    weights.resize(num_layers - 1);

    for(int i = 1; i < num_layers; i++) {

        weights.at(i - 1).resize(layer_sizes.at(i));

        for(long unsigned int j = 0; j < weights.at(i-1).size(); j++) {

            weights.at(i - 1).at(j).resize(layer_sizes.at(i - 1));

        }

    }

    cout << "Filled Weights" << endl;

    // properly size biases vector

    biases.resize(num_layers - 1);

    for(int i = 1; i < num_layers; i++) {

        biases.at(i - 1).resize(layer_sizes.at(i));

    }

    cout << "Filled Biases" << endl;

    cout << "Ending Constructor" << endl;

};

Neural_Network::~Neural_Network() {};

void Neural_Network::randomize() {

    cout << "Randomizing" << endl;

    // randomize rand() seed
    srand(time(NULL));

    double r;

    // randomize weights
    for(long unsigned int i = 0; i < weights.size(); i++) {

        for(long unsigned int j = 0; j < weights.at(i).size(); j++) {

            for(long unsigned int k = 0; k < weights.at(i).at(j).size(); k++) {

                r = rand();
                weights.at(i).at(j).at(k) = r / RAND_MAX;

            }

        }

    }

    // randomize biases
    for(long unsigned int i = 0; i < biases.size(); i++) {

        for(long unsigned int j = 0; j < biases.at(i).size(); j++) {

            /*
            r = rand();
            biases.at(i).at(j) = r / RAND_MAX;
            */

           biases.at(i).at(j) = 1.0;

        }

    }

};

void Neural_Network::train() {};

vector<double> Neural_Network::backpropagate() {

    

};

double Neural_Network::ReLU(double z) {

    if(z > 0) {

        return z;

    } else {

        return 0;

    }

};

void Neural_Network::print() {

    // print basic network info

    cout << endl << endl << endl;

    cout << "Printing out Neural Network" << endl << endl;

    cout << "Number of Layers: " << num_layers << endl << endl;

    for(int i = 0; i < num_layers; i++) {

        if(i == 0) {

            cout << "Input Layer Size: " << layer_sizes.at(0) << endl;

        } else if(i == num_layers - 1) {

            cout << "Output Layer Size: " << layer_sizes.at(num_layers - 1) << endl;

        } else {

            cout << "Hidden Layer (" << i << ") Size: " << layer_sizes.at(i) << endl;

        }

    }

    // print weights

    cout << endl << "Weights" << endl << endl;

    for(long unsigned int i = 0; i < weights.size(); i++) {

        for(long unsigned int j = 0; j < weights.at(i).size(); j++) {

            for(long unsigned int k = 0; k < weights.at(i).at(j).size(); k++) {

                cout << "(" << i << ")(" << j << ")(" << k << "): " << weights.at(i).at(j).at(k) << endl;

            }

        }

    }

    // print biases

    cout << endl << "Biases" << endl << endl;

    for(long unsigned int i = 0; i < biases.size(); i++) {

        for(long unsigned int j = 0; j < biases.at(i).size(); j++) {

            cout << "(" << i << ")(" << j << "): " << biases.at(i).at(j) << endl;

        }

    }

    // print activations

    cout << endl << "Activations" << endl << endl;

    for(long unsigned int i = 0; i < activations.size(); i++) {

        for(long unsigned int j = 0; j < activations.at(i).size(); j++) {

            cout << "(" << i << ")(" << j << "): " << activations.at(i).at(j) << endl;

        }

    }

    cout << endl << endl;

};

vector<double> Neural_Network::compute(vector<double> inputs) {

    cout << "Computing" << endl;

    double weighted_sum;

    for(int i = 0; i < num_layers; i++) {

        // input layer
        if(i == 0) {

            for(int j = 0; j < layer_sizes.at(i); j++) {

                cout << "Relu: " << ReLU(inputs.at(j)) << endl;

                activations.at(i).at(j) = ReLU(inputs.at(j));

                cout << "Activate: " << activations.at(i).at(j);

            }

        // hidden layers and output layer
        } else {

            for(int j = 0; j < layer_sizes.at(i); j++) {

                weighted_sum = 0; 

                for(int k = 0; k < layer_sizes.at(i - 1); k++) {

                    weighted_sum += activations.at(i - 1).at(k) * weights.at(i - 1).at(j).at(k);

                }

                activations.at(i).at(j) = ReLU(weighted_sum - biases.at(i - 1).at(j));

            }

        }

    }

    return activations.at(num_layers - 1);

    cout << "Done Computing" << endl;

};