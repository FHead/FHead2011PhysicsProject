import argparse
import subprocess

parser = argparse.ArgumentParser()
parser.add_argument("--Nu", type = float, help = "Matern Nu", default = 2.5)
parser.add_argument("--DoEarthquake", help = "earthquake?", action = "store_true")
parser.add_argument("--DoBigEarthquake", help = "big earthquake?", action = "store_true")
parser.add_argument("--DoSmoothing", help = "smoohting?", action = "store_true")
parser.add_argument("--Model", choices = ["Matter", "LBT", "MatterLBT1", "MatterLBT2"])
parser.add_argument("--KernelChoice", choices = ["Matern", "MaternNoise", "RBF"], default = "Matern")
parser.add_argument("--Alpha", type = float, default = 0.6)
args = parser.parse_args()

import src.reader as Reader

RawDesignL   = Reader.ReadDesign('input/LBTJake/Design.dat')
MaxN         = RawDesignL["Design"].shape[0]

import os
if os.path.exists('result.p'):
    os.remove("result.p")

for N in range(0, MaxN):
    print("Executing", N, "/", MaxN)
    CommandList = ["python3", "RunOneOnlyGP.py", "--N", str(N), "--Nu", str(args.Nu), "--Model", args.Model, "--KernelChoice", args.KernelChoice, "--Alpha", str(args.Alpha)]
    if args.DoEarthquake:
        CommandList.extend(["--DoEarthquake"])
    if args.DoBigEarthquake:
        CommandList.extend(["--DoBigEarthquake"])
    if args.DoSmoothing:
        CommandList.extend(["--DoSmoothing"])
    subprocess.call(CommandList)

CommandList = ["python3", "Profit.py", "--Nu", str(args.Nu), "--Model", args.Model, "--KernelChoice", args.KernelChoice, "--Alpha", str(args.Alpha)]
if args.DoEarthquake:
    CommandList.extend(["--DoEarthquake"])
if args.DoBigEarthquake:
    CommandList.extend(["--DoBigEarthquake"])
if args.DoSmoothing:
    CommandList.extend(["--DoSmoothing"])
subprocess.call(CommandList)

CommandList[1] = "PlotSummaryPlots.py"
subprocess.call(CommandList)


