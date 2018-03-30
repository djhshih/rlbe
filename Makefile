all:  demo

check: test.cpp
	g++ -o test test.cpp
	./test

demo: demo.cpp
	g++ -o demo demo.cpp

clean:
	rm -rf demo test

