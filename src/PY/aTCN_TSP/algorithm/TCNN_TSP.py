
import calculations as nn_calc
import aTCNN_dynamic as atcnn_dyn

import numpy as np
np.set_printoptions(threshold=np.nan)

import matplotlib.pyplot as plt

import math
import random
from datetime import datetime


"""
    Generate distance between cities
"""
def gen_city_dist(n,m):

    N = n * m

    D = np.zeros((N,N))

    for i in range(N):
        for j in range(N):
            D[i][j] = math.sqrt( math.pow(abs((i % m) - (j % m)),2) +  math.pow(abs((i / m) - (j / m)),2))

    return D

def test_gen_city_dist():

    Dist = gen_city_dist(10,10)
    print Dist


def tests():
    test_gen_city_dist()




"""
    Main function
"""
def main():

    col = 3
    row = 2
    Ncity = col * row

    random.seed(datetime.now())

    Y = (np.random.rand(Ncity,Ncity) - 0.5) * 2
    print Y
    X = np.zeros((Ncity,Ncity))
    D = gen_city_dist(row,col)

    Z = 1000

    N = 30000
    E = np.zeros((N))

    #Chaotic initial conditions
    dt_chaotic = 0.1
    Chaotic = np.random.rand(Ncity * Ncity, 3) - 0.5

    dt_nn_output = 0.1

    X_arr = []
    C_arr = []
    Y_arr = []

    for i in range(N):
        #chaotic calc
        Chaotic = atcnn_dyn.next_step_chaotic(Chaotic, dt_chaotic)

        tmp_arr = np.zeros((len(Chaotic), len(Chaotic[0])))
        for k in range(len(Chaotic)):
            for j in range(len(Chaotic[0])):
                tmp_arr[k][j] = Chaotic[k][j]

        C_arr.append(tmp_arr)

        X = nn_calc.neurons_output_calc_cont(Y, 1.0/25.0)
        X_arr.append(X)
        #                                                I0, k,   ,alpha, beta,   W1,   W2
#         [Y,Z] = nn_calc.network_output_calc(X, Y, Z, D, 0.5, 0.9, 0.015, 0.00005, 7.0, 2.0)
        #                                          X, Y, Z, D, Chaotic, k, alpha, beta, W1, W2, dt

        W1 = 4.0
        W2 = 0.5
        [Y,Z] = nn_calc.network_output_chaotic_calc(X, Y, Z, D, Chaotic, 0.45, 0.0001, W1, W2, dt_nn_output)
        Y_arr.append(Y);

        E[i] = nn_calc.energy_calc(X, D, W1, W2)

    #rearranging list to array
    out = np.zeros((len(C_arr),len(C_arr[0]), len(C_arr[0][0])))
    for i in range(len(C_arr)):
        for j in range(len(C_arr[0])):
            for k in range(len(C_arr[0][0])):
                out[i][j][k] = C_arr[i][j][k]

#     plt.plot(out[:,0:5,2])
#     plt.show()

    print "Plot"
    plt.plot(E)
    plt.show()

    print "E = ", E[-1]
    print X

    for i in range(Ncity):
        for j in range(Ncity):
            if X[i][j] > 0.5:
                print j+1, ", ", i+1


    print_y = np.zeros((Ncity,Ncity,N))
    for i in range(N):
        for j in range(Ncity):
            for k in range(Ncity):
                print_y[j][k][i] = X_arr[i][j][k]

#     print "Y_arr = ", print_y


    for j in range(Ncity):
        for k in range(Ncity):
            plt.subplot(Ncity,Ncity,j*Ncity + k+1)
            plt.plot(print_y[j][k])

    plt.show()

'''
    Run programm
'''


print "Run"
main()



