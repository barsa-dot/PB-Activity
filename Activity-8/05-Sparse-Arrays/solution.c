#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 21

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    char stringList[n][MAX_LEN];
    for (int i = 0; i < n; i++) {
        scanf("%s", stringList[i]);
    }

    int q;
    if (scanf("%d", &q) != 1) return 0;

    for (int i = 0; i < q; i++) {
        char query[MAX_LEN];
        scanf("%s", query);

        int count = 0;
        for (int j = 0; j < n; j++) {
            if (strcmp(stringList[j], query) == 0) {
                count++;
            }
        }
        printf("%d\n", count);
    }

    return 0;
}