#include "sort_array.h"
#include "sort_array_algorithm.h"

// Todo: try cache line alignment for performance.
uint8_t ary_a[] = {6, 3, 6, 31, 22, 57, 45, 70, 69, 70};
uint8_t ary_b[] = {6, 1, 31, 21, 41, 69, 71, 51, 73, 86, 99};
uint8_t ary_c[128];


// Define three arrays, two for input, one for output.
struct array_desc a_desc = {
            "array_a",
            ary_a,
            sizeof(ary_a),
            0,
            sizeof(ary_a)
        };

struct array_desc b_desc = {
            "array_b",
            ary_b,
            sizeof(ary_b),
            0,
            sizeof(ary_b)
        };

struct array_desc c_desc = {
            "array_c",
            ary_c,
            0,
            0,
            sizeof(ary_c)
        };


//*****************************************************************************
// Function: main
//
// Description: Exercise implementing various sorting algorithms, based on
//              command line arguments specifying sort type, whether duplicate
//              elements should be skipped and if the array should be reversed.
//
// Parameters: Sort type, skip duplicates and reverse array.
//
// Return: 0 on success, otherwise, non-zero.
//
//*****************************************************************************
int main(int argc, char **argv)
{
    bool skip_dups = false;
    bool  bubble = false;
    bool  merge = false;
    bool  quick = false;
    bool  rev = false;

    argc -= 1;

    while (argc) {
        if (strncmp("skip_dups", argv[1], strlen("skip_dups")) == 0) {
             skip_dups = true;
             argc--;
             argv++;
             continue;
        }

        if (strncmp("bubble", argv[1], strlen("bubble")) == 0) {
             bubble = true;
             argc--;
             argv++;
             continue;
        }

        if (strncmp("merge", argv[1], strlen("merge")) == 0) {
             merge = true;
             argc--;
             argv++;
             continue;
        }

        if (strncmp("quick", argv[1], strlen("quick")) == 0) {
             quick = true;
             argc--;
             argv++;
             continue;
        }

        if (strncmp("all", argv[1], strlen("all")) == 0) {
             merge = true;
             bubble = true;
             quick = true;
             argc--;
             argv++;
             continue;
        }

        if (strncmp("rev", argv[1], strlen("rev")) == 0) {
             rev = true;
             argc--;
             argv++;
             continue;
        }
        argc--;
    }

    print_array(__FUNCTION__, &a_desc);
    print_array(__FUNCTION__, &b_desc);

    printf("\n");

    if (bubble) {
        printf("************************************************************\n");
        printf(" doing bubble sort\n");
        printf("************************************************************\n");
        bubble_sort(&a_desc);
        bubble_sort(&b_desc);
        merge_array(&a_desc, &b_desc, &c_desc, skip_dups, false);

        print_array(__FUNCTION__, &a_desc);
        print_array(__FUNCTION__, &b_desc);
        print_array(__FUNCTION__, &c_desc);
    }

    pause_display_output(2);
    printf("\n");

    if (merge) {
        printf("************************************************************\n");
        printf(" doing merge sort\n");
        printf("************************************************************\n");
        merge_sort(&a_desc, skip_dups);
//       merge_sort(&b_desc);
//       merge_array(&a_desc, &b_desc, &c_desc);
        print_array(__FUNCTION__, &a_desc);
        print_array(__FUNCTION__, &b_desc);
        print_array(__FUNCTION__, &c_desc);
    }
    pause_display_output(2);
    printf("\n");

    if (quick) {
        printf("************************************************************\n");
        printf(" doing quick sort\n");
        printf("************************************************************\n");
        quick_sort(&a_desc, 0, a_desc.count - 1);
        quick_sort(&b_desc, 0, b_desc.count - 1);
        merge_array(&a_desc, &b_desc, &c_desc, skip_dups, false);
        print_array(__FUNCTION__, &a_desc);
        print_array(__FUNCTION__, &b_desc);
        print_array(__FUNCTION__, &c_desc);
    }
    pause_display_output(2);
    printf("\n");

    if (rev) {
        reverse_array(&a_desc);
        reverse_array(&b_desc);
        reverse_array(&c_desc);
    }
//    print_array(__FUNCTION__, &c_desc);
}


