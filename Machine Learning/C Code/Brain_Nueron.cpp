// driver file for the brain_nueron header
// Matthew Bringle
// 2/19/2023

#include "Brain_Nueron.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>


double getRandomDouble(double max) {
    // Seed the random number generator with the current time
    srand(static_cast<unsigned int>(time(nullptr)));

    // Generate a random number between 0 and 1, and scale it by max
    double random = static_cast<double>(rand()) / RAND_MAX;
    return random * max;
}


double getRandomDoubleInRange(double range) {
    // Seed the random number generator with the current time
    srand(static_cast<unsigned int>(time(nullptr)));

    // Generate a random number between 0 and 1, and scale it to the range [-1, 1]
    double random = static_cast<double>(rand()) / RAND_MAX;
    random = 2 * random - 1;

    // Scale the range to [-range, range], and return the result
    return random * range;
}


int Brain::setColumns(int columnNum) {
    if (columns == -1) {
        columns = columnNum;
        return true;
    } else {
        return false;
    }
}


int Brain::addNueron(Nueron *nueronToAdd, int column) {
    if (column < 0 || column >= columns) {              // Check if the column is valid
        return false;
    }

    for (auto& nueronPtr : nueronContainer[column]) {
        if (nueronPtr == nueronToAdd) {                 // Check if the nueron already exists in the specified column
            return false;
        }
    }

    nueronContainer[column].push_back(nueronToAdd);     // Add the nueron to the specified column
    return true;
}


int Brain::removeNueron(Nueron *nueronToRemove) {
    auto it = std::find(nueronContainer.begin(), nueronContainer.end(), nueronToRemove);
    if (it != nueronContainer.end()) {
        nueronContainer.erase(it);
        return true;
    }
    else {
        return false;                                   // Nueron not found in container
    }
}


int Brain::removeNueronByID(int ID) {
    // Find the nueron with the specified ID
    Nueron *nueronToRemove = nullptr;
    for (auto &column : nueronContainer) {
        for (auto &nueron : column) {
            if (nueron->ID == ID) {
                nueronToRemove = nueron;
                break;
            }
        }
        if (nueronToRemove) break;
    }
    
    // If the nueron was found, remove it from the connections of other nuerons and delete it
    if (nueronToRemove) {
        for (auto &column : nueronContainer) {
            for (auto it = column.begin(); it != column.end(); ) {
                if (*it == nueronToRemove) {
                    it = column.erase(it);
                } else {
                    (*it)->connections.erase(std::remove((*it)->connections.begin(), (*it)->connections.end(), nueronToRemove), (*it)->connections.end());
                    ++it;
                }
            }
        }
        delete nueronToRemove;
        return 1;
    }
    return 0;
}


Brain::Brain(int columnNum, double mutationFactor, int inputNum, int outputNum) {
    
    columns = columnNum;
    inputs = inputNum;
    outputs = outputNum;

    outputValues.resize(outputs);
    inputValues.resize(inputs);

    // Nueron Population:
    int nueronId = 0;

    // start with outputs
    for (int c = 0; c < outputs; c++) {
        Nueron* newNueron = new Nueron;
        newNueron->ID = nueronId;
        nueronId++;

        nueronContainer[columns].push_back(newNueron);

        //NOTE: outputNodes should not have any mutations
    }

    // middle nuerons
    for (int i = 0; i < columns; i++) {
        for (int c = 0; c < inputs; c++) {
            Nueron* newNueron = new Nueron;
            newNueron->ID = nueronId;
            nueronId++;

            // mutate values 
            newNueron->triggerLevel = (newNueron->triggerLevel) + getRandomDoubleInRange((1 - newNueron->hardness) * 1.0);
            newNueron->outputLevel = (newNueron->outputLevel) + getRandomDoubleInRange((1 - newNueron->hardness) * 1.0);
            newNueron->hardness = (newNueron->hardness) + getRandomDoubleInRange((1 - newNueron->hardness) * 1.0);

            //find things to point to in next column
            

            // push into vector
            nueronContainer[columns].push_back(newNueron);

        }
    }

}