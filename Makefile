SOURCES+=src/main.c
SOURCES+=src/world.c
SOURCES+=src/systems/sprite.c
SOURCES+=src/systems/debug_info.c
SOURCES+=src/systems/resource_manager.c
SOURCES+=src/systems/physics.c
SOURCES+=src/utils/ida.c

HEADERS+=src/world.h
SOURCES+=src/systems/sprite.h
HEADERS+=src/systems/debug_info.h
HEADERS+=src/systems/resource_manager.h
HEADERS+=src/systems/physics.h
SOURCES+=src/utils/da.h
SOURCES+=src/utils/ida.h

SOURCES+=thirdparty/lib/libraylib.a

CFLAGS+=-I./thirdparty/include

LDFLAGS+=-lm

main: ${SOURCES} ${HEADERS}
	${CC} -o main ${CFLAGS} ${LDFLAGS} ${SOURCES}
