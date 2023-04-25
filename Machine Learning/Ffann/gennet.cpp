// gennet.cpp
// Contributor: Phillip Graham
// Start Time: April, 25, 2023
// Last Edited: April, 08, 2023
// Logged Time: 0:05

#include <iostream>
#include <fstream>
#include <random>

using namespace std;

int main()
{
    int num_in, num_out, num_hidden, num_per_hidden;
    float thresh_min, thresh_max, weight_min, weight_max;
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

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> tdist(thresh_min, thresh_max);
    uniform_real_distribution<> wdist(weight_min,weight_max);

    std::ofstream outputFile("network.txt");
    if (outputFile.is_open()) {
        outputFile << num_in << " " << num_out << " " << num_hidden << " " << num_per_hidden;
        for (int i = 0; i < num_in; i++)
        {
            outputFile << " " << tdist(gen);
            for (int j = 0; j < num_per_hidden; j++) outputFile << " " << wdist(gen);
        }
        for (int i = 0; i < num_hidden - 1; i++)
        {
            outputFile << " " << tdist(gen);
            for (int j = 0; j < num_per_hidden; j++) outputFile << " " << wdist(gen);
        }
        outputFile << " " << tdist(gen);
        for (int i = 0; i < num_out; i++) outputFile << " " << wdist(gen);
        for (int i = 0; i < num_out; i++) outputFile << " " << tdist(gen);
        outputFile.close();
        cout << "Random numbers generated and written to network.txt" << std::endl;
    }
    else {
        std::cout << "Unable to open output file" << std::endl;
        return 1;
    }

    return 0;
}
