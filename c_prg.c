#include <stdio.h>

int main() {
    float length, width, area, perimeter;

    // 1. Take inputs from the user
    printf("Enter the length of the rectangle: ");
    scanf("%f", &length);

    printf("Enter the width of the rectangle: ");
    scanf("%f", &width);

    // 2. Perform calculations based on mathematical formulas
    area = length * width;
    perimeter = 2 * (length + width);

    // 3. Display the final results (rounded to 2 decimal places)
    printf("\n--- Results ---\n");
    printf("Area of the rectangle: %.2f\n", area);
    printf("Perimeter of the rectangle: %.2f\n", perimeter);

    return 0;
}   