#include "neural_network.h"
#include "time.h"
#include <stdlib.h>
#include <iostream>
#include <cmath>

using namespace std;

Neural_Network::Neural_Network(int input_layer_size, vector<int> hidden_layer_sizes, int output_layer_size) {

    cout << "Starting Constructor" << endl;

    num_hidden_layers = hidden_layer_sizes.size();
    num_layers = num_hidden_layers + 2;

    // fill layer_sizes vector

    layer_sizes.push_back(input_layer_size);
    
    for(long unsigned int i = 0; i < hidden_layer_sizes.size(); i++) {

        layer_sizes.push_back(hidden_layer_sizes.at(i));

    }

    cout << "Filled Layer Sizes" << endl;

    layer_sizes.push_back(output_layer_size);

    // properly size activations vector

    activations.resize(num_layers);

    for(int i = 0; i < num_layers; i++) {

        activations.at(i).resize(layer_sizes.at(i));

    }

    cout << "Filled Activations" << endl;

    // properly size weights vector

    weights.resize(num_layers - 1);

    for(int i = 1; i < num_layers; i++) {

        weights.at(i - 1).resize(layer_sizes.at(i));

        for(long unsigned int j = 0; j < weights.at(i-1).size(); j++) {

            weights.at(i - 1).at(j).resize(layer_sizes.at(i - 1));

        }

    }

    cout << "Filled Weights" << endl;

    // properly size biases vector

    biases.resize(num_layers - 1);

    for(int i = 1; i < num_layers; i++) {

        biases.at(i - 1).resize(layer_sizes.at(i));

    }

    cout << "Filled Biases" << endl;

    cout << "Ending Constructor" << endl;

};

Neural_Network::~Neural_Network() {};

void Neural_Network::randomize() {

    cout << "Randomizing" << endl;

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

    // randomize biases
    for(long unsigned int i = 0; i < biases.size(); i++) {

        for(long unsigned int j = 0; j < biases.at(i).size(); j++) {

            /*
            r = rand();
            biases.at(i).at(j) = r / RAND_MAX;
            */

           biases.at(i).at(j) = 1.0;

        }

    }

};

void Neural_Network::train() {};

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

double Neural_Network::ds_dT(char direction, double delta_t, double m, double phi_x, double phi_y) {

    double temp = -1; 

    if(direction == 'x') {

        double temp = -1 * pow(delta_t, 2) * cos(phi_y) * sin(phi_x) / (2 * m);

    } else if(direction == 'y') {

        double temp = -1 * pow(delta_t, 2) * cos(phi_x) * sin(phi_y) / (2 * m);

    } else if(direction == 'z') {

        double temp = pow(delta_t, 2) * cos(phi_x) * cos(phi_y) / (2 * m);

    }

    return temp;

};

double Neural_Network::dv_dT(char direction, double delta_t, double m, double phi_x, double phi_y) {

    double temp = -1; 

    if(direction == 'x') {

        double temp = -1 * delta_t * cos(phi_y) * sin(phi_x) / m;

    } else if(direction == 'y') {

        double temp = -1 * delta_t * cos(phi_x) * sin(phi_y) / m;

    } else if(direction == 'z') {

        double temp = delta_t * cos(phi_x) * cos(phi_y) / m;

    }

    return temp;

};

double Neural_Network::da_dT(char direction, double m, double phi_x, double phi_y) {

    double temp = -1; 

    if(direction == 'x') {

        double temp = -1 * cos(phi_y) * sin(phi_x) / m;

    } else if(direction == 'y') {

        double temp = -1 * cos(phi_x) * sin(phi_y) / m;

    } else if(direction == 'z') {

        double temp = cos(phi_x) * cos(phi_y) / m;

    }

    return temp;

}

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

void Neural_Network::rocket_backpropagate(vector<double> inputs) {

    int num_changes = 13;

    // initial position
    double sx1 = inputs.at(0);
    double sy1 = inputs.at(1);
    double sz1 = inputs.at(2);

    // final position
    double sx2 = inputs.at(3);
    double sy2 = inputs.at(4);
    double sz2 = inputs.at(5); 

    // initial velocity
    double vx1 = inputs.at(6);
    double vy1 = inputs.at(7);
    double vz1 = inputs.at(8);

    // final velocity
    double vx2 = inputs.at(9);
    double vy2 = inputs.at(10);
    double vz2 = inputs.at(11);

    // initial acceleration
    double ax1 = inputs.at(12);
    double ay1 = inputs.at(13);
    double az1 = inputs.at(14);

    // final acceleration
    double ax2 = inputs.at(15);
    double ay2 = inputs.at(16);
    double az2 = inputs.at(17);

    // initial angle of rocket
    double theta_x1 = inputs.at(18);
    double theta_y1 = inputs.at(19);
    
    // final angle of rocket
    double theta_x2 = inputs.at(20);
    double theta_y2 = inputs.at(21);
    
    // angular velocity
    double wx = inputs.at(11);
    double wy = inputs.at(12);

    // thruster power
    double thrust = inputs.at(13);
    
    // thruster angle
    double phi_x = inputs.at(14);
    double phi_y = inputs.at(15);

    // change in time
    double delta_t = inputs.at(16);

    // mass 
    double m = inputs.at(24);

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

            if(i == 0) {

                for(int k = 0; k < num_changes; k++) {

                    // sx
                    if(k == 0) {
                    
                        current_dz = d_cost(sx2, sx1) * ds_dT('x', delta_t, m, phi_x, phi_y);
                        dz.at(i).at(j) += current_dz;

                    }

                    // sy
                    if(k == 1) {

                        current_dz = d_cost(sy2, sy1) * ds_dT('y', delta_t, m, phi_x, phi_y);
                        dz.at(i).at(j) += current_dz;

                    }

                    // sz
                    if(k == 2) {

                        current_dz = d_cost(sz2, sz1) * ds_dT('z', delta_t, m, phi_x, phi_y);
                        dz.at(i).at(j) += current_dz;

                    }

                    // vx
                    if(k == 3) {

                        current_dz = d_cost(vx2, vx1) * dv_dT('x', delta_t, m, phi_x, phi_y);
                        dz.at(i).at(j) += current_dz;

                    }

                    // vy
                    if(k == 4) {

                        current_dz = d_cost(vy2, vy1) * dv_dT('y', delta_t, m, phi_x, phi_y);
                        dz.at(i).at(j) += current_dz;

                    }

                    // vz
                    if(k == 5) {

                        current_dz = d_cost(vz2, vz1) * dv_dT('z', delta_t, m, phi_x, phi_y);
                        dz.at(i).at(j) += current_dz;

                    }

                    // ax
                    if(k == 6) {

                        current_dz = d_cost(ax2, ax1) * da_dT('x', m, phi_x, phi_y);
                        dz.at(i).at(j) += current_dz;

                    }

                    // ay
                    if(k == 7) {

                        current_dz = d_cost(ay2, ay1) * da_dT('y', m, phi_x, phi_y);
                        dz.at(i).at(j) += current_dz;

                    }

                    // az
                    if(k == 8) {

                        current_dz = d_cost(az2, az1) * da_dT('z', m, phi_x, phi_y);
                        dz.at(i).at(j) += current_dz;

                    }
                    

                    // 


                }

            } else {

                for(int k = 0; k < layer_sizes.at(i + 1); k++) {



                }

            }

        }

    }

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

vector<double> Neural_Network::compute(vector<double> inputs) {

    cout << "Computing" << endl;

    double weighted_sum;

    for(int i = 0; i < num_layers; i++) {

        // input layer
        if(i == 0) {

            for(int j = 0; j < layer_sizes.at(i); j++) {

                cout << "Relu: " << ReLU(inputs.at(j)) << endl;

                activations.at(i).at(j) = ReLU(inputs.at(j));

                cout << "Activate: " << activations.at(i).at(j);

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

    cout << "Done Computing" << endl;

};