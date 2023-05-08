import os
import random

# Create the 'nets' folder if it doesn't exist
if not os.path.exists('nets'):
    os.makedirs('nets')

# Create the 'GEN1' folder inside the 'nets' folder if it doesn't exist
if not os.path.exists('nets/GEN1'):
    os.makedirs('nets/GEN1')

def create_neural_net(net_id):
    # Create a 4x9 neural network with weights and threshold for each neuron
    neural_net = []
    for row in range(4):
        neural_net_row = []
        for col in range(9):
            neuron = {
                'id': row * 9 + col,
                'weights': [random.uniform(-2, 2) for _ in range(4)] if col != 8 else None,
                'threshold': random.uniform(-2, 2)
            }
            neural_net_row.append(neuron)
        neural_net.append(neural_net_row)

    # Save the neural network to a file in the 'nets/GEN1' folder
    with open(f'nets/GEN1/net_{net_id}.txt', 'w') as file:
        for row in neural_net:
            for neuron in row:
                file.write(f"Neuron {neuron['id']}:\n")
                file.write(f"  Threshold: {neuron['threshold']}\n")
                if neuron['weights'] is not None:
                    file.write(f"  Weights: {', '.join(map(str, neuron['weights']))}\n")
                file.write('\n')

# Generate 1000 neural networks
for i in range(1000):
    create_neural_net(i)