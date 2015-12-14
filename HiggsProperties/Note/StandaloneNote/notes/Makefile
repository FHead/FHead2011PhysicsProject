# $Id: Makefile,v 1.2 2012/11/15 13:08:54 chenyi Exp $

DVIPS = dvips
DVIPSPREFLAGS = -t letter
DVIPSPOSTFLAGS = -Ppdf

# TEXINPUTS := $(HOME)/latex/foiltex:$(HOME)/tex-archive/macros/latex/contrib/supported/feynmf:.:$(TEXINPUTS)
# MPINPUTS := $(HOME)/tex-archive/macros/latex/contrib/supported/feynmf:.:$(MPINPUTS)

# LATEX = env TEXINPUTS=$(TEXINPUTS) latex
LATEX = pdflatex
LATEXFLAGS =

DVI = $(TEXSOURCES:.tex=.dvi)

SOURCE = note.pdf 

ALLTEX = $(wildcard *.tex)
RERUN = '(No file .*\.toc|There were undefined references)'

.PHONY: all
all: $(SOURCE)

%.pdf: %.tex $(ALLTEX) 
	@echo "====> LaTeX first pass"
	$(LATEX) $(LATEXFLAGS) $(<:.tex=)
	@if egrep -q $(RERUN) $*.log ; then echo "====> LaTeX rerun" && $(LATEX) $<; fi
	@if egrep -q $(RERUN) $*.log ; then echo "====> LaTeX rerun" && $(LATEX) $<; fi

.PHONY: clean
clean:
	rm -f *.pdf *.aux *.dvi *.log *.qsl *.sol *.lof *.lot *.toc *~
