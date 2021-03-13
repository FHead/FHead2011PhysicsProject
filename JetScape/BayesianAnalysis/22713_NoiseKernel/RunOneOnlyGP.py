import argparse
import subprocess

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
args = parser.parse_args()

if args.DoEarthquake == True:
    subprocess.call(["python3", "SetupData.py", "--CovType", args.CovType, "--Model", args.Model, "--N", str(args.N), "--DoEarthquake"])
elif args.DoBigEarthquake == True:
    subprocess.call(["python3", "SetupData.py", "--CovType", args.CovType, "--Model", args.Model, "--N", str(args.N), "--DoBigEarthquake"])
elif args.DoSmoothing == True:
    subprocess.call(["python3", "SetupData.py", "--CovType", args.CovType, "--Model", args.Model, "--N", str(args.N), "--DoSmoothing"])
else:
    subprocess.call(["python3", "SetupData.py", "--CovType", args.CovType, "--Model", args.Model, "--N", str(args.N)])
subprocess.call(["python3", "CleanPastFiles.py"])
subprocess.call(["python3", "-m", "src.emulator", "--retrain", "--npc", "3", "--nrestarts", "50", "--nu", str(args.Nu), "--kernelchoice", args.KernelChoice, "--alpha", str(args.Alpha), "--noise", str(args.Noise)])
subprocess.call(["python3", "ExportPrediction.py", "--N", str(args.N)])




