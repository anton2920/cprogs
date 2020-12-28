#ifndef LAB_DEV_LIBS_H
#define LAB_DEV_LIBS_H

#include <STL/STL_String.h>
#include <STL/STL_List.h>

/* Structures' declarations */
struct tree;

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

typedef union value {
    int ival;
    double dval;
} value_t;

typedef struct identifier {
    STL_String name;
    const char *type;
    lang_type_t etype;

    value_t val;
} identifier_t;

typedef struct lexema {
    unsigned int id;
    identifier_t value;
} lexema_t;

enum {
    N = 100,
    MAP_SIZE = 1024
};

/* Functions' declarations */
void remove_whitespaces(char *str);
void getLexToken(char *str, identifier_t *token);
int is_roman(STL_String *str);
void insert_whitespaces(STL_String *dest, const char *src);
size_t get_parse_token(const char *str, char **tok);
void line_list_to_tree(struct tree *tree, STL_List *line_list);

#endif
