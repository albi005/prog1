#include <stdio.h>

typedef struct Point {
    double x, y;
} Point;

Point felezo(Point a, Point b) {
    return (Point) {
        (a.x + b.x) / 2,
        (a.y + b.y) / 2
    };
}

int main() {
    Point a = { 2.2, 1.6 };
    Point b;
    scanf("b.x = %lf", &b.x);
    scanf("b.y = %lf", &b.y);

    Point c = felezo(a, b);
    printf("Felezőpont = (%g ; %g)", c.x, c.y);
}

