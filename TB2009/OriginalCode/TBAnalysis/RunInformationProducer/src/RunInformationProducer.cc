// -*- C++ -*-
//
// Package:    RunInformationProducer
// Class:      RunInformationProducer
// 
/**\class RunInformationProducer RunInformationProducer.cc TBAnalysis/RunInformationProducer/src/RunInformationProducer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Yi Chen
//         Created:  Thu Jul 30 10:50:56 CEST 2009
// $Id$
//
//


// system include files
#include <memory>
#include <fstream>
#include <algorithm>
#include <cmath>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "TBAnalysis/RunInformation/interface/RunInformation.h"
#include "TBDataFormats/HcalTBObjects/interface/HcalTBEventPosition.h"

//
// class decleration
//

class RunInformationProducer : public edm::EDProducer
{
   public:
      explicit RunInformationProducer(const edm::ParameterSet&);
      ~RunInformationProducer();

   private:
      virtual void beginJob(const edm::EventSetup&);
      virtual void produce(edm::Event&, const edm::EventSetup&);
      virtual void endJob();
      
      // ----------member data ---------------------------
      double beamEnergy;
      double wireChamberPositions[3];   // A, B, C
      double chamberBShift[2];
      double chamberCShift[2];
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
RunInformationProducer::RunInformationProducer(const edm::ParameterSet& iConfig)
{
   //register your products
   produces<RunInformation>();

   //now do what ever other initialization is needed
   wireChamberPositions[0] = iConfig.getUntrackedParameter<double>("chamberAPosition", -514);
   wireChamberPositions[1] = iConfig.getUntrackedParameter<double>("chamberBPosition", -404);
   wireChamberPositions[2] = iConfig.getUntrackedParameter<double>("chamberCPosition", -200);
   chamberBShift[0] = iConfig.getUntrackedParameter<double>("chamberBXShift", -1.67);
   chamberBShift[1] = iConfig.getUntrackedParameter<double>("chamberBYShift", 1.50);
   chamberCShift[0] = iConfig.getUntrackedParameter<double>("chamberCXShift", -1.544);
   chamberCShift[1] = iConfig.getUntrackedParameter<double>("chamberCYShift", 0.148);

   beamEnergy = iConfig.getUntrackedParameter<double>("beamEnergy", 150);
}


RunInformationProducer::~RunInformationProducer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
RunInformationProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   std::auto_ptr<RunInformation> pInfo(new RunInformation);

   pInfo->beamEnergy = beamEnergy;

   edm::Handle<HcalTBEventPosition> epos;
   iEvent.getByType(epos);

   std::vector<double> Ax;
   std::vector<double> Ay;
   std::vector<double> Bx;
   std::vector<double> By;
   std::vector<double> Cx;
   std::vector<double> Cy;

   epos->getChamberHits('A', Ax, Ay);
   epos->getChamberHits('B', Bx, By);
   epos->getChamberHits('C', Cx, Cy);

   if(Ax.size() == 1 && Ay.size() == 1 && Bx.size() == 1 && By.size() == 1 && Cx.size() == 1 && Cy.size() == 1)
   {
      double X[3] = {Ax[0], Bx[0], Cx[0]};
      double Y[3] = {Ay[0], By[0], Cy[0]};

      X[1] = X[1] + chamberBShift[0];
      X[2] = X[2] + chamberCShift[0];
      Y[1] = Y[1] + chamberBShift[1];
      Y[2] = Y[2] + chamberCShift[1];

      double SumZ = 0;
      double SumZZ = 0;
      double SumX = 0;
      double SumY = 0;
      double SumXZ = 0;
      double SumYZ = 0;

      for(int i = 0; i < 3; i++)
      {
         SumZ = SumZ + wireChamberPositions[i];
         SumZZ = SumZZ + wireChamberPositions[i] * wireChamberPositions[i];
         SumX = SumX + X[i];
         SumY = SumY + Y[i];
         SumXZ = SumXZ + X[i] * wireChamberPositions[i];
         SumYZ = SumYZ + Y[i] * wireChamberPositions[i];
      }

      double cx = (SumX * SumZZ - SumZ * SumXZ) / (3 * SumZZ - SumZ * SumZ);
      double cy = (SumY * SumZZ - SumZ * SumYZ) / (3 * SumZZ - SumZ * SumZ);

      pInfo->hitPosition[0] = cx;
      pInfo->hitPosition[1] = cy;

      double mx = (SumX - cx * 3) / SumZ;
      double my = (SumY - cy * 3) / SumZ;

      for(int i = 0; i < 3; i++)
      {
         double dx = X[i] - mx * wireChamberPositions[i] - cx;
         double dy = Y[i] - my * wireChamberPositions[i] - cy;
         pInfo->wireChamberHitsDistance2[i] = dx * dx + dy * dy;
      }

      // std::cout << cx << " " << cy << std::endl;
   }
   else
   {
      pInfo->hitPosition[0] = 0;
      pInfo->hitPosition[1] = 0;

      pInfo->wireChamberHitsDistance2[0] = -1;
      pInfo->wireChamberHitsDistance2[1] = -1;
      pInfo->wireChamberHitsDistance2[2] = -1;
   }

   iEvent.put(pInfo);
}

// ------------ method called once each job just before starting event loop  ------------
void 
RunInformationProducer::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
RunInformationProducer::endJob()
{
}

//define this as a plug-in
DEFINE_FWK_MODULE(RunInformationProducer);
