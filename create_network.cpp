#include "neural_network.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {

    int input_layer_size;
    int output_layer_size;
    int num_hidden_layers;
    vector<int> hidden_layer_sizes;

    cout << "Enter size of input layer as an int" << endl;
    cin >> input_layer_size;
    cout << "Enter size of output layer as an int" << endl;
    cin >> output_layer_size;
    cout << "Enter number of hidden layers as an int" << endl;
    cin >> num_hidden_layers; 
    cout << "Enter size of each hidden layer as an int" << endl;

    int temp;

    for(int i = 0; i < num_hidden_layers; i++) {

        cin >> temp;
        hidden_layer_sizes.push_back(temp);

    }

    cout << "here" << endl; 

    Neural_Network happy = Neural_Network(input_layer_size, output_layer_size, hidden_layer_sizes);

    cout << "made it" << endl;

    happy.randomize();

    happy.print();

    return 1;

}