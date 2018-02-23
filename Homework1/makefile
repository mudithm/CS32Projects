meme: testMap.o Map.o
	g++ -std=c++11 -o meme testMap.o Map.o

testMap.o: testMap.cpp Map.h
	g++ -std=c++11 -c testMap.cpp

Map.o: Map.cpp Map.h
	g++ -std=c++11 -c Map.cpp


clean:
	rm *.o meme momo

momo: testnewMap.o newMap.o
	g++ -std=c++11 -o momo testnewMap.o newMap.o

testnewMap.o: testnewMap.cpp newMap.h
	g++ -std=c++11 -c testnewMap.cpp

newMap.o:
	g++ -std=c++11 -c newMap.cpp

