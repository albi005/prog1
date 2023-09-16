#include <stdio.h>
#include <stdbool.h>
#include <math.h>

void addArrow(FILE *f, double width, double height, double rotation, bool outer) {
    double x = width / 2;
    double startY = -outer;
    rotation = rotation + 180;
    if (outer)
        height = -1 + height;
    fprintf(f, "<path d=\"M %lf %lf H %lf L 0 %lf Z\" fill=\"url(#prefix__i)\" transform=\"rotate(%lf)\" />", x, startY, -x, height, rotation);
}

int main() {
    double hours, minutes, seconds;
    scanf("%lf %lf %lf", &hours, &minutes, &seconds);
    printf("%lf hours, %lf minutes, %lf seconds\n", hours, minutes, seconds);

    FILE *f = fopen("ora.svg", "w");
    fprintf(f, "<svg width=\"500\" height=\"500\" viewBox=\"-1.2 -1.2 2.4 2.4\" xmlns:xlink=\"http://www.w3.org/1999/xlink\"    xmlns=\"http://www.w3.org/2000/svg\">    <defs>        <filter id=\"shadow\">            <!-- from https://codepen.io/sdthornton/pen/wBZdXq -->            <!-- box-shadow: 0 19px 38px rgba(0,0,0,0.30), 0 15px 12px rgba(0,0,0,0.22); -->            <feDropShadow dx=\"0\" dy=\"\" stdDeviation=\".038\" flood-color=\"rgba(0,0,0,0.30)\" />            <feDropShadow dx=\"0\" dy=\".005\" stdDeviation=\".012\" flood-color=\"rgba(0,0,0,0.22)\" />        </filter>        <linearGradient id=\"prefix__c\">            <stop offset=\"0\" stop-color=\"#fff\" />            <stop offset=\"1\" stop-color=\"#fff\" stop-opacity=\"0\" />        </linearGradient>        <linearGradient id=\"prefix__a\" color-interpolation=\"linearRGB\" >            <stop offset=\"0\" stop-color=\"#000081\" />            <stop offset=\"1\" stop-color=\"blue\" />        </linearGradient>        <linearGradient xlink:href=\"#prefix__c\" id=\"prefix__i\" x1=\".5\" y1=\"0\" x2=\".5\" y2=\"1\"            gradientUnits=\"objectBoundingBox\" />        <radialGradient xlink:href=\"#prefix__a\" id=\"prefix__d\" cx=\".5\" cy=\".5\" fx=\".5\" fy=\".5\" r=\".5\"            gradientUnits=\"objectBoundingBox\" />    </defs>    <circle cx=\"\" cy=\"\" r=\"1\" fill=\"url(#prefix__d)\" style=\"filter:url(#shadow)\" />");

    addArrow(f, 0.01, 0.9, 360 * seconds / 60, false);
    addArrow(f, 0.02, 0.9, 360 * minutes / 60, false);
    addArrow(f, 0.04, 0.6, 360 * hours / 12, false);

    for (int i = 0; i < 60; i++) {
        if (i % 15 == 0)
            addArrow(f, 0.03, 0.3, i * 6, true);
        else if (i % 5 == 0)
            addArrow(f, 0.02, 0.2, i * 6, true);
        else
            addArrow(f, 0.01, 0.1, i * 6, true);
    }

    fprintf(f, "</svg>");
}
