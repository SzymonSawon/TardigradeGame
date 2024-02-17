#ifndef IDA_H_
#define IDA_H_

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct ida_IndexEntry {
    size_t uuid;
    size_t index;
    struct ida_IndexEntry* next;
} ida_IndexEntry;

size_t new_uuid(void); 

static void _ida_insert_new_index(ida_IndexEntry* entries, size_t capacity,
                                  size_t uuid, size_t index) {
    ida_IndexEntry* entry = &entries[uuid % capacity];
    if (entry->uuid) {
        ida_IndexEntry* new_entry =
            (ida_IndexEntry*)malloc(sizeof(ida_IndexEntry));
        assert(new_entry && "Buy more ram lol");
        *new_entry = *entry;
        entry->next = new_entry;
    }
    entry->uuid = uuid;
    entry->index = index;
}

#define INVALID_INDEX 0xffffffffffffffff

static size_t _ida_get_index_by_uuid(ida_IndexEntry* entries, size_t capacity,
                                     size_t uuid) {
    ida_IndexEntry* entry = &entries[uuid % capacity];
    do {
        if (entry->uuid == uuid) {
            return entry->index;
        }
    } while (entry->next);
    return INVALID_INDEX;
}

static void _ida_free_entries(ida_IndexEntry* entries, size_t capacity) {
    for (size_t i = 0; i < capacity; i++) {
        if (entries[i].next) {
            _ida_free_entries(entries[i].next, 1);
        }
    }
    free(entries);
}

#define ida_append(arr, it)                                                  \
    do {                                                                     \
        if ((arr).capacity <= (arr).count) {                                 \
            if ((arr).capacity == 0)                                         \
                (arr).capacity = 2;                                          \
            else                                                             \
                _ida_free_entries((arr)._index, (arr).capacity);             \
            (arr).items = realloc(                                           \
                (arr).items, sizeof((arr).items[0]) * ((arr).capacity * 2)); \
            (arr)._index = (ida_IndexEntry*)calloc(sizeof(ida_IndexEntry),   \
                                                   (arr).capacity * 2);      \
            for (size_t _ida_i = 0; _ida_i < (arr).count; _ida_i++) {        \
                _ida_insert_new_index((arr)._index, (arr).capacity * 2,      \
                                      (arr).items[_ida_i].uuid, _ida_i);     \
            }                                                                \
            (arr).capacity *= 2;                                             \
        }                                                                    \
        (arr).items[(arr).count++] = (it);                                   \
    } while (0)

static size_t _ida_temp;

#define ida_find(arr, id)                                                  \
    (_ida_temp = _ida_get_index_by_uuid((arr)._index, (arr).capacity, id), \
     _ida_temp == INVALID_INDEX ? NULL : &(arr).items[_ida_temp])

#define ida_list(t)  \
    t* items;        \
    size_t count;    \
    size_t capacity; \
    ida_IndexEntry* _index

#endif
