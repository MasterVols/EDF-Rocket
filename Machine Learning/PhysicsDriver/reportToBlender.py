import os
import bpy

# set path to reports folder
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
    # set file name to the latest ReportsXXX.txt file
    file_name = os.path.join(report_folder, latest_file)

    # open file and read contents
    with open(file_name, "r") as f:
        file_contents = f.read()

    # split file contents into individual position and rotation lines
    lines = file_contents.split("\n")
    data_lines = [l for l in lines if l.startswith("Position:")]

    # loop through data lines and keyframe each frame
    rocket = bpy.data.objects["rocket"]
    for i, line in enumerate(data_lines):
        position = line.split("Position: [")[1].split("]")[0].split(", ")
        rotation = line.split("Rotation: [")[1].split("]")[0].split(", ")
        rocket.location = (float(position[0]), float(position[1]), float(position[2]))
        rocket.rotation_euler = (float(rotation[0]), float(rotation[1]), float(rotation[2]))
        rocket.keyframe_insert(data_path="location", frame=i)
        rocket.keyframe_insert(data_path="rotation_euler", frame=i)
