#include "Histograms.h"

Histograms::Histograms(int ptbin, double ptmin, double ptmax,
   int etabin, double etamin, double etamax,
   int isobin, double isomin, double isomax,
   vector<double> &thresholds, string Label)
{
   Thresholds = thresholds;

   for(int iT = 0; iT < (int)thresholds.size(); iT++)
   {
      HPT.push_back(new TH1D(Form("%s_PT_%06d", Label.c_str(), (int)thresholds[iT] * 100), "title;pt;#", ptbin, ptmin, ptmax));
      HPTEta15.push_back(new TH1D(Form("%s_PTEta15_%06d", Label.c_str(), (int)thresholds[iT] * 100), "title;pt;#", ptbin, ptmin, ptmax));
      HPTEtaLarge.push_back(new TH1D(Form("%s_PTEtaLarge_%06d", Label.c_str(), (int)thresholds[iT] * 100), "title;pt;#", ptbin, ptmin, ptmax));
      HEta.push_back(new TH1D(Form("%s_Eta_%06d", Label.c_str(), (int)thresholds[iT] * 100), "title;eta;#", etabin, etamin, etamax));
      HEtaPT20.push_back(new TH1D(Form("%s_EtaPT20_%06d", Label.c_str(), (int)thresholds[iT] * 100), "title;eta;#", etabin, etamin, etamax));
      HEtaPT25.push_back(new TH1D(Form("%s_EtaPT25_%06d", Label.c_str(), (int)thresholds[iT] * 100), "title;eta;#", etabin, etamin, etamax));
      HEtaPT200.push_back(new TH1D(Form("%s_EtaPT200_%06d", Label.c_str(), (int)thresholds[iT] * 100), "title;eta;#", etabin, etamin, etamax));
      HTkIso.push_back(new TH1D(Form("%s_TkIso_%06d", Label.c_str(), (int)thresholds[iT] * 100), "title;iso;#", isobin, isomin, isomax));
      
      HPT[iT]->Sumw2();
      HPTEta15[iT]->Sumw2();
      HPTEtaLarge[iT]->Sumw2();
      HEta[iT]->Sumw2();
      HEtaPT20[iT]->Sumw2();
      HEtaPT25[iT]->Sumw2();
      HEtaPT200[iT]->Sumw2();
      HTkIso[iT]->Sumw2();
   }
}

Histograms::~Histograms()
{
}

void Histograms::Fill(double check, double pt, double eta, double iso)
{
   for(int i = 0; i < (int)Thresholds.size(); i++)
   {
      if(check < Thresholds[i])
         continue;

      if(HPT[i] != NULL)                            HPT[i]->Fill(pt);
      if(HPTEta15[i] != NULL && fabs(eta) < 1.5)    HPTEta15[i]->Fill(pt);
      if(HPTEtaLarge[i] != NULL && fabs(eta) > 1.5) HPTEtaLarge[i]->Fill(pt);
      if(HEta[i] != NULL)                           HEta[i]->Fill(eta);
      if(HEtaPT20[i] != NULL && pt > 20)            HEtaPT20[i]->Fill(eta);
      if(HEtaPT25[i] != NULL && pt > 25)            HEtaPT25[i]->Fill(eta);
      if(HEtaPT200[i] != NULL && pt > 200)          HEtaPT200[i]->Fill(eta);
      if(HTkIso[i] != NULL)                         HTkIso[i]->Fill(iso);
   }
}

void Histograms::Fill(FourVector Check, FourVector P, double iso)
{
   Fill(Check.GetPT(), P.GetPT(), P.GetEta(), iso);
}

void Histograms::Write(TDirectory *Directory)
{
   if(Directory != NULL)
      Directory->cd();

   for(int i = 0; i < (int)HPT.size(); i++)
   {
      if(HPT[i] == NULL)
         continue;

      if(Directory != NULL)
         HPT[i]->SetDirectory(Directory);
      HPT[i]->Write();
   }
   
   for(int i = 0; i < (int)HPTEta15.size(); i++)
   {
      if(HPTEta15[i] == NULL)
         continue;

      if(Directory != NULL)
         HPTEta15[i]->SetDirectory(Directory);
      HPTEta15[i]->Write();
   }
   
   for(int i = 0; i < (int)HPTEtaLarge.size(); i++)
   {
      if(HPTEtaLarge[i] == NULL)
         continue;

      if(Directory != NULL)
         HPTEtaLarge[i]->SetDirectory(Directory);
      HPTEtaLarge[i]->Write();
   }
   
   for(int i = 0; i < (int)HEta.size(); i++)
   {
      if(HEta[i] == NULL)
         continue;

      if(Directory != NULL)
         HEta[i]->SetDirectory(Directory);
      HEta[i]->Write();
   }
   
   for(int i = 0; i < (int)HEtaPT20.size(); i++)
   {
      if(HEtaPT20[i] == NULL)
         continue;

      if(Directory != NULL)
         HEtaPT20[i]->SetDirectory(Directory);
      HEtaPT20[i]->Write();
   }
   
   for(int i = 0; i < (int)HEtaPT25.size(); i++)
   {
      if(HEtaPT25[i] == NULL)
         continue;

      if(Directory != NULL)
         HEtaPT25[i]->SetDirectory(Directory);
      HEtaPT25[i]->Write();
   }
   
   for(int i = 0; i < (int)HEtaPT200.size(); i++)
   {
      if(HEtaPT200[i] == NULL)
         continue;

      if(Directory != NULL)
         HEtaPT200[i]->SetDirectory(Directory);
      HEtaPT200[i]->Write();
   }
   
   for(int i = 0; i < (int)HTkIso.size(); i++)
   {
      if(HTkIso[i] == NULL)
         continue;

      if(Directory != NULL)
         HTkIso[i]->SetDirectory(Directory);
      HTkIso[i]->Write();
   }
}


