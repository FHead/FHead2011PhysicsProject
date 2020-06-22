import argparse

parser = argparse.ArgumentParser()
parser.add_argument("--N", type = int, help = "hold out index", default = 0)
parser.add_argument("--Nu", type = float, help = "Matern Nu", default = 2.5)
parser.add_argument("--DoEarthquake", help = "earthquake?", action = "store_true")
parser.add_argument("--DoBigEarthquake", help = "big earthquake?", action = "store_true")
parser.add_argument("--DoSmoothing", help = "smoohting?", action = "store_true")
parser.add_argument("--Model", choices = ["Matter", "LBT", "MatterLBT1", "MatterLBT2"])
parser.add_argument("--KernelChoice", choices = ["Matern", "MaternNoise", "RBF"], default = "Matern")
parser.add_argument("--Alpha", type = float, default = 0.6)
parser.add_argument("--Noise", type = float, default = -1)
parser.add_argument("--CovType", help = "what kind of error treatment", default = "Length0.2", choices = ["Length0.1", "Length0.2", "Length10", "Separated"])
args = parser.parse_args()

from src import emulator
EmulatorAuAu200 = emulator.Emulator.from_cache('AuAu200')
EmulatorPbPb2760 = emulator.Emulator.from_cache('PbPb2760')
EmulatorPbPb5020 = emulator.Emulator.from_cache('PbPb5020')

from src import AllData

import numpy as np
Design = np.array([AllData['holdoutdesign']])
PredictionAuAu200, CovarianceAuAu200 = EmulatorAuAu200.predict(Design, return_cov = True)
PredictionPbPb2760, CovariancePbPb2760 = EmulatorPbPb2760.predict(Design, return_cov = True)
PredictionPbPb5020, CovariancePbPb5020 = EmulatorPbPb5020.predict(Design, return_cov = True)

TempPrediction = {"AuAu200": PredictionAuAu200,
                 "PbPb2760": PredictionPbPb2760,
                 "PbPb5020": PredictionPbPb5020}
Covariance = {"AuAu200": CovarianceAuAu200,
             "PbPb2760": CovariancePbPb2760,
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
FileName = FileName + "_" + args.KernelChoice + "_" + "Nu" + str(args.Nu)
FileName = FileName + "_Alpha" + str(args.Alpha)
FileName = FileName + "_Noise" + str(args.Noise)
FileName = FileName + "_CovType" + args.CovType
FileName = FileName + "_Earthquake" + str(args.DoEarthquake)
FileName = FileName + "_BigEarthquake" + str(args.DoBigEarthquake)
FileName = FileName + "_Smoothing" + str(args.DoSmoothing)
FileName = FileName + "_Time" + now.strftime("%Y%m%d-%H%M%S")

np.savetxt(FileName + '_MCMCSamples.txt', MCMCSamples)

PosteriorAuAu200 = EmulatorAuAu200.predict(MCMCSamples)
PosteriorPbPb2760 = EmulatorPbPb2760.predict(MCMCSamples)
PosteriorPbPb5020 = EmulatorPbPb5020.predict(MCMCSamples)

np.savetxt(FileName + '_Posterior1.txt', PosteriorAuAu200 ['R_AA']['C0'])
np.savetxt(FileName + '_Posterior2.txt', PosteriorAuAu200 ['R_AA']['C1'])
np.savetxt(FileName + '_Posterior3.txt', PosteriorPbPb2760['R_AA']['C0'])
np.savetxt(FileName + '_Posterior4.txt', PosteriorPbPb2760['R_AA']['C1'])
np.savetxt(FileName + '_Posterior5.txt', PosteriorPbPb5020['R_AA']['C0'])
np.savetxt(FileName + '_Posterior6.txt', PosteriorPbPb5020['R_AA']['C1'])

with Path(FileName + "_X.txt").open('w') as f:
    np.savetxt(f, AllData['data']["AuAu200"]["R_AA"]["C0"]['x'])
    np.savetxt(f, AllData['data']["AuAu200"]["R_AA"]["C1"]['x'])
    np.savetxt(f, AllData['data']["PbPb2760"]["R_AA"]["C0"]['x'])
    np.savetxt(f, AllData['data']["PbPb2760"]["R_AA"]["C1"]['x'])
    np.savetxt(f, AllData['data']["PbPb5020"]["R_AA"]["C0"]['x'])
    np.savetxt(f, AllData['data']["PbPb5020"]["R_AA"]["C1"]['x'])

with Path(FileName + "_X.txt").open('w') as f:
    np.savetxt(f, AllData['data']["AuAu200"]["R_AA"]["C0"]['y'])
    np.savetxt(f, AllData['data']["AuAu200"]["R_AA"]["C1"]['y'])
    np.savetxt(f, AllData['data']["PbPb2760"]["R_AA"]["C0"]['y'])
    np.savetxt(f, AllData['data']["PbPb2760"]["R_AA"]["C1"]['y'])
    np.savetxt(f, AllData['data']["PbPb5020"]["R_AA"]["C0"]['y'])
    np.savetxt(f, AllData['data']["PbPb5020"]["R_AA"]["C1"]['y'])

with Path(FileName + "_X.txt").open('w') as f:
    np.savetxt(f, np.diag(AllData['cov']['AuAu200'][("R_AA","C0")][("R_AA","C0")]))
    np.savetxt(f, np.diag(AllData['cov']['AuAu200'][("R_AA","C1")][("R_AA","C1")]))
    np.savetxt(f, np.diag(AllData['cov']['PbPb2760'][("R_AA","C0")][("R_AA","C0")]))
    np.savetxt(f, np.diag(AllData['cov']['PbPb2760'][("R_AA","C1")][("R_AA","C1")]))
    np.savetxt(f, np.diag(AllData['cov']['PbPb5020'][("R_AA","C0")][("R_AA","C0")]))
    np.savetxt(f, np.diag(AllData['cov']['PbPb5020'][("R_AA","C1")][("R_AA","C1")]))




