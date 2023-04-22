import os
import bpy
import math

# set path to reports folder 
# Do not delete other peoples Path
report_folder = "C:\\Users\\Matth\\OneDrive\\Documents\\GitHub\\EDF-Rocket\\Machine Learning\\PhysicsDriver\\reports"




# find the most recent ReportsXXX.txt file in the folder
latest_file = ""
for file in os.listdir(report_folder):
    if file.startswith("Reports") and file.endswith(".txt"):
        if file > latest_file:
            latest_file = file

# check if a valid file was found
if latest_file == "":
    print("No ReportsXXX.txt files found in directory.")
else:
    print("Using File: ")
    print(latest_file)
    # set file name to the latest ReportsXXX.txt file
    file_name = os.path.join(report_folder, latest_file)

    # open file and read contents
    with open(file_name, "r") as f:
        file_contents = f.read()

    # split file contents into individual position and rotation lines
    lines = file_contents.split("\n")
    data_lines = [l for l in lines if l.startswith("Position:")]

    rocket = bpy.data.objects["rocket"]
    thrust = bpy.data.objects["thrust"]
    for i, line in enumerate(data_lines):
        position = line.split("Position: [")[1].split("]")[0].split(", ")
        rotation = line.split("Rotation: [")[1].split("]")[0].split(", ")
        thrust_rotation = line.split("Thrust Rotation: (")[1].split(")")[0].split(", ")
        thrust_magnitude = float(line.split("Thrust Magnitude: ")[1])

        rocket.location = (float(position[0]), float(position[1]), float(position[2]))
        rocket.rotation_euler = (float(rotation[0]), float(rotation[1]), float(rotation[2]))
        rocket.keyframe_insert(data_path="location", frame=i)
        rocket.keyframe_insert(data_path="rotation_euler", frame=i)

        thrust.location = rocket.location
        # Clamp thrust rotation to rocket rotation
        clamped_thrust_rotation_x = rocket.rotation_euler.x + -float(thrust_rotation[0])
        clamped_thrust_rotation_y = rocket.rotation_euler.y + -float(thrust_rotation[1])

        thrust.rotation_euler = (clamped_thrust_rotation_x, clamped_thrust_rotation_y, rocket.rotation_euler.z)
        thrust.scale = (1, 1, thrust_magnitude * 5)  # Adjust the scaling factor as needed
        thrust.keyframe_insert(data_path="location", frame=i)
        thrust.keyframe_insert(data_path="rotation_euler", frame=i)
        thrust.keyframe_insert(data_path="scale", frame=i)

#EXAMPLE of REPORT: Position: [0.0, 0.0, 99.997275], Rotation: [-0.021407666666666665, -0.00447585, 2.039270551465683], Velocity: [-0.006790729176076489, 0.02306420441853401, -0.07613362926191156], Thrust Rotation: (-1.28446, -0.268551), Thrust Magnitude: 0.554216

