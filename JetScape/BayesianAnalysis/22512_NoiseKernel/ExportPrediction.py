import argparse

parser = argparse.ArgumentParser()
parser.add_argument("--N", type = int, help = "hold out index", default = 0)
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
with open('result.p', 'wb') as handle:
    pickle.dump(AllResult, handle, protocol = pickle.HIGHEST_PROTOCOL)

# print(AllResult[args.N])
