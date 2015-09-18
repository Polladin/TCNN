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
import ctypes

#import ../plot as plot_lib
#from ..plot import *

import matplotlib.pyplot as plt
import math
import random

from common.plot.plot import *
from ctypes import cdll



def run_case_1_from_lib():
    lib = cdll.LoadLibrary('./TCNN_lib.so')

    argv = [WIN_BIN_OPT_FUNC
        , "--steps", "5000"
        , "--step_len", "0.1"
        , "--alpha", "0.3"
        , "--chaotic_coeff", "3"
        , "--chaotic_reduce", "0.9995"
        , "--function", "1"
        , "--init_cond", "0,-2.8"]

    amount_strs = len(argv)

    max_len = len(max(argv, key=len))

    s = [ctypes.create_string_buffer(max_len) for i in range(amount_strs)]
    results = (ctypes.c_char_p * amount_strs)(*map(ctypes.addressof, s));

    for i in range(len(argv)):
        results[i] = argv[i]

    lib.opt_func_like_main(amount_strs, results)


    sub_plot_find_path(RESULT_FILE_PATH_OPT, 3, 1)

    sub_plot_from_file(RESULT_FILE_PATH, 3, 1)
    sub_plot_from_file(RESULT_FILE_PATH_OPT, 3, 2)
    res = sub_plot_from_file(RESULT_FILE_PATH_OPT_CHAOS+"_0", 3, 3, 3)

    print (res)




def run_case_1_from_DLL_obj():
    lib = cdll.LoadLibrary('./TCNN_lib.so')

    argv = [WIN_BIN_OPT_FUNC
        , "--steps", "2000"
        , "--step_len", "0.1"
        , "--alpha", "0.3"
        , "--chaotic_coeff", "3"
        , "--chaotic_reduce", "0.9995"
        , "--function", "1"
        , "--init_cond", "0,-2.8"]

    amount_strs = len(argv)

    max_len = len(max(argv, key=len))

    s = [ctypes.create_string_buffer(max_len) for i in range(amount_strs)]
    results = (ctypes.c_char_p * amount_strs)(*map(ctypes.addressof, s));

    for i in range(len(argv)):
        results[i] = argv[i]

    optFunc = lib.optFuncCreateDLL();

    lib.optFuncSetInitialConditionByArgvDLL(optFunc, amount_strs, results)

    lib.optFuncRunOptimizationDLL(optFunc)

#     lib.optFuncWriteResultDLL(optFunc, "DLL_opt_func_result.log")

    rows = lib.optFunctGetResultRows(optFunc)
    columns = lib.optFunctGetResultColumns(optFunc)
    data = ctypes.ARRAY(ctypes.c_double, rows*columns)()

    lib.optFuncTakeResultDLL(optFunc, data)
    plt.plot(data[:rows], data[rows:])

    plt.show()


'''
 *      Function:
 *                  (X-0.9)^2 + cos(3*PI*(X-0.9))
'''
def run_N_dim(dim, avg_err, max_err):

    random.seed()

    init_cond = '0'
    for i in range(dim):
        init_cond += ', ' + str((random.random()-0.5)*10)

#     init_cond = '0, -2.91390797751, 1.94005208823, -3.9011124444, -1.51972470693, 3.57775812322, -2.89826140281, 4.80608980877, -3.43612785435, 2.35672655962, 4.8499752525, 1.55583452182, 4.01655082987, -4.96777414788, 3.20264640854, -4.00995659717, -4.36198468508, 4.52249834155, 4.54700744199, 0.344288020182, 4.3256256062, 4.69193484689, 3.39881798533, -3.48823300319, -2.2041100248, -2.97365342168, -4.12237968019, -1.82323246241, -4.27959232412, 4.34788259037, -0.694539446176'
    print (init_cond)
#0, -2.91390797751, 1.94005208823, -3.9011124444, -1.51972470693, 3.57775812322, -2.89826140281, 4.80608980877, -3.43612785435, 2.35672655962, 4.8499752525, 1.55583452182, 4.01655082987, -4.96777414788, 3.20264640854, -4.00995659717, -4.36198468508, 4.52249834155, 4.54700744199, 0.344288020182, 4.3256256062, 4.69193484689, 3.39881798533, -3.48823300319, -2.2041100248, -2.97365342168, -4.12237968019, -1.82323246241, -4.27959232412, 4.34788259037, -0.694539446176
    subprocess.check_call([WIN_BIN_OPT_FUNC
        , "--steps", "30000"
        , "--step_len", "0.001"
        , "--chaotic_step_len", "0.15"
        , "--alpha", "0.20"
        , "--chaotic_coeff", "150000" #800
        , "--chaotic_reduce", "0.4"
        , "--function", "5"
        , "--dim", str(dim)
        , "--init_cond", init_cond])
#         , "--init_cond", "0, 2.8, 3.8, 1.8, 2.8, 3.8, -1.2, -3.0, -0.8, 1.9, 1.8, 2.8, 3.8, 1.8, 2.8, 3.8, -1.2, -3.0, -0.8, 1.9, 1.8, 2.8, 3.8, 1.8, 2.8, 3.8, -1.2, -3.0, -0.8, 1.9, -1.9"])

#     X = fill_data_from_file(RESULT_FILE_PATH_OPT)

#     sub_plot_find_path(RESULT_FILE_PATH_OPT, 1, 1)

#     XX = fill_data_from_file(RESULT_FILE_PATH_OPT)

#     print(XX)

#     sub_plot_from_file(RESULT_FILE_PATH, 3, 1, 1)
#     sub_plot_from_file(RESULT_FILE_PATH_OPT, 3, 1, 1)
#     sub_plot_from_file(RESULT_FILE_PATH_OPT, 3, 2, 2)
#     sub_plot_from_file(RESULT_FILE_PATH_OPT, 3, 3, 3)

#     sub_plot_find_path(RESULT_FILE_PATH_OPT, 1, 1)
#     sub_plot_from_file(RESULT_FILE_PATH, 2, 1)
#     sub_plot_from_file(RESULT_FILE_PATH_OPT, 1, 1)

#     plot_amount = 6
#     for i in range(plot_amount):
#         sub_plot_from_file(RESULT_FILE_PATH_OPT, plot_amount, i+1, i+1)
    XX = fill_data_from_file(RESULT_FILE_PATH_OPT)

    bad = 0
    print(XX[-1])
    for i in range(len(XX[-1])-1):
#         print (XX[-1][i])
        if abs(float(XX[-1][i+1])) > 0.1:
#             print('bad')
            bad += 1

    print('failed : ' + str(len(XX[-1])-1) + '/' + str(bad))
    print('func result:' + str(cacl_Rastrigin_func(XX[-1])))

    avg_err += abs(cacl_Rastrigin_func(XX[-1]))
    max_err = max(max_err, abs(cacl_Rastrigin_func(XX[-1])))

    return bad, avg_err, max_err
#     res = sub_plot_from_file(RESULT_FILE_PATH_OPT_CHAOS+"_0", 3, 3, 3)

#     return(res)


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
        , "--function", "1"
        , "--init_cond", "0,-0.8"])

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
        , "--function", "2"
        , "--init_cond", "0,3.5"])

    sub_plot_find_path(RESULT_FILE_PATH_OPT, 3, 1)

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
        , "--steps", "2000"
        , "--step_len", "0.1"
        , "--alpha", "0.3"
        , "--chaotic_coeff", "3"
        , "--chaotic_reduce", "0.9995"
        , "--function", "3"
        , "--init_cond", "0,-2,-2"])

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



def run_N_dim_func_6(dim,avg_err, max_err):

    random.seed()

    init_cond = '0'
    for i in range(dim):
        init_cond += ', ' + str((random.random()-0.5)*10)

#     init_cond = '0, -2.91390797751, 1.94005208823, -3.9011124444, -1.51972470693, 3.57775812322, -2.89826140281, 4.80608980877, -3.43612785435, 2.35672655962, 4.8499752525, 1.55583452182, 4.01655082987, -4.96777414788, 3.20264640854, -4.00995659717, -4.36198468508, 4.52249834155, 4.54700744199, 0.344288020182, 4.3256256062, 4.69193484689, 3.39881798533, -3.48823300319, -2.2041100248, -2.97365342168, -4.12237968019, -1.82323246241, -4.27959232412, 4.34788259037, -0.694539446176'

    init_cond = '0, -10'
    print (init_cond)
#0, -2.91390797751, 1.94005208823, -3.9011124444, -1.51972470693, 3.57775812322, -2.89826140281, 4.80608980877, -3.43612785435, 2.35672655962, 4.8499752525, 1.55583452182, 4.01655082987, -4.96777414788, 3.20264640854, -4.00995659717, -4.36198468508, 4.52249834155, 4.54700744199, 0.344288020182, 4.3256256062, 4.69193484689, 3.39881798533, -3.48823300319, -2.2041100248, -2.97365342168, -4.12237968019, -1.82323246241, -4.27959232412, 4.34788259037, -0.694539446176
    subprocess.check_call([WIN_BIN_OPT_FUNC
        , "--steps", "30000"
        , "--step_len", "0.001"
        , "--chaotic_step_len", "0.15"
        , "--alpha", "0.2"
        , "--chaotic_coeff", '4000' #"1500" #800
        , "--chaotic_reduce", "0.4"
        , "--function", "6"
        , "--dim", str(dim)
        , "--init_cond", init_cond])

#     sub_plot_from_file(RESULT_FILE_PATH, 1, 1, 1)


#     sub_plot_find_path(RESULT_FILE_PATH_OPT, 1, 1)
#     sub_plot_from_file(RESULT_FILE_PATH, 2, 1)
    sub_plot_from_file(RESULT_FILE_PATH_OPT, 1, 1)

#     plot_amount = 1
#     for i in range(plot_amount):
#         sub_plot_from_file(RESULT_FILE_PATH_OPT, plot_amount, i+1, i+1)
    XX = fill_data_from_file(RESULT_FILE_PATH_OPT)

    bad = 0
    print(XX[-1])
    for i in range(len(XX[-1])-1):
#         print (XX[-1][i])
        if abs(float(XX[-1][i+1])) > 0.1:
#             print('bad')
            bad += 1

    print('failed : ' + str(len(XX[-1])-1) + '/' + str(bad))
    print('fVal: ' + str(calc_func_6(XX[-1])))

    avg_err += abs(calc_func_6(XX[-1]) + dim)
    max_err = max(max_err, abs(calc_func_6(XX[-1])+dim))

    return bad, avg_err, max_err
#     res = sub_plot_from_file(RESULT_FILE_PATH_OPT_CHAOS+"_0", 3, 3, 3)

#     return(res)

def calc_func_6(X):
    dim = len(X) - 1
    res = 0

    for i in range(dim):
        res += float(X[i+1]) * float(X[i+1]) - math.cos(3 * math.pi * float(X[i+1]))

    return res

#f(x) = 10n + Sum(x(i)^2 - 10cos(2pi*x(i)))
def cacl_Rastrigin_func(X):
    dim = len(X) - 1
    res = 10 * dim

    for i in range(dim):
        res += float(X[i+1]) * float(X[i+1]) - 10 * math.cos(2 * math.pi * float(X[i+1]))

    return res







def run_N_dim_func_7(dim, avg_err, max_err):

    random.seed()

    init_cond = '0'
    for i in range(dim):
        init_cond += ', ' + str((random.random()-0.5)*100)

#     init_cond = '0, -2.91390797751, 1.94005208823, -3.9011124444, -1.51972470693, 3.57775812322, -2.89826140281, 4.80608980877, -3.43612785435, 2.35672655962, 4.8499752525, 1.55583452182, 4.01655082987, -4.96777414788, 3.20264640854, -4.00995659717, -4.36198468508, 4.52249834155, 4.54700744199, 0.344288020182, 4.3256256062, 4.69193484689, 3.39881798533, -3.48823300319, -2.2041100248, -2.97365342168, -4.12237968019, -1.82323246241, -4.27959232412, 4.34788259037, -0.694539446176'

#     init_cond = '0, 4'
    print (init_cond)
#0, -2.91390797751, 1.94005208823, -3.9011124444, -1.51972470693, 3.57775812322, -2.89826140281, 4.80608980877, -3.43612785435, 2.35672655962, 4.8499752525, 1.55583452182, 4.01655082987, -4.96777414788, 3.20264640854, -4.00995659717, -4.36198468508, 4.52249834155, 4.54700744199, 0.344288020182, 4.3256256062, 4.69193484689, 3.39881798533, -3.48823300319, -2.2041100248, -2.97365342168, -4.12237968019, -1.82323246241, -4.27959232412, 4.34788259037, -0.694539446176
    subprocess.check_call([WIN_BIN_OPT_FUNC
        , "--steps", "100000"
        , "--step_len", "0.001"
        , "--chaotic_step_len", "0.15"
        , "--alpha", "0.6"
        , "--chaotic_coeff", '500000' #"1500" #800
        , "--chaotic_reduce", "0.2"
        , "--function", "7"
        , "--dim", str(dim)
        , "--init_cond", init_cond])

#     sub_plot_from_file(RESULT_FILE_PATH, 1, 1, 1)


#     sub_plot_find_path(RESULT_FILE_PATH_OPT, 1, 1)
#     sub_plot_from_file(RESULT_FILE_PATH, 2, 1)
#     sub_plot_from_file(RESULT_FILE_PATH_OPT, 1, 1)

#     plot_amount = 1
#     for i in range(plot_amount):
#         sub_plot_from_file(RESULT_FILE_PATH_OPT, plot_amount, i+1, i+1)
    XX = fill_data_from_file(RESULT_FILE_PATH_OPT)

    bad = 0
    print(XX[-1])
    for i in range(len(XX[-1])-1):
#         print (XX[-1][i])
        if abs(float(XX[-1][i+1])-420.968) > 1:
#             print('bad')
            bad += 1

    print('failed : ' + str(len(XX[-1])-1) + '/' + str(bad))

    avg_err += abs(cacl_Schwefel_func(XX[-1]) + (len(XX[-1])-1) * 418.9829)
    max_err = max(max_err, abs(cacl_Schwefel_func(XX[-1])+ (len(XX[-1])-1) * 418.9829))

    return bad, avg_err, max_err

#Schwefel f(x) = Sum(-x(i)*sin(sqrt(abs(x(i)))))   f(x) = -N * 418.9829 x(i) = 420.9687
def cacl_Schwefel_func(X):
    dim = len(X) - 1
    res = 0

    for i in range(dim):
        res += -float(X[i+1]) * math.sin(math.sqrt(abs(float(X[i+1]))))

    return res





def run_N_dim_func_8(dim, avg_err, max_err):

    random.seed()

    init_cond = '0'
    for i in range(dim):
        init_cond += ', ' + str((random.random()-0.5)*100)

#     init_cond = '0, -2.91390797751, 1.94005208823, -3.9011124444, -1.51972470693, 3.57775812322, -2.89826140281, 4.80608980877, -3.43612785435, 2.35672655962, 4.8499752525, 1.55583452182, 4.01655082987, -4.96777414788, 3.20264640854, -4.00995659717, -4.36198468508, 4.52249834155, 4.54700744199, 0.344288020182, 4.3256256062, 4.69193484689, 3.39881798533, -3.48823300319, -2.2041100248, -2.97365342168, -4.12237968019, -1.82323246241, -4.27959232412, 4.34788259037, -0.694539446176'

#     init_cond = '0, 4'
    print (init_cond)
#0, -2.91390797751, 1.94005208823, -3.9011124444, -1.51972470693, 3.57775812322, -2.89826140281, 4.80608980877, -3.43612785435, 2.35672655962, 4.8499752525, 1.55583452182, 4.01655082987, -4.96777414788, 3.20264640854, -4.00995659717, -4.36198468508, 4.52249834155, 4.54700744199, 0.344288020182, 4.3256256062, 4.69193484689, 3.39881798533, -3.48823300319, -2.2041100248, -2.97365342168, -4.12237968019, -1.82323246241, -4.27959232412, 4.34788259037, -0.694539446176
    subprocess.check_call([WIN_BIN_OPT_FUNC
        , "--steps", "100000"
        , "--step_len", "0.001"
        , "--chaotic_step_len", "0.15"
        , "--alpha", "0.2"
        , "--chaotic_coeff", '50000' #"1500" #800
        , "--chaotic_reduce", "0.3"
        , "--function", "8"
        , "--dim", str(dim)
        , "--init_cond", init_cond])

#     sub_plot_from_file(RESULT_FILE_PATH, 1, 1, 1)


#     sub_plot_find_path(RESULT_FILE_PATH_OPT, 1, 1)
#     sub_plot_from_file(RESULT_FILE_PATH, 2, 1)
#     sub_plot_from_file(RESULT_FILE_PATH_OPT, 1, 1)

#     plot_amount = 1
#     for i in range(plot_amount):
#         sub_plot_from_file(RESULT_FILE_PATH_OPT, plot_amount, i+1, i+1)
    XX = fill_data_from_file(RESULT_FILE_PATH_OPT)

    bad = 0
    print(XX[-1])
    for i in range(len(XX[-1])-1):
#         print (XX[-1][i])
        if abs(float(XX[-1][i+1])) > 1:
#             print('bad')
            bad += 1

    print('failed : ' + str(len(XX[-1])-1) + '/' + str(bad))

    avg_err += abs(cacl_Schwefel_func(XX[-1]))
    max_err = max(max_err, abs(cacl_Schwefel_func(XX[-1])))

    return bad, avg_err, max_err

'''
    MAIN
'''

EXPERIMENTS_AMOUNT = 1

res = 0
res_one_test = 0
fails_amount = 0

avg_err = 0
max_err = 0

for i in range(EXPERIMENTS_AMOUNT):
#     res_one_test, avg_err, max_err = run_N_dim(1, avg_err, max_err)
    res_one_test, avg_err, max_err = run_N_dim_func_6(1, avg_err, max_err)
#     res_one_test, avg_err, max_err = run_N_dim_func_7(30, avg_err, max_err)
#     res_one_test, avg_err, max_err = run_N_dim_func_8(30, avg_err, max_err)

    if res_one_test > 0:
        res += 1
        fails_amount += res_one_test
    print('>>>>> TESTING INFO <<<<<<')
    print('tests complete: ' + str(i+1))
    print ('result: ' + str(EXPERIMENTS_AMOUNT) + '/' + str(res))
    print ('fails: ' + str(fails_amount))
    print ('max_err: ' + str(max_err))
    print ('avg_err: ' + str(avg_err/(i+1)))
    print('>>>>> TESTING INFO <<<<<<')

print('---------------- TOTAL RESULT -------------------')
print ('result: ' + str(EXPERIMENTS_AMOUNT) + '/' + str(res))
print ('fails: ' + str(fails_amount))
print ('max_err: ' + str(max_err))
print ('avg_err: ' + str(avg_err/EXPERIMENTS_AMOUNT))




# run_case_1_from_DLL_obj()
#run_case_1_from_lib()
# run_case_1()
#run_case_2()
# run_case_3()
# run_case_4()




