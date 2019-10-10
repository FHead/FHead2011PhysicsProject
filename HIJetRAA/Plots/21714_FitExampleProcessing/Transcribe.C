
void Transcribe(string FileName = "X.root")
{
   TList *List = gPad->GetCanvas()->GetListOfPrimitives();
   TIter next(List);

   TFile File(FileName.c_str(), "RECREATE");

   int N = 1;

   TObject *object = nullptr;
   while((object = next()))
   {
      if(object->InheritsFrom("TH1") == false && object->InheritsFrom("TGraph") == false && object->InheritsFrom("TF1") == false)
         continue;

      cout << object->GetName() << ": " << object->GetTitle() << endl;

      object->Clone(Form("%s_%d", object->GetName(), N))->Write();
      N = N + 1;
   }

   File.Close();
}



