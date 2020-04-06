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

SystemCount = len(AllData["systems"])

with PdfPages('ResultPlots.pdf') as pdf:
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



