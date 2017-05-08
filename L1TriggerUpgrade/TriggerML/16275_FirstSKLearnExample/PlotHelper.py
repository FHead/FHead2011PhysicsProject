from matplotlib.backends.backend_pdf import PdfPages
import matplotlib.pyplot as plt
import datetime

class PdfFileHelper:

    pdf = 'NONE'
    pagecount = 0

    def Initialize(self, filename: str):
        if type(self.pdf) == str:
            self.pdf = PdfPages(filename)
            self.pagecount = 0

    def CleanUp(self):
        if type(self.pdf) == PdfPages:
            info = self.pdf.infodict()
            info['Title'] = 'MLP exercise'
            info['Author'] = 'FHead'
            info['Subject'] = 'MLP exercise on ecal TP data'
            info['Keywords'] = ''
            info['CreationDate'] = datetime.datetime.today()
            info['ModDate'] = datetime.datetime.today()

            self.pdf.close()
            self.pagecount = 0

    def Close(self):
        self.CleanUp()

    def AddPage(self):
        self.pagecount = self.pagecount + 1;
        if self.pagecount != 1:
            plt.annotate("%d" % self.pagecount,
                xy = (0.99, 0.01),
                horizontalalignment = 'right',
                verticalalignment = 'baseline',
                xycoords = 'figure fraction')
        self.pdf.savefig()

    def AddTimeStampPage(self):
        plt.figure(figsize = (10, 10))
        plt.annotate('Generated on',
            xy = (0.50, 0.55),
            horizontalalignment = 'center',
            verticalalignment = 'center',
            xycoords = 'figure fraction',
            fontsize = 36)
        plt.annotate(datetime.datetime.today(),
            xy = (0.50, 0.45),
            horizontalalignment = 'center',
            verticalalignment = 'center',
            xycoords = 'figure fraction',
            fontsize = 36)
        plt.axis('off')
        self.AddPage()
        plt.close()


    def __init__(self, filename: str):
        self.Initialize(filename)

