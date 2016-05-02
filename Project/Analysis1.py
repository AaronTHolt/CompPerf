import csv
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import statsmodels.api as sm

from statsmodels.stats.anova import anova_lm
from statsmodels.graphics.api import interaction_plot, abline_plot
from statsmodels.formula.api import ols

#average data again:
average_data = False

copy = pd.read_csv('Exp1/copy.csv', skiprows=1, \
    names=['repetition', 'opt_level', 'bits', 'precision', 'bw', 'avg_time'])
scale = pd.read_csv('Exp1/scale.csv', skiprows=1, \
    names=['repetition', 'opt_level', 'bits', 'precision', 'bw', 'avg_time'])
triad = pd.read_csv('Exp1/triad.csv', skiprows=1, \
    names=['repetition', 'opt_level', 'bits', 'precision', 'bw', 'avg_time'])
add = pd.read_csv('Exp1/add.csv', skiprows=1, \
    names=['repetition', 'opt_level', 'bits', 'precision', 'bw', 'avg_time'])

def offset(dataset, offset):
    '''Used to see points on scatter plots better'''
    return [x+offset for x in dataset]

# line0, = plt.plot(offset(copy['opt_level'],0.015), copy['bw'], 'bo', markersize=4.5)
# line1, = plt.plot(offset(scale['opt_level'],+0.04), scale['bw'], 'gp', markersize=4.5)
# line2, = plt.plot(offset(triad['opt_level'],-0.04), triad['bw'], 'kx', markersize=4.5)
# line3, = plt.plot(offset(add['opt_level'],-0.015), add['bw'], 'rs', markersize=4.5)
# plt.xlabel('Optimization Level')
# LABELS = ["O0", "O1", "O2", "O3" ]
# plt.xticks([0,1,2,3], LABELS)
# plt.ylabel('Bandwidth (MB/s)')
# plt.title("Optimization vs Bandwidth for Copy")
# plt.legend([line0, line1, line2, line3], 
#   ['Copy', 'Scale', 'Triad', 'Add'], loc=4)
# plt.show()

# line0, = plt.plot(offset(copy['bits'],0.015), copy['bw'], 'bo', markersize=4.5)
# line1, = plt.plot(offset(scale['bits'],-0.015), scale['bw'], 'gp', markersize=4.5)
# line2, = plt.plot(offset(triad['bits'],0.015), triad['bw'], 'kx', markersize=4.5)
# line3, = plt.plot(offset(add['bits'],-0.015), add['bw'], 'rs', markersize=4.5)
# plt.xlabel('Optimization Level')
# LABELS = ["32bit", "64bit" ]
# plt.xticks([-1,1], LABELS)
# plt.ylabel('Bandwidth (MB/s)')
# plt.title("Bits vs Bandwidth for Copy")
# plt.legend([line0, line1, line2, line3], 
#   ['Copy', 'Scale', 'Triad', 'Add'], loc=8)
# plt.show()

# line0, = plt.plot(offset(copy['precision'],0.015), copy['bw'], 'bo', markersize=4.5)
# line1, = plt.plot(offset(scale['precision'],-0.015), scale['bw'], 'gp', markersize=4.5)
# line2, = plt.plot(offset(triad['precision'],0.015), triad['bw'], 'kx', markersize=4.5)
# line3, = plt.plot(offset(add['precision'],-0.015), add['bw'], 'rs', markersize=4.5)
# plt.xlabel('Optimization Level')
# LABELS = ["Disabled", "Enabled" ]
# plt.xticks([-1,1], LABELS)
# plt.ylabel('Bandwidth (MB/s)')
# plt.title("Precision vs Bandwidth for Copy")
# plt.legend([line0, line1, line2, line3], 
#   ['Copy', 'Scale', 'Triad', 'Add'], loc=8)
# plt.show()


#### TODO: Confidence intervals!

#Avererage Data
if average_data == True:
    copy_avg = []
    scale_avg = []
    triad_avg = []
    add_avg = []

    files = ['copy', 'scale', 'triad', 'add']
    for file in files:
        new_content = []

        with open('Exp1/'+file+'.csv') as f:
            content = f.readlines()
            content2 = []


            #make numerical
            for row in content:
                indiv_row = []
                row = row.split(",")
                # print(row)
                for jj, col in enumerate(row):
                    if jj<=3:
                        indiv_row.append(int(float(col)))
                    else:
                        indiv_row.append(float(col))
                content2.append(indiv_row)

            
            for ii in range(0,len(content2),3):
                new_content.append([float(sum(col))/len(col) for col in zip(*content2[ii:ii+3])])
                # new_content = map(my_mean, zip(*content[ii:ii+3]))
                # print(ii, list(new_content))
                # if file == 'copy':
                #     copy_avg.append(new_content)

        with open('Exp1/' + file + '_avg.csv', 'ta') as outcsv:
            writer = csv.writer(outcsv)
            writer.writerows(new_content)


copy_avg = pd.read_csv('Exp1/copy_avg.csv', skiprows=1, \
    names=['repetition', 'opt_level', 'bits', 'precision', 'bw', 'avg_time'])
scale_avg = pd.read_csv('Exp1/scale_avg.csv', skiprows=1, \
    names=['repetition', 'opt_level', 'bits', 'precision', 'bw', 'avg_time'])
triad_avg = pd.read_csv('Exp1/triad_avg.csv', skiprows=1, \
    names=['repetition', 'opt_level', 'bits', 'precision', 'bw', 'avg_time'])
add_avg = pd.read_csv('Exp1/add_avg.csv', skiprows=1, \
    names=['repetition', 'opt_level', 'bits', 'precision', 'bw', 'avg_time'])


names=['repetition', 'opt_level', 'bits', 'precision', 'bw', 'avg_time']
for ii in names:
    copy_avg[ii] = copy_avg[ii].astype('category')
    scale_avg[ii] = scale_avg[ii].astype('category')
    triad_avg[ii] = triad_avg[ii].astype('category')
    add_avg[ii] = add_avg[ii].astype('category')


copy_lm = ols('bw ~ C(opt_level)*C(bits)*C(precision)', 
                data=copy).fit()
copy_anova = sm.stats.anova_lm(copy_lm, typ=2)
print(copy_anova)