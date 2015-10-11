CXX = gcc
Target = driver.c

$(Target) : compile
	gcc -L/usr/local/opt/flex/lib -lfl *.o

compile: link
	gcc -c *.c

link:
	flex ../Tools/tiger.lex
	mv lex.yy.c lex.yy.c.old
	cp ../Tools/lex.yy.c .
flex:
	brew install -y flex

clean:
	rm -rf *.o a.out
