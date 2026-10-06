#include <stdio.h>
#include <stdlib.h>

int diagonalDifference(int n, int arr[n][n]) {
    int primarySum = 0;
    int secondarySum = 0;

    for (int i = 0; i < n; i++) {
        primarySum += arr[i][i];
        secondarySum += arr[i][n - 1 - i];
    }

    return abs(primarySum - secondarySum);
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    int arr[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &arr[i][j]);
        }
    }

    printf("%d\n", diagonalDifference(n, arr));
    return 0;
}