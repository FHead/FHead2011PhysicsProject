
from __future__ import print_function

import subprocess

from sklearn.gaussian_process import GaussianProcessRegressor as GPR
from sklearn.gaussian_process import kernels
from sklearn.decomposition import PCA
from sklearn.preprocessing import StandardScaler
import joblib

import matplotlib.cm as cm
import matplotlib.pyplot as plt

from IPython.display import display, clear_output


from scipy.linalg import lapack
from scipy import stats
import emcee
import numpy as np

import os
import pickle
from pathlib import Path

import src.reader as Reader
from src import AllData

from matplotlib.backends.backend_pdf import PdfPages
import argparse
parser = argparse.ArgumentParser()
parser.add_argument("--N", type = int, help = "hold out index", default = 0)
parser.add_argument("--Tag", help = "Extra Tag", default = "")
args = parser.parse_args()

import src
src.Initialize()
from src import mcmc
chain = mcmc.Chain()
MCMCSamples = chain.load()

EmulatorAuAu200 = src.emulator.Emulator.from_cache('AuAu200')
EmulatorPbPb2760 = src.emulator.Emulator.from_cache('PbPb2760')
EmulatorPbPb5020 = src.emulator.Emulator.from_cache('PbPb5020')

if not os.path.exists('plots/'):
    os.mkdir('plots')

with PdfPages('plots/ResultPlots' + str(args.N) + args.Tag + ".pdf") as pdf:
    # MCMC Samples Plot
    with chain.dataset() as d:
        W = d.shape[0]     # number of walkers
        S = d.shape[1]     # number of steps
        N = d.shape[2]     # number of paramters
        T = int(S / 200)   # "thinning"
        A = 20 / W
        figure, axes = plt.subplots(figsize = (15, 2 * N), ncols = 1, nrows = N)
        for i, ax in enumerate(axes):
            for j in range(0, W):
                ax.plot(range(0, S, T), d[j, ::T, i], alpha = A)
        plt.tight_layout(True)
        pdf.savefig()
        plt.close()


    # Correlation Plot
    NDimension = len(AllData["labels"])
    Ranges = np.array(AllData["ranges"]).T
    figure, axes = plt.subplots(figsize = (3 * NDimension, 3 * NDimension), ncols = NDimension, nrows = NDimension)
    Names = AllData["labels"]
    for i, row in enumerate(axes):
        for j, ax in enumerate(row):
            if i==j:
                ax.hist(MCMCSamples[:,i], bins=50,
                        range=Ranges[:,i], histtype='step', color='green')
                ax.set_xlabel(Names[i])
                ax.set_xlim(*Ranges[:,j])
            if i>j:
                ax.hist2d(MCMCSamples[:, j], MCMCSamples[:, i],
                          bins=50, range=[Ranges[:,j], Ranges[:,i]],
                          cmap='Greens')
                ax.set_xlabel(Names[j])
                ax.set_ylabel(Names[i])
                ax.set_xlim(*Ranges[:,j])
                ax.set_ylim(*Ranges[:,i])

                ax.plot(AllData['holdoutdesign'][j], AllData['holdoutdesign'][i], 'ro')
            if i<j:
                ax.axis('off')
    plt.tight_layout(True)
    pdf.savefig()
    plt.close()


    # Posterior Plot
    Examples = MCMCSamples[ np.random.choice(range(len(MCMCSamples)), 2500), :]

    TempPrediction = {"AuAu200": EmulatorAuAu200.predict(Examples),
                     "PbPb2760": EmulatorPbPb2760.predict(Examples),
                     "PbPb5020": EmulatorPbPb5020.predict(Examples)}

    SystemCount = len(AllData["systems"])

    figure, axes = plt.subplots(figsize = (15, 5 * SystemCount), ncols = 2, nrows = SystemCount)

    for s1 in range(0, SystemCount):
        for s2 in range(0, 2):
            axes[s1][s2].set_xlabel(r"$p_{T}$")
            axes[s1][s2].set_ylabel(r"$R_{AA}$")

            S1 = AllData["systems"][s1]
            O  = AllData["observables"][0][0]
            S2 = AllData["observables"][0][1][s2]

            DX = AllData["data"][S1][O][S2]['x']
            DY = AllData["data"][S1][O][S2]['y']
            DE = np.sqrt(AllData["data"][S1][O][S2]['yerr']['stat'][:,0]**2 + AllData["data"][S1][O][S2]['yerr']['sys'][:,0]**2)

            for i, y in enumerate(TempPrediction[S1][O][S2]):
                axes[s1][s2].plot(DX, y, 'b-', alpha=0.005, label="Posterior" if i==0 else '')
            axes[s1][s2].errorbar(DX, DY, yerr = DE, fmt='ro', label="Measurements")

    plt.tight_layout(True)
    pdf.savefig()
    plt.close()





