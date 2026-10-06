#include <stdio.h>
#include <string.h>

int main() {
    int hh, mm, ss;
    char ampm[3];

    if (scanf("%2d:%2d:%2d%2s", &hh, &mm, &ss, ampm) == 4) {
        if (strcmp(ampm, "AM") == 0) {
            if (hh == 12) hh = 0;
        } else {
            if (hh != 12) hh += 12;
        }
        printf("%02d:%02d:%02d\n", hh, mm, ss);
    }

    return 0;
}