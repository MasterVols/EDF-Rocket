import subprocess
import random
import math
import time
import os

# MATTHEW's
Executable = "C:\\Users\\Matth\\OneDrive\\Documents\\GitHub\\EDF-Rocket\\Machine Learning\\PhysicsDriver\\test_driver.exe"
report_folder = "C:\\Users\\Matth\\OneDrive\\Documents\\GitHub\\EDF-Rocket\\Machine Learning\\PhysicsDriver\\reports"
# SAGE's
# Executable = "C:\\Users\\Matth\\OneDrive\\Documents\\GitHub\\EDF-Rocket\\Machine Learning\\PhysicsDriver\\test_driver.exe"
# report_folder = "C:\\Users\\Matth\\OneDrive\\Documents\\GitHub\\EDF-Rocket\\Machine Learning\\PhysicsDriver\\reports"
# SAGE's
# Executable = "C:\\Users\\Matth\\OneDrive\\Documents\\GitHub\\EDF-Rocket\\Machine Learning\\PhysicsDriver\\test_driver.exe"
# report_folder = "C:\\Users\\Matth\\OneDrive\\Documents\\GitHub\\EDF-Rocket\\Machine Learning\\PhysicsDriver\\reports"
# SAGE's
# Executable = "C:\\Users\\Matth\\OneDrive\\Documents\\GitHub\\EDF-Rocket\\Machine Learning\\PhysicsDriver\\test_driver.exe"
# report_folder = "C:\\Users\\Matth\\OneDrive\\Documents\\GitHub\\EDF-Rocket\\Machine Learning\\PhysicsDriver\\reports"




def generate_report_filename():
    os.makedirs(report_folder, exist_ok=True)

    idx = 0
    while True:
        filename = f"Reports{idx:03d}.txt"
        path = os.path.join(report_folder, filename)
        if not os.path.exists(path):
            return path
        idx += 1

# Constants
G = 9.81
DT = 0.01
HEIGHT = 100
ROCKET_HEIGHT = 1
CENTER_OF_MASS = 0.5

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
    position = [0, 0, HEIGHT]
    rotation = [random.uniform(0, 2*math.pi) for _ in range(3)]
    velocity = [0, 0, 0]

    report_filename = generate_report_filename()
    print(f"Writing report to {report_filename}")

    # Initialize thrust_rotation with random values
    thrust_rotation = (random.uniform(0, 2*math.pi), random.uniform(0, 2*math.pi))

    with open(report_filename, "w") as report_file:
        while position[2] > 0:
            # Send the current state to the C++ neural network program
            input_data = ' '.join(map(str, position + rotation + velocity + list(thrust_rotation)))
            output_data = subprocess.check_output([Executable], input=input_data, text=True).strip()

            # Parse the output
            thrust_rotation_1, thrust_rotation_2, thrust_value = map(float, output_data.split())
            thrust_rotation = (thrust_rotation_1, thrust_rotation_2)

            # Update the physics
            position, rotation, velocity = update_physics(position, rotation, velocity, thrust_value, thrust_rotation)

            # Write the current state to the report file
            report_line = f"Position: {position}, Rotation: {rotation}, Velocity: {velocity}\n"
            report_file.write(report_line)

            time.sleep(DT)


if __name__ == "__main__":
    main()
