import argparse
import subprocess

parser = argparse.ArgumentParser()
parser.add_argument("--N", type = int, help = "hold out index", default = 0)
parser.add_argument("--Nu", type = float, help = "Matern Nu", default = 2.5)
parser.add_argument("--DoEarthquake", help = "earthquake?", action = "store_true")
parser.add_argument("--DoBigEarthquake", help = "big earthquake?", action = "store_true")
parser.add_argument("--DoSmoothing", help = "smoohting?", action = "store_true")
parser.add_argument("--Model", choices = ["Matter", "LBT", "MatterLBT1", "MatterLBT2"])
parser.add_argument("--KernelChoice", choices = ["Matern", "MaternNoise", "RBF"], default = "Matern")
parser.add_argument("--Alpha", type = float, default = 0.0)
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
subprocess.call(["python3", "-m", "src.mcmc", "--nwalkers", "500", "--nburnsteps", "1000", "1000"])
subprocess.call(["python3", "ExportPosterior.py", "--N", str(args.N), "--Nu", str(args.Nu), "--Model", args.Model, "--KernelChoice", args.KernelChoice, "--Alpha", str(args.Alpha), "--Noise", str(args.Noise), "--CovType", args.CovType])

CommandList = ["python3", "MakeBaselinePlots.py", "--N", str(args.N), "--Nu", str(args.Nu), "--Model", args.Model, "--KernelChoice", args.KernelChoice, "--Alpha", str(args.Alpha), "--Noise", str(args.Noise), "--CovType", args.CovType]
if args.DoEarthquake:
    CommandList.extend(["--DoEarthquake"])
if args.DoBigEarthquake:
    CommandList.extend(["--DoBigEarthquake"])
if args.DoSmoothing:
    CommandList.extend(["--DoSmoothing"])
subprocess.call(CommandList)



