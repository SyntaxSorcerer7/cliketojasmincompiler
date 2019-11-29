// codeoptimizer.cpp
#include "global.hpp"
bool bringNodeLevelUpIfValue(TreeNode* &current, int val);
TreeNode* traverseAndOptimize(TreeNode* current);

bool calculateConstValues(TreeNode* &current, int type);

TreeNode* optimizeSyntaxTree(TreeNode* root){
    return traverseAndOptimize(root);
}

TreeNode* traverseAndOptimize(TreeNode* current){
    if(current==nullptr){
        return nullptr;
    }
    switch (current->type)
    {
    case MINUS:
    case PLUS: {
        current->args[0] = traverseAndOptimize(current->args[0]);
        current->args[1] = traverseAndOptimize(current->args[1]);
        if(!bringNodeLevelUpIfValue(current, 0)){
            calculateConstValues(current, current->type);
        }
    } 
    break;
    case DIVISION:
    case STAR: {
        current->args[0] = traverseAndOptimize(current->args[0]);
        current->args[1] = traverseAndOptimize(current->args[1]);
        if(!bringNodeLevelUpIfValue(current, 1)){
            calculateConstValues(current, current->type);
        }
    }
    break;
    case SMALLER:
    case BIGGER: {
        current->args[0] = traverseAndOptimize(current->args[0]);
        current->args[1] = traverseAndOptimize(current->args[1]);
        calculateConstValues(current, current->type);
    }
    break;
    case IF: {
        current->args[0] = traverseAndOptimize(current->args[0]);
        current->args[1] = traverseAndOptimize(current->args[1]);
        current->args[2] = traverseAndOptimize(current->args[2]);
        if(current->args[0]->type == NUMBER){
            if(current->args[0]->leaf_value){
                current= current->args[1];
            } else {
                current= current->args[2];
            }            
        }
    } 
    break;
    default: {
        for(int i =0; i<MAX_ARGS; i++){
            current->args[i] = traverseAndOptimize(current->args[i]);
        }
    }
        
    }
    return current;
}

bool bringNodeLevelUpIfValue(TreeNode* &current, int val){
    if(current->args[0]->type==NUMBER&&current->args[0]->leaf_value==val){
        current = (current->args[1]);
        return true;
    } else if(current->args[1]->type==NUMBER&&current->args[1]->leaf_value==val){
        current = (current->args[0]);
        return true;
    }
    return false;
}

bool calculateConstValues(TreeNode* &current, int type){
    if(current->args[0]->type==NUMBER && current->args[0]->type==NUMBER){
            //recycle tree node
            switch (type)
            {
            case PLUS:{
                current->args[0]->leaf_value = current->args[0]->leaf_value + current->args[1]->leaf_value;  
                current = current->args[0]; } break;
            
            case MINUS:{
                current->args[0]->leaf_value = current->args[0]->leaf_value - current->args[1]->leaf_value;  
                current = current->args[0]; } break;
            
            case STAR:{
                current->args[0]->leaf_value = current->args[0]->leaf_value * current->args[1]->leaf_value;  
                current = current->args[0]; } break;
            
            case DIVISION:{
                current->args[0]->leaf_value = current->args[0]->leaf_value / current->args[1]->leaf_value;  
                current = current->args[0]; } break;
            
            case BIGGER:{
                current->args[0]->leaf_value = current->args[0]->leaf_value > current->args[1]->leaf_value;  
                current = current->args[0]; } break;

            case SMALLER:{
                current->args[0]->leaf_value = current->args[0]->leaf_value < current->args[1]->leaf_value;  
                current = current->args[0]; } break;
            }
        return true;
    }
    return false;
}