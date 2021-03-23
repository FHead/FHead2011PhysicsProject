
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
parser.add_argument("--Nu", type = float, help = "Matern Nu", default = 2.5)
parser.add_argument("--DoEarthquake", help = "earthquake?", action = "store_true")
parser.add_argument("--DoBigEarthquake", help = "big earthquake?", action = "store_true")
parser.add_argument("--DoSmoothing", help = "smoohting?", action = "store_true")
parser.add_argument("--Model", choices = ["Matter", "LBT", "MatterLBT1", "MatterLBT2"])
parser.add_argument("--KernelChoice", choices = ["Matern", "MaternNoise", "MaternNoise1", "RBF"], default = "Matern")
parser.add_argument("--Alpha", type = float, default = 0.6)
parser.add_argument("--Noise", type = float, default = -1)
parser.add_argument("--CovType", help = "what kind of error treatment", default = "Length0.2", choices = ["Length0.1", "Length0.2", "Length10", "Separated", "Separated10"])
parser.add_argument("--Data", choices = ["All", "RHIC", "LHC"], default = "All")
args = parser.parse_args()

import src
src.Initialize()
from src import mcmc
chain = mcmc.Chain()
MCMCSamples = chain.load()

if args.Data == "All" or args.Data == "RHIC":
    EmulatorAuAu200 = src.emulator.Emulator.from_cache('AuAu200')
if args.Data == "All" or args.Data == "LHC":
    EmulatorPbPb2760 = src.emulator.Emulator.from_cache('PbPb2760')
    EmulatorPbPb5020 = src.emulator.Emulator.from_cache('PbPb5020')

if not os.path.exists('plots/'):
    os.mkdir('plots')

from datetime import datetime
now = datetime.now()

FileName = "plots/ResultPlots" + "_" + args.Model
FileName = FileName + "_" + str(args.N)
FileName = FileName + "_Data" + args.Data
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
    # MCMC Samples Plot
    # with chain.dataset() as d:
    #     W = d.shape[0]     # number of walkers
    #     S = d.shape[1]     # number of steps
    #     N = d.shape[2]     # number of paramters
    #     T = int(S / 200)   # "thinning"
    #     A = 20 / W
    #     figure, axes = plt.subplots(figsize = (15, 2 * N), ncols = 1, nrows = N)
    #     for i, ax in enumerate(axes):
    #         for j in range(0, W):
    #             ax.plot(range(0, S, T), d[j, ::T, i], alpha = A)
    #     plt.tight_layout(True)
    #     pdf.savefig()
    #     plt.close()


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

                # ax.plot(AllData['holdoutdesign'][j], AllData['holdoutdesign'][i], 'ro')
            if i<j:
                ax.axis('off')
    plt.tight_layout(True)
    pdf.savefig()
    plt.close()

    # transformed correlation plots
    if AllData["labels"][0] == "A+C" and AllData["labels"][1] == "A/(A+C)":
        NDimension = len(AllData["labels"])
        Ranges = np.array(AllData["ranges"]).T
        figure, axes = plt.subplots(figsize = (3 * NDimension, 3 * NDimension), ncols = NDimension, nrows = NDimension)
        Names = AllData["labels"]
        Names[0] = "A"
        Names[1] = "C"
        TransformedSamples = np.copy(MCMCSamples)
        TransformedSamples[:,0] = MCMCSamples[:,0] * MCMCSamples[:,1]
        TransformedSamples[:,1] = MCMCSamples[:,0] - MCMCSamples[:,0] * MCMCSamples[:,1]
        for i, row in enumerate(axes):
            for j, ax in enumerate(row):
                if i==j:
                    ax.hist(TransformedSamples[:,i], bins=50,
                            range=Ranges[:,i], histtype='step', color='blue')
                    ax.set_xlabel(Names[i])
                    ax.set_xlim(*Ranges[:,j])
                if i>j:
                    ax.hist2d(TransformedSamples[:, j], TransformedSamples[:, i],
                              bins=50, range=[Ranges[:,j], Ranges[:,i]],
                              cmap='Blues')
                    ax.set_xlabel(Names[j])
                    ax.set_ylabel(Names[i])
                    ax.set_xlim(*Ranges[:,j])
                    ax.set_ylim(*Ranges[:,i])

                    # ax.plot(AllData['holdoutdesign'][j], AllData['holdoutdesign'][i], 'ro')
                if i<j:
                    ax.axis('off')
        plt.tight_layout(True)
        pdf.savefig()
        plt.close()


    # Posterior Plot
    Examples = MCMCSamples[ np.random.choice(range(len(MCMCSamples)), 2500), :]

    if args.Data == "All":
        TempPrediction = {"AuAu200": EmulatorAuAu200.predict(Examples),
                         "PbPb2760": EmulatorPbPb2760.predict(Examples),
                         "PbPb5020": EmulatorPbPb5020.predict(Examples)}
    if args.Data == "LHC":
        TempPrediction = {"PbPb2760": EmulatorPbPb2760.predict(Examples),
                         "PbPb5020": EmulatorPbPb5020.predict(Examples)}
    if args.Data == "RHIC":
        TempPrediction = {"AuAu200": EmulatorAuAu200.predict(Examples)}

    SystemCount = len(AllData["systems"])
    RowCount = SystemCount
    if RowCount == 1:
        RowCount = 2

    figure, axes = plt.subplots(figsize = (15, 5 * RowCount), ncols = 2, nrows = RowCount)

    for s1 in range(0, SystemCount):
        for s2 in range(0, 2):
            axes[s1][s2].set_xlabel(r"$p_{T}$")
            axes[s1][s2].set_ylabel(r"$R_{AA}$")

            S1 = AllData["systems"][s1]
            O  = AllData["observables"][0][0]
            S2 = AllData["observables"][0][1][s2]

            DX = AllData["data"][S1][O][S2]['x']
            DY = AllData["data"][S1][O][S2]['y']
            DE = np.sqrt(AllData["data"][S1][O][S2]['yerr']['stat'][:,0]**2 +np.sum(AllData["data"][S1][O][S2]['yerr']['sys'][:,::2]**2, 1))

            for i, y in enumerate(TempPrediction[S1][O][S2]):
                axes[s1][s2].plot(DX, y, 'b-', alpha=0.005, label="Posterior" if i==0 else '')
            axes[s1][s2].errorbar(DX, DY, yerr = DE, fmt='ro', label="Measurements")

    plt.tight_layout(True)
    pdf.savefig()
    plt.close()


    # Posterior pull plot
    figure, axes = plt.subplots(figsize = (15, 5 * RowCount), ncols = 2, nrows = RowCount)

    AllPull = np.zeros(len(Examples))
    Pull = {}

    for s1 in range(0, SystemCount):
        Pull[s1] = {}
        for s2 in range(0, 2):
            Pull[s1][s2] = np.array([])
            axes[s1][s2].set_xlabel(r"$p_{T}$")
            axes[s1][s2].set_ylabel(r"$R_{AA}$")

            S1 = AllData["systems"][s1]
            O  = AllData["observables"][0][0]
            S2 = AllData["observables"][0][1][s2]

            DX = AllData["data"][S1][O][S2]['x']
            DY = AllData["data"][S1][O][S2]['y']
            DE = np.sqrt(AllData["data"][S1][O][S2]['yerr']['stat'][:,0]**2 +np.sum(AllData["data"][S1][O][S2]['yerr']['sys'][:,::2]**2, 1))

            for i, y in enumerate(TempPrediction[S1][O][S2]):
                axes[s1][s2].plot(DX, (y - DY) / DE, 'b-', alpha=0.005, label="Posterior" if i==0 else '')
                Pull[s1][s2] = np.append(Pull[s1][s2], (y - DY) / DE)

                AllPull[i] += np.sum((y - DY) / DE)

    plt.tight_layout(True)
    pdf.savefig()
    plt.close()



    # Pull summary plot
    figure, axes = plt.subplots(figsize = (15, 5 * RowCount), ncols = 2, nrows = RowCount)

    for s1 in range(0, SystemCount):
        for s2 in range(0, 2):
            axes[s1][s2].hist(Pull[s1][s2], bins = (int(np.ceil(max(Pull[s1][s2]))) - int(np.floor(min(Pull[s1][s2])))),
                range = (np.floor(min(Pull[s1][s2])) - 0.5, np.ceil(max(Pull[s1][s2])) - 0.5))

    plt.tight_layout(True)
    pdf.savefig()
    plt.close()



    # Overall pull summary plot

    plt.hist(AllPull / 60, bins = (int(np.ceil(max(AllPull))) - int(np.floor(min(AllPull)))),
        range = (np.floor(min(AllPull)) / 60, np.ceil(max(AllPull)) / 60))

    pdf.savefig()
    plt.close()
























