'''
Created on Jul 26, 2015

@author: alex
'''

import matplotlib.pyplot as plt

def column(matrix, i):
    return [row[i] for row in matrix]

def check_min_2_colums(XX):
    if len(XX) == 0:
        print ("No input data")
        return [True, "ERR: no_data"]
    
    if len(XX[0]) == 1:
        print ("Presented only one dimension data")
        return [True, "ERR: only one dimension data"]
    
    return [False, "SUCCESS"]


def plot_all(XX):    
    [err, res] = check_min_2_colums(XX)
    
    if err:
        return res
    
    ''' else len(XX) > 1 '''
    amount_subplots = len(XX[0]) - 1;
    
    for i in range(amount_subplots):
        plt.subplot(amount_subplots, 1, i+1)
        plt.plot(column(XX,0),column(XX,i+1))
        plt.xlabel("Axes - " + str(i+1))
    
    plt.show();
    return res



def subplot(XX, amount_subplots, index, col = 1):
    [err, res] = check_min_2_colums(XX)
    
    if err:
        return res
    
    plt.subplot(amount_subplots, 1, index)
    plt.plot(column(XX,0),column(XX,col))
    plt.xlabel("Axes - " + str(index))
    
    return res
    
    