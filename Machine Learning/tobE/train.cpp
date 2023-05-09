#include "neural_network.h"
#include <iostream> 
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

// This program does the same thing as main.cpp but stores the inputs from the previous
// time step. With information from two states, it calls the neural_network to perform
// backpropagation to adjust the weights and biases slightly based on how well it is
// performing. It calls backpropagation and then changes the weights and biases after
// every time step. 

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

    // start neural network

    int id = 001;

    Neural_Network *tobE;

    tobE = retrieve_from_text_file(id);

    double sx, sy, sz;
    double vx, vy, vz;
    double ax, ay, az;
    double theta_x, theta_y;
    double omega_x, omega_y;
    double alpha_x, alpha_y;
    double thrust, phi_x, phi_y;

    vector<double> inputs;
    vector<double> old_inputs;
    vector<double> outputs;
    vector<double> back_inputs;

    while (std::cin >> sx >> sy >> sz >> vx >> vy >> vz >> ax >> ay >> az >> theta_x >> theta_y >> omega_x >> omega_y >> alpha_x >> alpha_y >> thrust >> phi_x >> phi_y) {

        inputs = {sx, sy, sz, vx, vy, vz, ax, ay, az, theta_x, theta_y, omega_x, omega_y, alpha_x, alpha_y, thrust, phi_x, phi_y};

        back_inputs = {inputs.at(0), inputs.at(1), inputs.at(2), sx, sy, sz, inputs.at(3), inputs.at(4), inputs.at(5), vx, vy, vz, inputs.at(6), inputs.at(7), inputs.at(8), ax, ay, az, inputs.at(9), inputs.at(10), theta_x, theta_y, inputs.at(11), inputs.at(12), omega_x, omega_y, inputs.at(13), inputs.at(14), alpha_x, alpha_y, inputs.at(15), inputs.at(16), inputs.at(17)};

        outputs = tobE->compute(inputs);

        pair<vector<vector<vector<double>>>, vector<vector<double>>> dw_db = tobE->rocket_backpropagate(back_inputs);

        tobE->update_weights(dw_db.first);
        tobE->update_biases(dw_db.second);

        tobE->print_to_text_file(2);

        std::cout << std::fixed << std::setprecision(6) << outputs.at(1) << " " << outputs.at(2) << " " << outputs.at(0) << std::endl;

        old_inputs = inputs;
   
    }

    return 0;

}