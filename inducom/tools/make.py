# compile current c++ backend code and store exacutables in bin file
import os           as os
import json         as json
# g++ main.cpp sqlite3.o -Ipath\to\sqlite3
os.system("clear")

json_file       = open('./settings.json', 'r')
settings        = json.load(json_file)
directories     = settings["c libraries to compile"]
bin_folder      = "../bin/"
exe_name        = "c_libraries"
command         = "gcc -g -O -Wall "
files           = []

for current_dir in directories :
    src_code = os.listdir(current_dir)
    for current_file in src_code :
        if current_file.endswith(".c"):
            command += current_dir + current_file + " "
            files.append(current_dir + current_file)

if len(files) > 0 :
    print("Compiled Files:\n")
    print("============================================================")
    for fl in files : print(fl)
    print("============================================================\n\n")
    os.system(command + "-o " + bin_folder + exe_name)

json_file.close()



