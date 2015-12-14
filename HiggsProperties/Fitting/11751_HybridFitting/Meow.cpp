#include <iostream>
using namespace std;

#include "DataHelper.h"

int main()
{
   DataHelper DHFile("Normalization.dh");

   cout << DHFile["ee"]["T1A"].GetDouble() / DHFile["em"]["T1A"].GetDouble() << endl;
   cout << DHFile["ee"]["T1B"].GetDouble() / DHFile["em"]["T1B"].GetDouble() << endl;
   cout << DHFile["ee"]["T1C"].GetDouble() / DHFile["em"]["T1C"].GetDouble() << endl;
   cout << DHFile["ee"]["T1D"].GetDouble() / DHFile["em"]["T1D"].GetDouble() << endl;
   cout << DHFile["ee"]["T1E"].GetDouble() / DHFile["em"]["T1E"].GetDouble() << endl;
   cout << DHFile["ee"]["T1F"].GetDouble() / DHFile["em"]["T1F"].GetDouble() << endl;
   
   cout << DHFile["ee"]["T1A"].GetDouble() / DHFile["me"]["T1A"].GetDouble() << endl;
   cout << DHFile["ee"]["T1B"].GetDouble() / DHFile["me"]["T1B"].GetDouble() << endl;
   cout << DHFile["ee"]["T1C"].GetDouble() / DHFile["me"]["T1C"].GetDouble() << endl;
   cout << DHFile["ee"]["T1D"].GetDouble() / DHFile["me"]["T1D"].GetDouble() << endl;
   cout << DHFile["ee"]["T1E"].GetDouble() / DHFile["me"]["T1E"].GetDouble() << endl;
   cout << DHFile["ee"]["T1F"].GetDouble() / DHFile["me"]["T1F"].GetDouble() << endl;
   
   cout << DHFile["ee"]["T1A"].GetDouble() / DHFile["mm"]["T1A"].GetDouble() << endl;
   cout << DHFile["ee"]["T1B"].GetDouble() / DHFile["mm"]["T1B"].GetDouble() << endl;
   cout << DHFile["ee"]["T1C"].GetDouble() / DHFile["mm"]["T1C"].GetDouble() << endl;
   cout << DHFile["ee"]["T1D"].GetDouble() / DHFile["mm"]["T1D"].GetDouble() << endl;
   cout << DHFile["ee"]["T1E"].GetDouble() / DHFile["mm"]["T1E"].GetDouble() << endl;
   cout << DHFile["ee"]["T1F"].GetDouble() / DHFile["mm"]["T1F"].GetDouble() << endl;
}





