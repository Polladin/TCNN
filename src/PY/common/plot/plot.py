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


'''
Fill array with data from external file
'''
def fill_data_from_file(file_name):
    XX = []

    f = open(file_name, 'r')

    for line in f:
        XX.append([])
        for num in line.split():
            XX[-1].append(num)

    return XX

'''
Plot All data from file
'''
def plot_from_file(result_file_name):
    XX = fill_data_from_file(result_file_name)

    return plot_all(XX)


'''
Plot data on one the part
'''
def sub_plot_from_file(result_file_name, amount_plots, index, col = 1):
    XX = fill_data_from_file(result_file_name)

    res = subplot(XX, amount_plots, index, col)

    print (result_file_name + ":")
    print (XX[-1])

    if index == amount_plots:
        plt.show()

    return res


def sub_plot_find_path(file_name, amount_plots, index):
    XX = fill_data_from_file(file_name)

    plt.subplot(3, 1, 1)

    for i in range(0,len(XX),20):
        plt.plot([XX[i][1], XX[i][1]],[-2, 10], 'g')

    plt.plot([XX[0][1], XX[0][1]],[-2, 10], 'k', lw=4)
    plt.plot([XX[-1][1], XX[-1][1]],[-2, 10], 'r', lw=3)


