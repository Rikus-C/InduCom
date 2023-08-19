# compile current c++ backend code and store exacutables in bin file

import os           as os
import subprocess   as sub
# g++ main.cpp sqlite3.o -Ipath\to\sqlite3
os.system("clear")

directories = [
    "../src/",
    "../libs/delays/",
    "../libs/hash_map/",
    "../libs/linked_list/"
]

bin_folder      = "../bin/"
exe_name        = "RROS"
command         = "gcc -g -O -Wall "
files           = []

req = input("Compile code? (y or n)")

if req == "N" or req == "n" :
    os.system("clear")
    sub.run(bin_folder + exe_name, shell=True)
    quit()

os.system("clear")

for current_dir in directories :
    src_code = os.listdir(current_dir)
    for current_file in src_code :
        if current_file.endswith(".c"):
            command += current_dir + current_file + " "
            files.append(current_dir + current_file)

if len(files) > 0 :
    print("Compiled files:\n")
    print("============================================================")
    for fl in files : print(fl)
    print("============================================================\n\n")
    sub.run(command + "-o " + bin_folder + exe_name, shell=True)

# ask user if he would like to run the code now

a = input("\nRun code? (y or n)")
os.system("clear")

if a == "Y" or a == "y" :
    sub.run(bin_folder + exe_name, shell=True)
