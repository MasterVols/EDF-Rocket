#include "neuron.h"
#include <iostream>

using namespace std;

Neuron::Neuron() {

    value = 0;
    connections = 0;

}

Neuron::Neuron(int i) {

    value = i;
    connections = 0;

}

Neuron::~Neuron() {


    
}

double Neuron::getWeight(int i) {

    return weights.at(i);

}

double Neuron::getBias(int i) {

    return biases.at(i);

}

void Neuron::printWeights() {

    for(int i = 0; i < weights.size(); i++) {

        cout << weights.at(i) << endl;

    }

}

void Neuron::printBiases() {

    for(int i = 0; i < biases.size(); i++) {

        cout << biases.at(i) << endl;

    }

}

int Neuron::getConnections() {

    return connections;

}

double Neuron::getValue() {

    return value;

}

double Neuron::setWeight(int i, double j) {

    weights.at(i) = j;

} 

double Neuron::setBias(int i, double j) {

    biases.at(i) = j;

} 

double Neuron::setValue(double i) {

    value = i;

} 

