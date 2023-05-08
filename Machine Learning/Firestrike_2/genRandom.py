#
#
# What should be generated:
# 2 2 2
# 2 2 2
# 2 2 2
# 2 2 2
# 2 2 2
# 2 2 2
# 2 2 2
# 2 2 2
# 2 2 2
# 
# Where each 2 is a random float value from -2 to 2
import os
import random

def generate_random_matrix():
    matrix = ""
    for _ in range(9):
        row = " ".join([str(round(random.uniform(-2, 2), 2)) for _ in range(3)])
        matrix += row + "\n"
    return matrix

def main():
    if not os.path.exists("C:\\Users\\Matth\\OneDrive\\Documents\\GitHub\\EDF-Rocket\\Machine Learning\\Firestrike_better\\nets"):
        os.makedirs("C:\\Users\\Matth\\OneDrive\\Documents\\GitHub\\EDF-Rocket\\Machine Learning\\Firestrike_better\\nets")

    os.chdir("C:\\Users\\Matth\\OneDrive\\Documents\\GitHub\\EDF-Rocket\\Machine Learning\\Firestrike_better\\nets")

    if not os.path.exists("C:\\Users\\Matth\\OneDrive\\Documents\\GitHub\\EDF-Rocket\\nets\\GEN1"):
        os.makedirs("C:\\Users\\Matth\\OneDrive\\Documents\\GitHub\\EDF-Rocket\\nets\\GEN1")

    os.chdir("C:\\Users\\Matth\\OneDrive\\Documents\\GitHub\\EDF-Rocket\\nets\\GEN1")

    for i in range(1000):
        file_name = f"net{i:03d}.txt"
        with open(file_name, "w") as f:
            f.write(generate_random_matrix())

if __name__ == "__main__":
    main()
