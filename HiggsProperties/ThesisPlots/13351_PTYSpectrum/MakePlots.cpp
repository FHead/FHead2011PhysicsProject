#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "SetStyle.h"

#include "PTYFunctions.h"

int main();

int main()
{
   SetThesisRegularStyle();

   int Bin = 500;
   double s = 125 * 125;

   TH1D HSPT("HSPT", ";p_{T};a.u.", Bin, 0, 100);
   TH1D HUUbar8PT2e2mu("HUUbar8PT2e2mu", ";p_{T};a.u.", Bin, 0, 100);
   TH1D HDDbar8PT2e2mu("HDDbar8PT2e2mu", ";p_{T};a.u.", Bin, 0, 100);
   TH1D HGU8PT2e2mu("HGU8PT2e2mu", ";p_{T};a.u.", Bin, 0, 100);
   TH1D HGUbar8PT2e2mu("HGUbar8PT2e2mu", ";p_{T};a.u.", Bin, 0, 100);
   TH1D HGD8PT2e2mu("HGD8PT2e2mu", ";p_{T};a.u.", Bin, 0, 100);
   TH1D HGDbar8PT2e2mu("HGDbar8PT2e2mu", ";p_{T};a.u.", Bin, 0, 100);
   TH1D HUUbar8PT4e("HUUbar8PT4e", ";p_{T};a.u.", Bin, 0, 100);
   TH1D HDDbar8PT4e("HDDbar8PT4e", ";p_{T};a.u.", Bin, 0, 100);
   TH1D HGU8PT4e("HGU8PT4e", ";p_{T};a.u.", Bin, 0, 100);
   TH1D HGUbar8PT4e("HGUbar8PT4e", ";p_{T};a.u.", Bin, 0, 100);
   TH1D HGD8PT4e("HGD8PT4e", ";p_{T};a.u.", Bin, 0, 100);
   TH1D HGDbar8PT4e("HGDbar8PT4e", ";p_{T};a.u.", Bin, 0, 100);

   TH1D HSY("HSY", ";y_{4l};a.u.", Bin, -5.1, 5.2);
   TH1D HUUbar8Y2e2mu("HUUbar8Y2e2mu", ";y_{4l};a.u.", Bin, -5.1, 5.2);
   TH1D HDDbar8Y2e2mu("HDDbar8Y2e2mu", ";y_{4l};a.u.", Bin, -5.1, 5.2);
   TH1D HGU8Y2e2mu("HGU8Y2e2mu", ";y_{4l};a.u.", Bin, -5.1, 5.2);
   TH1D HGUbar8Y2e2mu("HGUbar8Y2e2mu", ";y_{4l};a.u.", Bin, -5.1, 5.2);
   TH1D HGD8Y2e2mu("HGD8Y2e2mu", ";y_{4l};a.u.", Bin, -5.1, 5.2);
   TH1D HGDbar8Y2e2mu("HGDbar8Y2e2mu", ";y_{4l};a.u.", Bin, -5.1, 5.2);
   TH1D HUUbar8Y4e("HUUbar8Y4e", ";y_{4l};a.u.", Bin, -5.1, 5.2);
   TH1D HDDbar8Y4e("HDDbar8Y4e", ";y_{4l};a.u.", Bin, -5.1, 5.2);
   TH1D HGU8Y4e("HGU8Y4e", ";y_{4l};a.u.", Bin, -5.1, 5.2);
   TH1D HGUbar8Y4e("HGUbar8Y4e", ";y_{4l};a.u.", Bin, -5.1, 5.2);
   TH1D HGD8Y4e("HGD8Y4e", ";y_{4l};a.u.", Bin, -5.1, 5.2);
   TH1D HGDbar8Y4e("HGDbar8Y4e", ";y_{4l};a.u.", Bin, -5.1, 5.2);
   
   TH2D HSPTY("HSPTY", ";p_{T};y_{4l}", Bin, 0, 100, Bin, -5.1, 5.2);

   TH1D HAll8YComp2e2mu("HAll8YComp2e2mu", ";YComp_{4l};a.u.", Bin, -5.1, 5.2);
   TH1D HUUbar8YComp2e2mu("HUUbar8YComp2e2mu", ";YComp_{4l};a.u.", Bin, -5.1, 5.2);
   TH1D HDDbar8YComp2e2mu("HDDbar8YComp2e2mu", ";YComp_{4l};a.u.", Bin, -5.1, 5.2);
   TH1D HGU8YComp2e2mu("HGU8YComp2e2mu", ";YComp_{4l};a.u.", Bin, -5.1, 5.2);
   TH1D HGUbar8YComp2e2mu("HGUbar8YComp2e2mu", ";YComp_{4l};a.u.", Bin, -5.1, 5.2);
   TH1D HGD8YComp2e2mu("HGD8YComp2e2mu", ";YComp_{4l};a.u.", Bin, -5.1, 5.2);
   TH1D HGDbar8YComp2e2mu("HGDbar8YComp2e2mu", ";YComp_{4l};a.u.", Bin, -5.1, 5.2);
   TH1D HAll8YComp22e2mu("HAll8YComp22e2mu", ";YComp2_{4l};a.u.", Bin, -5.1, 5.2);
   TH1D HUUbar8YComp22e2mu("HUUbar8YComp22e2mu", ";YComp2_{4l};a.u.", Bin, -5.1, 5.2);
   TH1D HDDbar8YComp22e2mu("HDDbar8YComp22e2mu", ";YComp2_{4l};a.u.", Bin, -5.1, 5.2);
   TH1D HGU8YComp22e2mu("HGU8YComp22e2mu", ";YComp2_{4l};a.u.", Bin, -5.1, 5.2);
   TH1D HGUbar8YComp22e2mu("HGUbar8YComp22e2mu", ";YComp2_{4l};a.u.", Bin, -5.1, 5.2);
   TH1D HGD8YComp22e2mu("HGD8YComp22e2mu", ";YComp2_{4l};a.u.", Bin, -5.1, 5.2);
   TH1D HGDbar8YComp22e2mu("HGDbar8YComp22e2mu", ";YComp2_{4l};a.u.", Bin, -5.1, 5.2);
   
   TH1D HUUbar8M4l2e2mu("HUUbar8M4l2e2mu", ";m_{4l};a.u.", Bin, 115, 135);
   TH1D HDDbar8M4l2e2mu("HDDbar8M4l2e2mu", ";m_{4l};a.u.", Bin, 115, 135);
   TH1D HGU8M4l2e2mu("HGU8M4l2e2mu",       ";m_{4l};a.u.", Bin, 115, 135);
   TH1D HGUbar8M4l2e2mu("HGUbar8M4l2e2mu", ";m_{4l};a.u.", Bin, 115, 135);
   TH1D HGD8M4l2e2mu("HGD8M4l2e2mu",       ";m_{4l};a.u.", Bin, 115, 135);
   TH1D HGDbar8M4l2e2mu("HGDbar8M4l2e2mu", ";m_{4l};a.u.", Bin, 115, 135);
   TH1D HUUbar8M4l4e("HUUbar8M4l4e", ";m_{4l};a.u.", Bin, 115, 135);
   TH1D HDDbar8M4l4e("HDDbar8M4l4e", ";m_{4l};a.u.", Bin, 115, 135);
   TH1D HGU8M4l4e("HGU8M4l4e",       ";m_{4l};a.u.", Bin, 115, 135);
   TH1D HGUbar8M4l4e("HGUbar8M4l4e", ";m_{4l};a.u.", Bin, 115, 135);
   TH1D HGD8M4l4e("HGD8M4l4e",       ";m_{4l};a.u.", Bin, 115, 135);
   TH1D HGDbar8M4l4e("HGDbar8M4l4e", ";m_{4l};a.u.", Bin, 115, 135);

   for(int i = 1; i <= Bin; i++)
   {
      for(int j = 1; j <= Bin; j++)
      {
         double pt = HSPT.GetBinCenter(i);
         double y = HSY.GetBinCenter(j);

         double FS      = GetPTYDensity8TeVSignal(pt, y, s);
         double FUUbar82e2mu = GetPTYDensity8TeVBackgroundUUbar2e2mu_Si12624(pt, y, s);
         double FDDbar82e2mu = GetPTYDensity8TeVBackgroundDDbar2e2mu_Si12624(pt, y, s);
         double FGU82e2mu    = GetPTYDensity8TeVBackgroundGU2e2mu_Si12624(pt, y, s);
         double FGUbar82e2mu = GetPTYDensity8TeVBackgroundGUbar2e2mu_Si12624(pt, y, s);
         double FGD82e2mu    = GetPTYDensity8TeVBackgroundGD2e2mu_Si12624(pt, y, s);
         double FGDbar82e2mu = GetPTYDensity8TeVBackgroundGDbar2e2mu_Si12624(pt, y, s);
         double FUUbar84e = GetPTYDensity8TeVBackgroundUUbar4e_Si12624(pt, y, s);
         double FDDbar84e = GetPTYDensity8TeVBackgroundDDbar4e_Si12624(pt, y, s);
         double FGU84e    = GetPTYDensity8TeVBackgroundGU4e_Si12624(pt, y, s);
         double FGUbar84e = GetPTYDensity8TeVBackgroundGUbar4e_Si12624(pt, y, s);
         double FGD84e    = GetPTYDensity8TeVBackgroundGD4e_Si12624(pt, y, s);
         double FGDbar84e = GetPTYDensity8TeVBackgroundGDbar4e_Si12624(pt, y, s);

         HSPT.Fill(pt, FS);
         HUUbar8PT2e2mu.Fill(pt, FUUbar82e2mu);
         HDDbar8PT2e2mu.Fill(pt, FDDbar82e2mu);
         HGU8PT2e2mu.Fill(pt, FGU82e2mu);
         HGUbar8PT2e2mu.Fill(pt, FGUbar82e2mu);
         HGD8PT2e2mu.Fill(pt, FGD82e2mu);
         HGDbar8PT2e2mu.Fill(pt, FGDbar82e2mu);
         HUUbar8PT4e.Fill(pt, FUUbar84e);
         HDDbar8PT4e.Fill(pt, FDDbar84e);
         HGU8PT4e.Fill(pt, FGU84e);
         HGUbar8PT4e.Fill(pt, FGUbar84e);
         HGD8PT4e.Fill(pt, FGD84e);
         HGDbar8PT4e.Fill(pt, FGDbar84e);
         
         HSY.Fill(y, FS);
         HUUbar8Y2e2mu.Fill(y, FUUbar82e2mu);
         HDDbar8Y2e2mu.Fill(y, FDDbar82e2mu);
         HGU8Y2e2mu.Fill(y, FGU82e2mu);
         HGUbar8Y2e2mu.Fill(y, FGUbar82e2mu);
         HGD8Y2e2mu.Fill(y, FGD82e2mu);
         HGDbar8Y2e2mu.Fill(y, FGDbar82e2mu);
         HUUbar8Y4e.Fill(y, FUUbar84e);
         HDDbar8Y4e.Fill(y, FDDbar84e);
         HGU8Y4e.Fill(y, FGU84e);
         HGUbar8Y4e.Fill(y, FGUbar84e);
         HGD8Y4e.Fill(y, FGD84e);
         HGDbar8Y4e.Fill(y, FGDbar84e);

         HSPTY.Fill(pt, y, FS);
         
         HUUbar8YComp2e2mu.Fill(y, FUUbar82e2mu * 0.0798463);
         HDDbar8YComp2e2mu.Fill(y, FDDbar82e2mu * 0.187831);
         HGU8YComp2e2mu.Fill(y, FGU82e2mu * 0.0979808 / 2);
         HGUbar8YComp2e2mu.Fill(-y, FGUbar82e2mu * 0.0597408 / 2);
         HGD8YComp2e2mu.Fill(y, FGD82e2mu * 0.224594 / 2);
         HGDbar8YComp2e2mu.Fill(-y, FGDbar82e2mu * 0.0830206 / 2);
         
         HUUbar8YComp22e2mu.Fill(y, FUUbar82e2mu * 0.0798463);
         HDDbar8YComp22e2mu.Fill(y, FDDbar82e2mu * 0.187831);
         HGU8YComp22e2mu.Fill(y, FGU82e2mu * 0.0979808 / 2);
         HGUbar8YComp22e2mu.Fill(y, FGUbar82e2mu * 0.0597408 / 2);
         HGD8YComp22e2mu.Fill(y, FGD82e2mu * 0.224594 / 2);
         HGDbar8YComp22e2mu.Fill(y, FGDbar82e2mu * 0.0830206 / 2);
         HUUbar8YComp22e2mu.Fill(-y, FUUbar82e2mu * 0.0798463);
         HDDbar8YComp22e2mu.Fill(-y, FDDbar82e2mu * 0.187831);
         HGU8YComp22e2mu.Fill(-y, FGU82e2mu * 0.0979808 / 2);
         HGUbar8YComp22e2mu.Fill(-y, FGUbar82e2mu * 0.0597408 / 2);
         HGD8YComp22e2mu.Fill(-y, FGD82e2mu * 0.224594 / 2);
         HGDbar8YComp22e2mu.Fill(-y, FGDbar82e2mu * 0.0830206 / 2);
      }
   }

   for(int i = 1; i <= Bin; i++)
   {
      for(int j = 1; j <= Bin; j++)
      {
         double m4l = HUUbar8M4l2e2mu.GetBinCenter(i);
         double y = HSY.GetBinCenter(j);
         
         HUUbar8M4l2e2mu.Fill(m4l, GetMDensityConditionalOnY8TeVBackgroundUUbar2e2mu_Si12624(m4l * m4l, y)
            * GetYDensity8TeVBackgroundUUbar2e2mu_Si12624(y));
         HDDbar8M4l2e2mu.Fill(m4l, GetMDensityConditionalOnY8TeVBackgroundDDbar2e2mu_Si12624(m4l * m4l, y)
            * GetYDensity8TeVBackgroundDDbar2e2mu_Si12624(y));
         HGU8M4l2e2mu.Fill(m4l, GetMDensityConditionalOnY8TeVBackgroundGU2e2mu_Si12624(m4l * m4l, y)
            * GetYDensity8TeVBackgroundGU2e2mu_Si12624(y));
         HGUbar8M4l2e2mu.Fill(m4l, GetMDensityConditionalOnY8TeVBackgroundGUbar2e2mu_Si12624(m4l * m4l, y)
            * GetYDensity8TeVBackgroundGUbar2e2mu_Si12624(y));
         HGD8M4l2e2mu.Fill(m4l, GetMDensityConditionalOnY8TeVBackgroundGD2e2mu_Si12624(m4l * m4l, y)
            * GetYDensity8TeVBackgroundGD2e2mu_Si12624(y));
         HGDbar8M4l2e2mu.Fill(m4l, GetMDensityConditionalOnY8TeVBackgroundGDbar2e2mu_Si12624(m4l * m4l, y)
            * GetYDensity8TeVBackgroundGDbar2e2mu_Si12624(y));
         HUUbar8M4l4e.Fill(m4l, GetMDensityConditionalOnY8TeVBackgroundUUbar4e_Si12624(m4l * m4l, y)
            * GetYDensity8TeVBackgroundUUbar4e_Si12624(y));
         HDDbar8M4l4e.Fill(m4l, GetMDensityConditionalOnY8TeVBackgroundDDbar4e_Si12624(m4l * m4l, y)
            * GetYDensity8TeVBackgroundDDbar4e_Si12624(y));
         HGU8M4l4e.Fill(m4l, GetMDensityConditionalOnY8TeVBackgroundGU4e_Si12624(m4l * m4l, y)
            * GetYDensity8TeVBackgroundGU4e_Si12624(y));
         HGUbar8M4l4e.Fill(m4l, GetMDensityConditionalOnY8TeVBackgroundGUbar4e_Si12624(m4l * m4l, y)
            * GetYDensity8TeVBackgroundGUbar4e_Si12624(y));
         HGD8M4l4e.Fill(m4l, GetMDensityConditionalOnY8TeVBackgroundGD4e_Si12624(m4l * m4l, y)
            * GetYDensity8TeVBackgroundGD4e_Si12624(y));
         HGDbar8M4l4e.Fill(m4l, GetMDensityConditionalOnY8TeVBackgroundGDbar4e_Si12624(m4l * m4l, y)
            * GetYDensity8TeVBackgroundGDbar4e_Si12624(y));
      }
   }

   HSPT.Scale(double(Bin) / 100 / HSPT.Integral());
   HUUbar8PT2e2mu.Scale(double(Bin) / 100 / HUUbar8PT2e2mu.Integral());
   HDDbar8PT2e2mu.Scale(double(Bin) / 100 / HDDbar8PT2e2mu.Integral());
   HGU8PT2e2mu.Scale(double(Bin) / 100 / HGU8PT2e2mu.Integral());
   HGUbar8PT2e2mu.Scale(double(Bin) / 100 / HGUbar8PT2e2mu.Integral());
   HGD8PT2e2mu.Scale(double(Bin) / 100 / HGD8PT2e2mu.Integral());
   HGDbar8PT2e2mu.Scale(double(Bin) / 100 / HGDbar8PT2e2mu.Integral());
   HUUbar8PT4e.Scale(double(Bin) / 100 / HUUbar8PT4e.Integral());
   HDDbar8PT4e.Scale(double(Bin) / 100 / HDDbar8PT4e.Integral());
   HGU8PT4e.Scale(double(Bin) / 100 / HGU8PT4e.Integral());
   HGUbar8PT4e.Scale(double(Bin) / 100 / HGUbar8PT4e.Integral());
   HGD8PT4e.Scale(double(Bin) / 100 / HGD8PT4e.Integral());
   HGDbar8PT4e.Scale(double(Bin) / 100 / HGDbar8PT4e.Integral());

   HSY.Scale(double(Bin) / 10.3 / HSY.Integral());
   HUUbar8Y2e2mu.Scale(double(Bin) / 10.3 / HUUbar8Y2e2mu.Integral());
   HDDbar8Y2e2mu.Scale(double(Bin) / 10.3 / HDDbar8Y2e2mu.Integral());
   HGU8Y2e2mu.Scale(double(Bin) / 10.3 / HGU8Y2e2mu.Integral());
   HGUbar8Y2e2mu.Scale(double(Bin) / 10.3 / HGUbar8Y2e2mu.Integral());
   HGD8Y2e2mu.Scale(double(Bin) / 10.3 / HGD8Y2e2mu.Integral());
   HGDbar8Y2e2mu.Scale(double(Bin) / 10.3 / HGDbar8Y2e2mu.Integral());
   HUUbar8Y4e.Scale(double(Bin) / 10.3 / HUUbar8Y4e.Integral());
   HDDbar8Y4e.Scale(double(Bin) / 10.3 / HDDbar8Y4e.Integral());
   HGU8Y4e.Scale(double(Bin) / 10.3 / HGU8Y4e.Integral());
   HGUbar8Y4e.Scale(double(Bin) / 10.3 / HGUbar8Y4e.Integral());
   HGD8Y4e.Scale(double(Bin) / 10.3 / HGD8Y4e.Integral());
   HGDbar8Y4e.Scale(double(Bin) / 10.3 / HGDbar8Y4e.Integral());

   HSPTY.Scale(double(Bin * Bin) / 100 / 10.3 / HSPTY.Integral());
   
   HUUbar8M4l2e2mu.Scale(double(Bin) / 20 / HUUbar8M4l2e2mu.Integral());
   HDDbar8M4l2e2mu.Scale(double(Bin) / 20 / HDDbar8M4l2e2mu.Integral());
   HGU8M4l2e2mu.Scale(double(Bin) / 20 / HGU8M4l2e2mu.Integral());
   HGUbar8M4l2e2mu.Scale(double(Bin) / 20 / HGUbar8M4l2e2mu.Integral());
   HGD8M4l2e2mu.Scale(double(Bin) / 20 / HGD8M4l2e2mu.Integral());
   HGDbar8M4l2e2mu.Scale(double(Bin) / 20 / HGDbar8M4l2e2mu.Integral());
   HUUbar8M4l4e.Scale(double(Bin) / 20 / HUUbar8M4l4e.Integral());
   HDDbar8M4l4e.Scale(double(Bin) / 20 / HDDbar8M4l4e.Integral());
   HGU8M4l4e.Scale(double(Bin) / 20 / HGU8M4l4e.Integral());
   HGUbar8M4l4e.Scale(double(Bin) / 20 / HGUbar8M4l4e.Integral());
   HGD8M4l4e.Scale(double(Bin) / 20 / HGD8M4l4e.Integral());
   HGDbar8M4l4e.Scale(double(Bin) / 20 / HGDbar8M4l4e.Integral());

   HAll8YComp2e2mu.Add(&HUUbar8YComp2e2mu);
   HAll8YComp2e2mu.Add(&HDDbar8YComp2e2mu);
   HAll8YComp2e2mu.Add(&HGU8YComp2e2mu);
   HAll8YComp2e2mu.Add(&HGUbar8YComp2e2mu);
   HAll8YComp2e2mu.Add(&HGD8YComp2e2mu);
   HAll8YComp2e2mu.Add(&HGDbar8YComp2e2mu);
   HUUbar8YComp2e2mu.Divide(&HAll8YComp2e2mu);
   HDDbar8YComp2e2mu.Divide(&HAll8YComp2e2mu);
   HGU8YComp2e2mu.Divide(&HAll8YComp2e2mu);
   HGUbar8YComp2e2mu.Divide(&HAll8YComp2e2mu);
   HGD8YComp2e2mu.Divide(&HAll8YComp2e2mu);
   HGDbar8YComp2e2mu.Divide(&HAll8YComp2e2mu);

   HGD8YComp2e2mu.Add(&HGDbar8YComp2e2mu);
   HGUbar8YComp2e2mu.Add(&HGD8YComp2e2mu);
   HGU8YComp2e2mu.Add(&HGUbar8YComp2e2mu);
   HDDbar8YComp2e2mu.Add(&HGU8YComp2e2mu);
   HUUbar8YComp2e2mu.Add(&HDDbar8YComp2e2mu);

   HAll8YComp22e2mu.Add(&HUUbar8YComp22e2mu);
   HAll8YComp22e2mu.Add(&HDDbar8YComp22e2mu);
   HAll8YComp22e2mu.Add(&HGU8YComp22e2mu);
   HAll8YComp22e2mu.Add(&HGUbar8YComp22e2mu);
   HAll8YComp22e2mu.Add(&HGD8YComp22e2mu);
   HAll8YComp22e2mu.Add(&HGDbar8YComp22e2mu);
   HUUbar8YComp22e2mu.Divide(&HAll8YComp22e2mu);
   HDDbar8YComp22e2mu.Divide(&HAll8YComp22e2mu);
   HGU8YComp22e2mu.Divide(&HAll8YComp22e2mu);
   HGUbar8YComp22e2mu.Divide(&HAll8YComp22e2mu);
   HGD8YComp22e2mu.Divide(&HAll8YComp22e2mu);
   HGDbar8YComp22e2mu.Divide(&HAll8YComp22e2mu);

   HGD8YComp22e2mu.Add(&HGDbar8YComp22e2mu);
   HGUbar8YComp22e2mu.Add(&HGD8YComp22e2mu);
   HGU8YComp22e2mu.Add(&HGUbar8YComp22e2mu);
   HDDbar8YComp22e2mu.Add(&HGU8YComp22e2mu);
   HUUbar8YComp22e2mu.Add(&HDDbar8YComp22e2mu);

   HSPT.SetLineWidth(2);
   HUUbar8PT2e2mu.SetLineWidth(2);
   HDDbar8PT2e2mu.SetLineWidth(2);
   HGU8PT2e2mu.SetLineWidth(2);
   HGUbar8PT2e2mu.SetLineWidth(2);
   HGD8PT2e2mu.SetLineWidth(2);
   HGDbar8PT2e2mu.SetLineWidth(2);
   HUUbar8PT4e.SetLineWidth(2);
   HDDbar8PT4e.SetLineWidth(2);
   HGU8PT4e.SetLineWidth(2);
   HGUbar8PT4e.SetLineWidth(2);
   HGD8PT4e.SetLineWidth(2);
   HGDbar8PT4e.SetLineWidth(2);

   HSPT.SetLineColor(kBlack);
   HUUbar8PT2e2mu.SetLineColor(kGreen - 3);
   HDDbar8PT2e2mu.SetLineColor(kGreen + 3);
   HGU8PT2e2mu.SetLineColor(kBlue);
   HGUbar8PT2e2mu.SetLineColor(kCyan);
   HGD8PT2e2mu.SetLineColor(kRed);
   HGDbar8PT2e2mu.SetLineColor(kOrange);
   HUUbar8PT4e.SetLineColor(kGreen - 3);
   HDDbar8PT4e.SetLineColor(kGreen + 3);
   HGU8PT4e.SetLineColor(kBlue);
   HGUbar8PT4e.SetLineColor(kCyan);
   HGD8PT4e.SetLineColor(kRed);
   HGDbar8PT4e.SetLineColor(kOrange);
   
   HUUbar8PT4e.SetLineStyle(kDashed);
   HDDbar8PT4e.SetLineStyle(kDashed);
   HGU8PT4e.SetLineStyle(kDashed);
   HGUbar8PT4e.SetLineStyle(kDashed);
   HGD8PT4e.SetLineStyle(kDashed);
   HGDbar8PT4e.SetLineStyle(kDashed);

   HSY.SetLineWidth(2);
   HUUbar8Y2e2mu.SetLineWidth(2);
   HDDbar8Y2e2mu.SetLineWidth(2);
   HGU8Y2e2mu.SetLineWidth(2);
   HGUbar8Y2e2mu.SetLineWidth(2);
   HGD8Y2e2mu.SetLineWidth(2);
   HGDbar8Y2e2mu.SetLineWidth(2);
   HUUbar8Y4e.SetLineWidth(2);
   HDDbar8Y4e.SetLineWidth(2);
   HGU8Y4e.SetLineWidth(2);
   HGUbar8Y4e.SetLineWidth(2);
   HGD8Y4e.SetLineWidth(2);
   HGDbar8Y4e.SetLineWidth(2);

   HSY.SetLineColor(kBlack);
   HUUbar8Y2e2mu.SetLineColor(kGreen - 3);
   HDDbar8Y2e2mu.SetLineColor(kGreen + 3);
   HGU8Y2e2mu.SetLineColor(kBlue);
   HGUbar8Y2e2mu.SetLineColor(kCyan);
   HGD8Y2e2mu.SetLineColor(kRed);
   HGDbar8Y2e2mu.SetLineColor(kOrange);
   HUUbar8Y4e.SetLineColor(kGreen - 3);
   HDDbar8Y4e.SetLineColor(kGreen + 3);
   HGU8Y4e.SetLineColor(kBlue);
   HGUbar8Y4e.SetLineColor(kCyan);
   HGD8Y4e.SetLineColor(kRed);
   HGDbar8Y4e.SetLineColor(kOrange);
   
   HUUbar8Y4e.SetLineStyle(kDashed);
   HDDbar8Y4e.SetLineStyle(kDashed);
   HGU8Y4e.SetLineStyle(kDashed);
   HGUbar8Y4e.SetLineStyle(kDashed);
   HGD8Y4e.SetLineStyle(kDashed);
   HGDbar8Y4e.SetLineStyle(kDashed);

   HUUbar8M4l2e2mu.SetLineWidth(2);
   HDDbar8M4l2e2mu.SetLineWidth(2);
   HGU8M4l2e2mu.SetLineWidth(2);
   HGUbar8M4l2e2mu.SetLineWidth(2);
   HGD8M4l2e2mu.SetLineWidth(2);
   HGDbar8M4l2e2mu.SetLineWidth(2);
   HUUbar8M4l4e.SetLineWidth(2);
   HDDbar8M4l4e.SetLineWidth(2);
   HGU8M4l4e.SetLineWidth(2);
   HGUbar8M4l4e.SetLineWidth(2);
   HGD8M4l4e.SetLineWidth(2);
   HGDbar8M4l4e.SetLineWidth(2);

   HUUbar8M4l2e2mu.SetLineColor(kGreen - 3);
   HDDbar8M4l2e2mu.SetLineColor(kGreen + 3);
   HGU8M4l2e2mu.SetLineColor(kBlue);
   HGUbar8M4l2e2mu.SetLineColor(kCyan);
   HGD8M4l2e2mu.SetLineColor(kRed);
   HGDbar8M4l2e2mu.SetLineColor(kOrange);
   HUUbar8M4l4e.SetLineColor(kGreen - 3);
   HDDbar8M4l4e.SetLineColor(kGreen + 3);
   HGU8M4l4e.SetLineColor(kBlue);
   HGUbar8M4l4e.SetLineColor(kCyan);
   HGD8M4l4e.SetLineColor(kRed);
   HGDbar8M4l4e.SetLineColor(kOrange);
   
   HUUbar8M4l4e.SetLineStyle(kDashed);
   HDDbar8M4l4e.SetLineStyle(kDashed);
   HGU8M4l4e.SetLineStyle(kDashed);
   HGUbar8M4l4e.SetLineStyle(kDashed);
   HGD8M4l4e.SetLineStyle(kDashed);
   HGDbar8M4l4e.SetLineStyle(kDashed);
   
   HUUbar8YComp2e2mu.SetLineColor(kGreen - 3);
   HDDbar8YComp2e2mu.SetLineColor(kGreen + 3);
   HGU8YComp2e2mu.SetLineColor(kBlue);
   HGUbar8YComp2e2mu.SetLineColor(kCyan);
   HGD8YComp2e2mu.SetLineColor(kRed);
   HGDbar8YComp2e2mu.SetLineColor(kOrange);
   HUUbar8YComp2e2mu.SetFillColor(kGreen - 3);
   HDDbar8YComp2e2mu.SetFillColor(kGreen + 3);
   HGU8YComp2e2mu.SetFillColor(kBlue);
   HGUbar8YComp2e2mu.SetFillColor(kCyan);
   HGD8YComp2e2mu.SetFillColor(kRed);
   HGDbar8YComp2e2mu.SetFillColor(kOrange);
   
   HUUbar8YComp22e2mu.SetLineColor(kGreen - 3);
   HDDbar8YComp22e2mu.SetLineColor(kGreen + 3);
   HGU8YComp22e2mu.SetLineColor(kBlue);
   HGUbar8YComp22e2mu.SetLineColor(kCyan);
   HGD8YComp22e2mu.SetLineColor(kRed);
   HGDbar8YComp22e2mu.SetLineColor(kOrange);
   HUUbar8YComp22e2mu.SetFillColor(kGreen - 3);
   HDDbar8YComp22e2mu.SetFillColor(kGreen + 3);
   HGU8YComp22e2mu.SetFillColor(kBlue);
   HGUbar8YComp22e2mu.SetFillColor(kCyan);
   HGD8YComp22e2mu.SetFillColor(kRed);
   HGDbar8YComp22e2mu.SetFillColor(kOrange);

   double x1, x2, y1, y2;
   x1 = ThesisNDCMappingRegularX(0.6);
   x2 = ThesisNDCMappingRegularX(0.9);
   y1 = ThesisNDCMappingRegularY(0.85);
   y2 = ThesisNDCMappingRegularY(0.52);

   TLegend Legend(x1, y1, x2, y2);
   Legend.SetFillStyle(0);
   Legend.SetTextFont(42);
   Legend.SetBorderSize(0);
   Legend.AddEntry(&HSPT, "SM Higgs", "l");
   Legend.AddEntry(&HUUbar8PT2e2mu, "u+#bar{u} #rightarrow 4l", "l");
   Legend.AddEntry(&HDDbar8PT2e2mu, "d+#bar{d} #rightarrow 4l", "l");
   Legend.AddEntry(&HGU8PT2e2mu,    "g+u #rightarrow 4l", "l");
   Legend.AddEntry(&HGUbar8PT2e2mu, "g+#bar{u} #rightarrow 4l", "l");
   Legend.AddEntry(&HGD8PT2e2mu,    "g+d #rightarrow 4l", "l");
   Legend.AddEntry(&HGDbar8PT2e2mu, "g+#bar{d} #rightarrow 4l", "l");

   TCanvas C;

   C.SetLogy(true);

   TH1D HWorldPT("HWorldPT", ";p_{T};a.u.", 100, 0, 100);
   HWorldPT.SetStats(0);
   HWorldPT.GetXaxis()->SetTitleOffset(1.1);
   HWorldPT.GetYaxis()->SetTitleOffset(1.2);
   HWorldPT.SetMaximum(1);
   HWorldPT.SetMinimum(1e-4);

   HWorldPT.Draw();
   HSPT.Draw("same");
   HUUbar8PT2e2mu.Draw("same");
   HDDbar8PT2e2mu.Draw("same");
   HGU8PT2e2mu.Draw("same");
   HGUbar8PT2e2mu.Draw("same");
   HGD8PT2e2mu.Draw("same");
   HGDbar8PT2e2mu.Draw("same");
   // HUUbar8PT4e.Draw("same");
   // HDDbar8PT4e.Draw("same");
   // HGU8PT4e.Draw("same");
   // HGUbar8PT4e.Draw("same");
   // HGD8PT4e.Draw("same");
   // HGDbar8PT4e.Draw("same");

   Legend.Draw();

   C.SaveAs("MultiDimensionalOverview-Production-SpectrumPT.png");
   C.SaveAs("MultiDimensionalOverview-Production-SpectrumPT.C");
   C.SaveAs("MultiDimensionalOverview-Production-SpectrumPT.eps");
   C.SaveAs("MultiDimensionalOverview-Production-SpectrumPT.pdf");

   TH1D HWorldY("HWorldY", ";y_{4l};a.u.", 100, -5, 5);
   HWorldY.SetStats(0);
   HWorldY.GetXaxis()->SetTitleOffset(1.1);
   HWorldY.GetYaxis()->SetTitleOffset(1.2);
   HWorldY.SetMaximum(0.58);

   C.SetLogy(false);
   HWorldY.Draw();
   HSY.Draw("same");
   HUUbar8Y2e2mu.Draw("same");
   HDDbar8Y2e2mu.Draw("same");
   HGU8Y2e2mu.Draw("same");
   HGUbar8Y2e2mu.Draw("same");
   HGD8Y2e2mu.Draw("same");
   HGDbar8Y2e2mu.Draw("same");
   // HUUbar8Y4e.Draw("same");
   // HDDbar8Y4e.Draw("same");
   // HGU8Y4e.Draw("same");
   // HGUbar8Y4e.Draw("same");
   // HGD8Y4e.Draw("same");
   // HGDbar8Y4e.Draw("same");
   
   Legend.Draw();

   C.SaveAs("MultiDimensionalOverview-Production-SpectrumY.png");
   C.SaveAs("MultiDimensionalOverview-Production-SpectrumY.C");
   C.SaveAs("MultiDimensionalOverview-Production-SpectrumY.eps");
   C.SaveAs("MultiDimensionalOverview-Production-SpectrumY.pdf");

   TH1D HWorldM4l("HWorldM4l", ";m_{4l};a.u.", 100, 115, 135);
   HWorldM4l.SetStats(0);
   HWorldM4l.GetXaxis()->SetTitleOffset(1.1);
   HWorldM4l.GetYaxis()->SetTitleOffset(1.2);
   HWorldM4l.SetMaximum(0.098);

   HWorldM4l.Draw();
   HUUbar8M4l2e2mu.Draw("same");
   HDDbar8M4l2e2mu.Draw("same");
   HGU8M4l2e2mu.Draw("same");
   HGUbar8M4l2e2mu.Draw("same");
   HGD8M4l2e2mu.Draw("same");
   HGDbar8M4l2e2mu.Draw("same");
   // HUUbar8M4l4e.Draw("same");
   // HDDbar8M4l4e.Draw("same");
   // HGU8M4l4e.Draw("same");
   // HGUbar8M4l4e.Draw("same");
   // HGD8M4l4e.Draw("same");
   // HGDbar8M4l4e.Draw("same");

   x1 = ThesisNDCMappingRegularX(0.6);
   x2 = ThesisNDCMappingRegularX(0.9);
   y1 = ThesisNDCMappingRegularY(0.85);
   y2 = ThesisNDCMappingRegularY(0.52);
   
   TLegend Legend2(x1, y1, x2, y2);
   Legend2.SetFillStyle(0);
   Legend2.SetTextFont(42);
   Legend2.SetBorderSize(0);
   Legend2.AddEntry(&HSPT, "", "");
   Legend2.AddEntry(&HUUbar8PT2e2mu, "u+#bar{u} #rightarrow 4l", "l");
   Legend2.AddEntry(&HDDbar8PT2e2mu, "d+#bar{d} #rightarrow 4l", "l");
   Legend2.AddEntry(&HGU8PT2e2mu,    "g+u #rightarrow 4l", "l");
   Legend2.AddEntry(&HGUbar8PT2e2mu, "g+#bar{u} #rightarrow 4l", "l");
   Legend2.AddEntry(&HGD8PT2e2mu,    "g+d #rightarrow 4l", "l");
   Legend2.AddEntry(&HGDbar8PT2e2mu, "g+#bar{d} #rightarrow 4l", "l");
   Legend2.Draw();
   
   C.SaveAs("MultiDimensionalOverview-Production-SpectrumM4l.png");
   C.SaveAs("MultiDimensionalOverview-Production-SpectrumM4l.C");
   C.SaveAs("MultiDimensionalOverview-Production-SpectrumM4l.eps");
   C.SaveAs("MultiDimensionalOverview-Production-SpectrumM4l.pdf");

   TH2D HSPTYWorld("HSPTYWorld", ";p_{T};y_{4l}", 100, 0, 100, 100, -3.9, 3.9);
   HSPTYWorld.SetStats(0);
   HSPTYWorld.Draw("");
   HSPTY.Draw("colz same");
 
   C.SaveAs("MultiDimensionalOverview-Production-SpectrumPTY.png");
   C.SaveAs("MultiDimensionalOverview-Production-SpectrumPTY.C");
   C.SaveAs("MultiDimensionalOverview-Production-SpectrumPTY.eps");
   C.SaveAs("MultiDimensionalOverview-Production-SpectrumPTY.pdf");

   TH1D HWorldYComp("HWorldYComp", ";y_{4l};Fraction", 100, -4.25, 4.25);
   HWorldYComp.SetStats(0);
   HWorldYComp.GetXaxis()->SetTitleOffset(1.1);
   HWorldYComp.GetYaxis()->SetTitleOffset(1.2);
   HWorldYComp.SetMaximum(2);

   HWorldYComp.Draw();
   HUUbar8YComp2e2mu.Draw("same");
   HDDbar8YComp2e2mu.Draw("same");
   HGU8YComp2e2mu.Draw("same");
   HGUbar8YComp2e2mu.Draw("same");
   HGD8YComp2e2mu.Draw("same");
   HGDbar8YComp2e2mu.Draw("same");

   Legend2.Draw();
   
   C.SaveAs("MultiDimensionalOverview-Production-InitialStateDecomposition.png");
   C.SaveAs("MultiDimensionalOverview-Production-InitialStateDecomposition.C");
   C.SaveAs("MultiDimensionalOverview-Production-InitialStateDecomposition.eps");
   C.SaveAs("MultiDimensionalOverview-Production-InitialStateDecomposition.pdf");
   
   HWorldYComp.Draw();
   HUUbar8YComp22e2mu.Draw("same");
   HDDbar8YComp22e2mu.Draw("same");
   HGU8YComp22e2mu.Draw("same");
   HGUbar8YComp22e2mu.Draw("same");
   HGD8YComp22e2mu.Draw("same");
   HGDbar8YComp22e2mu.Draw("same");

   Legend2.Draw();
   
   C.SaveAs("MultiDimensionalOverview-Production-InitialStateDecomposition2.png");
   C.SaveAs("MultiDimensionalOverview-Production-InitialStateDecomposition2.C");
   C.SaveAs("MultiDimensionalOverview-Production-InitialStateDecomposition2.eps");
   C.SaveAs("MultiDimensionalOverview-Production-InitialStateDecomposition2.pdf");
 
   return 0;
}






