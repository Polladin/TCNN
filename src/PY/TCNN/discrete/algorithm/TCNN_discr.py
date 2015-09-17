

import math
import random
import matplotlib.pyplot as plt

eps = 1
k = 1
alpha = 0.001 #0.005
I0 = 0.65
beta = 0.00005

STEPS_AMOUNT = 120000
dimention = 2

MULT_COEFF = 4

dF_plot = [[0]*STEPS_AMOUNT for i in range(dimention)]


def run():



    X = [[0]*STEPS_AMOUNT for i in range(dimention)]
    Y = [[0]*STEPS_AMOUNT for i in range(dimention)]
    Z = [0] * STEPS_AMOUNT

#     for i in range(dimention):
#         X[i][0] = random.random()
#         print(X[i][0])

    for i in range(dimention):
        Y[i][0] = (random.random() - 0.5 )

    Z[0] = 2

    calc(X,Y,Z, STEPS_AMOUNT-1, dimention)



    for i in range(dimention):
        print(scale_X(X[i][-2]))
        plt.subplot(dimention*2,1,i+1)
        plt.plot(X[i], '.')

    plt.subplot(dimention*2,1,3)
    plt.plot(dF_plot[0], '.')
    plt.subplot(dimention*2,1,4)
    plt.plot(dF_plot[1], '.')
    plt.show()

#     plt.subplot(2,1,1)
#     plt.plot(X[-1], '.')
#     plt.subplot(2,1,2)
#     plt.plot(Y[-1], '.')

#     plt.show()

#     plt.plot(column(X,0),column(X,1))

def scale_X(x):
    return (x-0.5)*MULT_COEFF

def fVal(X, step, dimention):
    res = 10 * dimention

    offset = -1

    for i in range(dimention):
        res += (scale_X(X[i][step])-offset) * (scale_X(X[i][step])-offset) - 10 * math.cos(2 * math.pi * (scale_X(X[i][step])-offset))

#     res = 0
#     for i in range(dimention):
#         res += (scale_X(X[i][step])-1) * (scale_X(X[i][step])-1)

    return res

def vectorSummOneDim(X, i, step, h):
    tmp_X = X
    tmp_X[i][step] += h

    return tmp_X

def dF(X,i,step, dimention, h):
#     global dF_plot
#     df = 2*(scale_X(X[i][step]))+ 20 * math.pi * math.sin(2*math.pi*(scale_X(X[i][step])))
#     return 2*scale_X(X[i][step])+ 20 * math.pi * math.sin(2*math.pi*scale_X(X[i][step]))

#     h = scale_X(h)
    df = (  -137.0 * fVal(X,step,dimention) + 300.0 * fVal(vectorSummOneDim(X,i,step,h),step,dimention) - 300.0 * fVal(vectorSummOneDim(X,i,step,2.0*h),step,dimention) \
              + 200.0 * fVal(vectorSummOneDim(X,i,step,3.0*h),step,dimention) - 75.0 * fVal(vectorSummOneDim(X,i,step,4.0*h),step,dimention) + 12.0 * fVal(vectorSummOneDim(X,i,step,5.0*h),step,dimention) \
           ) / (60 * h)

#     df = 2*(scale_X(X[i][step])-2)

    dF_plot[i][step] = df

    return df


def calc_x(X,Y,step, dimention):

    for i in range(dimention):
        X[i][step] = 1 / (1 + math.exp(-Y[i][step]/eps))


def calc_y(X,Y,Z, step, dimention):

    for i in range(dimention):
        Y[i][step+1] = k * Y[i][step] - alpha * dF(X,i,step, dimention, 0.0001) - Z[step] * (X[i][step] - I0)


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


