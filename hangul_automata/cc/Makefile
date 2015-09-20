CXX=g++


target=automata

$(target): $(target).o 
	$(CXX) $(target).o

$(target).o:
	$(CXX) -c $(target).cpp

clean:
	rm -rf ./a.out*
	rm -f *.o
