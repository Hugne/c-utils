%{
    #include <stdio.h>
    #include <sys/socket.h>
    #include "cli.h"

    int yylex(void);
    void yyerror(char*);
%}

%token USR_CONNECT
%token USR_DISCONNECT
%token USR_LISTEN
%token PORTNO
%token IPPROTO
%token IPV4ADDR
%token IPV6ADDR
%token EXIT


%union {
    int proto;
    int dstport;
    char dstipaddress[64];
}

%type <proto>		IPPROTO
%type <dstport>		PORTNO
%type <dstipaddress>	IPV4ADDR
%type <dstipaddress>	IPV6ADDR

%%

program:
    /* empty */
    | program	connect	    '\n'
    | program	error	    '\n'
    | program	exit	    '\n'
    | program /* empty */   '\n'
    ;

exit:
    EXIT {
    struct user_command cmd; 
    cmd.cmd = cmd_exit;
    execute_command(&cmd);
    }
;

connect:
    USR_CONNECT IPV6ADDR IPPROTO {
    printf("user connect %s proto:%d \n",$2, $3);
    struct user_command cmd;
    cmd.cmd = cmd_connect;
    inet_pton(AF_INET6, $2, &(cmd.args.usr_connect.dst));
    cmd.args.usr_connect.proto = $3;
    execute_command(&cmd);
    }
;

connect:
    USR_CONNECT IPV4ADDR IPPROTO {
    printf("user connect %s proto:%d \n",$2, $3);
    struct user_command cmd;
    cmd.cmd = cmd_connect;
    inet_pton(AF_INET, $2, &(cmd.args.usr_connect.dst));
    cmd.args.usr_connect.proto = $3;
    execute_command(&cmd);
    }
;

%%

void yyerror(char *s)
{
    fprintf(stderr, "%s\n",s);
}


