#include <iostream>
using namespace std;

#include "DataHelper.h"

int main()
{
   string Energies[] = {"0TeV", "13TeV", "14TeV"};
   string Cuts[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M"};
   string As[] = {"A1ZZ", "A2ZZ", "A3ZZ", "A4ZZ", "A1ZA", "A2ZA", "A3ZA", "A4ZA", "A1AZ", "A2AZ",
      "A3AZ", "A4AZ", "A1AA", "A2AA", "A3AA", "A4AA"};
   string Parts[] = {"R", "I"};
   string Channels[] = {"T", "V"};

   DataHelper DHFile("Normalization.dh");

   ofstream out("Normalization.json");

   out << "var Normalization = {";

   for(int iE = 0; iE < 3; iE++)
   {
      string State = Energies[iE];

      if(iE != 0)
         out << ", ";
      out << "Energy" << State << ": {";

      for(int iC = 0; iC < 13; iC++)
      {
         string Cut = Cuts[iC];

         if(iC != 0)
            out << ", ";
         out << "Cut" << Cut << ": {";

         for(int iA1 = 0; iA1 < 16; iA1++)
         {
            for(int iP1 = 0; iP1 < 2; iP1++)
            {
               if(iA1 != 0 || iP1 != 0)
                  out << ", ";

               out << As[iA1] << Parts[iP1] << ": {";

               for(int iA2 = 0; iA2 < 16; iA2++)
               {
                  for(int iP2 = 0; iP2 < 2; iP2++)
                  {
                     if(iA2 != 0 || iP2 != 0)
                        out << ", ";

                     out << As[iA2] << Parts[iP2] << ": ["
                        << DHFile[State]["T"+Cut+"1_"+As[iA1]+Parts[iP1]+"_"+As[iA2]+Parts[iP2]].GetDouble()
                        << ","
                        << DHFile[State]["V"+Cut+"1_"+As[iA1]+Parts[iP1]+"_"+As[iA2]+Parts[iP2]].GetDouble()
                        << "]";
                  }
               }

               out << "}";
            }
         }

         out << "}";
      }

      out << "}";
   }

   out << "};" << endl;
}



