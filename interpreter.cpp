#include "global.hpp"

int interpreteST(TreeNode* node){
    if(node==nullptr){
        return -1;
    }
    switch(node->type){
        case NUMBER: {
            return node->leaf_value;
        }
        case ID:{
            return symtable[node->leaf_value].variable_value;
        }
        case PLUS: {
            return interpreteST(node->args[0]) + interpreteST(node->args[1]);
        }
        case MINUS: {
            return interpreteST(node->args[0]) - interpreteST(node->args[1]);
        }
        case STAR: {
            return interpreteST(node->args[0]) * interpreteST(node->args[1]);
        }
        case DIVISION: {
            return interpreteST(node->args[0]) / interpreteST(node->args[1]);
        }
        case MOD: {
            return interpreteST(node->args[0]) % interpreteST(node->args[1]);
        }
        case BIGGER: {
            return interpreteST(node->args[0]) > interpreteST(node->args[1]);
        }
        case SMALLER: {
            return interpreteST(node->args[0]) < interpreteST(node->args[1]);
        }
        case BITAND: {
            return interpreteST(node->args[0]) & interpreteST(node->args[1]);
        }
        case BITOR: {
            return interpreteST(node->args[0]) | interpreteST(node->args[1]);
        }
        case CONDITIONAL: {
            if(interpreteST(node->args[0])){
                return interpreteST(node->args[1]);
            } else {
                return interpreteST(node->args[2]);
            }
        }
        case EQUAL:{
            int symbolTablePos = node->args[0]->leaf_value;
            symtable[symbolTablePos].variable_value = interpreteST(node->args[1]); 
            break;
        }
        case PRINT:{
            printf("%d \n", interpreteST(node->args[0]));
            break;
        }
        case READ: {
            int val = -1;
            printf("input please: ");
            scanf("%d", &val);
            int symbolTablePos = node->args[0]->leaf_value;
            symtable[symbolTablePos].variable_value = val;
        }
        case SEMICOLON: {
            interpreteST(node->args[0]);
            interpreteST(node->args[1]);
            break;
        }
        case IF: {
            if(interpreteST(node->args[0])){
                interpreteST(node->args[1]);
            } else {
                interpreteST(node->args[2]);
            }
            break;
        }
        case WHILE: {
            while(interpreteST(node->args[0])){
                interpreteST(node->args[1]);
            }
        }

    }
    return -1;

}