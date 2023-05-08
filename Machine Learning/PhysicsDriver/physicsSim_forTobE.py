import subprocess
import random
import math
import time
import os

#
#   Use python 3.8.10
#   python --version to check
#

# MATTHEW's
#Executable = "C:\\Users\\Matth\\OneDrive\\Documents\\GitHub\\EDF-Rocket\\Machine Learning\\PhysicsDriver\\test_driver.exe"
#report_folder = "C:\\Users\\Matth\\OneDrive\\Documents\\GitHub\\EDF-Rocket\\Machine Learning\\PhysicsDriver\\reports"
# PHILLIP's
#Executable = "C:\\Users\\reed2\\OneDrive\\Desktop\\Github Repos\\EDF-Rocket\\Machine Learning\\Ffann\\main.exe"
#report_folder = "C:\\Users\\reed2\\OneDrive\\Desktop\\Github Repos\\EDF-Rocket\Machine Learning\\Ffann\\ffann-reports"
# SAGE's
#Executable = "C:\\Users\\sgray\\OneDrive\\Documents\\GitHub\\EDF-Rocket\\Machine Learning\\PhysicsDriver\\test_driver.exe"
#report_folder = "C:\\Users\\sgray\\OneDrive\\Documents\\GitHub\\EDF-Rocket\\Machine_Learning\\PhysicsDriver\\sage_reports"
#C:\Users\sgray\OneDrive\Documents\GitHub\EDF-Rocket\Machine Learning\SG_brain
# Ethan's
Executable = "C:\\Users\\16159\\OneDrive\\Documents\\GitHub\\EDF-Rocket\\Machine Learning\\tobE\\run.exe"
report_folder = "C:\\Users\\16159\\OneDrive\\Documents\\GitHub\\EDF-Rocket\\Machine Learning\\tobE\\PhysicsDriver\\ethan_reports"

#TWEAKING VALUES:
randomRotationOnStart = False

#Fitness Tweaking:
landFrameMultiplier = 1             #Each frame survived is + 1 * multiplier

landRotMaxAngle = 5                 #Max rotation to call a successful landing
landVeloMaxVelo = 5                 #Max velocity to call a successful landing
landUnderMaxConsMultiplier = 100    #for a successful landing under max velo and rotation

# Constants
G = 9.81
DT = 1/60
HEIGHT = 100
ROCKET_HEIGHT = 1
CENTER_OF_MASS = 0.5
MASS = 1
MoI = MASS * ROCKET_HEIGHT * ROCKET_HEIGHT / 12




def generate_report_filename():
    os.makedirs(report_folder, exist_ok=True)

    idx = 0
    while True:
        filename = f"Reports{idx:03d}.txt"
        path = os.path.join(report_folder, filename)
        if not os.path.exists(path):
            return path
        idx += 1

def update_physics(position, velocity, acceleration, theta, omega, alpha, thrust, thrust_rotation):

    # acceleration 
    acceleration2 = [0.0,  0.0,  0.0]
    acceleration2[0] = -1 * thrust * math.cos(thrust_rotation[1]) * math.cos(thrust_rotation[0]) / MASS
    acceleration2[1] = -1 * thrust * math.cos(thrust_rotation[0]) * math.cos(thrust_rotation[1]) / MASS
    acceleration2[2] = thrust * math.cos(thrust_rotation[0]) * math.cos(thrust_rotation[1]) / MASS

    # velocity 
    velocity2 = [0.0,  0.0,  0.0]
    velocity2[0] = velocity[0] + acceleration[0] * DT
    velocity2[1] = velocity[1] + acceleration[1] * DT
    velocity2[2] = velocity[2] + acceleration[2] * DT

    # position
    position2 = [0.0,  0.0,  0.0]
    position2[0] = position[0] + velocity[0] * DT * 0.5 * acceleration[0] * DT * DT
    position2[1] = position[1] + velocity[1] * DT * 0.5 * acceleration[1] * DT * DT
    position2[2] = position[2] + velocity[2] * DT * 0.5 * acceleration[2] * DT * DT

    # angular acceleration 
    alpha2 = [0.0,  0.0, 0.0]
    alpha2[0] = -0.5 * thrust * ROCKET_HEIGHT * math.cos(thrust_rotation[1]) * math.sin(thrust_rotation[0]) / MoI
    alpha2[0] = -0.5 * thrust * ROCKET_HEIGHT * math.cos(thrust_rotation[0]) * math.sin(thrust_rotation[1]) / MoI

    # angular velocity
    omega2 = [0.0,  0.0, 0.0]
    omega2[0] = omega[0] + alpha[0] * DT
    omega2[1] = omega[1] + alpha[1] * DT

    # angular position
    theta2 = [0.0, 0.0, 0.0]
    theta2[0] = theta[0] + omega[0] * DT + 0.5 * alpha[0] * DT * DT
    theta2[1] = theta[1] + omega[1] * DT + 0.5 * alpha[1] * DT * DT

    return position2, velocity2, acceleration2, theta2, omega2, alpha2

def main():
    position = [0, 0, HEIGHT]
    velocity = [0, 0, 0]
    acceleration = [0, 0, -G]
    rotation = [random.uniform(0, 2*math.pi) for _ in range(3)]
    omega = [0, 0, 0]
    alpha = [0, 0, 0]
    thrust_value = 0

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
        while position[2] > 0 and position[2] < 300:
            # Send the current state to the C++ neural network program
            input_data = ' '.join(map(str, position + velocity + acceleration + rotation + omega + alpha + [thrust_value] + list(thrust_rotation)))
            output_data = subprocess.check_output([Executable], input=input_data, text=True).strip()

            # Parse the output
            thrust_rotation_1, thrust_rotation_2, thrust_value = map(float, output_data.split())
            thrust_rotation = (thrust_rotation_1, thrust_rotation_2)

            # Update the physics
            position, velocity, acceleration, rotation, omega, alpha = update_physics(position, velocity, acceleration, rotation, omega, alpha, thrust_value, thrust_rotation)

            fitness += 1 * landFrameMultiplier

            # Write the current state to the report file
            report_line = f"Position: {position}, Rotation: {rotation}, Velocity: {velocity}, Thrust Rotation: {thrust_rotation}, Thrust Magnitude: {thrust_value}\n"
            report_file.write(report_line)

            #time.sleep(DT)

        #Send final fitness:
        if rotation[0] < landRotMaxAngle and rotation[0] > -landRotMaxAngle and rotation[1] < landRotMaxAngle and rotation[1] > -landRotMaxAngle:
            fitness_line = f"fitness: {fitness + 1 * landUnderMaxConsMultiplier}\n"
        else:
            fitness_line = f"fitness: {fitness}\n"
        report_file.write(fitness_line)


if __name__ == "__main__":
    main()
