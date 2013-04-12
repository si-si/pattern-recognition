#ifndef _DMT_DB_
#define _DMT_DB_

#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct db_handler db_handler;

struct db_handler{
	int (*db_init)(db_handler *this, char *host, char *user, char *passwd, char *db, unsigned int port, const char *socket, unsigned long flag);
	int (*db_deinit)(db_handler *this);
	void *(*db_query)(db_handler *this, char *sql, void *(*pfun)(MYSQL_RES *));
};

db_handler *db_handler_create();

#endif

