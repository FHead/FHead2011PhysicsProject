#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "PlotHelper3.h"
#include "SetStyle.h"

int main()
{
   SetThesisStyle();

   double CEdge[6] = {0.0, 0.1, 0.3, 0.5, 0.8, 1.0};
   double PTEdge[6] = {140, 160, 180, 200, 300, 500};
   double Smear[5] = {17.2, 12.8, 7.5, 3.1, 1.0};

   TFile F1("StraightAA6Dijet.root");
   TFile F4("StraightPP6Dijet.root");
   TFile F6("ScaledResult1PP6Dijet.root");
   TFile F8("ScaledResult13PP6Dijet.root");
   TFile F10("ScaledResult17PP6Dijet.root");
   
   TTree *T1 = (TTree *)F1.Get("Tree");
   TTree *T4 = (TTree *)F4.Get("Tree");
   TTree *T6 = (TTree *)F6.Get("OutputTree");
   TTree *T8 = (TTree *)F8.Get("OutputTree");
   TTree *T10 = (TTree *)F10.Get("OutputTree");
   
   T1->SetAlias("PTWeightToAAData", "(1/(1.01000-exp(11.4934-0.103388*JetPT)))");
   T1->SetAlias("RawJetDPhi", "(JetPhi-NewJetPhi)");
   T1->SetAlias("JetDPhi", "(RawJetDPhi+2*3.1415926535*(RawJetDPhi<-3.1415926535)-2*3.1415926535*(RawJetDPhi>3.1415926535))");
   T1->SetAlias("JetDEta", "(JetEta-NewJetEta)");
   T1->SetAlias("JetShift", "sqrt(JetDPhi*JetDPhi+JetDEta*JetDEta)");
   
   T4->SetAlias("RawJetDPhi", "(JetPhi-NewJetPhi)");
   T4->SetAlias("JetDPhi", "(RawJetDPhi+2*3.1415926535*(RawJetDPhi<-3.1415926535)-2*3.1415926535*(RawJetDPhi>3.1415926535))");
   T4->SetAlias("JetDEta", "(JetEta-NewJetEta)");
   T4->SetAlias("JetShift", "sqrt(JetDPhi*JetDPhi+JetDEta*JetDEta)");

   T1->SetAlias("C0", "(Centrality < 0.1)");
   T1->SetAlias("C1", "(Centrality < 0.3 && Centrality >= 0.1)");
   T1->SetAlias("C2", "(Centrality < 0.5 && Centrality >= 0.3)");
   T1->SetAlias("C3", "(Centrality < 0.8 && Centrality >= 0.5)");
   T1->SetAlias("C4", "(Centrality < 1.0 && Centrality >= 0.8)");

   T6->SetAlias("ExcessPT", "((TotalPT-0.8*0.8*3.1415926535*Rho)/4)");
   T6->SetAlias("ExcessPT2", "((TotalPTInJet-0.4*0.4*3.1415926535*Rho))");
   T6->SetAlias("AdjustedExcessPT", "(ExcessPT*(ExcessPT>0)+ExcessPT*16*(ExcessPT<0))");
   T6->SetAlias("SmearWeight", "(exp(-ExcessPT*ExcessPT / (2*18*18)) / exp(-ExcessPT*ExcessPT / (2*21.4*21.4)))");
   T6->SetAlias("SmearWeightV2Positive", "(12891000*exp(-0.5*((ExcessPT+0.236714)/27.4658)**2))");
   T6->SetAlias("SmearWeightV2Negative", "(exp(15.5537+0.322953*ExcessPT)+9063180*exp(-0.5*((ExcessPT+2.73170)/14.3526)**2))");
   T6->SetAlias("SmearWeightV2", "(exp(-ExcessPT*ExcessPT/(2*18*18))/(((ExcessPT>0)*SmearWeightV2Positive)+((ExcessPT<0)*SmearWeightV2Negative)))");
   T6->SetAlias("SmearWeightV3", "(exp(-ExcessPT*ExcessPT / (2*17.2*17.2)) / exp(-ExcessPT*ExcessPT / (2*27.4*27.4)))");
   T6->SetAlias("SmearWeightV4", "(exp(-ExcessPT*ExcessPT / (2*12.8*12.8)) / exp(-ExcessPT*ExcessPT / (2*27.4*27.4)))");
   T6->SetAlias("SmearWeightV5", "(exp(-ExcessPT*ExcessPT / (2*7.5*7.5)) / exp(-ExcessPT*ExcessPT / (2*27.4*27.4)))");
   T6->SetAlias("SmearWeightV6", "(exp(-ExcessPT*ExcessPT / (2*3.1*3.1)) / exp(-ExcessPT*ExcessPT / (2*27.4*27.4)))");
   T6->SetAlias("RawJetDPhi", "(JetPhi-NewJetPhi)");
   T6->SetAlias("JetDPhi", "(RawJetDPhi+2*3.1415926535*(RawJetDPhi<-3.1415926535)-2*3.1415926535*(RawJetDPhi>3.1415926535))");
   T6->SetAlias("JetDEta", "(JetEta-NewJetEta)");
   T6->SetAlias("JetShift", "sqrt(JetDPhi*JetDPhi+JetDEta*JetDEta)");
   T6->SetAlias("RawBestJetDPhi", "(JetPhi-BestJetPhi)");
   T6->SetAlias("BestJetDPhi", "(RawBestJetDPhi+2*3.1415926535*(RawBestJetDPhi<-3.1415926535)-2*3.1415926535*(RawBestJetDPhi>3.1415926535))");
   T6->SetAlias("BestJetDEta", "(JetEta-BestJetEta)");
   T6->SetAlias("BestJetShift", "sqrt(BestJetDPhi*BestJetDPhi+BestJetDEta*BestJetDEta)");
   T6->SetAlias("PTWeightToEmbedded", "(0.929846+exp(9.16730-0.0754417*NewJetPT))");
   T6->SetAlias("PTWeightToEmbeddedCentral", "(0.725818+0.628636*exp(-(NewJetPT-77.054)*(NewJetPT-77.054)/(2*40.616*40.616)))");
   T6->SetAlias("JetShiftWeight", "(exp(-JetShift*JetShift/(2*0.1*0.1)))");
   T6->SetAlias("SmearWeightInJet", "(exp(-ExcessPT*ExcessPT / (2*15.2*15.2)) / exp(-ExcessPT*ExcessPT / (2*31.13*31.13)))");
   T6->SetAlias("SmearWeightInJet2", "(exp(-ExcessPT*ExcessPT / (2*17.2*17.2)) / exp(-ExcessPT*ExcessPT / (2*32.17*32.17)))");
   T6->SetAlias("SmearWeightInJet3", "(exp(-ExcessPT*ExcessPT / (2*5.2*5.2)) / exp(-ExcessPT*ExcessPT / (2*32.17*32.17)))");
   T6->SetAlias("SmearWeightAdjusted", "(((AdjustedExcessPT>0)+16*(AdjustedExcessPT<0)*(exp(-AdjustedExcessPT*AdjustedExcessPT/2/(27.35*27.35))/exp(-AdjustedExcessPT*AdjustedExcessPT/2/(27.35*27.35*16*16))))*(exp(-AdjustedExcessPT*AdjustedExcessPT/(2*17.2*17.2))/exp(-AdjustedExcessPT*AdjustedExcessPT/(2*27.35*27.35))))");
   T6->SetAlias("JetPTWeight", "(1 / (0.526940+0.475752*erf(0.0379893*(JetPT-95.6267))))");
   T6->SetAlias("JetPTWeight2", "(1 / (0.126940+0.875752*erf(0.0379893*(JetPT-95.6267))))");

   T8->SetAlias("ExcessPT", "((TotalPT-1.2*1.2*3.1415926535*Rho)/9)");
   T8->SetAlias("ExcessPT2", "((TotalPTInJet-0.4*0.4*3.1415926535*Rho))");
   T8->SetAlias("AdjustedExcessPT", "(ExcessPT*(ExcessPT>0)+ExcessPT*9*(ExcessPT<0))");
   T8->SetAlias("SmearWeight", "(exp(-ExcessPT*ExcessPT / (2*18*18)) / exp(-ExcessPT*ExcessPT / (2*21.4*21.4)))");
   T8->SetAlias("SmearWeightV2Positive", "(12891000*exp(-0.5*((ExcessPT+0.236714)/27.4658)**2))");
   T8->SetAlias("SmearWeightV2Negative", "(exp(15.5537+0.322953*ExcessPT)+9063180*exp(-0.5*((ExcessPT+2.73170)/14.3526)**2))");
   T8->SetAlias("SmearWeightV2", "(exp(-ExcessPT*ExcessPT/(2*18*18))/(((ExcessPT>0)*SmearWeightV2Positive)+((ExcessPT<0)*SmearWeightV2Negative)))");
   T8->SetAlias("SmearWeightV3", "(exp(-ExcessPT*ExcessPT / (2*17.2*17.2)) / exp(-ExcessPT*ExcessPT / (2*27.4*27.4)))");
   T8->SetAlias("SmearWeightV4", "(exp(-ExcessPT*ExcessPT / (2*12.8*12.8)) / exp(-ExcessPT*ExcessPT / (2*27.4*27.4)))");
   T8->SetAlias("SmearWeightV5", "(exp(-ExcessPT*ExcessPT / (2*7.5*7.5)) / exp(-ExcessPT*ExcessPT / (2*27.4*27.4)))");
   T8->SetAlias("SmearWeightV6", "(exp(-ExcessPT*ExcessPT / (2*3.1*3.1)) / exp(-ExcessPT*ExcessPT / (2*27.4*27.4)))");
   T8->SetAlias("RawJetDPhi", "(JetPhi-NewJetPhi)");
   T8->SetAlias("JetDPhi", "(RawJetDPhi+2*3.1415926535*(RawJetDPhi<-3.1415926535)-2*3.1415926535*(RawJetDPhi>3.1415926535))");
   T8->SetAlias("JetDEta", "(JetEta-NewJetEta)");
   T8->SetAlias("JetShift", "sqrt(JetDPhi*JetDPhi+JetDEta*JetDEta)");
   T8->SetAlias("RawBestJetDPhi", "(JetPhi-BestJetPhi)");
   T8->SetAlias("BestJetDPhi", "(RawBestJetDPhi+2*3.1415926535*(RawBestJetDPhi<-3.1415926535)-2*3.1415926535*(RawBestJetDPhi>3.1415926535))");
   T8->SetAlias("BestJetDEta", "(JetEta-BestJetEta)");
   T8->SetAlias("BestJetShift", "sqrt(BestJetDPhi*BestJetDPhi+BestJetDEta*BestJetDEta)");
   T8->SetAlias("PTWeightToEmbedded", "(0.929846+exp(9.16730-0.0754417*NewJetPT))");
   T8->SetAlias("PTWeightToEmbeddedCentral", "(0.725818+0.628636*exp(-(NewJetPT-77.054)*(NewJetPT-77.054)/(2*40.616*40.616)))");
   T8->SetAlias("JetShiftWeight", "(exp(-JetShift*JetShift/(2*0.1*0.1)))");
   T8->SetAlias("SmearWeightInJet", "(exp(-ExcessPT*ExcessPT / (2*15.2*15.2)) / exp(-ExcessPT*ExcessPT / (2*31.13*31.13)))");
   T8->SetAlias("SmearWeightInJet2", "(exp(-ExcessPT*ExcessPT / (2*17.2*17.2)) / exp(-ExcessPT*ExcessPT / (2*32.17*32.17)))");
   T8->SetAlias("SmearWeightAdjusted", "(((AdjustedExcessPT>0)+9*(AdjustedExcessPT<0)*(exp(-AdjustedExcessPT*AdjustedExcessPT/2/(27.35*27.35))/exp(-AdjustedExcessPT*AdjustedExcessPT/2/(27.35*27.35*9*9))))*(exp(-AdjustedExcessPT*AdjustedExcessPT/(2*17.2*17.2))/exp(-AdjustedExcessPT*AdjustedExcessPT/(2*27.35*27.35))))");
   T8->SetAlias("JetPTWeight", "(1 / (0.526940+0.475752*erf(0.0379893*(JetPT-95.6267))))");
   T8->SetAlias("JetPTWeight2", "(1 / (0.126940+0.875752*erf(0.0379893*(JetPT-95.6267))))");
   T8->SetAlias("GroomWeight", "min(12.0091-11.4330*NewJetSDPT2/NewJetPT,0.125406+1.11458*NewJetSDPT2/NewJetPT)");

   T10->SetAlias("ExcessPT", "((TotalPT-1.6*1.6*3.1415926535*Rho)/16)");
   T10->SetAlias("ExcessPT2", "((TotalPTInJet-0.4*0.4*3.1415926535*Rho))");
   T10->SetAlias("AdjustedExcessPT", "(ExcessPT*(ExcessPT>0)+ExcessPT*16*(ExcessPT<0))");
   T10->SetAlias("SmearWeight", "(exp(-ExcessPT*ExcessPT / (2*18*18)) / exp(-ExcessPT*ExcessPT / (2*21.4*21.4)))");
   T10->SetAlias("SmearWeightV2Positive", "(12891000*exp(-0.5*((ExcessPT+0.236714)/27.4658)**2))");
   T10->SetAlias("SmearWeightV2Negative", "(exp(15.5537+0.322953*ExcessPT)+9063180*exp(-0.5*((ExcessPT+2.73170)/14.3526)**2))");
   T10->SetAlias("SmearWeightV2", "(exp(-ExcessPT*ExcessPT/(2*18*18))/(((ExcessPT>0)*SmearWeightV2Positive)+((ExcessPT<0)*SmearWeightV2Negative)))");
   T10->SetAlias("SmearWeightV3", "(exp(-ExcessPT*ExcessPT / (2*17.2*17.2)) / exp(-ExcessPT*ExcessPT / (2*27.4*27.4)))");
   T10->SetAlias("SmearWeightV4", "(exp(-ExcessPT*ExcessPT / (2*12.8*12.8)) / exp(-ExcessPT*ExcessPT / (2*27.4*27.4)))");
   T10->SetAlias("SmearWeightV5", "(exp(-ExcessPT*ExcessPT / (2*7.5*7.5)) / exp(-ExcessPT*ExcessPT / (2*27.4*27.4)))");
   T10->SetAlias("SmearWeightV6", "(exp(-ExcessPT*ExcessPT / (2*3.1*3.1)) / exp(-ExcessPT*ExcessPT / (2*27.4*27.4)))");
   T10->SetAlias("RawJetDPhi", "(JetPhi-NewJetPhi)");
   T10->SetAlias("JetDPhi", "(RawJetDPhi+2*3.1415926535*(RawJetDPhi<-3.1415926535)-2*3.1415926535*(RawJetDPhi>3.1415926535))");
   T10->SetAlias("JetDEta", "(JetEta-NewJetEta)");
   T10->SetAlias("JetShift", "sqrt(JetDPhi*JetDPhi+JetDEta*JetDEta)");
   T10->SetAlias("RawBestJetDPhi", "(JetPhi-BestJetPhi)");
   T10->SetAlias("BestJetDPhi", "(RawBestJetDPhi+2*3.1415926535*(RawBestJetDPhi<-3.1415926535)-2*3.1415926535*(RawBestJetDPhi>3.1415926535))");
   T10->SetAlias("BestJetDEta", "(JetEta-BestJetEta)");
   T10->SetAlias("BestJetShift", "sqrt(BestJetDPhi*BestJetDPhi+BestJetDEta*BestJetDEta)");
   T10->SetAlias("PTWeightToEmbedded", "(0.929846+exp(9.16730-0.0754417*NewJetPT))");
   T10->SetAlias("PTWeightToEmbeddedCentral", "(0.725818+0.628636*exp(-(NewJetPT-77.054)*(NewJetPT-77.054)/(2*40.616*40.616)))");
   T10->SetAlias("JetShiftWeight", "(exp(-JetShift*JetShift/(2*0.1*0.1)))");
   T10->SetAlias("SmearWeightInJet", "(exp(-ExcessPT*ExcessPT / (2*15.2*15.2)) / exp(-ExcessPT*ExcessPT / (2*31.13*31.13)))");
   T10->SetAlias("SmearWeightInJet2", "(exp(-ExcessPT2*ExcessPT2 / (2*17.2*17.2)) / exp(-ExcessPT*ExcessPT / (2*32.17*32.17)))");
   T10->SetAlias("SmearWeightAdjusted", "(((AdjustedExcessPT>0)+16*(AdjustedExcessPT<0)*(exp(-AdjustedExcessPT*AdjustedExcessPT/2/(27.35*27.35))/exp(-AdjustedExcessPT*AdjustedExcessPT/2/(27.35*27.35*16*16))))*(exp(-AdjustedExcessPT*AdjustedExcessPT/(2*17.2*17.2))/exp(-AdjustedExcessPT*AdjustedExcessPT/(2*27.35*27.35))))");
   T10->SetAlias("JetPTWeight", "(1 / (0.526940+0.475752*erf(0.0379893*(JetPT-95.6267))))");
   T10->SetAlias("JetPTWeight2", "(1 / (0.126940+0.875752*erf(0.0379893*(JetPT-95.6267))))");
   T10->SetAlias("ExcessPTExtraWeight", "(exp(-(AdjustedExcessPT*AdjustedExcessPT)/(2*17.2*17.2))/(exp(-(AdjustedExcessPT-11.5)*(AdjustedExcessPT-11.5)/(2*17*17))))");

   for(int i = 0; i < 5; i++)
   {
      T10->SetAlias(Form("SmearWeightAdjusted%d", i), Form("(((AdjustedExcessPT>0)+16*(AdjustedExcessPT<0)*(exp(-AdjustedExcessPT*AdjustedExcessPT/2/(27.35*27.35))/exp(-AdjustedExcessPT*AdjustedExcessPT/2/(27.35*27.35*16*16))))*(exp(-AdjustedExcessPT*AdjustedExcessPT/(2*%f*%f))/exp(-AdjustedExcessPT*AdjustedExcessPT/(2*27.35*27.35))))", Smear[i], Smear[i]));
      T8->SetAlias(Form("SmearWeightInJet2%d", i), Form("(exp(-ExcessPT*ExcessPT / (2*%f*%f)) / exp(-ExcessPT*ExcessPT / (2*32.17*32.17)))", Smear[i], Smear[i]));
   }
   
   PdfFileHelper PdfFile("Result.pdf");
   PdfFile.AddTextPage("Closure");

   for(int iC = 0; iC < 5; iC++)
   {
      for(int iPT = 0; iPT < 5; iPT++)
      {
         cout << iC << " " << iPT << endl;
         PdfFile.AddTextPage(Form("PT %.0f-%.0f, Centrality %d%%-%d%%", PTEdge[iPT], PTEdge[iPT+1], (int)(CEdge[iC] * 100), (int)(CEdge[iC+1] * 100)));

         TH1D A("A", ";Jet SD Mass / Jet PT", 40, 0, 0.3);
         TH1D B("B", ";Jet SD Mass / Jet PT", 40, 0, 0.3);
         TH1D C("C", ";Jet SD Mass / Jet PT", 40, 0, 0.3);

         T1->Draw("SDMass[7]/NewJetPT>>A", Form("MCWeight * (JetPT > %f && JetPT < %f && abs(JetEta) < 1.3 && SDRecoDR[7] > 0.1 && Centrality < %f && Centrality > %f && JetShift < 0.05)", PTEdge[iPT], PTEdge[iPT+1], CEdge[iC+1], CEdge[iC]), "");
         T8->Draw("BestJetSDMass2/BestJetPT>>B", Form("MCWeight *  SmearWeightInJet2%d * PTWeightToEmbeddedCentral * (BestJetPT > %f && BestJetPT < %f && abs(BestJetEta) < 1.3 && BestJetDR2 > 0.1 && JetShift < 0.2)", iC, PTEdge[iPT], PTEdge[iPT+1]), "same");
         // T8->Draw("BestJetSDMass2/BestJetPT>>B", Form("MCWeight *  SmearWeightInJet2%d * PTWeightToEmbeddedCentral * GroomWeight * (BestJetPT > %f && BestJetPT < %f && abs(BestJetEta) < 1.3 && BestJetDR2 > 0.1 && JetShift < 0.2)", iC, PTEdge[iPT], PTEdge[iPT+1]), "same");
         // T8->Draw("BestJetSDMass2/BestJetPT>>B", Form("MCWeight *  SmearWeightInJet2%d * PTWeightToEmbeddedCentral * (BestJetPT > %f && BestJetPT < %f && abs(BestJetEta) < 1.3 && BestJetDR2 > 0.1 && JetShift < 0.2) * (1 - 0.4 * (NewJetSDPT2/NewJetPT > 0.99))", iC, PTEdge[iPT], PTEdge[iPT+1]), "same");
         T4->Draw("SDMass[7]/NewJetPT>>C", Form("MCWeight * (JetPT > %f && JetPT < %f && abs(JetEta) < 1.3 && SDRecoDR[7] > 0.1 && JetShift < 0.05)", PTEdge[iPT], PTEdge[iPT+1]), "");

         A.Scale(1 / A.Integral() / (0.3 / 40));
         B.Scale(1 / B.Integral() / (0.3 / 40));
         C.Scale(1 / C.Integral() / (0.3 / 40));
         A.SetLineColor(kBlack);
         A.SetMarkerColor(kBlack);
         A.SetMarkerStyle(20);
         B.SetLineColor(kRed);
         B.SetMarkerColor(kRed);
         B.SetMarkerStyle(20);
         C.SetLineColor(kGreen);
         C.SetMarkerColor(kGreen);
         C.SetMarkerStyle(20);
         A.SetTitle("");

         A.SetMinimum(0);
         A.SetMaximum(max(max(A.GetMaximum(), B.GetMaximum()), C.GetMaximum()) * 1.2);

         A.SetStats(0);
         B.SetStats(0);
         C.SetStats(0);

         TCanvas C1;

         A.Draw();
         B.Draw("same");
         C.Draw("same");

         TLegend Legend(0.4, 0.8, 0.7, 0.5);
         Legend.SetTextFont(42);
         Legend.SetTextSize(0.035);
         Legend.SetFillStyle(0);
         Legend.SetBorderSize(0);
         Legend.AddEntry(&A, "Embedded pythia");
         Legend.AddEntry(&B, "Smeared pythia");
         Legend.AddEntry(&C, "Pythia");
         Legend.Draw();

         PdfFile.AddCanvas(C1);

         TH1D *AClone = (TH1D *)A.Clone();
         AClone->Divide(&B);

         TCanvas C2;

         AClone->SetMaximum(2);
         AClone->Draw();

         PdfFile.AddCanvas(C2);

         delete AClone;

         TCanvas C3;

         A.Rebin(2);
         B.Rebin(2);
         C.Rebin(2);
         
         A.SetMaximum(A.GetMaximum() * 2);

         A.Draw();
         B.Draw("same");
         C.Draw("same");
         Legend.Draw();

         PdfFile.AddCanvas(C3);

         TCanvas C4;

         A.Divide(&B);
         A.SetMaximum(2);
         A.Draw();
         
         PdfFile.AddCanvas(C4);
      }

      break;
   }

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}


