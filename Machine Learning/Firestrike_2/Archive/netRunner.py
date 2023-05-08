import sys
import subprocess
import numpy as np

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

def main():
    # Get the file name from the command line
    file_name = sys.argv[1]
    input_values = list(map(float, sys.argv[2:]))  # Include all elements except the first one
    
    # Split the input_values into two parts, the first 4 elements, and the rest
    input_values_nn = input_values[:4]
    remaining_values = input_values[4:]

    # Parse neuron data from the text file
    neurons = parse_neuron_data(file_name)

    # Propagate input values through the neural network
    output_values = propagate(input_values_nn, neurons)

    # Combine the output_values with the remaining_values
    final_values = output_values + remaining_values

    # Print the final_values
    print(" ".join(map(str, final_values[:4])))

if __name__ == "__main__":
    main()