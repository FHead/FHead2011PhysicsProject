import random
import math
import numpy as np
import subprocess

def Predict(A, B, C, X):
    return A + B * 0.01 * X + C * 0.01 * 0.01 * X * X

N = 100
result = np.random.rand(N, 3)

with open('Design.dat', 'w') as f:
    f.write('# Version 1.0\n')
    f.write('# Parameter A B C\n')
    np.savetxt(f, result)

XMin = [10, 15, 20, 30, 40, 50, 60, 70, 85]
XMax = [15, 20, 30, 40, 50, 60, 70, 85, 100]
Y = np.zeros((N, len(XMin)))
DataStatError = 0.01
DataSysError = 0.02

Truth = [0.3, 0.7, 0.8]

DataTable = np.zeros((len(XMin), 7))

SysShift = np.random.normal(scale = DataSysError)

DataTable[:,0] = np.array(XMin).T
DataTable[:,1] = np.array(XMax).T
DataTable[:,2] = [Predict(Truth[0], Truth[1], Truth[2], (XMin[j] + XMax[j]) / 2) \
    + np.random.normal(scale = DataStatError) + SysShift for j in range(0, len(XMin))]
DataTable[:,3] = DataStatError
DataTable[:,4] = DataStatError
DataTable[:,5] = DataSysError
DataTable[:,6] = DataSysError

with open('Data_Selection1.dat', 'w') as f:
    f.write('# Version 1.0\n')
    f.write('# DOI None\n')
    f.write('# Source None\n')
    f.write('# Experiment JetScape\n')
    f.write('# System PbPb5020\n')
    f.write('# Centrality 0to10\n')
    f.write('# XY X Y\n')
    f.write('# Label xmin xmax y stat,low stat,high sys,low sys,high\n')
    np.savetxt(f, DataTable)

for i in range(0, N):
    A = result[i][0]
    B = result[i][1]
    C = result[i][2]

    for j in range(0, len(XMin)):
        X = (XMin[j] + XMax[j]) / 2
        Y[i, j] = Predict(A, B, C, X)

with open('Prediction_Selection1.dat', 'w') as f:
    f.write('# Version 1.0\n')
    f.write('# Data Data_Selection1.dat\n')
    f.write('# Design Design.dat\n')
    np.savetxt(f, np.transpose(Y))

