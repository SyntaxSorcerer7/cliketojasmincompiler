/* init.c */

#include "global.hpp"

struct symentry keywords[] = {
    { "div", DIVISION },
    { "mod", MOD, }
};

void init()  /*  loads keywords into symtable  */
{
    int nr_keywords = sizeof(keywords) / sizeof(keywords[0]);
    for (int i = 0; i < nr_keywords; ++i)
        insert(keywords[i].lexeme, keywords[i].token_type);
}
