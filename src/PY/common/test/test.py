'''
Created on Jul 26, 2015

@author: alex
'''



BIN_ODE_FILEPATH = "//home/alex/CProject_mars/TCNN/src/CPP/build/unit_test"

RESULT_FILE_PATH = "unit_test.log" #//home/alex/CProject_mars/TCNN/build/result/unit_test.log"

import subprocess

#import ../plot as plot_lib
#from ..plot import *

from common.plot.plot import plot_all

def test():

    ''' Call ODE program '''
    subprocess.check_call([BIN_ODE_FILEPATH, "--steps", "1000", "--step_len", "0.1"])
    
    f = open(RESULT_FILE_PATH, 'r')
    
    XX = []
    
    for line in f:
        XX.append([])
        for num in line.split():
            XX[-1].append(num)
    
    res = plot_all(XX)
    
    return res




'''
    MAIN
'''
res = test()
print (res)