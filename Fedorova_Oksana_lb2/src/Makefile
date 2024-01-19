LIBS=-lsfml-graphics -lsfml-window -lsfml-system
CXX:=g++
%.o:%.cpp
	$(CXX) -c $< -o $@ -I /home/motherlode/SFML/SFML-2.5.1/include
main: 
	g++ main.cpp -o main

tests: tests  
	g++ tests.cpp -o tests

clean: clean
	rm -f main tests sfml-app drower.o
drow: drow
	g++ -c drower.cpp
	g++ drower.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
	./sfml-app
