#include <iostream>
using namespace std;

#include "CommandLine.h"

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   int Tries = CL.GetInt("tries", 100000);

   return 0;
}



