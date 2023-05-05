#include "neural_network.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {

    int input_layer_size;
    int output_layer_size;
    int num_hidden_layers;
    vector<int> hidden_layer_sizes;

    cout << "Enter size of input layer as an int: ";
    cin >> input_layer_size;
    cout << endl;
    cout << "Enter size of output layer as an int: ";
    cin >> output_layer_size;
    cout << endl;
    cout << "Enter number of hidden layers as an int: ";
    cin >> num_hidden_layers; 
    cout << endl;
    cout << "Enter size of each hidden layer as an int: ";

    int temp;

    for(int i = 0; i < num_hidden_layers; i++) {

        cin >> temp;
        cout << " ";
        hidden_layer_sizes.push_back(temp);

    }

    cout << endl;

    Neural_Network happy = Neural_Network(input_layer_size, hidden_layer_sizes, output_layer_size);

    happy.randomize();

    //happy.print();

    vector<double> nums = {5.00, -3.00, 0.08, 60.00, -0.20};

    vector<double> solution = happy.compute(nums);

    happy.print();

    cout << "Solution: " << endl;

    for(unsigned long int i = 0; i < solution.size(); i++) {

        cout << solution.at(i) << endl;
        
    }

    return 1;

}