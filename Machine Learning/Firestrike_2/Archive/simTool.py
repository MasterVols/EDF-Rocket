import subprocess
import random
import math
import time
import os
import sys

# MATTHEW's
neural_network_script = "C:\\Users\\Matth\\OneDrive\\Documents\\GitHub\\EDF-Rocket\\Machine Learning\\Firestrike_better\\netRunner.py"
neural_network_name_format = "C:\\Users\\Matth\\OneDrive\\Documents\\GitHub\\EDF-Rocket\\nets\\GEN1\\net_{}.txt" 
report_folder = "C:\\Users\\Matth\\OneDrive\\Documents\\GitHub\\EDF-Rocket\\nets\\GEN1" 

#TWEAKING VALUES:
randomRotationOnStart = False

#Fitness Tweaking:
landFrameMultiplier = 10             #Each frame survived is + 1 * multiplier

landRotMaxAngle = 15                 #Max rotation to call a successful landing
landVeloMaxVelo = 15                 #Max velocity to call a successful landing
landUnderMaxConsMultiplier = 10000    #for a successful landing under max velo and rotation

# Constants
G = 9.81
DT = 1/60
HEIGHT = 100
ROCKET_HEIGHT = 1
CENTER_OF_MASS = 0.5


def generate_report_filename():
    os.makedirs(report_folder, exist_ok=True)

    idx = 0
    while True:
        filename = f"Reports{idx:03d}.txt"
        path = os.path.join(report_folder, filename)
        if not os.path.exists(path):
            return path
        idx += 1

def update_physics(position, rotation, velocity, thrust, thrust_rotation):
    # Update position
    position[0] += velocity[0] * DT
    position[1] += velocity[1] * DT
    position[2] += (velocity[2] - G * DT) * DT

    # Update rotation
    rotation[0] += thrust_rotation[0] * DT
    rotation[1] += thrust_rotation[1] * DT

    # Update velocity
    thrust_force = thrust * G
    velocity[0] += thrust_force * math.sin(thrust_rotation[1]) * math.cos(thrust_rotation[0]) * DT
    velocity[1] += thrust_force * math.sin(thrust_rotation[1]) * math.sin(thrust_rotation[0]) * DT
    velocity[2] += thrust_force * math.cos(thrust_rotation[1]) * DT - G * DT

    return position, rotation, velocity

def main():
    for net_id in range(1000):
        neural_network_name = neural_network_name_format.format(net_id)

        position = [0, 0, HEIGHT]
        rotation = [random.uniform(0, 2*math.pi) for _ in range(3)]
        velocity = [0, 0, -20]
        fitness = 0

        report_filename = generate_report_filename()
        print(f"Writing report to {report_filename}")

        # Initialize rotation with random values or no rotation based on randomRotationOnStart
        if randomRotationOnStart:
            #thrust_rotation = (random.uniform(0, 2*math.pi), random.uniform(0, 2*math.pi))
            rotation[0] = random.uniform(0, 2*math.pi)
            rotation[1] = random.uniform(0, 2*math.pi)
        else:
            rotation[0] = 0
            rotation[1] = 0
            #thrust_rotation = (0, 0)

        # simply define thrust_rotation
        thrust_rotation = (0, 0)

        with open(report_filename, "w") as report_file:
            while position[2] > 0 and position[2] < 300 and abs(position[0]) < 100 and abs(position[1]) < 100:
                # Send the current state to the neural network simulation script
                input_data = ' '.join(map(str, position + rotation + velocity + list(thrust_rotation)))


                # Pass the correct arguments to the netRunner.py script
                output_data = subprocess.check_output([sys.executable, neural_network_script, neural_network_name] + input_data.split(), text=True).strip()


                # Parse the output
                noise = 0
                thrust_rotation_1, thrust_rotation_2, thrust_value, noise = map(float, output_data.split())
                thrust_rotation = (thrust_rotation_1, thrust_rotation_2)

                # Update the physics
                position, rotation, velocity = update_physics(position, rotation, velocity, thrust_value, thrust_rotation)

                fitness += 1 * landFrameMultiplier

                # Write the current state to the report file
                report_line = f"Position: {position}, Rotation: {rotation}, Velocity: {velocity}, Thrust Rotation: {thrust_rotation}, Thrust Magnitude: {thrust_value}\n"
                report_file.write(report_line)

                #time.sleep(DT)

            #Send final fitness:
            if rotation[0] < abs(landRotMaxAngle) and rotation[1] < abs(landRotMaxAngle) and velocity[2] < abs(landVeloMaxVelo):
                fitness_line = f"fitness: {fitness + 1 * landUnderMaxConsMultiplier}\n"
            else:
                fitness_line = f"fitness: {fitness}\n"
            report_file.write(fitness_line)


if __name__ == "__main__":
    main()
