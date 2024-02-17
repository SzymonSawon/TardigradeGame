#include "ida.h"

size_t new_uuid(void) {
    static size_t current_uuid = 42;
    return current_uuid++;
}
