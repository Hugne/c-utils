#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>


#include "cli.h"


int main(int argc, char* argv[])
{
    
    parse();
    printf("fixme..");
    return 0;
}

void execute_command(struct user_command* cmd)
{
    switch(cmd->cmd)
    {
	case cmd_connect:
	case cmd_disconnect:
	case cmd_listen:
	    printf("fixme");
	break;
	case cmd_exit:
	    printf("bye\n");
	    exit(0);
	    break;

    }
}

