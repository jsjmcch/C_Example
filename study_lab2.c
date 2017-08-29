* 16 -> 2
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int hextobin(char *hex){
    int i,h;
    int len = strlen(hex)-1;
    int buf[4];

    while(len--)
    {
        printf("%c: ", *hex);
        if (isupper(*hex)) {
            h = *hex++ - 'A' + 10;
        } else if(islower(*hex)) {
            h = *hex++ - 'a' + 10;
        } else {
            h = *hex++ - 48;
        }

        for(i=3; i>=0; i--) {
            buf[i] = h % 2;
            h = h / 2;
        }

        for(i=0; i<4; i++) {
            printf("%d", buf[i]);
        }

        printf("\n");
    }

    return 0;
}

int main() {
    hextobin("c0131e30");
    return 0;
}


* result
$ ./hextobin.exe
c: 1100
0: 0000
1: 0001
3: 0011
1: 0001
e: 1110
3: 0011
