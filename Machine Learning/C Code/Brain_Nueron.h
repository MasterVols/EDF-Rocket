#ifndef Brain_Nueron
#define Brain_Nueron

// Matthew Bringle
// Brain And Nueron Driver Code
// 2/19/2023

#include <string>
#include <vector>

struct Nueron {

    std::string ID = "";                //ID for each nueron
    std::vector<Nueron*> connections;   //Stores the pointers for the next nuerons in the connection
    
    double triggerLevel = 0.6;           //How much stimulation does Nueron need before firing?
    double outputLevel = 0.4;            //How much stimulation does the Nueron Produce?
    double hardness = 0.5;               //Refers to the likelyhood of this nueron having it's values changed

};

class Brain {

    public:

        int setColumns(int columnNum);              //returns false if already set
        int addNueron(Nueron *nueronToAdd);         //returns false if duplicate
        int removeNueron(Nueron *nueronToRemove);   //removes nueron based on refrence. False if Nueron doesn't exist
        int removeNueronByID(std::string ID);       //removes nueron from ID. False if Nueron doesn't exist
        
    private:

        int columns = -1;                       //columns are given by user where rows are naturally generated from math and inputValues

        std::vector<Nueron*> nueronContainer;   //contains all nuerons in brain
        std::vector<int> inputValues;           //holds all input values (1st column of nuerons)
        std::vector<int> outputValues;          //holds all output values (N-th column of nuerons)

};


#endif