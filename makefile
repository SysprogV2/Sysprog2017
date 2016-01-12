#
#	baut das komplette Scanner Projekt
#
DEBUGDIR = debug
OBJDIR = objs
AUTOMATDIR = Automat
BUFFERDIR = Buffer
SYMBOLTABLEDIR = Symboltable
SCANNERDIR = Scanner

all:	automatOBJs bufferOBJs symboltableOBJs scanner  
	@echo "target all"

# rm 	remove
# -f	force, ohne nachfragen
clean:
	rm -f $(AUTOMATDIR)/$(OBJDIR)/*.o
	rm -f $(BUFFERDIR)/$(OBJDIR)/*.o
	rm -f $(SYMBOLTABLEDIR)/$(OBJDIR)/*.o
	rm -f $(SCANNERDIR)/$(OBJDIR)/*.o
	rm -f $(AUTOMATDIR)/$(DEBUGDIR)/*
	rm -f $(BUFFERDIR)/$(DEBUGDIR)/*
	rm -f $(SYMBOLTABLEDIR)/$(DEBUGDIR)/*
	rm -f $(SCANNERDIR)/$(DEBUGDIR)/*
	

automatOBJs:
	$(MAKE) -C $(AUTOMATDIR) AutomatOBJTarget
	
	
bufferOBJs:
	$(MAKE) -C $(BUFFERDIR) BufferOBJTarget

	
symboltableOBJs:
	$(MAKE) -C $(SYMBOLTABLEDIR) SymboltableOBJTarget
	

scanner: 
	$(MAKE) -C $(SCANNERDIR) makeTestScanner

	