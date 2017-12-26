
#include <stdarg.h>
#include <stdio.h>

void
foobar(char *args, ...)
{
    va_list ap;
    int i = 0;

fprintf(stderr, "in foobar()\n");

    va_start(ap, args);
    while (args != 0) {
    	printf("arg[%d] = %s\n", i, args);
	args = va_arg(ap, char *);
	i++;
    }

fprintf(stderr, "about to do VFPRINTF\n");
    va_start(ap, args);
    vfprintf(stderr, "arg1 = %s, arg2 = %s\n", ap);
fprintf(stderr, "\ndone VFPRINTF\n");

}



main()
{
	foobar ("one", "two", "three", NULL);
}


#ifdef MY_VFPRINTF
vfprintf()
{
	return 1;
}
#endif
