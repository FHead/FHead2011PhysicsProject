import argparse
import subprocess

parser = argparse.ArgumentParser()
parser.add_argument("--N", type = int, help = "hold out index", default = 0)
args = parser.parse_args()

subprocess.call(["python3", "SetupLBT.py", "--N", str(args.N)])
subprocess.call(["python3", "CleanPastFiles.py"])
subprocess.call(["python3", "-m", "src.emulator", "--retrain", "--npc", "3", "--nrestarts", "50", "--nu", "2.5"])
subprocess.call(["python3", "-m", "src.mcmc", "--nwalkers", "500", "--nburnsteps", "1000", "1000"])
subprocess.call(["python3", "MakeBaselinePlots.py", "--N", str(args.N)])
subprocess.call(["python3", "ExportPosterior.py", "--N", str(args.N)])




