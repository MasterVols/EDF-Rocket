#include "neural_network.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {

    int input_layer_size;
    int output_layer_size;
    int num_hidden_layers;
    vector<int> hidden_layer_sizes;

    cout << "Enter size of input layer as an int";
    cin >> input_layer_size;
    cout << endl;
    cout << "Enter size of output layer as an int";
    cin >> output_layer_size;
    cout << endl;
    cout << "Enter number of hidden layers as an int";
    cin >> num_hidden_layers; 
    cout << endl;
    cout << "Enter size of each hidden layer as an int" << endl;

    int temp;

    for(int i = 0; i < num_hidden_layers; i++) {

        cin >> temp;
        hidden_layer_sizes.push_back(temp);

    }

    Neural_Network happy = Neural_Network(input_layer_size, output_layer_size, hidden_layer_sizes);

    happy.randomize();

    happy.print();

    return 1;

}