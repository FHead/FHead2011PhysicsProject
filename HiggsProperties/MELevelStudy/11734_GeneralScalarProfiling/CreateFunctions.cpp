// Part rules:
//    AA/AA
//    ZZ/ZZ
//    ZA/ZA
//    AA/ZZ
//    ZA/AA
//    ZA/ZZ
//
//    A1*A1
//    A2*A2
//    A3*A3
//    A1*A2
//    A2*A3
//    A1*A3

#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main();
pair<int, int> MakePair(int Index1, int Index2);

int main()
{
   string labels[] = {"A1ZZ", "A2ZZ", "A3ZZ", "A1ZA", "A2ZA", "A3ZA", "A1AA", "A2AA", "A3AA"};
   vector<string> Labels(labels, labels + 9);
   
   string alternativelabels[] = {"ah", "aZ", "aZd", "none", "aZA", "aZAd", "none", "aA", "aAd"};
   vector<string> AlternativeLabels(alternativelabels, alternativelabels + 9);

   for(int i = 0; i < 6; i++)
   {
      int Start1, Start2;
      switch(i)
      {
         case 0:
            Start1 = 6, Start2 = 6;
            break;
         case 1:
            Start1 = 0, Start2 = 0;
            break;
         case 2:
            Start1 = 3, Start2 = 3;
            break;
         case 3:
            Start1 = 6, Start2 = 0;
            break;
         case 4:
            Start1 = 6, Start2 = 3;
            break;
         case 5:
            Start1 = 3, Start2 = 0;
            break;
      }

      for(int j = 0; j < 6; j++)
      {
         int Offset1, Offset2;
         switch(j)
         {
            case 0:
               Offset1 = 0, Offset2 = 0;
               break;
            case 1:
               Offset1 = 1, Offset2 = 1;
               break;
            case 2:
               Offset1 = 2, Offset2 = 2;
               break;
            case 3:
               Offset1 = 0, Offset2 = 1;
               break;
            case 4:
               Offset1 = 1, Offset2 = 2;
               break;
            case 5:
               Offset1 = 0, Offset2 = 2;
               break;
         }

         int PartNumber = i * 6 + j + 1;

         vector<pair<int, int> > PossibleCombinations;

         if(AlternativeLabels[Start1+Offset1] != "none" && AlternativeLabels[Start2+Offset2] != "none")
            PossibleCombinations.push_back(MakePair(Start1 + Offset1, Start2 + Offset2));
         if(AlternativeLabels[Start1+Offset2] != "none" && AlternativeLabels[Start2+Offset1] != "none")
            PossibleCombinations.push_back(MakePair(Start1 + Offset2, Start2 + Offset1));

         if(PossibleCombinations.size() == 0)
            continue;

         sort(PossibleCombinations.begin(), PossibleCombinations.end());
         PossibleCombinations.erase(unique(PossibleCombinations.begin(), PossibleCombinations.end()),
            PossibleCombinations.end());

         vector<pair<string, int> > AllParameters;
         for(int l = 0; l < (int)PossibleCombinations.size(); l++)
         {
            for(int k = 0; k < 4; k++)
            {
               if(PossibleCombinations[l].first == PossibleCombinations[l].second && k == 2)
                  continue;

               string RI1 = (k % 2 == 0) ? "R" : "I";
               string RI2 = (k / 2 == 0) ? "R" : "I";

               AllParameters.push_back(pair<string, int>(Labels[PossibleCombinations[l].first] + RI1,
                  PossibleCombinations[l].first * 10 + ((RI1 == "R") ? 0 : 1)));
               AllParameters.push_back(pair<string, int>(Labels[PossibleCombinations[l].second] + RI2,
                  PossibleCombinations[l].second * 10 + ((RI2 == "R") ? 0 : 1)));
            }
         }
         sort(AllParameters.begin(), AllParameters.end());
         AllParameters.erase(unique(AllParameters.begin(), AllParameters.end()), AllParameters.end());

         // cout << "All possible parameters = " << endl;
         // for(int k = 0; k < (int)AllParameters.size(); k++)
         // {
         //    int RI = AllParameters[k].second % 10;
         //    int Index = AllParameters[k].second / 10;
         //    cout << "   " << k + 1 << ": " << Labels[Index] << (RI == 0 ? "R" : "I") << endl;
         //    cout << "   " << " or " << AlternativeLabels[Index] << (RI == 0 ? "R" : "I") << endl;
         // }

         for(int l = 0; l < (int)PossibleCombinations.size(); l++)
         {
            for(int k = 0; k < 4; k++)
            {
               if(PossibleCombinations[l].first == PossibleCombinations[l].second && k == 2)
                  continue;

               string RI1 = (k % 2 == 0) ? "R" : "I";
               string RI2 = (k / 2 == 0) ? "R" : "I";

               vector<string> LabelList;
               LabelList.push_back(AlternativeLabels[PossibleCombinations[l].first] + RI1);
               LabelList.push_back(AlternativeLabels[PossibleCombinations[l].second] + RI2);
               sort(LabelList.begin(), LabelList.end());

               if(LabelList[0] != LabelList[1])
               {
                  cout << "double GetGeneralScalar4e_" << LabelList[0] << "_" << LabelList[1]
                     << "(LeptonVectors &leptons, double " << LabelList[0] << ", double " << LabelList[1] << ")"
                     << endl;
               }
               else
               {
                  cout << "double GetGeneralScalar4e_" << LabelList[0] << "_" << LabelList[1]
                     << "(LeptonVectors &leptons, double " << LabelList[0] << ")"
                     << endl;
               }
               cout << "{" << endl;
               cout << "   return GetGeneralScalar4e_Part" << PartNumber << "(leptons";

               for(int m = 0; m < (int)AllParameters.size(); m++)
               {
                  int RI = AllParameters[m].second % 10;
                  int Index = AllParameters[m].second / 10;
                  string CurrentLabel = AlternativeLabels[Index] + (RI == 0 ? "R" : "I");
                  if(CurrentLabel == LabelList[0] || CurrentLabel == LabelList[1])
                     cout << ", " << CurrentLabel;
                  else
                     cout << ", 0";
               }
               cout << ");" << endl;

               cout << "}" << endl;
               cout << endl;
            }
         }
      }
   }

   return 0;
}

pair<int, int> MakePair(int Index1, int Index2)
{
   return pair<int, int>(min(Index1, Index2), max(Index1, Index2));
}





