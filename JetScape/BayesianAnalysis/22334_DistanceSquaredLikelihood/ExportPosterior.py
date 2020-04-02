import argparse

parser = argparse.ArgumentParser()
parser.add_argument("--N", type = int, help = "hold out index", default = 0)
parser.add_argument("--Tag", help = "Extra Tag", default = "")
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

Tag = str(args.N) + args.Tag

if os.path.exists('result.p'):
    AllResult = pickle.load(Path('result.p').open('rb'))
else:
    AllResult = {}
AllResult[Tag] = {}
AllResult[Tag]['Prediction'] = TempPrediction
AllResult[Tag]['Covariance'] = Covariance
AllResult[Tag]['Design'] = AllData['holdoutdesign']
AllResult[Tag]['Model'] = AllData['holdoutmodel']
AllResult[Tag]['Samples'] = MCMCSamples
with open('result.p', 'wb') as handle:
    pickle.dump(AllResult, handle, protocol = pickle.HIGHEST_PROTOCOL)

# print(AllResult[args.N])

