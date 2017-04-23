# Definition der Variablen
HEADERDIR = includes
SRCDIR = src
OBJDIR = objs
BINDIRTEST = debug
INFODIR = ../Scanner/objs
GPP_ARGS = -std=c++14

dirs:
	mkdir -p $(SRCDIR)
	mkdir -p $(OBJDIR)
	mkdir -p $(BINDIRTEST)
	mkdir -p $(HEADERDIR)

# Linken der Object-Files
makeTestSymboltable:  SymboltableTarget TestSymboltableTarget
	g++ $(GPP_ARGS) -g $(OBJDIR)/*.o $(BINDIRTEST)/TestSymboltable.o  $(INFODIR)/Information.o -o $(BINDIRTEST)/SymboltableTest

# compilieren 

SymboltableTarget:  src/Symboltable.cpp includes/Symboltable.h
	g++ $(GPP_ARGS) -g  -c src/Symboltable.cpp  -o $(OBJDIR)/Symboltable.o
	g++ $(GPP_ARGS) -g  -c src/StringTab.cpp  -o $(OBJDIR)/StringTab.o
	g++ $(GPP_ARGS) -g  -c src/SymtabEntry.cpp  -o $(OBJDIR)/SymtabEntry.o

# TestSymboltable.o ist abhängig von src/TestSymboltable.cpp und includes/Symboltable.h
TestSymboltableTarget:  $(SRCDIR)/TestSymboltable.cpp $(HEADERDIR)/Symboltable.h
	g++ $(GPP_ARGS) -g  -c -Wall $(SRCDIR)/TestSymboltable.cpp -o $(BINDIRTEST)/TestSymboltable.o  
	
# loeschen aller files im verzeichnis $(OBJDIR) und $(BINDIRTEST) und neu compilieren
cleanSymboltable: 
	rm -rf $(OBJDIR)/*.o
	rm -rf $(BINDIRTEST)/*
	$(MAKE) makeTestSymboltable
	
# dieses Target wird vom makefile des Gesamtprojekts verwendet
# objs fuer Gesamtprojekt loeschen und dann neu erzeugen
SymboltableOBJTarget: 
	$(MAKE) SymboltableTarget

	