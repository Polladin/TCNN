

import math
import random
import matplotlib.pyplot as plt

eps = 0.004
k = 1
alpha = 0.000005
I0 = 0.65
beta = 0.0001

STEPS_AMOUNT = 12000
dimention = 2

dF_plot = [[0]*STEPS_AMOUNT for i in range(dimention)]


def run():



    X = [[0]*STEPS_AMOUNT for i in range(dimention)]
    Y = [[0]*STEPS_AMOUNT for i in range(dimention)]
    Z = [0] * STEPS_AMOUNT

#     for i in range(dimention):
#         X[i][0] = random.random()
#         print(X[i][0])

    Y[0][0] = 0.005
    Y[1][0] = -0.005

    Z[0] =  0.1


    calc(X,Y,Z, STEPS_AMOUNT-1, dimention)



    for i in range(dimention):
        print(scale_X(X[i][-2]))
        plt.subplot(dimention*2,1,i+1)
        plt.plot(X[i], '.')

        plt.subplot(dimention*2,1,3)
        plt.plot(dF_plot[0], '.')
        plt.subplot(dimention*2,1,4)
        plt.plot(dF_plot[1], '.')
#     plt.subplot(2,1,1)
#     plt.plot(X[-1], '.')
#     plt.subplot(2,1,2)
#     plt.plot(Y[-1], '.')
    plt.show()
#     plt.plot(column(X,0),column(X,1))

def scale_X(x):
    return (x-0.5)*10.24

def dF(X,i,step):
    global dF_plot
    dF_plot[i][step] = 2*(scale_X(X[i][step])-1)+ 20 * math.pi * math.sin(2*math.pi*(scale_X(X[i][step])-1))
    return 2*scale_X(X[i][step])+ 20 * math.pi * math.sin(2*math.pi*scale_X(X[i][step]))

def calc_x(X,Y,step, dimention):

    for i in range(dimention):
        X[i][step] = 1 / (1 + math.exp(-Y[i][step]/eps))


def calc_y(X,Y,Z, step, dimention):

    for i in range(dimention):
        Y[i][step+1] = k * Y[i][step] - alpha * dF(X,i,step) - Z[step] * (X[i][step] - I0)


def calc_z(Z, step):
    Z[step+1] = Z[step] * (1 - beta)



def one_step(X,Y,Z, step, dimention):
    calc_x(X, Y, step, dimention)
    calc_y(X, Y, Z, step, dimention)
    calc_z(Z, step)


def calc(X,Y,Z, step_amount, dimention):

    for step in range(step_amount):
        one_step(X,Y,Z,step, dimention)



def column(matrix, i):
    return [row[i] for row in matrix]





run()


