ecosystem.exe: main.o ecosystem.o animals.o plants.o
	g++ -o ecosystem.exe main.o ecosystem.o animals.o plants.o

main.o: main.cpp ecosystem.h
	g++ -c main.cpp

ecosystem.o: ecosystem.cpp ecosystem.h
	g++ -c ecosystem.cpp

animals.o: animals.cpp animals.h
	g++ -c animals.cpp

plants.o: plants.cpp plants.h
	g++ -c plants.cpp

clean:
	rm ecosystem.exe main.o ecosystem.o animals.o plants.o
