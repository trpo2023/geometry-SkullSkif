CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -MMD

hello: main.o libhello.a
        $(CC) $(CFLAGS) -o $@ $^

main.o: main.c
        $(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

libhello.a: hello.o
        ar rcs $@ $^

hello.o: hello.c
        $(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

-include main.d hello.d