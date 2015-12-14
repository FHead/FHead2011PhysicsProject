#include <iostream>
#include <iomanip>
using namespace std;

#include "DataHelper.h"

int main(int argc, char *argv[])
{
   if(argc < 2)
   {
      cerr << "Usage: " << argv[0] << " DHFile" << endl;
      return -1;
   }

   DataHelper DHFile(argv[1]);

   cout << "\\begin{tabular}{|c|c|c|}" << endl;
   cout << "   \\hline" << endl;
   cout << "   Model & True Value & 68\\% Range \\\\" << endl;
   cout << "   \\hline" << endl;
   cout << "   R_2^{ZZ} & - & (" << DHFile["YY_Y_4_2"]["Min"].GetDouble()
      << ", " << DHFile["YY_Y_4_2"]["Max"].GetDouble() << ") \\\\" << endl;
   cout << "   \\hline" << endl;
   cout << "   R_3^{ZZ} & - & (" << DHFile["YY_Y_4_3"]["Min"].GetDouble()
      << ", " << DHFile["YY_Y_4_3"]["Max"].GetDouble() << ") \\\\" << endl;
   cout << "   \\hline" << endl;
   cout << "   R_2^{ZA} & 0 & (" << DHFile["YY_Y_4_4"]["Min"].GetDouble()
      << ", " << DHFile["YY_Y_4_4"]["Max"].GetDouble() << ") \\\\" << endl;
   cout << "   \\hline" << endl;
   cout << "   R_3^{ZA} & 0 & (" << DHFile["YY_Y_4_5"]["Min"].GetDouble()
      << ", " << DHFile["YY_Y_4_5"]["Max"].GetDouble() << ") \\\\" << endl;
   cout << "   \\hline" << endl;
   cout << "   R_2^{AA} & 0 & (" << DHFile["YY_Y_4_6"]["Min"].GetDouble()
      << ", " << DHFile["YY_Y_4_6"]["Max"].GetDouble() << ") \\\\" << endl;
   cout << "   \\hline" << endl;
   cout << "   R_3^{AA} & 0 & (" << DHFile["YY_Y_4_7"]["Min"].GetDouble()
      << ", " << DHFile["YY_Y_4_7"]["Max"].GetDouble() << ") \\\\" << endl;
   cout << "   \\hline" << endl;
   cout << "   F_B & 0.375 & (" << DHFile["YY_Y_4_8"]["Min"].GetDouble()
      << ", " << DHFile["YY_Y_4_8"]["Max"].GetDouble() << ") \\\\" << endl;
   cout << "   \\hline" << endl;
   cout << "\\end{tabular}" << endl;

   return 0;
}







