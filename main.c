#include "db.h"

#define USER "root"
#define HOST "localhost"
#define PASSWD "duanmaotao"
#define DB "pattern_recognition"

#define LEN 20

typedef char word_t[LEN];

int *sum;
word_t *words;


void *get_result(MYSQL_RES *res);
void *get_value(MYSQL_RES *res);
void *get_word(MYSQL_RES *res);

int main()
{
	db_handler *db_handler = db_handler_create();
	db_handler->db_init(db_handler, HOST, USER, PASSWD, DB, 0, NULL, 0);
	sum = db_handler->db_query(db_handler, "select num from word_table", get_value);
	if (!sum){
		printf("get sum error!\n");
		return -1;
	}
	words = db_handler->db_query(db_handler, "select distinct(hyp) from word_table", get_word);
	if (!words){
		printf("get words error!\n");
		return -1;
	}

	db_handler->db_deinit(db_handler);
	free(words);
	words = NULL;
	free(sum);
	sum = NULL;
	return 0;
}

void *get_word(MYSQL_RES *res)
{
        MYSQL_ROW row;
        MYSQL_FIELD *field;
        if (!res)
                return NULL;
        int num_field, i;
        field = mysql_fetch_field(res);
        num_field = mysql_num_fields(res);
	
	word_t *p = calloc(res->row_count, sizeof(word_t));	
	word_t *pos = p;
	printf("get words!\n");
        while (row = mysql_fetch_row(res)){
		if (pos > p + res->row_count){
			free(p);
			printf("get_word failed!\n");
			return NULL;
		}
                strncpy(*pos, row[0], LEN);
		printf("str %s addr %d\n", pos, &pos);
		pos++;
        }	
	return (void *)p;
}

void *get_value(MYSQL_RES *res)
{
        MYSQL_ROW row;
        MYSQL_FIELD *field;
        if (!res)
                return NULL;
        int num_field, i;
        field = mysql_fetch_field(res);
        num_field = mysql_num_fields(res);
	
	unsigned int *p = malloc(sizeof(unsigned int));
	*p = 0;
        while (row = mysql_fetch_row(res)){    
      		*p += atoi(row[0]);
        }
	return (void *)p;
}

void *get_result(MYSQL_RES *res)
{
	MYSQL_ROW row;
	MYSQL_FIELD *field;
	printf("res.row_num :%d\n", res->row_count);
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
