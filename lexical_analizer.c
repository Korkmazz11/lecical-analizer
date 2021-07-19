#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void main()
{
    FILE *ceng;
    ceng=fopen("code.Ceng.txt","r");

    FILE *lex;
    lex = fopen("code.lex.txt","w");

    int size;
    fseek(ceng,0,SEEK_END);
    size = ftell(ceng);
    fseek(ceng,0,SEEK_SET);

    char chr;
    chr = getc(ceng);

    while (chr != EOF){

        char keywords [] = "break,case,char,const,continue,do,else,enum,float,for,goto,if,int, long,record,return,static,while";
        char operators [] = "+,-,*,/,++,--,:=";

        int index = 0;
        char *puncts;
        puncts = (char*) calloc (2,sizeof(char));


        char *token;
        token = (char*) calloc (20,sizeof(char));//max size is 20 for keywords and identifiers

        while(isdigit(chr) || isalpha(chr)){ //for identifiers,keywords and integer constants

            //printf("%c",chr); to control reading from file
            token [index] = chr;
            index++;
            chr = getc(ceng);

        }
        if(isalpha(token[0])){

            char *ptr;
            ptr = strtok(keywords,",");

            while (ptr != NULL){//control loop if token is a keyword.

                    int isTheSame = strcmp(token,ptr);
                    if(isTheSame == 0){

                        fprintf(lex,"Keyword (%s)\n",token);
                        printf("Keyword (%s)\n",token);
                        break;
                    }
                    else{
                        ptr = strtok(NULL,",\000");
                    }
                    if(ptr == NULL && isTheSame != 0){
                            fprintf(lex,"Identifier (%s)\n",token);
                            printf("Identifier (%s)\n",token);
                            if(strlen(token) > 20){
                                fprintf(lex,"Error! Maximum identifier size is 20 characters.\n");
                                printf("Error! Maximum identifier size is 20 characters.\n");
                            }
                        }
                }


            }
            if(isdigit(token[0])){

                fprintf(lex,"IntConst(%s)\n",token);
                printf("IntConst(%s)\n",token);
                if(strlen(token) > 10){
                    fprintf(lex,"Error! Maximum integer size is 10 digits.\n");
                    printf("Size error! Maximum integer size is 10 digits.\n");
                }

            }

            free(token);


            if(isspace(chr)){
                chr = getc(ceng);
                continue;
            }

            if(ispunct(chr)){

                if(chr == 40){// ( in ASCII

                    chr = getc(ceng);
                    if (chr == 42){//* in ASCII
                        chr = getc(ceng);
                        while (chr != 42){
                            chr = getc(ceng);

                            if (chr == EOF){
                            fprintf(lex,"Unterminated Comment Error! A comment cannot terminate before the file end.\n");
                            printf("Unterminated Comment Error! A comment cannot terminate before the file end.\n");
                            break;
                            }
                        }
                        chr = getc(ceng);
                        if(chr == 41){//41 equals ) in ASCII
                            //fprintf(tokens,"it's a comment\n");
                            printf("it's a comment\n");//to control if it works
                            chr = getc(ceng);
                            continue;
                        }
                        else{
                            chr = getc(ceng);
                        }
                    }
                    else{
                        fprintf(lex,"LeftPar\n");
                        printf("LeftPar\n");
                        chr = getc(ceng);
                        continue;
                    }
                }
                else if (chr == 41){
                    fprintf(lex,"RightPar\n");
                    printf("RightPar\n");
                    chr = getc(ceng);
                    continue;
                }
                else if(chr == 91){//91 equals [ in ASCII
                    fprintf(lex,"LeftSquareBracket\n");
                    printf("LeftSquareBracket\n");
                    chr = getc(ceng);
                    continue;

                }
                else if(chr == 93){//93 equals ] in ASCII
                    fprintf(lex,"RightSquareBracket\n");
                    printf("RightSquareBracket\n");
                    chr = getc(ceng);
                    continue;
                }
                else if(chr == 123){//  { in ASCII
                    fprintf(lex,"LeftCurlyBracket\n");
                    printf("LeftCurlyBracket\n");
                    chr = getc(ceng);
                }
                else if (chr == 125){//  } in ASCII
                    fprintf(lex,"RightCurlyBracket\n");
                    printf("RightCurlyBracket\n");
                    chr = getc(ceng);
                }
                else if(chr == 34){//  " in ASCII
                    int lenght = 0;
                    char *string;
                    string = (char*) calloc (lenght,sizeof(char));
                    chr = getc(ceng);

                    while (chr != 34 && chr != EOF){
                        string = (char*) realloc(string,lenght+1*sizeof(char));
                        string [lenght] = chr;
                        lenght++;
                        chr = getc(ceng);
                    }
                    if(chr != 34){ // "string unterminated  
                            fprintf(lex,"Unterminated String Error! A string constant cannot terminate before the file end./n");
                            printf("Unterminated String Error! A string constant cannot terminate before the file end./n");
                            break;
                    }
                    else{
                        fprintf(lex,"StringConst (%s)\n",string);
                        printf("StringConst (%s)\n",string);
                        chr = getc(ceng);
                        continue;
                    }
                    free(string);
                    lenght = 0;
                }
                else if (chr == 59){// ; in ASCII
                    fprintf(lex,"EndOfLine\n");
                    printf("EndOfLine\n");
                    chr = getc(ceng);
                }
                else{
                    puncts[0] = chr;
                    int lnght2 = strlen(puncts);
                    chr = getc(ceng);
                    if(ispunct(chr)){
                        puncts[1] = chr;
                    }
                    char *puncttoken;
                    puncttoken = strtok(operators,",");
                    while (puncttoken!= NULL){
                        int lnght = strlen(puncttoken);

                        int isOperator = strcmp(puncts,puncttoken);
                        if(isOperator == 0){
                            fprintf(lex,"Operator (%s)\n",puncttoken);
                            printf("Operator (%s)\n",puncttoken);

                            break;
                        }
                        else{
                            puncttoken = strtok(NULL,",");
                        }
                    }
                    }
                    free(puncts);
                }
            }
            fclose(ceng);
            fclose(lex);
        }

