output: main.o myvector.o contactbst.o contact.o
	g++ main.o myvector.o contactbst.o contact.o -o output
main.o: main.cpp
	g++ -c main.cpp
myvector.o: myvector.cpp myvector.h
	g++ -c myvector.cpp 
contactbst.o: contactbst.cpp contactbst.h
	g++ -c contactbst.cpp 
contact.o: contact.cpp contact.h
	g++ -c contact.cpp 