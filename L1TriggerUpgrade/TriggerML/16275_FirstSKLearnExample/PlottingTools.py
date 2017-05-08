import matplotlib.pyplot as plt
import numpy as np
import math

def BinAndMean(x: np.array, y: np.array, binning: np.array):
    binning = np.sort(binning)

    for i in np.arange(len(binning) - 1):
        BinMin = binning[i]
        BinMax = binning[i+1]

        datax = np.array([])
        datay = np.array([])
        for j in np.arange(len(x)):
            if x[j] >= BinMin and x[j] < BinMax:
                datax = np.append(datax, x[j])
                datay = np.append(datay, y[j])

        meanx = np.mean(datax)
        mean = np.mean(datay)
        std = np.std(datay)
        meanerr = std / math.sqrt(len(datay))
        stderr = std / math.sqrt(2 * len(datay))
        xerrlow = meanx - BinMin
        xerrhigh = BinMax - meanx

        if i == 0:
            Result = [[i, meanx, xerrlow, xerrhigh, mean, std, stderr, meanerr]]
        else:
            Result = np.append(Result, [[i, meanx, xerrlow, xerrhigh, mean, std, stderr, meanerr]], axis = 0)

    plt.figure(figsize = (10, 10))

    plt.errorbar(x = Result[:,1], y = Result[:,4], xerr = Result[:,2:4].T, yerr = Result[:,7], fmt = 'o')


def BinAndRMS(x: np.array, y: np.array, binning: np.array):
    binning = np.sort(binning)

    for i in np.arange(len(binning) - 1):
        BinMin = binning[i]
        BinMax = binning[i+1]

        datax = np.array([])
        datay = np.array([])
        for j in np.arange(len(x)):
            if x[j] >= BinMin and x[j] < BinMax:
                datax = np.append(datax, x[j])
                datay = np.append(datay, y[j])

        mean = np.mean(datax)
        std = np.std(datay)
        stderr = std / math.sqrt(2 * len(datay))
        xerrlow = mean - BinMin
        xerrhigh = BinMax - mean

        if i == 0:
            Result = [[i, mean, std, xerrlow, xerrhigh, stderr]]
        else:
            Result = np.append(Result, [[i, mean, std, xerrlow, xerrhigh, stderr]], axis = 0)

    plt.figure(figsize = (10, 10))

    plt.errorbar(x = Result[:,1], y = Result[:,2], xerr = Result[:,3:5].T, yerr = Result[:,5], fmt = 'o')
    plt.axes().set_yscale('log')

    # print(x[1:10])
    # print(y[1:10])
    # print(Result)
