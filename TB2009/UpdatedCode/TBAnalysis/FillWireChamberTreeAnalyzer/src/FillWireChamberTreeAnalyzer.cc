// -*- C++ -*-
//
// Package:    FillWireChamberTreeAnalyzer
// Class:      FillWireChamberTreeAnalyzer
// 
/**\class FillWireChamberTreeAnalyzer FillWireChamberTreeAnalyzer.cc TBAnalysis/FillWireChamberTreeAnalyzer/src/FillWireChamberTreeAnalyzer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Yi Chen
//         Created:  Thu Jul 30 14:48:51 CEST 2009
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

#include "TBDataFormats/HcalTBObjects/interface/HcalTBTriggerData.h"
#include "TBDataFormats/HcalTBObjects/interface/HcalTBBeamCounters.h"
#include "TBDataFormats/HcalTBObjects/interface/HcalTBEventPosition.h"
#include "TBDataFormats/HcalTBObjects/interface/HcalTBTiming.h"

#include "TNtuple.h"
#include "TFile.h"

//
// class decleration
//

class FillWireChamberTreeAnalyzer : public edm::EDAnalyzer
{
   public:
      explicit FillWireChamberTreeAnalyzer(const edm::ParameterSet&);
      ~FillWireChamberTreeAnalyzer();


   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      // ----------member data ---------------------------
      TNtuple *dataTree;
      TFile *outputFile;
      int eventnum;
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
FillWireChamberTreeAnalyzer::FillWireChamberTreeAnalyzer(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
   std::string outputFileName = iConfig.getUntrackedParameter<std::string>("output", "WireChamberTree.root");
   outputFile = new TFile(outputFileName.c_str(), "RECREATE");

   dataTree = new TNtuple("WireChamberTree", "Wire chamber information", "event:S1adc:S2adc:S3adc:S4adc:Ax:Ay:Bx:By:Cx:Cy:Dx:Dy:Ex:Ey:Ax0:Ay0:Bx0:By0:Cx0:Cy0:Dx0:Dy0:Ex0:Ey0:Trigger:TOF1S:TOF1J:TOF2S:TOF2J:BH1:BH2:BH3:BH4:VMF:VMB:VM1:VM2:VM3:VM4:VM5:VM6:VM7:VM8:CK1:CK2:CK3:TableEta:TablePhi");

   eventnum = 0;
}


FillWireChamberTreeAnalyzer::~FillWireChamberTreeAnalyzer()
{
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)
   delete dataTree;
   delete outputFile;
}


//
// member functions
//

// ------------ method called to for each event  ------------
void
FillWireChamberTreeAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   // edm Handles to get stuff from event
   edm::Handle<HcalTBTriggerData> trigger;
   edm::Handle<HcalTBBeamCounters> qadc;
   edm::Handle<HcalTBEventPosition> epos;
   edm::Handle<HcalTBTiming> time;

   iEvent.getByType(trigger);
   iEvent.getByType(qadc);
   iEvent.getByType(epos);
   iEvent.getByType(time);

   // vectors that store the x and y positions of hits (chambers A~E)
   std::vector<double> Ax;
   std::vector<double> Ay;
   std::vector<double> Bx;
   std::vector<double> By;
   std::vector<double> Cx;
   std::vector<double> Cy;
   std::vector<double> Dx;
   std::vector<double> Dy;
   std::vector<double> Ex;
   std::vector<double> Ey;

   epos->getChamberHits('A', Ax, Ay);
   epos->getChamberHits('B', Bx, By);
   epos->getChamberHits('C', Cx, Cy);
   epos->getChamberHits('D', Dx, Dy);
   epos->getChamberHits('E', Ex, Ey);

   // export trigger type...it might be useful?
   float trigger_type = 0;   // default
   if(trigger->wasBeamTrigger() == true)
      trigger_type = 1;   // beam
   if(trigger->wasOutSpillPedestalTrigger() == true)
      trigger_type = 2;   // pedestal

   // array to be put in the ntuple
   float data[49] = {0};
   data[0] = eventnum;

   // trigger scintillator information!
   data[1] = qadc->S1adc();
   data[2] = qadc->S2adc();
   data[3] = qadc->S3adc();
   data[4] = qadc->S4adc();

   // how many hits are there in the x & y hits of the chambers?
   data[5] = Ax.size();
   data[6] = Ay.size();
   data[7] = Bx.size();
   data[8] = By.size();
   data[9] = Cx.size();
   data[10] = Cy.size();
   data[11] = Dx.size();
   data[12] = Dy.size();
   data[13] = Ex.size();
   data[14] = Ey.size();

   // export only the first one, since the efficiency (ref. Dinko et. al.)
   //    of the wire chambers are high.  If I need to, I'll update this
   //    ntuple exporter....

   if(Ax.size() > 0)
      data[15] = Ax[0];
   else
      data[15] = 0;

   if(Ay.size() > 0)
      data[16] = Ay[0];
   else
      data[16] = 0;

   if(Bx.size() > 0)
      data[17] = Bx[0];
   else
      data[17] = 0;

   if(By.size() > 0)
      data[18] = By[0];
   else
      data[18] = 0;

   if(Cx.size() > 0)
      data[19] = Cx[0];
   else
      data[19] = 0;

   if(Cy.size() > 0)
      data[20] = Cy[0];
   else
      data[20] = 0;

   if(Dx.size() > 0)
      data[21] = Dx[0];
   else
      data[21] = 0;

   if(Dy.size() > 0)
      data[22] = Dy[0];
   else
      data[22] = 0;

   if(Ex.size() > 0)
      data[23] = Ex[0];
   else
      data[23] = 0;

   if(Ey.size() > 0)
      data[24] = Ey[0];
   else
      data[24] = 0;

   data[25] = trigger_type;

   // time of flight....is this installed??
   data[26] = time->TOF1Stime();
   data[27] = time->TOF1Jtime();
   data[28] = time->TOF2Stime();
   data[29] = time->TOF2Jtime();

   // beam halo detectors! right, left, up, down
   data[30] = qadc->BH1adc();
   data[31] = qadc->BH2adc();
   data[32] = qadc->BH3adc();
   data[33] = qadc->BH4adc();

   // Muon veto informations
   data[34] = qadc->VMFadc();
   data[35] = qadc->VMBadc();
   data[36] = qadc->VM1adc();
   data[37] = qadc->VM2adc();
   data[38] = qadc->VM3adc();
   data[39] = qadc->VM4adc();
   data[40] = qadc->VM5adc();
   data[41] = qadc->VM6adc();
   data[42] = qadc->VM7adc();
   data[43] = qadc->VM8adc();

   // cherenkov light detectors - not installed
   data[44] = qadc->CK1adc();
   data[45] = qadc->CK2adc();
   data[46] = qadc->CK3adc();

   // table positions....not installed?
   data[47] = epos->hbheTableEta();
   data[48] = epos->hbheTablePhi();

   dataTree->Fill(data);

   eventnum = eventnum + 1;
}


// ------------ method called once each job just before starting event loop  ------------
void 
FillWireChamberTreeAnalyzer::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
FillWireChamberTreeAnalyzer::endJob()
{
   outputFile->cd();
   dataTree->Write();
}

//define this as a plug-in
DEFINE_FWK_MODULE(FillWireChamberTreeAnalyzer);
