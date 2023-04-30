// gennet.cpp
// Contributor: Phillip Graham
// Start Time: April, 25, 2023
// Last Edited: April, 08, 2023
// Logged Time: 0:05

#include <iostream>
#include <fstream>
#include <ctime>
#include <math.h>
#include <stdio.h>
#include <bits/stdc++.h>
using namespace std;

float ranf(float,float);

int main()
{
    srand(time(0));
    int num_in, num_out, num_hidden, num_per_hidden;
    float thresh_min, thresh_max, weight_min, weight_max;
    /*
    cout << "Enter the number of inputs: ";
    cin >> num_in;
    cout << "Enter the number of outputs: ";
    cin >> num_out;
    cout << "Enter the number of hidden layers: ";
    cin >> num_hidden;
    cout << "Enter the number of nodes per hidden layer: ";
    cin >> num_per_hidden;
    cout << "Enter the minimum value for the threshold: ";
    cin >> thresh_min;
    cout << "Enter the maximum value for the threshold: ";
    cin >> thresh_max;
    cout << "Enter the minimum value for the weight: ";
    cin >> weight_min;
    cout << "Enter the maximum value for the weight: ";
    cin >> weight_max;
    */
    num_in = 9;
    num_out = 3;
    num_hidden = 3;
    num_per_hidden = 9;
    thresh_min = -2;
    thresh_max = 0.2;
    weight_min = -.9;
    weight_max = .8;
    std::ofstream outputFile("network.txt");
    if (outputFile.is_open()) {
        outputFile << num_in << " " << num_out << " " << num_hidden << " " << num_per_hidden;
        for (int i = 0; i < num_in; i++)
        {
            outputFile << " " << ranf(thresh_min,thresh_max);
            for (int j = 0; j < num_per_hidden; j++) outputFile << " " << ranf(weight_min,weight_max);
        }
        for (int i = 0; i < (num_hidden - 1) * num_per_hidden; i++)
        {
            outputFile << " " << ranf(thresh_min,thresh_max);;
            for (int j = 0; j < num_per_hidden; j++) outputFile << " " << ranf(weight_min,weight_max);
        }
        for (int i = 0; i < num_per_hidden; i++)
        {
            outputFile << " " << ranf(thresh_min,thresh_max);
            for (int j = 0;j<num_out;j++) outputFile << " " << ranf(weight_min,weight_max);
        }
        for (int i = 0; i < num_out; i++)
        {
            outputFile << " " << ranf(thresh_min,thresh_max);
        }
        outputFile.close();
        cout << "Random numbers generated and written to network.txt" << std::endl;
    }
    else {
        std::cout << "Unable to open output file" << std::endl;
        return 1;
    }

    return 0;
}

float ranf(float min,float max)
{
    float i = (float)(rand()) / (float)(RAND_MAX);
    return min + (fmod(i,max-min));
}
