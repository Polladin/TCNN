

#from Dynamic_learning.algorithm.RKF import *

import Dynamic_learning.algorithm.RKF as rkf
import numpy as np
import string

import math
from _elementtree import tostring

step_length = 0.01

NUM_NEURONS = 25
NUM_PATTERNS = 4

LINE_AMOUNT = 5

NUM_STEPS = 100

intern_state = [[[0]*4]*NUM_NEURONS]*NUM_STEPS #np.array([])
I = [] #[0] * NUM_NEURONS
W = [[0]*NUM_NEURONS]*NUM_NEURONS #np.array([])

patterns = [] #np.array([])


def read_in_pattern():
    global I
    pattern_in_file = open("patterns.in", "r")

    arr = []
    arr.append([])

    for line in pattern_in_file:
#         print (line)
        for num in line.split():
            if int(num) == 0:
                arr[-1].append(-1)
            else:
                arr[-1].append(int(num))

    I = arr[0]
#     print (I)

def read_patterns():
    global patterns

    arr = []
    arr.append([])

    idx = 0

    patterns_file = open("patterns.in", "r")

    for line in patterns_file:
#         print (line)
        if len(line.split()):
            for num in line.split():
                if int(num) == 0:
                    arr[-1].append(-1)
                else:
                    arr[-1].append(int(num))

            idx = idx + 1
            if idx == LINE_AMOUNT:
                patterns.append(arr[-1])
                arr = []
                arr.append([])
                idx = 0

#     for i in range(len(arr)):
#         print(arr[i])

#     for i in range(len(patterns)):
#         print ("New pattern " + str(i))
#         print (patterns[i])



def func_to_calc_sigmoid(u):
#     print("exp func : " +  str(u))
#     print(2 / (1 + math.exp(-u / step_length)) - 1)
    return 2 / (1 + math.exp(-u / step_length)) - 1


def norm(neuron):
    sum_w = 0

    for i in range(NUM_NEURONS):
        if i != neuron:
            sum_w = sum_w + W[neuron][i] * W[neuron][i]

    return math.sqrt(sum_w)


def learning():
    global W

    for i in range(NUM_NEURONS):
        for j in range(NUM_NEURONS):
            for pattern_num in range(NUM_PATTERNS):
                W[i][j] = W[i][j] + patterns[pattern_num][i] * patterns[pattern_num][j]

    for i in range(NUM_NEURONS):
        norm_w = norm(i)
        for j in range(NUM_NEURONS):
            W[i][j] = W[i][j] / norm_w


def calc_Dxy(step):
    sum_Dxy = 0

    for i in range(NUM_NEURONS):
        sum_Dxy = sum_Dxy + intern_state[step][i][1] * intern_state[step][i][2]

    return sum_Dxy

def calc_S(step, neuron):
    sum_S = 0

#     print("exp func : " +  str(intern_state[step][j][2]))

    for j in range(NUM_NEURONS):
        if neuron != j:
            sum_S = sum_S + W[neuron][j] * func_to_calc_sigmoid(intern_state[step][j][2])

    print(sum_S)
    return sum_S



def run():
    global intern_state
#     print(W)

#     print(intern_state[0][0])

#     np.resize(patterns, (NUM_PATTERNS,NUM_NEURONS))
#     np.resize(I, (NUM_NEURONS))
#     np.resize(intern_state, (NUM_STEPS, NUM_NEURONS, 4))
#     np.resize(W, (NUM_NEURONS,NUM_NEURONS))

    read_patterns()
    learning()
    read_in_pattern()

    for sstep in range(NUM_STEPS-1):
        for i in range(NUM_NEURONS):
            print(intern_state[sstep])
            intern_state[sstep+1][i] = rkf.solve_one_step(intern_state[sstep][i], calc_S(sstep, i), I[i], calc_Dxy(sstep))


    print("Done")


run()