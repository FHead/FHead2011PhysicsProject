import argparse

parser = argparse.ArgumentParser()
parser.add_argument("--Nu", type = float, help = "Matern Nu", default = 2.5)
parser.add_argument("--DoEarthquake", help = "earthquake?", action = "store_true")
parser.add_argument("--DoBigEarthquake", help = "big earthquake?", action = "store_true")
parser.add_argument("--DoSmoothing", help = "smoohting?", action = "store_true")
parser.add_argument("--Model", choices = ["Matter", "MatterInflated", "LBT", "MatterLBT1", "MatterLBT2"])
parser.add_argument("--KernelChoice", choices = ["Matern", "MaternNoise", "MaternNoise1", "RBF"], default = "Matern")
parser.add_argument("--Alpha", type = float, default = 0.6)
parser.add_argument("--Noise", type = float, default = -1)
parser.add_argument("--CovType", help = "what kind of error treatment", default = "Length0.2", choices = ["Length0.1", "Length0.2", "Length10", "Separated"])
args = parser.parse_args()

from pathlib import Path
import pickle, os

AllResult = pickle.load(Path('result.p').open('rb'))

import numpy as np
import matplotlib.cm as cm
import matplotlib.pyplot as plt
from matplotlib.backends.backend_pdf import PdfPages

from src import AllData

if not os.path.exists('plots/'):
    os.mkdir('plots')

from datetime import datetime
now = datetime.now()

FileName = "plots/HoldoutSummaryPlots" + "_" + args.Model
FileName = FileName + "_" + args.KernelChoice + "_" + "Nu" + str(args.Nu)
FileName = FileName + "_Alpha" + str(args.Alpha)
FileName = FileName + "_Noise" + str(args.Noise)
FileName = FileName + "_CovType" + args.CovType
FileName = FileName + "_Earthquake" + str(args.DoEarthquake)
FileName = FileName + "_BigEarthquake" + str(args.DoBigEarthquake)
FileName = FileName + "_Smoothing" + str(args.DoSmoothing)
FileName = FileName + "_Time" + now.strftime("%Y%m%d-%H%M%S")
FileName = FileName + ".pdf"

with PdfPages(FileName) as pdf:
    SystemCount = len(AllData["systems"])

    for s1 in range(0, SystemCount):
        for s2 in range(0, 2):
            S1 = AllData["systems"][s1]
            O  = AllData["observables"][0][0]
            S2 = AllData["observables"][0][1][s2]

            X = np.array([[]])
            E = np.array([[]])
            Y = np.array([[]])
            First = True

            for i in AllResult:
                if First == False:
                    X = np.append(X, [AllResult[i]["Model"][S1][O][S2]['Y']], axis = 0)
                    E = np.append(E, [np.sqrt(AllResult[i]["Covariance"][S1][(O,S2),(O,S2)][0].diagonal())], axis = 0)
                    Y = np.append(Y, [AllResult[i]["Prediction"][S1][O][S2][0]], axis = 0)
                else:
                    X = [AllResult[i]["Model"][S1][O][S2]['Y']]
                    E = [np.sqrt(AllResult[i]["Covariance"][S1][(O,S2),(O,S2)][0].diagonal())]
                    Y = [AllResult[i]["Prediction"][S1][O][S2][0]]
                    First = False

            N = X.shape[1]

            for i in range(0, N):
                PT = str(AllResult[0]["Model"][S1][O][S2]['x'][i])

                plt.figure(figsize = (5, 5))
                plt.xlabel('Calculated RAA')
                plt.ylabel('Predicted RAA')
                plt.title('Holdout test, ' + S1 + ', ' + S2 + ', PT = ' + PT + ' GeV')

                plt.plot([0, 1], [0, 1], 'k-')
                plt.errorbar(X[:,i], Y[:,i], yerr = E[:,i], fmt = 'bo')

                pdf.savefig()
                plt.close()






