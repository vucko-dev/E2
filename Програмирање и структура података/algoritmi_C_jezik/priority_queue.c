/*Priority queue implementation in C via heap (dynamic array)*/
#include <stdio.h>
#include <stdlib.h>
typedef int TYPE;
typedef struct dyn_array_st {
	TYPE *parray;
	int filled;
	int capacity;
} DYN_ARRAY;
void init_array(DYN_ARRAY *pq) {
	pq->parray = NULL;
	pq->filled = pq->capacity = 0;
}
void destroy_array(DYN_ARRAY *pq) {
	free(pq->parray);
	init_array(pq);
}
void resize_array(DYN_ARRAY *pq, double size) {
	if(pq->capacity == 0) {
		pq->capacity = 4;
		pq->parray = malloc(sizeof(TYPE) * pq->capacity);
		return;
	}
	pq->capacity*=size;
	pq->parray = realloc(pq->parray, sizeof(TYPE) * pq->capacity);
}
int left(int i) {
	return 2*i + 1;
}
int right(int i) {
	return 2*i + 2;
}
int parent(int i) {
	return (i - 1)/2;
}
void max_heapify(DYN_ARRAY *pq, int i) {
	int l = left(i);
	int r = right(i);
	int max = i;
	if(l < pq->filled && pq->parray[max] < pq->parray[l]) max = l;
	if(r < pq->filled && pq->parray[max] < pq->parray[r]) max = r;
	if(max != i) {
		TYPE temp = pq->parray[i];
		pq->parray[i] = pq->parray[max];
		pq->parray[max] = temp;
		max_heapify(pq, max);
	}
}
TYPE heap_max (DYN_ARRAY pq) {
	return pq.parray[0];
}
TYPE heap_extract_max(DYN_ARRAY *pq) {
	if(pq->filled == 0) {
		puts("ERROR: Tried to extract element from empty array.");
		exit(EXIT_FAILURE);
	}
	TYPE max = pq->parray[0];
	pq->parray[0] = pq->parray[--pq->filled];
	--pq->filled;
	max_heapify(pq, 0);
	return max;
}
void heap_insert(DYN_ARRAY *pq, TYPE new) {
	if(++pq->filled > pq->capacity) resize_array(pq, 2);
	pq->parray[pq->filled - 1] = new;
	int i = pq->filled -1;
	TYPE temp;
	while(i > 0 && pq->parray[parent(i)] < pq->parray[i]){
		temp = pq->parray[parent(i)];
		pq->parray[parent(i)] = pq->parray[i];
		pq->parray[i] = temp;
		i = parent(i);
	}
}
/*Expects that new is higher then the key at i-th position. If it is not then
	the element at the i-th won't be changed function will just simply return*/
void heap_increase_key(DYN_ARRAY *pq, int i, TYPE new) {
	if(i < 0 && i >= pq->filled && new < pq->parray[i]) return;
	pq->parray[i] = new;
	TYPE temp;
	while(i > 0 && pq->parray[parent(i)] < pq->parray[i]){
		temp = pq->parray[parent(i)];
		pq->parray[parent(i)] = pq->parray[i];
		pq->parray[i] = temp;
		i = parent(i);
	}
}

int main() {
	DYN_ARRAY priority_queue;
	init_array(&priority_queue);
	
	heap_insert(&priority_queue, 5);
	heap_insert(&priority_queue, 7);
	heap_insert(&priority_queue, 3);
	heap_insert(&priority_queue, 8);
	heap_insert(&priority_queue, 4);
	
	printf("Extracted max = %d\n", heap_extract_max(&priority_queue));
	printf("New max = %d\n", heap_max(priority_queue));
	heap_increase_key(&priority_queue, 3, 30);
	printf("Max after increased priority = %d\n", priority_queue.parray[0]);
	
	destroy_array(&priority_queue);
	
	return EXIT_SUCCESS;
}




