
TARGET := calcul
OBJECTS :=  calcul.tab.o lex.yy.o


$(TARGET): $(OBJECTS)
	gcc -o $@ $(OBJECTS)

calcul.tab.c calcul.tab.h: calcul.y
		bison -vd $^

lex.yy.c: calcul.l
		flex $^

%.o: %.c
	gcc -c  $^


clean:
	rm -rf *.o calcul.tab.* lex.yy.c *.output calcul
