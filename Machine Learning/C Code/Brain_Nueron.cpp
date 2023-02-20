// driver file for the brain_nueron header
// Matthew Bringle
// 2/19/2023

#include "Brain_Nueron.h"
#include <algorithm>

int Brain::setColumns(int columnNum) {
    if (columns == -1) {
        columns = columnNum;
        return true;
    } else {
        return false;
    }
}

int Brain::addNueron(Nueron *nueronToAdd) {
    if (std::find(nueronContainer.begin(), nueronContainer.end(), nueronToAdd) != nueronContainer.end()) {
        return false; // Nueron already in container
    }
    else {
        nueronContainer.push_back(nueronToAdd);
        return true;
    }
}

int Brain::removeNueron(Nueron *nueronToRemove) {
    auto it = std::find(nueronContainer.begin(), nueronContainer.end(), nueronToRemove);
    if (it != nueronContainer.end()) {
        nueronContainer.erase(it);
        return true;
    }
    else {
        return false; // Nueron not found in container
    }
}

int Brain::removeNueronByID(std::string ID) {
    auto it = std::find_if(nueronContainer.begin(), nueronContainer.end(), [&](Nueron* n) {
        return n->ID == ID;
    });
    if (it != nueronContainer.end()) {
        nueronContainer.erase(it);
        return true;
    }
    else {
        return false; // Nueron not found in container
    }
}