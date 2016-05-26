#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TH2D.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "SetStyle.h"

#define PI 3.14159265358979323846264338327950288479716939937510

int main();
void SetAlias(TTree *Tree);
void SetColor(vector<TH1D *> &H);
void Symmetrize(TH1D *H);
void PrintBin(ostream &out, vector<TH1D *> &H);

int main()
{
   SetThesisStyle();

   vector<string> FileNames;
   FileNames.push_back("ggtohtoEpMm_SM_115to135GeV_ggPDF_NoCuts_All.root");
   FileNames.push_back("ggtohtoEpMm_SMpMcwwt_1_115to125GeV_ggPDF_NoCuts_All.root");
   FileNames.push_back("ggtohtoEpMm_SMpcwwt_1_115to135GeV_ggPDF_NoCuts_All.root");
   FileNames.push_back("ggtohtoEpMm_SMpMcww_1_115to135GeV_ggPDF_NoCuts_All.root");
   FileNames.push_back("ggtohtoEpMm_SMpcww_1_115to135GeV_ggPDF_NoCuts_All.root");
   FileNames.push_back("htoEpMm_SM_125GeV_noPDF_NoCuts_All.root");
   // FileNames.push_back("ggtohto2l2nu_SM_115to135GeV_ggPDF_Full.root");
   // FileNames.push_back("ggtohto2l2nu_SMpA2WW_115to135GeV_ggPDF_Full_0d1.root");
   // FileNames.push_back("ggtohto2l2nu_SMpA3WW_115to135GeV_ggPDF_Full_0d5.root");
   // FileNames.push_back("ggtohto2l2nu_SMpA4WW_115to135GeV_ggPDF_Full_1.root");
   // FileNames.push_back("ggtohto2l2nu_SMpA2WW_115to135GeV_ggPDF_Full_0d1.root");
   // FileNames.push_back("ggtohto2l2nu_SMpA3WW_115to135GeV_ggPDF_Full_0d5.root");
   // FileNames.push_back("ggtohto2l2nu_SMpA4WW_115to135GeV_ggPDF_Full_1.root");
   // FileNames.push_back("ggtohto2l2nu_SMpA2WW_115to135GeV_ggPDF_Full_0d1.root");
   // FileNames.push_back("ggtohto2l2nu_SMpA3WW_115to135GeV_ggPDF_Full_0d5.root");
   // FileNames.push_back("ggtohto2l2nu_SMpA4WW_115to135GeV_ggPDF_Full_1.root");
   // FileNames.push_back("hto2l2nu_SM_125GeV_noPDF_Full.root");
   // FileNames.push_back("hto2l2nu_SMpA2WW_125GeV_noPDF_Full_0d1.root");
   // FileNames.push_back("hto2l2nu_SMpA3WW_125GeV_noPDF_Full_0d5.root");
   // FileNames.push_back("hto2l2nu_SMpA4WW_125GeV_noPDF_Full_1.root");
   // FileNames.push_back("hto2l2nu_SMpA2WW_125GeV_noPDF_Full_0d1.root");
   // FileNames.push_back("hto2l2nu_SMpA3WW_125GeV_noPDF_Full_0d5.root");
   // FileNames.push_back("hto2l2nu_SMpA4WW_125GeV_noPDF_Full_1.root");
   // FileNames.push_back("hto2l2nu_SMpA2WW_125GeV_noPDF_Full_0d1.root");
   // FileNames.push_back("hto2l2nu_SMpA3WW_125GeV_noPDF_Full_0d5.root");
   // FileNames.push_back("hto2l2nu_SMpA4WW_125GeV_noPDF_Full_1.root");

   vector<string> Tags;
   Tags.push_back("gg_SM");
   Tags.push_back("gg_SMpMcwwt");
   Tags.push_back("gg_SMpcwwt");
   Tags.push_back("gg_SMpMcww");
   Tags.push_back("gg_SMpcww");
   Tags.push_back("h");
   // Tags.push_back("SM (gg)");
   // Tags.push_back("A2WW 0.1 (gg)");
   // Tags.push_back("A2WW 0.5 (gg)");
   // Tags.push_back("A2WW 1.0 (gg)");
   // Tags.push_back("A3WW 0.1 (gg)");
   // Tags.push_back("A3WW 0.5 (gg)");
   // Tags.push_back("A3WW 1.0 (gg)");
   // Tags.push_back("A4WW 0.1 (gg)");
   // Tags.push_back("A4WW 0.5 (gg)");
   // Tags.push_back("A4WW 1.0 (gg)");
   // Tags.push_back("SM");
   // Tags.push_back("A2WW 0.1");
   // Tags.push_back("A2WW 0.5");
   // Tags.push_back("A2WW 1.0");
   // Tags.push_back("A3WW 0.1");
   // Tags.push_back("A3WW 0.5");
   // Tags.push_back("A3WW 1.0");
   // Tags.push_back("A4WW 0.1");
   // Tags.push_back("A4WW 0.5");
   // Tags.push_back("A4WW 1.0");

   vector<TFile *> Files(FileNames.size());
   for(int i = 0; i < (int)Files.size(); i++)
      Files[i] = new TFile(FileNames[i].c_str());

   vector<TTree *> Trees(Files.size());
   for(int i = 0; i < (int)Files.size(); i++)
   {
      Trees[i] = (TTree *)Files[i]->Get("Tree");
      SetAlias(Trees[i]);
   }

   // string CutString = "L1PT > 10 && L4PT > 10 && abs(L1Eta) < 2.5 && abs(L4Eta) < 2.5 && MLL > 4";
   string CutString = "";

   vector<TH1D *> HMll(Files.size());
   vector<TH1D *> HCosPhill(Files.size());
   vector<TH1D *> HDPhill(Files.size());
   vector<TH1D *> HMT(Files.size());
   for(int i = 0; i < (int)Files.size(); i++)
   {
      HMll[i] = new TH1D(Form("HMll%d", i + 1), Form("Mll, %s", Tags[i].c_str()), 100, 0, 100);
      Trees[i]->Draw(Form("MLL>>HMll%d", i + 1), CutString.c_str());

      HCosPhill[i] = new TH1D(Form("HCosPhill%d", i + 1), Form("cos(Phill), %s", Tags[i].c_str()), 100, -1, 1);
      Trees[i]->Draw(Form("CosPhiLL>>HCosPhill%d", i + 1), CutString.c_str());
      // Symmetrize(HCosPhill[i]);
      
      HDPhill[i] = new TH1D(Form("HDPhill%d", i + 1), Form("delta phill, %s", Tags[i].c_str()), 100, -PI, PI);
      Trees[i]->Draw(Form("DPhiLL>>HDPhill%d", i + 1), CutString.c_str());
     
      HMT[i] = new TH1D(Form("HMT%d", i + 1), Form("MT, %s", Tags[i].c_str()), 100, 0, 150);
      Trees[i]->Draw(Form("MT>>HMT%d", i + 1), CutString.c_str());
   }
   SetColor(HMll);
   SetColor(HCosPhill);
   SetColor(HDPhill);
   SetColor(HMT);

   TLegend AllLegend(0.60, 0.85, 0.85, 0.40);
   AllLegend.SetBorderSize(0);
   AllLegend.SetFillStyle(0);
   AllLegend.SetTextFont(42);
   for(int i = 0; i < (int)Files.size(); i++)
      AllLegend.AddEntry(HMll[i], Tags[i].c_str(), "l");

   TLegend SideLegend1(0.20, 0.85, 0.35, 0.60);
   TLegend SideLegend2(0.35, 0.85, 0.50, 0.60);
   TLegend SideLegend3(0.50, 0.85, 0.65, 0.60);
   TLegend SideLegend4(0.65, 0.85, 0.80, 0.60);
   SideLegend1.SetBorderSize(0);
   SideLegend1.SetFillStyle(0);
   SideLegend1.SetTextFont(42);
   SideLegend2.SetBorderSize(0);
   SideLegend2.SetFillStyle(0);
   SideLegend2.SetTextFont(42);
   SideLegend3.SetBorderSize(0);
   SideLegend3.SetFillStyle(0);
   SideLegend3.SetTextFont(42);
   SideLegend4.SetBorderSize(0);
   SideLegend4.SetFillStyle(0);
   SideLegend4.SetTextFont(42);
   for(int i = 0; i < (int)Files.size(); i = i + 4)
   {
      if((i + 0) < (int)Files.size())   SideLegend1.AddEntry(HMll[i+0], Tags[i+0].c_str(), "l");
      else                              SideLegend1.AddEntry("", "", "");
      if((i + 1) < (int)Files.size())   SideLegend2.AddEntry(HMll[i+1], Tags[i+1].c_str(), "l");
      else                              SideLegend2.AddEntry("", "", "");
      if((i + 2) < (int)Files.size())   SideLegend3.AddEntry(HMll[i+2], Tags[i+2].c_str(), "l");
      else                              SideLegend3.AddEntry("", "", "");
      if((i + 3) < (int)Files.size())   SideLegend4.AddEntry(HMll[i+3], Tags[i+3].c_str(), "l");
      else                              SideLegend4.AddEntry("", "", "");
   }
   
   TCanvas CMll;
   TH2D HMllWorld("HMllWorld", ";M_{ll};a.u.", 100, 0, 100, 100, 0, 12000);
   HMllWorld.SetStats(0);
   HMllWorld.Draw();
   for(int i = 0; i < (int)Files.size(); i++)
      HMll[i]->Draw("same");
   AllLegend.Draw();
   CMll.SaveAs("MLL.png");
   CMll.SaveAs("MLL.C");
   CMll.SaveAs("MLL.eps");
   CMll.SaveAs("MLL.pdf");

   ofstream outMll("outMll.txt");
   PrintBin(outMll, HMll);
   outMll.close();

   TCanvas CCosPhill;
   TH2D HCosPhillWorld("HCosPhillWorld", ";cos(Opening Angle);a.u.", 100, -1, 1, 100, 0, 20000);
   HCosPhillWorld.SetStats(0);
   HCosPhillWorld.Draw();
   for(int i = 0; i < (int)Files.size(); i++)
      HCosPhill[i]->Draw("same");
   SideLegend1.Draw();
   SideLegend2.Draw();
   SideLegend3.Draw();
   SideLegend4.Draw();
   CCosPhill.SaveAs("CosPhill.png");
   CCosPhill.SaveAs("CosPhill.C");
   CCosPhill.SaveAs("CosPhill.eps");
   CCosPhill.SaveAs("CosPhill.pdf");
   
   ofstream outCosPhill("outCosPhill.txt");
   PrintBin(outCosPhill, HCosPhill);
   outCosPhill.close();
   
   TCanvas CDPhill;
   TH2D HDPhillWorld("HDPhillWorld", ";2D lepton phi difference;a.u.", 100, -PI, PI, 100, 0, 12000);
   HDPhillWorld.SetStats(0);
   HDPhillWorld.Draw();
   for(int i = 0; i < (int)Files.size(); i++)
      HDPhill[i]->Draw("same");
   SideLegend1.Draw();
   SideLegend2.Draw();
   SideLegend3.Draw();
   SideLegend4.Draw();
   CDPhill.SaveAs("DPhill.png");
   CDPhill.SaveAs("DPhill.C");
   CDPhill.SaveAs("DPhill.eps");
   CDPhill.SaveAs("DPhill.pdf");

   ofstream outDPhill("outDPhill.txt");
   PrintBin(outDPhill, HDPhill);
   outDPhill.close();
   
   TCanvas CMT;
   TH2D HMTWorld("HMTWorld", ";MT;a.u.", 100, 0, 150, 100, 0, 25000);
   HMTWorld.SetStats(0);
   HMTWorld.Draw();
   for(int i = 0; i < (int)Files.size(); i++)
      HMT[i]->Draw("same");
   AllLegend.Draw();
   CMT.SaveAs("MT.png");
   CMT.SaveAs("MT.C");
   CMT.SaveAs("MT.eps");
   CMT.SaveAs("MT.pdf");

   ofstream outMT("outMT.txt");
   PrintBin(outMT, HMT);
   outMT.close();

   for(int i = 0; i < (int)Files.size(); i++)
   {
      delete HMll[i];
      delete HCosPhill[i];

      Files[i]->Close();
      delete Files[i];
   }

   return 0;
}

void SetAlias(TTree *Tree)
{
   if(Tree == NULL)
      return;

   Tree->SetAlias("L1Px", "(L1PT*cos(L1Phi))");
   Tree->SetAlias("L1Py", "(L1PT*sin(L1Phi))");
   Tree->SetAlias("L1Pz", "(L1PT*sinh(L1Eta))");
   Tree->SetAlias("L1E", "(L1PT*cosh(L1Eta))");
   Tree->SetAlias("L2Px", "(L2PT*cos(L2Phi))");
   Tree->SetAlias("L2Py", "(L2PT*sin(L2Phi))");
   Tree->SetAlias("L2Pz", "(L2PT*sinh(L2Eta))");
   Tree->SetAlias("L2E", "(L2PT*cosh(L2Eta))");
   Tree->SetAlias("L3Px", "(L3PT*cos(L3Phi))");
   Tree->SetAlias("L3Py", "(L3PT*sin(L3Phi))");
   Tree->SetAlias("L3Pz", "(L3PT*sinh(L3Eta))");
   Tree->SetAlias("L3E", "(L3PT*cosh(L3Eta))");
   Tree->SetAlias("L4Px", "(L4PT*cos(L4Phi))");
   Tree->SetAlias("L4Py", "(L4PT*sin(L4Phi))");
   Tree->SetAlias("L4Pz", "(L4PT*sinh(L4Eta))");
   Tree->SetAlias("L4E", "(L4PT*cosh(L4Eta))");
   Tree->SetAlias("PxLL", "(L1Px+L4Px)");
   Tree->SetAlias("PyLL", "(L1Py+L4Py)");
   Tree->SetAlias("PzLL", "(L1Pz+L4Pz)");
   Tree->SetAlias("ELL", "(L1E+L4E)");
   Tree->SetAlias("MLL", "sqrt(ELL*ELL-PxLL*PxLL-PyLL*PyLL-PzLL*PzLL)");

   Tree->SetAlias("PxNN", "(L2Px+L3Px)");
   Tree->SetAlias("PyNN", "(L2Py+L3Py)");
   Tree->SetAlias("PTNN", "sqrt(PxNN*PxNN+PyNN*PyNN)");

   Tree->SetAlias("CosPhiLL", "(L1Px*L4Px+L1Py*L4Py+L1Pz*L4Pz)/L1E/L4E");
   Tree->SetAlias("L1xL4Px", "(L1Py*L4Pz-L1Pz*L4Py)");
   Tree->SetAlias("L1xL4Py", "(L1Pz*L4Px-L1Px*L4Pz)");
   Tree->SetAlias("L1xL4Pz", "(L1Px*L4Py-L1Py*L4Px)");

   Tree->SetAlias("RawDPhiLL", "(L1Phi - L4Phi)");
   Tree->SetAlias("DPhiLL", "(RawDPhiLL + 3.1415926535 * 2 * (RawDPhiLL < -3.1415926535) - 3.1415926535 * 2 * (RawDPhiLL > 3.1415926535))");

   Tree->SetAlias("MT", "sqrt(2*(L1PT*L4PT-L1Px*L4Px-L1Py*L4Py))");
}

void SetColor(vector<TH1D *> &H)
{
   for(int i = 0; i < (int)H.size(); i++)
   {
      if(H[i] == NULL)
         continue;
      H[i]->SetLineColor((i % 5) + 1);
      H[i]->SetLineStyle(i / 5 + 1);
      H[i]->SetLineWidth(2);
   }
}

void Symmetrize(TH1D *H)
{
   if(H == NULL)
      return;

   int N = H->GetNbinsX();

   for(int i = 1; i < N - i + 1; i++)
   {
      TH1D X;
      double Average = (H->GetBinContent(i) + H->GetBinContent(N-i+1)) / 2;
      H->SetBinContent(i, Average);
      H->SetBinContent(N - i + 1, Average);
   }
}

void PrintBin(ostream &out, vector<TH1D *> &H)
{
   for(int i = 0; i < (int)H.size(); i++)
   {
      out << "H" << i + 1 << " " << H[i]->GetNbinsX() << " " << H[i]->GetBinLowEdge(1) << " " << H[i]->GetXaxis()->GetBinUpEdge(H[i]->GetNbinsX());
      for(int j = 1; j <= H[i]->GetNbinsX(); j++)
         out << " " << H[i]->GetBinContent(j);
      out << endl;
   }
}






