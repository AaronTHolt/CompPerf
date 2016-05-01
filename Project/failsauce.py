import os
import subprocess
from pyDOE import *
import csv


#Experiment 1:
# 4*2*2
# O[0-4], -DSTREAM_TYPE=float (single precision variables on or off), -m32 vs -m64


#compile and run experiment?
comp = False
run = False


# print(table)

all_data = {}
full_table = []

commands = []
filenames = []

cmd_base = ['cc', 'stream.c', '-o']


#O3 opts
opt_list = ['inline-functions', 'unswitch-loops', 'predictive-commoning', 'gcse-after-reload', 
 'tree-loop-distribute-patterns', 'tree-slp-vectorize', 'vect-cost-model', 'tree-partial-pre', 'ipa-cp-clone']

#these ones not found 'tree-loop-vectorize', 'split-paths'

### Create experiment
# print(len(opt_list))
table = ff2n(len(opt_list))
# table = pbdesign(44)
print(table)
print(len(table))
print(len(table[0]))

for exp in table:
    full_command = []
    cmd_opts = ['-O2']
    t1 = [-1]

    file_output = "Exp2/"
    for ii, param in enumerate(exp):
        if param > 0:
            cmd_opts.append("-f"+opt_list[ii])
            file_output += "1"
            t1.append(1)
        else:
            # cmd_opts.append("-fno-"+opt_list[ii])
            file_output += "0"
            t1.append(0)
    
    #construct results table
    t1.append(-1)
    t1.append(-1)
    for jj in range(3):
        full_table.append(t1)

    # file_output += ".out"

    #Put compile command together
    for item in cmd_base:
        full_command.append(item)
    full_command.append(file_output)
    for item in cmd_opts:
        full_command.append(item)

    #store compile commands
    commands.append(full_command)

    #store output filenames
    filenames.append(file_output)

    


all_data['copy'] = list(full_table)
all_data['scale'] = list(full_table)
all_data['add'] = list(full_table)
all_data['triad'] = list(full_table)

print(len(full_table))

if comp == True:
    ### Compile Experiment
    for cmd in commands:
        print(cmd)
        subprocess.call(cmd)
        process = subprocess.Popen(cmd, \
            stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL).communicate()[0]

if run == True:
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
    exponent = 8

    for ii, factor in enumerate(filename):
        index += int(float(factor))*replications*(2**exponent)
        exponent -= 1

    #replication number
    index += cur_repl
    # print(filename, factor, ii, index, 'cur_repl = ', cur_repl)

    return index

def stream_data_to_csv(all_data, filename, csv_prefix, replications):
    ''' filename is stream data file
        csv_prefix is the directory the csvs are in
        replications is the number of times each setup was run'''
    content = []
    with open(csv_prefix+filename+".out") as f:
        content = f.readlines()
    f.close()

    repl = 0
    results = {}
    results['copy'] = []
    results['scale'] = []
    results['add'] = []
    results['triad'] = []

    for line in content:
        if repl >= replications:
            break

        index = get_index(filename, replications, repl)

        if "Copy:" in line:
            # print("Repl = ", repl)
            data = str_to_float(line.split())
            results['copy'].append([index, repl, data[0], data[1]])
            # all_data['copy'][index][0] = repl
            # all_data['copy'][index][10] = data[0]
            # all_data['copy'][index][11] = data[1]

            # print(all_data['copy'][index], repl, index)

        elif "Scale:" in line:
            data = str_to_float(line.split())
            results['scale'].append([index, repl, data[0], data[1]])
            # all_data['scale'][index][0] = repl
            # all_data['scale'][index][10] = data[0]
            # all_data['scale'][index][11] = data[1]

        elif "Add:" in line:
            data = str_to_float(line.split())
            results['add'].append([index, repl, data[0], data[1]])
            # all_data['add'][index][0] = repl
            # all_data['add'][index][10] = data[0]
            # all_data['add'][index][11] = data[1]

        elif "Triad:" in line:
            data = str_to_float(line.split())
            results['triad'].append([index, repl, data[0], data[1]])
            # all_data['triad'][index][0] = repl
            # all_data['triad'][index][10] = data[0]
            # all_data['triad'][index][11] = data[1]

            ##next replication after triad
            repl += 1

        # print(all_data['copy'][0:2])
    return results



### Process Data
csv_prefix = "Exp2/"

files = ['copy', 'scale', 'add', 'triad']

# print(len(filenames))

for ii in files:
    #clear contents of old files
    open(csv_prefix + ii + '.csv', 'w').close()


for exp in sorted(filenames):
    # print(exp)

    outfile = exp[5:]
    # print(outfile)
    results = stream_data_to_csv(all_data, outfile, csv_prefix, 3)

    for ff in files:
        for ii in range(3):
            rownum = results[ff][ii][0]
            all_data[ff][rownum][0] =  results[ff][ii][1]
            all_data[ff][rownum][10] =  results[ff][ii][2]
            all_data[ff][rownum][11] =  results[ff][ii][3]

        print(all_data['copy'][0:2])


print(all_data['copy'][0:2])


# print(all_data['copy'])

# #Write data to csv
# for ii in files:
#     with open(csv_prefix + ii + '.csv', 'wt') as outcsv:
#         writer = csv.writer(outcsv)
#         writer.writerow(['Repl', 'inline-functions', 'unswitch-loops', 'predictive-commoning', 'gcse-after-reload', 
#                         'tree-loop-distribute-patterns', 'tree-slp-vectorize', 'vect-cost-model', 'tree-partial-pre', 
#                         'ipa-cp-clone', 'Best Rate', 'Avg Time'])
#         for row in all_data[ii]:
#             print(row)
#             writer.writerow(row)
#     outcsv.close()




# opt_list = [['auto-inc-dec', 'branch-count-reg', 'combine-stack-adjustments'],
# ['compare-elim', 'cprop-registers' ,'dce'], ['defer-pop' ,'delayed-branch', 'dse'], 
# ['forward-propagate', 'guess-branch-probability', 'if-conversion2'], 
# ['if-conversion', 'inline-functions-called-once', 'ipa-pure-const'], 
# ['ipa-profile', 'ipa-reference', 'merge-constants'], 
# ['move-loop-invariants', 'reorder-blocks', 'shrink-wrap'], ['split-wide-types', 'ssa-backprop', 'ssa-phiopt'], 
# ['tree-bit-ccp', 'tree-ccp', 'tree-ch'], ['tree-coalesce-vars', 'tree-copy-prop', 'tree-dce'],
# ['tree-dominator-opts', 'tree-dse', 'tree-forwprop'], ['tree-fre', 'tree-phiprop', 'tree-sink'], 
# ['tree-slsr', 'tree-sra', 'tree-pta'], ['tree-ter', 'unit-at-a-time']]

## 01 ops
# opt_list = ['auto-inc-dec', 'branch-count-reg', 'combine-stack-adjustments',
# 'compare-elim', 'cprop-registers' ,'dce', 'defer-pop' ,'delayed-branch', 'dse', 
# 'forward-propagate', 'guess-branch-probability', 'if-conversion2', 
# 'if-conversion', 'inline-functions-called-once', 'ipa-pure-const', 
# 'ipa-profile', 'ipa-reference', 'merge-constants', 
# 'move-loop-invariants', 'reorder-blocks', 'shrink-wrap', 'split-wide-types', 'ssa-backprop', 'ssa-phiopt', 
# 'tree-bit-ccp', 'tree-ccp', 'tree-ch', 'tree-coalesce-vars', 'tree-copy-prop', 'tree-dce',
# 'tree-dominator-opts', 'tree-dse', 'tree-forwprop', 'tree-fre', 'tree-phiprop', 'tree-sink', 
# 'tree-slsr', 'tree-sra', 'tree-pta', 'tree-ter', 'unit-at-a-time']
