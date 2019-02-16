#include<stdio.h>
#include <stdlib.h>

#include "mysql.h"

int main(int arg, char * argv[])
{
    MYSQL * conn_ptr;

    conn_ptr = mysql_init(NULL);
    if (!conn_ptr)
    {
        fprintf(stderr, "mysql_init failed\n");
	exit(EXIT_FAILURE);
    }

    conn_ptr = mysql_real_connect(conn_ptr, "localhost", "rick", "123456", "foo", 0, NULL, 0);
    if (conn_ptr)
    {
        printf("connection success\n");
    }
    else
    {
        printf("connection failed\n");
    }

    mysql_close(conn_ptr);

    exit(EXIT_SUCCESS);

}
