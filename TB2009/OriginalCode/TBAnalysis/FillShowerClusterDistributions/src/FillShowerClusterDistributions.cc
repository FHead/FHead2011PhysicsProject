// -*- C++ -*-
//
// Package:    FillShowerClusterDistributions
// Class:      FillShowerClusterDistributions
// 
/**\class FillShowerClusterDistributions FillShowerClusterDistributions.cc TBAnalysis/FillShowerClusterDistributions/src/FillShowerClusterDistributions.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Yi Chen
//         Created:  Tue Aug 18 17:18:41 CEST 2009
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "TBAnalysis/ShowerCluster/interface/ShowerCluster.h"
// #include "TBDataFormats/HcalTBObjects/interface/HcalTBVLSBData.h"
// #include "TBAnalysis/VLSBInformatin/interface/VLSBInformation.h"

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TNtuple.h"

//
// class decleration
//

class FillShowerClusterDistributions : public edm::EDAnalyzer
{
   public:
      explicit FillShowerClusterDistributions(const edm::ParameterSet&);
      ~FillShowerClusterDistributions();


   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      // ----------member data ---------------------------
      TFile *outputFile;
      TH1D *clusterNumberHistogram;
      TH1D *firstClusterDepthHistogram;
      TH1D *firstClusterEnergyHistogram;
      TH1D *leadingClusterEnergyHistogram;
      TH1D *depthRmsHistogram;
      TH1D *timeRmsHistogram;
      TH2D *depthRmsVsEnergy;
      TH2D *firstClusterDepthRmsVsEnergy;
      TH2D *firstClusterDepthVsEnergy;
      bool fillNtuple;
      TNtuple *allclusters;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
FillShowerClusterDistributions::FillShowerClusterDistributions(const edm::ParameterSet& iConfig)
{
   std::string outputFileName = iConfig.getUntrackedParameter<std::string>("output", "ClusterInfo.root");
   outputFile = new TFile(outputFileName.c_str(), "RECREATE");

   double factor = iConfig.getUntrackedParameter<double>("factor", 1);

   clusterNumberHistogram = new TH1D("NumberOfClusters", "Number of clusters;Number;Count", 11, -0.5, 10.5);
   firstClusterDepthHistogram = new TH1D("FirstClusterDepth", "Depth of first cluster", 256, -0.5, 15.5);
   firstClusterEnergyHistogram = new TH1D("FirstClusterEnergy", "Energy of first cluster", 600, -1, 60 * factor - 1);
   leadingClusterEnergyHistogram = new TH1D("LeadingClusterEnergy", "Energy of leading cluster", 600, -1, 60 * factor - 1);
   depthRmsHistogram = new TH1D("DepthRms", "RMS of cluster in depth direction", 200, -0.1, 4.9);
   timeRmsHistogram = new TH1D("TimeRms", "Spread of the cluster in time direction", 100, -0.5, 31.5);
   depthRmsVsEnergy = new TH2D("DepthRmsVsEnergy", "Spread in depth vs. energy", 200, -0.1, 4.9, 300, -1, 30 * factor - 1);
   firstClusterDepthRmsVsEnergy = new TH2D("FirstClusterDepthRmsVsEnergy", "Spread in depth vs. energy of first cluster", 200, -0.1, 4.9, 300, -1, 30 * factor - 1);
   firstClusterDepthVsEnergy = new TH2D("FirstClusterDepthVsEnergy", "Depth vs. energy of first cluster", 256, -0.5, 15.5, 300, -1, 30 * factor - 1);

   fillNtuple = iConfig.getUntrackedParameter<bool>("ntuple", false);
   allclusters = new TNtuple("AllClusters", "AllClusters", "EventNum:DepthIndex:ClusterIndex:Energy:Depth:DepthRms:Time:TimeRms:RemainingEnergy");
}


FillShowerClusterDistributions::~FillShowerClusterDistributions()
{
   delete allclusters;

   delete firstClusterDepthVsEnergy;
   delete firstClusterDepthRmsVsEnergy;
   delete depthRmsVsEnergy;
   delete timeRmsHistogram;
   delete depthRmsHistogram;
   delete leadingClusterEnergyHistogram;
   delete firstClusterEnergyHistogram;
   delete firstClusterDepthHistogram;
   delete clusterNumberHistogram;

   delete outputFile;
}


//
// member functions
//

// ------------ method called to for each event  ------------
void
FillShowerClusterDistributions::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   edm::Handle<std::vector<ShowerCluster> > hClusters;
   iEvent.getByType(hClusters);

   if(hClusters->size() > 0)
   {
      int mindepthindex = 0;
      for(int iCluster = 1; iCluster < (int)hClusters->size(); iCluster++)
         if(hClusters->at(mindepthindex).depth > hClusters->at(iCluster).depth)
            mindepthindex = iCluster;
      firstClusterDepthHistogram->Fill(hClusters->at(mindepthindex).depth);
      firstClusterEnergyHistogram->Fill(hClusters->at(mindepthindex).energy);
      firstClusterDepthRmsVsEnergy->Fill(hClusters->at(mindepthindex).depth_rms, hClusters->at(mindepthindex).energy);
      firstClusterDepthVsEnergy->Fill(hClusters->at(mindepthindex).depth, hClusters->at(mindepthindex).energy);

      int maxenergyindex = 0;
      for(int iCluster = 1; iCluster < (int)hClusters->size(); iCluster++)
         if(hClusters->at(maxenergyindex).energy < hClusters->at(iCluster).energy)
            maxenergyindex = iCluster;
      leadingClusterEnergyHistogram->Fill(hClusters->at(maxenergyindex).energy);

      for(int iCluster = 0; iCluster < (int)hClusters->size(); iCluster++)
      {
         timeRmsHistogram->Fill(hClusters->at(iCluster).time_rms);
         depthRmsHistogram->Fill(hClusters->at(iCluster).depth_rms);
         depthRmsVsEnergy->Fill(hClusters->at(iCluster).depth_rms, hClusters->at(iCluster).energy);
      }
   }

   clusterNumberHistogram->Fill(hClusters->size());

   if(fillNtuple == true)
   {
      std::map<double, int> depthVsClusters;
      for(int iCluster = 0; iCluster < (int)hClusters->size(); iCluster++)
         depthVsClusters.insert(std::pair<double, int>(hClusters->at(iCluster).depth, iCluster));

      int depthindex = 0;
      std::map<int, int> clusterDepthIndex;
      for(std::map<double, int>::iterator iter = depthVsClusters.begin(); iter != depthVsClusters.end(); iter++)
      {
         clusterDepthIndex.insert(std::pair<int, int>(iter->second, depthindex));
         depthindex = depthindex + 1;
      }

      int eventnum = iEvent.id().event();
      for(int iCluster = 0; iCluster < (int)hClusters->size(); iCluster++)
         allclusters->Fill(eventnum, clusterDepthIndex[iCluster], iCluster, hClusters->at(iCluster).energy,
            hClusters->at(iCluster).depth, hClusters->at(iCluster).depth_rms,
            hClusters->at(iCluster).time, hClusters->at(iCluster).time_rms,
            hClusters->at(iCluster).remaining_energy);
   }
}


// ------------ method called once each job just before starting event loop  ------------
void 
FillShowerClusterDistributions::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
FillShowerClusterDistributions::endJob()
{
   outputFile->cd();

   if(fillNtuple == true)
      allclusters->Write();

   clusterNumberHistogram->Write();
   firstClusterDepthHistogram->Write();
   firstClusterEnergyHistogram->Write();
   leadingClusterEnergyHistogram->Write();
   depthRmsHistogram->Write();
   timeRmsHistogram->Write();
   depthRmsVsEnergy->Write();
   firstClusterDepthRmsVsEnergy->Write();
   firstClusterDepthVsEnergy->Write();
}

//define this as a plug-in
DEFINE_FWK_MODULE(FillShowerClusterDistributions);
