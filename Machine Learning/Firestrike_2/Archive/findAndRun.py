import os
import sys
import random
import math
import numpy as np

# CONSTANTS
# MATTHEW's
neural_network_name_format = "C:\\Users\\Matth\\OneDrive\\Documents\\GitHub\\EDF-Rocket\\nets\\GEN1\\net_{}.txt" 
report_folder = "C:\\Users\\Matth\\OneDrive\\Documents\\GitHub\\EDF-Rocket\\nets\\GEN1" 

#TWEAKING VALUES:
randomRotationOnStart = False

#Fitness Tweaking:
landFrameMultiplier = 10             #Each frame survived is + 1 * multiplier

landRotMaxAngle = 15                 #Max rotation to call a successful landing
landVeloMaxVelo = 15                 #Max velocity to call a successful landing
landUnderMaxConsMultiplier = 100000    #for a successful landing under max velo and rotation

# Constants
G = 9.81
DT = 1/60
HEIGHT = 100
ROCKET_HEIGHT = 1
CENTER_OF_MASS = 0.5

# FUNCTIONS
def parse_neuron_data(file_name):
    neurons = []
    with open(file_name, 'r') as file:
        lines = file.readlines()
        i = 0
        while i < len(lines):
            line = lines[i].strip()
            if line.startswith('Neuron'):
                neuron = {}
                i += 1
                line = lines[i].strip()
                if line.startswith('Threshold'):
                    neuron['threshold'] = float(line.split(': ')[1])
                    i += 1
                line = lines[i].strip()
                if line.startswith('Weights'):
                    neuron['weights'] = list(map(float, line.split(': ')[1].split(', ')))
                    i += 1
                neurons.append(neuron)
            else:
                i += 1
    return neurons

def sigmoid(x):
    return 1 / (1 + np.exp(-x))

def propagate(input_values, neurons):
    output_values = []
    for neuron in neurons:
        if 'weights' in neuron:
            net_input = np.dot(input_values, neuron['weights']) - neuron['threshold']
            activation = sigmoid(net_input)
            output_values.append(activation)
    return output_values[:4]

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

        if randomRotationOnStart:
            rotation[0] = random.uniform(0, 2*math.pi)
            rotation[1] = random.uniform(0, 2*math.pi)
        else:
            rotation[0] = 0
            rotation[1] = 0

        thrust_rotation = (0, 0)

        with open(report_filename, "w") as report_file:
            while position[2] > 0 and position[2] < 300 and abs(position[0]) < 100 and abs(position[1]) < 100:
                input_data = ' '.join(map(str, position + rotation + velocity + list(thrust_rotation)))

                neurons = parse_neuron_data(neural_network_name)
                output_data = propagate(list(map(float, input_data.split()[:4])), neurons)


                noise = 0
                thrust_rotation_1, thrust_rotation_2, thrust_value, noise = output_data
                thrust_rotation = (thrust_rotation_1, thrust_rotation_2)

                position, rotation, velocity = update_physics(position, rotation, velocity, thrust_value, thrust_rotation)

                fitness += 1 * landFrameMultiplier

                report_line = f"Position: {position}, Rotation: {rotation}, Velocity: {velocity}, Thrust Rotation: {thrust_rotation}, Thrust Magnitude: {thrust_value}\n"
                report_file.write(report_line)

            if rotation[0] < abs(landRotMaxAngle) and rotation[1] < abs(landRotMaxAngle) and velocity[2] < abs(landVeloMaxVelo):
                fitness_line = f"fitness: {fitness + 1 * landUnderMaxConsMultiplier}\n"
            else:
                fitness_line = f"fitness: {fitness}\n"
            report_file.write(fitness_line)

if __name__ == "__main__":
    main()
