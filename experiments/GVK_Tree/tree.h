/* Header inclusion */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* New data types */
typedef struct _node {
	int key;
	struct _node *s_left;
	struct _node *s_right;
} node;

typedef node sheet;