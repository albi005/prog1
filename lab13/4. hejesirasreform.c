#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add_char(char** s, char c) {
    size_t len = strlen(*s);
    len++;
    *s = realloc(*s, sizeof(char) * (len + 1));
    (*s)[len - 1] = c;
    (*s)[len] = 0;
}
 
int main(void) {
    typedef enum LyAllapot {
        alap, l_volt, ll_volt
    } LyAllapot;
    LyAllapot all;
    int c;

    char* s = malloc(sizeof(char));
    s[0] = 0;
 
    all = alap;
    while ((c = getchar()) != EOF) {
        switch (all) {
          case alap:
            if (c == 'l') all = l_volt;
            else add_char(&s, c);
            break;
 
          case l_volt:
            switch (c) {
                case 'l':
                    all = ll_volt; break;
                case 'y':
                    add_char(&s, 'j');
                    all = alap;
                    break;
                default:
                    add_char(&s, 'l');
                    add_char(&s, c);
                    all = alap;
                    break;
            }
            break;
 
          case ll_volt:
            switch (c) {
              case 'l':
                  add_char(&s, 'l');
                  break;
              case 'y':
                  add_char(&s, 'j');
                  add_char(&s, 'j');
                  all = alap;
                  break;
              default:
                  add_char(&s, 'l');
                  add_char(&s, 'l');
                  add_char(&s, c);
                  all = alap;
                  break;
            }
            break;
        }
    }
 
    printf("%s\n", s);
 
    return 0;
}

