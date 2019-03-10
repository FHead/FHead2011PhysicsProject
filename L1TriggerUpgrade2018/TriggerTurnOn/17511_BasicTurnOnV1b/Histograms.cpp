#include "Histograms.h"

Histograms::Histograms(int ptbin, double ptmin, double ptmax,
   int etabin, double etamin, double etamax,
   int isobin, double isomin, double isomax,
   vector<double> &thresholds, string Label)
{
   int rbin = 100;
   double rmin = 0.0;
   double rmax = 2.5;

   Thresholds = thresholds;

   for(int iT = 0; iT < (int)thresholds.size(); iT++)
   {
      string Cut = Form("%06d", (int)thresholds[iT] * 100);

      HPT.push_back(new TH1D((Label + "_PT_" + Cut).c_str(),                 ";PT;#", ptbin, ptmin, ptmax));
      HPTEta15.push_back(new TH1D((Label + "_PTEta15_" + Cut).c_str(),       ";PT;#", ptbin, ptmin, ptmax));
      HPTEtaLarge.push_back(new TH1D((Label + "_PTEtaLarge_" + Cut).c_str(), ";PT;#", ptbin, ptmin, ptmax));
      HResponse.push_back(new TH1D((Label + "_Response_" + Cut).c_str(),     ";R;#", rbin, rmin, rmax));
      HResponseEta15.push_back(new TH1D((Label + "_ResponseEta15_" + Cut).c_str(), ";R;#", rbin, rmin, rmax));
      HResponseEtaLarge.push_back(new TH1D((Label + "_ResponseEtaLarge_" + Cut).c_str(), ";R;#", rbin, rmin, rmax));
      HResponsePT10.push_back(new TH1D((Label + "_ResponsePT10_" + Cut).c_str(), ";R;#", rbin, rmin, rmax));
      HResponsePT10Eta15.push_back(new TH1D((Label + "_ResponsePT10Eta15_" + Cut).c_str(), ";R;#", rbin, rmin, rmax));
      HResponsePT10EtaLarge.push_back(new TH1D((Label + "_ResponsePT10EtaLarge_" + Cut).c_str(), ";R;#", rbin, rmin, rmax));
      HEta.push_back(new TH1D((Label + "_Eta_" + Cut).c_str(),               ";Eta;#", etabin, etamin, etamax));
      HEtaPT20.push_back(new TH1D((Label + "_EtaPT20_" + Cut).c_str(),       ";Eta;#", etabin, etamin, etamax));
      HEtaPT25.push_back(new TH1D((Label + "_EtaPT25_" + Cut).c_str(),       ";Eta;#", etabin, etamin, etamax));
      HEtaPT200.push_back(new TH1D((Label + "_EtaPT200_" + Cut).c_str(),     ";Eta;#", etabin, etamin, etamax));
      HTkIso.push_back(new TH1D((Label + "_TkIso_" + Cut).c_str(),           ";Iso;#", isobin, isomin, isomax));
      HTkIsoPT10.push_back(new TH1D((Label + "_TkIsoPT10_" + Cut).c_str(),   ";Iso;#", isobin, isomin, isomax));
      HTkIsoPT20.push_back(new TH1D((Label + "_TkIsoPT20_" + Cut).c_str(),   ";Iso;#", isobin, isomin, isomax));
      HTkIsoPT30.push_back(new TH1D((Label + "_TkIsoPT30_" + Cut).c_str(),   ";Iso;#", isobin, isomin, isomax));
      HTkIsoPT40.push_back(new TH1D((Label + "_TkIsoPT40_" + Cut).c_str(),   ";Iso;#", isobin, isomin, isomax));
      
      HPT[iT]->Sumw2();
      HPTEta15[iT]->Sumw2();
      HPTEtaLarge[iT]->Sumw2();
      HResponse[iT]->Sumw2();
      HResponseEta15[iT]->Sumw2();
      HResponseEtaLarge[iT]->Sumw2();
      HResponsePT10[iT]->Sumw2();
      HResponsePT10Eta15[iT]->Sumw2();
      HResponsePT10EtaLarge[iT]->Sumw2();
      HEta[iT]->Sumw2();
      HEtaPT20[iT]->Sumw2();
      HEtaPT25[iT]->Sumw2();
      HEtaPT200[iT]->Sumw2();
      HTkIso[iT]->Sumw2();
      HTkIsoPT10[iT]->Sumw2();
      HTkIsoPT20[iT]->Sumw2();
      HTkIsoPT30[iT]->Sumw2();
      HTkIsoPT40[iT]->Sumw2();
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

      if(HPT[i] != NULL)                                  HPT[i]->Fill(pt);
      if(HPTEta15[i] != NULL && fabs(eta) < 1.5)          HPTEta15[i]->Fill(pt);
      if(HPTEtaLarge[i] != NULL && fabs(eta) > 1.5)       HPTEtaLarge[i]->Fill(pt);
      if(HResponse[i] != NULL)                            HResponse[i]->Fill(check / pt);
      if(HResponseEta15[i] != NULL && fabs(eta) < 1.5)    HResponseEta15[i]->Fill(check / pt);
      if(HResponseEtaLarge[i] != NULL && fabs(eta) > 1.5) HResponseEtaLarge[i]->Fill(check / pt);
      if(HResponsePT10[i] != NULL)                        HResponsePT10[i]->Fill(check / pt);
      if(HResponsePT10Eta15[i] != NULL && pt > 10 && fabs(eta) < 1.5)    HResponsePT10Eta15[i]->Fill(check / pt);
      if(HResponsePT10EtaLarge[i] != NULL && pt > 10 && fabs(eta) > 1.5) HResponsePT10EtaLarge[i]->Fill(check / pt);
      if(HEta[i] != NULL)                                 HEta[i]->Fill(eta);
      if(HEtaPT20[i] != NULL && pt > 20)                  HEtaPT20[i]->Fill(eta);
      if(HEtaPT25[i] != NULL && pt > 25)                  HEtaPT25[i]->Fill(eta);
      if(HEtaPT200[i] != NULL && pt > 200)                HEtaPT200[i]->Fill(eta);
      if(HTkIso[i] != NULL)                               HTkIso[i]->Fill(iso);
      if(HTkIsoPT10[i] != NULL && pt > 10)                HTkIsoPT10[i]->Fill(iso);
      if(HTkIsoPT20[i] != NULL && pt > 20)                HTkIsoPT20[i]->Fill(iso);
      if(HTkIsoPT30[i] != NULL && pt > 30)                HTkIsoPT30[i]->Fill(iso);
      if(HTkIsoPT40[i] != NULL && pt > 40)                HTkIsoPT40[i]->Fill(iso);
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

   Write(HPT,                   Directory);
   Write(HPTEta15,              Directory);
   Write(HPTEtaLarge,           Directory);
   Write(HResponse,             Directory);
   Write(HResponseEta15,        Directory);
   Write(HResponseEtaLarge,     Directory);
   Write(HResponsePT10,         Directory);
   Write(HResponsePT10Eta15,    Directory);
   Write(HResponsePT10EtaLarge, Directory);
   Write(HEta,                  Directory);
   Write(HEtaPT20,              Directory);
   Write(HEtaPT25,              Directory);
   Write(HEtaPT200,             Directory);
   Write(HTkIso,                Directory);
   Write(HTkIsoPT10,            Directory);
   Write(HTkIsoPT20,            Directory);
   Write(HTkIsoPT30,            Directory);
   Write(HTkIsoPT40,            Directory);
}

void Histograms::Write(vector<TH1D *> &Histograms, TDirectory *Directory)
{
   for(auto H : Histograms)
   {
      if(H == NULL)
         continue;
      
      if(Directory != NULL)
         H->SetDirectory(Directory);
      H->Write();
   }
}

