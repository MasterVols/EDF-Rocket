#ifndef Brain_Nueron
#define Brain_Nueron

// Matthew Bringle
// Brain And Nueron Driver Code
// 2/19/2023

#include <string>
#include <vector>

struct Nueron {

    int ID = -1;                        //ID for each nueron
    std::vector<Nueron*> connections;   //Stores the pointers for the next nuerons in the connection
    
    double triggerLevel = 0.25;             //How much stimulation does Nueron need before firing?
    double outputLevel = 0.1;               //How much stimulation does the Nueron Produce?
    double hardness = 0.2;                  //Refers to the likelyhood of this nueron having it's values changed
    double totaledInputs = 0;
    int amountOfConnections = 3;

};

class Brain {

    public:

        int setColumns(int columnNum);                          //returns false if already set
        int addNueron(Nueron *nueronToAdd, int column);         //returns false if duplicate
        int removeNueron(Nueron *nueronToRemove);               //removes nueron based on refrence. False if Nueron doesn't exist
        int removeNueronByID(int ID);                           //removes nueron from ID. False if Nueron doesn't exist
        
        Brain();
        Brain(int columnNum, double mutationFactor, int inputNum, int outputNum);
        
    //private:
    

        int columns = -1;                       //columns are given by user where rows are naturally generated from math and inputValues
        int inputs = -1;
        int outputs = -1;

        std::vector<std::vector<Nueron*>> nueronContainer;   //contains all nuerons in brain
        std::vector<double> inputValues;           //holds all input values (1st column of nuerons)
        std::vector<double> outputValues;          //holds all output values (N-th column of nuerons)

};


#endif