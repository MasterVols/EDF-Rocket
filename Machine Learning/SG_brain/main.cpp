/* Time Spent:
 *	3/15: 2.5 Hours, researching Neural Networks
 *	3/27: 1 hour, learning matrix rotations
 *	3/28: 2 hours, creating matrix function
 *	3/29: 2 hours, editing matrix function, writing the cin function
 *	4/16: 1 hour finishing Matrix function
 *	4/18: 2 hours calculating final requirement though matrices
 *	4/24: 1 hour determining Pitch and Yaw change equations
 *	4/25: 1.5 hours learning how to implement rotation in code
 * https://mathworld.wolfram.com/EulerAngles.html
 *  https://stackoverflow.com/questions/1996957/conversion-euler-to-matrix-and-matrix-to-euler
 *  https://www.gatevidyalay.com/3d-rotation-in-computer-graphics-definition-examples/
 *  https://www.youtube.com/watch?v=zjMulxRvygQ
 * Right now I'm getting the euler values into a matrix, I will need to multiply it by a matrix to get the rocket where I want it to be, and then use that to determine where the thruster needs to be positioned so I can thrust at some value.
 * Mayhaps use a map to hold the values every input so they can be referenced easily by the neural networks`
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
float PI = 3.141592;
/* eul_to_mat3
 * Purpose: convert given euler rotations into a matrix, using the pitch, roll, yaw convention
 * Parameters:
 *	mat: the matrix being loaded up with values
 *	eul: the given euler values
 * Pre-condition: eul must be given in i, j, h (pitch, roll, yaw) notation
 * Post-condition: matrix contains sin/cos decimals of euler notation, ready to be multiplied
 * Returns: Nothing
 */
// looking for 0, 0, 0
void eul_to_mat( float (&mat)[3][3], float eul[3] ) {
		float cosP, cosR, cosY, sinP, sinR, sinY, coscos, cossin, sincos, sinsin;

		cosP = cosf( eul[0] );//*( 180/PI ); //Pitch
		sinP = sinf( eul[0] );//*( 180/PI ); //Pitch
		cosR = cosf( eul[1] );//*( 180/PI ); //Roll
		sinR = sinf( eul[1] );//*( 180/PI ); //Roll
		cosY = cosf( eul[2] );//*( 180/PI ); //Yaw
		sinY = sinf( eul[2] );//*( 180/PI ); //Yaw
		coscos = cosP * cosY;
		cossin = cosP * sinY;
		sincos = sinP * cosY;
		sinsin = sinP * sinY;

		mat[0][0] = ( coscos );
		mat[1][0] = ( cossin );
		mat[2][0] = (-sinP );
		mat[0][1] = ( (sinR*sincos) - (cosR*sinY) );
		mat[1][1] = ( (sinR*sinsin) + (cosR*cosY) );
		mat[2][1] = ( sinR*cosP );
		mat[0][2] = ( (cosR*sincos) + (sinR*sinY));
		mat[1][2] = ( (cosR*sinsin) - (sinR*cosY) );
		mat[2][2] = ( cosR*cosP );

}

int main(){
	float eul[3];
	float rotation[3][3];
	float euler = 0;
	float i, j, k;
	cin >> i >> j >> k;
	eul[0] = i*PI/180;
	eul[1] = j*PI/180;
	eul[2] = k*PI/180;
	eul_to_mat( rotation, eul );
	cout << "Rotation Matrix: " << endl;
	for ( int i = 0; i < 3; i++ ){
		for ( int j = 0; j < 3; j++ ){
			cout << "| " << rotation[i][j] << " " ;
			if ( j == 2 ) {
				cout << endl;
			}
		}
	}
	return 0;
}
