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
      HPTEta10.push_back(new TH1D(Form("%s_PTEta10_%06d", Label.c_str(), (int)thresholds[iT] * 100), "title;pt;#", ptbin, ptmin, ptmax));
      HPTEtaLarge.push_back(new TH1D(Form("%s_PTEtaLarge_%06d", Label.c_str(), (int)thresholds[iT] * 100), "title;pt;#", ptbin, ptmin, ptmax));
      HEta.push_back(new TH1D(Form("%s_Eta_%06d", Label.c_str(), (int)thresholds[iT] * 100), "title;eta;#", etabin, etamin, etamax));
      HEtaPT20.push_back(new TH1D(Form("%s_EtaPT20_%06d", Label.c_str(), (int)thresholds[iT] * 100), "title;eta;#", etabin, etamin, etamax));
      HEtaPT25.push_back(new TH1D(Form("%s_EtaPT25_%06d", Label.c_str(), (int)thresholds[iT] * 100), "title;eta;#", etabin, etamin, etamax));
      HEtaPT200.push_back(new TH1D(Form("%s_EtaPT200_%06d", Label.c_str(), (int)thresholds[iT] * 100), "title;eta;#", etabin, etamin, etamax));
      HPTIso010.push_back(new TH1D(Form("%s_PTIso010_%06d", Label.c_str(), (int)thresholds[iT] * 100), "title;pt;#", ptbin, ptmin, ptmax));
      HPTEta10Iso010.push_back(new TH1D(Form("%s_PTEta10Iso010_%06d", Label.c_str(), (int)thresholds[iT] * 100), "title;pt;#", ptbin, ptmin, ptmax));
      HPTEtaLargeIso010.push_back(new TH1D(Form("%s_PTEtaLargeIso010_%06d", Label.c_str(), (int)thresholds[iT] * 100), "title;pt;#", ptbin, ptmin, ptmax));
      HEtaIso010.push_back(new TH1D(Form("%s_EtaIso010_%06d", Label.c_str(), (int)thresholds[iT] * 100), "title;eta;#", etabin, etamin, etamax));
      HEtaPT20Iso010.push_back(new TH1D(Form("%s_EtaPT20Iso010_%06d", Label.c_str(), (int)thresholds[iT] * 100), "title;eta;#", etabin, etamin, etamax));
      HEtaPT25Iso010.push_back(new TH1D(Form("%s_EtaPT25Iso010_%06d", Label.c_str(), (int)thresholds[iT] * 100), "title;eta;#", etabin, etamin, etamax));
      HEtaPT200Iso010.push_back(new TH1D(Form("%s_EtaPT200Iso010_%06d", Label.c_str(), (int)thresholds[iT] * 100), "title;eta;#", etabin, etamin, etamax));
      HPTIso014.push_back(new TH1D(Form("%s_PTIso014_%06d", Label.c_str(), (int)thresholds[iT] * 100), "title;pt;#", ptbin, ptmin, ptmax));
      HPTEta10Iso014.push_back(new TH1D(Form("%s_PTEta10Iso014_%06d", Label.c_str(), (int)thresholds[iT] * 100), "title;pt;#", ptbin, ptmin, ptmax));
      HPTEtaLargeIso014.push_back(new TH1D(Form("%s_PTEtaLargeIso014_%06d", Label.c_str(), (int)thresholds[iT] * 100), "title;pt;#", ptbin, ptmin, ptmax));
      HEtaIso014.push_back(new TH1D(Form("%s_EtaIso014_%06d", Label.c_str(), (int)thresholds[iT] * 100), "title;eta;#", etabin, etamin, etamax));
      HEtaPT20Iso014.push_back(new TH1D(Form("%s_EtaPT20Iso014_%06d", Label.c_str(), (int)thresholds[iT] * 100), "title;eta;#", etabin, etamin, etamax));
      HEtaPT25Iso014.push_back(new TH1D(Form("%s_EtaPT25Iso014_%06d", Label.c_str(), (int)thresholds[iT] * 100), "title;eta;#", etabin, etamin, etamax));
      HEtaPT200Iso014.push_back(new TH1D(Form("%s_EtaPT200Iso014_%06d", Label.c_str(), (int)thresholds[iT] * 100), "title;eta;#", etabin, etamin, etamax));
      HPTIso023.push_back(new TH1D(Form("%s_PTIso023_%06d", Label.c_str(), (int)thresholds[iT] * 100), "title;pt;#", ptbin, ptmin, ptmax));
      HPTEta10Iso023.push_back(new TH1D(Form("%s_PTEta10Iso023_%06d", Label.c_str(), (int)thresholds[iT] * 100), "title;pt;#", ptbin, ptmin, ptmax));
      HPTEtaLargeIso023.push_back(new TH1D(Form("%s_PTEtaLargeIso023_%06d", Label.c_str(), (int)thresholds[iT] * 100), "title;pt;#", ptbin, ptmin, ptmax));
      HEtaIso023.push_back(new TH1D(Form("%s_EtaIso023_%06d", Label.c_str(), (int)thresholds[iT] * 100), "title;eta;#", etabin, etamin, etamax));
      HEtaPT20Iso023.push_back(new TH1D(Form("%s_EtaPT20Iso023_%06d", Label.c_str(), (int)thresholds[iT] * 100), "title;eta;#", etabin, etamin, etamax));
      HEtaPT25Iso023.push_back(new TH1D(Form("%s_EtaPT25Iso023_%06d", Label.c_str(), (int)thresholds[iT] * 100), "title;eta;#", etabin, etamin, etamax));
      HEtaPT200Iso023.push_back(new TH1D(Form("%s_EtaPT200Iso023_%06d", Label.c_str(), (int)thresholds[iT] * 100), "title;eta;#", etabin, etamin, etamax));
      HPTIso045.push_back(new TH1D(Form("%s_PTIso045_%06d", Label.c_str(), (int)thresholds[iT] * 100), "title;pt;#", ptbin, ptmin, ptmax));
      HPTEta10Iso045.push_back(new TH1D(Form("%s_PTEta10Iso045_%06d", Label.c_str(), (int)thresholds[iT] * 100), "title;pt;#", ptbin, ptmin, ptmax));
      HPTEtaLargeIso045.push_back(new TH1D(Form("%s_PTEtaLargeIso045_%06d", Label.c_str(), (int)thresholds[iT] * 100), "title;pt;#", ptbin, ptmin, ptmax));
      HEtaIso045.push_back(new TH1D(Form("%s_EtaIso045_%06d", Label.c_str(), (int)thresholds[iT] * 100), "title;eta;#", etabin, etamin, etamax));
      HEtaPT20Iso045.push_back(new TH1D(Form("%s_EtaPT20Iso045_%06d", Label.c_str(), (int)thresholds[iT] * 100), "title;eta;#", etabin, etamin, etamax));
      HEtaPT25Iso045.push_back(new TH1D(Form("%s_EtaPT25Iso045_%06d", Label.c_str(), (int)thresholds[iT] * 100), "title;eta;#", etabin, etamin, etamax));
      HEtaPT200Iso045.push_back(new TH1D(Form("%s_EtaPT200Iso045_%06d", Label.c_str(), (int)thresholds[iT] * 100), "title;eta;#", etabin, etamin, etamax));
      HTkIso.push_back(new TH1D(Form("%s_TkIso_%06d", Label.c_str(), (int)thresholds[iT] * 100), "title;iso;#", isobin, isomin, isomax));
      HTkIsoRestricted.push_back(new TH1D(Form("%s_TkIsoRestricted_%06d", Label.c_str(), (int)thresholds[iT] * 100), "title;iso;#", isobin, isomin, isomax));
      HTkIsoRestricted2.push_back(new TH1D(Form("%s_TkIsoRestricted2_%06d", Label.c_str(), (int)thresholds[iT] * 100), "title;iso;#", isobin, isomin, isomax));
      
      HPT[iT]->Sumw2();
      HPTEta10[iT]->Sumw2();
      HPTEtaLarge[iT]->Sumw2();
      HEta[iT]->Sumw2();
      HEtaPT20[iT]->Sumw2();
      HEtaPT25[iT]->Sumw2();
      HEtaPT200[iT]->Sumw2();
      HPTIso010[iT]->Sumw2();
      HPTEta10Iso010[iT]->Sumw2();
      HPTEtaLargeIso010[iT]->Sumw2();
      HEtaIso010[iT]->Sumw2();
      HEtaPT20Iso010[iT]->Sumw2();
      HEtaPT25Iso010[iT]->Sumw2();
      HEtaPT200Iso010[iT]->Sumw2();
      HPTIso014[iT]->Sumw2();
      HPTEta10Iso014[iT]->Sumw2();
      HPTEtaLargeIso014[iT]->Sumw2();
      HEtaIso014[iT]->Sumw2();
      HEtaPT20Iso014[iT]->Sumw2();
      HEtaPT25Iso014[iT]->Sumw2();
      HEtaPT200Iso014[iT]->Sumw2();
      HPTIso023[iT]->Sumw2();
      HPTEta10Iso023[iT]->Sumw2();
      HPTEtaLargeIso023[iT]->Sumw2();
      HEtaIso023[iT]->Sumw2();
      HEtaPT20Iso023[iT]->Sumw2();
      HEtaPT25Iso023[iT]->Sumw2();
      HEtaPT200Iso023[iT]->Sumw2();
      HPTIso045[iT]->Sumw2();
      HPTEta10Iso045[iT]->Sumw2();
      HPTEtaLargeIso045[iT]->Sumw2();
      HEtaIso045[iT]->Sumw2();
      HEtaPT20Iso045[iT]->Sumw2();
      HEtaPT25Iso045[iT]->Sumw2();
      HEtaPT200Iso045[iT]->Sumw2();
      HTkIso[iT]->Sumw2();
      HTkIsoRestricted[iT]->Sumw2();
      HTkIsoRestricted2[iT]->Sumw2();
   }
}

Histograms::~Histograms()
{
   // We don't have ownership over histograms!

   // for(int i = 0; i < (int)HPT.size(); i++)
   //    if(HPT[i] != NULL)
   //       delete HPT[i];
   // for(int i = 0; i < (int)HPTEta10.size(); i++)
   //    if(HPTEta10[i] != NULL)
   //       delete HPTEta10[i];
   // for(int i = 0; i < (int)HPTEtaLarge.size(); i++)
   //    if(HPTEtaLarge[i] != NULL)
   //       delete HPTEtaLarge[i];
   // for(int i = 0; i < (int)HEta.size(); i++)
   //    if(HEta[i] != NULL)
   //       delete HEta[i];
   // for(int i = 0; i < (int)HEtaPT20.size(); i++)
   //    if(HEtaPT20[i] != NULL)
   //       delete HEtaPT20[i];
   // for(int i = 0; i < (int)HEtaPT25.size(); i++)
   //    if(HEtaPT25[i] != NULL)
   //       delete HEtaPT25[i];
}

void Histograms::Fill(double check, double pt, double eta, double iso)
{
   for(int i = 0; i < (int)Thresholds.size(); i++)
   {
      if(check < Thresholds[i])
         continue;

      if(HPT[i] != NULL)                         HPT[i]->Fill(pt);
      if(HPTEta10[i] != NULL && fabs(eta) < 1)   HPTEta10[i]->Fill(pt);
      if(HPTEtaLarge[i] != NULL && fabs(eta) > 1)   HPTEtaLarge[i]->Fill(pt);
      if(HEta[i] != NULL)                        HEta[i]->Fill(eta);
      if(HEtaPT20[i] != NULL && pt > 20)         HEtaPT20[i]->Fill(eta);
      if(HEtaPT25[i] != NULL && pt > 25)         HEtaPT25[i]->Fill(eta);
      if(HEtaPT200[i] != NULL && pt > 200)       HEtaPT200[i]->Fill(eta);
      if(iso < 0.10)
      {
         if(HPTIso010[i] != NULL)                         HPTIso010[i]->Fill(pt);
         if(HPTEta10Iso010[i] != NULL && fabs(eta) < 1)   HPTEta10Iso010[i]->Fill(pt);
         if(HPTEtaLargeIso010[i] != NULL && fabs(eta) > 1)   HPTEtaLargeIso010[i]->Fill(pt);
         if(HEtaIso010[i] != NULL)                        HEtaIso010[i]->Fill(eta);
         if(HEtaPT20Iso010[i] != NULL && pt > 20)         HEtaPT20Iso010[i]->Fill(eta);
         if(HEtaPT25Iso010[i] != NULL && pt > 25)         HEtaPT25Iso010[i]->Fill(eta);
         if(HEtaPT200Iso010[i] != NULL && pt > 200)       HEtaPT200Iso010[i]->Fill(eta);
      }
      if(iso < 0.14)
      {
         if(HPTIso014[i] != NULL)                         HPTIso014[i]->Fill(pt);
         if(HPTEta10Iso014[i] != NULL && fabs(eta) < 1)   HPTEta10Iso014[i]->Fill(pt);
         if(HPTEtaLargeIso014[i] != NULL && fabs(eta) > 1)   HPTEtaLargeIso014[i]->Fill(pt);
         if(HEtaIso014[i] != NULL)                        HEtaIso014[i]->Fill(eta);
         if(HEtaPT20Iso014[i] != NULL && pt > 20)         HEtaPT20Iso014[i]->Fill(eta);
         if(HEtaPT25Iso014[i] != NULL && pt > 25)         HEtaPT25Iso014[i]->Fill(eta);
         if(HEtaPT200Iso014[i] != NULL && pt > 200)       HEtaPT200Iso014[i]->Fill(eta);
      }
      if(iso < 0.23)
      {
         if(HPTIso023[i] != NULL)                         HPTIso023[i]->Fill(pt);
         if(HPTEta10Iso023[i] != NULL && fabs(eta) < 1)   HPTEta10Iso023[i]->Fill(pt);
         if(HPTEtaLargeIso023[i] != NULL && fabs(eta) > 1)   HPTEtaLargeIso023[i]->Fill(pt);
         if(HEtaIso023[i] != NULL)                        HEtaIso023[i]->Fill(eta);
         if(HEtaPT20Iso023[i] != NULL && pt > 20)         HEtaPT20Iso023[i]->Fill(eta);
         if(HEtaPT25Iso023[i] != NULL && pt > 25)         HEtaPT25Iso023[i]->Fill(eta);
         if(HEtaPT200Iso023[i] != NULL && pt > 200)       HEtaPT200Iso023[i]->Fill(eta);
      }
      if(iso < 0.45)
      {
         if(HPTIso045[i] != NULL)                         HPTIso045[i]->Fill(pt);
         if(HPTEta10Iso045[i] != NULL && fabs(eta) < 1)   HPTEta10Iso045[i]->Fill(pt);
         if(HPTEtaLargeIso045[i] != NULL && fabs(eta) > 1)   HPTEtaLargeIso045[i]->Fill(pt);
         if(HEtaIso045[i] != NULL)                        HEtaIso045[i]->Fill(eta);
         if(HEtaPT20Iso045[i] != NULL && pt > 20)         HEtaPT20Iso045[i]->Fill(eta);
         if(HEtaPT25Iso045[i] != NULL && pt > 25)         HEtaPT25Iso045[i]->Fill(eta);
         if(HEtaPT200Iso045[i] != NULL && pt > 200)       HEtaPT200Iso045[i]->Fill(eta);
      }
      if(HTkIso[i] != NULL)                      HTkIso[i]->Fill(iso);
      if(HTkIsoRestricted[i] != NULL && fabs(eta) < 1.5 && pt > 20) HTkIsoRestricted[i]->Fill(iso);
      if(HTkIsoRestricted2[i] != NULL && fabs(eta) < 2.1 && pt > 20) HTkIsoRestricted2[i]->Fill(iso);
   }
}

void Histograms::Fill(FourVector Check, FourVector P, double iso)
{
   for(int i = 0; i < (int)Thresholds.size(); i++)
   {
      if(Check.GetPT() < Thresholds[i])
         continue;

      if(HPT[i] != NULL)                               HPT[i]->Fill(P.GetPT());
      if(HPTEta10[i] != NULL && P.GetAbsEta() < 1.0)   HPTEta10[i]->Fill(P.GetPT());
      if(HPTEtaLarge[i] != NULL && P.GetAbsEta() > 1.0)   HPTEtaLarge[i]->Fill(P.GetPT());
      if(HEta[i] != NULL)                              HEta[i]->Fill(P.GetEta());
      if(HEtaPT20[i] != NULL && P.GetPT() > 20)        HEtaPT20[i]->Fill(P.GetEta());
      if(HEtaPT25[i] != NULL && P.GetPT() > 25)        HEtaPT25[i]->Fill(P.GetEta());
      if(HEtaPT200[i] != NULL && P.GetPT() > 200)      HEtaPT200[i]->Fill(P.GetEta());
      if(iso < 0.10)
      {
         if(HPTIso010[i] != NULL)                               HPTIso010[i]->Fill(P.GetPT());
         if(HPTEta10Iso010[i] != NULL && P.GetAbsEta() < 1.0)   HPTEta10Iso010[i]->Fill(P.GetPT());
         if(HPTEtaLargeIso010[i] != NULL && P.GetAbsEta() > 1.0)   HPTEtaLargeIso010[i]->Fill(P.GetPT());
         if(HEtaIso010[i] != NULL)                              HEtaIso010[i]->Fill(P.GetEta());
         if(HEtaPT20Iso010[i] != NULL && P.GetPT() > 20)        HEtaPT20Iso010[i]->Fill(P.GetEta());
         if(HEtaPT25Iso010[i] != NULL && P.GetPT() > 25)        HEtaPT25Iso010[i]->Fill(P.GetEta());
         if(HEtaPT200Iso010[i] != NULL && P.GetPT() > 200)      HEtaPT200Iso010[i]->Fill(P.GetEta());
      }
      if(iso < 0.14)
      {
         if(HPTIso014[i] != NULL)                               HPTIso014[i]->Fill(P.GetPT());
         if(HPTEta10Iso014[i] != NULL && P.GetAbsEta() < 1.0)   HPTEta10Iso014[i]->Fill(P.GetPT());
         if(HPTEtaLargeIso014[i] != NULL && P.GetAbsEta() > 1.0)   HPTEtaLargeIso014[i]->Fill(P.GetPT());
         if(HEtaIso014[i] != NULL)                              HEtaIso014[i]->Fill(P.GetEta());
         if(HEtaPT20Iso014[i] != NULL && P.GetPT() > 20)        HEtaPT20Iso014[i]->Fill(P.GetEta());
         if(HEtaPT25Iso014[i] != NULL && P.GetPT() > 25)        HEtaPT25Iso014[i]->Fill(P.GetEta());
         if(HEtaPT200Iso014[i] != NULL && P.GetPT() > 200)      HEtaPT200Iso014[i]->Fill(P.GetEta());
      }
      if(iso < 0.23)
      {
         if(HPTIso023[i] != NULL)                               HPTIso023[i]->Fill(P.GetPT());
         if(HPTEta10Iso023[i] != NULL && P.GetAbsEta() < 1.0)   HPTEta10Iso023[i]->Fill(P.GetPT());
         if(HPTEtaLargeIso023[i] != NULL && P.GetAbsEta() > 1.0)   HPTEtaLargeIso023[i]->Fill(P.GetPT());
         if(HEtaIso023[i] != NULL)                              HEtaIso023[i]->Fill(P.GetEta());
         if(HEtaPT20Iso023[i] != NULL && P.GetPT() > 20)        HEtaPT20Iso023[i]->Fill(P.GetEta());
         if(HEtaPT25Iso023[i] != NULL && P.GetPT() > 25)        HEtaPT25Iso023[i]->Fill(P.GetEta());
         if(HEtaPT200Iso023[i] != NULL && P.GetPT() > 200)      HEtaPT200Iso023[i]->Fill(P.GetEta());
      }
      if(iso < 0.45)
      {
         if(HPTIso045[i] != NULL)                               HPTIso045[i]->Fill(P.GetPT());
         if(HPTEta10Iso045[i] != NULL && P.GetAbsEta() < 1.0)   HPTEta10Iso045[i]->Fill(P.GetPT());
         if(HPTEtaLargeIso045[i] != NULL && P.GetAbsEta() > 1.0)   HPTEtaLargeIso045[i]->Fill(P.GetPT());
         if(HEtaIso045[i] != NULL)                              HEtaIso045[i]->Fill(P.GetEta());
         if(HEtaPT20Iso045[i] != NULL && P.GetPT() > 20)        HEtaPT20Iso045[i]->Fill(P.GetEta());
         if(HEtaPT25Iso045[i] != NULL && P.GetPT() > 25)        HEtaPT25Iso045[i]->Fill(P.GetEta());
         if(HEtaPT200Iso045[i] != NULL && P.GetPT() > 200)      HEtaPT200Iso045[i]->Fill(P.GetEta());
      }
      if(HTkIso[i] != NULL)                          HTkIso[i]->Fill(iso);
      if(HTkIsoRestricted[i] != NULL && P.GetAbsEta() < 1.5 && P.GetPT() > 20) HTkIsoRestricted[i]->Fill(iso);
      if(HTkIsoRestricted2[i] != NULL && P.GetAbsEta() < 2.1 && P.GetPT() > 20) HTkIsoRestricted2[i]->Fill(iso);
   }
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
   
   for(int i = 0; i < (int)HPTEta10.size(); i++)
   {
      if(HPTEta10[i] == NULL)
         continue;

      if(Directory != NULL)
         HPTEta10[i]->SetDirectory(Directory);
      HPTEta10[i]->Write();
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
   
   for(int i = 0; i < (int)HPTIso010.size(); i++)
   {
      if(HPTIso010[i] == NULL)
         continue;

      if(Directory != NULL)
         HPTIso010[i]->SetDirectory(Directory);
      HPTIso010[i]->Write();
   }
   
   for(int i = 0; i < (int)HPTEta10Iso010.size(); i++)
   {
      if(HPTEta10Iso010[i] == NULL)
         continue;

      if(Directory != NULL)
         HPTEta10Iso010[i]->SetDirectory(Directory);
      HPTEta10Iso010[i]->Write();
   }
   
   for(int i = 0; i < (int)HPTEtaLargeIso010.size(); i++)
   {
      if(HPTEtaLargeIso010[i] == NULL)
         continue;

      if(Directory != NULL)
         HPTEtaLargeIso010[i]->SetDirectory(Directory);
      HPTEtaLargeIso010[i]->Write();
   }
   
   for(int i = 0; i < (int)HEtaIso010.size(); i++)
   {
      if(HEtaIso010[i] == NULL)
         continue;

      if(Directory != NULL)
         HEtaIso010[i]->SetDirectory(Directory);
      HEtaIso010[i]->Write();
   }
   
   for(int i = 0; i < (int)HEtaPT20Iso010.size(); i++)
   {
      if(HEtaPT20Iso010[i] == NULL)
         continue;

      if(Directory != NULL)
         HEtaPT20Iso010[i]->SetDirectory(Directory);
      HEtaPT20Iso010[i]->Write();
   }
   
   for(int i = 0; i < (int)HEtaPT25Iso010.size(); i++)
   {
      if(HEtaPT25Iso010[i] == NULL)
         continue;

      if(Directory != NULL)
         HEtaPT25Iso010[i]->SetDirectory(Directory);
      HEtaPT25Iso010[i]->Write();
   }
   
   for(int i = 0; i < (int)HEtaPT200Iso010.size(); i++)
   {
      if(HEtaPT200Iso010[i] == NULL)
         continue;

      if(Directory != NULL)
         HEtaPT200Iso010[i]->SetDirectory(Directory);
      HEtaPT200Iso010[i]->Write();
   }
   
   for(int i = 0; i < (int)HPTIso014.size(); i++)
   {
      if(HPTIso014[i] == NULL)
         continue;

      if(Directory != NULL)
         HPTIso014[i]->SetDirectory(Directory);
      HPTIso014[i]->Write();
   }
   
   for(int i = 0; i < (int)HPTEta10Iso014.size(); i++)
   {
      if(HPTEta10Iso014[i] == NULL)
         continue;

      if(Directory != NULL)
         HPTEta10Iso014[i]->SetDirectory(Directory);
      HPTEta10Iso014[i]->Write();
   }
   
   for(int i = 0; i < (int)HPTEtaLargeIso014.size(); i++)
   {
      if(HPTEtaLargeIso014[i] == NULL)
         continue;

      if(Directory != NULL)
         HPTEtaLargeIso014[i]->SetDirectory(Directory);
      HPTEtaLargeIso014[i]->Write();
   }
   
   for(int i = 0; i < (int)HEtaIso014.size(); i++)
   {
      if(HEtaIso014[i] == NULL)
         continue;

      if(Directory != NULL)
         HEtaIso014[i]->SetDirectory(Directory);
      HEtaIso014[i]->Write();
   }
   
   for(int i = 0; i < (int)HEtaPT20Iso014.size(); i++)
   {
      if(HEtaPT20Iso014[i] == NULL)
         continue;

      if(Directory != NULL)
         HEtaPT20Iso014[i]->SetDirectory(Directory);
      HEtaPT20Iso014[i]->Write();
   }
   
   for(int i = 0; i < (int)HEtaPT25Iso014.size(); i++)
   {
      if(HEtaPT25Iso014[i] == NULL)
         continue;

      if(Directory != NULL)
         HEtaPT25Iso014[i]->SetDirectory(Directory);
      HEtaPT25Iso014[i]->Write();
   }
   
   for(int i = 0; i < (int)HEtaPT200Iso014.size(); i++)
   {
      if(HEtaPT200Iso014[i] == NULL)
         continue;

      if(Directory != NULL)
         HEtaPT200Iso014[i]->SetDirectory(Directory);
      HEtaPT200Iso014[i]->Write();
   }
   
   for(int i = 0; i < (int)HPTIso023.size(); i++)
   {
      if(HPTIso023[i] == NULL)
         continue;

      if(Directory != NULL)
         HPTIso023[i]->SetDirectory(Directory);
      HPTIso023[i]->Write();
   }
   
   for(int i = 0; i < (int)HPTEta10Iso023.size(); i++)
   {
      if(HPTEta10Iso023[i] == NULL)
         continue;

      if(Directory != NULL)
         HPTEta10Iso023[i]->SetDirectory(Directory);
      HPTEta10Iso023[i]->Write();
   }
   
   for(int i = 0; i < (int)HPTEtaLargeIso023.size(); i++)
   {
      if(HPTEtaLargeIso023[i] == NULL)
         continue;

      if(Directory != NULL)
         HPTEtaLargeIso023[i]->SetDirectory(Directory);
      HPTEtaLargeIso023[i]->Write();
   }
   
   for(int i = 0; i < (int)HEtaIso023.size(); i++)
   {
      if(HEtaIso023[i] == NULL)
         continue;

      if(Directory != NULL)
         HEtaIso023[i]->SetDirectory(Directory);
      HEtaIso023[i]->Write();
   }
   
   for(int i = 0; i < (int)HEtaPT20Iso023.size(); i++)
   {
      if(HEtaPT20Iso023[i] == NULL)
         continue;

      if(Directory != NULL)
         HEtaPT20Iso023[i]->SetDirectory(Directory);
      HEtaPT20Iso023[i]->Write();
   }
   
   for(int i = 0; i < (int)HEtaPT25Iso023.size(); i++)
   {
      if(HEtaPT25Iso023[i] == NULL)
         continue;

      if(Directory != NULL)
         HEtaPT25Iso023[i]->SetDirectory(Directory);
      HEtaPT25Iso023[i]->Write();
   }
   
   for(int i = 0; i < (int)HEtaPT200Iso023.size(); i++)
   {
      if(HEtaPT200Iso023[i] == NULL)
         continue;

      if(Directory != NULL)
         HEtaPT200Iso023[i]->SetDirectory(Directory);
      HEtaPT200Iso023[i]->Write();
   }
   
   for(int i = 0; i < (int)HPTIso045.size(); i++)
   {
      if(HPTIso045[i] == NULL)
         continue;

      if(Directory != NULL)
         HPTIso045[i]->SetDirectory(Directory);
      HPTIso045[i]->Write();
   }
   
   for(int i = 0; i < (int)HPTEta10Iso045.size(); i++)
   {
      if(HPTEta10Iso045[i] == NULL)
         continue;

      if(Directory != NULL)
         HPTEta10Iso045[i]->SetDirectory(Directory);
      HPTEta10Iso045[i]->Write();
   }
   
   for(int i = 0; i < (int)HPTEtaLargeIso045.size(); i++)
   {
      if(HPTEtaLargeIso045[i] == NULL)
         continue;

      if(Directory != NULL)
         HPTEtaLargeIso045[i]->SetDirectory(Directory);
      HPTEtaLargeIso045[i]->Write();
   }
   
   for(int i = 0; i < (int)HEtaIso045.size(); i++)
   {
      if(HEtaIso045[i] == NULL)
         continue;

      if(Directory != NULL)
         HEtaIso045[i]->SetDirectory(Directory);
      HEtaIso045[i]->Write();
   }
   
   for(int i = 0; i < (int)HEtaPT20Iso045.size(); i++)
   {
      if(HEtaPT20Iso045[i] == NULL)
         continue;

      if(Directory != NULL)
         HEtaPT20Iso045[i]->SetDirectory(Directory);
      HEtaPT20Iso045[i]->Write();
   }
   
   for(int i = 0; i < (int)HEtaPT25Iso045.size(); i++)
   {
      if(HEtaPT25Iso045[i] == NULL)
         continue;

      if(Directory != NULL)
         HEtaPT25Iso045[i]->SetDirectory(Directory);
      HEtaPT25Iso045[i]->Write();
   }
   
   for(int i = 0; i < (int)HEtaPT200Iso045.size(); i++)
   {
      if(HEtaPT200Iso045[i] == NULL)
         continue;

      if(Directory != NULL)
         HEtaPT200Iso045[i]->SetDirectory(Directory);
      HEtaPT200Iso045[i]->Write();
   }
   
   for(int i = 0; i < (int)HTkIso.size(); i++)
   {
      if(HTkIso[i] == NULL)
         continue;

      if(Directory != NULL)
         HTkIso[i]->SetDirectory(Directory);
      HTkIso[i]->Write();
   }
   
   for(int i = 0; i < (int)HTkIsoRestricted.size(); i++)
   {
      if(HTkIsoRestricted[i] == NULL)
         continue;

      if(Directory != NULL)
         HTkIsoRestricted[i]->SetDirectory(Directory);
      HTkIsoRestricted[i]->Write();
   }
   
   for(int i = 0; i < (int)HTkIsoRestricted2.size(); i++)
   {
      if(HTkIsoRestricted2[i] == NULL)
         continue;

      if(Directory != NULL)
         HTkIsoRestricted2[i]->SetDirectory(Directory);
      HTkIsoRestricted2[i]->Write();
   }
}


