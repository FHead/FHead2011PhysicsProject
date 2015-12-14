CC=g++

CFLAGS= -Wall -fPIC \
	-I$(ROOTSYS)/include/ \
	-I. -Isrc -Iinclude/ \
	-L.

.cpp.o:
	$(CC) -c $(CFLAGS) $< 
.cpp.a:
	$(CC) -c $(CFLAGS) $<
	ar r $@ $*.o; rm $*.o

all: Generate.x Generate_new.x Generate_bkg.x Make_dataset.x Evaluate_prob.x Evaluate_prob_new.x Make_full_dataset.x Make_Num_PDF.x Normalize_Num_PDF.x Measure_XP.x Measure_spinone.x Measure_spinzero.x Compare_spinzero.x Eff.x Read_bkg.x plot_bkg.x Make_Num_PDF_sig.x Make_Num_PDF_bkg.x Make_bkg_hist.x Measure_SB.x Make_reco_sig.x Make_reco_bkg.x

Generate.x: Makefile Generate.o 
	$(CC)  -fsigned-char -Wstrict-prototypes -Wimplicit  -Wmissing-prototypes -Wunused \
	-o Generate.x $(CFLAGS) Generate.o -L$(ROOTSYS)/lib/root $(shell root-config --glibs) 
	touch Generate.x

Generate_new.x: Makefile Generate_new.o 
	$(CC)  -fsigned-char -Wstrict-prototypes -Wimplicit  -Wmissing-prototypes -Wunused \
	-o Generate_new.x $(CFLAGS) Generate_new.o -L$(ROOTSYS)/lib/root $(shell root-config --glibs) 
	touch Generate_new.x

Generate_bkg.x: Makefile Generate_bkg.o 
	$(CC)  -fsigned-char -Wstrict-prototypes -Wimplicit  -Wmissing-prototypes -Wunused \
	-o Generate_bkg.x $(CFLAGS) Generate_bkg.o -L$(ROOTSYS)/lib/root $(shell root-config --glibs) 
	touch Generate_bkg.x

Make_dataset.x: Makefile Make_dataset.o 
	$(CC)  -fsigned-char -Wstrict-prototypes -Wimplicit  -Wmissing-prototypes -Wunused \
	-o Make_dataset.x $(CFLAGS) Make_dataset.o -L$(ROOTSYS)/lib/root $(shell root-config --glibs) 
	touch Make_dataset.x

Make_full_dataset.x: Makefile Make_full_dataset.o 
	$(CC)  -fsigned-char -Wstrict-prototypes -Wimplicit  -Wmissing-prototypes -Wunused \
	-o Make_full_dataset.x $(CFLAGS) Make_full_dataset.o -L$(ROOTSYS)/lib/root $(shell root-config --glibs) 
	touch Make_full_dataset.x

Make_reco_sig.x: Makefile Make_reco_sig.o 
	$(CC)  -fsigned-char -Wstrict-prototypes -Wimplicit  -Wmissing-prototypes -Wunused \
	-o Make_reco_sig.x $(CFLAGS) Make_reco_sig.o -L$(ROOTSYS)/lib/root $(shell root-config --glibs) 
	touch Make_reco_sig.x

Make_reco_bkg.x: Makefile Make_reco_bkg.o 
	$(CC)  -fsigned-char -Wstrict-prototypes -Wimplicit  -Wmissing-prototypes -Wunused \
	-o Make_reco_bkg.x $(CFLAGS) Make_reco_bkg.o -L$(ROOTSYS)/lib/root $(shell root-config --glibs) 
	touch Make_reco_bkg.x

Evaluate_prob.x: Makefile Evaluate_prob.o 
	$(CC)  -fsigned-char -Wstrict-prototypes -Wimplicit  -Wmissing-prototypes -Wunused \
	-o Evaluate_prob.x $(CFLAGS) Evaluate_prob.o -L$(ROOTSYS)/lib/root $(shell root-config --glibs) 
	touch Evaluate_prob.x

Evaluate_prob_new.x: Makefile Evaluate_prob_new.o 
	$(CC)  -fsigned-char -Wstrict-prototypes -Wimplicit  -Wmissing-prototypes -Wunused \
	-o Evaluate_prob_new.x $(CFLAGS) Evaluate_prob_new.o -L$(ROOTSYS)/lib/root $(shell root-config --glibs) 
	touch Evaluate_prob_new.x

Make_Num_PDF.x: Makefile Make_Num_PDF.o 
	$(CC)  -fsigned-char -Wstrict-prototypes -Wimplicit  -Wmissing-prototypes -Wunused \
	-o Make_Num_PDF.x $(CFLAGS) Make_Num_PDF.o -L$(ROOTSYS)/lib/root $(shell root-config --glibs) 
	touch Make_Num_PDF.x

Make_Num_PDF_sig.x: Makefile Make_Num_PDF_sig.o 
	$(CC)  -fsigned-char -Wstrict-prototypes -Wimplicit  -Wmissing-prototypes -Wunused \
	-o Make_Num_PDF_sig.x $(CFLAGS) Make_Num_PDF_sig.o -L$(ROOTSYS)/lib/root $(shell root-config --glibs) 
	touch Make_Num_PDF_sig.x

Make_Num_PDF_bkg.x: Makefile Make_Num_PDF_bkg.o 
	$(CC)  -fsigned-char -Wstrict-prototypes -Wimplicit  -Wmissing-prototypes -Wunused \
	-o Make_Num_PDF_bkg.x $(CFLAGS) Make_Num_PDF_bkg.o -L$(ROOTSYS)/lib/root $(shell root-config --glibs) 
	touch Make_Num_PDF_bkg.x

Make_bkg_hist.x: Makefile Make_bkg_hist.o 
	$(CC)  -fsigned-char -Wstrict-prototypes -Wimplicit  -Wmissing-prototypes -Wunused \
	-o Make_bkg_hist.x $(CFLAGS) Make_bkg_hist.o -L$(ROOTSYS)/lib/root $(shell root-config --glibs) 
	touch Make_bkg_hist.x

Normalize_Num_PDF.x: Makefile Normalize_Num_PDF.o 
	$(CC)  -fsigned-char -Wstrict-prototypes -Wimplicit  -Wmissing-prototypes -Wunused \
	-o Normalize_Num_PDF.x $(CFLAGS) Normalize_Num_PDF.o -L$(ROOTSYS)/lib/root $(shell root-config --glibs) 
	touch Normalize_Num_PDF.x

Measure_XP.x: Makefile Measure_XP.o 
	$(CC)  -fsigned-char -Wstrict-prototypes -Wimplicit  -Wmissing-prototypes -Wunused \
	-o Measure_XP.x $(CFLAGS) Measure_XP.o -L$(ROOTSYS)/lib/root $(shell root-config --glibs) 
	touch Measure_XP.x

Measure_spinone.x: Makefile Measure_spinone.o 
	$(CC)  -fsigned-char -Wstrict-prototypes -Wimplicit  -Wmissing-prototypes -Wunused \
	-o Measure_spinone.x $(CFLAGS) Measure_spinone.o -L$(ROOTSYS)/lib/root $(shell root-config --glibs) 
	touch Measure_spinone.x

Measure_spinzero.x: Makefile Measure_spinzero.o 
	$(CC)  -fsigned-char -Wstrict-prototypes -Wimplicit  -Wmissing-prototypes -Wunused \
	-o Measure_spinzero.x $(CFLAGS) Measure_spinzero.o -L$(ROOTSYS)/lib/root $(shell root-config --glibs) 
	touch Measure_spinzero.x

Compare_spinzero.x: Makefile Compare_spinzero.o 
	$(CC)  -fsigned-char -Wstrict-prototypes -Wimplicit  -Wmissing-prototypes -Wunused \
	-o Compare_spinzero.x $(CFLAGS) Compare_spinzero.o -L$(ROOTSYS)/lib/root $(shell root-config --glibs) 
	touch Compare_spinzero.x

Eff.x: Makefile Eff.o 
	$(CC)  -fsigned-char -Wstrict-prototypes -Wimplicit  -Wmissing-prototypes -Wunused \
	-o Eff.x $(CFLAGS) Eff.o -L$(ROOTSYS)/lib/root $(shell root-config --glibs) 
	touch Eff.x

Read_bkg.x: Makefile Read_bkg.o 
	$(CC)  -fsigned-char -Wstrict-prototypes -Wimplicit  -Wmissing-prototypes -Wunused \
	-o Read_bkg.x $(CFLAGS) Read_bkg.o -L$(ROOTSYS)/lib/root $(shell root-config --glibs) 
	touch Read_bkg.x

plot_bkg.x: Makefile plot_bkg.o 
	$(CC)  -fsigned-char -Wstrict-prototypes -Wimplicit  -Wmissing-prototypes -Wunused \
	-o plot_bkg.x $(CFLAGS) plot_bkg.o -L$(ROOTSYS)/lib/root $(shell root-config --glibs) 
	touch plot_bkg.x

Measure_SB.x: Measure_SB.o 
	$(CC)  -fsigned-char -Wstrict-prototypes -Wimplicit  -Wmissing-prototypes -Wunused \
	-o Measure_SB.x $(CFLAGS) Measure_SB.o -L$(ROOTSYS)/lib/root $(shell root-config --glibs) 
	touch Measure_SB.x

# clean
clean: 
	rm *.o *.x
