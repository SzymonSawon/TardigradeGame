#ifndef DEBUG_INFO_H_
#define DEBUG_INFO_H_

#include <stdbool.h>

typedef struct {
    bool visible;
} DebugInfoSystem;

void debug_info_system_update(DebugInfoSystem*);

#endif
