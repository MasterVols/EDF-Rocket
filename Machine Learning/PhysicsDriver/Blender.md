#Blender Rocket Control Script
This Python script is designed to control a rigid body in Blender as it falls down. The script will call an external executable that will take in the location, rotation, and velocity of the rocket, and output the thruster settings needed to control the rocket's motion.

#Installation
To use this script, follow these steps:

Open Blender and create a new scene.
Import the rocket model that you want to control.
Save the Blender file in a location of your choice.
Copy the Python script into a text editor.
Replace the path/to/executable value in the script with the actual path to your executable.
Save the Python script with a .py extension in the same location as the Blender file.
Open the Blender file and select the rocket object.
Open the Text Editor panel in Blender and open the Python script file.
Press the "Run Script" button to run the script.
#Usage
Once the script is running, it will call the external executable once every 1/60th of a second (i.e. at 60Hz). The executable should take in the following values on standard input:

x, y, z: The current location of the rocket in Blender world coordinates.
rotation x, rotation y, rotation z: The current rotation of the rocket in Blender Euler angles.
velocity x, velocity y, velocity z: The current velocity of the rocket in Blender world coordinates.
The executable should output a single line of text with three values separated by spaces:

thruster x: The rotation angle of the thruster in the X direction, in degrees. Must be between -90 and 90.
thruster y: The rotation angle of the thruster in the Y direction, in degrees. Must be between -90 and 90.
thrust: The magnitude of the thrust to apply to the rocket, between 0 and 1.
The script will parse these values and apply them to the rocket's thrusters and rigid body physics.

The script will continue running until the rocket hits the ground (i.e. its z coordinate is less than or equal to 0).

#Customization
You can customize the following values in the script:

path/to/executable: The path to the external executable that will control the rocket.
thrust_min: The minimum thrust value that will be applied to the rocket. Defaults to 0.0.
thrust_max: The maximum thrust value that will be applied to the rocket. Defaults to 1.0.
You can also modify the rocket object in Blender to change its shape, size, or other properties.

#Troubleshooting
If you are having issues with the script, try the following steps:

Make sure that the rocket object in Blender is named "rocket".
Make sure that the external executable is located at the correct path and is executable.
Make sure that the external executable is outputting values in the correct format.
Make sure that the rocket object has rigid body physics enabled and is set to an active body type.
If you are still having issues, try printing out debug information in the script to see what values are being passed to and from the external executable.