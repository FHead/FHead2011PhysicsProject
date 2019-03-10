grep KSI2K Log/LSFJOB_*/STDOUT LSFJOB_*/STDOUT \
   | awk '{print $11}' | tr -d '(' | TextToTree Meow.root 1
