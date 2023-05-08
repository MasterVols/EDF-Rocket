import os
import numpy as np

# Define the folder containing the reports
folder_path = 'C:\\Users\\Matth\\OneDrive\\Documents\\GitHub\\EDF-Rocket\\reports'

# Find the largest GENX folder
gen_folders = [f for f in os.listdir(folder_path) if f.startswith('GEN')]
if len(gen_folders) == 0:
    gen_folder_path = folder_path
else:
    gen_folder_names = [f.split('GEN')[-1] for f in gen_folders]
    gen_folder_indices = [int(n) for n in gen_folder_names if n.isdigit()]
    if len(gen_folder_indices) == 0:
        gen_folder_path = folder_path
    else:
        largest_gen_index = max(gen_folder_indices)
        largest_gen_folder_name = f'GEN{largest_gen_index:03d}'
        largest_gen_folder_path = os.path.join(folder_path, largest_gen_folder_name)
        gen_folder_path = largest_gen_folder_path

# Loop through the reports
best_fitness = -1
best_report = ''
for i in range(1000):
    # Define the report file path
    report_file = os.path.join(gen_folder_path, f'Reports{i:03d}.txt')
    # Check if the report file exists
    if not os.path.isfile(report_file):
        continue
    # Get the fitness value from the report file
    with open(report_file, 'r') as f:
        lines = f.readlines()
    if len(lines) == 0:
        continue
    fitness = float(lines[-1].split()[-1])
    # Check if this is the best fitness so far
    if fitness > best_fitness:
        # Update the best fitness and report
        best_fitness = fitness
        best_report = report_file

# Create the new GENX+1 directory
new_gen_index = largest_gen_index + 1
new_gen_folder_name = f'GEN{new_gen_index:03d}'
new_gen_folder_path = os.path.join(folder_path, new_gen_folder_name)
os.mkdir(new_gen_folder_path)

# Define the mutation parameters
mutation_rate = 0.1
mutation_range = 0.2

# Find the corresponding net file and mutate it
best_net = os.path.join(gen_folder_path, f'net_{best_report.split("_")[-1]}')
with open(best_net, 'r') as f:
    lines = f.readlines()
    for i in range(len(lines)):
        # Check if this line defines a threshold or weights
        if 'Threshold' in lines[i]:
            # Mutate the threshold value
            threshold = float(lines[i+1].strip().split(':')[-1])
            threshold += mutation_range * (2 * np.random.random() - 1)
            lines[i+1] = f'  Threshold: {threshold}\n'
        elif 'Weights' in lines[i]:
            # Mutate the weights values
            weights = list(map(float, lines[i+1].strip().split(':')[-1].split(',')))
            for j in range(len(weights)):
                if np.random.random() < mutation_rate:
                    weights[j] += mutation_range * (2 * np.random.random() - 1)
            lines[i+1] = f'  Weights: {", ".join(str(w) for w in weights)}\n'

# Write the mutated net file in the new directory
new_net_path = os.path.join(new_gen_folder_path, f'net_{best_net.split("_")[-1]}')
with open(new_net_path, 'w') as f:
    f.writelines(lines)

# Copy the best report file to the new directory
new_report_path = os.path.join(new_gen_folder_path, os.path.basename(best_report))
shutil.copy(best_report, new_report_path)

# Print the results
print(f'Best fitness: {best_fitness}')
print(f'Best net: {best_net}')
print(f'Best report: {best_report}')
print(f'New net path: {new_net_path}')
print(f'New report path: {new_report_path}')