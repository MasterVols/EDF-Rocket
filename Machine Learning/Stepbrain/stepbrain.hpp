// stepbrain.hpp
// Contributor: Phillip Graham
// Time Started: March, 05, 2023 @ 6:30 pm
// Last Edited: March, 05, 2023 @ 7:00 pm
// Logged Time: 1:30 
// Description: This file is made to act as a header file to describe the object called
//              step brain. This object is used to implement a neuralnetwrok of my design.
//              This file will be used by stepbrain.cpp which will describe the functions
//              of all of the proceeding initialized functions and objects. It will also
//              be used by main.cpp which will creae stepbrains and then output them to
//              the user for later use in scripts
#ifdef STEP_BRAIN
#define STEP_BRAIN

using namespace std;
#include <string>
#include <vector>

class stepbrain
{
    public:
        stepbrain();
        stepbrain(int num_input,int num_output, int num_laayer)
        ~stepbrain();
    private:
        void generate_brain();
        vector <vector<int>> layer_vector; 
            // Each index describes one layer. The first index will always be the input
            // layer and the last input will always be the output layer.
}
#endif