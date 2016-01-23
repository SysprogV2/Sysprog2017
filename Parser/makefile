# Definition der Variablen
HEADERDIR = includes
SRCDIR = src
OBJDIR = objs
BINDIRTEST = debug
AUTOMATDIR = ../Automat
BUFFERDIR = ../Buffer
SYMBOLTABLEDIR = ../Symboltable
SCANNERDIR = ../Scanner
# hier alle Object Files eintragen, ausser das File mit der Mainmethode
# darauf achten, dass letzte Zeile ohne "\" eingetragen wird

OBJS = $(OBJDIR)/Parser.o \
	$(OBJDIR)/ParseTree.o \
	$(OBJDIR)/TokenSequence.o

# linken der Object-files 
makeTestParser: $(OBJS) ParserTest

$(OBJDIR)/%.o :  $(SRCDIR)/%.cpp $(HEADERDIR)/%.h
	@echo "g++ $*.cpp"
	g++ -g  -c -Wall  -o $@  $<

ParserTest: $(SRCDIR)/TestParser.cpp $(HEADERDIR)/Parser.h
	g++ -g  -c -Wall $(SRCDIR)/TestParser.cpp -o $(BINDIRTEST)/TestParser.o
	g++ -g $(BINDIRTEST)/TestParser.o $(OBJDIR)/*.o $(AUTOMATDIR)/$(OBJDIR)/*.o $(BUFFERDIR)/$(OBJDIR)/*.o $(SYMBOLTABLEDIR)/$(OBJDIR)/*.o $(SCANNERDIR)/$(OBJDIR)/*.o -o $(BINDIRTEST)/ParserTest  

# loeschen aller files im verzeichnis $(OBJDIR) und $(BINDIRTEST) und neu erstellen
cleanScanner:
	rm -rf $(OBJDIR)/*.o
	rm -rf $(BINDIRTEST)/*
	$(MAKE) makeTestParser
