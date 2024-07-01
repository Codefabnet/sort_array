#include "sort_array.h"
#include "sort_array_algorithm.h"

//*****************************************************************************
// Function: reverse_array
//
// Description: Reverse the order of the elements in an array.
//
// Parameters: desc - pointer to the struct array_desc.
//
// Return: void
//
//*****************************************************************************
void reverse_array(struct array_desc *const array)
{

    uint32_t left_index = 0;
    uint32_t right_index = array->count - 1;

    // Print the input array.
    print_array(__FUNCTION__, array);

    // Swap outboard array elements, moving inward.
    for (left_index = 0;
         left_index < (array->count >> 1);
         left_index++, right_index = (array->count - 1) - left_index) {

        int left_element = get_array_indexed_element(array, left_index);
        int right_element = get_array_indexed_element(array, right_index);

        left_element ^= right_element;
        right_element ^= left_element;
        left_element ^= right_element;

        set_array_indexed_element(array, left_index, left_element);
        set_array_indexed_element(array, right_index, right_element);
    }

    // Print the output array.
    print_array(__FUNCTION__, array);
}

void swap(uint8_t *elema, uint8_t *elemb)
{
    if (*elema == *elemb)
        return;
    *elema ^= *elemb;
    *elemb ^= *elema;
    *elema ^= *elemb;
}

//*****************************************************************************
// Function: bubble_sort
//
// Description: Sort the elements in an array.
//
// Parameters: desc - pointer to the struct array_desc.
//
// Return: void
//
//*****************************************************************************
void bubble_sort(struct array_desc *const array)
{

    uint32_t i;
    uint32_t swap_count;

    // Print the input array.
    print_array(__FUNCTION__, array);

    // Swap adjacent array elements of the entire array, repeat as needed.
    do {
        // swap_count controls the number of swap iterations.
        swap_count = 0;
        for (i = 0; i < array->count - 1; i++){
            uint8_t *current_element = &array->ptr[i];
            uint8_t *next_element = &array->ptr[i + 1];

            if (*current_element > *next_element) {
                // Increment swap_count to force another sort operation.
                swap_count++;
                swap(current_element, next_element);
            }
        }
    }while (swap_count);

    // Print the output array.
    print_array(__FUNCTION__, array);
}

void quick_sort(struct array_desc *array, int low_index, int high_index )
{

    // Use the last element for the pivot in the partition step.
    int pivot = array->ptr[high_index];
    int left_index = low_index;
    int right_index = high_index;

    if (low_index >= high_index) {
        return;
    }

    //************************************************************
    // Partition the array
    //************************************************************
    while (left_index < right_index) {
        while (array->ptr[left_index] <= pivot && left_index < right_index) {
            left_index++;
        }
        while (array->ptr[right_index] >= pivot && left_index < right_index) {
            right_index--;
        }
        swap(&array->ptr[left_index], &array->ptr[right_index]);
    }
    swap(&array->ptr[left_index], &array->ptr[high_index]);

    // Sort recursively.
    quick_sort(array, low_index, left_index - 1);
    quick_sort(array, left_index + 1, high_index);
}

//*****************************************************************************
// Function: merge_array
//
// Description: Combine the elements of two arrays, maintaining order of the
//              input arrays.
//
// Parameters: a_desc - Array descriptor for one input array.
//             b_desc - Array descriptor for one input array.
//             c_desc - Array descriptor for the output array.
//
// Return: void
//
//*****************************************************************************

void merge_array(struct array_desc *a_desc,
                 struct array_desc *b_desc,
                 struct array_desc *c_desc,
                 bool skip_dups,
                 bool merge_back)
{
    const uint8_t a_count = a_desc->count;
    const uint8_t b_count = b_desc->count;

    printf("\nmerging arrays...\n");
    print_arrays(__FUNCTION__, merging, c_desc, a_desc, b_desc);
//    dprintf("%s: a_count = %d, b_count = %d\n",
//            __FUNCTION__,
//            a_count,
//            b_count);

    // Loop while there are elements in ary_a and ary_b and put
    // the smaller value of the two in ary_c. The index in the
    // struct array_desc is incremented as appropriate inside the loop.
    while ((a_desc->index < a_count) && (b_desc->index < b_count)) {

        uint8_t *element_a = get_array_element_ptr(a_desc);
        uint8_t *element_b = get_array_element_ptr(b_desc);
        uint8_t donor_element;
        if (merge_back) {
            // for merge sort, a_array begins at the start of the output
            // array.(Divide and Conquer) Simply writing elements in
            // the output array may overwrite elements in a_array that
            // still need to be considered for input, so we swap in place.
            if (*element_a > *element_b) {
                *element_a ^= *element_b;
                *element_b ^= *element_a;
                *element_a ^= *element_b;
            }
            // donor_element in this case is used to look for duplicates.
            donor_element = *element_a;
            a_desc->index++;
        } else {
            // Find the smaller number from the 2 arrays.
            struct array_desc *donor_array = (*element_a < *element_b) ?
                                            a_desc : b_desc;
            donor_element = get_array_element(donor_array);

            // Insert next element into the output array, ary_c.
            set_array_element(c_desc, donor_element);
            donor_array->index++;
        }

        if (skip_dups) {
            // Skip duplicates from ary_a.
            while ((get_array_element(a_desc) == donor_element) &&
			    (a_desc->index < a_desc->count)) {
                   a_desc->index++;
            }

            // Skip duplicates from ary_b.
            while ((get_array_element(b_desc) == donor_element) &&
			    (b_desc->index < b_desc->count)) {
                   b_desc->index++;
            }
        }
        // Update the output array stats.
        c_desc->count++;
        c_desc->index++;

    } // while (a_index < a_count && b_index < b_count )

    //*********************************************************
    // Only one of the 2 arrays has been indexed to the end,
    // in the initial while loop. Copy remaining elements
    // from the other array into the output array.
    //*********************************************************

    struct array_desc *donor_array = (a_desc->index < a_count) ?
                                    a_desc : b_desc;
    int donor_count = donor_array->count;

    // Store the remaining elements from the longest array, if any.
    // For this exercise, longest means the array with the most unique
    // element.
    while (donor_array->index < donor_count) {

        int donor_element = get_array_element(donor_array);

        // Insert element from the longer array into ary_c.
        set_array_element(c_desc, donor_element);
        donor_array->index++;

        if (skip_dups) {
            // Skip duplicates from the array..
            while (get_array_element(donor_array) == donor_element &&
                    donor_array->index < donor_array->count) {
                   donor_array->index++;
            }
        }

        // Update ary_c stats.
        c_desc->count++;
        c_desc->index++;
    }


}


//*****************************************************************************
// Function: merge_sort
//
// Description: Recursively call this function, for each half of the given
//              Until a single element array is passed, After returning, the
//              algorithm merges the two halves of the array at each recursive
//              level. Upon returning from the top level, the entire array is
//              sorted.
//
// Parameters:  array - To be sorted.
//              skip_dups - Discard duplicate elements if true.
//
// Return: void
//
//*****************************************************************************

void merge_sort(struct array_desc *const array, bool skip_dups)
{
    dprintf("\n");
    dprintf("Entering %s\n", __FUNCTION__);
    int array_count = array->count;

    if (array_count < 2) {
        printf("Exiting %s on count == 1\n", __FUNCTION__);
        return;
    }
    struct array_desc a_array = {
        .ptr = &array->ptr[0],
        .name = "a",
        .count = array->count / 2,
        .index = 0,
        .size = array-> size / 2,
    };
    struct array_desc b_array = {
        .ptr = &array->ptr[a_array.count],
        .name = "b",
        .count = array->count - a_array.count,
        .index = 0,
        .size = array->size - a_array.size,
    };
//    print_array(__FUNCTION__, array);
//    print_array(__FUNCTION__, &a_array);
//    print_array(__FUNCTION__, &b_array);
    print_arrays(__FUNCTION__, sorting, array, &a_array, &b_array);
    array->index = 0;
    array->count = 0;
    pause_display_output(2);
    merge_sort(&a_array, skip_dups);
    merge_sort(&b_array, skip_dups);
    a_array.index = 0;
    b_array.index = 0;
    pause_display_output(2);
    merge_array(&a_array, &b_array, array, skip_dups, true);
    print_single_array(__FUNCTION__, array);
    dprintf("\nExiting %s\n", __FUNCTION__);
}

