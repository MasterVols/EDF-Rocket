#include "neural_network.h"
#include "time.h"
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <fstream> 
#include <string> 
#include <sstream>

using namespace std;

// Constructor: initializes variables storing the sizes of the
// neural network then initializes the weights, biases, and
// activations vectors to the proper sizes storing values of 0
Neural_Network::Neural_Network(int input_layer_size, vector<int> hidden_layer_sizes, int output_layer_size) {

    num_hidden_layers = hidden_layer_sizes.size();
    num_layers = num_hidden_layers + 2;

    // fill layer_sizes vector

    layer_sizes.push_back(input_layer_size);
    
    for(long unsigned int i = 0; i < hidden_layer_sizes.size(); i++) {

        layer_sizes.push_back(hidden_layer_sizes.at(i));

    }

    layer_sizes.push_back(output_layer_size);

    // properly size activations vector

    activations.resize(num_layers);

    for(int i = 0; i < num_layers; i++) {

        activations.at(i).resize(layer_sizes.at(i));

    }

    // properly size weights vector

    weights.resize(num_layers - 1);

    for(int i = 1; i < num_layers; i++) {

        weights.at(i - 1).resize(layer_sizes.at(i));

        for(long unsigned int j = 0; j < weights.at(i-1).size(); j++) {

            weights.at(i - 1).at(j).resize(layer_sizes.at(i - 1));

        }

    }

    // properly size biases vector

    biases.resize(num_layers - 1);

    for(int i = 1; i < num_layers; i++) {

        biases.at(i - 1).resize(layer_sizes.at(i));

    }

};

Neural_Network::~Neural_Network() {};

// randomizes the weights of the neural network and sets biases
// equal to 0 
void Neural_Network::randomize() {

    // randomize rand() seed
    srand(time(NULL));

    double r;

    // randomize weights
    for(long unsigned int i = 0; i < weights.size(); i++) {

        for(long unsigned int j = 0; j < weights.at(i).size(); j++) {

            for(long unsigned int k = 0; k < weights.at(i).at(j).size(); k++) {

                r = rand();
                weights.at(i).at(j).at(k) = r / RAND_MAX;

            }

        }

    }

    // set biases equal to 1.0
    for(long unsigned int i = 0; i < biases.size(); i++) {

        for(long unsigned int j = 0; j < biases.at(i).size(); j++) {

           biases.at(i).at(j) = 1.0;

        }

    }

};

void Neural_Network::change_weight(int i, int j, int k, double w) {

    weights.at(i).at(j).at(k) = w;

};

void Neural_Network::change_bias(int i, int j, double b) {

    biases.at(i).at(j) = b;

};

void Neural_Network::update_weights(vector<vector<vector<double>>> dw) {

    for(long unsigned int i = 0; i < weights.size(); i++) {

        for(long unsigned int j = 0; j < weights.at(i).size(); j++) {

            for(long unsigned int k = 0; k < weights.at(i).at(j).size(); k++) {

                weights.at(i).at(j).at(k) -= dw.at(i).at(j).at(k);

            }

        }

    }

};

void Neural_Network::update_biases(vector<vector<double>> db) {

    for(long unsigned int i = 0; i < biases.size(); i++) {

        for(long unsigned int j = 0; j < biases.at(i).size(); j++) {

            biases.at(i).at(j) -= db.at(i).at(j);

        }

    }

}

// cost function returns a score based on improvement the rocket has made
// over a timestep towards the landing site
double Neural_Network::cost(double x, double x0) {

    double temp;

    if(x > x0 - 1) {

        temp = pow(x - x0 + 1, 4);

        return temp;

    } else {

        return 0;

    }

}; 

double Neural_Network::d_cost(double x, double x0) {

    double temp;

    if(x > x0 - 1) {

        temp = pow( 4 * (x - x0 + 1), 3);

        return temp;

    } else {

        return 0;

    }

};

// The following six functions take in a string that determines what to take
// the derivative with respect to (thrust, phi_x, or phi_y) and a char to 
// define the direction x, y, or z the variable is about

double Neural_Network::ds(string wrt, char direction) {

    double temp; 

    if(wrt == "thrust") {

        if(direction == 'x') {

            temp = -1 * pow(delta_t, 2) * cos(phi_y) * sin(phi_x) / (2 * m);

        } else if(direction == 'y') {

            temp = -1 * pow(delta_t, 2) * cos(phi_x) * sin(phi_y) / (2 * m);

        } else if(direction == 'z') {

            temp = pow(delta_t, 2) * cos(phi_x) * cos(phi_y) / (2 * m);

        } else {

            temp = -1;

        }

    }

    if(wrt == "phi_x") {

        if(direction == 'x') {

            temp = -1 * thrust * pow(delta_t, 2) * cos(phi_y) * cos(phi_x) / (2 * m);

        } else if(direction == 'y') {

            temp = thrust * pow(delta_t, 2) * sin(phi_y) * sin(phi_x) / (2 * m);

        } else if(direction == 'z') {

            temp = -1 * thrust * pow(delta_t, 2) * cos(phi_y) * sin(phi_x) / (2 * m);

        } else {

            temp = -1;

        }

    }

    if(wrt == "phi_y") {

        if(direction == 'x') {

            temp = thrust * pow(delta_t, 2) * sin(phi_x) * sin(phi_y) / (2 * m);

        } else if(direction == 'y') {

            temp = -1 * thrust * pow(delta_t, 2) * cos(phi_x) * cos(phi_y) / (2 * m);

        } else if(direction == 'z') {

            temp = -1 * thrust * pow(delta_t, 2) * cos(phi_x) * sin(phi_y) / (2 * m);

        } else {

            temp = -1;

        }

    }

    return temp;

};

double Neural_Network::dv(string wrt, char direction) {

    double temp; 

    if(wrt == "thrust") {

        if(direction == 'x') {

            temp = -1 * delta_t * cos(phi_y) * sin(phi_x) / m;

        } else if(direction == 'y') {

            temp = -1 * delta_t * cos(phi_x) * sin(phi_y) / m;

        } else if(direction == 'z') {

            temp = delta_t * cos(phi_x) * cos(phi_y) / m;

        } else {
        
            temp = -1;
        
        }

    }

    if(wrt == "phi_x") {

        if(direction == 'x') {

            temp = -1 * thrust * delta_t * cos(phi_y) * cos(phi_x) / m;

        } else if(direction == 'y') {

            temp = thrust * delta_t * sin(phi_y) * sin(phi_x) / m;

        } else if(direction == 'z') {

            temp = -1 * thrust * delta_t * cos(phi_y) * sin(phi_x) / m;

        } else {
        
            temp = -1;
        
        }

    }

    if(wrt == "phi_y") {

        if(direction == 'x') {

            temp = thrust * delta_t * sin(phi_x) * sin(phi_y) / m;

        } else if(direction == 'y') {

            temp = -1 * thrust * delta_t * cos(phi_x) * cos(phi_y) / m;

        } else if(direction == 'z') {

            temp = -1 * thrust * delta_t * cos(phi_x) * sin(phi_y) / m;

        } else {
        
            temp = -1;
        
        }

    }

    return temp;

};

double Neural_Network::da(string wrt, char direction) {

    double temp; 

    if(wrt == "thrust") {

        if(direction == 'x') {

            temp = -1 * cos(phi_y) * sin(phi_x) / m;

        } else if(direction == 'y') {

            temp = -1 * cos(phi_x) * sin(phi_y) / m;

        } else if(direction == 'z') {

            temp = cos(phi_x) * cos(phi_y) / m;

        } else {

            temp = -1;

        }

    }

    if(wrt == "phi_x") {

        if(direction == 'x') {

            temp = -1 * thrust * cos(phi_y) * cos(phi_x) / m;

        } else if(direction == 'y') {

            temp = thrust * sin(phi_y) * sin(phi_x) / m;

        } else if(direction == 'z') {

            temp = -1 * thrust * cos(phi_y) * sin(phi_x) / m;

        } else {

            temp = -1;

        }

    }

    if(wrt == "phi_y") {

        if(direction == 'x') {

            temp = thrust * sin(phi_x) * sin(phi_y) / m;

        } else if(direction == 'y') {

            temp = -1 * thrust * cos(phi_x) * cos(phi_y) / m;

        } else if(direction == 'z') {

            temp = -1 * thrust * cos(phi_x) * sin(phi_y) / m;

        } else {

            temp = -1;

        }

    }

    return temp;

};

double Neural_Network::d_theta(string wrt, char direction) {

    double temp = -1;

    if(wrt == "thrust") {

        if(direction == 'x') {

            temp = -1 * length * pow(delta_t, 2) * cos(phi_y) * sin(phi_x) / (4 * I);

        } else if(direction == 'y') {

            temp = -1 * length * pow(delta_t, 2) * cos(phi_x) * sin(phi_y) / (4 * I);

        } else {

            temp = -1;

        }

    }

    if(wrt == "phi_x") {

        if(direction == 'x') {

            temp = -1 * thrust * length * pow(delta_t, 2) * cos(phi_y) * cos(phi_x) / (4 * I);

        } else if(direction == 'y') {

            temp = thrust * length * pow(delta_t, 2) * sin(phi_y) * sin(phi_x) / (4 * I);

        } else {

            temp = -1;

        }

    }

    if(wrt == "phi_y") {

        if(direction == 'x') {

            temp = thrust * length * pow(delta_t, 2) * sin(phi_x) * sin(phi_y) / (4 * I);

        } else if(direction == 'y') {

            temp = -1 * thrust * length * pow(delta_t, 2) * cos(phi_x) * cos(phi_y) / (4 * I);

        } else {

            temp = -1;

        }

    }

    return temp;

};

double Neural_Network::d_omega(string wrt, char direction) {

    double temp = -1;

    if(wrt == "thrust") {

        if(direction == 'x') {

            temp = -1 * length * delta_t * cos(phi_y) * sin(phi_x) / (2 * I);

        } else if(direction == 'y') {

            temp = -1 * length * delta_t * cos(phi_x) * sin(phi_y) / (2 * I);

        } else {

            temp = -1;

        }

    }

    if(wrt == "phi_x") {

        if(direction == 'x') {

            temp = -1 * thrust * length * delta_t * cos(phi_y) * cos(phi_x) / (2 * I);

        } else if(direction == 'y') {

            temp = thrust * length * delta_t * sin(phi_y) * sin(phi_x) / (2 * I);

        } else {

            temp = -1;

        }

    }

    if(wrt == "phi_y") {

        if(direction == 'x') {

            temp = thrust * length * delta_t * sin(phi_x) * sin(phi_y) / (2 * I);

        } else if(direction == 'y') {

            temp = -1 * thrust * length * delta_t * cos(phi_x) * cos(phi_y) / (2 * I);

        } else {

            temp = -1;

        }

    }

    return temp;

};

double Neural_Network::d_alpha(string wrt, char direction) {

    double temp = -1;

    if(wrt == "thrust") {

        if(direction == 'x') {

            temp = -1 * length * cos(phi_y) * sin(phi_x) / (2 * I);

        } else if(direction == 'y') {

            temp = -1 * length * cos(phi_x) * sin(phi_y) / (2 * I);

        } else {

            temp = -1;

        }

    }

    if(wrt == "phi_x") {

        if(direction == 'x') {

            temp = -1 * thrust * length * cos(phi_y) * cos(phi_x) / (2 * I);

        } else if(direction == 'y') {

            temp = thrust * length * sin(phi_y) * sin(phi_x) / (2 * I);

        } else {

            temp = -1;

        }

    }

    if(wrt == "phi_y") {

        if(direction == 'x') {

            temp = thrust * length * sin(phi_x) * sin(phi_y) / (2 * I);

        } else if(direction == 'y') {

            temp = -1 * thrust * length * cos(phi_x) * cos(phi_y) / (2 * I);

        } else {

            temp = -1;

        }

    }

    return temp;

};


// ReLU is a training function that is equivalent to the larger value between
// 0 and your input.
double Neural_Network::ReLU(double z) {

    if(z > 0) {

        return z;

    } else {

        return 0;

    }

};

double Neural_Network::d_ReLU(double z) {

    if(z > 0) {

        return 1;

    } else {

        return 0;

    }

};

// This function performs backpropagation specifically for this rocket neural network scenario. 
// It does this be finding a dC/dw or dC/db for every weight or bias in the neural network
// using the chain rule. It also calculates dC/dz as a middle value. The program returns a 3d vector of
// weight changes and a 2d vector of bias changes which will be subtracted from the current weights and biases of the network.  
pair<vector<vector<vector<double>>>, vector<vector<double>>> Neural_Network::rocket_backpropagate(vector<double> inputs) {

    int num_changes = 15;

    // initial position
    sx1 = inputs.at(0);
    sy1 = inputs.at(1);
    sz1 = inputs.at(2);

    // final position
    sx2 = inputs.at(3);
    sy2 = inputs.at(4);
    sz2 = inputs.at(5); 

    // initial velocity
    vx1 = inputs.at(6);
    vy1 = inputs.at(7);
    vz1 = inputs.at(8);

    // final velocity
    vx2 = inputs.at(9);
    vy2 = inputs.at(10);
    vz2 = inputs.at(11);

    // initial acceleration
    ax1 = inputs.at(12);
    ay1 = inputs.at(13);
    az1 = inputs.at(14);

    // final acceleration
    ax2 = inputs.at(15);
    ay2 = inputs.at(16);
    az2 = inputs.at(17);

    // initial angle of rocket
    theta_x1 = inputs.at(18);
    theta_y1 = inputs.at(19);
    
    // final angle of rocket
    theta_x2 = inputs.at(20);
    theta_y2 = inputs.at(21);
    
    // initial angular velocity
    omega_x1 = inputs.at(22);
    omega_y1 = inputs.at(23);

    // final angular velocity
    omega_x2 = inputs.at(24);
    omega_y2 = inputs.at(25);

    // initial angular acceleration
    alpha_x1 = inputs.at(26);
    alpha_y1 = inputs.at(27);

    // final angular acceleration
    alpha_x2 = inputs.at(28);
    alpha_y2 = inputs.at(29);

    // thruster power
    thrust = inputs.at(30);
    
    // thruster angle
    phi_x = inputs.at(31);
    phi_y = inputs.at(32);

    // change in time
    //delta_t = inputs.at(33);
    delta_t = 1/60;

    // mass 
    //m = inputs.at(34);
    m = 1;

    // length of rocket
    //length = inputs.at(35);
    length = 1;

    // moment of intertia
    I = m * pow(length, 2) / 12;

    // initialize vector for storing dC/dw

    vector<vector<vector<double>>> d_weights; 

    d_weights.resize(num_layers - 1);

    for(int i = 1; i < num_layers; i++) {

        d_weights.at(i - 1).resize(layer_sizes.at(i));

        for(long unsigned int j = 0; j < d_weights.at(i-1).size(); j++) {

            d_weights.at(i - 1).at(j).resize(layer_sizes.at(i - 1));

        }

    }

    // initialize vector for storing dC/db
    
    vector<vector<double>> d_biases;

    d_biases.resize(num_layers - 1);

    for(int i = 1; i < num_layers; i++) {

        d_biases.at(i - 1).resize(layer_sizes.at(i));

    }

    // initialize vector for storing dC/dz

    vector<vector<double>> dz;

    dz.resize(num_layers - 1);

    for(int i = 1; i < num_layers; i++) {

        dz.at(i - 1).resize(layer_sizes.at(i));

    }

    // begin backpropagation

    double current_dz = 0;
    double current_dw = 0;
    double current_db = 0;

    for(int i = num_layers - 1; i > 0; i--) {

        for(int j = 0; j < layer_sizes.at(i); j++) {

            // find dz

            if(i == num_layers - 1) {

                string wrt;

                if(j == 0) {

                    wrt = "thrust";

                } else if(j == 1) {

                    wrt = "phi_x";

                } else if(j == 2) {

                    wrt = "phi_y";

                } else {

                    wrt = "";

                }

                for(int k = 0; k < num_changes; k++) {

                    // sx
                    if(k == 0) {

                        current_dz = d_cost(sx2, sx1) * ds(wrt, 'x') * d_ReLU(activations.at(i).at(j));
                        dz.at(i - 1).at(j) += current_dz;

                    }

                    // sy
                    if(k == 1) {

                        current_dz = d_cost(sy2, sy1) * ds(wrt, 'y') * d_ReLU(activations.at(i).at(j));
                        dz.at(i - 1).at(j) += current_dz;

                    }

                    // sz
                    if(k == 2) {

                        current_dz = d_cost(sz2, sz1) * ds(wrt, 'z') * d_ReLU(activations.at(i).at(j));
                        dz.at(i - 1).at(j) += current_dz;

                    }

                    // vx
                    if(k == 3) {

                        current_dz = d_cost(vx2, vx1) * dv(wrt, 'x') * d_ReLU(activations.at(i).at(j));
                        dz.at(i - 1).at(j) += current_dz;

                    }

                    // vy
                    if(k == 4) {

                        current_dz = d_cost(vy2, vy1) * dv(wrt, 'y') * d_ReLU(activations.at(i).at(j));
                        dz.at(i - 1).at(j) += current_dz;

                    }

                    // vz
                    if(k == 5) {

                        current_dz = d_cost(vz2, vz1) * dv(wrt, 'z') * d_ReLU(activations.at(i).at(j));
                        dz.at(i - 1).at(j) += current_dz;

                    }

                    // ax
                    if(k == 6) {

                        current_dz = d_cost(ax2, ax1) * da(wrt, 'x') * d_ReLU(activations.at(i).at(j));
                        dz.at(i - 1).at(j) += current_dz;

                    }

                    // ay
                    if(k == 7) {

                        current_dz = d_cost(ay2, ay1) * da(wrt, 'y') * d_ReLU(activations.at(i).at(j));
                        dz.at(i - 1).at(j) += current_dz;

                    }

                    // az
                    if(k == 8) {

                        current_dz = d_cost(az2, az1) * da(wrt, 'z') * d_ReLU(activations.at(i).at(j));
                        dz.at(i - 1).at(j) += current_dz;

                    }
                    
                    // theta_x
                    if(k == 9) {

                        current_dz = d_cost(theta_x2, theta_x1) * d_theta(wrt, 'x') * d_ReLU(activations.at(i).at(j));
                        dz.at(i - 1).at(j) += current_dz;

                    }

                    // theta_y
                    if(k == 10) {

                        current_dz = d_cost(theta_y2, theta_y1) * d_theta(wrt, 'y') * d_ReLU(activations.at(i).at(j));
                        dz.at(i - 1).at(j) += current_dz;

                    }

                    // omega_x
                    if(k == 11) {

                        current_dz = d_cost(omega_x2, omega_x1) * d_omega(wrt, 'x') * d_ReLU(activations.at(i).at(j));
                        dz.at(i - 1).at(j) += current_dz;

                    }

                    // omega_y
                    if(k == 12) {

                        current_dz = d_cost(omega_y2, omega_y1) * d_omega(wrt, 'y') * d_ReLU(activations.at(i).at(j));
                        dz.at(i - 1).at(j) += current_dz;

                    }

                    // alpha_x
                    if(k == 13) {

                        current_dz = d_cost(alpha_x2, alpha_x1) * d_alpha(wrt, 'x') * d_ReLU(activations.at(i).at(j));
                        dz.at(i - 1).at(j) += current_dz;

                    }

                    // alpha_y
                    if(k == 14) {

                        current_dz = d_cost(alpha_y2, alpha_y1) * d_alpha(wrt, 'x') * d_ReLU(activations.at(i).at(j));
                        dz.at(i - 1).at(j) += current_dz;

                    }

                }

            } else {

                for(int k = 0; k < layer_sizes.at(i + 1); k++) {

                    current_dz = dz.at(i).at(k) * weights.at(i).at(k).at(j) * d_ReLU(activations.at(i).at(j));
                    dz.at(i - 1).at(j) += current_dz;

                }

            }

            // dw

            for(int k = 0; k < layer_sizes.at(i - 1); k++) {

                current_dw = dz.at(i - 1).at(j) * activations.at(i - 1).at(k);
                d_weights.at(i - 1).at(j).at(k) = current_dw;

            }

            // db

            current_db = dz.at(i - 1).at(j);
            d_biases.at(i - 1).at(j) = current_db;

        }

    }
    
    pair<vector<vector<vector<double>>>, vector<vector<double>>> solution = make_pair(d_weights, d_biases);

    return solution;

};

void Neural_Network::print() {

    // print basic network info

    cout << endl << endl << endl;

    cout << "Printing out Neural Network" << endl << endl;

    cout << "Number of Layers: " << num_layers << endl << endl;

    for(int i = 0; i < num_layers; i++) {

        if(i == 0) {

            cout << "Input Layer Size: " << layer_sizes.at(0) << endl;

        } else if(i == num_layers - 1) {

            cout << "Output Layer Size: " << layer_sizes.at(num_layers - 1) << endl;

        } else {

            cout << "Hidden Layer (" << i << ") Size: " << layer_sizes.at(i) << endl;

        }

    }

    // print weights

    cout << endl << "Weights" << endl << endl;

    for(long unsigned int i = 0; i < weights.size(); i++) {

        for(long unsigned int j = 0; j < weights.at(i).size(); j++) {

            for(long unsigned int k = 0; k < weights.at(i).at(j).size(); k++) {

                cout << "(" << i << ")(" << j << ")(" << k << "): " << weights.at(i).at(j).at(k) << endl;

            }

        }

    }

    // print biases

    cout << endl << "Biases" << endl << endl;

    for(long unsigned int i = 0; i < biases.size(); i++) {

        for(long unsigned int j = 0; j < biases.at(i).size(); j++) {

            cout << "(" << i << ")(" << j << "): " << biases.at(i).at(j) << endl;

        }

    }

    // print activations

    cout << endl << "Activations" << endl << endl;

    for(long unsigned int i = 0; i < activations.size(); i++) {

        for(long unsigned int j = 0; j < activations.at(i).size(); j++) {

            cout << "(" << i << ")(" << j << "): " << activations.at(i).at(j) << endl;

        }

    }

    cout << endl << endl;

};

// This function prints the size of the network, its weights, and its biases to a text file
// so that the neural network can be retrieved later on. 
void Neural_Network::print_to_text_file(int id) {

    string file_name = "tobE_" + to_string(id) + ".txt";

    ofstream out(file_name);

    if(!out.is_open()) {
        cerr << "Error opening file" << endl;
        return;
    }

    out << "tobE" << id << endl;
    out << "size: ";

    for(int i = 0; i < layer_sizes.size(); i++) {

        out << layer_sizes.at(i) << " ";

    }

    out << endl;

    out << "weights:" << endl;

    for(long unsigned int i = 0; i < weights.size(); i++) {

        for(long unsigned int j = 0; j < weights.at(i).size(); j++) {

            for(long unsigned int k = 0; k < weights.at(i).at(j).size(); k++) {

                out << i << " " << j << " " << k << " " << weights.at(i).at(j).at(k) << endl;

            }

        }

    }

    out << "biases:" << endl;

    for(long unsigned int i = 0; i < biases.size(); i++) {

        for(long unsigned int j = 0; j < biases.at(i).size(); j++) {

            out << i << " " << j << " " << biases.at(i).at(j) << endl;

        }

    }

    out.close();

}

// This function sends a vector of inputs to the input layer of the neural network.
// Then it calculates the activations for every node in the network until it can determine the
// activations of the output layer which it returns. 
vector<double> Neural_Network::compute(vector<double> inputs) {

    double weighted_sum;

    for(int i = 0; i < num_layers; i++) {

        // input layer
        if(i == 0) {

            for(int j = 0; j < layer_sizes.at(i); j++) {

                activations.at(i).at(j) = ReLU(inputs.at(j));

            }

        // hidden layers and output layer
        } else {

            for(int j = 0; j < layer_sizes.at(i); j++) {

                weighted_sum = 0; 

                for(int k = 0; k < layer_sizes.at(i - 1); k++) {

                    weighted_sum += activations.at(i - 1).at(k) * weights.at(i - 1).at(j).at(k);

                }

                activations.at(i).at(j) = ReLU(weighted_sum - biases.at(i - 1).at(j));

            }

        }

    }

    return activations.at(num_layers - 1);

};