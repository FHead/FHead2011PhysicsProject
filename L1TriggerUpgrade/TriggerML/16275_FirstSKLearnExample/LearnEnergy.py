# Import stuff
import datetime
import numpy as np
from sklearn.neural_network import MLPRegressor
from sklearn.preprocessing import StandardScaler
from matplotlib.backends.backend_pdf import PdfPages
import matplotlib.pyplot as plt

# Getting data
data = np.loadtxt('WToEnu200PU.txt')
TP = data[:,10::6]
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
pdf = PdfPages('Result.pdf')

# Loop over the layer settings we want to probe
layersizes = [(5), (10), (100), (5, 5), (10, 10), (25, 10), (100, 20), (100, 100), (5, 5, 5), (25, 10, 5), (5, 5, 5, 5)]

for layer in layersizes:
    print('Start to run with layer setting %s' % (layer,))

    # Setup the multi-layer perceptron regressor
    model = MLPRegressor(hidden_layer_sizes = layer, alpha = 1e-5, solver = 'adam', random_state = 1, max_iter = 1000)

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
        verticalalignment = 'bottom',
        transform = plt.axes().transAxes,
        fontsize = 12)
    plt.text(0.98, 0.05, 'Layer setting = %s' % (model.hidden_layer_sizes,),
        horizontalalignment = 'right',
        verticalalignment = 'bottom',
        transform = plt.axes().transAxes,
        fontsize = 12)
    pdf.savefig()
    plt.close()

info = pdf.infodict()
info['Title'] = 'MLP exercise'
info['Author'] = 'FHead'
info['Subject'] = 'MLP exercise on ecal TP data'
info['Keywords'] = ''
info['CreationDate'] = datetime.datetime.today()
info['ModDate'] = datetime.datetime.today()

pdf.close()



