
TARGET := calcul
OBJECTS := calcul.o calcul.tab.o lex.yy.o


$(TARGET): $(OBJECTS)
	gcc -L/usr/local/opt/flex/lib -lfl -o $@ $(OBJECTS)

calcul.tab.c calcul.tab.h: calcul.y
		bison -vd $^

lex.yy.c: calcul.l
		flex $^

%.o: %.c
	gcc -c --std=c99 $^


clean:
	rm -rf *.o calcul.tab.* lex.yy.c
