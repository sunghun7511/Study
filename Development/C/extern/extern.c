#include <stdio.h>
#include <stdlib.h>

#include "values.h"

int main(int argc, char *argv[]){
    int i;
    
    for(i = 0 ; i < max_amount ; i ++){
        printf("Hi! (%d)\n", i+1);
    }

    return EXIT_SUCCESS;
}

/*

output

Hi! (1)
Hi! (2)
Hi! (3)
Hi! (4)
Hi! (5)
Hi! (6)
Hi! (7)
Hi! (8)
Hi! (9)
Hi! (10)

*/