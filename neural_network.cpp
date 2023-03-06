#include "neural_network.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

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

        vector<Neuron> vec;
        hidden_layer.push_back(vec);

        for(int j = 0; j < hidden.at(i); j++) {

            hidden_layer.at(i).push_back(Neuron());

        }

    }

    int hidden_layers = hidden.size();


    // create weights and biases
    
    // randomize rand() seed
    srand(time(NULL));

    for(int i = 0; i < input_layer.size(); i++) {

        for(int j = 0; j < hidden_layer.at(0).size(); j++) {
        
            input_layer.at(i).createWeight(rand());
            input_layer.at(i).createBias(rand());

        }

    }

    cout << "created input layer weights/biases" << endl;

    cout << hidden_layer.size() << endl;
    cout << hidden_layer.at(0).size() << endl;
    cout << hidden_layer.at(1).size() << endl;
    cout << hidden_layer.at(2).size() << endl << endl;
    
/*
    for(int i = 0; i < hidden_layer.size()-1; i++) {

        cout << i;

        for(int j = 0; j < hidden_layer.at(i).size(); i++) {

            cout << j;

            for(int k = 0; k < hidden_layer.at(i+1).size(); k++) {

                cout << k;

                hidden_layer.at(i).at(j).createWeight(rand());
                hidden_layer.at(i).at(j).createBias(rand());

            }

        }

    }
*/
    cout << "created hidden layer weights/biases" << endl;

    for(int i = 0; i < hidden_layer.at(hidden_layer.size()-1).size(); i++) {

        for(int j = 0; j < output_layer.size(); j++) {

            hidden_layer.at(hidden_layer.size()-1).at(i).createWeight(rand());
            hidden_layer.at(hidden_layer.size()-1).at(i).createBias(rand());

        }

    }

    cout << "created ouptut layer weights/biases" << endl;


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

void Neural_Network::print() {

    // Print Input Layer

    cout << "Input Layer:" << endl;

    for(int i = 0; i < input_layer.size(); i++) {

        cout << "Weights" << endl;
        input_layer.at(i).printWeights();

        cout << "Biases" << endl;
        input_layer.at(i).printBiases();

    }

    // Print Hidden Layer

    cout << "Hidden Layer:" << endl;

    for(int i = 0; i < hidden_layer.size(); i++) {

        for(int j = 0; j < hidden_layer.at(i).size(); j++) {

            cout << "Weights" << endl;
            hidden_layer.at(i).at(j).printWeights();

            cout << "Biases" << endl;
            hidden_layer.at(i).at(j).printBiases();

        }

    }

}

void Neural_Network::calculate() {

    

}