
import numpy as np

step_length = 0.01

tau = 0.1
k   = 10.0
D   = 200
b   = 2.6

step_length = 0.01

res = np.array([])

def resize_res(NUM_NEURONS):
    np.resize(res, (NUM_NEURONS, 4))


def solve_one_step(X, S, I, Dxy):
    tmp_X = X[:]

#     print("solve_one with S:" + str(S) + " I:" + str(I) + " Dxy:" + str(Dxy))
#     print(X)

    K1 = calcFunc(tmp_X, S, I, Dxy);
    K2 = calcFunc(calc_K_by_h_div_2(tmp_X,K1,step_length), S, I, Dxy);
    K3 = calcFunc(calc_K_by_h_div_2(tmp_X,K2,step_length), S, I, Dxy);
    K4 = calcFunc(calc_K_by_h(tmp_X,K1,step_length), S, I, Dxy);

    tmp_X = calc_new_X(X, K1, K2, K3, K4, step_length);

    return tmp_X



def calc_K_by_h(X, K, h):
    tmp = [0] * len(X)

    for i in range(len(X)):
        tmp[i] = X[i] + K[i] * h;

    return tmp;


def calc_K_by_h_div_2(X, K, h):
    return calc_K_by_h(X, K, h/2.0)


def calcFunc(X, S, I, Dxy):
    tmp_X = X[:]
    tmp_X[0] = 1
    tmp_X[1] = (-k * X[1] + k * X[2]) / tau
    tmp_X[2] = (-X[2] + X[3] * X[1] + S + I) / tau
    tmp_X[3] = (-b * X[3] - Dxy + b * D) / tau

    return tmp_X

def calc_new_X(X, K1, K2, K3, K4, step_length):
    tmp = [0] * len(X)

    tmp[0] = X[0] + step_length;

    for i in range(len(X)):
        tmp[i] = X[i] + step_length * (K1[i] + 2.0*K2[i] + 2.0*K3[i] + K4[i]) / 6.0

    return tmp

