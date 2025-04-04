#include <stdlib.h>

#include "array.h"
#include "triangle.h"

#define ARRAY_RAW_DATA(array) ((int *)(array) - 2)
#define ARRAY_CAPACTIY(array) (ARRAY_RAW_DATA(array)[0])
#define ARRAY_OCCUPIED(array) (ARRAY_RAW_DATA(array)[1])

static int cmpavgz(const void *a, const void *b)
{
	const triangle_t *tri_a = (triangle_t *)a;
	const triangle_t *tri_b = (triangle_t *)b;
	return tri_a->depth > tri_b->depth ? 1 : -1;
}

void *array_hold(void *array, int count, int item_size)
{
	if (array == NULL) {
		int raw_size = (sizeof(int) * 2) + (item_size * count);
		int *base = (int *)malloc(raw_size);
		base[0] = count;
		base[1] = count;
		return base + 2;
	} else if (ARRAY_OCCUPIED(array) + count <= ARRAY_CAPACTIY(array)) {
		ARRAY_OCCUPIED(array) += count;
		return array;
	} else {
		int needed_size = ARRAY_OCCUPIED(array) + count;
		int float_curr = ARRAY_CAPACTIY(array) * 2;
		int capacity =
		    needed_size > float_curr ? needed_size : float_curr;
		int occupied = needed_size;
		int raw_size = sizeof(int) * 2 + item_size * capacity;
		int *base = (int *)realloc(ARRAY_RAW_DATA(array), raw_size);
		base[0] = capacity;
		base[1] = occupied;
		return base + 2;
	}
}

int array_length(void *array)
{
	return (array != NULL) ? ARRAY_OCCUPIED(array) : 0;
}

void array_free(void *array)
{
	if (array != NULL) {
		free(ARRAY_RAW_DATA(array));
	}
}

void array_qsort(void *array)
{
	int len = array_length(array);
	qsort(array, len, sizeof(triangle_t), cmpavgz);
}
