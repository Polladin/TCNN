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

#D:\progs\Cygwin\home\akukushk\TCNN\src\CPP\build\opt_func_test.exe
WIN_BIN_OPT_FUNC = "D:/progs/Cygwin/home/akukushk/TCNN/src/CPP/build/opt_func_test.exe"

import subprocess

#import ../plot as plot_lib
#from ..plot import *

import matplotlib.pyplot as plt

from common.plot.plot import *


def run_case_1():
    subprocess.check_call([WIN_BIN_OPT_FUNC
        , "--steps", "8000"
        , "--step_len", "0.1"
        , "--alpha", "0.3"
        , "--chaotic_coeff", "3"
        , "--chaotic_reduce", "0.9995"])

    sub_plot_from_file(RESULT_FILE_PATH_OPT, 3, 1)
    sub_plot_from_file(RESULT_FILE_PATH_OPT_CHAOS+"_0", 3, 2, 3)
    res = sub_plot_from_file(RESULT_FILE_PATH_OPT_CHAOS+"_1", 3, 3, 3)

    print (res)

def run_case_2():
    subprocess.check_call([WIN_BIN_OPT_FUNC
        , "--steps", "2000"
        , "--step_len", "0.1"
        , "--alpha", "0.3"
        , "--chaotic_coeff", "3"
        , "--chaotic_reduce", "0.9995"
        , "--function", "1"])

    sub_plot_from_file(RESULT_FILE_PATH_OPT, 2, 1)
    res = sub_plot_from_file(RESULT_FILE_PATH_OPT_CHAOS+"_0", 2, 2, 3)

    print (res)
'''
    MAIN
'''
#res = test(BIN_ODE_FILEPATH_ODE45, RESULT_FILE_PATH_ODE45)
#res = test(BIN_ODE_FILEPATH, RESULT_FILE_PATH)
#res = test(BIN_ODE_FILEPATH, RESULT_FILE_PATH_OPT)
#res = test(BIN_ODE_FILEPATH, RESULT_FILE_PATH_OPT_CHAOS)

#run_bin_file(BIN_ODE_FILEPATH)
#run_bin_file(WIN_BIN_OPT_FUNC)

#res = sub_plot_from_file(RESULT_FILE_PATH, 3, 1)
#res = sub_plot_from_file(RESULT_FILE_PATH_OPT, 3, 1)
#res = sub_plot_from_file(RESULT_FILE_PATH_OPT_CHAOS+"_0", 3, 2, 3)
#res = sub_plot_from_file(RESULT_FILE_PATH_OPT_CHAOS+"_1", 3, 3, 3)

# res = sub_plot_from_file("chaos_test.log", 1, 1)

run_case_2()




