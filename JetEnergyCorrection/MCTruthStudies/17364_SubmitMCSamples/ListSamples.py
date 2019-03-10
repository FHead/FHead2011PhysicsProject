Query = '/QCD_Pt*Flat*_13TeV_pythia8/RunIISummer16DR80Premix-PUMoriond17_94X_*/AODSIM'

from dbs.apis.dbsClient import DbsApi
dbs = DbsApi('https://cmsweb.cern.ch/dbs/prod/global/DBSReader')
datasets = dbs.listDatasets(dataset = Query)
outputfile = open("Samples.txt", "w")
for sample in datasets:
   outputfile.write(sample['dataset'] + '\n')
outputfile.close()

