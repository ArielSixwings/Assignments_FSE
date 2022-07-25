main: main.o semaphore.o trafficIntersection.o
	g++ main.o semaphore.o trafficIntersection.o -o main

main.o: main.cpp
	g++ -c main.cpp

semaphore.o: semaphore.cpp semaphore.h
	g++ -c semaphore.cpp

trafficIntersection.o: trafficIntersection.cpp trafficIntersection.h
	g++ -c trafficIntersection.cpp

clean:
	rm *.o main