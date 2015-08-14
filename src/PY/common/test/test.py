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


'''
 *      Function:
 *                  (X-0.9)^2 + cos(3*PI*(X-0.9))
'''
def run_case_1():
    subprocess.check_call([WIN_BIN_OPT_FUNC
        , "--steps", "2000"
        , "--step_len", "0.1"
        , "--alpha", "0.3"
        , "--chaotic_coeff", "3"
        , "--chaotic_reduce", "0.9995"
        , "--function", "1"])

    sub_plot_find_path(RESULT_FILE_PATH_OPT, 3, 1)

    sub_plot_from_file(RESULT_FILE_PATH, 3, 1)
    sub_plot_from_file(RESULT_FILE_PATH_OPT, 3, 2)
    res = sub_plot_from_file(RESULT_FILE_PATH_OPT_CHAOS+"_0", 3, 3, 3)



    print (res)


'''
/*
 *      Function:
 *                  (10*X-0.5)^2
 */
 '''
def run_case_2():
    subprocess.check_call([WIN_BIN_OPT_FUNC
        , "--steps", "2000"
        , "--step_len", "0.1"
        , "--alpha", "0.3"
        , "--chaotic_coeff", "3"
        , "--chaotic_reduce", "0.9995"
        , "--function", "2"])

    sub_plot_find_path(RESULT_FILE_PATH_OPT, 3, 1))

    sub_plot_from_file(RESULT_FILE_PATH, 3, 1)
    sub_plot_from_file(RESULT_FILE_PATH_OPT, 3, 2)
    res = sub_plot_from_file(RESULT_FILE_PATH_OPT_CHAOS+"_0", 3, 3, 3)

    print (res)



'''
/*
 *     3D Function:
 *                  -20.0*exp(-0.2*sqrt(0.5*(X0^2+X1^2))) - exp(0.5*(cos(2*PI*X0)+cos(2*PI*X[1]))) + exp(1) + 20;
 */
 '''
def run_case_3():
    subprocess.check_call([WIN_BIN_OPT_FUNC
        , "--steps", "8000"
        , "--step_len", "0.1"
        , "--alpha", "0.3"
        , "--chaotic_coeff", "3"
        , "--chaotic_reduce", "0.9995"
        , "--function", "3"])

    sub_plot_from_file(RESULT_FILE_PATH_OPT, 3, 1)
    sub_plot_from_file(RESULT_FILE_PATH_OPT_CHAOS+"_0", 3, 2, 3)
    res = sub_plot_from_file(RESULT_FILE_PATH_OPT_CHAOS+"_1", 3, 3, 3)

    print (res)

'''
/*
 *     3D Function:
 *                  sin^2(3*PI*X) + (X-1)^2 * (1+sin^2(3*PI*Y)) + (Y-1)^2 * (1+sin(2*PI*Y))
 */
 '''
def run_case_4():
    subprocess.check_call([WIN_BIN_OPT_FUNC
        , "--steps", "8000"
        , "--step_len", "0.1"
        , "--alpha", "0.3"
        , "--chaotic_coeff", "4"
        , "--chaotic_reduce", "0.9995"
        , "--function", "4"])

    sub_plot_from_file(RESULT_FILE_PATH_OPT, 3, 1)
    sub_plot_from_file(RESULT_FILE_PATH_OPT_CHAOS+"_0", 3, 2, 3)
    res = sub_plot_from_file(RESULT_FILE_PATH_OPT_CHAOS+"_1", 3, 3, 3)

    print (res)



'''
    MAIN
'''


run_case_1()
# run_case_2()
# run_case_3()
# run_case_4()




