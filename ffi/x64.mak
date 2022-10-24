
SRCS = src/closures.c src/debug.c src/dlmalloc.c src/java_raw_api.c src/prep_cif.c src/raw_api.c src/tramp.c src/types.c src/x86/ffiw64.c
OBJS = $(SRCS:%.c=%.o)

default: all

all: libffi.a

libffi.a: $(OBJS)
	ar cr $(@) $(OBJS)

libffi.lib: $(OBJS)
	$(CC) -c ./src/x86/win64.S -o src/x86/win64.o -Iinclude -fno-asynchronous-unwind-tables $(CFLAGS)
	lib /out:$(@) $(OBJS) src/x86/sysv.o src/x86/win64.o src/x86/unix64.o

$(OBJS): $(@:%.o=%.c)
	$(CC) $(OPT) -o $(@) -c $(@:%.o=%.c) -Iinclude -fno-asynchronous-unwind-tables $(CFLAGS)
