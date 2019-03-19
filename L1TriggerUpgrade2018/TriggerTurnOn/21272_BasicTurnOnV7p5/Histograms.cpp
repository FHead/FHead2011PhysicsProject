#include "Histograms.h"

Histograms::Histograms(int ptbin, double ptmin, double ptmax,
   int Etabin, double Etamin, double Etamax,
   int isobin, double isomin, double isomax,
   int dxybin, double dxymin, double dxymax,
   vector<double> &thresholds, string label)
{
   int rbin = 100;
   double rmin = 0.0;
   double rmax = 2.5;

   int drbin = 100;
   double drmin = 0.0;
   double drmax = 1.0;

   Thresholds = thresholds;
   Thresholds.insert(Thresholds.begin(), -1);

   for(int iT = 0; iT < (int)Thresholds.size(); iT++)
   {
      string Label = label;
      string Cut = Form("%06d", (int)Thresholds[iT] * 100);
      
      if(Thresholds[iT] < 0)
      {
         Label = label + "NoMatch";
         Cut = "000000";
      }

      HPT.push_back(                  New(Label, "PT",                   Cut, ";PT;#",  ptbin,  ptmin,  ptmax));
      HPTEta15.push_back(             New(Label, "PTEta15",              Cut, ";PT;#",  ptbin,  ptmin,  ptmax));
      HPTEtaLarge.push_back(          New(Label, "PTEtaLarge",           Cut, ";PT;#",  ptbin,  ptmin,  ptmax));
      HResponse.push_back(            New(Label, "Response",             Cut, ";R;#",   rbin,   rmin,   rmax));
      HResponseEta15.push_back(       New(Label, "ResponseEta15",        Cut, ";R;#",   rbin,   rmin,   rmax));
      HResponseEtaLarge.push_back(    New(Label, "ResponseEtaLarge",     Cut, ";R;#",   rbin,   rmin,   rmax));
      HResponsePT10.push_back(        New(Label, "ResponsePT10",         Cut, ";R;#",   rbin,   rmin,   rmax));
      HResponsePT10Eta15.push_back(   New(Label, "ResponsePT10Eta15",    Cut, ";R;#",   rbin,   rmin,   rmax));
      HResponsePT10EtaLarge.push_back(New(Label, "ResponsePT10EtaLarge", Cut, ";R;#",   rbin,   rmin,   rmax));
      HResponsePT50.push_back(        New(Label, "ResponsePT50",         Cut, ";R;#",   rbin,   rmin,   rmax));
      HResponsePT100.push_back(       New(Label, "ResponsePT100",        Cut, ";R;#",   rbin,   rmin,   rmax));
      HResponsePT150.push_back(       New(Label, "ResponsePT150",        Cut, ";R;#",   rbin,   rmin,   rmax));
      HResponsePT200.push_back(       New(Label, "ResponsePT200",        Cut, ";R;#",   rbin,   rmin,   rmax));
      HEta.push_back(                 New(Label, "Eta",                  Cut, ";Eta;#", Etabin, Etamin, Etamax));
      HEtaPT3to5.push_back(           New(Label, "EtaPT3to5",            Cut, ";Eta;#", Etabin, Etamin, Etamax));
      HEtaPT3to10.push_back(          New(Label, "EtaPT3to10",           Cut, ";Eta;#", Etabin, Etamin, Etamax));
      HEtaPT3to15.push_back(          New(Label, "EtaPT3to15",           Cut, ";Eta;#", Etabin, Etamin, Etamax));
      HEtaPT15.push_back(             New(Label, "EtaPT15",              Cut, ";Eta;#", Etabin, Etamin, Etamax));
      HEtaPT20.push_back(             New(Label, "EtaPT20",              Cut, ";Eta;#", Etabin, Etamin, Etamax));
      HEtaPT25.push_back(             New(Label, "EtaPT25",              Cut, ";Eta;#", Etabin, Etamin, Etamax));
      HEtaPT30.push_back(             New(Label, "EtaPT30",              Cut, ";Eta;#", Etabin, Etamin, Etamax));
      HEtaPT100.push_back(            New(Label, "EtaPT100",             Cut, ";Eta;#", Etabin, Etamin, Etamax));
      HEtaPT200.push_back(            New(Label, "EtaPT200",             Cut, ";Eta;#", Etabin, Etamin, Etamax));
      HTkIso.push_back(               New(Label, "TkIso",                Cut, ";Iso;#", isobin, isomin, isomax));
      HTkIsoPT10.push_back(           New(Label, "TkIsoPT10",            Cut, ";Iso;#", isobin, isomin, isomax));
      HTkIsoPT20.push_back(           New(Label, "TkIsoPT20",            Cut, ";Iso;#", isobin, isomin, isomax));
      HTkIsoPT30.push_back(           New(Label, "TkIsoPT30",            Cut, ";Iso;#", isobin, isomin, isomax));
      HTkIsoPT40.push_back(           New(Label, "TkIsoPT40",            Cut, ";Iso;#", isobin, isomin, isomax));
      HTkIsoEta15.push_back(          New(Label, "TkIsoEta15",           Cut, ";Iso;#", isobin, isomin, isomax));
      HTkIsoEtaLarge.push_back(       New(Label, "TkIsoEtaLarge",        Cut, ";Iso;#", isobin, isomin, isomax));
      HTkIsoPT10Eta15.push_back(      New(Label, "TkIsoPT10Eta15",       Cut, ";Iso;#", isobin, isomin, isomax));
      HTkIsoPT10EtaLarge.push_back(   New(Label, "TkIsoPT10EtaLarge",    Cut, ";Iso;#", isobin, isomin, isomax));
      HDR.push_back(                  New(Label, "DR",                   Cut, ";DR;#",  drbin,  drmin,  drmax));
      HDRPT10.push_back(              New(Label, "DRPT10",               Cut, ";DR;#",  drbin,  drmin,  drmax));
      HDRPT20.push_back(              New(Label, "DRPT20",               Cut, ";DR;#",  drbin,  drmin,  drmax));
      HDRPT50.push_back(              New(Label, "DRPT50",               Cut, ";DR;#",  drbin,  drmin,  drmax));
      HDREta15.push_back(             New(Label, "DREta15",              Cut, ";DR;#",  drbin,  drmin,  drmax));
      HDRPT10Eta15.push_back(         New(Label, "DRPT10Eta15",          Cut, ";DR;#",  drbin,  drmin,  drmax));
      HDRPT20Eta15.push_back(         New(Label, "DRPT20Eta15",          Cut, ";DR;#",  drbin,  drmin,  drmax));
      HDREtaLarge.push_back(          New(Label, "DREtaLarge",           Cut, ";DR;#",  drbin,  drmin,  drmax));
      HDRPT10EtaLarge.push_back(      New(Label, "DRPT10EtaLarge",       Cut, ";DR;#",  drbin,  drmin,  drmax));
      HDRPT20EtaLarge.push_back(      New(Label, "DRPT20EtaLarge",       Cut, ";DR;#",  drbin,  drmin,  drmax));
      HDXY.push_back(                 New(Label, "DXY",                  Cut, ";DXY;#", dxybin, dxymin, dxymax));

      HPT[iT]                  ->Sumw2();
      HPTEta15[iT]             ->Sumw2();
      HPTEtaLarge[iT]          ->Sumw2();
      HResponse[iT]            ->Sumw2();
      HResponseEta15[iT]       ->Sumw2();
      HResponseEtaLarge[iT]    ->Sumw2();
      HResponsePT10[iT]        ->Sumw2();
      HResponsePT10Eta15[iT]   ->Sumw2();
      HResponsePT10EtaLarge[iT]->Sumw2();
      HResponsePT50[iT]        ->Sumw2();
      HResponsePT100[iT]       ->Sumw2();
      HResponsePT150[iT]       ->Sumw2();
      HResponsePT200[iT]       ->Sumw2();
      HEta[iT]                 ->Sumw2();
      HEtaPT3to5[iT]           ->Sumw2();
      HEtaPT3to10[iT]          ->Sumw2();
      HEtaPT3to15[iT]          ->Sumw2();
      HEtaPT15[iT]             ->Sumw2();
      HEtaPT20[iT]             ->Sumw2();
      HEtaPT25[iT]             ->Sumw2();
      HEtaPT30[iT]             ->Sumw2();
      HEtaPT100[iT]            ->Sumw2();
      HEtaPT200[iT]            ->Sumw2();
      HTkIso[iT]               ->Sumw2();
      HTkIsoPT10[iT]           ->Sumw2();
      HTkIsoPT20[iT]           ->Sumw2();
      HTkIsoPT30[iT]           ->Sumw2();
      HTkIsoPT40[iT]           ->Sumw2();
      HTkIsoEta15[iT]          ->Sumw2();
      HTkIsoEtaLarge[iT]       ->Sumw2();
      HTkIsoPT10Eta15[iT]      ->Sumw2();
      HTkIsoPT10EtaLarge[iT]   ->Sumw2();
      HDR[iT]                  ->Sumw2();
      HDRPT10[iT]              ->Sumw2();
      HDRPT20[iT]              ->Sumw2();
      HDRPT50[iT]              ->Sumw2();
      HDREta15[iT]             ->Sumw2();
      HDRPT10Eta15[iT]         ->Sumw2();
      HDRPT20Eta15[iT]         ->Sumw2();
      HDREtaLarge[iT]          ->Sumw2();
      HDRPT10EtaLarge[iT]      ->Sumw2();
      HDRPT20EtaLarge[iT]      ->Sumw2();
      HDXY[iT]                 ->Sumw2();
   }
}

Histograms::~Histograms()
{
}

void Histograms::Fill(double check, double pt, double Eta, double iso, double dr, bool Mode, int Region, double dxy)
{
   for(int i = 0; i < (int)Thresholds.size(); i++)
   {
      if(Mode == MODE_NOMATCH && i != 0)
         continue;
      if(Mode == MODE_NORMAL && i == 0)
         continue;

      if(Thresholds[i] > 0 && check < Thresholds[i])
         continue;

      if(HPT[i] != NULL)                                             HPT[i]->Fill(pt);
      if(HPTEta15[i] != NULL && Region == 0)                         HPTEta15[i]->Fill(pt);
      if(HPTEtaLarge[i] != NULL && Region == 1)                      HPTEtaLarge[i]->Fill(pt);
      if(HResponse[i] != NULL)                                       HResponse[i]->Fill(check / pt);
      if(HResponseEta15[i] != NULL && Region == 0)                   HResponseEta15[i]->Fill(check / pt);
      if(HResponseEtaLarge[i] != NULL && Region == 1)                HResponseEtaLarge[i]->Fill(check / pt);
      if(HResponsePT10[i] != NULL)                                   HResponsePT10[i]->Fill(check / pt);
      if(HResponsePT10Eta15[i] != NULL && pt > 10 && Region == 0)    HResponsePT10Eta15[i]->Fill(check / pt);
      if(HResponsePT10EtaLarge[i] != NULL && pt > 10 && Region == 1) HResponsePT10EtaLarge[i]->Fill(check / pt);
      if(HResponsePT50[i] != NULL && pt > 50)                        HResponsePT50[i]->Fill(check / pt);
      if(HResponsePT100[i] != NULL && pt > 100)                      HResponsePT100[i]->Fill(check / pt);
      if(HResponsePT150[i] != NULL && pt > 150)                      HResponsePT150[i]->Fill(check / pt);
      if(HResponsePT200[i] != NULL && pt > 200)                      HResponsePT200[i]->Fill(check / pt);
      if(HEta[i] != NULL)                                            HEta[i]->Fill(Eta);
      if(HEtaPT3to5[i] != NULL && pt > 3 && pt < 5)                  HEtaPT3to5[i]->Fill(Eta);
      if(HEtaPT3to10[i] != NULL && pt > 3 && pt < 10)                HEtaPT3to10[i]->Fill(Eta);
      if(HEtaPT3to15[i] != NULL && pt > 3 && pt < 15)                HEtaPT3to15[i]->Fill(Eta);
      if(HEtaPT15[i] != NULL && pt > 15)                             HEtaPT15[i]->Fill(Eta);
      if(HEtaPT20[i] != NULL && pt > 20)                             HEtaPT20[i]->Fill(Eta);
      if(HEtaPT25[i] != NULL && pt > 25)                             HEtaPT25[i]->Fill(Eta);
      if(HEtaPT30[i] != NULL && pt > 30)                             HEtaPT30[i]->Fill(Eta);
      if(HEtaPT100[i] != NULL && pt > 100)                           HEtaPT100[i]->Fill(Eta);
      if(HEtaPT200[i] != NULL && pt > 200)                           HEtaPT200[i]->Fill(Eta);
      if(HTkIso[i] != NULL)                                          HTkIso[i]->Fill(iso);
      if(HTkIsoPT10[i] != NULL && pt > 10)                           HTkIsoPT10[i]->Fill(iso);
      if(HTkIsoPT20[i] != NULL && pt > 20)                           HTkIsoPT20[i]->Fill(iso);
      if(HTkIsoPT30[i] != NULL && pt > 30)                           HTkIsoPT30[i]->Fill(iso);
      if(HTkIsoPT40[i] != NULL && pt > 40)                           HTkIsoPT40[i]->Fill(iso);
      if(HTkIsoEta15[i] != NULL && Region == 0)                      HTkIsoEta15[i]->Fill(iso);
      if(HTkIsoEtaLarge[i] != NULL && Region == 1)                   HTkIsoEtaLarge[i]->Fill(iso);
      if(HTkIsoPT10Eta15[i] != NULL && Region == 0 && pt > 10)       HTkIsoPT10Eta15[i]->Fill(iso);
      if(HTkIsoPT10EtaLarge[i] != NULL && Region == 1 && pt > 10)    HTkIsoPT10EtaLarge[i]->Fill(iso);
      if(HDR[i] != NULL)                                             HDR[i]->Fill(dr);
      if(HDRPT10[i] != NULL && pt > 10)                              HDRPT10[i]->Fill(dr);
      if(HDRPT20[i] != NULL && pt > 20)                              HDRPT20[i]->Fill(dr);
      if(HDRPT50[i] != NULL && pt > 50)                              HDRPT50[i]->Fill(dr);
      if(HDREta15[i] != NULL && Region == 0)                         HDREta15[i]->Fill(dr);
      if(HDRPT10Eta15[i] != NULL && pt > 10 && Region == 0)          HDRPT10Eta15[i]->Fill(dr);
      if(HDRPT20Eta15[i] != NULL && pt > 20 && Region == 0)          HDRPT20Eta15[i]->Fill(dr);
      if(HDREtaLarge[i] != NULL && Region == 1)                      HDREtaLarge[i]->Fill(dr);
      if(HDRPT10EtaLarge[i] != NULL && pt > 10 && Region == 1)       HDRPT10EtaLarge[i]->Fill(dr);
      if(HDRPT20EtaLarge[i] != NULL && pt > 20 && Region == 1)       HDRPT20EtaLarge[i]->Fill(dr);
      if(HDXY[i] != NULL)                                            HDXY[i]->Fill(dxy);
   }
}

void Histograms::Fill(FourVector Check, FourVector P, double iso, int Region, double dxy)
{
   if(P[0] > 0 && Check[0] > 0)
      Fill(Check.GetPT(), P.GetPT(), P.GetEta(), iso, GetDR(Check, P), MODE_NORMAL, Region, dxy);
   if(P[0] > 0)
      Fill(Check.GetPT(), P.GetPT(), P.GetEta(), iso, GetDR(Check, P), MODE_NOMATCH, Region, dxy);
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
   Write(HResponsePT50,         Directory);
   Write(HResponsePT100,        Directory);
   Write(HResponsePT150,        Directory);
   Write(HResponsePT200,        Directory);
   Write(HEta,                  Directory);
   Write(HEtaPT3to5,            Directory);
   Write(HEtaPT3to10,           Directory);
   Write(HEtaPT3to15,           Directory);
   Write(HEtaPT15,              Directory);
   Write(HEtaPT20,              Directory);
   Write(HEtaPT25,              Directory);
   Write(HEtaPT30,              Directory);
   Write(HEtaPT100,             Directory);
   Write(HEtaPT200,             Directory);
   Write(HTkIso,                Directory);
   Write(HTkIsoPT10,            Directory);
   Write(HTkIsoPT20,            Directory);
   Write(HTkIsoPT30,            Directory);
   Write(HTkIsoPT40,            Directory);
   Write(HTkIsoEta15,           Directory);
   Write(HTkIsoEtaLarge,        Directory);
   Write(HTkIsoPT10Eta15,       Directory);
   Write(HTkIsoPT10EtaLarge,    Directory);
   Write(HDR,                   Directory);
   Write(HDRPT10,               Directory);
   Write(HDRPT20,               Directory);
   Write(HDRPT50,               Directory);
   Write(HDREta15,              Directory);
   Write(HDRPT10Eta15,          Directory);
   Write(HDRPT20Eta15,          Directory);
   Write(HDREtaLarge,           Directory);
   Write(HDRPT10EtaLarge,       Directory);
   Write(HDRPT20EtaLarge,       Directory);
   Write(HDXY,                  Directory);
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

TH1D *Histograms::New(string Label, string Name, string Cut, string Title, int Bin, double Min, double Max)
{
   return (new TH1D((Label + "_" + Name + "_" + Cut).c_str(), Title.c_str(), Bin, Min, Max));
}
