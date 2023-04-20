/* Time Spent:
 *	3/15: 2.5 Hours, researching Neural Networks
 *	3/27: 1 hour, learning matrix rotations
 *	3/28: 2 hours, creating matrix function
 *	3/29: 2 hours, editing matrix function, writing the cin function
 * https://mathworld.wolfram.com/EulerAngles.html
 * Right now I'm getting the euler values into a matrix, I will need to multiply it by a matrix to get the rocket where I want it to be, and then use that to determine where the thruster needs to be positioned so I can thrust at some value.
 * General Rotation A = BCD
 *	Where: D =	cos phi		sin phi		0
 *				-sin phi	cos phi		0
 *				0			0			1
 *		   (z?)Yaw
 *
 *		   C =	cos theta	0			-sin theta
 *				0			1			0
 *				sin theta	0			cos theta
 *		   (x?)Pitch
 *
 *		   B =	1			0			0
 *				0			cos psi		sin psi
 *				0			-sin psi	cos psi
 *		   (y?)Roll
 */

#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;
int PI = 3.141592;
/* eul_to_mat3
 * Purpose: convert given euler rotations into a matrix, using the pitch, roll, yaw convention
 * Parameters:
 *	mat: the matrix being loaded up with values
 *	eul: the given euler values
 * Pre-condition: eul must be given in i, j, h (pitch, roll, yaw) notation
 * Post-condition: matrix contains sin/cos decimals of euler notation, ready to be multiplied
 * Returns: Nothing
 */

void eul_to_mat( vector<float> (&mat)(9), vector<float> eul[3] ) {
		double cosi, cosj, cosh, sini, sinj, sinh, coscos, cossin, sincos, sinsin;

		cosi = cos( eul[0] )*( 180/PI );
		cosj = cos( eul[1] )*( 180/PI );
		cosh = cos( eul[2] )*( 180/PI );
		sini = sin( eul[0] )*( 180/PI );
		sinj = sin( eul[1] )*( 180/PI );
		sinh = sin( eul[2] )*( 180/PI );
		coscos = cosi * cosh;
		cossin = cosi * sinh;
		sincos = sini * cosh;
		sinsin = sini * sinh;

		mat[0][0] = ( float )( cosj * cosh );
		mat[1][0] = ( float )( sinj * sincos - cossin );
		mat[2][0] = ( float )( sinj * coscos + sinsin);
		mat[0][1] = ( float )( cosj * sinh );
		mat[1][1] = ( float )( sinj * sinsin + coscos );
		mat[2][1] = ( float )( sinj * cossin - sincos );
		mat[0][2] = ( float )( -sinj );
		mat[1][2] = ( float )( cosj * sini );
		mat[2][2] = ( float )( cosj * cosi );

}

int main(){
	vector<float> eul(3);
	vector<float> rotation(9);
	fill ( rotation.begin(), rotation.end(), 0 );
	float euler = 0;
	while (cin >> euler){
		eul.push_back(euler);
	}
	eul_to_mat( rotation, eul );
	cout << "Rotation Matrix: ";
	for ( int i = 0; i < 3; i++ ){
		for ( int j = 0; j < 3; j++ ){
			cout << "| " << rotation[i][j] << " " ;
			if ( j == 3 ) {cout << endl;}
		}
	}
	return 0;
}
