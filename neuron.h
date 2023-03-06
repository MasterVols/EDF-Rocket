#ifndef NEURON
#define NEURON

#include <vector>

class Neuron {

    public:

        Neuron();
        Neuron(int);
        ~Neuron();

        void printWeights();
        void printBiases();
        double getWeight(int);
        double getBias(int);
        int getConnections();
        double getValue();
        double setWeight(int, double);
        double setBias(int, double);
        double setValue(double);

    private:

        double value;
        int connections;
        std::vector<double> weights;
        std::vector<double> biases; 

};

#endif