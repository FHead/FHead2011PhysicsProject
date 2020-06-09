from pathlib import Path
import pickle
import os
from matplotlib.backends.backend_pdf import PdfPages
import numpy as np
import datetime
import matplotlib.pyplot as plt
from src import AllData

if os.path.exists('result.p'):
    AllResult = pickle.load(Path('result.p').open('rb'))

import argparse

parser = argparse.ArgumentParser()
parser.add_argument("--Nu", type = float, help = "Matern Nu", default = 2.5)
parser.add_argument("--DoEarthquake", help = "earthquake?", action = "store_true")
parser.add_argument("--DoBigEarthquake", help = "big earthquake?", action = "store_true")
parser.add_argument("--DoSmoothing", help = "smoohting?", action = "store_true")
parser.add_argument("--Model", choices = ["Matter", "LBT", "MatterLBT1", "MatterLBT2"])
parser.add_argument("--KernelChoice", choices = ["Matern", "MaternNoise", "RBF"], default = "Matern")
parser.add_argument("--Alpha", type = float, default = 0.6)
parser.add_argument("--CovType", help = "what kind of error treatment", default = "Length0.2", choices = ["Length0.1", "Length0.2", "Length10", "Separated"])
args = parser.parse_args()

SystemCount = len(AllData["systems"])

from datetime import datetime
now = datetime.now()

FileName = "plots/ResultPlotsGP" + "_" + args.Model
FileName = FileName + "_" + args.KernelChoice + "_" + "Nu" + str(args.Nu)
FileName = FileName + "_Alpha" + str(args.Alpha)
FileName = FileName + "_CovType" + args.CovType
FileName = FileName + "_Earthquake" + str(args.DoEarthquake)
FileName = FileName + "_BigEarthquake" + str(args.DoBigEarthquake)
FileName = FileName + "_Smoothing" + str(args.DoSmoothing)
FileName = FileName + "_Time" + now.strftime("%Y%m%d-%H%M%S")
FileName = FileName + ".pdf"

with PdfPages(FileName) as pdf:
    for i in AllResult:
        if i < 0:
            continue
        print("processing index", i)
        figure, axes = plt.subplots(figsize = (15, 5 * SystemCount), ncols = 2, nrows = SystemCount)

        figure.suptitle('Index = {:d}, Parameters = ({:.3f}, {:.2f}, {:.3f}, {:.2f})'.format(i, AllData["design"][i][0],AllData["design"][i][1], AllData["design"][i][2], AllData["design"][i][3]), fontsize=16)

        for s1 in range(0, SystemCount):
            for s2 in range(0, 2):
                axes[s1][s2].set_xlabel(r"$p_{T}$")
                axes[s1][s2].set_ylabel(r"$R_{AA}$")

                S1 = AllData["systems"][s1]
                O  = AllData["observables"][0][0]
                S2 = AllData["observables"][0][1][s2]

                PY = AllResult[i]["Prediction"][S1][O][S2][0]
                PE = np.sqrt(AllResult[i]["Covariance"][S1][(O,S2),(O,S2)][0].diagonal())
                MX = AllResult[i]["Model"][S1][O][S2]['x']
                MY = AllResult[i]["Model"][S1][O][S2]['Y']

                axes[s1][s2].plot(MX, MY, 'b-', label="Prediction")
                axes[s1][s2].errorbar(MX, PY, yerr = PE, fmt='ro', label="Measurements")

        plt.tight_layout(True, rect=[0, 0, 1, 0.95])
        pdf.savefig()
        plt.close()



