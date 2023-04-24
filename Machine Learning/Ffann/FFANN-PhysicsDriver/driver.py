


import bpy
import subprocess
import time
import random

# Set up the rocket object
rocket = bpy.data.objects['rocket']
rocket.rigid_body.enabled = True
rocket.rigid_body.type = 'ACTIVE'

# Set up the executable command
executable = "test_driver"
thrust_min = 0.0
thrust_max = 1.0

# randomize location and rotation (height is 100)
rocket.location = (random.uniform(-10, 10), random.uniform(-10, 10), 100)
rocket.rotation_euler = (random.uniform(0, 2 * 3.14), random.uniform(0, 2 * 3.14), random.uniform(0, 2 * 3.14))

# Reset the rigid body world and set the frame to zero
bpy.ops.ptcache.free_bake_all()
bpy.context.scene.frame_set(0)

# Initialize the previous location variable
previous_location = None

# Main loop
while rocket.location.z > 0:
    # Get the current state of the rocket
    loc = rocket.location
    rot = rocket.rotation_euler

    # Calculate the velocity based on the difference in position between two frames
    if previous_location is None:
        vel = (0, 0, 0)
    else:
        vel = tuple((loc[i] - previous_location[i]) / (1/60) for i in range(3))
    previous_location = loc

    # Call the executable to get the thruster settings
    proc = subprocess.Popen(
        [executable],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        universal_newlines=True
    )
    proc.stdin.write(f"{loc.x} {loc.y} {loc.z} {rot.x} {rot.y} {rot.z} {vel[0]} {vel[1]} {vel[2]}\n")
    proc.stdin.flush()

    # Read stdout and stderr messages from the subprocess and print them to the console
    while True:
        output = proc.stdout.readline()
        if output == '' and proc.poll() is not None:
            break
        if output:
            print(output.strip())
        error = proc.stderr.readline()
        if error:
            print(error.strip())

    proc.wait()

    # Parse the response into thruster settings
    thruster_x, thruster_y, thrust = map(float, response.split())

    # Clamp the thrust between the minimum and maximum values
    thrust = max(thrust_min, min(thrust_max, thrust))

    # Set the rocket's thruster settings
    rocket.rotation_euler.x = thruster_x
    rocket.rotation_euler.y = thruster_y
    #rocket.rigid_body.apply_force(0, 0, thrust)

    # Wait for 1/60th of a second
    #time.sleep(1/60)
    
    # Advance the animation by one frame
    bpy.context.scene.frame_set(bpy.context.scene.frame_current + 1)

# End of program
print("Rocket has landed!")