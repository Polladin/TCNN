

import math

eps = 0.001
k = 0.1
alpha = 0.2
I0 = 0.6
beta = 0.0001

def dF(X,i,step):
    return 2*X[i][step]

def calc_x(X,Y,step):

    for i in range(len(X)):
        X[i][step] = 1 / (1 + math.exp(-Y[i][step]/eps))


def calc_y(X,Y,Z, step):

    for i in range(len(Y)):
        Y[i][step+1] = k * Y[i][step] - alpha * dF(X,i,step) - Z[step] * (X[i][step] - I0)


def calc_z(Z, step):
    Z[step+1] = Z[step] * (1 - beta)



def one_step(X,Y,Z, step):
    calc_x(X, Y, step)
    calc_y(X, Y, Z, step)
    calc_z(Z, step)


def calc(X,Y,Z):
    
    for step in range(STEPS_AMOUNT):
        


