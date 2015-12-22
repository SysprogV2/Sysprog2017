# Definition der Variablen
HEADERDIR = includes
SRCDIR = src
OBJDIR = objs
BINDIRTEST = debug

# Linken der Object-files, abhaengig von BufferTarget und TestBufferTarget
makeTestBuffer: BufferTarget 	TestBufferTarget
	g++ -g $(OBJDIR)/Buffer.o 	$(BINDIRTEST)/TestBuffer.o  -o $(BINDIRTEST)/BufferTest
	

# compilieren der Source-files
# Buffer.o ist abhaengig von Buffer.cpp und Buffer.h
BufferTarget :  $(SRCDIR)/Buffer.cpp $(HEADERDIR)/Buffer.h 
	g++ -g  -c -Wall  $(SRCDIR)/Buffer.cpp -o $(OBJDIR)/Buffer.o



#TestBuffer.o ist abhaengig von TestBuffer.cpp und Buffer.h
TestBufferTarget :  $(SRCDIR)/TestBuffer.cpp $(HEADERDIR)/Buffer.h
	g++ -g  -c -Wall $(SRCDIR)/TestBuffer.cpp -o $(BINDIRTEST)/TestBuffer.o

# loeschen aller files im verzeichnis $(OBJDIR) und $(BINDIRTEST) und neu compilieren
cleanBuffer:
	rm -f $(OBJDIR)/*.o
	rm -f $(BINDIRTEST)/*
	$(MAKE) makeTestBuffer
	
# dieses Target wird vom makefile des Gesamtprojekts verwendet
# objs fuer GesamtProjekt loeschen und dann neu erzeugen
BufferOBJTarget:
	$(MAKE) BufferTarget

	