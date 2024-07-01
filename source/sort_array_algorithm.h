#include "sort_array.h"

void reverse_array(struct array_desc *const array);
void swap(uint8_t *elema, uint8_t *elemb);
void bubble_sort(struct array_desc *const array);
void quick_sort(struct array_desc *array, int low_index, int high_index );
void merge_sort(struct array_desc *const array, bool skip_dups);
void merge_array(struct array_desc *a_desc,
                 struct array_desc *b_desc,
                 struct array_desc *c_desc,
                 bool skip_dups,
                 bool merge_back);
