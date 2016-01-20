from scipy.integrate import ode

import numpy as np
import matplotlib.pyplot as plt




def test():
    #test_neurons_output_calc_cont()
    test_network_output_calc()



"""
    Calculate the Energy
"""
def energy_calc(X, D, W1, W2):

    [XdimSize, YdimSize] = X.shape

    Xrow = 0
    Xcol = 0
    Dist = 0

    #calc Xrow
    for i in range(XdimSize):
        sumX = 0

        for j in range(YdimSize):
            sumX += X[i][j]

        Xrow += (sumX - 1) * (sumX - 1)

    #calc Xcol
    for j in range(YdimSize):
        sumX = 0

        for i in range(XdimSize):
            sumX += X[i][j]

        Xcol += (sumX - 1) * (sumX - 1)

    #calc Dist
    N = len(X)

    for i in range(XdimSize):
        for j in range(YdimSize):
            for k in range (N):
                Dist += (X[k][(j+1)%(N-1)] + X[k][(j-1)%(N-1)]) * X[i][j] * D[i][k]

    #calc energy
    E = W1/2.0 * (Xrow + Xcol) + W2/2.0 * Dist

    return E


"""
        Calculate Neurons Output as continuous output
"""
def neurons_output_calc_cont(Y, eps):

    X = 1 / (1 + np.exp(-Y / eps))

    return X

#test
def test_neurons_output_calc_cont():

    Y = np.arange(-1,1,0.01)
    eps = 1.0/25.0
    X = neurons_output_calc_cont(Y, eps)
    print (X)
    plt.plot(Y, X)
    plt.show()



"""
        Calculate Network Output
"""
def calc_sum_Xl(X, i,j):
    sum_Xl = 0

    for l in range(len(X)):
        if l != j:
            sum_Xl += X[i][l]

    return sum_Xl


def calc_sum_Xk(X, i,j):
    sum_Xk = 0

    for k in range(len(X)):
        if k != i:
            sum_Xk += X[k][j]

    return sum_Xk


def calc_sum_D_plus_1(X,D,i,j):
    sum_D_plus_1 = 0
    N = len(X)

    for k in range(N):
        if k != i:
            sum_D_plus_1 += D[i][k] * X[k][(j+1)%(N-1)]

    return sum_D_plus_1


def calc_sum_D_minus_1(X,D,i,j):
    sum_D_minus_1 = 0
    N = len(X)

    for k in range(N):
        if k != i:
            sum_D_minus_1 += D[i][k] * X[k][(j-1)%(N-1)]

    return sum_D_minus_1


#----------------------------- Calculate Network Output -----------------------------------------
def network_output_calc(X, Y, Z, D, I0, k, alpha, beta, W1, W2):

    [XdimSize, YdimSize] = Y.shape
    Yout = np.zeros(Y.shape)

    for i in range(XdimSize):
        for j in range(YdimSize):
            Yout[i][j] = k * Y[i][j] - Z * (X[i][j] - I0)                                                       \
                            + alpha * (                                                                         \
                                       - W1 * (calc_sum_Xl(X,i,j) + calc_sum_Xk(X,i,j))                         \
                                       - W2 * (calc_sum_D_plus_1(X,D,i,j) + calc_sum_D_minus_1(X,D,i,j))        \
                                       + W1                                                                     \
                                       )
            Z = (1 - beta) * Z



    return Yout, Z


#--------------------- Calculate Output as analog function  -----------------------------------------
def nn_output_diff_function(t, y, X, i, j, W1, W2, alpha, D, Z, chaotic):

    tmp =  - Z * (chaotic)                                                      \
                            + alpha * (                                                                         \
                                       - W1 * (calc_sum_Xl(X,i,j) + calc_sum_Xk(X,i,j))                         \
                                       - W2 * (calc_sum_D_plus_1(X,D,i,j) + calc_sum_D_minus_1(X,D,i,j))        \
                                       + W1                                                                     \
                                       )
#     print "chaotic = ", - Z * (chaotic)
#     print "W1 part = ", - W1 * (calc_sum_Xl(X,i,j) + calc_sum_Xk(X,i,j))
#     print "W2 part = ", - W2 * (calc_sum_D_plus_1(X,D,i,j) + calc_sum_D_minus_1(X,D,i,j))

    return tmp


def network_output_chaotic_calc(X, Y, Z, D, Chaotic, alpha, beta, W1, W2, dt):

    [XdimSize, YdimSize] = Y.shape
    Yout = np.zeros(Y.shape)

    ode_func = ode(nn_output_diff_function).set_integrator('vode', method='bdf')


    for i in range(XdimSize):
        for j in range(YdimSize):
            ode_func.set_initial_value(Y[i][j], 0).set_f_params(X, i, j, W1, W2, alpha, D, Z, Chaotic[i*YdimSize + j,2])
            assert ode_func.successful()

            ode_func.integrate(dt)
            Yout[i][j] = ode_func.y[0]

    Z = (1 - beta) * Z

    return Yout, Z



#test
def test_network_output_calc():

    Y = np.zeros((5,5))
    X = np.random.rand(5,5)
    D = np.random.rand(5,5)
    Z = 1

    print "X = ", X
    print "D = ", D

    print (Y.shape)
    [Xsize, Ysize] = Y.shape
    print "Xsize = ", Xsize
    print "Ysize = ", Ysize

    [Y,Z] = network_output_calc(X, Y, Z, D, 0.65, 0.9, 0.015, 0.00005, 1, 1.0/3.0)
    E = energy_calc(X, D, 1, 1.0/3.0)

    print "Y = "
    print Y
    print "E = ", E






"""
    Run Tests
"""
#test()


