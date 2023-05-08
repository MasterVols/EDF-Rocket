#include "neural_network.h"
#include <iostream> 
#include <fstream>
#include <sstream>
#include <iomanip>

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

    // start neural network

    int id;

    Neural_Network *tobE;

    tobE = retrieve_from_text_file(id);

    double sx, sy, sz;
    double vx, vy, vz;
    double ax, ay, az;
    double theta_x, theta_y;
    double omega_x, omega_y;
    double alpha_x, alpha_y;
    double thrust, phi_x, phi_y;

    vector<double> inputs(17, 0);
    vector<double> outputs;

    while (std::cin >> sx >> sy >> sz >> vx >> vy >> vz >> ax >> ay >> az >> theta_x >> theta_y >> omega_x >> omega_y >> alpha_x >> alpha_y >> thrust >> phi_x >> phi_y) {

        inputs.at(0) = sx;
        inputs.at(1) = sy;
        inputs.at(2) = sz;
        inputs.at(3) = vx;
        inputs.at(4) = vy;
        inputs.at(5) = vz;
        inputs.at(6) = ax;
        inputs.at(7) = ay;
        inputs.at(8) = az;
        inputs.at(9) = theta_x;
        inputs.at(10) = theta_y;
        inputs.at(11) = omega_x;
        inputs.at(12) = omega_y;
        inputs.at(13) = alpha_x;
        inputs.at(14) = alpha_y;
        inputs.at(15) = thrust;
        inputs.at(16) = phi_x;
        inputs.at(17) = phi_y;
        
        outputs = tobE->compute(inputs);

        std::cout << std::fixed << std::setprecision(6) << outputs.at(1) << " " << outputs.at(2) << " " << outputs.at(0) << std::endl;
   
    }

    return 0;

}