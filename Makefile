SOURCES+=src/main.c
SOURCES+=src/world.c
SOURCES+=src/systems/sprite.c

SOURCES+=thirdparty/lib/libraylib.a

HEADERS+=src/world.h
HEADERS+=src/systems/sprite.h

CFLAGS+=-I./thirdparty/include

LDFLAGS+=-lm

main: ${SOURCES} ${HEADERS}
	${CC} -o main ${CFLAGS} ${LDFLAGS} ${SOURCES}
