#ifndef LAB_DEV_LIBS_H
#define LAB_DEV_LIBS_H

#include <STL/STL_String.h>

/* New types */
typedef enum language_types {
    IMMEDIATE_INTEGER,
    IMMEDIATE_DOUBLE,
    VARIABLE,
    ROMAN_NUMBER,
    CONDITIONAL_STATEMENT,
    COMPARISON_OPERATOR,
    ASSIGNMENT_OPERATOR
} lang_type_t;

typedef struct identifier {
    STL_String name;
    STL_String type;
    lang_type_t etype;
} identifier_t;

typedef struct lexema {
    unsigned int id;
    identifier_t value;
} lexema_t;

enum {
    N = 100,
    MAP_SIZE = 1024
};

#endif
