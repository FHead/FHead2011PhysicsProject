import argparse
import subprocess

parser = argparse.ArgumentParser()
parser.add_argument("--N", type = int, help = "hold out index", default = 0)
parser.add_argument("--ModelCov", type = float, help = "model covariance", default = 1)
parser.add_argument("--LikelihoodType", type = int, help = "type of likelihood", default = 0)
parser.add_argument("--CorrLength", type = float, help = "correlation length", default = 0.1)
parser.add_argument("--Tag", help = "Extra tag", default = "")
parser.add_argument("--Nu", help = "Nu", type = float, default = 2.5)
args = parser.parse_args()

subprocess.call(["python3", "SetupLBT.py", "--N", str(args.N), "--CorrLength", str(args.CorrLength)])
subprocess.call(["python3", "CleanPastFiles.py"])
subprocess.call(["python3", "-m", "src.emulator", "--retrain", "--npc", "3", "--nrestarts", "50", "--nu", str(args.Nu)])
subprocess.call(["python3", "-m", "src.mcmc", "--nwalkers", "500", "--nburnsteps", "2000", "--model_cov_factor", str(args.ModelCov), "--likelihood_type", str(args.LikelihoodType), "1000"])
subprocess.call(["python3", "MakeBaselinePlots.py", "--N", str(args.N), "--Tag", args.Tag])
subprocess.call(["python3", "ExportPosterior.py", "--N", str(args.N), "--Tag", args.Tag])




