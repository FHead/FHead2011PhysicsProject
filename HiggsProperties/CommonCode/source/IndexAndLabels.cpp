#include <string>
using namespace std;

#include "IndexAndLabels.h"

string IndexAndLabels::IndexToNewLabel(int Index)
{
   switch(Index)
   {
   case 1:    return "A1ZZR";
   case 2:    return "A1ZZI";
   case 3:    return "A2ZZR";
   case 4:    return "A2ZZI";
   case 5:    return "A3ZZR";
   case 6:    return "A3ZZI";
   case 7:    return "A2ZAR";
   case 8:    return "A2ZAI";
   case 9:    return "A3ZAR";
   case 10:   return "A3ZAI";
   case 11:   return "A2AAR";
   case 12:   return "A2AAI";
   case 13:   return "A3AAR";
   case 14:   return "A3AAI";
   }
   
   return "NONE";
}

string IndexAndLabels::IndexToOldLabel(int Index)
{
   switch(Index)
   {
   case 1:    return "ahR";
   case 2:    return "ahI";
   case 3:    return "aZR";
   case 4:    return "aZI";
   case 5:    return "aZdR";
   case 6:    return "aZdI";
   case 7:    return "aZAR";
   case 8:    return "aZAI";
   case 9:    return "aZAdR";
   case 10:   return "aZAdI";
   case 11:   return "aAR";
   case 12:   return "aAI";
   case 13:   return "aAdR";
   case 14:   return "aAdI";
   }
   
   return "NONE";
}

int IndexAndLabels::LabelToIndex(string Label)
{
   if(Label == "A1ZZR" || Label == "ahR")     return 1;
   if(Label == "A1ZZI" || Label == "ahI")     return 2;
   if(Label == "A2ZZR" || Label == "aZR")     return 3;
   if(Label == "A2ZZI" || Label == "aZI")     return 4;
   if(Label == "A3ZZR" || Label == "aZdR")    return 5;
   if(Label == "A3ZZI" || Label == "aZdI")    return 6;
   if(Label == "A2ZAR" || Label == "aZAR")    return 7;
   if(Label == "A2ZAI" || Label == "aZAI")    return 8;
   if(Label == "A3ZAR" || Label == "aZAdR")   return 9;
   if(Label == "A3ZAI" || Label == "aZAdI")   return 10;
   if(Label == "A2AAR" || Label == "aAR")     return 11;
   if(Label == "A2AAI" || Label == "aAI")     return 12;
   if(Label == "A3AAR" || Label == "aAdR")    return 13;
   if(Label == "A3AAI" || Label == "aAdI")    return 14;

   return -1;
}

int IndexAndLabels::IndexToLinearizedIndex(int Index)
{
   return IndexToLinearizedIndex(Index, Index);
}

int IndexAndLabels::LabelToLinearizedIndex(string Label)
{
   return IndexToLinearizedIndex(LabelToIndex(Label));
}

int IndexAndLabels::IndexToLinearizedIndex(int Index1, int Index2)
{
   return (Index1 - 1) * 14 + Index2;
}

int IndexAndLabels::LabelToLinearizedIndex(string Label1, string Label2)
{
   int Index1 = LabelToIndex(Label1);
   int Index2 = LabelToIndex(Label2);

   return IndexToLinearizedIndex(Index1, Index2);
}
   
pair<int, int> IndexAndLabels::LinearizedIndexToIndex(int Index)
{
   int Index1 = (Index - 1) / 14 + 1;
   int Index2 = (Index - 1) % 14 + 1;

   return pair<int, int>(Index1, Index2);
}

int IndexAndLabels::IndexToComponentIndex(int Index)
{
   return IndexToComponentIndex(Index, Index);
}

int IndexAndLabels::LabelToComponentIndex(string Label)
{
   return IndexToComponentIndex(LabelToIndex(Label));
}

int IndexAndLabels::IndexToComponentIndex(int Index1, int Index2)
{
   if(Index1 <= 0 || Index2 <= 0 || Index1 > 14 || Index2 > 14)
      return -1;

   int Indices[14][14] =
      {{1,  -1,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25},
      {-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1},
      {14,  -1,   2,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36},
      {15,  -1,  26,   3,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46},
      {16,  -1,  27,  37,   4,  47,  48,  49,  50,  51,  52,  53,  54,  55},
      {17,  -1,  28,  38,  47,   5,  56,  57,  58,  59,  60,  61,  62,  63},
      {18,  -1,  29,  39,  48,  56,   6,  64,  65,  66,  67,  68,  69,  70},
      {19,  -1,  30,  40,  49,  57,  64,   7,  71,  72,  73,  74,  75,  76},
      {20,  -1,  31,  41,  50,  58,  65,  71,   8,  77,  78,  79,  80,  81},
      {21,  -1,  32,  42,  51,  59,  66,  72,  77,   9,  82,  83,  84,  85},
      {22,  -1,  33,  43,  52,  60,  67,  73,  78,  82,  10,  86,  87,  88},
      {23,  -1,  34,  44,  53,  61,  68,  74,  79,  83,  86,  11,  89,  90},
      {24,  -1,  35,  45,  54,  62,  69,  75,  80,  84,  87,  89,  12,  91},
      {25,  -1,  36,  46,  55,  63,  70,  76,  81,  85,  88,  90,  91,  13}};

   return Indices[Index1-1][Index2-1];
}

int IndexAndLabels::LabelToComponentIndex(string Label1, string Label2)
{
   int Index1 = LabelToIndex(Label1);
   int Index2 = LabelToIndex(Label2);

   return IndexToComponentIndex(Index1, Index2);
}

pair<int, int> IndexAndLabels::ComponentIndexToIndex(int Index)
{
   if(Index == 1)         return pair<int, int>(1, 1);
   else if(Index <= 13)   return pair<int, int>(Index + 1, Index + 1);
   else if(Index > 91)    return pair<int, int>(-1, -1);
   else if(Index < 0)     return pair<int, int>(-1, -10);

   int Starts[12] = {14, 26, 37, 47, 56, 64, 71, 77, 82, 86, 89, 91};
   for(int i = 0; i < 12; i++)
   {
      if(Index < Starts[i])
         continue;

      int Index1 = (i > 0) ? i + 2 : 1;
      int Index2 = (Index - Starts[i]) + (i + 3);

      return pair<int, int>(Index1, Index2);
   }

   return pair<int, int>(-1, -1);
}






