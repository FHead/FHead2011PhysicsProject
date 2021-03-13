import argparse
import subprocess

parser = argparse.ArgumentParser()
parser.add_argument("--N", type = int, help = "hold out index", default = 0)
parser.add_argument("--DoEarthquake", help = "earthquake?", action = "store_true")
parser.add_argument("--DoBigEarthquake", help = "big earthquake?", action = "store_true")
parser.add_argument("--DoSmoothing", help = "smoohting?", action = "store_true")
args = parser.parse_args()

if args.DoEarthquake == True:
    subprocess.call(["python3", "SetupMATTER.py", "--N", str(args.N), "--DoEarthquake"])
elif args.DoBigEarthquake == True:
    subprocess.call(["python3", "SetupMATTER.py", "--N", str(args.N), "--DoBigEarthquake"])
elif args.DoSmoothing == True:
    subprocess.call(["python3", "SetupMATTER.py", "--N", str(args.N), "--DoSmoothing"])
else:
    subprocess.call(["python3", "SetupMATTER.py", "--N", str(args.N)])
subprocess.call(["python3", "CleanPastFiles.py"])
subprocess.call(["python3", "-m", "src.emulator", "--retrain", "--npc", "3", "--nrestarts", "50", "--nu", "2.5"])
subprocess.call(["python3", "-m", "src.mcmc", "--nwalkers", "500", "--nburnsteps", "1000", "1000"])
subprocess.call(["python3", "MakeBaselinePlots.py", "--N", str(args.N)])
subprocess.call(["python3", "ExportPosterior.py", "--N", str(args.N)])




