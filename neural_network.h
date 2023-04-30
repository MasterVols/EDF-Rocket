#ifndef NEURAL_NETWORK
#define NEURAL_NETWORK

#include <vector> 

class Neural_Network {

    public:

    Neural_Network(int, std::vector<int>, int);
    ~Neural_Network();

    void randomize();
    void train();           // probably takes in training data
    void backpropagate();
    double ReLU(double);
    void print();
    std::vector<double> compute(std::vector<double>);

    private: 

    std::vector<int> layer_sizes;
    std::vector<std::vector<std::vector<double>>> weights;
    std::vector<std::vector<double>> biases;
    std::vector<std::vector<double>> activations;

    int num_layers;
    int num_hidden_layers;

};

#endif