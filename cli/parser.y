%{
    #include <stdio.h>
    int yylex(void);
    void yyerror(char*);
%}

%token USR_CONNECT
%token USR_DISCONNECT
%token USR_LISTEN
%token IPPROTO



%%

program:
    
%%

void yyerror(char *s)
{
    fprintf(stderr, "%s\n",s);
}


