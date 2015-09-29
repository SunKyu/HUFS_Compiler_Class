CXX=gcc

TARGET=driver

$(TARGET): object
	$(CXX) *.o

object:
	$(CXX) -c *.c

queen: $(TARGET)
	./a.out ../queens.tig

merge: $(TARGET)
	./a.out ../merge.tig

test: $(TARGET)
	./a.out ../test.tig

clean :
	rm -f *.o a.out
