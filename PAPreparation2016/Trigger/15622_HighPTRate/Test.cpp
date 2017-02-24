for(int i=0; i<nTriggers_L1; i++)
{ // L1 loop (loop over all L1 triggers)
   if(TriggerFlag_L1[i])
   {
      nEvts_L1_raw[i]++;                                            

      for(int j=0; j<nTriggersHlt; j++)               // to see how many raw events 
      {
         if(TriggerFlag_HLT[j] && L1PathForHLT[j]==i) // passed both the L1 and HLT
         {
            nEvtsHlt_ps1[j]++;                          // if all PS = 1. 
         }
      }

      if(Int_t(nEvts_L1_raw[i]) % Int_t(PreScale_L1[i])==0)
      {
         for(int j=0; j<nTriggersHlt; j++) // HLT loop
         {
            if(TriggerFlag_HLT[j] && L1PathForHLT[j]==i)//if HLT fired && we're looking at the corresponding L1
            {
               nEvtsHlt_raw[j]++;                                      
            }// if HLT fired  &&  we're looking at the corresponding L1
         }// HLT loop 
      }// L1 pScale 
   }// if L1 fired 
}// L1 loop 


