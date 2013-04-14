#ifndef _DMT_SORT_
#define _DMT_SORT_

#include <stdio.h>

#define ST(x,y) ((x)<(y))
#define SE(x,y) ((x)<=(y))
#define LE(x,y) ((x)>=(y))
#define LT(x,y) ((x)>(y))
#define EQ(x,y) ((x)==(y))

typedef struct elem_t elem_t;

struct elem_t{
	int value;
	void *p;
};

extern int quik_sort(elem_t *data, int s, int f);


#endif
