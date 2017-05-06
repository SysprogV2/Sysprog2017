# Definition der Variablen
HEADERDIR = includes
SRCDIR = src
OBJDIR = objs
BINDIRTEST = debug
GPP_ARGS = 

dirs:
	mkdir -p $(SRCDIR)
	mkdir -p $(OBJDIR)
	mkdir -p $(BINDIRTEST)
	mkdir -p $(HEADERDIR)

# Linken der Object-files, abhaengig von AutomatTarget und TestAutomatTarget
makeTestAutomat : AutomatTarget TestAutomatTarget
	g++ $(GPP_ARGS) -g $(OBJDIR)/Syntax.o $(OBJDIR)/Stack.o $(OBJDIR)/Automat.o $(BINDIRTEST)/TestAutomat.o -o $(BINDIRTEST)/AutomatTest
	 	

# compilieren des Files Automat.cpp zu Automat.o, 
# das Objekt-File ist abhängig von src/Automat.cpp und src/Automat.h
AutomatTarget: src/Automat.cpp includes/Automat.h
	g++ $(GPP_ARGS) -g  -c -Wall $(SRCDIR)/Automat.cpp     -o $(OBJDIR)/Automat.o 
	g++ $(GPP_ARGS) -g  -c -Wall $(SRCDIR)/Syntax.cpp      -o $(OBJDIR)/Syntax.o
	g++ $(GPP_ARGS) -g  -c -Wall $(SRCDIR)/Stack.cpp       -o $(OBJDIR)/Stack.o
	
# TestAutomat.o ist abhängig von src/TestAutomat.cpp und src/Automat.h
TestAutomatTarget : dirs  $(SRCDIR)/TestAutomat.cpp    $(HEADERDIR)/Automat.h
	g++ $(GPP_ARGS) -g  -c -Wall $(SRCDIR)/TestAutomat.cpp -o $(BINDIRTEST)/TestAutomat.o  

# loeschen aller files im verzeichnis obj und debug, dann neu erzeugen
cleanAutomat: 
	rm -f $(OBJDIR)/*.o
	rm -f $(BINDIRTEST)/*
	$(MAKE) makeTestAutomat

# dieses Target wird vom makefile des Gesamtprojekts verwendet
# objs fuer Gesamtprojekt loeschen und dann neu erzeugen
AutomatOBJTarget:  
	$(MAKE) AutomatTarget

