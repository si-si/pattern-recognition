#include "db.h"

#define USER "root"
#define HOST "localhost"
#define PASSWD "duanmaotao"
#define DB "pattern_recognition"

void *get_result(MYSQL_RES *res);

int main()
{
	db_handler *db_handler = db_handler_create();
	db_handler->db_init(db_handler, HOST, USER, PASSWD, DB, 0, NULL, 0);
	db_handler->db_query(db_handler, "select * from word_table", get_result);
	db_handler->db_deinit(db_handler);
	return 0;
}

void *get_result(MYSQL_RES *res)
{
	MYSQL_ROW row;
	MYSQL_FIELD *field;
	if (!res)
		return NULL;
	int num_field, i;
	field = mysql_fetch_field(res);
	num_field = mysql_num_fields(res);
	
	for (i = 0; i < num_field; i++){
		printf("%s\t", field[i].name);
	}
	printf("\n");
	while (row = mysql_fetch_row(res)){
		for (i = 0; i < num_field; i++){
			printf("%s\t", row[i]);
		}
		printf("\n");
	}
	return NULL;
}
