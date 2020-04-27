# Import stuff
from __future__ import print_function

import subprocess

from sklearn.gaussian_process import GaussianProcessRegressor as GPR
from sklearn.gaussian_process import kernels
from sklearn.decomposition import PCA
from sklearn.preprocessing import StandardScaler
import joblib

import random

import matplotlib.cm as cm
import matplotlib.pyplot as plt
from matplotlib.backends.backend_pdf import PdfPages

from IPython.display import display, clear_output

from scipy.signal import savgol_filter
from scipy.linalg import lapack
from scipy import stats
import emcee
import numpy as np

import os
import pickle
from pathlib import Path

import src.reader as Reader

from ipywidgets import interact, interactive, fixed, interact_manual
import ipywidgets as widgets

import argparse

parser = argparse.ArgumentParser()
parser.add_argument("--N", help = "Which index to use as holdout", default = -1, type = int)
parser.add_argument("--DoSmoothing", help = "Whether to smooth the model calculation or not", action = "store_true")
parser.add_argument("--DoEarthquake", help = "Whether to shift the model calculation or not", action = "store_true")
parser.add_argument("--DoBigEarthquake", help = "Whether to shake up the model calculation or not", action = "store_true")
parser.add_argument("--BeforeAfterCheck", help = "Do we export plots for before vs after check", action = 'store_true')
args = parser.parse_args()

print("Earthquake = " + str(args.DoEarthquake))
print("BigEarthquake = " + str(args.DoBigEarthquake))
print("Smoothing = " + str(args.DoSmoothing))

# Read data files
RawData1L   = Reader.ReadData('input/MATTERLBT1/Data_PHENIX_AuAu200_RAACharged_0to10_2013.dat')
RawData2L   = Reader.ReadData('input/MATTERLBT1/Data_PHENIX_AuAu200_RAACharged_40to50_2013.dat')
RawData3L   = Reader.ReadData('input/MATTERLBT1/Data_ATLAS_PbPb2760_RAACharged_0to5_2015.dat')
RawData4L   = Reader.ReadData('input/MATTERLBT1/Data_ATLAS_PbPb2760_RAACharged_30to40_2015.dat')
RawData5L   = Reader.ReadData('input/MATTERLBT1/Data_CMS_PbPb5020_RAACharged_0to10_2017.dat')
RawData6L   = Reader.ReadData('input/MATTERLBT1/Data_CMS_PbPb5020_RAACharged_30to50_2017.dat')

# Read covariance
RawCov11L = Reader.ReadCovariance('input/MATTERLBT1/Covariance_PHENIX_AuAu200_RAACharged_0to10_2013_PHENIX_AuAu200_RAACharged_0to10_2013_Jake.dat')
RawCov22L = Reader.ReadCovariance('input/MATTERLBT1/Covariance_PHENIX_AuAu200_RAACharged_40to50_2013_PHENIX_AuAu200_RAACharged_40to50_2013_Jake.dat')
RawCov33L = Reader.ReadCovariance('input/MATTERLBT1/Covariance_ATLAS_PbPb2760_RAACharged_0to5_2015_ATLAS_PbPb2760_RAACharged_0to5_2015_Jake.dat')
RawCov44L = Reader.ReadCovariance('input/MATTERLBT1/Covariance_ATLAS_PbPb2760_RAACharged_30to40_2015_ATLAS_PbPb2760_RAACharged_30to40_2015_Jake.dat')
RawCov55L = Reader.ReadCovariance('input/MATTERLBT1/Covariance_CMS_PbPb5020_RAACharged_0to10_2017_CMS_PbPb5020_RAACharged_0to10_2017_Jake.dat')
RawCov66L = Reader.ReadCovariance('input/MATTERLBT1/Covariance_CMS_PbPb5020_RAACharged_30to50_2017_CMS_PbPb5020_RAACharged_30to50_2017_Jake.dat')

# Read design points
RawDesignL   = Reader.ReadDesign('input/MATTERLBT1/Design.dat')

# Read model prediction
RawPrediction1L   = Reader.ReadPrediction('input/MATTERLBT1/Prediction_PHENIX_AuAu200_RAACharged_0to10_2013.dat')
RawPrediction2L   = Reader.ReadPrediction('input/MATTERLBT1/Prediction_PHENIX_AuAu200_RAACharged_40to50_2013.dat')
RawPrediction3L   = Reader.ReadPrediction('input/MATTERLBT1/Prediction_ATLAS_PbPb2760_RAACharged_0to5_2015.dat')
RawPrediction4L   = Reader.ReadPrediction('input/MATTERLBT1/Prediction_ATLAS_PbPb2760_RAACharged_30to40_2015.dat')
RawPrediction5L   = Reader.ReadPrediction('input/MATTERLBT1/Prediction_CMS_PbPb5020_RAACharged_0to10_2017.dat')
RawPrediction6L   = Reader.ReadPrediction('input/MATTERLBT1/Prediction_CMS_PbPb5020_RAACharged_30to50_2017.dat')

RawPrediction1LOG = Reader.ReadPrediction('input/MATTERLBT1/Prediction_PHENIX_AuAu200_RAACharged_0to10_2013.dat')
RawPrediction2LOG = Reader.ReadPrediction('input/MATTERLBT1/Prediction_PHENIX_AuAu200_RAACharged_40to50_2013.dat')
RawPrediction3LOG = Reader.ReadPrediction('input/MATTERLBT1/Prediction_ATLAS_PbPb2760_RAACharged_0to5_2015.dat')
RawPrediction4LOG = Reader.ReadPrediction('input/MATTERLBT1/Prediction_ATLAS_PbPb2760_RAACharged_30to40_2015.dat')
RawPrediction5LOG = Reader.ReadPrediction('input/MATTERLBT1/Prediction_CMS_PbPb5020_RAACharged_0to10_2017.dat')
RawPrediction6LOG = Reader.ReadPrediction('input/MATTERLBT1/Prediction_CMS_PbPb5020_RAACharged_30to50_2017.dat')

# Smooth their predictions
print(RawPrediction1L['Prediction'].shape)

Window = 5
Order = 1
DesignCount = RawPrediction1L['Prediction'].shape[0]

if args.DoSmoothing == True:
    for i in range(DesignCount):
        RawPrediction1L['Prediction'][i, :] = savgol_filter(RawPrediction1LOG['Prediction'][i, :], Window, Order)
        RawPrediction2L['Prediction'][i, :] = savgol_filter(RawPrediction2LOG['Prediction'][i, :], Window, Order)
        RawPrediction3L['Prediction'][i, :] = savgol_filter(RawPrediction3LOG['Prediction'][i, :], Window, Order)
        RawPrediction4L['Prediction'][i, :] = savgol_filter(RawPrediction4LOG['Prediction'][i, :], Window, Order)
        RawPrediction5L['Prediction'][i, :] = savgol_filter(RawPrediction5LOG['Prediction'][i, :], Window, Order)
        RawPrediction6L['Prediction'][i, :] = savgol_filter(RawPrediction6LOG['Prediction'][i, :], Window, Order)
if args.DoEarthquake == True:
    for i in range(DesignCount):
        RawPrediction1L['Prediction'][i, :] = RawPrediction1LOG['Prediction'][i, :] + np.random.uniform(-0.025, 0.025)
        RawPrediction2L['Prediction'][i, :] = RawPrediction2LOG['Prediction'][i, :] + np.random.uniform(-0.025, 0.025)
        RawPrediction3L['Prediction'][i, :] = RawPrediction3LOG['Prediction'][i, :] + np.random.uniform(-0.025, 0.025)
        RawPrediction4L['Prediction'][i, :] = RawPrediction4LOG['Prediction'][i, :] + np.random.uniform(-0.025, 0.025)
        RawPrediction5L['Prediction'][i, :] = RawPrediction5LOG['Prediction'][i, :] + np.random.uniform(-0.025, 0.025)
        RawPrediction6L['Prediction'][i, :] = RawPrediction6LOG['Prediction'][i, :] + np.random.uniform(-0.025, 0.025)
if args.DoBigEarthquake == True:
    for i in range(DesignCount):
        N = RawPrediction1L['Prediction'].shape[1]
        RawPrediction1L['Prediction'][i, :] += np.random.uniform(-0.025, 0.025, N)
        N = RawPrediction2L['Prediction'].shape[1]
        RawPrediction2L['Prediction'][i, :] += np.random.uniform(-0.025, 0.025, N)
        N = RawPrediction3L['Prediction'].shape[1]
        RawPrediction3L['Prediction'][i, :] += np.random.uniform(-0.025, 0.025, N)
        N = RawPrediction4L['Prediction'].shape[1]
        RawPrediction4L['Prediction'][i, :] += np.random.uniform(-0.025, 0.025, N)
        N = RawPrediction5L['Prediction'].shape[1]
        RawPrediction5L['Prediction'][i, :] += np.random.uniform(-0.025, 0.025, N)
        N = RawPrediction6L['Prediction'].shape[1]
        RawPrediction6L['Prediction'][i, :] += np.random.uniform(-0.025, 0.025, N)

if args.BeforeAfterCheck == True:
    with PdfPages('plots/BeforeAfterPlots.pdf') as pdf:
        for i in range(DesignCount):
            print(i)

            figure, axes = plt.subplots(figsize = (15, 15), ncols = 2, nrows = 3)

            axes[0][0].plot(RawPrediction1L['Prediction'][i, :], 'r-')
            axes[0][1].plot(RawPrediction2L['Prediction'][i, :], 'r-')
            axes[1][0].plot(RawPrediction3L['Prediction'][i, :], 'r-')
            axes[1][1].plot(RawPrediction4L['Prediction'][i, :], 'r-')
            axes[2][0].plot(RawPrediction5L['Prediction'][i, :], 'r-')
            axes[2][1].plot(RawPrediction6L['Prediction'][i, :], 'r-')

            axes[0][0].plot(RawPrediction1LOG['Prediction'][i, :], 'bo')
            axes[0][1].plot(RawPrediction2LOG['Prediction'][i, :], 'bo')
            axes[1][0].plot(RawPrediction3LOG['Prediction'][i, :], 'bo')
            axes[1][1].plot(RawPrediction4LOG['Prediction'][i, :], 'bo')
            axes[2][0].plot(RawPrediction5LOG['Prediction'][i, :], 'bo')
            axes[2][1].plot(RawPrediction6LOG['Prediction'][i, :], 'bo')

            plt.title(i)
            plt.tight_layout(True)
            pdf.savefig()
            plt.close()


# Remove one index if applicable
assert args.N < RawDesignL['Design'].shape[0],"Hold out index out of bound"
# assert args.N < RawDesignL['Design'].shape[0]
if args.N >= 0:
    HoldoutDesignL = RawDesignL['Design'][args.N]
    HoldoutPrediction1L = RawPrediction1L['Prediction'][args.N]
    HoldoutPrediction2L = RawPrediction2L['Prediction'][args.N]
    HoldoutPrediction3L = RawPrediction3L['Prediction'][args.N]
    HoldoutPrediction4L = RawPrediction4L['Prediction'][args.N]
    HoldoutPrediction5L = RawPrediction5L['Prediction'][args.N]
    HoldoutPrediction6L = RawPrediction6L['Prediction'][args.N]

    RawData1L["Data"]["y"] = HoldoutPrediction1L
    RawData2L["Data"]["y"] = HoldoutPrediction2L
    RawData3L["Data"]["y"] = HoldoutPrediction3L
    RawData4L["Data"]["y"] = HoldoutPrediction4L
    RawData5L["Data"]["y"] = HoldoutPrediction5L
    RawData6L["Data"]["y"] = HoldoutPrediction6L

    RawDesignL['Design'] = np.delete(RawDesignL['Design'], args.N, axis = 0)
    RawPrediction1L['Prediction'] = np.delete(RawPrediction1L['Prediction'], args.N, axis = 0)
    RawPrediction2L['Prediction'] = np.delete(RawPrediction2L['Prediction'], args.N, axis = 0)
    RawPrediction3L['Prediction'] = np.delete(RawPrediction3L['Prediction'], args.N, axis = 0)
    RawPrediction4L['Prediction'] = np.delete(RawPrediction4L['Prediction'], args.N, axis = 0)
    RawPrediction5L['Prediction'] = np.delete(RawPrediction5L['Prediction'], args.N, axis = 0)
    RawPrediction6L['Prediction'] = np.delete(RawPrediction6L['Prediction'], args.N, axis = 0)
    print("Holdout index = ", args.N)
else:
    HoldoutDesignL = RawDesignL['Design'][0] * -1
    HoldoutPrediction1L = RawPrediction1L['Prediction'][0]
    HoldoutPrediction2L = RawPrediction2L['Prediction'][0]
    HoldoutPrediction3L = RawPrediction3L['Prediction'][0]
    HoldoutPrediction4L = RawPrediction4L['Prediction'][0]
    HoldoutPrediction5L = RawPrediction5L['Prediction'][0]
    HoldoutPrediction6L = RawPrediction6L['Prediction'][0]
    print("No holdout")

# Setup LBT

# Initialize empty dictionary
AllData = {}

# Insert holdout stuff
AllData["holdoutdesign"] = HoldoutDesignL
HoldoutPrediction = \
    {"AuAu200": {"R_AA": {"C0": {"Y": HoldoutPrediction1L, "x": RawData1L["Data"]['x']},
                          "C1": {"Y": HoldoutPrediction2L, "x": RawData2L["Data"]['x']}}},
    "PbPb2760": {"R_AA": {"C0": {"Y": HoldoutPrediction3L, "x": RawData3L["Data"]['x']},
                          "C1": {"Y": HoldoutPrediction4L, "x": RawData4L["Data"]['x']}}},
    "PbPb5020": {"R_AA": {"C0": {"Y": HoldoutPrediction5L, "x": RawData5L["Data"]['x']},
                          "C1": {"Y": HoldoutPrediction6L, "x": RawData6L["Data"]['x']}}}}
AllData["holdoutmodel"] = HoldoutPrediction

# Basic information
AllData["systems"] = ["AuAu200", "PbPb2760", "PbPb5020"]
AllData["keys"] = RawDesignL["Parameter"]
AllData["labels"] = RawDesignL["Parameter"]
AllData["ranges"] = [(0, 1.5), (0, 1.0), (0, 20), (0, 20), (1, 4)]
AllData["observables"] = [('R_AA', ['C0', 'C1'])]

# Data points
Data = {"AuAu200": {"R_AA": {"C0": RawData1L["Data"], "C1": RawData2L["Data"]}},
       "PbPb2760": {"R_AA": {"C0": RawData3L["Data"], "C1": RawData4L["Data"]}},
       "PbPb5020": {"R_AA": {"C0": RawData5L["Data"], "C1": RawData6L["Data"]}}}

# Model predictions
Prediction = {"AuAu200": {"R_AA": {"C0": {"Y": RawPrediction1L["Prediction"], "x": RawData1L["Data"]['x']},
                                   "C1": {"Y": RawPrediction2L["Prediction"], "x": RawData2L["Data"]['x']}}},
             "PbPb2760": {"R_AA": {"C0": {"Y": RawPrediction3L["Prediction"], "x": RawData3L["Data"]['x']},
                                   "C1": {"Y": RawPrediction4L["Prediction"], "x": RawData4L["Data"]['x']}}},
             "PbPb5020": {"R_AA": {"C0": {"Y": RawPrediction5L["Prediction"], "x": RawData5L["Data"]['x']},
                                   "C1": {"Y": RawPrediction6L["Prediction"], "x": RawData6L["Data"]['x']}}}}

# Covariance matrices - the indices are [system][measurement1][measurement2], each one is a block of matrix
Covariance = Reader.InitializeCovariance(Data)
Covariance["AuAu200"][("R_AA", "C0")][("R_AA", "C0")]  = Reader.EstimateCovariance(RawData1L, RawData1L, SysLength = {"default": 0.2})
Covariance["AuAu200"][("R_AA", "C1")][("R_AA", "C1")]  = Reader.EstimateCovariance(RawData2L, RawData2L, SysLength = {"default": 0.2})
Covariance["PbPb2760"][("R_AA", "C0")][("R_AA", "C0")] = Reader.EstimateCovariance(RawData3L, RawData3L, SysLength = {"default": 0.2})
Covariance["PbPb2760"][("R_AA", "C1")][("R_AA", "C1")] = Reader.EstimateCovariance(RawData4L, RawData4L, SysLength = {"default": 0.2})
Covariance["PbPb5020"][("R_AA", "C0")][("R_AA", "C0")] = Reader.EstimateCovariance(RawData5L, RawData5L, SysLength = {"default": 0.2})
Covariance["PbPb5020"][("R_AA", "C1")][("R_AA", "C1")] = Reader.EstimateCovariance(RawData6L, RawData6L, SysLength = {"default": 0.2})

# This is how we can supply external pre-generated matrices
# Covariance["AuAu200"][("R_AA", "C0")][("R_AA", "C0")] = RawCov11L["Matrix"]
# Covariance["AuAu200"][("R_AA", "C1")][("R_AA", "C1")] = RawCov22L["Matrix"]
# Covariance["PbPb2760"][("R_AA", "C0")][("R_AA", "C0")] = RawCov33L["Matrix"]
# Covariance["PbPb2760"][("R_AA", "C1")][("R_AA", "C1")] = RawCov44L["Matrix"]
# Covariance["PbPb5020"][("R_AA", "C0")][("R_AA", "C0")] = RawCov55L["Matrix"]
# Covariance["PbPb5020"][("R_AA", "C1")][("R_AA", "C1")] = RawCov66L["Matrix"]

# Assign data to the dictionary
AllData["design"] = RawDesignL["Design"]
AllData["model"] = Prediction
AllData["data"] = Data
AllData["cov"] = Covariance

# Save to the desired pickle file
with open('input/default.p', 'wb') as handle:
    pickle.dump(AllData, handle, protocol = pickle.HIGHEST_PROTOCOL)




