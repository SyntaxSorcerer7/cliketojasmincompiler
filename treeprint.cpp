/* treeprinter.cpp */

#include "global.hpp"
#include <iostream>

void printType(int type);
void printTree(std::string prefix, TreeNode* n, int pos);

void printSyntaxTree(TreeNode* n){
    printf("syntax tree: \n");
    printTree("", n, 3);
}

void printTree(std::string prefix, TreeNode* n, int pos)
{
    if( n != nullptr )
    {
        std::cout << prefix;

        if(pos == 3){
            printf("└──");    
        } else {
            printf("├──");
        }

        if(n->type == ID){
            printf("%s", symtable[n->leaf_value].lexeme);
        } else if (n->type == NUMBER) {
            printf("%d", n->leaf_value);
        } else {
            printType(n->type);
        }
        printf("\n");

        printTree( prefix + (pos!=3 ? "│   " : "    "), n->args[0], 1);
        printTree( prefix + (pos!=3 ? "│   " : "    "), n->args[1], 2);
        printTree( prefix + (pos!=3 ? "│   " : "    "), n->args[2], 3);
    }
}

void printType(int type){
    switch(type){
        case STAR:
            printf(" * ");
            break;
        case SEMICOLON:
            printf(" ; ");
            break;
        case DOUBLEPOINT:
            printf(" : ");
            break;
        case CONDITIONAL:
            printf(" ? ");
            break;
        case BIGGER:
            printf(" > ");
            break;
        case SMALLER:
            printf(" < ");
            break;
        case BITAND:
            printf(" & ");
            break;
        case BITOR:
            printf(" | ");
            break;
        case EQUAL:
            printf(" = ");
            break;
        case PLUS:
            printf(" + ");
            break;
        case MINUS:
            printf(" - ");
            break;
        case DIVISION:
            printf(" / ");
            break;
        case MOD:
            printf(" %% ");
            break;
        case IF:
            printf(" IF");
            break;
        case ELSE:
            printf("ELSE");
            break;
        case WHILE:
            printf("WHILE");
            break;
        case PRINT:
            printf("PRINT");
            break;
        case READ:
            printf("READ");
            break;
        
    }
}