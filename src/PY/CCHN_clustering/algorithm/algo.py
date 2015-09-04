
import random

import matplotlib.pyplot as plt

beta_var = 1    #random(0,1)
ro = 0      #random(0,1)
A = 0       #random(0,1)

DATA_IN_CLUSTER = 10
CLUSTERS_AMOUNT = 4

NEURONS_AMOUNT = DATA_IN_CLUSTER * CLUSTERS_AMOUNT

DIMENTION = 2
STEPS_AMOUNT = 100

U = [[0]*CLUSTERS_AMOUNT for i in range(NEURONS_AMOUNT)]
V = [[0]*CLUSTERS_AMOUNT for i in range(NEURONS_AMOUNT)]

C = [[0]*DIMENTION for i in range(CLUSTERS_AMOUNT)]

X = [] #[[0]*DIMENTION for i in range(NEURONS_AMOUNT)]

O = [0]*CLUSTERS_AMOUNT



def init_X():
    global X

    offset_X = [-1, 1, -1, 1]
    offset_Y = [-1, -1, 1, 1]

    for k in range(CLUSTERS_AMOUNT):
        for i in range(DATA_IN_CLUSTER):
            X[i+k*DATA_IN_CLUSTER] = [random.random() + offset_X[k], random.random() + offset_Y[k]]


def init_A_beta_ro():
    global A
    global ro

    A = random.random()
    ro = random.random()

def init_U_V(u, v):

    for i in range(NEURONS_AMOUNT):
        cluster_set = i % CLUSTERS_AMOUNT #random.randrange(0, CLUSTERS_AMOUNT)

        u[i][cluster_set] = 1
        v[i][cluster_set] = 1
        for j in range(CLUSTERS_AMOUNT):
            if j != cluster_set:
                u[i][j] = -1
                v[i][j] = 0


def calc_sum_v_k(clustrer_num, dimention):
    sum_v_k = 0

    for i in range(NEURONS_AMOUNT):
        sum_v_k += V[i][clustrer_num] * X[i][dimention]

    return sum_v_k


def calc_sum_v(clustrer_num):
    sum_v = 0

    for i in range(NEURONS_AMOUNT):
        sum_v += V[i][clustrer_num]

    return sum_v

def calc_centers():
    global C

    for k in range(CLUSTERS_AMOUNT):
        for d in range(DIMENTION):
            C[k][d] = calc_sum_v_k(k,d) / calc_sum_v(k)

def dist_c(neuron, cluster):
    dist_cluster = 0

    for d in range(DIMENTION):
        dist_cluster += (X[neuron][d] - C[cluster][d]) * (X[neuron][d] - C[cluster][d])

    dist_cluster -= NEURONS_AMOUNT/2

    return dist_cluster


def column(matrix, i):
    return [row[i] for row in matrix]

def plot_input():

    plt.plot(column(X,0), column(X,1), 'ro')
    plt.show()


def color_plot():
    cluster_color = ['ro', 'go', 'bo', 'mo']

    for i in range(NEURONS_AMOUNT):
        for k in range(CLUSTERS_AMOUNT):
            if V[i][k] == 1:
                plt.plot(X[i][0], X[i][1], cluster_color[k])

    plt.show()


def read_X():
    global X

    pattern_in_file = open("SampleSimple5.txt", "r")

    arr = []
    arr.append([])

    for line in pattern_in_file:
        arr = []
        for num in line.split():
            arr.append(float(num))
        X.append(arr)


def run():
    global U
    global X
    global V
    global C
    global O
    global CLUSTERS_AMOUNT
    global DATA_IN_CLUSTER
    global NEURONS_AMOUNT
    global DIMENTION

    random.seed()

    X = []

    read_X()

    DATA_IN_CLUSTER = len(X)
    CLUSTERS_AMOUNT = 4

    NEURONS_AMOUNT = DATA_IN_CLUSTER #* CLUSTERS_AMOUNT

    DIMENTION = 2

    U = [[0]*CLUSTERS_AMOUNT for i in range(NEURONS_AMOUNT)]
    V = [[0]*CLUSTERS_AMOUNT for i in range(NEURONS_AMOUNT)]

    C = [[0]*DIMENTION for i in range(CLUSTERS_AMOUNT)]

    O = [0]*CLUSTERS_AMOUNT

#     init_X()

#     plot_input()

    init_A_beta_ro()
    init_U_V(U,V)

#     print(U)
#     print(V)

    beta_var = 1
#     ro = 0.999
    ro = 0.990051887438

    print("RO:")
    print(ro)

    for k in range(CLUSTERS_AMOUNT):
        O[k] =random.random()

    STEPS_AMOUNT = 100
    #Main Loop
    for sstep in range (STEPS_AMOUNT):

        calc_centers()

        for i in range(NEURONS_AMOUNT):
            for k in range(CLUSTERS_AMOUNT):
                U[i][k] = -2 * A * dist_c(i, k) + beta_var * O[k]
                O[k] = 4 * O[k] * (1 - O[k])


            for k in range(CLUSTERS_AMOUNT):
                if U[i][k] == max(U[i]):
                    V[i][k] = 1
                else:
                    V[i][k] = 0

        beta_var = beta_var * (1 - ro)


#     print (V)
#     print(U)

    for i in range(len(V)):
        print('i = ' + str(i) + ' val = ' + str(V[i]))

    color_plot()




run()