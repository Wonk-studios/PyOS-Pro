#This is a developer tool that is not mainly used by the end user. It is used to index the repository and list all the files in the repository.

import os #Includes the OS module and headers

def index_repository(root_dir): #defines the index repository
    for root, dirs, files in os.walk(root_dir): #os.walk is used to list all the files in the repository
        for file in files: #for loop to list all the files in the repository
            file_path = os.path.join(root, file) #joins the root and file
            print(file_path) #prints the file path

if __name__ == "__main__": #if the file is run as the main file
    root_directory = "."  # Change this to the root directory of your repository
    index_repository("/workspaces/PyOS-Pro/PyOS/") #Defines the path to index