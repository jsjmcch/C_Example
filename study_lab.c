프로그램 명: calfflac

문장 속에 포함된 가장 큰 palindrome 을 찾는 문제이다.
문장속에 포함된 A-Z 과 a-z 만을 고려하고 대소문자는 고려하지 않는다.
문장의 전체 문자수는 20,000 을 넘지 않고 , 또한 가장 큰 palindrome 은 원 문장에서 특수문자를 제거하지 않은 상태에서 2,000 문자를 넘지 않는다고 하자.

입력
입력은 20,000 문자를 넘지 않는다. 여러 줄에 걸쳐서 입력될 수도 있다.

출력
출력은 첫 째줄에는 palindrome 을 이루는 문자의 크기를 출력하고 다음 줄에는 palindrome 을 이루는 특수문자나 숫자등을 제거하지 않은 원 문장을 출력한다.

입출력 예
입력
Confucius say: Madam, I'm Adam.
출력
11
Madam, I'm Adam


* answer #1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_SIZE 20000
#define MAX_ANS_SIZE 2000

int main(void) {
    int i, j;
    int center, back, front, spchCnt;
    int size = 0, diffLen = 0, retLen = 0;
    char buf[MAX_SIZE + 1] = { 0 };
    char tmpBuf[200] = { 0 };
    char result[MAX_ANS_SIZE + 1] = { 0 };

    // input Data
    printf("insert text : ");
    while (1) {
        fgets(tmpBuf, sizeof(tmpBuf), stdin);
        if (strncmp(tmpBuf, "exit", 4) == 0) break; // input exit if quit.
        else {
            strcat(buf, tmpBuf);
            if (strlen(buf) > MAX_SIZE) {
                printf("input data is too long\n");
                return EXIT_FAILURE;
            }
        }
    }

    size = strlen(buf);

    // Data compare
    for (center = 0; center < size - 1; center++) {
        spchCnt = 0;    // special char count
        for (back = 1, front = 1;
                (center - back >= 0) && (center + front <= size - 1);
                    back++, front++)
        {
            // i를 기준 앞뒤로 특수문자를 제외한 알파벳 back, front index 구함
            // back index move
            while ((center - back >= 0) && (isalpha(buf[center-back]) == false)) {
                spchCnt++;
                back++;
            }
            // front index move
            while ((center + front <= size - 1) && (isalpha(buf[center+front]) == false)) {
                spchCnt++;
                front++;
            }

            // if equal,
            if (tolower(buf[center-back]) == tolower(buf[center+front])) {
                if (front + back + 1 > diffLen) {
                    diffLen = front + back + 1;
                    memset(result, 0x0, strlen(result));
                    strncpy(result, &buf[center-back], diffLen);    // copy palindrome
                    retLen = diffLen - spchCnt;                     // save palindrome length
                    if (strlen(result) > MAX_ANS_SIZE) {
                        printf("palindrome is too long\n");
                        return EXIT_FAILURE;
                    }
                }
            }
            else break;
        }
    }

    printf("%d\n", retLen);
    printf("%s\n", result);

    return EXIT_SUCCESS;
}

* answer #2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* palindrome_normalize(char* str)
{
        int len = strlen(str);
        char* p = (char*)malloc(len + 1);
        char* s = str;
        char* d = p;

        while (*s)
        {
                if (isalpha(*s))
                {
                        *d = tolower(*s);
                        d++;
                }
                s++;
        }
        *d = '\0';
        return p;
}

char* strdup_reverse(char* str)
{
        int len = strlen(str);
        char* r = (char*)malloc(len + 1);
        char* s = str + len - 1;
        char* d = r;

        while (s >= str)
                *d++ = *s--;
        *d = '\0';
        return r;
}

int get_diff_index(char* s1, char* s2)
{
        int idx;

        for (idx = 0; *s1 && *s2; s1++, s2++, idx++)
        {
                if (*s1 != *s2)
                        return idx;
        }
        return idx;
}

void print_palindrome(char* str, int index, int length)
{
        int i;
        char* p = str;

        for (i = 0; i < index && *p; p++)
        {
                if (isalpha(*p))
                        i++;
        }
        while (*p && !isalpha(*p))
                p++;

        printf("%d\n", length);
        for (i = 0; i < length && *p; p++)
        {
                printf("%c", *p);
                if (isalpha(*p))
                        i++;
        }
}

int main(int argc, char* argv[])
{
        char* origin;
        char* normal;
        char* reverse;
        int length;
        int palindrome_idx = -1;
        int palindrome_len = 0;
        int i, j;

        if (argc < 2)
                exit(1);

        origin = strdup(argv[1]);
        normal = palindrome_normalize(origin);
        reverse = strdup_reverse(normal);
        length = strlen(normal);
        if (length < 3)
        {
                printf("not enough string.\n");
                goto done;
        }

        for (i = 0; i < length-2; i++)
        {
                for (j = 0; j < length-2; j++)
                {
                        int idx = get_diff_index(normal+i, reverse+j);

                        if (idx > 2 && idx > palindrome_len)
                        {
                                palindrome_idx = i;
                                palindrome_len = idx;
                        }
                }
        }

        if (palindrome_idx >= 0 && palindrome_len > 0)
                print_palindrome(origin, palindrome_idx, palindrome_len);
done:
        free(origin);
        free(normal);
        free(reverse);
        return 0;
}
=======================================================================================
프로그램 명: rbit(open)
입력받은 16진수를 바이트로 표현했을 때, 그 바이트 값을 거꾸로 뒤집는 문제이다.

입력받은 16진수가 72라면 비트 값은 다음과 같다.
0 1 1 1 0 0 1 0

이것을 비트 단위에서 역순으로 뒤집으면 다음과 같다. (엔디안 표기법에서 바이트 단위를 뒤집는 것과 다르다.)
0 1 0 0 1 1 1 0

이것을 16진수로 나타내면 4E가 된다.

입력
16진수 두 자리를 입력으로 받는다.

출력
비트를 뒤집은 16진수를 출력한다. 문자의 경우 대문자로 출력한다.

입출력 예시
입력
72
출력
4E

* answer #1
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]) {
    int i,j;
    long int input = 0;
    char buf[50] ={0};
    char *ptr;
    div_t divresult;

    if (argc < 2 || argc > 2) {
        printf("argc error\n");
        return -1;
    }

    if (strlen(argv[1]) != 2) {
        printf("input 2digit, please\n");
        return -1;
    }

    printf("입력 : \n");
    printf("%s\n", argv[1]);

    input = strtol(argv[1], &ptr, 16);

    i = 0;
    while(i<=7) {
        divresult = div(input,2);
        buf[i] = divresult.rem + '0';
        input = divresult.quot;
        i++;
    }

    input = strtol(buf, &ptr, 2);
    printf("출력 : \n");
    printf("%x", input);

    return 0;
}

* answer #2
 
#include <stdio.h>
#include <string.h>

char hex_reverse_lookup[16] = {
        '0', '8', '4', 'C',
        '2', 'A', '6', 'E',
        '1', '9', '5', 'D',
        '3', 'B', '7', 'F'
};

int main(int argc, char* argv[])
{
        char* hex;
        int len;
        int i;

        if (argc < 2)
                return 1;

        hex = argv[1];
        len = strlen(hex);
        for (i = len-1; i >= 0; i--)
        {
                int val = 0;
                if (hex[i] >= '0' && hex[i] <= '9')
                        val = hex[i] - '0';
                else if (hex[i] >= 'A' && hex[i] <= 'F')
                        val = hex[i] - 'A' + 10;
                else if (hex[i] >= 'a' && hex[i] <= 'f')
                        val = hex[i] - 'a' + 10;
                else
                        printf("\ninvalid hex value %c\n", hex[i]);
                printf("%c", hex_reverse_lookup[val]);
        }
        printf("\n");
        return 0;
}

* answer #3
#include <stdio.h>
#include <math.h>

int main(void)
{
 short nInput, i;
 short nMask;
 char szHex[9] = {0,};
 short nOutput;

 scanf("%X",&nInput);
 for (i=0; i<8; i++)
 {
 	nMask = (1 << (7-i));
  	if (nInput & nMask)
  	{
   		szHex[i] = '1';
  	}
  	else
  	{
   		szHex[i] = '0';
  	}
 }

 nOutput = 0;
 for (i=0; i<8; i++)
 {
  	if (szHex[i] == '1')
  	{
   		nOutput += pow(2,i);
  	}
 }
 printf("%X\n",nOutput);
 return 0;
}


=======================================================================================
Exercise 문제 #2 - Log Parsing
이번 연습 문제에서는 access.log 파일을 파싱하여 URL 호출 성공 횟수와 이미지 파일 호출 횟수를 세는 프로그램을 작성한다.

 


<요구사항>
1. access.log 파일을 읽어 들여 문자열을 파싱한다.
2. HTTP 상태 값이 200(성공)인 라인의 수를 센다.
3. 이미지 파일이 호출된 라인 수를 센다. (HTTP 상태와는 상관 없음)
 그림 파일은 대소문자 구분 없이 jpg, gif, png 확장자로 끝난다. 단, 디렉토리가 /png/와 같이 포함된 경우도 있다.
4. access.log 파일은 아래와 같은 형태로 구성되어 있다.

* answer #1 
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    int i,j;
    char buf[200] = {0,};
    char *ptr;
    int count1 = 0, count2 = 0;
    char acSrh1[2][20] = {"HTTP/1.1\" 200","HTTP/1.0\" 200"};
    char acSrh2[6][10] = {".jpg",".JPG", ".gif", ".GIF", ".png",".PNG"};

    FILE *fp = NULL;

    fp = fopen("access.log", "r");
    if( fp == NULL ) {
        printf("fp is NULL\n");
        return -1;
    }

    while( !feof(fp) ) {
        fgets(buf, sizeof(buf), fp);
        for(i=0; i<sizeof(acSrh1)/sizeof(acSrh1[0]); i++) {
            ptr = strstr(buf,acSrh1[i]);
            if (ptr != NULL) {
                count1++;
                break;
            }
        }
        for(i=0; i<sizeof(acSrh2)/sizeof(acSrh2[0]); i++) {
            ptr = strstr(buf,acSrh2[i]);
            if (ptr != NULL) {
                count2++;
                break;
            }
        }
    }

    printf("Result Status 200 count is %d\n", count1);
    printf("Image file count is %d\n", count2);

    fclose(fp);

    return 0;
}

=======================================================================================
수식이 주어질 때 같은 짝의 괄호의 위치를 찾는 문제이다. stack을 활용하여 문제를 풀어주세요.
(a*(b+c)+d) 

이 경우에는 3 과 7 , 0 과 10 이 한 쌍의 괄호이다. 

입력 
입력은 공백없이 입력된다. 입력되는 문자는 소문자,소괄호,(+,-,*,/)이다. 
문자열의 길이는 최대 50 까지이다. 

출력 
왼쪽에서 오른쪽을 가면서 먼저 짝이 맞는 (여는 괄호 위치, 닫는 괄호 위치) 순으로 출력하고, 짝이 맞지 않는 수식은 not match 를 출력한다. 

입 출력 예
입력
(a*(b+c)+d)
출력
3 7
0 10

* answer #1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 30

typedef struct _susik {
    int buf[MAX_SIZE];
    int top;
} susik;

susik sk;

bool is_empty() {
    if (sk.top == -1) return true;
    else return false;
}

bool is_full() {
    if (sk.top >= MAX_SIZE - 1) return true;
    else return false;
}

bool push(int num) {
    if(is_full()) {
        printf("stack is full!\n");
        return false;
    }
    else {
        sk.top++;
        sk.buf[sk.top] = num;
        return true;
    }
}

int pop() {
    int num;
    if(is_empty()) {
        printf("stack is empty!\n");
        return false;
    }

    num = sk.buf[sk.top];
    sk.top = sk.top - 1;

    return num;
}

int main(void) {
    int i,j;
    char array[50];
    int num;

    sk.top = -1;
    memset(sk.buf, 0x0, sizeof(sk.buf));

    printf("insert susik :\n");
    fgets(array, sizeof(array), stdin);

    //printf("array = %s\n", array);

    for(i=0; i<strlen(array); i++) {
        if (array[i] == '(')
            push(i);
        else if (array[i] == ')') {
            num = pop();
            printf(" %d %d\n", num, i);
        }
    }

    if (is_empty() != true) {
        printf("it's not match.\n");
    }

    return 0;
}
=======================================================================================
공백을 기준으로 단어 별 역순으로 출력하는 프로그램을 작성하시오. 

입력
입력되는 수의 첫 수는 공백이 아니고 각 단어 사이에는 공백이 하나씩만 존재 한다. 
한 줄에 최대 80 자까지 입력될 수 있고 , 단어는 하나 이상이다. 

출력
단어별 역순으로 출력한 값을 공백 하나를 사이에 두고 출력한다. 

입출력 예
입력
I like spring.
출력
I ekil .gnirps 

* answer #1
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char cache[80];
int cache_size = 0;

static void cache_put(char c)
{
        cache[cache_size++] = c;
}

static void cache_flush()
{
        if (cache_size > 0)
        {
                int i;
                for (i = cache_size - 1; i >= 0; i--)
                        printf("%c", cache[i]);
                printf(" ");
                cache_size = 0;
        }
}

int main(void)
{
        char buf[81];
        char* p;

        while ((p = fgets(buf, sizeof(buf), stdin)) != NULL)
        {
                while (*p)
                {
                        if (isspace(*p))
                                cache_flush();
                        else
                                cache_put(*p);
                        p++;
                }
                cache_flush();
                printf("\n");
        }
        return 0;
}

* answer #2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[] ) {
    char* buf[81];
    memset(buf, 0x00, 81);

    if(argc < 2 || argc > 81) {
        printf("argc error\n");
        return -1;
    }

    for(int i=1;i<argc;i++) {
        buf[i-1]= argv[i];

        int strlength = strlen(buf[i-1]);
        for(int j=strlength-1;j>=0;j--) {
            printf("%c", buf[i-1][j]);
        }
        printf(" ");
    }
    printf("\n");
    return EXIT_SUCCESS;
}

* answer #3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]) {
    int i,j,k,len;
    char *ptr = NULL;
    char *array[80] = {NULL, };

    if (argc < 2 || argc > 81) {
        printf("argc error\n");
        return -1;
    }

    strcpy(buf, argv[1]);

    ptr = strtok(buf, " ");
    i = 0;
    while( ptr != NULL) {
        array[i] = (char *) malloc(sizeof(char)*50);
        strcpy(array[i], ptr);
        ptr = strtok(NULL, " ");
        i++;
    }

    for(j=0; j<i; j++) {
        len = strlen(array[j]);
        for(k=len; k>=0; k--) {
            printf("%c", array[j][k]);
        }
        printf(" ");
    }

    for(j=0; j<i; j++) {
        free(array[j]);
    }

    return 0;
}
=======================================================================================
10 진수를 입력으로 받아 이 수를 해당 진법으로 변환하는 프로그램를 작성하시오. 

입력
첫 수는 10 진수 d , 두 번째 수는 바꿀 진법 r 이다. d 는 10000 이하의 자연수이고 , r 은 2 이상 24 이하의 자연수이다. 
수는 0 , 1 , 2 , ... , 9 , A , B , C .... 

출력
공백없이 한줄에 출력한다. 

입출력 예
입력
32 16 

출력
20

* answer #1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
        int i,j;
        int digit,jinbub;
        div_t divresult;
        char buf[30] = {0,};

        printf("insert two values :\n");
        scanf("%d %d", &digit, &jinbub);

        // validation check
        if ( digit > 10000) {
                printf("insert digit(d<=10000), please\n");
                return -1;
        }
        if ( jinbub < 2 || jinbub > 24) {
                printf("insert digit( 2 <= r && r <= 24), please\n");
                return -1;
        }

        i = 0;
        while ( digit > 0 ) {
                divresult = div(digit,jinbub);
                buf[i] = divresult.rem + '0';
                if (buf[i] > '9') buf[i] = buf[i] + 7;
                digit = divresult.quot;
                i++;
        }

        printf("output \n");
        for(j=i-1; j>=0; j--) {
                printf("%c", buf[j]);
        }

        return 0;
}

* answer #2
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[] ) {
    char buf[200] = {0,};

    if(argc < 3 || argc > 4) {
        printf("argc error\n");
        return -1;
    }
    int input = atoi(argv[1]);
    if(input < 0 || input > 10000) {
        printf("argu1 error\n");
        return -1;
    }

    int rad = atoi(argv[2]);
    if(rad < 2 || rad > 24) {
        printf("rad error\n");
        return -1;
    }

    int num = input;
    int pos = 0;

    while(1) {
        int a = num / rad;
        int b = num % rad;

        if(b < 10) {
            buf[pos] = '0'+b;
        }
        else {
            buf[pos] = 'A'+b-10;
        }

        if(a != 0) {
            num = a;
            pos++;
        }
        else
            break;
    }

    for(int i=pos;i>=0;i--) {
        printf("%c", buf[i]);
    }
    printf("\n");
    return EXIT_SUCCESS;
}
=======================================================================================
0 과 1 사이의 분수가 입력으로 주어질 때 소수이하 k 자리까지 출력하는 문제이다.

입력
세 수가 입력으로 주어진다.
차례대로 분자, 분모 ,표현할 소수이하 자리 k 이다. 세수 모두 1000 이하의 자연수이다.

출력
출력 예의 형식으로 출력한다.
소수이하 유효자리를 포함하는 것은 보장되고 반올림은 하지 않는다.

입출력 예
입력
6 7 2
출력
0.85

* answer 
#include <stdio.h>

#include <stdlib.h>

#include <string.h>

 

#define MAX 1010

int main(void) {
    int i,j;
    int bunja, bunmo, sosu;
    char buf[MAX] = {0,};
    char mok,nam;

    printf("insert data : ");
    scanf("%d %d %d", &bunja, &bunmo, &sosu);

    if (bunja > 1000 || bunmo > 1000 || sosu > 1000) {
        printf("input num is too big(num < 1000)\n");
        return -1;
    }

    for(i=0;i<sosu;i++) {
        mok = (bunja*10) / bunmo;
        nam = (bunja*10) % bunmo;
        bunja = nam;
        buf[i] = mok + '0';
    }
    buf[sosu] = '\0';

    printf("result = 0.%s\n", buf);

    return 0;
}
=======================================================================================
안정된 형태로 통나무를 쌓기 위해서는 아래 그림과 같이 최하단 부터 쌓기 시작하여 한 층 위로 올라갈 때 마다 
통나무 개수가 한 개씩 줄어 들도록 해야 한다. 이 때 최상단에 놓인 통나무의 수는 바로 아래 층의 통나무 개수보다 한 개 이상 적다.

OO
OOOO
OOOOO
OOOOOO

N 개의 통나무를 안정된 형태로 쌓으려고 할 때, 최 상단에 놓일 수 있는 통나무의 개수와 이 때 최하단에 놓이는 통나무의 개수를 
구하는 프로그램을 작성하시오. 단, 가능한 최하단에 놓이는 통나무의 수를 최소로 하는 답을 구하여 야 한다.

입력 형식
통나무의 개수가 입력된다. 통나무의 개수는 300 이하의 자연수이다.

출력 형식
최 하단과 최 상단에 놓일 통나무 수를 출력한다.

입출력 예
입력 
18
출력 
6 3

입력 
19
출력 
6 1

* answer #1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int i,j;
    int nVal, nTmp = 0;
    int sum = 0;
    int lowLogCount = 0;
    int highLogCount = 0;


    printf("insert logcount to stack : ");
    scanf("%d", &nVal);

    nTmp = nVal / 2;

    for (j=0; j < nVal/2; j++) {
        for (i=nTmp; i>0; i--) {
            sum += i;
            // 합이 통나무 총 개수와 같으면 값 저장
            if (sum == nVal) {
                highLogCount = i;   // 맨 위 통나무 수
                lowLogCount = nTmp; // 맨 아래 통나무 수
                break;
            }
            else if (sum > nVal) {  // 합이 통나무 총 개수보다 큰경우
                highLogCount = i - (sum - nVal);    // 현재층의 통나무 수 - (over된 통나무)
                lowLogCount = nTmp; // 맨 아래 통나무 수
                break;
            }
        }

        sum = 0;
        nTmp--;
    }

    printf("output : %d, %d\n", lowLogCount, highLogCount);
    return 0;
}
=======================================================================================
영어 대소문자와 띄어쓰기(빈칸)만으로 이루어진 문장이 주어진다. 
이 문장에는 몇 개의 단어가 있을까? 이를 구하는 프로그램을 작성하시오. 
단, 단어는 띄어쓰기(빈칸)로 구분된다고 생각한다. 빈칸은 문장의 맨 앞에도 올 수 있다. 

예제 입력 : I am a boy.
예제 출력 : 4
 
* answer #1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int i,j;
    char buf[40] = {0,};
    char* pch = NULL;
    int count = 0;

    printf("insert data to parse : ");
    fgets(buf, 40, stdin);
    
    pch = strtok(buf, " ");
    while (pch != NULL) {
        count++;
        pch = strtok(NULL, " ");
    }
    printf("total word count : %d\n", count);
    return 0;
}

* answer #2
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[] ) {
    if(argc < 2) {
        printf("argc error\n");
        return -1;
    }
    printf("%d\n", argc-1);

    return EXIT_SUCCESS;
}
=======================================================================================
연산자 우선수위

* 단항연산자
==============
1. 단항연산자
 --(감소)
 ++(증가)
 !(논리 not)
 ~(비트 not)

* 이항연산자
=============
2. 산술연산자
 *, /, %, +, -

3. 시프트연산자
 <<, >>

4. 관계연산자
 <, <=, >=, >, ==, !=

5. 비트연산자
 &(and), ^(xor), |(or)

6. 논리연산자
 &&(논리 and), ||(논리 or)

* 삼항연산자
=============
7. 조건연산자 
 ?:

8. 대입연산자
 >>=, <<=, %=, /=, *=, -=, =

9. 순서연산자
 ,
=======================================================================================
1. 1부터 순서대로 입력된 긴 숫자가 있다. 
123456789101112131415161718192021... 

맨 왼쪽의 1을 첫 번째 자리로 시작하여, n 번째 자리에 무슨 숫자가 있는지 출력하시오. 
위의 수열에서 예를 들면, 1을 첫 번째 자리로 하였을 때, n=3이면 3이고, n=25일 경우 7임을 알 수 있다. 

입력
정수 n 이 입력된다. 1 <= n < 1,000,000 

출력
n 번째 수를 출력한다. 

입출력 예
입력
3
출력
3
입력
25
출력
7
* answer #1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(void) {
    int i,j,k;
    char *ptr = NULL;
    int findNum = 0;
    char buf[10] = {0,};
    int len = 0;

    printf("insert data to find value : \n");
    scanf("%d", &findNum);

    if (findNum < 1 || findNum > 1000000) {
        printf("please input 1 <= n < 1000000\n");
        return -1;
    }

    ptr = malloc(sizeof(char) * findNum + 1);

    j = 1;
    for (i=0; i < findNum;) {
        sprintf(buf, "%d", j);
        len = strlen(buf);
        k = 0;
        while (k < len) {
            ptr[i++] = buf[k++];
        }
        memset(buf, 0x0, 10);
        j = j + 1;
    }

    printf("find num = %c\n", ptr[findNum-1]);
    return 0;
}

* answer #2

=======================================================================================
2. 프로그램 명: rank_sort 요즘은 공정성과 정확성을 위해 대부분 컴퓨터를 이용해 채점을 한다. 
각 개인별로 채점이 끝나고, 마지막 작업으로 각 사람들의 순위를 정해주고자 한다. 
물론 점수가 높은 사람이 순위가 더 높다. 
예를들어 85점, 105점, 92점을 받았다면, 각각 3등, 1등, 2등이다. 
드물게 동점자가 나오는 경우도 있다. 예로 90, 100, 90, 80 점을 맞은 경우에는, 2등, 1등, 2등, 4등으로 처리하도록 한다. 
입력•첫째 줄에는 사람의 수 N(1000 이하 정수)이 주어진다. •다음줄부터는 각 사람의 점수가 주어진다. 점수는 1000 이하의 정수이다. 
출력입력된 순서대로 각 사람이 몇 등인지를 출력한다. 
입출력 예
입력
597
65
84
84
91

출력 
15332

* answer #1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _score {
    int jumsu;
    int grade;
} score;

int main(void) {
    int i,j;
    int tmp = 0;
    int count = 0;
    int grade = 0;

    score sc[10] = {0,};
    score sc1[10] = {0,};

    printf("input count : \n");
    scanf("%d", &count);

    for (i=0; i < count; i++) {
        scanf("%d", &sc[i].jumsu);
        sc[i].grade = 1;
    }

    for (i=0; i < count; i++) {
        sc1[i].jumsu = sc[i].jumsu;
        sc1[i].grade = sc[i].grade;
        //memcpy(&sc1[i], &sc[i], sizeof(sc));
    }

    // 정렬
    for (i=0; i < count-1; i++) {
        for (j=0; j < count-1-i; j++) {
            if (sc[j].jumsu > sc[j+1].jumsu) {
                tmp = sc[j].jumsu;
                sc[j].jumsu = sc[j+1].jumsu;
                sc[j+1].jumsu = tmp;
            }
        }
    }

    // 동일점수 처리
    for (i=4; i > 0; ) {
        if (sc[i].jumsu == sc[i-1].jumsu) {
            sc[i].grade = count - i;
            sc[i-1].grade = count - i;
            i = i - 1;
        }
        else {
            sc[i].grade = count - i;
        }
        i = i - 1;
    }
    sc[i].grade = count;    // 마지막 등수 입력

    // 원순서대로 점수 저장
    for (i=0; i < count; i++) {
        for (j=0; j < count; j++) {
            if (sc1[i].jumsu == sc[j].jumsu) {
                sc1[i].grade = sc[j].grade;
            }
        }
    }

    // 출력
    for (i=0; i < count; i++) {
        printf("%d ", sc1[i].grade);
    }

    return 0;
}
=======================================================================================
1. 한 줄로 된 직사각형 건물들의 천장에 가로 스트로크를 사용하여 페인트를
    칠할 때 모든 벽면을 칠할 수 있는 최소 획의 수를 구하는 프로그램을 완성하시오.
  * 요구사항
   - 가로 스트로크는 한번의 붓칠로 같은 높이의 연속된 벽면을 칠할 수 있다.
   - 건물들은 모두 같은 너비이지만 높이는 다를 수 있다.
   - 건물 N개의 높이를 저장한 배열 A가 제공된다.
   - 만약 스트로크 수가 1,000,000,000개를 넘어가면 -1을 출력한다.


  * 예시
   $./stroke.exe
     buildings high : 1 3 1 3 2 1
     stroke : 5
     buildings high : 1 2 3 4 3 2 1
     stroke : 4
     buildings high : 1 2 3 4 1 2 3 4
     stroke : 7

* answer #1
/*
 * 한 줄로 된 직사각형 건물들의 천장에 가로 스트로크를 사용하여 페인트를
 * 칠할 때 벽면을 칠할 수 있는 최소 획의 수를 구하는 프로그램을 완성하시오.
 *
 * 요구사항
 * - 가로 스트로크는 한번의 붓칠로 같은 높이의 연속된 벽면을 칠할 수 있다.
 * - 건물들은 모두 같은 너비이지만 높이는 다를 수 있다.
 * - 건물 N개의 높이를 저장한 배열 A가 제공된다.
 * - 만약 스트로크 수가 1,000,000,000개를 넘어가면 -1을 출력한다.
 *
 */

#include <stdio.h>
#include <stdlib.h>

int stroke_count(int A[], int N);
void print_array(int arr[], int len);

int main(void) {
	int skyline1[] = { 1, 3, 1, 3, 2, 1 };
	int skyline2[] = { 1, 2, 3, 4, 3, 2, 1 };
	int skyline3[] = { 1, 2, 3, 4, 1, 2, 3, 4 };

	print_array(skyline1, sizeof(skyline1)/sizeof(int));
	//빌딩들을 모두 칠하기 위해서 필요한 최소 스트로크 수를 출력한다.
	printf("stroke: %d\n", stroke_count(skyline1, sizeof(skyline1)/sizeof(int)));

	print_array(skyline2, sizeof(skyline2)/sizeof(int));
	//빌딩들을 모두 칠하기 위해서 필요한 최소 스트로크 수를 출력한다.
	printf("stroke: %d\n", stroke_count(skyline2, sizeof(skyline2)/sizeof(int)));

	print_array(skyline3, sizeof(skyline3)/sizeof(int));
	//빌딩들을 모두 칠하기 위해서 필요한 최소 스트로크 수를 출력한다.
	printf("stroke: %d\n", stroke_count(skyline3, sizeof(skyline3)/sizeof(int)));

	return EXIT_SUCCESS;
}

/*
 * 건물의 높이를 저장한 N개의 길이를 가진 배열 A를 바탕으로 최소 스트로크 수를 구하는 함수
 * @param A: 건물의 높이를 저장한 배열
 * @param N: 배열의 길이
 * @return: 최소 스트로크의 수
 */
int stroke_count(int A[], int N)
{
	  int stroke = 0;
	  int curr_high = 0;
	  int i;

	  for (i = 0; i < N; i++) {
	      if (curr_high < A[i]) {
	    	  // 다음 빌딩의 높이가 현재 건물 높이보다 높을 경우
	    	  // 스트로크가 추가 된다.
	    	  // ex) 2층 -> 3층: 1개의 스트로크 추가가 필요함
	    	  printf("curr_high=%d, A[%d]=%d \n", curr_high, i, A[i]);
	          stroke += A[i] - curr_high;

	          // 스트로크 최대 값 확인.
	          if (stroke > 1000000000) {
	            return -1;
	          }
	      }
	      //현재 건물의 높이를 갱신
	      curr_high = A[i];
	  }

	  return stroke;
}

/*
 * 배열의 모든 원소를 출력한다.
 * @param A: 건물의 높이를 저장한 배열
 * @param N: 배열의 길이
 */
void print_array(int arr[], int len) {
	int i;
	printf("buildings high: ");
	for(i=0; i<len; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

* answer #2
int stroke_count(int A[], int N)
{
	int i, k, nMax = 0;
	int sum = 0;
	int nCount = 0;
	int nStart = 0, nEnd;
	unsigned char **buf;

	for (i = 0; i<N; i++)
	{
		if (nMax < A[i])
			nMax = A[i];
	}

	buf = (unsigned char **)malloc(sizeof(unsigned char*) * N);
	if (buf == NULL) {
		printf("buf is not alloced!\n");
		return EXIT_FAILURE;
	}

	for (i = 0; i<N; i++)
	{
		buf[i] = (unsigned char *)malloc(sizeof(unsigned char) * nMax);
		if (buf[i] == NULL) {
			printf("buf[i] is not alloced!\n");
			return EXIT_FAILURE;
		}

		memset(buf[i], 0x0, nMax);
	}

	// stroke 가 있으면 1로 채운다 
	for (i = 0; i<N; i++)
	{
		for (k = 0; k<A[i]; k++)
		{
			buf[i][k] = 1;
			printf("%d ", buf[i][k]);
		}
		printf("\n");
	}

	for (i=0; i<nMax; i++)
	{
		for (k=0; k<N-1; k++)
		{
			if (buf[k][i] < buf[k+1][i]) nCount++;
			sum += buf[k][i];
		}
		sum += buf[k][i];
		if (sum == N) nCount++;	// 0->1 혹은 모두 1인같嚥荑〉?증가   
	}

	// 메모리 해제
	for (i = 0; i<N; i++)
	{
		free(buf[i]);
	}

	free(buf);

	return nCount;
}


=======================================================================================
2. 양의 정수를 입력 했을 때 그 수의 최대 Binary Gap을 구하는 프로그램을 작성한다.
 * 요구사항.
   - Binary Gap을 구할 정수 N을 아규먼트로 전달 받는다.
   - N의 범위는 1부터 2,147,483,647까지 이다. 범위를 벗어난 경우 -1을 출력하고 종료한다.
   - N의 최대 Binary Gap을 표준 출력장치에 출력한다.
 
   Binary Gap 예제
   0: 00             0 (No gap).
   1: 01             0 (No gap)
   2: 11             0 (No gap).
   5: 101            1 (Gap is 1).
   9: 1001           2 (Gap is 2).
   529:  1000010001     4 (Max gap is 4).
   1041: 10000010001    5 (Max gap is 5).

* answer #1
#include <stdio.h>
#include <stdlib.h>

int bin_gap(int N);
void print_usage();

int main(int argc, char *argv[]) {
	int N;
	//아규먼트를 입력 여부를 확인한다.
	if((argc != 2))
	{
		print_usage();
		return EXIT_FAILURE;
	}

	N = atoi(argv[1]);

	//N값의 유효성을 검사한다.
	if( N<1 || N>2147483647 )
	{
		printf("-1\n");
		return EXIT_FAILURE;
	}

	//최대 Binary gap을 출력한다.
	printf("%d\n", bin_gap(N));

	return EXIT_SUCCESS;
}

/*
 * 주어진 정수 N의 최대 binary gap을 구하는 함수
 * @param N: binary gap을 구할 정수
 * @return: N의 최대 binary gap
 */
int bin_gap(int N)
{
	int max=0, gap=0, start=0;

	//N의 값을 오른쪽 shift를 반목하면서 0이 될 때까지 진행한다.
	while( N > 0 ) {
		//N의 마지막 bit가 1이면 Binary Gap이 시작되거나 종료됨.
		if ((N&1) == 1) {
			//종료 case를 생각해서 최대 값을 저장한다.
			if (max < gap)
				max = gap;
			start = 1;
			gap = 0;
		}
		//마지막 bit가 0이면 Binary Gap이 진행 중.
		else {
			if (start == 1)
				gap++;
		}
		//N을 오른쪽으로 shift
		N = N >> 1;
	}
	return max;
}

/*
 * 사용법을 출력한다.
 */
void print_usage()
{
	puts("[usage] bgap.exe integer");
}
=======================================================================================
3. 2진수를 표현하는 문자열을 정수로 변환하는 프로그램을 작성한다.
   * 요구사항.
    - 2진수 문자열은 최대 32글자를 넘지 않으며, 아규먼트로 전달 받는다.
    - 아규먼트가 없거나, 입력한 문자열이 2진수가 아니거나 제한을 초과한경우 usage를 출력한다.
    - 주어진 문자열을 정수로 가정 하여 변환 한다.
    - 변환한 숫자를 표준 출력장치에 출력한다.

   * 실행 예시
    $ ./convert.exe 10
       2
      ./convert.exe 01001001
       73

* answer #1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char** argv)
{
    int i, j;
    char buf[30] = { 0, };
    int sum = 0;
    int tmp = 0;

    if (argc != 2) {
        printf("usage : ./convert.exe 10\n");
        return -1;
    }
    if (strlen(buf) > 32) {
        printf("input data cannot over 32 digit\n");
        return -1;
    }

    strcpy(buf, argv[1]);

    printf("buf = %s\n", buf);
    for (i = strlen(buf) - 1; i >= 0; i--) {
        if (buf[i] == '1') {
            j = strlen(buf) - i - 1;
            tmp = pow(2, j);
            sum += tmp;
        }
    }
    printf("converted decimal is %d\n", sum);
    return 0;
}

* answer #2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[])
{
    int nRes = 0;
    int i, nMask;

    if (argc != 2)
    {
        printf("Argument Error!\n");
        return -1;
    }

    int nLen = strlen(argv[1]);
    for (i=0; i<nLen; i++)
    {
        nMask = nLen - 1 - i;
        if (argv[1][i] == '1')
            nRes |= (1 << nMask);
    }

    printf("%d\n",nRes);
    return EXIT_SUCCESS;
}

* answer #3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int bstr_to_dec(const char *str);
int check_val(const char *str);
void print_usage();

int main(int argc, char *argv[])
{
	int dec;
    
	//아규먼트를 입력과 유효성을 확인한다.
	if((argc != 2) || !check_val(argv[1]))
	{
		print_usage();
		return EXIT_FAILURE;
	}

	//바이너리 문자열을 숫자로 변환한다.
	dec = bstr_to_dec(argv[1]);
	printf("%d\n", dec);
	return EXIT_SUCCESS;
}

/*
 * 주어진 바이너리 문자열을 숫자로 변환 한다.
 * @param str: 바이너리 문자열
 * @return: 바이너리 문자열을 변환한 정수
 */
int bstr_to_dec(const char *str)
{
	int val = 0;

	//NULL 문자를 가리킬 때 까지 반복해서
	//'1'일 경우만 1을 더한 뒤 2를 곱한 값을 저장한다.
	while (*str != '\0') {
		printf("%c ", *str);
		val = 2 * val + (*str++ - '0');
	}	

	return val;
}

/*
 * 주어진 바이너리 문자열의 유효성을 검사한다.
 * @param str: 바이너리 문자열
 * @return: 문자열의 유효성 여부. 유효하면 1 그렇지 않으면 0.
 */
int check_val(const char *str)
{
	int valid = 1;
	if(strlen(str) > 32)
		valid = 0;

	while (valid && *str != '\0')
	{
		if (*str != '0' && *str != '1')
			valid = 0;
		++str;
	}
	return valid;
}

/*
 * 사용법을 출력한다.
 */
void print_usage()
{
	puts("[usage] convert.exe binary_string");
}

=======================================================================================
4. 링크드리스트를 이용하여 전화번호 관리 프로그램을 만드시오.
  * 요구사항.
    - 전화번호 관리 프로그램이 기본적으로 지녀야 하는 기능은 다음과 같다.
     1. 입력: 이름과 전화번호를 입력
     2. 삭제: 이름을 입력하여 해당 이름의 정보를 삭제
     3. 검색: 이름을 입력하면 해당 이름의 전화번호를 출력
     4. 전체 출력: 저장된 모든 이름과 전화번호 정보를 출력
    - 사용자가 입력 할 수 있는 전화번호 개수에는 제한이 없다.
    - 프로그램이 종료 되어도 기존 데이터를 유지 할 수 있도록 한다.
     1. 새로운 데이터가 입력 될 때 마다 모든 데이터를 파일에 write 한다.
     2. 프로그램을 시작 할 때 데이터가 저장된 파일이 있으면 read해서 정보를 load한다.

  * 실행예시
     ***** MENU *****
     1.Insert
     2.Delete
     3.Search
     4.Print All
     0.Exit

     Choose the item : 4
     [Print All Data]
     Name: kim   Tel: 010-2323-5343
     Name: park  Tel: 010-3872-5000
     ......

* answer #1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//전화번호부 내용을 저장할 파일
#define SAVE_FILE "pb.txt"
//버퍼 크기
#define BUF_SIZE 100

//전화번호를 저장할 Node의 구조체 정의
typedef struct _node
{
	char *name;
	char *phone;
	struct _node *next;
}node;

int get_selection(void);
node* create_node(const char *name, const char* phone);
void insert_node(node **root, node *new);
void delete_phonebook(node **root, node *del);
node* search_phonebook(node *root);
void show_phonebook(node *root);
int write_file(node *root, const char* filename);
int read_file(node **root, const char* filename);
char* f_gets(char *st, int n, FILE* fp);
void eatline(void);
void print_node(node *n);
void free_all_node(node *root);
void free_node(node *n);

int main()
{
	setbuf(stdout, NULL);

	//linked list의 root
	node *root=NULL;
	int sel=0;
	//search 기능시 사용할 node 포인터
	node *tmp;

	//사용자 입력 버퍼
	char buf_name[BUF_SIZE];
	char buf_phone[BUF_SIZE];

	//파일로 부터 저장된 list를 읽어온다.
	read_file(&root, SAVE_FILE);

	//메뉴를 출력하고 사용자로 부터 선택을 받는다.
	while((sel=get_selection())> 0)
	{
		switch(sel)
		{
		case 1:
			puts("[Insert Phonebook]");

			//사용자로 부터 이름과 전화번호를 입력받는다.
			printf("Input Name: ");
			f_gets(buf_name, sizeof(buf_name), stdin);
			printf("Input Tel Number: ");
			f_gets(buf_phone, sizeof(buf_phone), stdin);

			//Node를 생성한다.
			tmp = create_node(buf_name, buf_phone);
			if(tmp!= NULL)
			{
				//Node를 list에 삽입하고, 파일에 node의 내용을 write한다.
				insert_node(&root, tmp);
				write_file(root, SAVE_FILE);
			}
			break;

		case 2:
			puts("[Delete Phonebook]");
			//Node를 찾는다.
			tmp = search_phonebook(root);
			if(tmp != NULL)
			{
				print_node(tmp);
				//Node를 list에서 삭제하고, 파일에 node의 내용을 write한다.
				delete_phonebook(&root,tmp);
				write_file(root, SAVE_FILE);
			}
			else
				puts("Can't find!");

			break;

		case 3:
			puts("[Search Phonebook]");
			//Node를 찾는다.
			tmp = search_phonebook(root);
			if(tmp != NULL)
				print_node(tmp);
			else
				puts("Can't find!");

			break;

		case 4:
			puts("[Print All Data]");
			//모든 list를 출력한다.
			show_phonebook(root);
			break;

		default:
			puts("Wrong selection.");
			break;
		}
	}

	free_all_node(root);

	return 0;
}

/*
 * 메뉴를 출력하고 사용자로 부터 선택을 받는다.
 * @return: 사용자 선택
 */
int get_selection(void)
{
	int ret = 0;
	putchar('\n');
	puts("***** MENU *****");
	puts("1.Insert");
	puts("2.Delete");
	puts("3.Search");
	puts("4.Print All");
	puts("0.Exit");
	printf("Choose the item:");
	scanf("%d",&ret);

	eatline();

	return ret;
}

/*
 * 사용자로 부터 name과
 * @return: 사용자 선택
 */
node* create_node(const char *name, const char *phone)
{
	node *new = NULL;
	if((new = (node*)malloc(sizeof(node))) != NULL)
	{
		new->name = strdup(name);
		new->phone = strdup(phone);
		new->next = NULL;
	}
	return new;
}

/*
 * linked list에 node를 삽입하는 함수
 * @param root: root node의 이중 포인터.
 * @param new: linked list의 마지막에 연결할 node
 */
void insert_node(node **root, node *new)
{
	//linked list에 아무것도 없을 때
	if(*root==NULL)
	{
		(*root)=new;
	}
	else
	{
		node *curr = *root;
		//가장 마지막 node를 찾아서 삽입한다.
		while(curr->next != NULL)
			curr = curr->next;
		curr->next = new;
	}
}

/*
 * 사용자로 부터 이름을 입력 받고 해당하는 node를 찾는다.
 * @param root: list의 시작 주소
 * @return: 찾은 node의 주소
 */
node* search_phonebook(node *root)
{
	node *curr = root;
	char buf_name[100];

	printf("Input Name: ");
	f_gets(buf_name, sizeof(buf_name), stdin);

	//node를 순회하면서 같은 이름의 node를 찾는다.
	while(curr!=NULL)
	{
		if(!strcmp(curr->name, buf_name))
			break;
		curr=curr->next;
	}
	return curr;
}

/*
 * linked list에서 node를 지운다.
 * @param root: list의 시작 주소
 * @param del: 삭제할 node의 주소
 * @return: 찾은 node의 주소
 */
void delete_phonebook(node **root, node *del)
{
	node *curr = *root;

	if(curr==NULL || del==NULL)
		return;

	// 첫번째 node를 삭제할 경우
	if(*root==del)
	{
		*root=(*root)->next;
	}
	else
	{
		while(curr->next!=NULL)
		{
			if(curr->next==del)
			{
				curr->next=del->next;
				break;
			}
			curr=curr->next;
		}
	}

	free_node(del);
}

/*
 * linked list의 모든 node를 출력한다.
 * @param root: list의 시작 주소
 */
void show_phonebook(node *root)
{
	while(root!=NULL)
	{
		print_node(root);
		root=root->next;
	}
}

/*
 * node의 내용을 출력한다.
 * @param n: 출력할 node의 주소
 */
void print_node(node *n)
{
	printf("Name: %s\tTel: %s\n", n->name, n->phone);
}

/*
 * 모든 node의 메모리를 해제하고 삭제한다.
 * @param root: linked list의 시작 주소
 */
void free_all_node(node *root)
{
	node *del;
	while(root!=NULL)
	{
		del = root;
		root=root->next;

		free_node(del);
	}
}

/*
 * node의 메모리를 해제한다.
 * @param n: 삭제할 node의 주소
 */
void free_node(node *n)
{
	free(n->name);
	free(n->phone);
	free(n);
}

/*
 * 파일에 linked list의 모든 내용을 write한다.
 * @param root: list의 시작 주소
 * @param filename: 파일 이름
 * @return: 성공하면 1, 실패하면 0
 */
int write_file(node *root, const char *filename)
{
	FILE *fp=NULL;

	if(root==NULL)
		return 0;

    if ((fp = fopen(filename,"wt")) == NULL)
    {
        printf("write_file can't open %s\n", filename);
        return 0;
    }

	while(root!=NULL)
	{
		fprintf(fp, "%s\n%s\n", root->name, root->phone);
		root=root->next;
	}

	fclose(fp);
	return 1;
}

/*
 * 파일로부터 내용을 읽어서 linked list에 복원한다.
 * @param root: list의 시작 주소
 * @param filename: 파일 이름
 * @return: 성공하면 1, 실패하면 0
 */
int read_file(node **root, const char *filename)
{
	node *tmp;

	char buf_name[100];
	char buf_phone[100];

	FILE *fp=NULL;

    if ((fp = fopen(filename,"rt")) == NULL)
    {
        printf("read_file can't open %s\n", filename);
        return 0;
    }

	while(1)
	{
		f_gets(buf_name, sizeof(buf_name), fp);
		f_gets(buf_phone, sizeof(buf_phone), fp);
		// while의 조건문에서 feof()를 호출하면, 파일의 끝이 제대로 검출 되지 않음.
		// http://www.drpaulcarter.com/cs/common-c-errors.php#4.2
	    if ( feof(fp) )
	      break;
		//새로운 node를 생성한다.
		tmp = create_node(buf_name, buf_phone);
		if(tmp!= NULL)
			insert_node(root, tmp);
	}

	fclose(fp);
	return 1;
}

/*
 * fgets의 단점 (줄바꿈 문자)을 보완하는 함수
 * @param st: 스트림으로 부터 입력을 저장할 버퍼
 * @param n: 버퍼의 길이
 * @param fp: 스트림 주소
 * @return: fgets의 return 주소
 */
char* f_gets(char *st, int n, FILE *fp)
{
	char *ret_val;
	char *find;

	ret_val = fgets(st, n, fp);
	if (ret_val)
	{
		find = strchr(st, '\r'); //캐리지 리턴('\r')의 위치를 찾는다.
		if (find) // 만약 찾았다면,
			*find = '\0'; // NULL 캐릭터로 채운다

		find = strchr(st, '\n'); //뉴 라인('\n')의 위치를 찾는다.
		if (find) // 만약 찾았다면,
			*find = '\0'; // NULL 캐릭터로 채운다
	}
	return ret_val;
}
/*
 * scanf로 입력을 받을때 입력 버퍼에
 * 줄바꿈이 남아있는 문제를 해결하기 위한 함수.
 */
void eatline(void)
{
	while (getchar() != '\n')
		continue;
}

=======================================================================================
1. 1부터 100까지 숫자를 무작위로 1줄에 10개씩 text file로 저장하시오.  
    숫자가 중복되어  저장돼서는 안 됨.  한 줄에 10개씩 출력. 숫자 사이에는 빈칸(space)으로 구분.
    ex) output.txt
92 18 84 4 61 10 47 39 66 98
20 52 65 48 95 83 49 37 79 100
23 41 12 21 17 28 82 33 29 87
35 67 54 93 85 2 32 59 89 97
63 42 57 25 56 6 64 75 36 24
51 43 31 88 46 53 8 70 69 11
38 91 74 73 5 99 16 77 76 30
15 86 44 94 1 34 50 80 96 7
27 9 3 14 78 60 19 26 45 81
90 13 62 71 55 40 22 72 68 58

* answer #1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(void) {
	FILE *fp = NULL;
	int i,j,count;
	int num; 
	int flag = 0;
	int acBuf[100] = {0,};

	count = 0;

	fp = fopen("output.txt", "w");
	if (fp == NULL) {
		printf("fp is NULL\n");
		return -1;
	}

	// random 숫자 버퍼 저장
	for (i=0; i < 100; i++) {
		num = (rand() % 100)+1;
		for (j=0; j <= count;j++) {
			if (flag == 1) { j = 0; flag = 0;}
			// 중복 체크해서 중복되면 처음부터 다시 시작
			if (acBuf[j] == num) {
				num = (rand() % 100)+1;
				flag = 1;
			}
		}

		acBuf[count++] = num;	// inseart val
		//printf("count = %d[%d]\n", count,num);
	}
	
	// output.txt에 축력 
	for (i=0; i < 100; i++) {
		fprintf(fp, "%d ", acBuf[i]);
		if ((i+1) % 10 == 0) { 
			fputs("\n", fp);
		}
	}

	fclose(fp);
	return 0;
}

* answer #2
#include "stdafx.h"
#include <stdio.h>
#include "stdlib.h"

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
int _tmain(int argc, _TCHAR* argv[])
{
 int num[100];
 int ret[100];

 for(int i=0;i<100;i++) {
  num[i] = i+1;
 }

 for(int i=0;i<100;i++) {
  int nFind = 0;
  while(!nFind) {
   int r = rand() %100;
   if(num[r] <= 100) {
    ret[i] = num[r];
    num[r] += 100;
    nFind = 1;
   }
  }
 }

 FILE * pFile = NULL; 
 pFile = fopen ("output.txt","w"); 
 if (pFile!=NULL)  
 {
 for(int i=0;i<100;i++) {
   printf("%3d ", ret[i]);
   fprintf(pFile, "%3d ", ret[i]);
   if((i+1)%10 == 0) {
    printf("\n");
    fprintf(pFile, "\n");
   }
  }
  fclose (pFile);
 }
 return 0;
}

* answer #3

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_BUF 100

int random_func(int n)
{
    return rand() % n;
}

int main()
{
    int i;
    unsigned char num100[MAX_BUF];
    int nMax = MAX_BUF;
    int nIndex;
    FILE * fp;

    fp = fopen("output.txt", "wt");
    for (i = 0; i < 100; i++)
        num100[i] = i+1;

    srand((unsigned)time(NULL));

    for (i = 1; i <= MAX_BUF; i++)
    {
        nIndex = random_func(nMax);
        fprintf(fp, "%d ", num100[nIndex]);
        memcpy(&num100[nIndex], &num100[nIndex + 1], nMax - nIndex - 1);
        nMax--;

        if ((i % 10) == 0)
            fprintf(fp, "\n");
    }

    fclose(fp);
    return 0;
}

=======================================================================================
2. 1번의 output.txt에 출력된 숫자가 중복된 수가 없는 것을 검증하는 코드를 작성하시오. 
   중복된 수가 발견되면 그 수를 출력하고 종료. 이상 없으면 "Clear"출력
   ex) 중복된 수가 56일 경우 "Error : 56"출력 후 종료
       중복된 수가 없으면 "Clear" 출력
       
* answer #1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

int main(void) {
	FILE *fp = NULL;
	int i,j,count;
	char acBuf[MAX]= {0,};
	char acBuf2[MAX*5]= {0,};
	int aiDigit[MAX]= {0,};
	char ch = 0;
	char* pch = 0;
	
	count = 0;

	fp = fopen("output.txt", "r");
	if (fp == NULL) {
		printf("fp is NULL\n");
		return -1;
	}
	
	while(!(feof(fp))) {
		fgets(acBuf, 100, fp);
		strcat(acBuf2, acBuf);
	}	
	//printf("%s", acBuf2);
	
	pch = strtok(acBuf2, " ");
	aiDigit[count++] = atoi(pch);

	while (pch != NULL) {
		pch = strtok(NULL, " ");
		if (pch == NULL) break;
		aiDigit[count++] = atoi(pch);
	}
#if 0
	for (i=0; i<count-1;i++) {
		printf("%d\n", aiDigit[i]);
	}
#endif

	for(i=0; i < MAX-1; i++) {
		for(j=i+1; j < MAX; j++) {
			if (aiDigit[i] == aiDigit[j]) {
				printf("Error : %d\n", aiDigit[i]);
				return -1;
			} 
		}
	}

	printf("Clear\n");

	fclose(fp);

	return 0;
}
=======================================================================================
3. 3. 1~1000까지의 숫자 중 임의의 수 100개를 text file로 저장하시오.  
   숫자가 중복되어  저장돼서는 안 됨.  한 줄에 10개씩 저장. 숫자 사이에는 빈칸(space)으로 구분.

  ex) output.txt
      6 4 2 3 8 10 11 92 99 22
     33 45 67 89 100 101 643 1 999 111
     ....

* answer #1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
	FILE *fp = NULL;
	int i,j,count;
	int num; 
	int flag = 0;
	int acBuf[100] = {0,};

	count = 0;

	fp = fopen("output.txt", "w");
	if (fp == NULL) {
		printf("fp is NULL\n");
		return -1;
	}

	// random 숫자 버퍼 저장
	for (i=0; i < 100; i++) {
		num = (rand() % 1000)+1;
		for (j=0; j <= count;j++) {
			if (flag == 1) { j = 0; flag = 0; }
			// 중복 체크해서 중복되면 처음부터 다시 시작
			if (acBuf[j] == num) {
				num = (rand() % 1000)+1;
				flag = 1;
			}
		}

		acBuf[count++] = num;	// inseart val
		printf("count = %3d[%4d]\n", count,num);
	}
	
	// output.txt에 축력 
	for (i=0; i < 100; i++) {
		fprintf(fp, "%d ", acBuf[i]);
		//fprintf(fp, "%4d ", acBuf[i]);
		if ((i+1) % 10 == 0) { 
			fputs("\n", fp);
		}
	}

	fclose(fp);
	return 0;
}

* answer #2
// MyQ1_3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAX_BUF	1000
int random(int n)
{
	return rand() % n;
}

int main()
{
	int i;
	int num1000[MAX_BUF];
	int nMax = MAX_BUF;
	int nIndex;
	FILE * fp;

	fp = fopen("output.txt", "wt");

	for (i = 0; i < 1000; i++)
		num1000[i] = i + 1;

	srand((unsigned)time(NULL));

	for (i = 0; i < 100; i++)
	{
		nIndex = random(nMax);
		fprintf(fp, "%d ", num1000[nIndex]);
		memcpy(&num1000[nIndex], &num1000[nIndex + 1], nMax - nIndex - 1);
		nMax--;

		if (((i+1) % 10) == 0)
			fprintf(fp, "\n");
	}

	fclose(fp);
	return 0;
}

=======================================================================================
4. 1~1000까지의 숫자 중 5개를 입력받아서, 3번의 output.txt 파일에서 존재하는지를 체크하시오. 
   존재하면 1, 존재하지 않으면 0을 출력하시오. 
  
  ex) 입력 : 6 1000 555 2 3 
      출력 : 1 0 0 1 1 
* answer #1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

int main(void) {
	FILE *fp = NULL;
	int i=0,j=0,count=0;
	char acBuf[MAX]= {0,};
	char acBuf2[MAX*5]= {0,};
	int aiDigit[MAX]= {0,};
	char* pch = 0;
	char answer[5] = {0,};
	int input[10] = {0,};

	// 입력값 처리
	printf("입력 : ");
	gets(acBuf2);
	pch = strtok(acBuf2, " ");
	input[i++] = atoi(pch);	
	while(pch != NULL) {
		pch = strtok(NULL, " ");
		if (pch == NULL) break;
		input[i++] = atoi(pch);
	}

	// output.txt 값 read
	fp = fopen("output.txt", "r");
	if (fp == NULL) {
		printf("fp is NULL\n");
		return -1;
	}
	
	while(!(feof(fp))) {
		fgets(acBuf, 100, fp);
		strcat(acBuf2, acBuf);
	}	
	//printf("%s", acBuf2);
	
	pch = strtok(acBuf2, " ");
	aiDigit[count++] = atoi(pch);

	while (pch != NULL) {
		pch = strtok(NULL, " ");
		if (pch == NULL) break;
		aiDigit[count++] = atoi(pch);
	}
#if 0
	for (i=0; i<count-1;i++) {
		printf("%d\n", aiDigit[i]);
	}
#endif
	
	// value 비교
	for(j=0; j < 5; j++) {
		for(i=0; i < MAX; i++) {
			if (aiDigit[i] == input[j]) {
				answer[j] = 1;
			} 
		}
	}

	printf("출력 : ");
	for (i=0; i<5; i++) {
		printf("%d ", answer[i]);
	}

	fclose(fp);

	return 0;

}

* answer #2
// MyQ1_4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main()
{
	int input_num[5];
	int bSame = 0;

	scanf("%d %d %d %d %d", &input_num[0], &input_num[1], &input_num[2], &input_num[3], &input_num[4]);

	FILE * fp;
	fp = fopen("output.txt", "rt");
	int i, k;
	int nums[100];
	int oneNum;

	for (i = 0; i < 100; i++)
	{
		fscanf(fp, "%d", &nums[i]);
	}
	fclose(fp);

	for (k = 0; k < 5; k++)
	{
		for (i = 0; i < 100; i++)
		{
			if (nums[i] == input_num[k])
			{
				bSame = 1;
				break;
			}
		}
		if (bSame)
			printf("1 ");
		else 
			printf("0 ");
		bSame = 0;
	}

	return 0;
}

=======================================================================================
5. 4번 문제를 이진 탐색으로 구현하시오. 

* answer #1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

int binarySearch(int min, int max, int key, int array[]);

int main(void) {
	FILE *fp = NULL;
	int i=0,j=0,count=0;
	char acBuf[MAX]= {0,};
	char acBuf2[MAX*5]= {0,};
	int aiDigit[MAX]= {0,};
	char* pch = 0;
	char answer[5] = {0,};
	int input[10] = {0,};
	int tmpVal = 0;

	// 입력값 처리
	printf("입력 : ");
	//gets(acBuf2);
	fgets(acBuf2, sizeof(acBuf2)-1, stdin);

	// 입력값을 파싱
	pch = strtok(acBuf2, " ");
	input[i++] = atoi(pch);	

	while(pch != NULL) {
		pch = strtok(NULL, " ");
		//printf("pch = %s\n", pch);
		if (pch == NULL) break;
		input[i++] = atoi(pch);
	}
	/*	
	for(i=0; i<5; i++) {
		printf("%d ", input[i]);
	}
	*/
	
	// output.txt에서 값 read
	fp = fopen("output.txt", "r");
	if (fp == NULL) {
		printf("fp is NULL\n");
		return -1;
	}

	memset(acBuf2, 0x0, sizeof(acBuf2));
	
	while(!(feof(fp))) {
		fgets(acBuf, 100, fp);
		strcat(acBuf2, acBuf);
	}	
	//printf("%s", acBuf2);

	pch = strtok(acBuf2, " ");
	aiDigit[count++] = atoi(pch);

	while (pch != NULL) {
		pch = strtok(NULL, " ");
		if (pch == NULL) break;
		aiDigit[count++] = atoi(pch);
	}

	// 오름차순 정렬 (bubble sort)
	for (i=0; i < MAX-1; i++) {
		for (j=0; j < MAX-i-1; j++) {
			if (aiDigit[j] > aiDigit[j+1]) {
				tmpVal = aiDigit[j];
				aiDigit[j] = aiDigit[j+1];
				aiDigit[j+1] = tmpVal;
			}
		}
	}
#if 0
	for (i=0; i < MAX; i++) {
		printf("%d ", aiDigit[i]);
	}
#endif

	// 이진 탑색 호출
	for(j=0; j < 5; j++) {
		answer[j] = binarySearch(0, MAX, input[j], aiDigit);
	}
	
	// 출력
	printf("출력 : ");
	for (i=0; i<5; i++) {
		printf("%d ", answer[i]);
	}

	fclose(fp);

	return 0;

}

int binarySearch(int min, int max, int key, int* aiDig) {
	int mid = 0;

	if (max < min) return 0;

	mid = (min + max) / 2;
	
	if (key == aiDig[mid])
		return 1;

	else if (key < aiDig[mid]) {
		binarySearch(min, mid-1, key, aiDig);
	}
	else if (key > aiDig[mid]) {
		binarySearch(mid+1, max, key, aiDig);
	}
	else return 0;
}

* answer #2
// MyQ1_5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

void sort(int * N)
{
	int i, j;
	int nMin;
	int nIndex, nTemp;

	for (i = 0; i < 100; i++)
	{
		nMin = N[i];
		for (j = i; j < 100; j++)
		{
			if (N[j] < nMin)
			{
				nMin = N[j];
				nIndex = j;
			}
		}
		nTemp = N[nIndex];
		N[nIndex] = N[i];
		N[i] = nTemp;
	}
}

int binary_search(int * N, int value, int low, int high) {
	int mid;

	if (high < low)
		return -1; // not found
	mid = (low + high) / 2;

	if (N[mid] > value)
		return binary_search(N, value, low, mid - 1);
	else if (N[mid] < value)
		return binary_search(N, value, mid + 1, high);
	else
		return mid; // found
}

int main()
{
	int input_num[5];
	int bFound = 0;

	scanf("%d %d %d %d %d", &input_num[0], &input_num[1], &input_num[2], &input_num[3], &input_num[4]);

	FILE * fp;
	fp = fopen("output.txt", "rt");
	int i, k;
	int nums[100];
	int oneNum;

	for (i = 0; i < 100; i++)
	{
		fscanf(fp, "%d", &nums[i]);
	}
	fclose(fp);

	// sort
	sort(nums);

	for (k = 0; k < 5; k++)
	{
		bFound = binary_search(nums, input_num[k], 0, 99);
		if (bFound == -1)
			printf("0 ");
		else
			printf("1 ");
	}

	return 0;
}

=======================================================================================
1. C 문법 (필기)

 1) ++연산자 (++a, a++) 차이
 2) call by value, call by reference의 차이
 3) scanf, printf 지시자 (%5.2f, %5d..)의 정확한 의미
 4) 함수포인터 선언방법
 5) 싱글 링크드 리스트에 node 추가하는 방법
 6) 논리식/비트연산 (a>>1, a>b ? c)의 의미

 7) TCP 서버 system call 순서는? 

 7-1) Client call 순서는?

 

2. C (실기)

1) 오일회사 최대이익 문제
 
 |1일 |2일 |3일 |4일 |5일 |6일 |7일 |8일 |9일 |10일|
 |12원|11원|19원|10원|22원|30원|10원|24원|10원|12원| 

위와같은 입력이 있을 때, 최소가격에 구입, 최대가격에 판매하는 경우 구입일, 판매일,
이익을 출력하시오

 

2) trim 함수 구현
 "######1234####" "#" 와 같이 입력을 하는 경우 1234를 출력하는 함수를 구현하시오
 "####AB#CC####"  의 경우는 AB#CC를 출력

 

3) TLV 파싱함수 구현
 type, length, value 캐릭터 스트림을 파싱하여 출력하시오
 A041111B0512345 인 경우, 아래와 같이 출력. value에 TLV가 올 수 있음
 A, 04
 1111
  B, 05
   12345
 

=======================================================================================
아래 그림과 같이 패턴 잠금을 위한 3x3 영역이 있다.  (Y축은 10, 20, 30, X축은 1, 2, 3) 
소스코드를 작성하여 아래 조건을 만족하는 프로그램을 완성 하시오. (lock ok/lock fail출력)

30  -   -   -
20  -   -   -
10  -   -   -
    1   2   3

1. parameter로 좌표를 입력 받고 입력 좌표는 5개 이상 9개 이하가 되도록 하시오 
  ex) pattern.exe 11 12 13 22 33 32             : lock ok

2. 인접 위치로만 이동할 수 있고, 연속하여 동일한 좌표가 입력되면 실패 처리 하시오 
  ex) pattern.exe 11 12 13 22 33 32             : lock ok
  ex) pattern.exe 11 23 22 33 32 31             : lock fail

* answer #1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int i,j;
    int buf[20] = {0,};
    int a, b;
    int a1, b1;

    if (argc < 6 || argc > 10) {
        printf("usage : pattern.exe 11 12 13 22 23\n");
        return -1;
    }

    for (i=0; i < argc-1; i++) {
        buf[i] = atoi(argv[i+1]);
        printf("buf[%d] = %d\n", i, buf[i]);
    }

    for (j=0; j<i-1; j++) {
        // 중복체크
        if (buf[j] == buf[j+1]) {
            printf("lock fail\n");
            return -1;
        }

        // 인접여부 체크
        a = buf[j] / 10;
        b = buf[j] % 10;
        a1 = buf[j+1] / 10;
        b1 = buf[j+1] % 10;
        if ((abs(a1-a) + abs(b1-b)) >= 2) {
            printf("lock fail\n");
            return -1;
        }
    }
    printf("lock ok\n");
    return 0;
}

* answer #2
거리계산으로 풀이함

 

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include "math.h"

int _tmain(int argc, _TCHAR* argv[])
{
 if((argc < 6) || (argc > 10) ) {
  printf("invalid arg\n");
  return -1;
 }

 int nRet = 1;

 int *nNumber = NULL;
 nNumber = (int*)malloc(sizeof(int)*(argc-1));

 for(int i=0;i<argc-1;i++) {
  nNumber[i] = atoi(argv[i+1]);
  printf("%d ", nNumber[i]);

  if(i > 0) {
   int prev = nNumber[i-1];
   int cur = nNumber[i];
   if( prev == cur) {
    nRet = 0;
    break;
   }
   int x= prev/10 - cur/10;
   int y= prev%10 - cur%10;
   
   double dVal = sqrt(double(x*x + y*y));
   if(dVal >= 2) {
    nRet = 0;
    break;
   }
  }
 }

 if(nRet)
  printf("lock ok\n");
 else 
  printf("lock fail\n");

 if(nNumber) free(nNumber);

 return 0;
}

* answer #3
#include<stdio.h>
#include<iostream>

int pattern[9] = {11, 12, 13, 21, 22, 23, 31, 32, 33};

int main(int argc, char**argv)
{
 // validation check
 for(int i = 1; i != (argc); i++)
 { 
  int isPattern = 0;
  for(int j = 0; j != 9; j++)
  {
   if(pattern[j] == atoi(argv[i]))
   {
    isPattern = 1;
   }
  }
  if(isPattern == 0 || (argc-1) < 5 || (argc-1) > 9)
  {
   printf("lock fail");
   return -1;
  }
 }

 // confirm lock ok or fail
 int prev, after;
 for(int i = 1; i != (argc-1); i++)
 {
  prev = atoi(argv[i]);
  after = atoi(argv[i+1]);

  if(abs((prev/10) - (after/10)) > 1)
  {
   printf("lock fail");
   return -1;
  }

  if(abs(prev%10 - after%10) > 1)
  {
   printf("lock fail");
   return -1;
  }

  if( prev == after)
  {
   printf("lock fail");
   return -1;
  }

 }

 printf("lock ok");
 return 1;
}

* answer #4
#include <math.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{
	int i;
	int nCount = 6;
	int num1F, num1S, num2F, num2S;
	int nInput[9]; // = { 11, 23, 22, 33, 32, 31 };
	nCount = argc - 1;
	if (nCount < 5 || nCount > 9)
	{
		printf("lock fail\n");
		return 0;
	}
	for (i = 0; i < argc - 1; i++){
		nInput[i] = atoi(argv[i + 1]);
		//printf("%d ", nInput[i]);
	}
	// 연속 동일 좌표 fail
	for (i = 0; i < nCount-1; i++){
		if (nInput[i] == nInput[i+1]){
			printf("lock fail\n");
			return 0;
		}
	}
	// 인접 좌표 검사
	for (i = 0; i < nCount - 1; i++){ // 12이면 1,2로 나눔.
		num1F = nInput[i] / 10;
		num1S = nInput[i] % 10;
		num2F = nInput[i+1] / 10;
		num2S = nInput[i+1] % 10;
		if ((abs(num1F-num2F) > 1) || (abs(num1S - num2S) > 1)){
			printf("lock fail\n");
			return 0;
		}
	}
	printf("lock ok\n");
	return 0;
}
=======================================================================================
<Elevator Program>

1.
#include <stdio.h>
#include <time.h>

void TransTime(char * strTime, struct tm * pTime)
{
    time_t ct;
    char szHour[3], szMin[3], szSec[3];

    szHour[0] = strTime[0]; szHour[1] = strTime[1]; szHour[2] = 0;
    szMin[0] = strTime[3]; szMin[1] = strTime[4]; szMin[2] = 0;
    szSec[0] = strTime[6]; szSec[1] = strTime[7]; szSec[2] = 0;

    ct = time(NULL);
    *pTime = *localtime(&ct);

    pTime->tm_hour = atoi(szHour);
    pTime->tm_min = atoi(szMin);
    pTime->tm_sec = atoi(szSec);
}

int main(void)
{
    struct tm inputTime;
    struct tm stopTime;
    time_t tInput, tStop=0;
    char strTime[80];
    int nFromLevel;
    int nToLevel;
    int nWaitingTime = 0;
    int nStopLevel = 0;
    int nRidingTime = 1;
    int nElevatorNum;
    int nCurrentPos = 1;
    int bFirst = 1;

    while(1)
    {
	scanf("%s %d %d",strTime, &nFromLevel, &nToLevel);
	if (strcmp(strTime,"q") == 0)
	    return 0;

	TransTime(strTime,&inputTime);
	//printf("InputTime - %02d:%02d:%02d\n",inputTime.tm_hour, inputTime.tm_min, inputTime.tm_sec);
	tInput = mktime(&inputTime);

        nWaitingTime = abs(nCurrentPos - nFromLevel);

	if (tStop > tInput) 
	{
	    nWaitingTime = -1;
	    nElevatorNum = -1;
	}
	else 
	{
	    nElevatorNum = 1;
	    nCurrentPos = nToLevel;
	    
	    tStop = tInput + nWaitingTime + abs(nToLevel-nFromLevel)+nRidingTime;
	    stopTime = *localtime(&tStop);
	    //printf("StopTime - %02d:%02d:%02d\n",stopTime.tm_hour, stopTime.tm_min, stopTime.tm_sec);
	}

	printf("%d %d\n",nElevatorNum, nWaitingTime);
    }
}

2.
#include <stdio.h>
#include <time.h>

void TransTime(char * strTime, struct tm * pTime)
{
    time_t ct;
    char szHour[3], szMin[3], szSec[3];

    szHour[0] = strTime[0]; szHour[1] = strTime[1]; szHour[2] = 0;
    szMin[0] = strTime[3]; szMin[1] = strTime[4]; szMin[2] = 0;
    szSec[0] = strTime[6]; szSec[1] = strTime[7]; szSec[2] = 0;

    ct = time(NULL);
    *pTime = *localtime(&ct);

    pTime->tm_hour = atoi(szHour);
    pTime->tm_min = atoi(szMin);
    pTime->tm_sec = atoi(szSec);
}

int main(void)
{
    struct tm inputTime;
    struct tm stopTime;
    time_t tInput, tStop=0;
    time_t tPrevInput = 0;
    char strTime[80];
    int nFromLevel;
    int nToLevel;
    int nWaitingTime= 0;
    int nStopLevel = 0;
    int nRidingTime = 1;
    int nGetoutTime = 1;
    int nElevatorNum = 1;
    int nCurrentPos = 1;
    int bFirst = 1;

    while(1)
    {
	scanf("%s %d %d",strTime, &nFromLevel, &nToLevel);
	if (strcmp(strTime,"q") == 0)
	    return 0;

	TransTime(strTime,&inputTime);
	//printf("InputTime - %02d:%02d:%02d\n",inputTime.tm_hour, inputTime.tm_min, inputTime.tm_sec);
	tInput = mktime(&inputTime);

	nWaitingTime = abs(nCurrentPos - nFromLevel);

	if (tStop > tInput) 
	{
	    nWaitingTime += tStop - tInput;
	    if (nCurrentPos != nFromLevel) 
		nWaitingTime += nGetoutTime;
	}

	{
	    nCurrentPos = nToLevel;
	    tPrevInput = tInput;
	    
	    tStop = tPrevInput + nWaitingTime + abs(nToLevel-nFromLevel)+nRidingTime;
	    //stopTime = *localtime(&tStop);
	    //printf("StopTime - %02d:%02d:%02d\n",stopTime.tm_hour, stopTime.tm_min, stopTime.tm_sec);
	}

	printf("%d %d\n",nElevatorNum, nWaitingTime);
    }
}

3. 
#include <stdio.h>
#include <time.h>

void TransTime(char * strTime, struct tm * pTime)
{
    time_t ct;
    char szHour[3], szMin[3], szSec[3];

    szHour[0] = strTime[0]; szHour[1] = strTime[1]; szHour[2] = 0;
    szMin[0] = strTime[3]; szMin[1] = strTime[4]; szMin[2] = 0;
    szSec[0] = strTime[6]; szSec[1] = strTime[7]; szSec[2] = 0;

    ct = time(NULL);
    *pTime = *localtime(&ct);

    pTime->tm_hour = atoi(szHour);
    pTime->tm_min = atoi(szMin);
    pTime->tm_sec = atoi(szSec);
}

int main(void)
{
    int i;
    struct tm inputTime;
    struct tm stopTime;
    time_t tInput;
    time_t tStop[4] = {0,};
    time_t tPrevInput = 0;
    char strTime[80];
    int nFromLevel;
    int nToLevel;
    int nWaitingTime[4] = {0,};
    int nMinWaitingTime = 0;
    int nStopLevel = 0;
    int nRidingTime = 1;
    int nGetoutTime = 1;
    int nElevatorNum;
    int nCurrentPos[4] = {1,1,1,1};
    int bFirst = 1;

    while(1)
    {
	scanf("%s %d %d",strTime, &nFromLevel, &nToLevel);
	if (strcmp(strTime,"q") == 0)
	    return 0;

	TransTime(strTime,&inputTime);
	//printf("InputTime - %02d:%02d:%02d\n",inputTime.tm_hour, inputTime.tm_min, inputTime.tm_sec);
	tInput = mktime(&inputTime);

	for (i=0; i<4; i++)
	{
	    nWaitingTime[i] = abs(nCurrentPos[i] - nFromLevel);

	    if (tStop[i] >= tInput) 
	    {
		nWaitingTime[i] += tStop[i] - tInput;
	        if (nCurrentPos[i] != nFromLevel) 
		    nWaitingTime[i] += nGetoutTime;
	    }
	}

	nMinWaitingTime = nWaitingTime[0];
	nElevatorNum = 0;
	for (i=1; i<4; i++)
	{
	    if (nMinWaitingTime > nWaitingTime[i])
	    {
		nMinWaitingTime = nWaitingTime[i];
		nElevatorNum = i;
	    }
	}


        nCurrentPos[nElevatorNum] = nToLevel;
	tPrevInput = tInput;
	    
	tStop[nElevatorNum] = tPrevInput + nWaitingTime[nElevatorNum] + abs(nToLevel-nFromLevel)+nRidingTime;
	    //stopTime = *localtime(&tStop);
	    //printf("StopTime - %02d:%02d:%02d\n",stopTime.tm_hour, stopTime.tm_min, stopTime.tm_sec);
	

	printf("%d %d\n",nElevatorNum+1, nWaitingTime[nElevatorNum]);
    }
}
=======================================================================================
표준 입력으로 정수와 길이 10 이하의 문자열이 입력됩니다. 
입력된 문자열을 정수만큼 문자 단위로 N-gram을 출력하는 프로그램을 만드세요
(scanf 함수 호출 전에 문자열을 출력하면 안 됩니다). 만약 입력된 문자열의 길이가 입력된 정수 미만이라면 wrong을 출력하세요.
N-gram이란? 
n-gram 은 통계적인 자연어 처리에서 널리 사용되는 모델이다. 어떠한 글에서 여러 문자나 단어들의 빈도수를 알아낼 때 유용하다.

입력
3 Beethoven

결과
Bee
eet
eth
tho
hov
ove
ven
 
* answer #1
/*
 * ngram.c
 *
 *  Created on: 2017. 4. 3.
 *      Author: 74903
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	if(argc < 3) {
		printf("argc error\n");
		return -1;
	}

	char buf[11];
	memset(buf, 0x00, 11);

	int nCount = atoi(argv[1]);
	sprintf(buf, "%s", argv[2]);

	int nMax = strlen(buf);

	if(nMax < nCount) {
		printf("wrong");
		return -1;
	}

	for(int i=0; i<nMax; i++) {
		if(i+2 > nMax-1) break;
		printf("%c%c%c\n", buf[i], buf[i+1], buf[i+2]);
	}

	return 0;
}

=======================================================================================
표준 입력으로 정수 10개와 정수 1개가 각 줄에 입력됩니다. 
여기서 정수 10개는 연결 리스트에 저장되고, 정수 1개는 삭제할 정수입니다. 
다음 소스 코드에서 removeNode 함수를 완성하여 연결 리스트에서 특정 숫자가 저장된 노드를 삭제하세요. 
단, 머리 노드 삭제 기능은 구현하지 않아도 됩니다.

예
입력
10 20 30 40 50 60 70 80 90 100
40

결과
100 90 80 70 60 50 30 20 10
 
* sample
/*
 * linkedlist2.c
 *
 *  Created on: 2017. 4. 3.
 *      Author: 74903
 */
/*
10 20 30 40 50 60 70 80 90 100
40

100 90 80 70 60 50 30 20 10
*/

#include <stdio.h>
#include <stdlib.h>

struct NODE {
    struct NODE *next;
    int data;
};

void addFirst(struct NODE *target, int data)
{
    struct NODE *newNode = malloc(sizeof(struct NODE));
    newNode->next = target->next;
    newNode->data = data;
    target->next = newNode;
}

void removeNode(struct NODE *node, int data)
{
    //TODO:
}

int main()
{
    int numArr[10] = { 0, };
    int removeNum;

    scanf("%d %d %d %d %d %d %d %d %d %d",
        &numArr[0], &numArr[1], &numArr[2], &numArr[3], &numArr[4],
        &numArr[5], &numArr[6], &numArr[7], &numArr[8], &numArr[9]
    );

    scanf("%d", &removeNum);

    struct NODE *head = malloc(sizeof(struct NODE));
    head->next = NULL;

    for (int i = 0; i < 10; i++)
    {
        addFirst(head, numArr[i]);
    }

    removeNode(head, removeNum);

    struct NODE *curr = head->next;

    while (curr != NULL)
    {
        printf("%d ", curr->data);
        curr = curr->next;
    }

    curr = head->next;

    while (curr != NULL)
    {
        struct NODE *next = curr->next;
        free(curr);
        curr = next;
    }

    free(head);

    return 0;
}

* answer #1
void removeNode(struct NODE *node, int data)
{
    //TODO:
	if(node == NULL) return;

	struct NODE *prev = node;
	struct NODE *cur = node->next;
	while(cur != NULL) {
		if(cur->data == data) {
			prev->next = cur->next;
			free(cur);
		}
		prev = cur;
		cur = cur->next;
	}
 }

=======================================================================================
표준 입력으로 3명의 인적 정보가 입력됩니다(홀수 번째는 이름, 짝수 번째는 나이). 
다음 소스 코드에서 getPrintFunc 함수를 작성하여 입력된 인적 정보가 각 줄에 출력되게 만드세요.

정답에는 밑줄 친 부분에 들어갈 코드만 작성해야 합니다.

예
입력
홍대용 49 정약용 18 박제가 30
	
결과
홍대용 49
정약용 18
박제가 30

#include <stdio.h>

struct Person {
    char name[30];
    int age;
    void (*print)(struct Person *);
};

 

void print(struct Person *p)
{
    printf("%s %d\n", p->name, p->age);
}
 
void executer(void (*fp[])(struct Person *), struct Person p[], int count)
{
    for (int i = 0; i < count; i++)
    {
        fp[i](&p[i]);
    }
}

__________________________
__________________________
__________________________
__________________________

 

int main()
{
    struct Person p[3];
    p[0].print = print;
    p[1].print = print;
    p[2].print = print;

    scanf("%s %d %s %d %s %d",
        p[0].name,& p[0].age,
        p[1].name,& p[1].age,
        p[2].name,& p[2].age
    );

    void (*fp[3])(struct Person *);

    for (int i = 0; i < sizeof(p) / sizeof(struct Person); i++)
    {
        fp[i] = getPrintFunc(&p[i]);
    }

    executer(fp, p, sizeof(p) / sizeof(struct Person));

    return 0;
}
=======================================================================================
표준 입력으로 x, y 좌표 두 개가 입력됩니다. 다음 소스 코드를 완성하여 두 점 사이의 거리가 출력되게 만드세요. 
이때 두 점 사이의 거리는 double형 실수로 출력되어야 합니다..
정답에는 밑줄 친 부분에 들어갈 코드만 작성해야 합니다.

입력
10 10 20 20

출력
14.142136

#include <stdio.h>
#include <math.h>

struct Point2D {
    int x;
    int y;
};

___________________________
____________________________
____________________________
____________________________
____________________________
____________________________
____________________________

int main()
{
    struct Point2D p1;
    struct Point2D p2;
	
    scanf("%d %d %d %d", &p1.x, &p1.y, &p2.x, &p2.y);
    printf("%f\n", getDistance(p1, p2));

    return 0;
}

*answer #1
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

struct Point2D {
    int x;
    int y;
};

float getDistance(struct Point2D p1, struct Point2D p2) {
    int x = pow(p1.x-p2.x, 2);
    int y = pow(p1.y-p2.y, 2);

    return sqrt(x+y);
}

int main(int argc, char * argv[]) {
    if(argc < 5)
    {
        printf("argc error\n");
        return -1;
    }

    struct Point2D p1;
    struct Point2D p2;

    p1.x = atoi(argv[1]);
    p1.y = atoi(argv[2]);
    p2.x = atoi(argv[3]);
    p2.y = atoi(argv[4]);

    printf("%f\n", getDistance(p1, p2));
}

* answer #2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct Point2D {
    int x;
    int y;
};

float getDistance(struct Point2D p1, struct Point2D p2) {
    int point1 = 0;
    int point2 = 0;
    float fval = 0.0f;
    point1 = p2.x - p1.x;
    point2 = p2.y - p1.y;

    fval = sqrt(pow(point1,2) + pow(point2,2));

    return fval;
}

int main()
{
    struct Point2D p1;
    struct Point2D p2;

    scanf("%d %d %d %d", &p1.x, &p1.y, &p2.x, &p2.y);
    printf("%f\n", getDistance(p1, p2));

    return 0;
}

=======================================================================================
이번 연습문제에서는 1~1000까지 369 게임 시 박수를 몇 번 치게 되는지 계산하는 프로그램을 작성한다.

※ 369 게임이란?
1) 숫자를 1부터 차례대로 세면서 3, 6, 9가 나오면 그 개수만큼 박수를 치는 게임이다.
2) 10의 자리에서 369 숫자가 중복으로 겹칠시에는(ex. 33, 36, 39) 박수를 두 번 치게 된다.
3) 100의 자리에서 369 숫자가 중복으로 두 번 겹칠 시에는(ex. 133, 169, 193) 박수를 두 번 치게 된다.
4) 100의 자리에서 369 숫자가 중복으로 세 번 겹칠 시에는(ex. 333, 666, 699) 박수를 세 번 치게 된다.

<요구사항>
1. 제공된 프로그램을 완성하며, 1부터 어느 수까지 369게임을 할 것인지는 아규먼트로 입력한다.
2. 입력이 허용된 숫자는 1~10,000이며, 1이하는 1로, 10,000 이상은 10,000으로 처리한다.
3. 입력된 숫자까지 박수의 총 횟수를 표준 출력 장치에 표시한다.

<실행예시>
./game.exe 100
60
 
* answer #1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[] ) {
	int number, count=0;
	char numStr[10];

	if (argc != 2){
		printf ("Please execute with Number\nex)game.exe 1000");
		return EXIT_SUCCESS;
	}

	number = atoi(argv[1]);
	if (number < 1) number = 1;
	else if (number > 10000) number = 10000;

	for(int i=1; i<=number; i++)
	{
		sprintf(numStr, "%d", i);

		for (int j=0; j<sizeof(numStr); j++)
		{
			if (numStr[j]=='3' || numStr[j] == '6' || numStr[j]=='9')
				count++;
		}
	}
	printf ("%d\n", count);

	return EXIT_SUCCESS;
}
=======================================================================================
이번 연습문제에서는 정수와 실수를 비트 형태로 출력하는 프로그램을 작성한다.
<요구사항>
1. 정수와 실수를 하나씩 순서대로 입력받아 비트열을 출력한다.
2. Little Endian 시스템에서 수행하는것으로 가정한다.
※ Little Endian 시스템이란, 값이 작은 바이트를 메모리 낮은 번지부터 저장하는 방식임.
3. 4비트씩 끊어서 출력한다. (ex. 1111 0000 1010 0101)

<실행예시>
$ ./print_bit.exe 1000 1234.56
0000 0000 0000 0000 0000 0011 1110 1000 : 1000
0100 0100 1001 1010 0101 0001 1110 1100 : 1234.560059
$ ./print_bit.exe -1 -1.999999
1111 1111 1111 1111 1111 1111 1111 1111 : -1
1011 1111 1111 1111 1111 1111 1111 1000 : -1.999999

* answer #1
/*
 * 정수와 실수를 비트 형태로 출력하는 프로그램을 작성한다.
 *
 * 요구사항
 * - 정수와 실수를 하나씩 순서대로 입력 받아 비트열을 출력한다.
 * - Little Endian 시스템에서 수행하는 것으로 가정한다.
 *   ※ Little Endian 시스템이란, 값이 작은 바이트를 메모리 낮은 번지 부터 저장하는 방식임.
 * - 4비트씩 끊어서 출력한다. (ex. 1111 0000 1010 0101)
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_usage();

int main(int argc, char *argv[]) {

	int inum;
	float fnum;

	//아규먼트를 입력 여부를 확인한다.
	if(argc != 3)
	{
		print_usage();
		return EXIT_FAILURE;
	}

	inum = atoi(argv[1]);
	int size = sizeof(int)*8;
	char* p = (char*)malloc(size+1);

	for(int i=size-1; i>=0; i--) {
		p[i] = (1 & inum);
		inum >>= 1;
	}
	p[size] = '\0';

	for(int i=0; i<size; i++) {
		printf("%d", p[i]);
		if(((i+1) % 4) == 0)
			printf(" ");
	}
	free(p);

	int nPlus = 0;
	if(argv[2][0] == '-')
		nPlus = 1;

	printf("\n");

	fnum = atof(argv[2]);
	bit_ptn(*((int*)&fnum));

	return EXIT_SUCCESS;
}

void bit_ptn(int n) {
	for(int i=31; i>=0; i--) {
		printf("%d", (n & (1<<i))==0? 0: 1);
		if(i != 0 && (i%4 == 0))
			printf(" ");
	}
}
/*
 * 사용법을 출력한다.
 */
void print_usage()
{
	puts("[usage] print_bit.exe decimal float");
}

* answer #2
#include <stdio.h>
#include <stdlib.h>

void bit_prn(int n) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", ((n & (1 << i)) == 0) ? 0 : 1);
        if ( i != 0 ) {
            printf("%s", ((i % 4) == 0) ? " " : "");
        }
    }
}

int main(int argc, char * argv[]) {
    int a;
    float b;

    if (argc > 1) {
        a = atoi(argv[1]);
    }

    if (argc > 2) {
        b = atof(argv[2]);
    }

    bit_prn(a);
    printf(" : %d\n", a);

    bit_prn(*((int*) &b));
    printf(" : %f\n", b);

    return 0;
}

* answer #3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void change_bit(int val) {
    int i;
    for (i=31; i >=0; i--) {
        printf("%d", (val & (1 << i) ? 1 : 0));
        if (i != 0)
            printf("%s", ((i%4) == 0) ? " " : "");
    }
}

int main(int argc, char** argv) {
    int i,j;
    char buf[30] = {0,};
    int digit;
    float fValue;

    if (argc < 3) {
        printf("usage : ./print_bit.exe 123 43.13 \n");
        return 0;
    }

    digit = atoi(argv[1]);
    fValue = atof(argv[2]);

    change_bit(digit);
    printf(" : %d\n", digit);
    change_bit(*((int*) &fValue));
    printf(" : %f\n", fValue);

    return 0;
}
=======================================================================================
프로그램 명: complete_graph 

제한시간: 1 초 
꼭지점(vertex)의 수 n 이 주어질 때 임의의 점에서 다른 점으로 바로 가는 길이 존재할 때 선의 수(edge) 을 구하는 것이 문제이다. 

n 이 4 이면 6 개의 선이 존재한다. 

입력
n 이 주어진다. n 은 2 이상 1000 이하의 정수이다. 
출력
선의 수를 출력한다. 

입출력 예
입력
4
출력
6
* 이러한 그래프를 완전 그래프(complete graph)라 합니다. 

/*
 * complete_graph.c
 *
 *  Created on: 2017. 3. 20.
 *      Author: 74903
 */

#include <stdio.h>

void main() {
	setbuf(stdout, NULL);
	printf("점의 갯수를 입력하세요:");

	int num=0;
	scanf("%d", &num);

	int nTotalLine = num*(num-1) /2;

	printf("선의 갯수는 [%d]입니다.", nTotalLine);
	return ;
}

	
=======================================================================================
주희는 심심해서 다음과 같이 수를 쓰기 시작 했다. 

이렇게 수를 쓰는 경우 어떤 수가 몇 층에 있는지가 궁금해 졌다. 
참고로 100 은 7 층에 존재 한다. 

입력
32 비트 정수 범위내의 값이 입력으로 주어진다. 
출력
층 수를 출력한다. 

입출력 예
입력
100
출력
7
♣n 개의 노드를 가지는 complete binary tree 의 depth 를 구하는 문제입니다. 

* answer #1
/*
 * flr.c
 *
 *  Created on: 2017. 3. 20.
 *      Author: 74903
 */
#include<stdio.h>

void main()
{
	int num = 0;
	fflush(stdin);

	printf("숫자를 입력하세요:");
	scanf("%d", &num);

	int nFloor = 2;
	int nStart = 0, nLast = 1;
	int nDur = 1;

	if(num < 0) {
		printf("음수는 싫어요");
		return;
	}
	else if(num == 1) {
		printf("%d는 1층에 있습니다.", num);
		return;
	}
	while(1) {
		nDur *= 2;

		nStart = nLast+1;
		nLast = nStart+nDur -1;
		printf("[%d]층, start[%d], last[%d], nDur[%d]\n", nFloor, nStart, nLast, nDur);
		if((num >= nStart) && (num <= nLast))
			break;

		nFloor++;
	}

	printf("%d는 %d층에 있습니다.", num, nFloor);
	return;
}	
