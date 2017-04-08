#
#	baut das komplette Scanner Projekt
#
DEBUGDIR = debug
OBJDIR = objs
AUTOMATDIR = Automat
BUFFERDIR = Buffer
SYMBOLTABLEDIR = Symboltable
SCANNERDIR = Scanner
PARSERDIR = Parser

all: makedirs automatOBJs bufferOBJs symboltableOBJs scanner parserOBJs
	@echo "target all"

# rm 	remove
# -f	force, ohne nachfragen
clean:
	rm -f $(AUTOMATDIR)/$(OBJDIR)/*.o
	rm -f $(BUFFERDIR)/$(OBJDIR)/*.o
	rm -f $(SYMBOLTABLEDIR)/$(OBJDIR)/*.o
	rm -f $(SCANNERDIR)/$(OBJDIR)/*.o
	rm -f $(PARSERDIR)/$(OBJDIR)/*.o
	rm -f $(AUTOMATDIR)/$(DEBUGDIR)/*
	rm -f $(BUFFERDIR)/$(DEBUGDIR)/*
	rm -f $(SYMBOLTABLEDIR)/$(DEBUGDIR)/*
	rm -f $(SCANNERDIR)/$(DEBUGDIR)/*
	rm -f $(PARSERDIR)/$(DEBUGDIR)/*
	
makedirs:
	mkdir -p $(BUFFERDIR)/$(OBJDIR)
	mkdir -p $(BUFFERDIR)/$(DEBUGDIR)
	mkdir -p $(AUTOMATDIR)/$(OBJDIR)
	mkdir -p $(AUTOMATDIR)/$(DEBUGDIR)
	mkdir -p $(SYMBOLTABLEDIR)/$(OBJDIR)
	mkdir -p $(SYMBOLTABLEDIR)/$(DEBUGDIR)
	mkdir -p $(SCANNERDIR)/$(OBJDIR)
	mkdir -p $(SCANNERDIR)/$(DEBUGDIR)
	
automatOBJs:
	$(MAKE) -C $(AUTOMATDIR) AutomatOBJTarget
	
	
bufferOBJs:
	$(MAKE) -C $(BUFFERDIR) BufferOBJTarget

	
symboltableOBJs:
	$(MAKE) -C $(SYMBOLTABLEDIR) SymboltableOBJTarget
	

scanner: 
	$(MAKE) -C $(SCANNERDIR) makeTestScanner

parserOBJs:
	$(MAKE) -C $(PARSERDIR) makeTestParser
	
