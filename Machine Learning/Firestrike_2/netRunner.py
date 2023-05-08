# THIS CODE FINDS THE NUERAL NET AND RUNS IT.
# THIS CODE IS CALLED FROM THE SUBPROCCESS FUNCTION

import sys

def read_file_data(file_path):
    data = []
    with open(file_path, 'r') as file:
        for line in file.readlines():
            data.append([float(x) for x in line.strip().split()])
    return data

def calculate_results(file_data, input_data):
    results = [0, 0, 0]
    for i in range(9):
        for j in range(3):
            results[j] += file_data[i][j] * input_data[i]
    return results

def main():
    file_path = "C:\\Users\\Matth\\OneDrive\\Documents\\GitHub\\EDF-Rocket\\nets\\GEN1\\net000.txt"
    file_data = read_file_data(file_path)

    for line in sys.stdin:
        input_data = [float(x) for x in line.strip().split()]
        if len(input_data) != 9:
            break

        output = calculate_results(file_data, input_data)
        print(" ".join(str(x) for x in output))

if __name__ == "__main__":
    main()