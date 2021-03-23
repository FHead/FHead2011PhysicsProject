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
parser.add_argument("--Alpha", type = float, default = 0.0)
parser.add_argument("--Noise", type = float, default = -1)
parser.add_argument("--CovType", help = "what kind of error treatment", default = "Length0.2", choices = ["Length0.1", "Length0.2", "Length10", "Separated", "Separated10"])
parser.add_argument("--Data", choices = ["All", "LHC", "RHIC"], default = "All")
args = parser.parse_args()

if args.DoEarthquake == True:
    subprocess.call(["python3", "SetupData.py", "--CovType", args.CovType, "--Model", args.Model, "--N", str(args.N), "--DoEarthquake", "--Data", args.Data])
elif args.DoBigEarthquake == True:
    subprocess.call(["python3", "SetupData.py", "--CovType", args.CovType, "--Model", args.Model, "--N", str(args.N), "--DoBigEarthquake", "--Data", args.Data])
elif args.DoSmoothing == True:
    subprocess.call(["python3", "SetupData.py", "--CovType", args.CovType, "--Model", args.Model, "--N", str(args.N), "--DoSmoothing", "--Data", args.Data])
else:
    subprocess.call(["python3", "SetupData.py", "--CovType", args.CovType, "--Model", args.Model, "--N", str(args.N), "--Data", args.Data])
subprocess.call(["python3", "CleanPastFiles.py"])
subprocess.call(["python3", "-m", "src.emulator", "--retrain", "--npc", "3", "--nrestarts", "50", "--nu", str(args.Nu), "--kernelchoice", args.KernelChoice, "--alpha", str(args.Alpha), "--noise", str(args.Noise)])
subprocess.call(["python3", "-m", "src.mcmc", "--nwalkers", "500", "--nburnsteps", "1000", "1000", "--likelihood_type", "0", "--model_cov_factor", "1"])
subprocess.call(["python3", "ExportPosterior.py", "--N", str(args.N), "--Nu", str(args.Nu), "--Model", args.Model, "--KernelChoice", args.KernelChoice, "--Alpha", str(args.Alpha), "--Noise", str(args.Noise), "--CovType", args.CovType, "--Data", args.Data])

CommandList = ["python3", "MakeBaselinePlots.py", "--N", str(args.N), "--Nu", str(args.Nu), "--Model", args.Model, "--KernelChoice", args.KernelChoice, "--Alpha", str(args.Alpha), "--Noise", str(args.Noise), "--CovType", args.CovType, "--Data", args.Data]
if args.DoEarthquake:
    CommandList.extend(["--DoEarthquake"])
if args.DoBigEarthquake:
    CommandList.extend(["--DoBigEarthquake"])
if args.DoSmoothing:
    CommandList.extend(["--DoSmoothing"])
subprocess.call(CommandList)

from datetime import datetime
now = datetime.now()

FileName = "pickle/Result" + "_" + args.Model
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

from shutil import copyfile
copyfile('result.p', FileName + ".p")
if args.Data == "RHIC" or args.Data == "All":
    copyfile('cache/emulator/AuAu200.pkl', FileName + "_AuAu200.pkl")
if args.Data == "LHC" or args.Data == "All":
    copyfile('cache/emulator/PbPb2760.pkl', FileName + "_PbPb2760.pkl")
    copyfile('cache/emulator/PbPb5020.pkl', FileName + "_PbPb5020.pkl")


