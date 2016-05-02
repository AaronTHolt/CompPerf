import os
import subprocess
from pyDOE import *
import csv


#Experiment 1:
# 4*2*2
# O[0-4], -DSTREAM_TYPE=float (single precision variables on or off), -m32 vs -m64


#compile and run experiment?
run = False

### Create experiment
table = ff2n(2)
# print(table)

all_data = {}
full_table = []

commands = []
filenames = []

cmd_base = "cc stream.c -o "

for opt in [0,1,2,3]:
	

    for exp in table:
        cmd_opts = ""
        O_level = " -O"+str(opt)
        cmd_opts += O_level

        file_output = "Exp1/"
        file_output += "O" + str(opt)

        if exp[0] > 0:
            cmd_opts += " -m32"
            file_output += "_32"
        else:
            cmd_opts += " -m64"
            file_output += "_64"

        if exp[1] < 0:
            cmd_opts += " -DSTREAM_TYPE=float"
            file_output += "_S"
        else:
            file_output += "_D"

        for jj in range(3):
            full_table.append([-1,opt,exp[0],exp[1],-1,-1])
        filenames.append(file_output)
        commands.append(cmd_base+file_output+cmd_opts)

all_data['copy'] = list(full_table)
all_data['scale'] = list(full_table)
all_data['add'] = list(full_table)
all_data['triad'] = list(full_table)

if run == True:
    ### Compile Experiment
    for cmd in commands:
        print(cmd)
        subprocess.call(cmd, shell=True)
        process = subprocess.Popen(cmd, shell=True, \
            stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL).communicate()[0]


    ### Run Experiment
    for trial in filenames:
        for replication in range(3):
            #overwrite file on first repl
            if replication == 0:
                print("./"+trial + " > " + trial+".out")
                process = subprocess.Popen("./"+trial + " >> " + trial+".out", shell=True)
                process.wait()
            else:
                print("./"+trial + " >> " + trial+".out")
                process = subprocess.Popen("./"+trial + " >> " + trial+".out", shell=True)
                process.wait()


def str_to_float(stream_list):
    stream_list.pop(0)
    for ii, col in enumerate(stream_list):
            stream_list[ii] = float(stream_list[ii])

    return stream_list

def get_index(filename, replications, cur_repl):
    index = 0

    #optimization level
    index += int(float(filename[6]))*12

    #32 or 62 bit
    if "_64" in filename:
        index += 2*replications

    #single precision?
    if "_S" in filename:
        index += 1*replications

    #replication number
    index += cur_repl

    return index

def stream_data_to_csv(filename, csvfile, replications):
    '''	filename is stream data file
        csvfile is the csv to write to
        replications is the number of times each setup was run'''
    content = []
    with open(filename) as f:
        content = f.readlines()
    f.close()

    repl = 0
    csv_prefix = "Exp1/"

    for line in content:
        if repl >= replications:
            break

        index = get_index(filename, replications, repl)

        if "Copy:" in line:
            tt = 'copy'
            # print("Repl = ", repl)
            data = str_to_float(line.split())
            all_data[tt][index][0] = repl
            all_data[tt][index][4] = data[0]
            all_data[tt][index][5] = data[1]

            # print(all_data['copy'][index], repl, index)
            with open(csv_prefix + tt + '.csv', 'ta') as outcsv:
                writer = csv.writer(outcsv)
                writer.writerow(all_data[tt][index])

        elif "Scale:" in line:
            tt = 'scale'
            data = str_to_float(line.split())
            all_data[tt][index][0] = repl
            all_data[tt][index][4] = data[0]
            all_data[tt][index][5] = data[1]

            # print(all_data['copy'][index], repl, index)
            with open(csv_prefix + tt + '.csv', 'ta') as outcsv:
                writer = csv.writer(outcsv)
                writer.writerow(all_data[tt][index])

        elif "Add:" in line:
            tt = 'add'
            data = str_to_float(line.split())
            all_data[tt][index][0] = repl
            all_data[tt][index][4] = data[0]
            all_data[tt][index][5] = data[1]

            # print(all_data['copy'][index], repl, index)
            with open(csv_prefix + tt + '.csv', 'ta') as outcsv:
                writer = csv.writer(outcsv)
                writer.writerow(all_data[tt][index])

        elif "Triad:" in line:
            tt = 'triad'
            data = str_to_float(line.split())
            all_data[tt][index][0] = repl
            all_data[tt][index][4] = data[0]
            all_data[tt][index][5] = data[1]

             # print(all_data['copy'][index], repl, index)
            with open(csv_prefix + tt + '.csv', 'ta') as outcsv:
                writer = csv.writer(outcsv)
                writer.writerow(all_data[tt][index])

            ##next replication after triad
            repl += 1



### Process Data
csv_prefix = "Exp1/"

files = ['copy', 'scale', 'add', 'triad']

for ii in files:
    #clear contents of old files
    open(csv_prefix + ii + '.csv', 'w').close()


for exp in sorted(filenames):
    # print(exp)

    outfile = exp+".out"
    # print(outfile)
    stream_data_to_csv(outfile, csv_prefix, 3)
