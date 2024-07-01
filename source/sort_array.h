#if !defined(__SORT_ARRAY_H__)
#define __SORT_ARRAY_H__
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>


enum merge_sort {
    merging,
    sorting
};

#define DEBUG
#if defined(DEBUG)
     #define dprintf(format, ...) printf(format __VA_OPT__(,) __VA_ARGS__)
     #define dprint_array(func, array) print_array(func, array)
#else
     #define dprintf(...)
     #define dprint_array(...)
#endif

static inline void pause_display_output(int delay)
{
    for (int i = 0; i < delay; i++) {
        putchar('.');
        fflush(stdout);
        sleep(1);
    }
}
#if 0
static inline void pause_get_input(int delay)
{
    fd_set fds;
    struct timeval tv;
    int ret;

    FD_ZERO(&fds);
    FD_SET(0, &fds);

    tv.tv_sec = delay;
    tv.tv_usec = 0;

    for (int i = 0; i < delay; i++) {
        putchar('.');
        ret = select(1, &fds, 0, 0, &tv);

        if (ret, FD_ISSET(0, &fds)) {
            char c = getchar();
            break;
        }
    }
}
#endif

// struct array_desc contains a pointer to the array it represents,
// a name string for debug purposes, count and size of the
// array and an index used in get and set operations.
struct array_desc {
    const char *name;
    uint8_t *ptr;
    uint32_t count;
    uint32_t index;
    uint32_t size;
};

uint8_t *get_array_element_ptr(struct array_desc *const desc);
int get_array_element(struct array_desc *const desc);
int set_array_element(struct array_desc *const desc, const int element);
int get_array_indexed_element(struct array_desc *const desc, const int index);
int set_array_indexed_element(struct array_desc *const desc,
                              const int index,
                              const int element);
void print_array(const char *const function, const struct array_desc *const array);
void print_arrays(const char *const function,
                  const enum merge_sort ms,
                  const struct array_desc *const array,
                  const struct array_desc *const ary_a,
                  const struct array_desc *const ary_b);
void print_single_array(const char *const function,
                  const struct array_desc *const array);
void print_split_arrays(const char *const function,
                        const struct array_desc *const ary_a,
                        const struct array_desc *const ary_b);

#endif // !defined(__SORT_ARRAY_H__)
