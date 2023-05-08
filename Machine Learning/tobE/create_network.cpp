#include "neural_network.h"
#include <fstream>
#include <sstream>

using namespace std;

Neural_Network* retrieve_from_text_file(int id) {

    int input;
    vector<int> hidden;
    int output;
    int temp;

    string file_name = "tobE_" + to_string(id) + ".txt";

    ifstream in(file_name);

    string line;
    getline(in, line);
    line.clear();
    getline(in, line);

    istringstream ss(line.substr(6));
    int num; 

    while(ss >> num) {

        hidden.push_back(num);

    }

    input = hidden.front();
    hidden.erase(hidden.begin());
    output = hidden.back();
    hidden.pop_back();

    Neural_Network *tobE = new Neural_Network(input, hidden, output);

    // retrieve weights

    getline(in,line);
    line.clear();

    while(getline(in, line)) {

        if (line == "biases:") break;

        istringstream ss(line);
        int i, j, k;
        double weight;

        ss >> i >> j >> k >> weight;

        tobE->change_weight(i, j, k, weight);

    }

    // retrieve biases

    while(getline(in, line)) {

        istringstream ss(line);
        int i, j;
        double bias;

        ss >> i >> j >> bias;

        tobE->change_bias(i, j, bias);

    }

    return tobE;

}

int main() {

    int input = 17;
    int output = 3;
    vector<int> hidden = {16, 12, 8, 6};

    Neural_Network *tobE = new Neural_Network(input, hidden, output);

    tobE->randomize();

    tobE->print_to_text_file(001);

    //Neural_Network *tobE2;

    //tobE2 = retrieve_from_text_file(001);

    //tobE2->print_to_text_file(002);

    return 0;

}