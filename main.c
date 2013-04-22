#include "db.h"
#include "sort.h"
#include "lcs.h"

#define USER "root"
#define HOST "localhost"
#define PASSWD "duanmaotao"
#define DB "pattern_recognition"

#define LEN 20
#define SIM_NUM 50
#define SQLLEN 100

typedef char word_t[LEN];

int sum;
word_t *words;

void *get_result(MYSQL_RES *res);
void *get_value(MYSQL_RES *res);
void *get_word(MYSQL_RES *res);

int main()
{
	int *psum;
	char sql[SQLLEN];
	db_handler *db_handler = db_handler_create();
	db_handler->db_init(db_handler, HOST, USER, PASSWD, DB, 0, NULL, 0);

	psum = db_handler->db_query(db_handler, "select count(distinct(hyp)) from word_table", get_value);

        if (!psum){
                printf("get sum error!\n");
                return -1;
        }
	sum = *psum;
	free(psum);

	words = db_handler->db_query(db_handler, "select distinct(hyp) from word_table", get_word);
	
	if (!words){
		printf("get words error!\n");
		return -1;
	}

	char input[LEN];
	elem_t similar[SIM_NUM];
	int i, count, choosen;
	int len;
	int *pi = NULL;
	while (1){
		fflush(stdin);
		fflush(stdout);
		bzero(input, LEN);
		bzero(similar, SIM_NUM);
		printf("please input your word: ");
		scanf("%s", input);
		len = strlen(input);
		count = 0;
		for (i = 0; i < sum; i++){
			if ((LCS(input, words[i], NULL) >= len - 2) && ((int)strlen(words[i]) - len <= 2)){
				similar[count].p = words[i];
				bzero(sql, SQLLEN);
				sprintf(sql, "select num from word_table where hyp='%s' and inp='%s'", words[i], input);
				pi = db_handler->db_query(db_handler, sql, get_value);
				if (pi == NULL)
					continue;
				similar[count].value = *pi;
				if (count++ >= SIM_NUM){
					break;
				}	
				free(pi);
				pi = NULL;						
			}
		}
		if (count == 0)
			printf("there is no similar correct words!!\n");
		else{
			quik_sort(similar, 0, count-1);
			for (i = count-1; i >= 0; i--)
				printf("%d.%s\t", count-i, (char *)similar[i].p);
			printf("\ninput your words' number:  ");
			scanf("%d", &choosen);
			if (choosen < 1 || choosen > count){
				printf("choose error!\n");
				continue;
			}
			bzero(sql, SQLLEN);
			sprintf(sql, "update word_table set num=num+1 where hyp='%s' and inp='%s'", (char *)similar[count-choosen].p, input);
			db_handler->db_query(db_handler, sql, NULL);
		}
	}

	db_handler->db_deinit(db_handler);
	free(words);
	words = NULL;
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
		printf("str %s addr %d\n", pos, pos);
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
