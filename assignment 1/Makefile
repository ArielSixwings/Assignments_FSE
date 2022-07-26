main: main.o semaphore.o trafficIntersection.o eventHandler.o
	g++ main.o semaphore.o trafficIntersection.o eventHandler.o -o main

main.o: main.cpp
	g++ -c main.cpp

semaphore.o: semaphore.cpp semaphore.h
	g++ -c semaphore.cpp

trafficIntersection.o: trafficIntersection.cpp trafficIntersection.h
	g++ -c trafficIntersection.cpp

eventHandler.o: eventHandler.cpp eventHandler.h
	g++ -c eventHandler.cpp

clean:
	rm *.o main