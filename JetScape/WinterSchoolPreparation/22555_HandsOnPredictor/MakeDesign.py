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

XMin1 = [40, 50, 60, 70, 80, 90]
XMax1 = [50, 60, 70, 80, 90, 100]
XMin2 = [10, 12, 14, 16, 18, 20, 23, 26, 29, 32, 38]
XMax2 = [12, 14, 16, 18, 20, 23, 26, 29, 32, 38, 45]
Y1 = np.zeros((N, len(XMin1)))
Y2 = np.zeros((N, len(XMin2)))
DataStatError1 = 0.02
DataStatError2 = 0.01
DataSysError1 = 0.02
DataSysError2 = 0.005

Truth = [0.3, 0.7, 0.8]

DataTable1 = np.zeros((len(XMin1), 7))
DataTable2 = np.zeros((len(XMin2), 7))

SysShift1 = np.random.normal(scale = DataSysError1)
SysShift2 = np.random.normal(scale = DataSysError2)

DataTable1[:,0] = np.array(XMin1).T
DataTable1[:,1] = np.array(XMax1).T
DataTable1[:,2] = [Predict(Truth[0], Truth[1], Truth[2], (XMin1[j] + XMax1[j]) / 2) \
    + np.random.normal(scale = DataStatError1) + SysShift1 for j in range(0, len(XMin1))]
DataTable1[:,3] = DataStatError1
DataTable1[:,4] = DataStatError1
DataTable1[:,5] = DataSysError1
DataTable1[:,6] = DataSysError1

DataTable2[:,0] = np.array(XMin2).T
DataTable2[:,1] = np.array(XMax2).T
DataTable2[:,2] = [Predict(Truth[0], Truth[1], Truth[2], (XMin2[j] + XMax2[j]) / 2) \
    + np.random.normal(scale = DataStatError2) + SysShift2 for j in range(0, len(XMin2))]
DataTable2[:,3] = DataStatError2
DataTable2[:,4] = DataStatError2
DataTable2[:,5] = DataSysError2
DataTable2[:,6] = DataSysError2

with open('Data_Selection1.dat', 'w') as f:
    f.write('# Version 1.0\n')
    f.write('# DOI None\n')
    f.write('# Source None\n')
    f.write('# Experiment JetScapeRun1\n')
    f.write('# System PbPb5020\n')
    f.write('# Centrality 0to10\n')
    f.write('# XY X Y\n')
    f.write('# Label xmin xmax y stat,low stat,high sys,low sys,high\n')
    np.savetxt(f, DataTable1)
with open('Data_Selection2.dat', 'w') as f:
    f.write('# Version 1.0\n')
    f.write('# DOI None\n')
    f.write('# Source None\n')
    f.write('# Experiment JetScapeRun2\n')
    f.write('# System PbPb5020\n')
    f.write('# Centrality 0to10\n')
    f.write('# XY X Y\n')
    f.write('# Label xmin xmax y stat,low stat,high sys,low sys,high\n')
    np.savetxt(f, DataTable2)

for i in range(0, N):
    A = result[i][0]
    B = result[i][1]
    C = result[i][2]

    for j in range(0, len(XMin1)):
        X = (XMin1[j] + XMax1[j]) / 2
        Y1[i, j] = Predict(A, B, C, X)
    for j in range(0, len(XMin2)):
        X = (XMin2[j] + XMax2[j]) / 2
        Y2[i, j] = Predict(A, B, C, X)

with open('Prediction_Selection1.dat', 'w') as f:
    f.write('# Version 1.0\n')
    f.write('# Data Data_Selection1.dat\n')
    f.write('# Design Design.dat\n')
    np.savetxt(f, np.transpose(Y1))

with open('Prediction_Selection2.dat', 'w') as f:
    f.write('# Version 1.0\n')
    f.write('# Data Data_Selection2.dat\n')
    f.write('# Design Design.dat\n')
    np.savetxt(f, np.transpose(Y2))


