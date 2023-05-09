#ifndef NEURAL_NETWORK
#define NEURAL_NETWORK

#include <vector> 
#include <string>

class Neural_Network {

    public:

    Neural_Network(int, std::vector<int>, int);
    ~Neural_Network();

    void randomize();                                   // randomizes weights and sets biases to 1
    void change_weight(int, int, int, double);          // changes specific weight
    void change_bias(int, int, double);                 // changes specific bias
    void update_weights(std::vector<std::vector<std::vector<double>>>);     // modifies all weights based on negative gradient of cost function
    void update_biases(std::vector<std::vector<double>>);                   // modifies all weights based on negative gradient of cost function
    std::pair<std::vector<std::vector<std::vector<double>>>, std::vector<std::vector<double>>> rocket_backpropagate(std::vector<double>);   // performs backpropagation for this specific rocket neural network
    double ReLU(double);    // ReLU function 
    double d_ReLU(double);  // derivative of ReLU function 
    void print();
    void print_to_text_file(int);   // prints a neural network into a text file
    std::vector<double> compute(std::vector<double>);   // sends inputs to the neural network and calculates output

    double cost(double, double);            // cost function
    double d_cost(double, double);          // derivative of cost function

    // derivatives with respect to thrust, phi_x, or phi_y
    double ds(std::string, char);           
    double dv(std::string, char);           
    double da(std::string, char);
    double d_theta(std::string, char);
    double d_omega(std::string, char);
    double d_alpha(std::string, char);

    private: 

    std::vector<int> layer_sizes;
    std::vector<std::vector<std::vector<double>>> weights;
    std::vector<std::vector<double>> biases;
    std::vector<std::vector<double>> activations;

    int num_layers;
    int num_hidden_layers;

    // state variables

    double thrust;                                      // thruster force
    double phi_x;                                       // x-angle of thruster
    double phi_y;                                       // y-angle of thruster
    double sx1, sx2, sy1, sy2, sz1, sz2;                // position
    double vx1, vx2, vy1, vy2, vz1, vz2;                // velocity
    double ax1, ax2, ay1, ay2, az1, az2;                // acceleration
    double theta_x1, theta_x2, theta_y1, theta_y2;      // angle of rocket
    double omega_x1, omega_x2, omega_y1, omega_y2;      // angular velocity
    double alpha_x1, alpha_x2, alpha_y1, alpha_y2;      // angular acceleration
    double length;                                      // length of rocket
    double m;                                           // mass    
    double I;                                           // moment of inertia
    double delta_t;                                     // time interval

};

#endif