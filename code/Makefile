ODIR = ./build
EDIR = ./bin
TDIR = ./tests

input:
	make -f makefile.input

output:
	make -f makefile.output

.PHONY: cleanBuild

cleanBuild:
	rm -f $(ODIR)/*.o $(EDIR)/*

.PHONY: cleanOutput

cleanOutput:
	rm -f $(TDIR)/*.subgraphs $(TDIR)/*.satinput $(TDIR)/*.satoutput