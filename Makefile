all:	project

project:	main.o  Ecosystem.o Plants.o Animals.o
	g++ -std=c++11 -o project main.o  Ecosystem.o Plants.o Animals.o -lstdc++

main.o: main.cpp
	g++ -std=c++11 -c main.cpp	

Ecosystem.o: Ecosystem.cpp
	g++ -std=c++11 -c Ecosystem.cpp 

Plants.o: Plants.cpp
	g++ -std=c++11 -c Plants.cpp
 
Animals.o: Animals.cpp
	g++ -std=c++11 -c Animals.cpp 

clean:
	rm -f *.o project
