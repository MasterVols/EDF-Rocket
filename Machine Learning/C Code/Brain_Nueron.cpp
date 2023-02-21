// driver file for the brain_nueron header
// Matthew Bringle
// 2/19/2023

#include "Brain_Nueron.h"
#include "Random_Number_Generators.cpp"
#include <algorithm>


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
    //debug
    //std::cout << "Created Brain Instance" << std::endl;
    
    columns = columnNum;
    inputs = inputNum;
    outputs = outputNum;

    //cout << "Sizing Vectors... ";
    outputValues.resize(outputs);
    inputValues.resize(inputs);
    nueronContainer.resize(columns + 1);
    //sizes each vector to zero:
    for (auto& innerVector : nueronContainer) {
        innerVector.resize(0);
    }
    //cout << "DONE!" << endl;

    // Nueron Population:
    //cout << "Creating Nueron Population Counter... ";
    int nueronId = 0;
    //cout << "DONE!" << endl;

    // start with outputs
    for (int c = 0; c < outputs; c++) {
        Nueron* newNueron = new Nueron;
        newNueron->ID = nueronId;
        //cout << "Output Nueron Created, ID=" << newNueron->ID << endl;

        nueronId++;
        nueronContainer[columns].push_back(newNueron);

        //NOTE: outputNodes should not have any mutations
    }

    // middle nuerons
    int iteration;
    for (int i = columns + 1; i > 0; i--) {
        for (int c = 0; c < inputs; c++) {
            Nueron* newNueron = new Nueron;
            newNueron->ID = nueronId;
            nueronId++;

            // mutate values 
            newNueron->triggerLevel = (newNueron->triggerLevel) + getRandomDoubleInRange((1 - newNueron->hardness + mutationFactor) * 1.0);
            newNueron->outputLevel = (newNueron->outputLevel) + getRandomDoubleInRange((1 - newNueron->hardness + mutationFactor) * 1.0);
            newNueron->hardness = (newNueron->hardness) + getRandomDoubleInRange((1 - newNueron->hardness + mutationFactor) * 1.0);

            //debug:
            //cout << "Creating Nueron ID=" << newNueron->ID << " Will exist on column=" << i - 1<< endl;

            //find things to point to in next column. Odd case if next line is the outputs
            if (i == columns + 1) {
                //cout << "Making Connections for Nueron ID=" << newNueron->ID << endl;
                //odd case:
                for (int j = 0; j < newNueron->amountOfConnections; j++) {
                    Nueron* pointer = nueronContainer[columns][getRandomIntInRange(0, outputs - 1)];
                    newNueron->connections.push_back(pointer);
                }
                //cout << "Connections made for Nueron ID=" << newNueron->ID << endl;

            } else {

                //cout << "Making Connections for Nueron ID=" << newNueron->ID << endl;

                //usual case:
                for (int j = 0; j < newNueron->amountOfConnections; j++) {
                    iteration = columns - i;
                    Nueron* pointer = nueronContainer[columns - iteration][getRandomIntInRange(0, inputs - 1)];
                    newNueron->connections.push_back(pointer);
                }
                //cout << "Connections made for Nueron ID=" << newNueron->ID << endl;
            }

            // push into vector
            nueronContainer[i-1].push_back(newNueron);

        }
    }

}
