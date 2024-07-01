#include "sort_array.h"

//*****************************************************************************
// Function: get_array_element
//
// Description: Get the element at index stored in the struct array_desc.
//
// Parameters: desc - pointer to the struct array_desc.
//
// Return: the element at the current index in the array.
//
//*****************************************************************************
int get_array_element(struct array_desc *const desc)
{
    return desc->ptr[desc->index];
}

uint8_t *get_array_element_ptr(struct array_desc *const desc)
{
    return &desc->ptr[desc->index];
}

//*****************************************************************************
// Function: get_array_indexed_element
//
// Description: Get the element at index provided.
//
// Parameters: desc  - pointer to the struct array_desc.
//             index - index of the element requested.
//
// Return: the element at the current index in the array.
//
//*****************************************************************************
int get_array_indexed_element(struct array_desc *const desc,
                              const int index)
{
    return desc->ptr[index];
}

//*****************************************************************************
// Function: set_array_element
//
// Description: Set the element at index stored in the struct array_desc.
//
// Parameters: desc    - pointer to the struct array_desc.
//             element - value to be stored.
//
// Return: the new element at the current index in the array.
//
//*****************************************************************************
int set_array_element(struct array_desc *const desc,
                      const int element)
{
    return desc->ptr[desc->index] = element;
}

//*****************************************************************************
// Function: set_array_indexed_element
//
// Description: Set the element at index provided.
//
// Parameters: desc    - pointer to the struct array_desc.
//             index   - index of the element requested.
//             element - value to be stored.
//
// Return: the new element at the current index in the array.
//
//*****************************************************************************
int set_array_indexed_element(struct array_desc *const desc,
                              const int index,
                              const int element)
{
    return desc->ptr[index] = element;
}


//*****************************************************************************
// Function: print_array
//
// Description: Print the elements of the array.
//
// Parameters: function - calling function, for print
//             desc - pointer to the struct array_desc.
//
// Return: void
//
//*****************************************************************************
void print_array(const char *const function, const struct array_desc *const array)
{

    uint32_t i;
#if 0
    printf("%s:\t%s", function, strlen(function) < 7 ? "\t" : "" );

    printf("%s size = %d, count = %d, index = %d\n",
            array->name,
            array->size,
            array->count,
            array->index);
#endif
    for (i = 0; i < array->count; i++) {
        if (i == 0 ) {
//            printf("\t\t%s = [%d, ", array->name, array->ptr[i]);
            if (strcmp("b", array->name) == 0) {
                if (i == array->count - 1) {
                    printf("[%d]\n", array->ptr[i]);
                } else {
                    printf("[%d, ", array->ptr[i]);
                }
            } else {
                if (i == array->count - 1) {
                    printf("\n[%d]", array->ptr[i]);
                } else {
                    printf("\n[%d, ", array->ptr[i]);
                }
            }
        }
        else {
            if (i < array->count - 1) {
                printf("%d, ", array->ptr[i]);
            } else {
                if (strcmp("a", array->name) == 0) {
                    printf("%d]", array->ptr[i]);
                } else {
                    printf("%d]\n", array->ptr[i]);
                }
            }
        }
    }
//    printf("]\n");
}
void print_single_array(const char *const function,
                  const struct array_desc *const array)
{

    uint32_t i;

    for (i = 0; i < array->count; i++) {
        if (i == 0 ) {
            printf("%s\t\t = [%d, ", array->name, array->ptr[i]);
        }
        else {
            if (i < array->count - 1) {
                printf("%d, ", array->ptr[i]);
            } else {
                printf("%d]\n", array->ptr[i]);
            }
        }
    }
}
void print_split_arrays(const char *const function,
                        const struct array_desc *const ary_a,
                        const struct array_desc *const ary_b)
{

    uint32_t i;

    printf("[%s][%s]\t\t = ", ary_a->name, ary_b->name);
    for (i = 0; i < ary_a->count; i++) {
        if (i == 0 ) {
            if (i == ary_a->count - 1) {
                printf("[%d]", ary_a->ptr[i]);
            } else {
                printf("[%d, ", ary_a->ptr[i]);
            }
        }
        else {
            if (i < ary_a->count - 1) {
                printf("%d, ", ary_a->ptr[i]);
            } else {
                printf("%d]", ary_a->ptr[i]);
            }
        }
    }
    for (i = 0; i < ary_b->count; i++) {
        if (i == 0 ) {
            if (i == ary_b->count - 1) {
                printf("[%d]\n", ary_b->ptr[i]);
            } else {
                printf("[%d, ", ary_b->ptr[i]);
            }
        }
        else {
            if (i < ary_b->count - 1) {
                printf("%d, ", ary_b->ptr[i]);
            } else {
                printf("%d]\n", ary_b->ptr[i]);
            }
        }
    }

}
void print_arrays(const char *const function,
                  const enum merge_sort merge_sort,
                  const struct array_desc *const array,
                  const struct array_desc *const ary_a,
                  const struct array_desc *const ary_b)
{

    if (merge_sort == sorting) {
        print_single_array(function, array);
        print_split_arrays(function, ary_a, ary_b);
    } else {
        print_split_arrays(function, ary_a, ary_b);
        print_single_array(function, array);
    }

}

