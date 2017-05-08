# Import stuff
import sys
import datetime
import numpy as np
from sklearn.neural_network import MLPRegressor
from sklearn.preprocessing import StandardScaler
from matplotlib.backends.backend_pdf import PdfPages
import matplotlib.pyplot as plt

from PlotHelper import PdfFileHelper
import PlottingTools


# Input stuff
if len(sys.argv) != 3:
    print('Usage: python %s Tag Mode=(ECAL|WithHCAL|WithIEta|All)' % sys.argv[0])
    exit()

Tag = sys.argv[1]

Mode = sys.argv[2]
if Mode != 'ECAL' and Mode != 'WithHCAL' and Mode != 'WithIEta':
    Mode = 'All'

print('start running with tag %s and mode %s' % (Tag, Mode))

# Getting data
data = np.loadtxt('WToEnu%s.txt' % Tag)

ecal_indices = np.arange(10, 158, 6)
hcal_indices = np.arange(11, 158, 6)
ieta_indices = np.arange(8, 158, 6)

indices = ecal_indices
if Mode == 'WithHCAL':
    indices = np.concatenate((ecal_indices, hcal_indices))
if Mode == 'WithIEta':
    indices = np.concatenate((ecal_indices, ieta_indices))
if Mode == 'All':
    indices = np.concatenate((ecal_indices, hcal_indices, ieta_indices))

TP = data[:,indices]
Gen = np.ravel(data[:,0:1])
Reco = np.ravel(data[:,3:4])

# trigger primitive value of -999 means that the TP is not there - assign an energy of zero
TP[TP <= -900] = 0

# Split into training and testing sets
train_X = TP[:-4000,:]
test_X = TP[-4000:,:]
train_Y = Reco[:-4000]
test_Y = Reco[-4000:]

# Scale data to have better ML performance
scaler = StandardScaler()
scaler.fit(train_X)
train_X = scaler.transform(train_X)
test_X = scaler.transform(test_X)

# Output PDF File
# pdf = PdfPages('Result%s.pdf' % Tag)
PdfFile = PdfFileHelper('PDF/Result%s%s.pdf' % (Mode, Tag))

# Title page
plt.figure(figsize = (10, 10))
# plt.text(0.50, 0.50, 'Energy from TP (%s)' % Tag,
#     horizontalalignment = 'center',
#     verticalalignment = 'center',
#     transform = plt.axes().transAxes,
#     fontsize = 36)
plt.text(0.50, 0.50, 'Energy from TP (%s)' % Tag,
    horizontalalignment = 'center',
    verticalalignment = 'center',
    fontsize = 36)
plt.axis('off')
PdfFile.AddPage()
plt.close()

# Loop over the layer settings we want to probe
layersizes = [(5), (10), (100), (5, 5), (10, 10), (25, 10), (100, 20), (100, 100), (5, 5, 5), (25, 10, 5), (5, 5, 5, 5), (10, 10, 10, 10, 10, 10, 10, 10, 10, 10), (10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10), (5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5), (10, 9, 8, 7, 6, 5, 4), (10, 5, 10), (10, 5, 10, 5, 10), (10, 5, 10, 5, 10, 5, 10), (10, 5, 10, 5, 10, 5, 10, 5, 10)]

binning = [0, 10, 20, 30, 40, 50, 75, 100, 200]

for layer in layersizes:
    print('Start to run with layer setting %s' % (layer,))

    # Setup the multi-layer perceptron regressor
    model = MLPRegressor(hidden_layer_sizes = layer, alpha = 1e-5, solver = 'adam', random_state = 1, max_iter = 10000)

    # Drum roll
    model.fit(train_X, train_Y)

    # Check performance on test sample
    Score = model.score(test_X, test_Y)
    print("Score = %.3f" % Score)

    # Make scatter plot
    predict_test_Y = model.predict(test_X)

    plt.figure(figsize = (10, 10))
    plt.plot(test_Y, predict_test_Y, '.')
    plt.title('Predicted vs true on test sample', fontsize = 12)
    plt.xlabel('True energy (Reco)', fontsize = 12)
    plt.ylabel('Predicted', fontsize = 12)
    plt.text(0.98, 0.02, 'Score = %.3f' % Score,
        horizontalalignment = 'right',
        verticalalignment = 'baseline',
        transform = plt.axes().transAxes,
        fontsize = 12)
    plt.text(0.98, 0.05, 'Layer setting = %s' % (model.hidden_layer_sizes,),
        horizontalalignment = 'right',
        verticalalignment = 'baseline',
        transform = plt.axes().transAxes,
        fontsize = 12)

    plt.axes().set_autoscale_on(False)
    plt.plot([-100, 300], [-100, 300])

    PdfFile.AddPage()
    plt.close()

    # Mean as a function of reco energy
    PlottingTools.BinAndMean(test_Y, np.divide(predict_test_Y, test_Y), binning)

    plt.title('Mean (predicted / true) vs true on test sample', fontsize = 12)
    plt.xlabel('True energy (Reco)', fontsize = 12)
    plt.ylabel('Mean (predicted / true)', fontsize = 12)
    plt.axes().set_ylim([0.95, 1.05])

    plt.axes().set_autoscale_on(False)
    plt.plot([-1000, 1000], [1, 1])

    PdfFile.AddPage()
    plt.close()

    # RMS as a function of reco energy
    PlottingTools.BinAndRMS(test_Y, np.divide(predict_test_Y, test_Y), binning)

    plt.title('RMS (predicted / true) vs true on test sample', fontsize = 12)
    plt.xlabel('True energy (Reco)', fontsize = 12)
    plt.ylabel('RMS (predicted / true)', fontsize = 12)
    plt.axes().set_ylim([0.01, 5])

    PdfFile.AddPage()
    plt.close()



# Close file
PdfFile.AddTimeStampPage()
PdfFile.Close()

print()

