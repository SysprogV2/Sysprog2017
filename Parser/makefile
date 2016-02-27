# Definition der Variablen
HEADERDIR = includes
SRCDIR = src
OBJDIR = objs
BINDIRTEST = debug
AUTOMATDIR = ../Automat
BUFFERDIR = ../Buffer
SYMBOLTABLEDIR = ../Symboltable
SCANNERDIR = ../Scanner
CPPVERSION = c++11
# hier alle Object Files eintragen, ausser das File mit der Mainmethode
# darauf achten, dass letzte Zeile ohne "\" eingetragen wird

OBJS = $(OBJDIR)/Parser.o \
	$(OBJDIR)/ParseTree.o \
	$(OBJDIR)/TokenSequence.o

# linken der Object-files 
makeTestParser: $(OBJS) ParserTest

$(OBJDIR)/%.o :  $(SRCDIR)/%.cpp $(HEADERDIR)/%.h
	@echo "g++ $*.cpp"
	g++ -std=$(CPPVERSION) -g -c -Wall  -o $@  $<

ParserTest: $(SRCDIR)/TestParser.cpp $(HEADERDIR)/Parser.h
	g++ -std=$(CPPVERSION) -g -c -Wall $(SRCDIR)/TestParser.cpp -o $(BINDIRTEST)/TestParser.o
	g++ -std=$(CPPVERSION) -g $(AUTOMATDIR)/$(OBJDIR)/*.o $(BUFFERDIR)/$(OBJDIR)/*.o $(SYMBOLTABLEDIR)/$(OBJDIR)/*.o $(SCANNERDIR)/$(OBJDIR)/*.o $(OBJDIR)/Parser.o $(OBJDIR)/ParseTree.o $(OBJDIR)/TokenSequence.o $(BINDIRTEST)/TestParser.o -o $(BINDIRTEST)/ParserTest  

# loeschen aller files im verzeichnis $(OBJDIR) und $(BINDIRTEST) und neu erstellen
cleanParser:
	rm -rf $(OBJDIR)/*.o
	rm -rf $(BINDIRTEST)/*
	$(MAKE) makeTestParser
