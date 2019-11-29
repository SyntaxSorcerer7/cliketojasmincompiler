//codegenerator.cpp
#include "global.hpp"

//we should calculate the exact stack height and number of variables 
std::string prefixCode = ".class public App\n.super java/lang/Object\n.method public static main([Ljava/lang/String;)V\n";
const std::string postfixCode = "return\n.end method";
const std::string printPrefixCode = "getstatic java/lang/System/out Ljava/io/PrintStream;\n";
const std::string printPostCode = "invokevirtual java/io/PrintStream/println(I)V\n";
std::string jasminCode = "";
int labelCount = 0;
int stackSize = 1;
int maxStackSize =1;

void traverseSyntaxTree(TreeNode *node);



void addCode(std::string instruction){
    jasminCode = (jasminCode + instruction + "\n");

}

std::string createUniqueLabel()
{
    labelCount++;
    return "label" + std::to_string(labelCount);
}

void updateStackSize(int delta = 1){
    stackSize = stackSize + delta;
    if(stackSize>maxStackSize){
        maxStackSize = stackSize;
    }
}

std::string getCompleteCode(std::string instructions){
    return prefixCode 
    + ".limit stack " + std::to_string(maxStackSize) + "\n"
    + ".limit locals " + std::to_string(getNumberOfVariables()) + "\n" 
    + jasminCode + postfixCode;
}

std::string generateJasminCode(TreeNode *node){
    stackSize=1;
    labelCount=0;
    maxStackSize=1;
    jasminCode="";
    traverseSyntaxTree(node);
    return getCompleteCode(jasminCode);
}

void printJasminCode(){
    printf(getCompleteCode(jasminCode).c_str());
}

std::string createBranchStatement(TreeNode* expressionNode, std::string labelJumpFlase){
    std::string fBranchLabel = createUniqueLabel();
            traverseSyntaxTree(expressionNode->args[0]);
            traverseSyntaxTree(expressionNode->args[1]);
            if(expressionNode->type==BIGGER){
                //jump to false branch if this is lower
                return "if_icmplt " + labelJumpFlase;
            } else if(expressionNode->type==SMALLER){
                //jump to false branch if this is bigger
                return "if_icmpgt " + labelJumpFlase;
            }
    throw std::exception();
}

void traverseSyntaxTree(TreeNode *node){
if(node==nullptr){
        return;;
    }
    switch(node->type){
        case NUMBER: {
            updateStackSize();
            std::string instr = "sipush " + std::to_string(node->leaf_value);
            addCode(instr);
            break;
        }
        case ID:{
                updateStackSize();
                const std::string instr = "iload " + std::to_string(node->leaf_value);
                addCode(instr);
                break;
        }
        case PLUS: {
            traverseSyntaxTree(node->args[0]);
            traverseSyntaxTree(node->args[1]);
            const std::string instr = "iadd";
            addCode(instr);
            updateStackSize(-1);
            break;
        }
        case MINUS: {
            traverseSyntaxTree(node->args[0]);
            traverseSyntaxTree(node->args[1]);
            const std::string instr = "isub";
            addCode(instr);
            updateStackSize(-1);
            break;
        }
        case STAR: {
            traverseSyntaxTree(node->args[0]);
            traverseSyntaxTree(node->args[1]);
            const std::string instr = "imul";
            addCode(instr);
            updateStackSize(-1);
            break;
        }
        case DIVISION: {
            traverseSyntaxTree(node->args[0]);
            traverseSyntaxTree(node->args[1]);
            const std::string instr = "idiv";
            addCode(instr);
            updateStackSize(-1);
            break;
        }
        case MOD: {
            traverseSyntaxTree(node->args[0]);
            traverseSyntaxTree(node->args[1]);
            const std::string instr = "irem";
            addCode(instr);
            updateStackSize(-1);
            break;
        }
        case BITAND: {
            traverseSyntaxTree(node->args[0]);
            traverseSyntaxTree(node->args[1]);
            const std::string instr = "iand";
            addCode(instr);
            updateStackSize(-1);
            break;
        }
        case BITOR: {
            traverseSyntaxTree(node->args[0]);
            traverseSyntaxTree(node->args[1]);
            const std::string instr = "ior";
            addCode(instr);
            updateStackSize(-1);
            break;
        }       
        case IF: {  
            std::string fBranchLabel = createUniqueLabel();
            std::string tBranchLabel = createUniqueLabel();
            addCode(createBranchStatement(node->args[0], fBranchLabel));
            updateStackSize(-1);
            //push code for true branch
            traverseSyntaxTree(node->args[1]);
            addCode("goto " + tBranchLabel);
            //label for false branch
            addCode(fBranchLabel+":");
            //push code for false branch 
            traverseSyntaxTree(node->args[2]);
            addCode(tBranchLabel+":");
            break;
        }
        case WHILE: {
            std::string labelBeginLoop = createUniqueLabel();
            std::string labelEndLoop = createUniqueLabel();
            addCode(labelBeginLoop+":");
            //evaluate condition
            addCode(createBranchStatement(node->args[0], labelEndLoop));
            updateStackSize(-1);
            //execute code in loop body
            traverseSyntaxTree(node->args[1]);
            //jump back to beginning of loop
            addCode("goto "+labelBeginLoop);
            //create label for jumping out of loop
            addCode(labelEndLoop+":");
            break;

        }
        case EQUAL:{
            int symbolTablePos = node->args[0]->leaf_value;
            traverseSyntaxTree(node->args[1]);
            const std::string instr = std::string("istore ").append(std::to_string(symbolTablePos));
            addCode(instr);
            updateStackSize(-1);
            //Instruction ass(assign);
            //sm->append(ass);
            break;
        }
        case SEMICOLON: {
            traverseSyntaxTree(node->args[0]);
            traverseSyntaxTree(node->args[1]);
            break;
        }
        case CONDITIONAL: {
            std::string fLabel = createUniqueLabel();
            std::string tLabel = createUniqueLabel();

            //expression
            addCode(createBranchStatement(node->args[0], fLabel));
            updateStackSize(-1);
            //jump to false branch if value on stack is false
            //Instruction bf(gofalse, labelNumber);
            //sm->append(bf);
            //push code for true branch
            traverseSyntaxTree(node->args[1]);
            addCode("goto " + tLabel);
            //label for false branch
            addCode(fLabel+":");
            //Instruction labelfalse(label, labelNumber);
            //sm->append(labelfalse);
            //push code for false branch 
            traverseSyntaxTree(node->args[2]);
            addCode(tLabel+":");
            break;
        }
        case PRINT:{
            addCode(printPrefixCode);
            traverseSyntaxTree(node->args[0]);
            addCode(printPostCode);        
            updateStackSize(-1);    
            break;
        }
    }
}

