/* lexer.c */

#include "global.hpp"

char lexeme[MAX_ID_LENGTH + 1];
int  lineno = 1;

int lexan()  /*  lexical analyzer  */
{
    int c;
    while(1) {
        c = getchar();
        if (c == ' ' || c == '\t'){
              /*  strip out white space  */
            continue;
        }
        else if (c == '\n'){
            lineno = lineno + 1;
            continue;

        }
        else if (isdigit(c)) {  /*  c is a digit  */
            ungetc(c, stdin);
            scanf("%d", &yylval.i);
            return NUMBER;
        }
	    else if (c == ';')
		return SEMICOLON;
	    else if (c == ':')
		return DOUBLEPOINT;
	    else if (c == '?')
		return CONDITIONAL;
	    else if (c == '>')
		return BIGGER;
	    else if (c == '<')
		return SMALLER;
	    else if (c == '&')
		return BITAND;
	    else if (c == '|')
		return BITOR;
	    else if (c == '=')
	    	return EQUAL;
	    else if (c == '+')
	    	return PLUS;
	    else if (c == '-')
	    	return MINUS;
	    else if (c == '*')
	    	return STAR;
	    else if (c == '(')
	    	return LPAREN;
	    else if (c == ')')
	    	return RPAREN;
	    else if (c == '/')
	        return DIVISION;
        else if (c == '%')
            	return MOD;
        else if (c == '{')
            	return LCURLY;
        else if (c == '}')
            	return RCURLY;
	    else if (isalpha(c)) {  /*  c is a letter */
            int id_number, chars = 0;
            while (isalnum(c)) {  /* c is alphanumeric  */
                lexeme[chars++] = c; 
                if (chars > MAX_ID_LENGTH)
                    error("identifier too long");
                c = getchar();
            }
            lexeme[chars] = EOS;
            if (c != EOF)
                ungetc(c, stdin);
            if(strcmp("while", lexeme)==0){
                return WHILE;
            } else if(strcmp("if", lexeme)==0){
                return IF;
            } else if(strcmp("else", lexeme)==0){
                return ELSE;
            } else if(strcmp("print", lexeme)==0){
                return PRINT;
            } else if(strcmp("read", lexeme)==0){
                return READ;
            } else if(strcmp("END", lexeme)==0){
                return DONE;
            }
            id_number = lookup(lexeme);
            if (id_number == -1)
                id_number = insert(lexeme, ID);
            yylval.i = id_number;
            return symtable[id_number].token_type;
        }
        else if (c == EOF)
            return DONE;
        else {
            //yylval = NONE;
            return c;
        }
    }
}
