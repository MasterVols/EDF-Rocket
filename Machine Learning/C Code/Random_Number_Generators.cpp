// Matthew Bringle 
// 2/20/2023

#include <cstdlib>
#include <ctime>

double getRandomDouble(double max) {
    // Seed the random number generator with the current time
    srand(static_cast<unsigned int>(time(nullptr)));

    // Generate a random number between 0 and 1, and scale it by max
    double random = static_cast<double>(rand()) / RAND_MAX;
    return random * max;
}


double getRandomDoubleInRange(double range) {
    // Seed the random number generator with the current time
    srand(static_cast<unsigned int>(time(nullptr)));

    // Generate a random number between 0 and 1, and scale it to the range [-1, 1]
    double random = static_cast<double>(rand()) / RAND_MAX;
    random = 2 * random - 1;

    // Scale the range to [-range, range], and return the result
    return random * range;
}


int getRandomInt(int max) {
    // Seed the random number generator with the current time
    srand(static_cast<unsigned int>(time(nullptr)));

    // Generate a random number between 0 and max - 1, and return it
    return rand() % max;
}

int getRandomIntInRange(int min, int max) {
    // Seed the random number generator with the current time
    srand(static_cast<unsigned int>(time(nullptr)));

    // Generate a random number between min and max, and return the result
    return rand() % (max - min + 1) + min;
}