#include <assert.h>

typedef char *string;
typedef char bool;

#define TRUE 1
#define FALSE 0

void *checked_malloc(int);
string String(char *);

#define BUFMAX 1000
extern char strbuf[];
extern int  bufptr;
extern void clearbuf();
extern void putbuf(char);
