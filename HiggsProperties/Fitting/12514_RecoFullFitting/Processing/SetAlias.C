{
   for(int i1 = 0; i1 < 2; i1++)
   {
      for(int i2 = 0; i2 < 2; i2++)
      {
         for(int i3 = 0; i3 < 2; i3++)
         {
            for(int i4 = 0; i4 < 2; i4++)
            {
               for(int i5 = 0; i5 < 2; i5++)
               {
                  for(int i6 = 0; i6 < 2; i6++)
                  {
                     string S1 = "NNNNNN";
                     if(i1 == 1)   S1[0] = 'Y';
                     if(i2 == 1)   S1[1] = 'Y';
                     if(i3 == 1)   S1[2] = 'Y';
                     if(i4 == 1)   S1[3] = 'Y';
                     if(i5 == 1)   S1[4] = 'Y';
                     if(i6 == 1)   S1[5] = 'Y';

                     string S2 = "(";
                     if(i1 == 1)   S2 = S2 + "A2ZZA1ZZError > 0";
                     else          S2 = S2 + "A2ZZA1ZZError == 0";
                     if(i2 == 1)   S2 = S2 + " && A3ZZA1ZZError > 0";
                     else          S2 = S2 + " && A3ZZA1ZZError == 0";
                     if(i3 == 1)   S2 = S2 + " && A2ZAA1ZZError > 0";
                     else          S2 = S2 + " && A2ZAA1ZZError == 0";
                     if(i4 == 1)   S2 = S2 + " && A3ZAA1ZZError > 0";
                     else          S2 = S2 + " && A3ZAA1ZZError == 0";
                     if(i5 == 1)   S2 = S2 + " && A2AAA1ZZError > 0";
                     else          S2 = S2 + " && A2AAA1ZZError == 0";
                     if(i6 == 1)   S2 = S2 + " && A3AAA1ZZError > 0";
                     else          S2 = S2 + " && A3AAA1ZZError == 0";
                     S2 = S2 + ")";

                     ResultTree->SetAlias(S1.c_str(), S2.c_str());
                  }
               }
            }
         }
      }
   }

   ResultTree->SetAlias("NN", "(N1Error == 0 && N2Error == 0)");
   ResultTree->SetAlias("NY", "(N1Error == 0 && N2Error > 0)");
   ResultTree->SetAlias("YN", "(N1Error > 0 && N2Error == 0)");
   ResultTree->SetAlias("YY", "(N1Error > 0 && N2Error > 0)");

   ResultTree->SetAlias("N", "(FemError == 0)");
   ResultTree->SetAlias("Y", "(FemError > 0)");

   ResultTree->SetAlias("A2ZZ", "A2ZZA1ZZ");
   ResultTree->SetAlias("A3ZZ", "A3ZZA1ZZ");
   ResultTree->SetAlias("A2ZA", "A2ZAA1ZZ");
   ResultTree->SetAlias("A3ZA", "A3ZAA1ZZ");
   ResultTree->SetAlias("A2AA", "A2AAA1ZZ");
   ResultTree->SetAlias("A3AA", "A3AAA1ZZ");

   ResultTree->SetAlias("ZZ", "sqrt(A2ZZ*A2ZZ+A3ZZ*A3ZZ+1)");
   ResultTree->SetAlias("ZA", "sqrt(A2ZA*A2ZA+A3ZA*A3ZA)");
   ResultTree->SetAlias("AA", "sqrt(A2AA*A2AA+A3AA*A3AA)");
}



