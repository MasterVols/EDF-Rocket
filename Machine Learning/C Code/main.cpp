// Matthew Bringle
// Main for ML brain generation
// 2/19/2023

//#include "File_Checker.cpp"
#include <iostream>
#include "Brain_Nueron.cpp"

using namespace std;

int main() {
    // Create a brain with 2 columns, 2 input nodes, and 1 output node
    Brain myBrain(3, 0.5, 2, 1);

    // Print out the number of neurons in each column
    std::cout << "Number of neurons in each column:" << std::endl;
    for (int i = 0; i < myBrain.columns; i++) {
        std::cout << "Column " << i << ": " << myBrain.nueronContainer[i].size() << " neurons" << std::endl;
    }

    // Remove a neuron by ID
    myBrain.removeNueronByID(2);

    // Print out the number of neurons in each column again
    std::cout << "Number of neurons in each column after removing neuron with ID 2:" << std::endl;
    for (int i = 0; i < myBrain.columns; i++) {
        std::cout << "Column " << i << ": " << myBrain.nueronContainer[i].size() << " neurons" << std::endl;
    }

    // Add a new neuron to column 0
    Nueron* newNueron = new Nueron;
    myBrain.addNueron(newNueron, 0);

    // Print out the number of neurons in each column again
    std::cout << "Number of neurons in each column after adding a new neuron to column 0:" << std::endl;
    for (int i = 0; i < myBrain.columns; i++) {
        std::cout << "Column " << i << ": " << myBrain.nueronContainer[i].size() << " neurons" << std::endl;
    }

    return 0;
}

