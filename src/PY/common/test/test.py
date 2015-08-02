'''
Created on Jul 26, 2015

@author: alex
'''



BIN_ODE_FILEPATH_ODE45 = "//home/alex/CProject_mars/TCNN/src/CPP/build/unit_test"
RESULT_FILE_PATH_ODE45 = "unit_test.log" #//home/alex/CProject_mars/TCNN/build/result/unit_test.log"

BIN_ODE_FILEPATH = "//home/alex/CProject_mars/TCNN/src/CPP/build/opt_func_test"
RESULT_FILE_PATH = "function.log"
RESULT_FILE_PATH_OPT = "opt_func_res.log"
RESULT_FILE_PATH_OPT_CHAOS = "chaos.log"

import subprocess

#import ../plot as plot_lib
#from ..plot import *

import matplotlib.pyplot as plt

from common.plot.plot import plot_all
from common.plot.plot import subplot


'''
Run ODE from binary file
'''
def run_bin_file(bin_path):
    subprocess.check_call([bin_path, "--steps", "1000", "--step_len", "0.1"])


'''
Fill array with data from external file
'''
def fill_data_from_file(file_name):
    XX = []
    
    f = open(file_name, 'r')

    for line in f:
        XX.append([])
        for num in line.split():
            XX[-1].append(num)
    
    return XX

'''
Plot All data from file
'''
def plot_from_file(result_file_name):
    XX = fill_data_from_file(result_file_name)
    
    return plot_all(XX)


'''
Plot data on one the part
'''
def sub_plot_from_file(result_file_name, amount_plots, index, col = 1):
    XX = fill_data_from_file(result_file_name)
    
    res = subplot(XX, amount_plots, index, col)
    
    print (result_file_name + ":")
    print (XX[-1])
    
    if index == amount_plots:
        plt.show()
    
    return res

def test(bin_path, result_file_name):

    ''' Call ODE program '''
    subprocess.check_call([bin_path, "--steps", "5000", "--step_len", "0.1"])
    
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
#res = test(BIN_ODE_FILEPATH, RESULT_FILE_PATH_OPT)
#res = test(BIN_ODE_FILEPATH, RESULT_FILE_PATH_OPT_CHAOS)

run_bin_file(BIN_ODE_FILEPATH)
 
res = sub_plot_from_file(RESULT_FILE_PATH, 3, 1)
res = sub_plot_from_file(RESULT_FILE_PATH_OPT, 3, 2)
res = sub_plot_from_file(RESULT_FILE_PATH_OPT_CHAOS, 3, 3, 3)

# res = sub_plot_from_file("chaos_test.log", 1, 1)


print (res)


