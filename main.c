/**
* author: lukai
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void showImageSize(FILE *p);
int power(int num, int exp);
int hexToDec(int a[], int len);
void thresholdFilter(FILE *fp, char outputName[], float filter);

int width, height;

int main(int argc, const char * argv[]) {
    
    FILE *fp = NULL;
    char outputName[100];
    float t;
    int oFlag, tFlag, hFlag;

    fp = fopen(argv[argc-1], "rb");
    showImageSize(fp);
    rewind(fp);
    for (int counter = 1; counter < argc-1; counter++) {
        if (argv[counter][0] == '-') {
            switch (argv[counter][1]) {
                case 't':
                    tFlag = 1;
                    t = (float) atof(argv[counter + 1]);
                    break;
                case 'o':
                    oFlag = 1;
                    int len = strlen(argv[counter + 1]);
                    for(int i = 0; i < len; i++) {
                       outputName[i] = argv[counter + 1][i]; 
                    }
                    outputName[len] = '\0';
                    break;
                case 'h':
                    hFlag = 1;
                    break;
                default:
                    break;
            }
        }
    }

    if (tFlag) {
        if (!oFlag) {
            thresholdFilter(fp, "out.bmp", t);
        } else {
            thresholdFilter(fp, outputName, t);

        }
    }
    return 0;
}

void showImageSize(FILE *p) {
    int i = 0;
    int c;
    int widthArr[4], heightArr[4];
    while(1) {
        i++;
        c = fgetc(p);
        if (i > 18 && i < 23) {
            widthArr[i-19] = c;
        } else if (i > 22 && i < 27) {
            heightArr[i - 23] = c;
        } else if (i > 27) {
            break;
        }
    }
    width = hexToDec(widthArr, 4);
    height = hexToDec(heightArr, 4);
    printf("Image width: %d\n", width);
    printf("Image height: %d\n", height);
}

void thresholdFilter(FILE *fp, char outputName[], float filter) {
    int red, green, blue;
    int c;
    int size;
    int rowSize;
    int i = 0;
    // calculate row size
    size = (4 - ((width * 3) % 4)) % 4;
    rowSize = (width * 3) + size;
    
    FILE *ofp = NULL;
    ofp = fopen(outputName,"wb");

    while (1) {
        c = fgetc(fp);
        if (c == EOF) {
            break;
        }
        if (i >= 54 && ((i - 54) % rowSize) < width * 3) {
            i += 3;
            blue = c;
            green = fgetc(fp);
            red = fgetc(fp);
            float average = ((float) (red + green + blue))/3.0f;
            printf("%f  ", average);
            if (average > filter * 255) {
                red = 255;
                green = 255;
                blue = 255;
            } else {
                red = 0;
                green = 0;
                blue = 0;
            }
            fputc(blue, ofp);
            fputc(green, ofp);
            fputc(red, ofp);
        } else {
            i++;
            fputc(c, ofp);
        }

    }
    fclose(ofp);
    return;
}

int hexToDec(int a[], int len) {
    int rs = 0;
    for (int i = 0; i < len; i++ ) {
        a[i] *= power(16, i*2);
        rs += a[i];
    }
    return rs;
}

int power(int num, int exp) {
    int rs = 1;
    for (int i = 0; i < exp; i++) {
        rs *= num;
    }
    return rs;
}

