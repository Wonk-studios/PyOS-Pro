import os

def index_repository(root_dir):
    for root, dirs, files in os.walk(root_dir):
        for file in files:
            file_path = os.path.join(root, file)
            print(file_path)

if __name__ == "__main__":
    root_directory = "."  # Change this to the root directory of your repository
    index_repository(root_directory)