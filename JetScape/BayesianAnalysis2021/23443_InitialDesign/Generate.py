#!/use/bin/python3
import sys, getopt
import lhsmdu
import numpy as np

def main(argv):

    RandomSeed          = 31426
    Dimension           = 5
    SamplesPerDimension = 8
    ParameterName       = ['A', 'B', 'C', 'D', 'E']
    Scale               = ['Linear', 'Linear', 'Log', 'Linear', 'Linear']
    Min                 = [0, 1, 2, 3, 2]
    Max                 = [3, 5, 6, 7, 6]
    OutputFile          = "DefaultLHS.data"
    Mode                = -1
    HeaderLine          = "Default test file"

    opts, args = getopt.getopt(argv, "hsom", ["help", "seed=", "output=", "mode="])
    for opt, arg in opts:
        if opt in ('-h', "--help"):
            PrintHelp()
            sys.exit()
        elif opt in ("-s", "--seed"):
            RandomSeed = int(arg)
        elif opt in ("-o", "--output"):
            OutputFile = arg
        elif opt in ("-m", "--mode"):
            Mode = int(arg)

    if Mode == 1:
        Dimension           = 6
        SamplesPerDimension = 10
        ParameterName       = ['AlphaS', 'Q0',     'C1',       'C2',        'Tau0',    'C3']
        Scale               = ['Linear', 'Linear', 'Log',       'Log',       'Linear', 'Log']
        Min                 = [0.1,      1,        np.exp(-5),  np.exp(-5),  0.0,      np.exp(-3)]
        Max                 = [0.5,      10,       10,          10,          1.5,      100]
        HeaderLine          = "Version 1.0\n- Intial design point for exponential PDF"
    if Mode == 2:
        Dimension           = 7
        SamplesPerDimension = 10
        ParameterName       = ['AlphaS', 'Q0',     'C1',       'C2',        'Tau0',   'A',      'B']
        Scale               = ['Linear', 'Linear', 'Log',      'Log',       'Linear', 'Linear', 'Linear']
        Min                 = [0.1,      1,        np.exp(-5), np.exp(-5),  0.0,      -10,      -10]
        Max                 = [0.5,      10,       10,         10,          1.5,      100,      100]
        HeaderLine          = "Version 1.0\n- Intial design point for binomial PDF"

    HeaderLine = HeaderLine + "\n- Number of points per dimension: " + str(SamplesPerDimension)
    HeaderLine = HeaderLine + "\n- Random Seed: " + str(RandomSeed)
    HeaderLine = HeaderLine + "\nParameter " + ' '.join(ParameterName)
    for d in range(0, Dimension):
        HeaderLine = HeaderLine + '\n- Parameter ' + ParameterName[d] + ': ' + Scale[d] + ' [' + str(Min[d]) + ', ' + str(Max[d]) + ']'

    lhsmdu.setRandomSeed(RandomSeed)
    UnitCube = np.array(lhsmdu.sample(Dimension, Dimension * SamplesPerDimension))
    LatinCube = np.zeros((Dimension, Dimension * SamplesPerDimension))

    for d in range(0, Dimension):
        if Scale[d] == 'Linear':
            LatinCube[d,:] = UnitCube[d,:] * (Max[d] - Min[d]) + Min[d]
        elif Scale[d] == 'Log':
            LatinCube[d,:] = np.exp(UnitCube[d,:] * (np.log(Max[d]) - np.log(Min[d])) + np.log(Min[d]))

    np.savetxt(OutputFile, LatinCube.T, header = HeaderLine)

def PrintHelp():
    print('This script generates Latin-Hypercube for JETSCAPE STAT 2021 initial design')
    print('Options:')
    print('   -h --help   help')
    print('   -s --seed   RandomSeed')
    print('   -o --output OutputFileName')
    print('   -m --mode   Mode')

if __name__ == "__main__":
   main(sys.argv[1:])


