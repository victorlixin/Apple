#
# makefile   for gawk
#


PROG=gawk

OBJS=   main.o eval.o builtin.o msg.o iop.o io.o field.o getopt1.o \
        getopt.o array.o alloca.o \
        node.o version.o missing.o re.o awktab.o regex.o dfa.o

CFLAGS+=-I.  -DGAWK -D__OPENNT


$(PROG): $(OBJS)
	$(CC) -o $(PROG) $(LDFLAGS) $(OBJS) -lm

alloca.o: alloca.c

clean:
	rm -f $(OBJS) $(PROG)
