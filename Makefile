all: 
	 g++ -std=c++11 -pthread  Task.cpp Calc.cpp MajorThread.cpp OtherThread.cpp -o task

clean:
	rm *o task



