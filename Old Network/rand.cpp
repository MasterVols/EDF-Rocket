#include <time.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int main() {

    srand(time(0));

    for(int i = 0; i < 100; i++) {

        double r = rand();
        double rand = r / RAND_MAX;
        cout << rand << endl;

    }

}