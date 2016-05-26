/**
* author: lukai
*/

#include <stdio.h>

int power(int num, int exp);
int hexToDec(char a[], int len);

int main(int argc, const char * argv[]) {
    FILE *fp = NULL;
    int i = 0;
    char c;
    char widthArr[4], heightArr[4];
    int width, height;
    fp = fopen("cup.bmp", "rb");
    fseek(fp, 0, 0);
    while(fscanf(fp, "%c", &c) != EOF) {
        i++;
        if (i > 18 && i < 23) {
            widthArr[i-19] = c;
        } else if (i > 22 && i < 27) {
            heightArr[i - 23] = c;
        } else if (i > 27) {
            break;
        }
    }
    for (int count = 0; count < 4; count++) {
        height += heightArr[count] * power(16, 2*count);
        width += widthArr[count] * power(16, 2*count);
    }
    printf("width: %d", width);
    printf("height: %d", height);
}

int hexToDec(char a[], int len) {
    int rs = 0;
    for (int i = 0; i < len; i++ ) {
        a[i] *= power(16, i*2);
        rs += a[i];
        printf("rs: %d\n",rs);
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

