
testapp:	testapp.o poset.o
	g++ -o testapp testapp.o poset.o

reduce:	reduce.o poset.o
	g++ -o reduce reduce.o poset.o

testapp.o:	poset.h testapp.cpp
	g++ -c testapp.cpp

reduce.o:	poset.h reduce.cpp
	g++ -c reduce.cpp

poset.o:	poset.h poset.cpp
	g++ -c poset.cpp

