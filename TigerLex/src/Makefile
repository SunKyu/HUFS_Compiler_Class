CXX = gcc
Target = driver.c

$(Target) : link
	gcc -L/usr/local/opt/flex/lib -lfl *.o

link:
	gcc -c *.c

clean:
	rm -rf *.o a.out
