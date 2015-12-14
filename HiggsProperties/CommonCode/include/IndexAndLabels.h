#ifndef INDEXANDLABELS_12315_FHEAD_AKSDNFKJASDNFJLAWBEJFAHWEJF
#define INDEXANDLABELS_12315_FHEAD_AKSDNFKJASDNFJLAWBEJFAHWEJF

#include <string>
#include <map>

namespace IndexAndLabels
{
   std::string IndexToNewLabel(int Index);
   std::string IndexToOldLabel(int Index);
   int LabelToIndex(std::string Label);
   int IndexToLinearizedIndex(int Index);
   int LabelToLinearizedIndex(std::string Label);
   int IndexToLinearizedIndex(int Index1, int Index2);
   int LabelToLinearizedIndex(std::string Label1, std::string Label2);
   std::pair<int, int> LinearizedIndexToIndex(int Index);
   int IndexToComponentIndex(int Index);
   int LabelToComponentIndex(std::string Label);
   int IndexToComponentIndex(int Index1, int Index2);
   int LabelToComponentIndex(std::string Label1, std::string Label2);
   std::pair<int, int> ComponentIndexToIndex(int Index);
}

#endif
