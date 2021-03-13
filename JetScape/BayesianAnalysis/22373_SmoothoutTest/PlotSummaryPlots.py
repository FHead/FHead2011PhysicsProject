# import argparse
#
# parser = argparse.ArgumentParser()
# parser.add_argument("--N", type = int, help = "hold out index", default = 0)
# args = parser.parse_args()

# from pathlib import Path
# import pickle, os
#
# if os.path.exists('result.p'):
#     AllResult = pickle.load(Path('result.p').open('rb'))
# else:
#     AllResult = {}
# AllResult[args.N] = {}
# AllResult[args.N]['Prediction'] = TempPrediction
# AllResult[args.N]['Covariance'] = Covariance
# AllResult[args.N]['Design'] = AllData['holdoutdesign']
# AllResult[args.N]['Model'] = AllData['holdoutmodel']
# with open('result.p', 'wb') as handle:
#     pickle.dump(AllResult, handle, protocol = pickle.HIGHEST_PROTOCOL)

# print(AllResult[args.N])

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

with PdfPages('plots/SummaryPlots.pdf') as pdf:
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






