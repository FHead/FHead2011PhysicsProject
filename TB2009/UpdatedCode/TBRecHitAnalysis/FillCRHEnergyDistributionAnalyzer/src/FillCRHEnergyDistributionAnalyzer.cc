// -*- C++ -*-
//
// Package:    FillCRHEnergyDistributionAnalyzer
// Class:      FillCRHEnergyDistributionAnalyzer
// 
/**\class FillCRHEnergyDistributionAnalyzer FillCRHEnergyDistributionAnalyzer.cc TBRecHitAnalysis/FillCRHEnergyDistributionAnalyzer/src/FillCRHEnergyDistributionAnalyzer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Yi Chen
//         Created:  Mon Aug 10 14:05:48 CEST 2009
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

#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"
#include "DataFormats/HcalDigi/interface/HcalDigiCollections.h"

#include <fstream>
#include <map>

#include "TFile.h"
#include "TH1D.h"

//
// class decleration
//

class FillCRHEnergyDistributionAnalyzer : public edm::EDAnalyzer
{
   public:
      explicit FillCRHEnergyDistributionAnalyzer(const edm::ParameterSet&);
      ~FillCRHEnergyDistributionAnalyzer();


   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      // ----------member data ---------------------------
      std::string module;

      TFile *outputFile;
      TH1D *totalEnergy;
      TH1D *centralTowerPercentage;
      TH1D *centralStripPercentage;
      TH1D *centralStripEta89Percentage;
      TH1D *towerEnergy[3][3];   // iphi = 2, 3, 4; ieta = 2, 3, 4
      TH1D *layergroupEnergy[3][3][16];   // vlsb: use up all 16 layergroups; normal: only 4 layergroups

      std::map<int, double> interCalibrationConstants;
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
FillCRHEnergyDistributionAnalyzer::FillCRHEnergyDistributionAnalyzer(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed
   module = iConfig.getUntrackedParameter<std::string>("module", "");

   std::string outputFileName = iConfig.getUntrackedParameter<std::string>("output", "EnergyDistribution.root");
   outputFile = new TFile(outputFileName.c_str(), "RECREATE");

   totalEnergy = new TH1D("TotalEnergy", "Total energy in 3x3 towers", 3000, -50, 3500);
   centralTowerPercentage = new TH1D("CentralTowerPercentage", "Percentage of energy in central tower",
      202, 0, 1.01);
   centralStripPercentage = new TH1D("CentralStripPercentage", "Percentage of energy in central strip (iphi = 3)", 202, 0, 1.01);
   centralStripEta89Percentage = new TH1D("CentralStripEta89Percentage", "Percentage of energy in two towers (iphi = 3, ieta = 8, 9)", 202, 0, 1.01);

   for(int iPhiIndex = 0; iPhiIndex < 3; iPhiIndex++)
   {
      for(int iEtaIndex = 0; iEtaIndex < 3; iEtaIndex++)
      {
         TString name = Form("TowerEnergy_iphi%d_ieta%d", iPhiIndex + 2, iEtaIndex + 7);
         TString title = Form("Energy of whole tower (iphi %d, ieta %d)", iPhiIndex + 2, iEtaIndex + 7);
         towerEnergy[iPhiIndex][iEtaIndex] = new TH1D(name, title, 3000, -50, 1450);

         for(int iLayerGroup = 0; iLayerGroup < 16; iLayerGroup++)
         {
            if(iPhiIndex != 1 && iLayerGroup >= 4)   // normal readout
            {
               layergroupEnergy[iPhiIndex][iEtaIndex][iLayerGroup] = NULL;
               continue;
            }

            name = Form("ChannelEnergy_iphi%d_ieta%d_layergroup%d", iPhiIndex + 2, iEtaIndex + 7, iLayerGroup);
            title = Form("Energy of layer group %d (iphi %d, ieta %d)", iLayerGroup, iPhiIndex + 2, iEtaIndex + 7);

            layergroupEnergy[iPhiIndex][iEtaIndex][iLayerGroup] = new TH1D(name, title, 2630, -10, 290);
         }
      }
   }

   std::string calibrationFileName = iConfig.getUntrackedParameter<std::string>("calibration", "");

   std::ifstream in(calibrationFileName.c_str());

   while(in)
   {
      int eta = 0;
      int phi = 0;
      double constant = 0;

      in >> phi >> eta >> constant;

      interCalibrationConstants.insert(std::pair<int, double>(eta * 100 + phi, constant));
   }

   in.close();
}


FillCRHEnergyDistributionAnalyzer::~FillCRHEnergyDistributionAnalyzer()
{
   for(int iPhiIndex = 0; iPhiIndex < 3; iPhiIndex++)
      for(int iEtaIndex = 0; iEtaIndex < 3; iEtaIndex++)
         for(int iLayerGroup = 0; iLayerGroup < 16; iLayerGroup++)
            if(layergroupEnergy[iPhiIndex][iEtaIndex][iLayerGroup] != NULL)
               delete layergroupEnergy[iPhiIndex][iEtaIndex][iLayerGroup];

   for(int iPhiIndex = 0; iPhiIndex < 3; iPhiIndex++)
      for(int iEtaIndex = 0; iEtaIndex < 3; iEtaIndex++)
         delete towerEnergy[iPhiIndex][iEtaIndex];

   delete centralStripEta89Percentage;
   delete centralStripPercentage;
   delete centralTowerPercentage;
   delete totalEnergy;

   delete outputFile;
}


//
// member functions
//

// ------------ method called to for each event  ------------
void
FillCRHEnergyDistributionAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   double totalenergy = 0;
   double centraltower = 0;
   double centralstrip = 0;
   double centralstripEta89 = 0;

   if(module.size() != 0)
   {
      edm::Handle<HBHERecHitCollection> hData;
      iEvent.getByLabel(module, hData);

      double towerenergy[3][3] = {{0}};

      for(HBHERecHitCollection::const_iterator iter = hData->begin(); iter != hData->end(); iter++)
      {
         double energy = iter->energy();

         if(interCalibrationConstants.find(iter->id().ieta() * 100 + iter->id().iphi()) != interCalibrationConstants.end())
            energy = energy * interCalibrationConstants[iter->id().ieta()*100+iter->id().iphi()];

         int ieta = iter->id().ieta();

         int iphi = iter->id().iphi();
         int layergroup = 0;

         if(iphi >= 50)
         {
            layergroup = iphi - 50;
            iphi = 3;
         }
         else
         {
            layergroup = iphi / 10 - 1;
            iphi = iphi % 10;
         }

         if(iphi < 2 || iphi > 4)   // not of interest to us
            continue;
         if(ieta < 7 || ieta > 9)   // not of interest to us
            continue;
         if(iphi == 3 && (layergroup >= 16 || layergroup < 0))
            continue;
         if(iphi != 3 && (layergroup >= 4 || layergroup < 0))
            continue;

         if(ieta == 8 && iphi == 3)
            centraltower = centraltower + energy;
         if((ieta == 8 || ieta == 9) && iphi == 3)
            centralstripEta89 = centralstripEta89 + energy;
         if(iphi == 3)
            centralstrip = centralstrip + energy;

         int iPhiIndex = iphi - 2;
         int iEtaIndex = ieta - 7;

         totalenergy = totalenergy + energy;
         towerenergy[iPhiIndex][iEtaIndex] = towerenergy[iPhiIndex][iEtaIndex] + energy;
         layergroupEnergy[iPhiIndex][iEtaIndex][layergroup]->Fill(energy);
      }

      for(int iPhiIndex = 0; iPhiIndex < 3; iPhiIndex++)
         for(int iEtaIndex = 0; iEtaIndex < 3; iEtaIndex++)
            towerEnergy[iPhiIndex][iEtaIndex]->Fill(towerenergy[iPhiIndex][iEtaIndex]);
   }

   totalEnergy->Fill(totalenergy);
   centralTowerPercentage->Fill(centraltower / totalenergy);
   centralStripPercentage->Fill(centralstrip / totalenergy);
   centralStripEta89Percentage->Fill(centralstripEta89 / totalenergy);
}


// ------------ method called once each job just before starting event loop  ------------
void 
FillCRHEnergyDistributionAnalyzer::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
FillCRHEnergyDistributionAnalyzer::endJob()
{
   outputFile->cd();

   totalEnergy->Write();

   centralTowerPercentage->Write();
   centralStripPercentage->Write();
   centralStripEta89Percentage->Write();

   for(int iPhiIndex = 0; iPhiIndex < 3; iPhiIndex++)
      for(int iEtaIndex = 0; iEtaIndex < 3; iEtaIndex++)
         towerEnergy[iPhiIndex][iEtaIndex]->Write();

   for(int iPhiIndex = 0; iPhiIndex < 3; iPhiIndex++)
      for(int iEtaIndex = 0; iEtaIndex < 3; iEtaIndex++)
         for(int iLayerGroup = 0; iLayerGroup < 16; iLayerGroup++)
            if(layergroupEnergy[iPhiIndex][iEtaIndex][iLayerGroup] != NULL)
               layergroupEnergy[iPhiIndex][iEtaIndex][iLayerGroup]->Write();
}

//define this as a plug-in
DEFINE_FWK_MODULE(FillCRHEnergyDistributionAnalyzer);
