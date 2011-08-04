#ifndef CLI_PARSER_H
#define CLI_PARSER_H

#include <sys/socket.h>

enum command {
    cmd_connect = 1,
    cmd_disconnect,
    cmd_listen
};

struct connect_args {
    struct sockaddr_storage dst;
};

struct user_command {
    enum command cmdid;
    union {
	struct connect_args usr_connect; /*Args for cmd_connect*/
    }args;
};


void execute_command(struct user_command *cmd);

#endif
