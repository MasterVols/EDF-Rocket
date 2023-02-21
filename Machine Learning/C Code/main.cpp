// Matthew Bringle
// Main for ML brain generation
// 2/19/2023

using namespace std;

//#include "File_Checker.cpp"
#include <iostream>
#include "Brain_Nueron.cpp"


int main() {

    srand(static_cast<unsigned int>(time(nullptr)));

    // Create a brain with 2 columns, 2 input nodes, and 1 output node
    Brain myBrain(4, 0.5, 8, 3);

    // Output connections from every neuron
    for (int column = 0; column <= myBrain.columns; column++) {
        for (auto& nueronPtr : myBrain.nueronContainer[column]) {
            std::cout << "Nueron ID: " << nueronPtr->ID << std::endl;
            std::cout << "  Connections: ";
            for (auto& connectionPtr : nueronPtr->connections) {
                std::cout << connectionPtr->ID << " ";
            }
            std::cout << std::endl;
        }
    }

    return 0;
}

