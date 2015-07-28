'''
Created on Jul 26, 2015

@author: alex
'''



BIN_ODE_FILEPATH_ODE45 = "//home/alex/CProject_mars/TCNN/src/CPP/build/unit_test"
RESULT_FILE_PATH_ODE45 = "unit_test.log" #//home/alex/CProject_mars/TCNN/build/result/unit_test.log"

BIN_ODE_FILEPATH = "//home/alex/CProject_mars/TCNN/src/CPP/build/opt_func_test"
RESULT_FILE_PATH = "function.log"
RESULT_FILE_PATH_OPT = "opt_func_res.log"

import subprocess

#import ../plot as plot_lib
#from ..plot import *

from common.plot.plot import plot_all

def test(bin_path, result_file_name):

    ''' Call ODE program '''
    subprocess.check_call([bin_path, "--steps", "1000", "--step_len", "0.1"])
    
    f = open(result_file_name, 'r')
    
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
#res = test(BIN_ODE_FILEPATH_ODE45, RESULT_FILE_PATH_ODE45)
#res = test(BIN_ODE_FILEPATH, RESULT_FILE_PATH)
res = test(BIN_ODE_FILEPATH, RESULT_FILE_PATH_OPT)

print (res)


