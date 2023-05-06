#include <iostream>
using namespace std;

int main(){
	float angx;
	float angy;
	float angz;
	float x, y, z;
	float vx, vy, vz;
	float thrustx, thrusty, thrust;
	float vtarg = 4;
	float n = (10);

	cin >> x >> y >> z >> angx >> angy >> angz >> vx >> vy >> vz;

	thrustx = (angx)*(-1);
	thrusty = (angy)*(-1);
	thrust = (vz/vtarg); /// n;
	cout << thrustx << " " << thrusty << " " << thrust;
	return 0;
}	
