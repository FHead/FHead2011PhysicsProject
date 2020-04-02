import argparse
import subprocess

parser = argparse.ArgumentParser()
parser.add_argument("--N", type = int, help = "hold out index", default = 0)
args = parser.parse_args()

import src.reader as Reader

RawDesignL   = Reader.ReadDesign('input/LBTJake/Design.dat')
MaxN         = RawDesignL["Design"].shape[0]

for N in range(0, MaxN):
    print("Executing", N, "/", MaxN)
    subprocess.call(["python3", "RunOne.py", "--N", str(N)])

subprocess.call(["python3", "RunOne.py", "--N", "-1"])
subprocess.call(["python3", "Profit.py"])


