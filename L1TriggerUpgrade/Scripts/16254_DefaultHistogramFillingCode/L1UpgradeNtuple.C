#define l1ntuple_cxx
#include "L1UpgradeNtuple.h"

double L1UpgradeNtuple::deltaPhi(double phi1, double phi2) {
  double result = phi1 - phi2;
  if(fabs(result) > 9999) return result;
  while (result > TMath::Pi()) result -= 2*TMath::Pi();
  while (result <= -TMath::Pi()) result += 2*TMath::Pi();
  return result;
}

double L1UpgradeNtuple::deltaR(double eta1, double phi1, double eta2, double phi2) {
  double deta = eta1 - eta2;
  double dphi = deltaPhi(phi1, phi2);
  return sqrt(deta*deta + dphi*dphi);
}

void L1UpgradeNtuple::testPerformance()
{ 

  if (fChain == 0)  return;
 
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  //unsigned int nevents =0;

  std::cout << nentries << " events to process"<<std::endl;

  TFile *total=new TFile("total.root","RECREATE");

  TDirectory *dirEG = total->mkdir("l1upgrade_EGamma","Histograms for upgraded EG, isoEG , TkEle, TkIsoEle objects");
  TDirectory *dirMU = total->mkdir("l1upgrade_Muons","Histograms for upgraded Muon objects");
  TDirectory *dirJET = total->mkdir("l1upgrade_Jets","Histograms for upgraded L1Jet objects");
  TDirectory *dirTAU = total->mkdir("l1upgrade_Taus","Histograms for upgraded Taus");

   // ELECTRONS
  TH1D *hUpgrade1 = new TH1D("hupgrade1","",25,0.,50.); TH1D *hUpgrade2 = new TH1D("hupgrade2","",25,0.,50.);

  TH1D *nGENele = new TH1D("ngenele","",11,-0.5,10.5);
  TH1D *nEGele = new TH1D("negele","",21,-0.5,20.5);

  TH1D *hGen = new TH1D("gelectrons","",25,0.,50.); TH1D *hGENeta = new TH1D("hgeneta","",30,-3.,3.); 
  TH1D *hEGeta = new TH1D("hegeta","",30,-3.,3.); TH1D *hisoEGeta = new TH1D("hisoegeta","",30,-3.,3.);

  TH1D *hEGgeneta = new TH1D("heggeneta","",30,-3.,3.); 
  TH1D *hisoEGgeneta = new TH1D("hisoeggeneta","",30,-3.,3.); // gen pT/eta with EG match

  TH1F *DRmin1 = new TH1F("drmin1","",100,0.,5.); TH1F *DRmin2 = new TH1F("drmin2","",100,0.,5.);
  TH2F *dPTvsdR1 = new TH2F("dptvsdr1","",100,0.,1.,100,0.,2.);
  TH2F *dPTvsdR2 = new TH2F("dptvsdr2","",100,0.,1.,100,0.,2.);

  // MUONS
  TH1D *hMUall = new TH1D("hmuall","",200,0.,200.);  TH1D *hMUalleta = new TH1D("hmualleta","",30,-3.,3.);
  TH1D *hMUgen = new TH1D("hmugen","",200,0.,200.);  TH1D *hMUgeneta = new TH1D("hmugeneta","",30,-3.,3.);

  TH1D *hMU10 =  new TH1D("hmu10","",200,0.,200.);
  TH1D *hMU20 =  new TH1D("hmu20","",200,0.,200.);
  TH1D *hMU30 =  new TH1D("hmu30","",200,0.,200.);
  TH1D *hMU40 =  new TH1D("hmu40","",200,0.,200.);
  TH1D *hMU50 =  new TH1D("hmu50","",200,0.,200.);
  
  // JETS
  TH1D *hJETgen = new TH1D("hjetgen","",100,0.,1000.);
  TH1D *hJet25 = new TH1D("hjet25","",100,0.,1000.);
  TH1D *hJet50 = new TH1D("hjet50","",100,0.,1000.);
  TH1D *hJet75 = new TH1D("hjet75","",100,0.,1000.);

  TH1D *hJet100 = new TH1D("hjet100","",100,0.,1000.);
  TH1D *hJet150 = new TH1D("hjet150","",100,0.,1000.);
  TH1D *hJet200 = new TH1D("hjet200","",100,0.,1000.);
  TH1D *hJet250 = new TH1D("hjet250","",100,0.,1000.);
  TH1D *hJet300 = new TH1D("hjet300","",100,0.,1000.);
  // TAUS
  TH1D *hTaugen = new TH1D("htaugen","",1000,0.,1000.);
  TH1D *hTau30 = new TH1D("htau30","",1000,0.,1000.);
  TH1D *hTau45 = new TH1D("htau45","",1000,0.,1000.);
  TH1D *hTau60 = new TH1D("htau60","",1000,0.,1000.);
  TH1D *hTau75 = new TH1D("htau75","",1000,0.,1000.);
  TH1D *hTau90 = new TH1D("htau90","",1000,0.,1000.);

  TH1D *hisoTaugen = new TH1D("hisotaugen","",1000,0.,1000.);
  TH1D *hIsoTau30 = new TH1D("hisotau30","",1000,0.,1000.);
  TH1D *hIsoTau45 = new TH1D("hisotau45","",1000,0.,1000.);
  TH1D *hIsoTau60 = new TH1D("hisotau60","",1000,0.,1000.);
  TH1D *hIsoTau75 = new TH1D("hisotau75","",1000,0.,1000.);
  TH1D *hIsoTau90 = new TH1D("hisotau90","",1000,0.,1000.);

  TH1D *htkTaugen = new TH1D("htktaugen","",1000,0.,1000.);
  TH1D *htkTau10 = new TH1D("htktau10","",1000,0.,1000.);
  TH1D *htkTau20 = new TH1D("htktau20","",1000,0.,1000.);
  TH1D *htkTau30 = new TH1D("htktau30","",1000,0.,1000.);
  TH1D *htkTau45 = new TH1D("htktau45","",1000,0.,1000.);
  TH1D *htkTau60 = new TH1D("htktau60","",1000,0.,1000.);
  TH1D *htkTau75 = new TH1D("htktau75","",1000,0.,1000.);
  TH1D *htkTau90 = new TH1D("htktau90","",1000,0.,1000.);

   // EGAMMA
  TH1D *hEGgen = new TH1D("heggen","",25,0.,50.);
  TH1D *hEG12 = new TH1D("heg12","",25,0.,50.);
  TH1D *hEG15 = new TH1D("heg15","",25,0.,50.);
  TH1D *hEG20 = new TH1D("heg20","",25,0.,50.);
  TH1D *hEG25 = new TH1D("heg25","",25,0.,50.);
  TH1D *hEG30 = new TH1D("heg30","",25,0.,50.);

  TH1D *hisoEGgen = new TH1D("hisoeggen","",25,0.,50.);
  TH1D *hisoEG12 = new TH1D("hisoeg12","",25,0.,50.);
  TH1D *hisoEG15 = new TH1D("hisoeg15","",25,0.,50.);
  TH1D *hisoEG20 = new TH1D("hisoeg20","",25,0.,50.);
  TH1D *hisoEG25 = new TH1D("hisoeg25","",25,0.,50.);
  TH1D *hisoEG30 = new TH1D("hisoeg30","",25,0.,50.);

  // TkElectrons
  TH1D *hTkEGgen = new TH1D("htkeggen","",25,0.,50.);
  TH1D *hTkEGgeneta = new TH1D("htkeggeneta","",30,-3.,3.);

  TH1D *hTkEG12 = new TH1D("htkeg12","",25,0.,50.);
  TH1D *hTkEG15 = new TH1D("htkeg15","",25,0.,50.);
  TH1D *hTkEG20 = new TH1D("htkeg20","",25,0.,50.);
  TH1D *hTkEG25 = new TH1D("htkeg25","",25,0.,50.);
  TH1D *hTkEG30 = new TH1D("htkeg30","",25,0.,50.);

  //TkPhotons
  TH1D *hTkEMgen = new TH1D("htkemgen","",75,5.,75.);
  TH1D *hTkEMgeneta = new TH1D("htkemgeneta","",30,-3.,3.);

  TH1D *hTkEM12 = new TH1D("htkem12","",75,5.,75.);
  TH1D *hTkEM15 = new TH1D("htkem15","",75,5.,75.);
  TH1D *hTkEM20 = new TH1D("htkem20","",75,5.,75.);
  TH1D *hTkEM25 = new TH1D("htkem25","",75,5.,75.);
  TH1D *hTkEM30 = new TH1D("htkem30","",75,5.,75.);


  TH1D *hTkIsoEGgen = new TH1D("hTkIsoeggen","",25,0.,50.);
  TH1D *hTkIsoEGgeneta = new TH1D("hTkIsoeggeneta","",30,-3.,3.);

  TH1D *hTkIsoEG12 = new TH1D("hTkIsoeg12","",25,0.,50.);
  TH1D *hTkIsoEG15 = new TH1D("hTkIsoeg15","",25,0.,50.);
  TH1D *hTkIsoEG20 = new TH1D("hTkIsoeg20","",25,0.,50.);
  TH1D *hTkIsoEG25 = new TH1D("hTkIsoeg25","",25,0.,50.);
  TH1D *hTkIsoEG30 = new TH1D("hTkIsoeg30","",25,0.,50.);

  TH1D *resEG = new TH1D("reseg","",300,-3.,3.);
  TH1D *resTkEG = new TH1D("restkeg","",300,-3.,3.);

  TH1D *resEG1 = new TH1D("reseg1","",300,-3.,3.);
  TH1D *resTkEG1 = new TH1D("restkeg1","",300,-3.,3.);
  TH1D *resEG2 = new TH1D("reseg2","",300,-3.,3.);
  TH1D *resTkEG2 = new TH1D("restkeg2","",300,-3.,3.);
  TH1D *resEG3 = new TH1D("reseg3","",300,-3.,3.);
  TH1D *resTkEG3 = new TH1D("restkeg3","",300,-3.,3.);
  TH1D *resEG4 = new TH1D("reseg4","",300,-3.,3.);
  TH1D *resTkEG4 = new TH1D("restkeg4","",300,-3.,3.);
  TH1D *resEG5 = new TH1D("reseg5","",300,-3.,3.);
  TH1D *resTkEG5 = new TH1D("restkeg5","",300,-3.,3.);

  std::map<int,double> taus;
  std::map<int,double> partons;
  std::vector<double> electrons;

  TLorentzVector photon(0.,0.,0.,0.);
  TLorentzVector electron(0.,0.,0.,0.);
  TLorentzVector muon(0.,0.,0.,0.);

  TLorentzVector tauplus(0.,0.,0.,0.); TLorentzVector tauplus_vis(0.,0.,0.,0.);
  TLorentzVector tauminus(0.,0.,0.,0.); TLorentzVector tauminus_vis(0.,0.,0.,0.);

  TLorentzVector nuplus(0.,0.,0.,0.);
  TLorentzVector numinus(0.,0.,0.,0.);

  TLorentzVector parton;
  //TLorentzVector egamma, isoegamma;
  
  for (Long64_t jentry=0; jentry<nentries;jentry++)
  {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    
    nb = fChain->GetEntry(jentry); nbytes += nb;
    /*
    std::cout << "" << std::endl;
    std::cout << "Event = " << int(jentry) << std::endl;
    */
    electrons.clear();
    partons.clear(); taus.clear();

    // genParticles (==Reference collection to efficiency studies)
    // Only pick-up the highest-pT particle - and then loop over the L1 collection to find a match in DR.
    int imu=0; int iele=0; int itau=0; int ipho=0; 
    int ptau=-1; int mtau=-1;
    
    int idp;

    for (int i=0; i<gen_->id.size(); i++) {

      //      std::cout << "Particle " << i << " has id = " << gen_->id.at(i) << " and status = " << gen_->status.at(i) << std::endl;

      // Fill electrons
      if (abs(gen_->id.at(i))==11) {
	electron.SetPxPyPzE(gen_->px.at(i),gen_->py.at(i),gen_->pz.at(i),gen_->e.at(i));
	iele++;
      }
      // Fill photons
      if (abs(gen_->id.at(i))==22) {
        photon.SetPxPyPzE(gen_->px.at(i),gen_->py.at(i),gen_->pz.at(i),gen_->e.at(i));
        ipho++;
      }

      // Fill muons 
      //  if (gen_->status.at(i)==3) { 
      if (abs(gen_->id.at(i))==13) {
	muon.SetPxPyPzE(gen_->px.at(i),gen_->py.at(i),gen_->pz.at(i),gen_->e.at(i));
	imu++;
      }
      //}

      // Fill hadronic-taus
      if (gen_->status.at(i)==3) { 
	if  (gen_->id.at(i)==15) { //  && abs(gen_->parent_id.at(i))==24) {
	  ptau=i; itau++; } // found tau+
	if  (gen_->id.at(i)==-15) { //  && abs(gen_->parent_id.at(i))==24) {
	  mtau=i; itau++; } // found tau-
      } // status 3

      // Fill partons
      idp=abs(gen_->id.at(i));
      if (gen_->status.at(i)==3) { //continue; }
	if (idp==1 || idp==2 || idp==3 || idp==4 || idp==5 || idp==21) {
	  parton.SetPxPyPzE(gen_->px.at(i),gen_->py.at(i),gen_->pz.at(i),gen_->e.at(i));
	  if (fabs(parton.Eta())<=3.) { partons[i]=parton.Pt(); }
	}
      }
    }

    // ---------------------------------------------------------------------------------------------------------------------------
    // TAU analysis

    //    if (itau==2) {
      // Exclude leptonically decayed Taus
    for (int j=0; j<gen_->id.size(); j++) {
      if  ( gen_->status.at(j)!=3 && (abs(gen_->id.at(j))==11 || abs(gen_->id.at(j))==13) && gen_->parent_id.at(j)==-15) {
	itau--; mtau=-1;  }
      if  ( gen_->status.at(j)!=3 && (abs(gen_->id.at(j))==11 || abs(gen_->id.at(j))==13) && gen_->parent_id.at(j)==15) {
	itau--; ptau=-1;  }
    } 
       // }

    if (ptau>0) {
      tauplus.SetPxPyPzE(gen_->px.at(ptau),gen_->py.at(ptau),gen_->pz.at(ptau),gen_->e.at(ptau));

      for (int j=0; j<gen_->id.size(); j++) {
	if  ( gen_->status.at(j)!=3 && (abs(gen_->id.at(j))==16) && gen_->parent_id.at(j)==15) {
	  nuplus.SetPxPyPzE(gen_->px.at(j),gen_->py.at(j),gen_->pz.at(j),gen_->e.at(j)); break;
	}
      }

      //      std::cout << "Tau+ pT = " << tauplus.Pt() << " and neutrino pT = " << nuplus.Pt() << std::endl;
      tauplus_vis=(tauplus-nuplus);
      //      std::cout << "Tau+ visible pT = " << tauplus.Pt() << std::endl;
    }


    if (mtau>0) {
      tauminus.SetPxPyPzE(gen_->px.at(mtau),gen_->py.at(mtau),gen_->pz.at(mtau),gen_->e.at(mtau));
      
      for (int j=0; j<gen_->id.size(); j++) {
	if  ( gen_->status.at(j)!=3 && (abs(gen_->id.at(j))==16) && gen_->parent_id.at(j)==-15) {
	  numinus.SetPxPyPzE(gen_->px.at(j),gen_->py.at(j),gen_->pz.at(j),gen_->e.at(j)); break;
	}
      }

      //      std::cout << "Tau- pT = " << tauminus.Pt() << " and neutrino pT = " << numinus.Pt() << std::endl;
      
      tauminus_vis=(tauminus-numinus);
      //      std::cout << "Tau- visible pT = " << tauminus.Pt() << std::endl;
    }

    // At least 1 GEN tau decayed hadronically
    if (itau>0) { 
 
      int iTau;
      
      double dr; double drmax; 
      double dpt; double dptmin;

      if (ptau>0) {
	//	tauplus.SetPxPyPzE(gen_->px.at(ptau),gen_->py.at(ptau),gen_->pz.at(ptau),gen_->e.at(ptau));

	if ( fabs(tauplus.Eta()) < 2.4) {

	  iTau=-1; drmax=0.5; dptmin=0.;
	// Loop over Taus
	  for (Int_t i=0; i<l1upgrade_->nTau; i++) {
	    
	    dpt=l1upgrade_->tauEt.at(i) ;
	    dr=deltaR(tauplus.Eta(),tauplus.Phi(),l1upgrade_->tauEta.at(i),l1upgrade_->tauPhi.at(i));
	    
	    if (dr<drmax && dpt>dptmin) { 
	      drmax=dr; dptmin=dpt; iTau=i; }
	  } // End loop L1jets
	  
	  if (iTau>=0) { // gen-L1 jet match
	    //	std::cout << "Kept tau with Et= " << dptmin << std::endl;
	    
	    hTaugen->Fill(tauplus_vis.Pt());
	    
	    if (l1upgrade_->tauEt.at(iTau)>=30.) hTau30->Fill(tauplus_vis.Pt());
	    if (l1upgrade_->tauEt.at(iTau)>=45.) hTau45->Fill(tauplus_vis.Pt());
	    if (l1upgrade_->tauEt.at(iTau)>=60.) hTau60->Fill(tauplus_vis.Pt());
	    if (l1upgrade_->tauEt.at(iTau)>=75.) hTau75->Fill(tauplus_vis.Pt());
	    if (l1upgrade_->tauEt.at(iTau)>=90.) hTau90->Fill(tauplus_vis.Pt());
	    
	  } // end found match
	  
	  iTau=-1; drmax=0.5; dptmin=0.;
	  // Loop over IsoTaus
	  for (Int_t i=0; i<l1upgrade_->nIsoTau; i++) {
	    
	    dpt=l1upgrade_->isoTauEt.at(i);
	    dr=deltaR(tauplus.Eta(),tauplus.Phi(),l1upgrade_->isoTauEta.at(i),l1upgrade_->isoTauPhi.at(i));
	    
	    if (dr<drmax && dpt>dptmin) { 
	      drmax=dr; dptmin=dpt; iTau=i; }
	  } // End loop L1jets
	  
	  if (iTau>=0) { // gen-L1 jet match
	    hisoTaugen->Fill(tauplus_vis.Pt());
	    
	    if (l1upgrade_->isoTauEt.at(iTau)>=30.) hIsoTau30->Fill(tauplus_vis.Pt());
	    if (l1upgrade_->isoTauEt.at(iTau)>=45.) hIsoTau45->Fill(tauplus_vis.Pt());
	    if (l1upgrade_->isoTauEt.at(iTau)>=60.) hIsoTau60->Fill(tauplus_vis.Pt());
	    if (l1upgrade_->isoTauEt.at(iTau)>=75.) hIsoTau75->Fill(tauplus_vis.Pt());
	    if (l1upgrade_->isoTauEt.at(iTau)>=90.) hIsoTau90->Fill(tauplus_vis.Pt());
	    
	  }

	  // TkTaus
	  iTau=-1; drmax=0.5; dptmin=0.;
	// Loop over Taus
	  for (Int_t i=0; i<l1upgrade_->nTkTau; i++) {
	    
	    dpt=l1upgrade_->tkTauEt.at(i) ;
	    dr=deltaR(tauplus.Eta(),tauplus.Phi(),l1upgrade_->tkTauEta.at(i),l1upgrade_->tkTauPhi.at(i));
	    
	    if (dr<drmax && dpt>dptmin) { 
	      drmax=dr; dptmin=dpt; iTau=i; }
	  } // End loop L1jets
	  
	  if (iTau>=0) { // gen-L1 jet match
	    //	std::cout << "Kept tau with Et= " << dptmin << std::endl;
	    
	    htkTaugen->Fill(tauplus_vis.Pt());
	    
	    if (l1upgrade_->tkTauEt.at(iTau)>=10.) htkTau10->Fill(tauplus_vis.Pt());
	    if (l1upgrade_->tkTauEt.at(iTau)>=20.) htkTau20->Fill(tauplus_vis.Pt());
	    if (l1upgrade_->tkTauEt.at(iTau)>=30.) htkTau30->Fill(tauplus_vis.Pt());
	    if (l1upgrade_->tkTauEt.at(iTau)>=45.) htkTau45->Fill(tauplus_vis.Pt());
	    if (l1upgrade_->tkTauEt.at(iTau)>=60.) htkTau60->Fill(tauplus_vis.Pt());
	    if (l1upgrade_->tkTauEt.at(iTau)>=75.) htkTau75->Fill(tauplus_vis.Pt());
	    if (l1upgrade_->tkTauEt.at(iTau)>=90.) htkTau90->Fill(tauplus_vis.Pt());
	    
	  } // end found match

	} // gen tau eta restriction

      } // if TAU+

      if (mtau>0) {
	//	tauminus.SetPxPyPzE(gen_->px.at(mtau),gen_->py.at(mtau),gen_->pz.at(mtau),gen_->e.at(mtau));

	if ( fabs(tauminus.Eta())<2.4) {

	  iTau=-1; drmax=0.5; dptmin=0.;
	  // Loop over Taus
	  for (Int_t i=0; i<l1upgrade_->nTau; i++) {
	    
	    dpt=l1upgrade_->tauEt.at(i) ;
	    
	    dr=deltaR(tauminus.Eta(),tauminus.Phi(),l1upgrade_->tauEta.at(i),l1upgrade_->tauPhi.at(i));
	    
	    if (dr<drmax && dpt>dptmin) { 
	      drmax=dr; dptmin=dpt; iTau=i; }
	  } // End loop L1jets
	  
	  if (iTau>=0) { // gen-L1 jet match
	    hTaugen->Fill(tauminus_vis.Pt());
	    
	    if (l1upgrade_->tauEt.at(iTau)>=30.) hTau30->Fill(tauminus_vis.Pt());
	    if (l1upgrade_->tauEt.at(iTau)>=45.) hTau45->Fill(tauminus_vis.Pt());
	    if (l1upgrade_->tauEt.at(iTau)>=60.) hTau60->Fill(tauminus_vis.Pt());
	    if (l1upgrade_->tauEt.at(iTau)>=75.) hTau75->Fill(tauminus_vis.Pt());
	    if (l1upgrade_->tauEt.at(iTau)>=90.) hTau90->Fill(tauminus_vis.Pt());
	    
	  } // end found match
	  
	  iTau=-1; drmax=0.5; dptmin=0.;
	  // Loop over IsoTaus
	  for (Int_t i=0; i<l1upgrade_->nIsoTau; i++) {
	    
	    dpt=l1upgrade_->isoTauEt.at(i);
	    dr=deltaR(tauminus.Eta(),tauminus.Phi(),l1upgrade_->isoTauEta.at(i),l1upgrade_->isoTauPhi.at(i));
	    
	    if (dr<drmax && dpt>dptmin) { 
	      drmax=dr; dptmin=dpt; iTau=i; }
	  } // End loop L1jets
	  
	  if (iTau>=0) { // gen-L1 jet match
	    hisoTaugen->Fill(tauminus_vis.Pt());
	    
	    if (l1upgrade_->isoTauEt.at(iTau)>=30.) hIsoTau30->Fill(tauminus_vis.Pt());
	    if (l1upgrade_->isoTauEt.at(iTau)>=45.) hIsoTau45->Fill(tauminus_vis.Pt());
	    if (l1upgrade_->isoTauEt.at(iTau)>=60.) hIsoTau60->Fill(tauminus_vis.Pt());
	    if (l1upgrade_->isoTauEt.at(iTau)>=75.) hIsoTau75->Fill(tauminus_vis.Pt());
	    if (l1upgrade_->isoTauEt.at(iTau)>=90.) hIsoTau90->Fill(tauminus_vis.Pt());
	    
	  }

	  // TkTaus
	  iTau=-1; drmax=0.5; dptmin=0.;
	  // Loop over Taus
	  for (Int_t i=0; i<l1upgrade_->nTkTau; i++) {
	    
	    dpt=l1upgrade_->tkTauEt.at(i) ;
	    
	    dr=deltaR(tauminus.Eta(),tauminus.Phi(),l1upgrade_->tkTauEta.at(i),l1upgrade_->tkTauPhi.at(i));
	    
	    if (dr<drmax && dpt>dptmin) { 
	      drmax=dr; dptmin=dpt; iTau=i; }
	  } // End loop L1jets
	  
	  if (iTau>=0) { // gen-L1 jet match
	    htkTaugen->Fill(tauminus_vis.Pt());
	    
	    if (l1upgrade_->tkTauEt.at(iTau)>=10.) htkTau10->Fill(tauminus_vis.Pt());
	    if (l1upgrade_->tkTauEt.at(iTau)>=20.) htkTau20->Fill(tauminus_vis.Pt());
	    if (l1upgrade_->tkTauEt.at(iTau)>=30.) htkTau30->Fill(tauminus_vis.Pt());
	    if (l1upgrade_->tkTauEt.at(iTau)>=45.) htkTau45->Fill(tauminus_vis.Pt());
	    if (l1upgrade_->tkTauEt.at(iTau)>=60.) htkTau60->Fill(tauminus_vis.Pt());
	    if (l1upgrade_->tkTauEt.at(iTau)>=75.) htkTau75->Fill(tauminus_vis.Pt());
	    if (l1upgrade_->tkTauEt.at(iTau)>=90.) htkTau90->Fill(tauminus_vis.Pt());
	    
	  } // end found match


	} // gen tau eta restriction
      } //if TAU-
      
    } // end TAU analysis
    // -----------------------------------------------------------------------------------------------------------
    // JET analysis
    // Sort partons in PT
    std::map<int, double>::iterator tt = partons.begin();
    double maxpt = tt->second;
    int maxipt=-1;
    for (tt=partons.begin(); tt!=partons.end(); ++tt) {
      if (tt->second>=maxpt) {
	maxpt=tt->second; maxipt=tt->first;
      }
    }
    if (maxipt>0) {      // Found highest-pT genJet

      parton.SetPxPyPzE(gen_->px.at(maxipt),gen_->py.at(maxipt),gen_->pz.at(maxipt),gen_->e.at(maxipt));

      int iJet=-1;
      double dr; 
      double drmax=0.5;
      double dpt; double dptmin=0.0;
      // Loop over L1jets
      for (Int_t i=0; i<l1upgrade_->nJets; i++) {

	if (i>0) break;

	dpt=l1upgrade_->jetEt.at(i);
	//	std::cout << "L1 Jet Et = " << dpt << std::endl;
	dr=deltaR(parton.Eta(),parton.Phi(),l1upgrade_->jetEta.at(i),l1upgrade_->jetPhi.at(i));

	if (dr<drmax && dpt>dptmin) { 
	  dptmin=dpt; iJet=i; }
      } // End loop L1jets

      if (iJet>=0) { // gen-L1 jet match
	hJETgen->Fill(parton.Pt());

	//	std::cout << "Picked up L1Jet iwth Et = " << l1upgrade_->jetEt.at(iJet) << std::endl;

	if (l1upgrade_->jetEt.at(iJet)>=25.) hJet25->Fill(parton.Pt());
	if (l1upgrade_->jetEt.at(iJet)>=50.) hJet50->Fill(parton.Pt());
	if (l1upgrade_->jetEt.at(iJet)>=75.) hJet75->Fill(parton.Pt());
	
	if (l1upgrade_->jetEt.at(iJet)>=100.) hJet100->Fill(parton.Pt());
	if (l1upgrade_->jetEt.at(iJet)>=150.) hJet150->Fill(parton.Pt());
	if (l1upgrade_->jetEt.at(iJet)>=200.) hJet200->Fill(parton.Pt());
	if (l1upgrade_->jetEt.at(iJet)>=250.) hJet250->Fill(parton.Pt());
	if (l1upgrade_->jetEt.at(iJet)>=300.) hJet300->Fill(parton.Pt());
      }

    } // end if found highest-pT ref (parton-)Jet

    // -------------------------------------------------------------------------------------------
    // MUON analysis
    if (imu==1) {
      if ( (muon.Pt()>5.) && (abs(muon.Eta())<2.1) ) { // pT/eta cuts
	
	hMUall->Fill(muon.Pt()); hMUalleta->Fill(muon.Eta());
	 // loop over Muons
	int iMU=-1;
    
	double dR;
	double dRmax=0.5;
	double dpt; double dptmin=0.0;
	for (Int_t i=0; i<l1upgrade_->nTkMuons; i++) {
	  if (i>0) break;

	  if (l1upgrade_->tkMuonQuality.at(i)<3) continue;
	  dpt=l1upgrade_->tkMuonEt.at(i);
	  //	  std::cout << "TkMuon pT = " << dpt << std::endl;

	  dR=deltaR(muon.Eta(),muon.Phi(),l1upgrade_->tkMuonEta.at(i),l1upgrade_->tkMuonPhi.at(i));
	  if (dR<dRmax) { 
	    dRmax=dR; dptmin=dpt; iMU=i; }
	  
	} 
	
	if (iMU>=0) {  // if found a match within 0.5
	  hMUgen->Fill(muon.Pt());  
	  hMUgeneta->Fill(muon.Eta());
	  
	  //	  std::cout << "Picked up TkMuon with pT = " <<  l1upgrade_->tkMuonEt.at(iMU) << std::endl;
	  if (l1upgrade_->tkMuonEt.at(iMU)>10.) hMU10->Fill(muon.Pt());
	  if (l1upgrade_->tkMuonEt.at(iMU)>20.) hMU20->Fill(muon.Pt());
	  if (l1upgrade_->tkMuonEt.at(iMU)>30.) hMU30->Fill(muon.Pt());
	  if (l1upgrade_->tkMuonEt.at(iMU)>40.) hMU40->Fill(muon.Pt());
	  if (l1upgrade_->tkMuonEt.at(iMU)>50.) hMU50->Fill(muon.Pt());
	}
    
      } // end pT/eta cuts
    } 
    /*
    else { // exactly 1-muon
      std::cout << "Have found more than 1 muons!!!" << std::endl;
    }
    */
    //---------------------------------------------------------------------------------------------

    //Photon analysis
    if (ipho==1) {
      if ( (photon.Pt()>2.) && (fabs(photon.Eta())<2.4) ) {
	
	double dptall,drall;

	// loop over Egamma
	int iP=-1;

	double dR;
	double dRmax=0.5;
	double dpt; double dptmin=0.0;

	for (Int_t i=0; i<l1upgrade_->nTkEM; i++) {

	  if (i>0) break;
	  dpt=l1upgrade_->tkEMEt.at(i);
	  dR=deltaR(photon.Eta(),photon.Phi(),l1upgrade_->tkEMEta.at(i),l1upgrade_->tkEMPhi.at(i));
	  //      if (dR<dRmax) {
	  if (dR<dRmax && dpt>dptmin) {
	    dRmax=dR; dptmin=dpt; iP=i; }

	}

	if (iP>=0) {  // if found a match within 0.5
	  hTkEMgen->Fill(photon.Pt());
	  hTkEMgeneta->Fill(photon.Eta());

	  if (l1upgrade_->tkEMEt.at(iP)>12.) hTkEM12->Fill(photon.Pt());
	  if (l1upgrade_->tkEMEt.at(iP)>15.) hTkEM15->Fill(photon.Pt());
	  if (l1upgrade_->tkEMEt.at(iP)>20.) hTkEM20->Fill(photon.Pt());
	  if (l1upgrade_->tkEMEt.at(iP)>25.) hTkEM25->Fill(photon.Pt());
	  if (l1upgrade_->tkEMEt.at(iP)>30.) hTkEM30->Fill(photon.Pt());
	}

      } // acceptance cuts
    } // 1 photon found


    // ELECTRON analysis
    if ( (electron.Pt()<2.) || (fabs(electron.Eta())>2.4) ) continue;

    nGENele->Fill(iele); nEGele->Fill(l1upgrade_->nEG);

    hGen->Fill(electron.Pt()); hGENeta->Fill(electron.Eta());
    
    double dptall,drall;
    
    // loop over Egamma
    int iEG=-1;
    
    double dR;
    double dRmax=0.5;
    double dpt; double dptmin=0.0;

    for (Int_t i=0; i<l1upgrade_->nEG; i++) {
 
      if (i>0) break;
      dpt=l1upgrade_->egEt.at(i);
      dptall=fabs(electron.Pt()-l1upgrade_->egEt.at(i))/electron.Pt();
      dR=deltaR(electron.Eta(),electron.Phi(),l1upgrade_->egEta.at(i),l1upgrade_->egPhi.at(i));
      
      dPTvsdR1->Fill(dR,dptall);
      //      if (dR<dRmax) {
      if (dR<dRmax && dpt>dptmin) { 
	dRmax=dR; dptmin=dpt; iEG=i; }
    } 
    
    if (iEG>=0) {  // if found a match within 0.5
      DRmin1->Fill(dRmax);
      
      //  hGen->Fill(electron.Pt()); hGENeta->Fill(electron.Eta());
      //      std::cout << "Found a match within DR= " << dRmax << std::endl; 
      hEGgen->Fill(electron.Pt());  
      hEGgeneta->Fill(electron.Eta());

      resEG->Fill((electron.Pt()-l1upgrade_->egEt.at(iEG))/electron.Pt());

      if (electron.Pt()<10.) {
	resEG1->Fill((electron.Pt()-l1upgrade_->egEt.at(iEG))/electron.Pt());
      } else if (electron.Pt()<20. && electron.Pt()>=10.) {
	resEG2->Fill((electron.Pt()-l1upgrade_->egEt.at(iEG))/electron.Pt());
      } else if (electron.Pt()<30. && electron.Pt()>=20.) {
	resEG3->Fill((electron.Pt()-l1upgrade_->egEt.at(iEG))/electron.Pt());
      } else if  (electron.Pt()<40. && electron.Pt()>=30.) {
	resEG4->Fill((electron.Pt()-l1upgrade_->egEt.at(iEG))/electron.Pt());
      } else if  (electron.Pt()>=40. ) {
	resEG5->Fill((electron.Pt()-l1upgrade_->egEt.at(iEG))/electron.Pt());
      }

      if (l1upgrade_->egEt.at(iEG)>12.) hEG12->Fill(electron.Pt());
      if (l1upgrade_->egEt.at(iEG)>15.) hEG15->Fill(electron.Pt());
      if (l1upgrade_->egEt.at(iEG)>20.) hEG20->Fill(electron.Pt());
      if (l1upgrade_->egEt.at(iEG)>25.) hEG25->Fill(electron.Pt());
      if (l1upgrade_->egEt.at(iEG)>30.) hEG30->Fill(electron.Pt());
      
      hUpgrade1->Fill(l1upgrade_->egEt.at(iEG));
      hEGeta->Fill(l1upgrade_->egEta.at(iEG));
    }
    
      // Start with a gen electron & loop over isoEgamma
    iEG=-1;

      //double dR;
    dRmax=0.5;   dptmin=0.0;
    for (Int_t i=0; i<l1upgrade_->nIsoEG; i++) {
      
      if (i>0) break;
      dpt=l1upgrade_->isoEGEt.at(i);
      dptall=fabs(electron.Pt()-l1upgrade_->isoEGEt.at(i))/electron.Pt();
      dR=deltaR(electron.Eta(),electron.Phi(),l1upgrade_->isoEGEta.at(i),l1upgrade_->isoEGPhi.at(i));
      
      dPTvsdR2->Fill(dR,dptall);
      //if (dR<dRmax) {
      if (dR<dRmax && dpt>dptmin) { 
	dRmax=dR; dptmin=dpt; iEG=i; }

    }

    if (iEG>=0) { 
      DRmin2->Fill(dRmax);

      hisoEGgen->Fill(electron.Pt());  
      hisoEGgeneta->Fill(electron.Eta());
      
      if (l1upgrade_->isoEGEt.at(iEG)>12.) hisoEG12->Fill(electron.Pt());
      if (l1upgrade_->isoEGEt.at(iEG)>15.) hisoEG15->Fill(electron.Pt());
      if (l1upgrade_->isoEGEt.at(iEG)>20.) hisoEG20->Fill(electron.Pt());
      if (l1upgrade_->isoEGEt.at(iEG)>25.) hisoEG25->Fill(electron.Pt());
      if (l1upgrade_->isoEGEt.at(iEG)>30.) hisoEG30->Fill(electron.Pt());
      
      hUpgrade2->Fill(l1upgrade_->isoEGEt.at(iEG));
      hisoEGeta->Fill(l1upgrade_->isoEGEta.at(iEG));
    }
    // -----------------------------------------------------------------------------------------------------------
 
   // TkElectrons
    iEG=-1;
    dRmax=0.5; dptmin=0.0;
    for (Int_t i=0; i<l1upgrade_->nTkEG; i++) {
 
      if (i>0) break;
      dpt=l1upgrade_->tkEGEt.at(i);
      dR=deltaR(electron.Eta(),electron.Phi(),l1upgrade_->tkEGEta.at(i),l1upgrade_->tkEGPhi.at(i));
      //      if (dR<dRmax) {
      if (dR<dRmax && dpt>dptmin) { 
	dRmax=dR; dptmin=dpt; iEG=i; }

    } 
    
    if (iEG>=0) {  // if found a match within 0.5

      hTkEGgen->Fill(electron.Pt());  
      hTkEGgeneta->Fill(electron.Eta());

      resTkEG->Fill((electron.Pt()-l1upgrade_->tkEGEt.at(iEG))/electron.Pt());

       if (electron.Pt()<10.) {
	resTkEG1->Fill((electron.Pt()-l1upgrade_->egEt.at(iEG))/electron.Pt());
      } else if (electron.Pt()<20. && electron.Pt()>=10.) {
	resTkEG2->Fill((electron.Pt()-l1upgrade_->egEt.at(iEG))/electron.Pt());
      } else if (electron.Pt()<30. && electron.Pt()>=20.) {
	resTkEG3->Fill((electron.Pt()-l1upgrade_->egEt.at(iEG))/electron.Pt());
      } else if  (electron.Pt()<40. && electron.Pt()>=30.) {
	resTkEG4->Fill((electron.Pt()-l1upgrade_->egEt.at(iEG))/electron.Pt());
      } else if  (electron.Pt()>=40. ) {
	resTkEG5->Fill((electron.Pt()-l1upgrade_->egEt.at(iEG))/electron.Pt());
      }

      if (l1upgrade_->tkEGEt.at(iEG)>12.) hTkEG12->Fill(electron.Pt());
      if (l1upgrade_->tkEGEt.at(iEG)>15.) hTkEG15->Fill(electron.Pt());
      if (l1upgrade_->tkEGEt.at(iEG)>20.) hTkEG20->Fill(electron.Pt());
      if (l1upgrade_->tkEGEt.at(iEG)>25.) hTkEG25->Fill(electron.Pt());
      if (l1upgrade_->tkEGEt.at(iEG)>30.) hTkEG30->Fill(electron.Pt());

    }
    
      // Start with a gen electron & loop over tkIsoEgamma
    iEG=-1;

    dRmax=0.5; dptmin=0.0;
    for (Int_t i=0; i<l1upgrade_->nTkIsoEG; i++) {
      
      if (i>0) break;
      dpt=l1upgrade_->tkIsoEGEt.at(i);
      dR=deltaR(electron.Eta(),electron.Phi(),l1upgrade_->tkIsoEGEta.at(i),l1upgrade_->tkIsoEGPhi.at(i));
      //      if (dR<dRmax) {
      if (dR<dRmax && dpt>dptmin) { 
	dRmax=dR; dptmin=dpt; iEG=i; }

    }
    // htkIsoEGgen->Fill(electron.Pt());
    if (iEG>=0) { 

      hTkIsoEGgen->Fill(electron.Pt());  
      hTkIsoEGgeneta->Fill(electron.Eta());
      
      if (l1upgrade_->tkIsoEGEt.at(iEG)>12.) hTkIsoEG12->Fill(electron.Pt());
      if (l1upgrade_->tkIsoEGEt.at(iEG)>15.) hTkIsoEG15->Fill(electron.Pt());
      if (l1upgrade_->tkIsoEGEt.at(iEG)>20.) hTkIsoEG20->Fill(electron.Pt());
      if (l1upgrade_->tkIsoEGEt.at(iEG)>25.) hTkIsoEG25->Fill(electron.Pt());
      if (l1upgrade_->tkIsoEGEt.at(iEG)>30.) hTkIsoEG30->Fill(electron.Pt());
    }
    // ----------------------------------------------------------------------------------------------

  }

  hMUall->Sumw2(); hMUalleta->Sumw2();
  hMUgen->Sumw2(); hMUgeneta->Sumw2();
  hMU10->Sumw2(); hMU20->Sumw2(); hMU30->Sumw2(); hMU40->Sumw2(); hMU50->Sumw2();

  hMUall->SetDirectory(dirMU); hMUalleta->SetDirectory(dirMU);
  hMUgen->SetDirectory(dirMU); hMUgeneta->SetDirectory(dirMU);
  hMU10->SetDirectory(dirMU); hMU20->SetDirectory(dirMU); hMU30->SetDirectory(dirMU); hMU40->SetDirectory(dirMU); hMU50->SetDirectory(dirMU);
  
  hGen->Sumw2(); hGENeta->Sumw2();
  hUpgrade1->Sumw2(); hUpgrade2->Sumw2();
  hEGeta->Sumw2(); hisoEGeta->Sumw2();
  hEGgeneta->Sumw2(); hisoEGgeneta->Sumw2();

  nGENele->Sumw2(); nEGele->Sumw2();
  nGENele->SetDirectory(dirEG); nEGele->SetDirectory(dirEG);

  hEGgen->Sumw2(); hisoEGgen->Sumw2();
  hEG12->Sumw2(); hisoEG12->Sumw2();
  hEG15->Sumw2(); hisoEG15->Sumw2();
  hEG20->Sumw2(); hisoEG20->Sumw2();
  hEG25->Sumw2(); hisoEG25->Sumw2();
  hEG30->Sumw2(); hisoEG30->Sumw2();

  // ---- TkElectrons ------------------------------------------------------
  resEG->Sumw2(); resTkEG->Sumw2();
  resEG->SetDirectory(dirEG); resTkEG->SetDirectory(dirEG);

  resEG1->Sumw2(); resTkEG1->Sumw2();
  resEG1->SetDirectory(dirEG); resTkEG1->SetDirectory(dirEG);
  resEG2->Sumw2(); resTkEG2->Sumw2();
  resEG2->SetDirectory(dirEG); resTkEG2->SetDirectory(dirEG);
  resEG3->Sumw2(); resTkEG3->Sumw2();
  resEG3->SetDirectory(dirEG); resTkEG3->SetDirectory(dirEG);
  resEG4->Sumw2(); resTkEG4->Sumw2();
  resEG4->SetDirectory(dirEG); resTkEG4->SetDirectory(dirEG);
  resEG5->Sumw2(); resTkEG5->Sumw2();
  resEG5->SetDirectory(dirEG); resTkEG5->SetDirectory(dirEG);

  hTkEGgen->Sumw2(); hTkIsoEGgen->Sumw2();
  hTkEGgeneta->Sumw2(); hTkIsoEGgeneta->Sumw2();
  hTkEG12->Sumw2(); hTkIsoEG12->Sumw2();
  hTkEG15->Sumw2(); hTkIsoEG15->Sumw2();
  hTkEG20->Sumw2(); hTkIsoEG20->Sumw2();
  hTkEG25->Sumw2(); hTkIsoEG25->Sumw2();
  hTkEG30->Sumw2(); hTkIsoEG30->Sumw2();

  hTkEMgen->Sumw2();hTkEMgeneta->Sumw2();hTkEM12->Sumw2();hTkEM15->Sumw2();hTkEM20->Sumw2();hTkEM25->Sumw2();hTkEM30->Sumw2();
  hTkEMgen->SetDirectory(dirEG);hTkEMgeneta->SetDirectory(dirEG);
  hTkEM12->SetDirectory(dirEG);hTkEM15->SetDirectory(dirEG); hTkEM20->SetDirectory(dirEG);hTkEM25->SetDirectory(dirEG);hTkEM30->SetDirectory(dirEG);

  hTkEGgen->SetDirectory(dirEG); hTkIsoEGgen->SetDirectory(dirEG);
  hTkEGgeneta->SetDirectory(dirEG); hTkIsoEGgeneta->SetDirectory(dirEG);
  hTkEG12->SetDirectory(dirEG); hTkIsoEG12->SetDirectory(dirEG);
  hTkEG15->SetDirectory(dirEG); hTkIsoEG15->SetDirectory(dirEG);
  hTkEG20->SetDirectory(dirEG); hTkIsoEG20->SetDirectory(dirEG);
  hTkEG25->SetDirectory(dirEG); hTkIsoEG25->SetDirectory(dirEG);
  hTkEG30->SetDirectory(dirEG); hTkIsoEG30->SetDirectory(dirEG);
  // -----------------------------------------------------------------------

  hUpgrade1->SetDirectory(dirEG); hUpgrade2->SetDirectory(dirEG);
  hGen->SetDirectory(dirEG);
  hGENeta->SetDirectory(dirEG); hEGeta->SetDirectory(dirEG); hisoEGeta->SetDirectory(dirEG);
  DRmin1->SetDirectory(dirEG); DRmin2->SetDirectory(dirEG);
  dPTvsdR1->SetDirectory(dirEG); dPTvsdR2->SetDirectory(dirEG);

  hTaugen->Sumw2();
  hTau30->Sumw2(); hTau45->Sumw2(); hTau60->Sumw2();
  hTau75->Sumw2(); hTau90->Sumw2();

  hTaugen->SetDirectory(dirTAU);
  hTau30->SetDirectory(dirTAU); hTau45->SetDirectory(dirTAU); hTau60->SetDirectory(dirTAU);
  hTau75->SetDirectory(dirTAU); hTau90->SetDirectory(dirTAU);

  htkTaugen->Sumw2();
  htkTau10->Sumw2(); htkTau20->Sumw2();
  htkTau30->Sumw2(); htkTau45->Sumw2(); htkTau60->Sumw2();
  htkTau75->Sumw2(); htkTau90->Sumw2();

  htkTaugen->SetDirectory(dirTAU);
  htkTau10->SetDirectory(dirTAU); htkTau20->SetDirectory(dirTAU);
  htkTau30->SetDirectory(dirTAU); htkTau45->SetDirectory(dirTAU); htkTau60->SetDirectory(dirTAU);
  htkTau75->SetDirectory(dirTAU); htkTau90->SetDirectory(dirTAU);

  hisoTaugen->Sumw2();
  hIsoTau30->Sumw2(); hIsoTau45->Sumw2(); hIsoTau60->Sumw2();
  hIsoTau75->Sumw2(); hIsoTau90->Sumw2();

  hisoTaugen->SetDirectory(dirTAU);  
  hIsoTau30->SetDirectory(dirTAU); hIsoTau45->SetDirectory(dirTAU); hIsoTau60->SetDirectory(dirTAU);
  hIsoTau75->SetDirectory(dirTAU); hIsoTau90->SetDirectory(dirTAU);

  hJETgen->Sumw2();
  hJet25->Sumw2(); hJet50->Sumw2(); hJet75->Sumw2();
  hJet100->Sumw2(); hJet150->Sumw2(); hJet200->Sumw2();
  hJet250->Sumw2(); hJet300->Sumw2();
  hJETgen->SetDirectory(dirJET);
  hJet25->SetDirectory(dirJET); hJet50->SetDirectory(dirJET); hJet75->SetDirectory(dirJET);
  hJet100->SetDirectory(dirJET); hJet150->SetDirectory(dirJET); hJet200->SetDirectory(dirJET);
  hJet250->SetDirectory(dirJET); hJet300->SetDirectory(dirJET);

  hEGgen->SetDirectory(dirEG); hisoEGgen->SetDirectory(dirEG);
  hEGgeneta->SetDirectory(dirEG); hisoEGgeneta->SetDirectory(dirEG);

  hEG12->SetDirectory(dirEG); hisoEG12->SetDirectory(dirEG);
  hEG15->SetDirectory(dirEG); hisoEG15->SetDirectory(dirEG);
  hEG20->SetDirectory(dirEG); hisoEG20->SetDirectory(dirEG);
  hEG25->SetDirectory(dirEG); hisoEG25->SetDirectory(dirEG);
  hEG30->SetDirectory(dirEG); hisoEG30->SetDirectory(dirEG);

  total->Write(); total->Close();
}
