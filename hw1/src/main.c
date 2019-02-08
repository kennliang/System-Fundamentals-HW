#include <stdio.h>
#include <stdlib.h>

#include "const.h"
#include "debug.h"

#ifdef _STRING_H
#error "Do not #include <string.h>. You will get a ZERO."
#endif

#ifdef _STRINGS_H
#error "Do not #include <strings.h>. You will get a ZERO."
#endif

#ifdef _CTYPE_H
#error "Do not #include <ctype.h>. You will get a ZERO."
#endif

int main(int argc, char **argv)
{
    int ret;
    // if returns 0 then doesn't execute
    if(validargs(argc, argv))
    {
        USAGE(*argv, EXIT_FAILURE);
    }
    debug("Options: 0x%x", global_options);

    // h flag provided
    if((global_options & 1))
    {
        USAGE(*argv, EXIT_SUCCESS);
        //printf("%s\n","executed");
    }
    // c flag provided
    else if(global_options & 0x2)
    {
        compress();
        //printf("%s\n","executed");
        //USAGE(*argv, EXIT_SUCCESS);
    }
    // d flag provided
    else if(global_options & 0x4)
    {

    }
    // printf("%s\n","executed");
     return EXIT_SUCCESS;
}

/*
 * Just a reminder: All non-main functions should
 * be in another file not named main.c
 */
