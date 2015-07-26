'''
Created on Jul 26, 2015

@author: alex
'''

import matplotlib.pyplot as plt

def column(matrix, i):
    return [row[i] for row in matrix]


def plot_all(XX):    
    if len(XX) == 0:
        print ("No input data")
        return "ERR: no_data"
    
    if len(XX[0]) == 1:
        print ("Presented only one dimension data")
        return "ERR: only one dimension data"

    ''' else len(XX) > 1 '''
    amount_subplots = len(XX[0]) - 1;
    
    for i in range(amount_subplots):
        plt.subplot(amount_subplots, 1, i+1)
        plt.plot(column(XX,0),column(XX,i+1))
        plt.xlabel("Axes - " + str(i+1))
    
    plt.show();
    return "SUCCESS"
    