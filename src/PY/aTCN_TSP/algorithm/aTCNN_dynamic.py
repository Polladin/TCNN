
import matplotlib.pyplot as plt

from scipy.integrate import ode
import numpy as np


def chaotic_diff_function(t, y, *f_args):
    return [y[1], y[2], -0.44*y[2] - 2.0*y[1] + (y[0]*y[0] - 1.0)]



def next_step_chaotic(X, dt):

    ode_func = ode(chaotic_diff_function).set_integrator('vode', method='bdf')

    for i in range(len(X)):
        ode_func.set_initial_value(X[i], 0)
        assert ode_func.successful()

        ode_func.integrate(dt)
        X[i] = ode_func.y

    return X





"""
    Test functions
"""
def test_chaotic_dyn(num_chaotic):

    X = np.random.rand(num_chaotic,3) - 0.5
    t = 0;
    dt = 0.1
    t_end = 2000
    X_arr = []

    while t < t_end:

        tmp_arr = np.zeros((len(X), len(X[0])))
        for i in range(len(X)):
            for j in range(len(X[0])):
                tmp_arr[i][j] = X[i][j]

        X_arr.append(tmp_arr)

        X = next_step_chaotic(X, dt)
        t += dt

    #rearranging list to array
    out = np.zeros((len(X_arr),len(X_arr[0]), len(X_arr[0][0])))
    for i in range(len(X_arr)):
        for j in range(len(X_arr[0])):
            for k in range(len(X_arr[0][0])):
                out[i][j][k] = X_arr[i][j][k]

#     print "Out"
#     print out[:,1,2]

    #clalc sum of chaotic signals
    sum_signal = np.zeros((len(out)))
    for i in range(num_chaotic):
        sum_signal += out[:,i,2]


#     plt.plot(out[:,0,2])
    plt.plot(sum_signal)
    plt.show()


"""
    Run programm
"""

# calc_diff_function()
# test_chaotic_dyn(4)











"""
    Not used functions
"""

def calc_diff_function():
    r = ode(chaotic_diff_function).set_integrator('vode', method='bdf')
    r.set_initial_value([0.5, 0, -0.4], 0)

    dt = 0.1
    t_end = 1000;

    t_array = []
    y_array = []

    while r.successful() and r.t < t_end:
        r.integrate(r.t+dt)
#         print r.t, ", ", r.y
        t_array.append(r.t)
        y_array.append(r.y)

    out = np.zeros((len(y_array),len(y_array[0])))
    for i in range(len(y_array)):
        for j in range(len(y_array[0])):
            out[i][j] = y_array[i][j]

    plt.plot(t_array, out[:, 2])
    plt.show()
