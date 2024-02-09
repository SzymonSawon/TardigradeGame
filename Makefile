SOURCES+=src/main.c
SOURCES+=src/world.c
SOURCES+=src/systems/debug_info.c

HEADERS+=src/world.h
HEADERS+=src/systems/debug_info.h

SOURCES+=thirdparty/lib/libraylib.a

CFLAGS+=-I./thirdparty/include

LDFLAGS+=-lm

main: ${SOURCES} ${HEADERS}
	${CC} -o main ${CFLAGS} ${LDFLAGS} ${SOURCES}
