import os

def read_zones(folder_name):
    data = {}

    # Get the current working directory
    current_dir = os.getcwd()

    # Go into the folder
    target_folder = os.path.join(current_dir, folder_name)

    for filename in os.listdir(target_folder):
        file_path = os.path.join(target_folder, filename)

        # Check if it is a file
        if os.path.isfile(file_path):
            with open(file_path, "r", encoding="utf-8") as f:
                content = f.read()
                lines = content.splitlines()
                finalLine = []
                for line in lines:
                    if line.strip():
                        finalLine.append([line.split(" ")[1], line.split(" ")[3]])
                data[filename] = finalLine

    return data


# Example of use
folder_name = "utils/WifiData"
files_dict = read_zones(folder_name)

print(files_dict)