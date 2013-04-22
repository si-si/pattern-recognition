#include "sort.h"

static void change_pos(elem_t *p1, elem_t *p2)
{
	elem_t tmp;
	tmp.value = p1->value;
	tmp.p = p1->p;
	p1->value = p2->value;
	p1->p = p2->p;
	p2->value = tmp.value;
	p2->p = tmp.p;
}

static int partition(elem_t *data, int s, int f)
{
	int i, j;
	j = s-1;
	for (i = s; i <= f; i++){
		if (SE(data[i].value, data[f].value)){
			j++;
			change_pos(&data[i], &data[j]);
		}	
	}
	return j; 
}

static int quik_recur(elem_t *data, int s, int f)
{
        int pivot;
        if (s < f){
                pivot = partition(data, s, f);
                quik_recur(data, s, pivot-1);
                quik_recur(data, pivot+1, f);
        }
        return 1;
}

int quik_sort(elem_t *data, int s, int f)
{
        if (s > f){
                printf("para error s > f\n");
                return -1;
        }
        else{
                quik_recur(data, s, f);
                return 0;
        }
}

