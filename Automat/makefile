#
#		Targets zum Bauen des Tests
#

# Linken der Object-files, abhaengig von AutomatTarget und TestAutomatTarget
# flag:
# -g --> debug Informationen erzeugen
# -o --> name des output-files

makeTestAutomat : AutomatTarget TestAutomatTarget SyntaxTarget StackTarget
	g++ -g objs/Automat.o objs/Syntax.o objs/Stack.o debug/TestAutomat.o -o debug/AutomatTest

# PositionTarget SyntaxTarget StackTarget	
# objs/Position.o objs/Syntax.o objs/Stack.o
	 	

# compilieren des Files Automat.cpp zu Automat.o, 
# das Objekt-File ist abhängig von src/Automat.cpp und src/Automat.h
# flag:
# -c --> nur compilieren
# -g --> debug Informationen erzeugen
# -Wall --> alle meldungen erzeugen (Warning all)

AutomatTarget:  src/Automat.cpp includes/Automat.h
	g++ -g  -c -Wall src/Automat.cpp -o objs/Automat.o 

SyntaxTarget: src/Syntax.cpp includes/Syntax.h
	g++ -g  -c -Wall src/Syntax.cpp -o objs/Syntax.o

StackTarget: src/Stack.cpp includes/Stack.h
	g++ -g  -c -Wall src/Stack.cpp -o objs/Stack.o


# TestAutomat.o ist abhängig von src/TestAutomat.cpp und src/Automat.h
TestAutomatTarget :  src/TestAutomat.cpp includes/Automat.h
	g++ -g  -c -Wall src/TestAutomat.cpp  -o debug/TestAutomat.o  



# loeschen aller files im verzeichnis obj und debug, dann neu erzeugen

cleanAutomat:
	rm -f objs/*.o
	rm -f debug/*
	$(MAKE) makeTestAutomat
	
	
# dieses Target wird vom makefile des Gesamtprojekts verwendet
# objs fuer Gesamtprojekt loeschen und dann neu erzeugen
#AutomatOBJTarget:
	$(MAKE) AutomatTarget

