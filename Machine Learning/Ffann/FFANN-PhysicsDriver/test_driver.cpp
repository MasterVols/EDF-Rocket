/*
Matthew Bringle
g++ -o test_driver test_driver.cpp
executable = "path/to/test_driver"
*/


#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>

double random_double(double min, double max) {
    double random = static_cast<double>(std::rand()) / RAND_MAX;
    return min + random * (max - min);
}

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    double loc_x, loc_y, loc_z;
    double rot_x, rot_y, rot_z;
    double vel_x, vel_y, vel_z;

    while (std::cin >> loc_x >> loc_y >> loc_z >> rot_x >> rot_y >> rot_z >> vel_x >> vel_y >> vel_z) {
        double thruster_x = random_double(0, 1);
        double thruster_y = random_double(0, 1);
        double thrust = random_double(0, 2);
        std::cout << std::fixed << std::setprecision(6) << thruster_x << " " << thruster_y << " " << thrust << std::endl;
    }

    return 0;
}