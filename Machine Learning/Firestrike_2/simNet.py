import sys
import subprocess
import random
import math
import time
import os
import io
import shutil
import numpy as np

NUM_GENERATIONS = 600  # Adjust this value to control the number of generations

# MATTHEW's
#report_folder = "C:\\Users\\Matth\\OneDrive\\Documents\\GitHub\\EDF-Rocket\\Machine Learning\\Firestrike_better\\nets\\GEN1"
#file_path = "C:\\Users\\Matth\\OneDrive\\Documents\\GitHub\\EDF-Rocket\\Machine Learning\\Firestrike_better\\nets\\GEN1\\net000.txt"

#TWEAKING VALUES:
randomRotationOnStart = False

#Fitness Tweaking:
landFrameMultiplier = 5             #Each frame survived is + 1 * multiplier

landRotMaxAngle = 10                 #Max rotation to call a successful landing
landVeloMaxVelo = 15                 #Max velocity to call a successful landing
landUnderMaxConsMultiplier = 1000000    #for a successful landing under max velo and rotation

# Constants
G = 9.81
DT = 1/60
HEIGHT = 250
ROCKET_HEIGHT = 1
CENTER_OF_MASS = 0.5

def find_highest_generation(base_folder):
    highest_gen = -1
    for folder_name in os.listdir(base_folder):
        if folder_name.startswith("GEN"):
            try:
                gen_num = int(folder_name[3:])
                if gen_num > highest_gen:
                    highest_gen = gen_num
            except ValueError:
                pass
    return highest_gen


def create_mutated_nets(best_net_path, next_gen_folder, num_mutations=999):
    mutation_scale = 0.001

    # Read the best net weights
    best_net_weights = np.loadtxt(best_net_path)

    # Create mutated neural nets
    for i in range(1, num_mutations+1):
        mutated_net_weights = best_net_weights + np.random.normal(0, mutation_scale, best_net_weights.shape)
        mutated_net_path = os.path.join(next_gen_folder, f"net{i:03d}.txt")
        np.savetxt(mutated_net_path, mutated_net_weights, fmt='%.8f')


def select_best_nets(generation_number):
    best_fitness = -1
    best_net_number = -1

    # Start the range from 1 instead of 0
    for net_number in range(1, 1000):
        report_filename = f"Reports{net_number:03d}.txt"
        report_path = os.path.join(report_folder, report_filename)
        with open(report_path, 'r') as report_file:
            lines = report_file.readlines()
            fitness = float(lines[-1].split(':')[1].strip())

            if fitness > best_fitness:
                best_fitness = fitness
                best_net_number = net_number

    # Copy the best net file to the next generation folder
    parent_folder = os.path.dirname(report_folder)  # Add this line to get the parent directory
    next_gen_folder = os.path.join(parent_folder, f"GEN{generation_number+1:02d}")  # Update this line to use the parent_folder
    os.makedirs(next_gen_folder, exist_ok=True)

    best_net_filename = f"net{best_net_number:03d}.txt"
    best_net_path = os.path.join(report_folder, best_net_filename)
    next_gen_net_path = os.path.join(next_gen_folder, "net000.txt")

    print(f"fitness: {best_fitness}")

    shutil.copy2(best_net_path, next_gen_net_path)

    return best_net_path, next_gen_folder

def calculate_results(file_data, position, rotation, velocity):
    input_data = position + rotation + velocity
    results = [0, 0, 0]
    for i in range(9):
        for j in range(3):
            results[j] += file_data[i][j] * input_data[i]
    return results

def read_file_data(file_path):
    data = []
    with open(file_path, 'r') as file:
        for line in file.readlines():
            data.append([float(x) for x in line.strip().split()])
    return data

def generate_report_filename(report_folder):
    os.makedirs(report_folder, exist_ok=True)

    idx = 1  # Start the range from 1 instead of 0
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

def main(net_number, report_folder):
    file_path = os.path.join(report_folder, f"net{net_number:03d}.txt")
    file_data = read_file_data(file_path)

    position = [0, 0, HEIGHT]
    rotation = [random.uniform(0, 2*math.pi) for _ in range(3)]
    velocity = [0, 0, -20]
    fitness = 0

    report_filename = generate_report_filename(report_folder)
    #print(f"Writing report to {report_filename}")

    if randomRotationOnStart:
        rotation[0] = random.uniform(0, 2*math.pi)
        rotation[1] = random.uniform(0, 2*math.pi)
    else:
        rotation[0] = 0
        rotation[1] = 0

    thrust_rotation = (0, 0)


    with open(report_filename, "w") as report_file:
        while position[2] > 0 and position[2] < 300 and abs(position[0]) < 100 and abs(position[1]) < 100:
        
            # Call calculate_results function directly
            output_data = calculate_results(file_data, position, rotation, velocity)
        
            thrust_rotation_1, thrust_rotation_2, thrust_value = output_data
            if abs(thrust_value) > 2:
                thrust_value = 2
            if thrust_value < 0:
                thrust_value = 0

            thrust_rotation = (thrust_rotation_1, thrust_rotation_2)

            position, rotation, velocity = update_physics(position, rotation, velocity, thrust_value, thrust_rotation)

            fitness += 1 * landFrameMultiplier

            report_line = f"Position: {position}, Rotation: {rotation}, Velocity: {velocity}, Thrust Rotation: {thrust_rotation}, Thrust Magnitude: {thrust_value}\n"
            #uncomment when wanting to see results in blender:
            #report_file.write(report_line)

        if rotation[0] < landRotMaxAngle and rotation[0] > -landRotMaxAngle and rotation[1] < landRotMaxAngle and rotation[1] > -landRotMaxAngle and abs(velocity[0]) < landVeloMaxVelo and abs(velocity[1]) < landVeloMaxVelo and abs(velocity[2]) < landVeloMaxVelo and abs(position[0]) < 100 and abs(position[1]) < 100:
            fitness_line = f"fitness: {fitness + 1 * landUnderMaxConsMultiplier}\n"
        else:
            fitness_line = f"fitness: {fitness}\n"
        report_file.write(fitness_line)

if __name__ == "__main__":
    base_folder = "C:\\Users\\Matth\\OneDrive\\Documents\\GitHub\\EDF-Rocket\\Machine Learning\\Firestrike_better\\nets"
    start_generation = find_highest_generation(base_folder)

    if start_generation == -1:
        start_generation = 0
        print("No existing generations found. Starting from generation 1.")
    else:
        print(f"Starting from generation {start_generation+1}.")

    for generation_number in range(start_generation, NUM_GENERATIONS):
        print(f"\nRunning generation {generation_number+1} of {NUM_GENERATIONS}")

        report_folder = f"{base_folder}\\GEN{generation_number:02d}"

        os.makedirs(report_folder, exist_ok=True)

        # Start the range from 1 instead of 0
        for net_number in range(1, 1000):
            #print(f"Running  {net_number:03d}")
            main(net_number, report_folder)

        best_net_path, next_gen_folder = select_best_nets(generation_number)
        print(f"Selected the best net: {best_net_path}")

        create_mutated_nets(best_net_path, next_gen_folder)
        print(f"Created mutated neural nets in {next_gen_folder}")

        # Update the report_folder for the next generation
        report_folder = next_gen_folder
