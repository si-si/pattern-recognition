#include "db.h"

typedef struct private_db_handler private_db_handler;

struct private_db_handler{
        db_handler public;
        MYSQL mysql;
};

static int db_init(private_db_handler *this, char *host, char *user, char *passwd, char *db, unsigned int port, const char *socket, unsigned long flag)
{
        if (!mysql_init(&this->mysql)){
		printf("mysql_init error!\n");
                return -1;
        }
        printf("mysql initialized successfully !\n");
        if (!mysql_real_connect(&this->mysql, host, user, passwd, db, port, socket, flag)){
		printf("mysql_connect error!\n");
                return -1;
        }
	printf("mysql connect successfully!\n");  
	return 1;
}

static int db_deinit(private_db_handler *this)
{
	mysql_close(&this->mysql);
	free(this);
	this = NULL;
	return 1;
}

static void *db_query(private_db_handler *this, char *sql, void *(*pfun)(MYSQL_RES *))
{
	MYSQL_RES *result;

	if (mysql_real_query(&this->mysql, sql, strlen(sql))){
		printf("mysql_real_query error!\n");
		return NULL;
	}	
	if (!(result = mysql_store_result(&this->mysql))){
		//printf("mysql_store_result error!\n");
		return NULL;
	}
	void *p = NULL;
	if (pfun){
		p = pfun(result);
	}
	if (result)
		mysql_free_result(result);
	return p;
}

db_handler *db_handler_create()
{
	private_db_handler *this = malloc(sizeof(private_db_handler));
	if (!this){
		fprintf(stderr, "db_handler_create error %s!!\n", strerror(errno));
		return NULL;
	}
	this->public.db_init = (int (*)(db_handler *this, char *host, char *user, char *passwd, char *db, unsigned int port, const char *socket, unsigned long flag))db_init;
	this->public.db_deinit = (int (*)(db_handler *this))db_deinit;
	this->public.db_query = (void *(*)(db_handler *this, char *sql, void *(*pfun)(MYSQL_RES *)))db_query; 
	return (db_handler *)this;
}
