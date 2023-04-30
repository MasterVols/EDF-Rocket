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
        void setWeight(int, double);
        void setBias(int, double);
        void setValue(double);
        void createWeight(double);
        void createBias(double);

    private:

        double value;
        int connections;
        std::vector<double> weights;
        std::vector<double> biases; 

};

#endif