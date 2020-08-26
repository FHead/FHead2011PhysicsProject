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
parser.add_argument("--CovType", help = "what kind of error treatment", default = "Length0.2", choices = ["Length0.1", "Length0.2", "Length10", "Separated"])
parser.add_argument("--Data", choices = ["All", "LHC", "RHIC"], default = "All")
args = parser.parse_args()

from src import emulator
if args.Data == "All" or args.Data == "RHIC":
    EmulatorAuAu200 = emulator.Emulator.from_cache('AuAu200')
if args.Data == "All" or args.Data == "LHC":
    EmulatorPbPb2760 = emulator.Emulator.from_cache('PbPb2760')
    EmulatorPbPb5020 = emulator.Emulator.from_cache('PbPb5020')

from src import AllData

import numpy as np
Design = np.array([AllData['holdoutdesign']])
if args.Data == "All" or args.Data == "RHIC":
    PredictionAuAu200, CovarianceAuAu200 = EmulatorAuAu200.predict(Design, return_cov = True)
if args.Data == "All" or args.Data == "LHC":
    PredictionPbPb2760, CovariancePbPb2760 = EmulatorPbPb2760.predict(Design, return_cov = True)
    PredictionPbPb5020, CovariancePbPb5020 = EmulatorPbPb5020.predict(Design, return_cov = True)

if args.Data == "All":
    TempPrediction = {"AuAu200": PredictionAuAu200,
                     "PbPb2760": PredictionPbPb2760,
                     "PbPb5020": PredictionPbPb5020}
    Covariance = {"AuAu200": CovarianceAuAu200,
                 "PbPb2760": CovariancePbPb2760,
                 "PbPb5020": CovariancePbPb5020}
if args.Data == "RHIC":
    TempPrediction = {"AuAu200": PredictionAuAu200}
    Covariance = {"AuAu200": CovarianceAuAu200}
if args.Data == "LHC":
    TempPrediction = {"PbPb2760": PredictionPbPb2760,
                     "PbPb5020": PredictionPbPb5020}
    Covariance = {"PbPb2760": CovariancePbPb2760,
                 "PbPb5020": CovariancePbPb5020}

import src
src.Initialize()
from src import mcmc
chain = mcmc.Chain()
MCMCSamples = chain.load()


from pathlib import Path
import pickle, os

if os.path.exists('result.p'):
    AllResult = pickle.load(Path('result.p').open('rb'))
else:
    AllResult = {}
AllResult[args.N] = {}
AllResult[args.N]['Prediction'] = TempPrediction
AllResult[args.N]['Covariance'] = Covariance
AllResult[args.N]['Design'] = AllData['holdoutdesign']
AllResult[args.N]['Model'] = AllData['holdoutmodel']
AllResult[args.N]['Samples'] = MCMCSamples
with open('result.p', 'wb') as handle:
    pickle.dump(AllResult, handle, protocol = pickle.HIGHEST_PROTOCOL)

# print(AllResult[args.N])

from datetime import datetime
now = datetime.now()

FileName = "txt/Result" + "_" + args.Model
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

np.savetxt(FileName + '_MCMCSamples.txt', MCMCSamples)

if args.Data == "All" or args.Data == "RHIC":
    PosteriorAuAu200 = EmulatorAuAu200.predict(MCMCSamples)
if args.Data == "All" or args.Data == "LHC":
    PosteriorPbPb2760 = EmulatorPbPb2760.predict(MCMCSamples)
    PosteriorPbPb5020 = EmulatorPbPb5020.predict(MCMCSamples)

if args.Data == "All" or args.Data == "RHIC":
    PriorAuAu200 = EmulatorAuAu200.predict(AllData['design'])
if args.Data == "All" or args.Data == "LHC":
    PriorPbPb2760 = EmulatorPbPb2760.predict(AllData['design'])
    PriorPbPb5020 = EmulatorPbPb5020.predict(AllData['design'])

Median = np.median(MCMCSamples, axis = 0)
print(Median)

np.savetxt(FileName + '_Median.txt', [Median])

if args.Data == "All" or args.Data == "RHIC":
    MedianAuAu200 = EmulatorAuAu200.predict([Median])
if args.Data == "All" or args.Data == "LHC":
    MedianPbPb2760 = EmulatorPbPb2760.predict([Median])
    MedianPbPb5020 = EmulatorPbPb5020.predict([Median])

with Path(FileName + "_MedianPrediction.txt").open('w') as f:
    if args.Data == "All" or args.Data == "RHIC":
        np.savetxt(f, MedianAuAu200 ['R_AA']['C0'])
        np.savetxt(f, MedianAuAu200 ['R_AA']['C1'])
    if args.Data == "All" or args.Data == "LHC":
        np.savetxt(f, MedianPbPb2760['R_AA']['C0'])
        np.savetxt(f, MedianPbPb2760['R_AA']['C1'])
        np.savetxt(f, MedianPbPb5020['R_AA']['C0'])
        np.savetxt(f, MedianPbPb5020['R_AA']['C1'])

if args.Data == "All" or args.Data == "RHIC":
    np.savetxt(FileName + '_Prior1.txt', PriorAuAu200 ['R_AA']['C0'])
    np.savetxt(FileName + '_Prior2.txt', PriorAuAu200 ['R_AA']['C1'])
if args.Data == "All" or args.Data == "LHC":
    np.savetxt(FileName + '_Prior3.txt', PriorPbPb2760['R_AA']['C0'])
    np.savetxt(FileName + '_Prior4.txt', PriorPbPb2760['R_AA']['C1'])
    np.savetxt(FileName + '_Prior5.txt', PriorPbPb5020['R_AA']['C0'])
    np.savetxt(FileName + '_Prior6.txt', PriorPbPb5020['R_AA']['C1'])

if args.Data == "All" or args.Data == "RHIC":
    np.savetxt(FileName + '_Posterior1.txt', PosteriorAuAu200 ['R_AA']['C0'])
    np.savetxt(FileName + '_Posterior2.txt', PosteriorAuAu200 ['R_AA']['C1'])
if args.Data == "All" or args.Data == "LHC":
    np.savetxt(FileName + '_Posterior3.txt', PosteriorPbPb2760['R_AA']['C0'])
    np.savetxt(FileName + '_Posterior4.txt', PosteriorPbPb2760['R_AA']['C1'])
    np.savetxt(FileName + '_Posterior5.txt', PosteriorPbPb5020['R_AA']['C0'])
    np.savetxt(FileName + '_Posterior6.txt', PosteriorPbPb5020['R_AA']['C1'])

with Path(FileName + "_X.txt").open('w') as f:
    if args.Data == "All" or args.Data == "RHIC":
        np.savetxt(f, [AllData['data']["AuAu200"]["R_AA"]["C0"]['x']])
        np.savetxt(f, [AllData['data']["AuAu200"]["R_AA"]["C1"]['x']])
    if args.Data == "All" or args.Data == "LHC":
        np.savetxt(f, [AllData['data']["PbPb2760"]["R_AA"]["C0"]['x']])
        np.savetxt(f, [AllData['data']["PbPb2760"]["R_AA"]["C1"]['x']])
        np.savetxt(f, [AllData['data']["PbPb5020"]["R_AA"]["C0"]['x']])
        np.savetxt(f, [AllData['data']["PbPb5020"]["R_AA"]["C1"]['x']])

with Path(FileName + "_Y.txt").open('w') as f:
    if args.Data == "All" or args.Data == "RHIC":
        np.savetxt(f, [AllData['data']["AuAu200"]["R_AA"]["C0"]['y']])
        np.savetxt(f, [AllData['data']["AuAu200"]["R_AA"]["C1"]['y']])
    if args.Data == "All" or args.Data == "LHC":
        np.savetxt(f, [AllData['data']["PbPb2760"]["R_AA"]["C0"]['y']])
        np.savetxt(f, [AllData['data']["PbPb2760"]["R_AA"]["C1"]['y']])
        np.savetxt(f, [AllData['data']["PbPb5020"]["R_AA"]["C0"]['y']])
        np.savetxt(f, [AllData['data']["PbPb5020"]["R_AA"]["C1"]['y']])

with Path(FileName + "_E.txt").open('w') as f:
    if args.Data == "All" or args.Data == "RHIC":
        np.savetxt(f, [np.sqrt(np.diag(AllData['cov']['AuAu200'][("R_AA","C0")][("R_AA","C0")]))])
        np.savetxt(f, [np.sqrt(np.diag(AllData['cov']['AuAu200'][("R_AA","C1")][("R_AA","C1")]))])
    if args.Data == "All" or args.Data == "LHC":
        np.savetxt(f, [np.sqrt(np.diag(AllData['cov']['PbPb2760'][("R_AA","C0")][("R_AA","C0")]))])
        np.savetxt(f, [np.sqrt(np.diag(AllData['cov']['PbPb2760'][("R_AA","C1")][("R_AA","C1")]))])
        np.savetxt(f, [np.sqrt(np.diag(AllData['cov']['PbPb5020'][("R_AA","C0")][("R_AA","C0")]))])
        np.savetxt(f, [np.sqrt(np.diag(AllData['cov']['PbPb5020'][("R_AA","C1")][("R_AA","C1")]))])

with Path(FileName + "_S.txt").open('w') as f:
    if args.Data == "All" or args.Data == "RHIC":
        np.savetxt(f, [AllData['data']["AuAu200"]["R_AA"]["C0"]['yerr']['stat'][:,0]])
        np.savetxt(f, [AllData['data']["AuAu200"]["R_AA"]["C1"]['yerr']['stat'][:,0]])
    if args.Data == "All" or args.Data == "LHC":
        np.savetxt(f, [AllData['data']["PbPb2760"]["R_AA"]["C0"]['yerr']['stat'][:,0]])
        np.savetxt(f, [AllData['data']["PbPb2760"]["R_AA"]["C1"]['yerr']['stat'][:,0]])
        np.savetxt(f, [AllData['data']["PbPb5020"]["R_AA"]["C0"]['yerr']['stat'][:,0]])
        np.savetxt(f, [AllData['data']["PbPb5020"]["R_AA"]["C1"]['yerr']['stat'][:,0]])




