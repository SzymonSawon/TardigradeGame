#include "debug_info.h"

#include <raylib.h>

void debug_info_system_update(DebugInfoSystem* sys) {
    if (IsKeyPressed(KEY_F1)) {
        sys->visible = !sys->visible;
    }
    if (sys->visible) {
        DrawFPS(5, 5);
    }
}
