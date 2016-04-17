import os,sys

def cleanAvg(f,f0,n):
    for fn in [1,2,3,4,5]:
        f[fn] = f[fn]/n
    f[0] = f0
    return f

def batchAverage(fd, timeWindow = 10.0):
    line = fd.readline()
    if line == "" :
        raise Exception('eol')
    avg = line.split(',')
    avg = [ float(x) for x in avg ]
    startTime = avg[0]
    n = 1
    while fd:
        line = fd.readline()
        if line == "":
            return cleanAvg(avg, fields[0], n)
        n = n + 1
        fields = line.split(',')
        fields = [ float(x) for x in fields ]
#        print "add in ", fields
        for fn in [1,2,3,4,5]:
            avg[fn] = avg[fn] + fields[fn]
        if fields[0] - startTime > timeWindow:
            return cleanAvg(avg, fields[0], n)

while sys.stdin:
    try:
        avgs = [ str(f) for f in batchAverage(sys.stdin) ]
        print ', '.join(avgs)
    except Exception as err:
        #print "Exception", err
        break
 
