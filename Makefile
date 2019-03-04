 PA9 : 
#	g++ main.cpp Stem_Exceptions.cpp Driver.cpp Parse_File.cpp Stem.cpp -I. -o PA7

CC = g++ 
CFLAGS = -std=c++11 -Wall -O3 -c 
LFLAGS = -std=c++11 -Wall 
OBJS = main.o Stem_Exceptions.o Parse_File.o Driver.o Stem.o
INCLUDE = -I.

PA9 : $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) $(INCLUDE) -o PA9
	

main.o : main.cpp Driver.cpp Driver.h
	$(CC) main.cpp $(INCLUDE) $(CFLAGS)
	
Stem_Exceptions.o : Stem_Exceptions.cpp Stem_Exceptions.h
	$(CC) Stem_Exceptions.cpp $(INCLUDE) $(CFLAGS)

Driver.o : Driver.cpp Driver.h Stem_Exceptions.cpp Stem_Exceptions.h Parse_File.cpp Parse_File.h
	$(CC) Driver.cpp $(INCLUDE) $(CFLAGS)
	
Parse_File.o : Parse_File.cpp Parse_File.h Stem.cpp Stem.h
	$(CC) Parse_File.cpp $(INCLUDE) $(CFLAGS)
	
Stem.o : Stem.cpp Stem.h
	$(CC) Stem.cpp $(INCLUDE) $(CFLAGS)

	
clean : 
	-rm *.o PA9
  
