

#from Dynamic_learning.algorithm.RKF import *


import M_ACNN.algorithm.RKF as rkf

import math

import matplotlib.pyplot as plt
import matplotlib.patches as patches

step_length = 0.001


NUM_NEURONS = 100 #25
NUM_PATTERNS = 4

LINE_AMOUNT = 10 #5

NUM_STEPS = 5000

intern_state = [[[0]*4 for i in range(NUM_NEURONS)] for j in range(NUM_STEPS)]
I = []
W = [[0]*NUM_NEURONS for i in range(NUM_NEURONS)]

patterns = [] #np.array([])


def read_in_pattern():
    global I
    pattern_in_file = open("input_pattern.in", "r")

    arr = []
    arr.append([])

    for line in pattern_in_file:
        for num in line.split():
            if int(num) == 0:
                arr[-1].append(0)
            else:
                arr[-1].append(int(num))

    I = arr[0]

    idx = 0
    str_out = ''

    for i in range(NUM_NEURONS):
        str_out += str(I[i])
        idx += 1

        if idx == LINE_AMOUNT:
            print (str_out)
            idx = 0
            str_out=''

    print(str_out)

def read_patterns():
    global patterns

    arr = []
    arr.append([])

    idx = 0

    patterns_file = open("patterns_2.in", "r")

    for line in patterns_file:
#         print (line)
        if len(line.split()):
            for num in line.split():
                if int(num) == 0:
                    arr[-1].append(0)
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
            if i != j:
                for pattern_num in range(NUM_PATTERNS):
#                     W[i][j] += (2*patterns[pattern_num][i]-1) * (2*patterns[pattern_num][j]-1)
                    W[i][j] += patterns[pattern_num][i] * patterns[pattern_num][j]
#                     print(W)
#                     print('i='+str(i) + ' j=' + str(j) + ' W=' + str(W[i][j]) + ' pattern:'+str(patterns[pattern_num][i]) + '/' + str(patterns[pattern_num][j]))


#     for i in range(NUM_NEURONS):
# #         norm_w = norm(i)
#         for j in range(NUM_NEURONS):
#             W[i][j] = W[i][j] / NUM_NEURONS #NUM_PATTERNS #norm_w


def calc_Dxy(step):
    sum_Dxy = 0

    for i in range(NUM_NEURONS):
        sum_Dxy = sum_Dxy + intern_state[step][i][1] * intern_state[step][i][3]

    return sum_Dxy

def calc_S(step, neuron):
    sum_S = 0

#     print("exp func : " +  str(intern_state[step][j][2]))

    for j in range(NUM_NEURONS):
        sum_S += W[neuron][j] * intern_state[step][j][3] #rkf.func_to_calc_sigmoid(intern_state[step][j][3])

#     print(sum_S)
    return sum_S


def get_out(out_state):
    arr = []

    for i in range(NUM_NEURONS):
        arr.append(out_state[i][3])
#         arr.append(int(round(rkf.func_to_calc_sigmoid(out_state[i][2]))))

    return arr

def print_out(out_state):

    st_outr = ''
    idx = 0

    for i in range(NUM_NEURONS):
        st_outr += str(int((out_state[i][3])))
        idx += 1

        if idx == LINE_AMOUNT:
            print(st_outr)
            st_outr=''
            idx = 0

    print(st_outr)


def show_picture(Out_pattern, fig, num_row, num_col, plt_idx):

    ax1 = fig.add_subplot(num_row,num_col,plt_idx, aspect='equal')
    plt.axis('off')

    for i in range(NUM_NEURONS):
        if Out_pattern[i] == 1:
            ax1.add_patch(patches.Rectangle((LINE_AMOUNT*10 - (i % LINE_AMOUNT)*10,(LINE_AMOUNT*10 - (i / LINE_AMOUNT)*10)), 10, 10))



    ax1.add_patch(patches.Rectangle((10-1,10-1),LINE_AMOUNT*10+1,LINE_AMOUNT*10+1, fill=False))

    plt.axis([10-1.1,LINE_AMOUNT*10+10+1.1,10-1.1,LINE_AMOUNT*10+10+1.1])

    #fig1.savefig('rect1.png', dpi=90, bbox_inches='tight')






'''
#===============================================================================
#                 MAIN FUNCTION
#===============================================================================
'''
def run():
    global intern_state

    read_patterns()
    print(W)
    learning()
    print(W)
    read_in_pattern()

#     show_picture(I)
    fig1 = plt.figure()
    idx = 1
    show_picture(I, fig1, 10, 10, idx)
    idx += 1

    print(W)
    for i in range(len(W[0])):
        print(W[i])

#     show_picture(patterns[0], fig1, 1, 4, 1)
#     show_picture(patterns[1], fig1, 1, 4, 2)
#     show_picture(patterns[2], fig1, 1, 4, 3)
#     show_picture(patterns[3], fig1, 1, 4, 4)
#     plt.show()

    for i in range(NUM_NEURONS):
        intern_state[0][i][3] = I[i]


#     print(W)

    N_global = 0
    E_global = 0

    for sstep in range(NUM_STEPS-1):
        for i in range(NUM_NEURONS):
            #print(intern_state[sstep])
#             print("Summ = " + str(calc_S(sstep, i)))
            intern_state[sstep+1][i] = rkf.solve_one_step(intern_state[sstep][i], calc_S(sstep, i), I[i]
                                                          , calc_Dxy(sstep), step_length, N_global, E_global)
        N_global = intern_state[sstep+1][NUM_NEURONS-1][1]
        E_global = intern_state[sstep+1][NUM_NEURONS-1][2]

        if sstep % 100 == 0:
            print("State on step=" + str(sstep))
            print_out(intern_state[sstep+1])

#             if sstep > (NUM_STEPS - 4900):
#                 show_picture(get_out(intern_state[sstep+1]), fig1, 5, 10, idx)
#                 idx += 1

    print("Done")

#     show_picture(get_out(intern_state[-2]), fig1, 5, 10, idx)
#     plt.show()

    arr_val = []
    arr_time = []
    arr_time_1 = []
    arr_time_2 = []
    for i in range(NUM_STEPS):
        arr_time.append(intern_state[i][0][0])
        arr_val.append(intern_state[i][0][3])
        arr_time_1.append(intern_state[i][0][2])
        arr_time_2.append(intern_state[i][0][1])

    print(arr_time)
    print(arr_val)
    print(arr_time_1)
    print(arr_time_2)


    for i in range(90):
        show_picture(get_out(intern_state[NUM_STEPS-100+i]), fig1, 10, 10, idx)
        idx = idx + 1

    print_out(intern_state[-2])

#     plt.figure(2)
#
#     plt.plot(arr_time, arr_val)
    plt.show()



run()