#include <iostream>
using namespace std;

int main(){
	float angx;
	float angy;
	float angz;
	float x, y, z;
	float v;
	float thrustx, thrusty, thrust;
	float vtarg = 4;
	float n = (10);

	cin >> x >> y >> z >> angx >> angy >> angz >> v;

	thrustx = (angx)*(-1);
	thrusty = (angy)*(-1);
	thrust = (v/vtarg); /// n;
	cout << thrustx << " " << thrusty << " " << thrust;
}	
