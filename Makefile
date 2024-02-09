SOURCES+=src/main.c
SOURCES+=src/world.c
SOURCES+=src/systems/debug_info.c
SOURCES+=src/systems/resource_manager.c

HEADERS+=src/world.h
HEADERS+=src/systems/debug_info.h
HEADERS+=src/systems/resource_manager.h

SOURCES+=thirdparty/lib/libraylib.a

CFLAGS+=-I./thirdparty/include

LDFLAGS+=-lm

main: ${SOURCES} ${HEADERS}
	${CC} -o main ${CFLAGS} ${LDFLAGS} ${SOURCES}
