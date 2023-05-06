import subprocess
import random
import math
import time
import os

#
#   Use python 3.8.10
#   python --version to check
#

Executable = "C:\\Users\\reed2\\OneDrive\\Desktop\\Github Repos\\EDF-Rocket\\Machine Learning\\Ffann\\main.exe"
report_folder = "C:\\Users\\reed2\\OneDrive\\Desktop\\Github Repos\\EDF-Rocket\Machine Learning\\Ffann\\ffann-reports"

#TWEAKING VALUES:
randomRotationOnStart = False

#Fitness Tweaking:
landFrameMultiplier = 0.1             #Each frame survived is + 1 * multiplier

landRotMaxAngle = 5                 #Max rotation to call a successful landing
landVeloMaxVelo = 5                 #Max velocity to call a successful landing
landUnderMaxConsMultiplier = 100    #for a successful landing under max velo and rotation

# Constants
G = 9.81
DT = 1/60
HEIGHT = 100
ROCKET_HEIGHT = 1
CENTER_OF_MASS = 0.5

for a in range(10):
    gennetexecutable = "C:\\Users\\reed2\\OneDrive\\Desktop\\Github Repos\\EDF-Rocket\\Machine Learning\Ffann\\netpsp.exe"
    subprocess.check_output([gennetexecutable], text=False)

    for a in range(100):
        with open("repnum.txt","r") as file:
            netind = file.read()
        with open("repnum.txt","w") as file:
            file.truncate()
            file.write(str(int(netind)+1))
            
        
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
            position = [0, 0, HEIGHT]
            rotation = [random.uniform(0, 2*math.pi) for _ in range(3)]
            velocity = [0, 0, 0]
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
                while position[2] > 0 and position[2] < 300 and position[1] < 1000 and position[1] > -1000 and position[0] < 1000 and position[0] > -1000:
                    # Send the current state to the C++ neural network program
                    input_data = ' '.join(map(str, position + rotation + velocity + list(thrust_rotation)))
                    output_data = subprocess.check_output([Executable], input=input_data, text=True).strip()

                    # Parse the output
                    thrust_rotation_1, thrust_rotation_2, thrust_value = map(float, output_data.split())
                    thrust_rotation = (thrust_rotation_1, thrust_rotation_2)

                    # Update the physics
                    position, rotation, velocity = update_physics(position, rotation, velocity, thrust_value, thrust_rotation)

                    fitness += 1 * landFrameMultiplier

                    # Write the current state to the report file
                    report_line = f"Position: {position}, Rotation: {rotation}, Velocity: {velocity}, Thrust Rotation: {thrust_rotation}, Thrust Magnitude: {thrust_value}\n"
                    report_file.write(report_line)

                    #time.sleep(DT)

                #Send final fitness:
                if abs(rotation[0]) % 360 < landRotMaxAngle and abs(rotation[1]) % 360 < landRotMaxAngle and abs(velocity[2]) < landVeloMaxVelo:
                    fitness_line = f"fitness: {fitness + 1 * landUnderMaxConsMultiplier}\n"
                else:
                    if abs(position[1]) < 10:
                        fitness += 10
                    if abs(position[0]) < 10:
                        fitness += 10
                    
                    if abs(velocity[2]) < landVeloMaxVelo:
                        fitness += 100
                    elif abs(velocity[2]) < landVeloMaxVelo * 2:
                        fitness += 25
                    else:
                        fitness = fitness / (1 + abs(velocity[2]))
                        
                    if abs(position[0]) > 1000 or abs(position[1]) > 1000:
                        fitness = 0
                    
                    fitness = round(fitness)
                    if position[0] > 1000 or position[0] < -1000 or position[1] > 1000 or position[1] < -1000:
                        fitness = 0
                    fitness_line = f"fitness: {fitness}\n"
                report_file.write(fitness_line)
        if __name__ == "__main__":
            main()


