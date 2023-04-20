# Unless you are familiar with python, physics simulators, and blender... Don't alter this script


import bpy
import subprocess
import time

# Set up the rocket object
rocket = bpy.data.objects['rocket']
rocket.rigid_body.enabled = True
rocket.rigid_body.type = 'ACTIVE'

# Set up the executable command
executable = "path/to/executable"
thrust_min = 0.0
thrust_max = 1.0

# Main loop
while rocket.location.z > 0:
    # Get the current state of the rocket
    loc = rocket.location
    rot = rocket.rotation_euler
    vel = rocket.rigid_body.velocity

    # Call the executable to get the thruster settings
    proc = subprocess.Popen(
        [executable],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        universal_newlines=True
    )
    proc.stdin.write(f"{loc.x} {loc.y} {loc.z} {rot.x} {rot.y} {rot.z} {vel.x} {vel.y} {vel.z}\n")
    proc.stdin.flush()
    response = proc.stdout.readline().strip()
    proc.stdin.close()
    proc.wait()

    # Parse the response into thruster settings
    thruster_x, thruster_y, thrust = map(float, response.split())

    # Clamp the thrust between the minimum and maximum values
    thrust = max(thrust_min, min(thrust_max, thrust))

    # Set the rocket's thruster settings
    rocket.rotation_euler.x = thruster_x
    rocket.rotation_euler.y = thruster_y
    rocket.rigid_body.active_object.apply_force((0, 0, thrust), False)

    # Wait for 1/60th of a second
    time.sleep(1/60)

# End of program
print("Rocket has landed!")