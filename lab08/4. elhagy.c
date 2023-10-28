#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debugmalloc.h"

// egy uj string-be beirja s start-nal kisebb indexu es end-nel nagyobb/egyenlo indexu karaktereit.
// a visszaadott stringet fel kell szabaditani.
char *elhagy(char *s, int start, int end) {
    int len = strlen(s);
    int l1 = start;
    int l2 = len - end;
    len = l1 + l2 + 1;
    char *new = (char*)malloc(len * sizeof(char*));
    strncpy(new, s, l1);
    strncpy(new + l1, s + end, l2);
    new[len - 1] = (long)NULL;
    return new;
}
    
int main() {
    char *s = "hello, vilag";
    char *uj = elhagy(s, 4, 8);
 
    printf("%s\n", uj);

    free(uj);
}
