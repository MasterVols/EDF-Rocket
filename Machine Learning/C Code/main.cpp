// Matthew Bringle
// Main for ML brain generation
// 2/19/2023

#include "Brain_Nueron.cpp"
#include "File_Checker.cpp"
#include <iostream>

using namespace std;

int main() {
    Brain brain;
    brain.setColumns(3);

    Nueron n1, n2, n3;
    n1.ID = "N1";
    n2.ID = "N2";
    n3.ID = "N3";

    brain.addNueron(&n1);
    brain.addNueron(&n2);
    brain.addNueron(&n3);

    std::cout << "Before removal: " << brain.removeNueron(&n2) << std::endl;
    std::cout << "After removal: " << brain.removeNueronByID("N3") << std::endl;

    return 0;
}