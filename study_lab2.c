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
==================================================================================

1.strcmp함수로 문자열을 비교했을 때 반환값이 올바른 것을 모두 고르세요(Visual Studio 기준).

a.strcmp("hello", "hello"); → 1
b.strcmp("hello", "world"); → 1
c.strcmp("hello", "world"); → -1
d.strcmp("world", "world"); → 0
e.strcmp("ccc", "ddd"); → 0
f.strcmp("ccc", "ddd"); → -1
하나 혹은 하나 이상을 선택하세요. 

 
2.. strcpy 함수를 사용하여 "Hello" 문자열을 char 배열에 복사할 때 배열의 최소 크기는 얼마가 되어야 할까요?
a. 5 
b. 6 
c. 8 
d. 10 
e. 20 
하나를 선택하세요.

3. strcat 함수를 사용하여 "Hello" 문자열과 "world" 문자열을 붙였을 때 최종 문자열이 차지하는 공간은 몇 바이트일까요? 
   (숫자만 입력) 각 문자열은 char 배열입니다.

4.strcpy 함수가 선언된 헤더 파일은?
a. stdio.h 
b. stdlib.h 
c. string.h 
d. limits.h 
e. strings.h 
하나를 선택하세요. 

5. 문자 배열 s1에 "Hello, world!" 문자열을 생성하여 저장하는 코드로 올바른 것을 고르세요.
a.sprintf("Hello, %s", s1, "world!");
b.sprintf("Hello, %s", "world!");
c.sprintf("Hello, %s", s1);
d.sprintf(s1, "Hello, %s", "world!");
e.sprintf("world!", "Hello, %s", s1);
하나를 선택하세요.

6.문자 배열 s1이 "a 10" 형태가 되도록 코드를 완성하세요.
sprintf(s1,  빈칸, 'a', 10);

7.다음 중 문자열 안에서 문자로 검색하는 함수를 모두 고르세요.
a. strcmp 
b. strstr 
c. strchr 
d. strcpy 
e. strrchr 
f. strcat 

8.문자 배열 s1에서 "Dia"으로 시작하는 문자열을 검색한 뒤 메모리 주소를 ptr에 저장하려고 합니다. 올바른 코드를 고르세요.
a.char s1 = strstr(ptr, "Dia");
b.char *ptr = strstr(s1, "Dia");
c.strstr *ptr = char(s1, "Dia");
d.char *s1 = strstr("Dia", ptr);
e.char ptr = strstr("Dia", s1);
하나를 선택하세요.

9.다음 중 문자열을 자르는 함수는?
a. strcmp 
b. strstr 
c. strchr 
d. strtok 
e. strrchr 


10.strtok 함수의 설명으로 잘못된 것을 모두 고르세요.
a. 기준 문자는 하나만 지정할 수 있음 
b. 문자열을 자를 때 기준 문자 부분을 NULL로 채움 
c. 문자열을 복제한 뒤 포인터를 반환함 
d. 자르는 문자열의 내용을 바꿈 
e. strtok(NULL, " ")처럼 NULL을 넣어주면 이전 strtok 함수에서 처리했던 문자열에서 잘린 문자열만큼 문자로 이동한 뒤 다음 문자열을 자름 
f. 잘린 문자열의 포인터만 반환함 
   
1. c,d,f 
2. b 
3. 11 
4. C 
5. d 
6. "%c %d" 
7. c,e 
8. b 
9. d 
10. a, c 
==================================================================================
typedef 함수포인터 사용

지난번에 이야기한 struct의 typedef을 사용한 바와 같이typedef은 데이터 타입에 대해서 따로 별명을 붙여서 주어 간편하게 쓰는데 목적이 있다고 했다.
그럼 함수포인터에 대해서 typedef을 쓰는이유는? 당연히 간편하게 쓸려고 그런거다.

우선 함수포인터의 쓰는 방법 부터 보자.
int test(int num){
	printf("input num is %d.\n", num);
}

int main()
{
	int (*testptr)(int);
	testptr = test;
	testptr(100);
}

위의 코드에서와 같이 호출하고자 하는 함수 이름 대신에 별표(*) 포인터변수를 적어주면된다.

    ****>> 리턴타입 + (* 함수포인터 변수) ( 함수 인자 타입, .... )
    
그럼 왜 typedef 함수 포인터를 선언하는가?
예제에서와 같이 int (*testptr)(int); 식으로 적어서 함수포인터 변수를 선언하면 되는데 매번 이런식으로 적으면 코드가 길어지기도 하지만 
뭔가 눈에 쏙쏙들어오지 않는다.보통 변수타입 + 변수명 으로 선언을 하기 때문에 그렇다. 
그래서 아래와 같이
typedef int (*TestFuncPtr)(int);

이런 식으로 선언을 해놓고 아래와 같이 쓰면 보기에도 좋고 간편하니 보통 이렇게 쓴다.
TestFuncPtr testptr;

정리
함수포인터를 typedef 선언해서 쓰는 이유는 보기 쉽고 간편해서이다.

typedef int (*TestFuncPtr)(int);	// 선언
TestFuncPtr testptr; 		        // 사용
==================================================================================
#include <stdio.h>
#include <stdarg.h>

void printNumbers( int args, ...) {
    va_list ap;

    va_start(ap, args);
    for( int i=0; i<args; i++) {
        int num = va_arg(ap, int);
        printf("%d ", num);
    }
    va_end(ap);
    printf("\n");
}

int main() {
    printNumbers(1, 10);
    printNumbers(2, 10, 20);
    printNumbers(3, 10, 20, 30);
    printNumbers(4, 10, 20, 30, 40);

    return 0;
}    
==================================================================================
<GOTO>
#include <stdio.h>
int main()
{
    int num1 = 0;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (num1 == 20)    // num1이 20이라면
                goto EXIT;     // 레이블 EXIT로 즉시 이동

            num1++;
        }
    }

EXIT:    // 레이블 EXIT
    printf("%d\n", num1);    // 20

    return 0;
}
변수 num1이 20이 되면 goto를 사용하여 레이블 EXIT로 즉시 이동합니다. 따라서 안쪽과 바깥쪽 루프를 break로 끝낼 필요가 없습니다.
이처럼 goto는 다중 루프를 빠져나올 때 유용합니다. 여기서는 for 반복문을 예로 들었지만 while, do while로 된 중첩 루프도 빠져 나올 수 있습니다.
	
	
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
    int gender;      // 성별: 남자 1, 여자 2
    int age;         // 나이
    int isOwner;     // 주택 소유 여부: 자가 1, 전월세 0

    scanf("%d %d %d", &gender, &age, &isOwner);

    printf("안녕하세요.\n");
    printf("문을 연다.\n");

    if (gender == 2)
        goto EXIT;    // 에러가 발생했으므로 EXIT로 이동

    if (age < 30)
        goto EXIT;    // 에러가 발생했으므로 EXIT로 이동

    if (isOwner == 0)
        goto EXIT;    // 에러가 발생했으므로 EXIT로 이동
 
EXIT:
    printf("안녕히계세요.\n");    // 에러 처리 코드를
    printf("문을 닫는다.\n");     // 한 번만 사용함

    return 0;    // 프로그램 종료
}
이제 조건이 맞지 않아 에러가 발생할 때마다 EXIT로 이동하여 에러 처리 코드(인사를 한 뒤 문을 닫기)를 실행합니다. 
즉, 종료 직전에 항상 실행해야 하는 에러 처리 코드들은 한 곳에 모아놓고 goto를 사용하면 중복 코드를 없앨 수 있고, 
코드의 의도도 좀 더 명확해집니다.

실무에서는 파일을 열어놓거나 메모리를 할당한 상태에서 에러가 발생하면 파일을 닫거나 
메모리를 해제한 뒤 프로그램을 종료하는 패턴을 주로 사용합니다. 

#include <stdio.h>

int main()
{
    int num1 = 1;

    for (int i = 0; i < 10; i++)
    {
        switch (num1)
        {
        case 1:
            printf("1입니다.\n");
            ① ______________
        default:
            break;
        }
    }

②___________
    return 0;
}
① goto EXIT;
② EXIT:
해설
for 반복문으로 10번 반복하고 있습니다. 만약 case 1:에서 break를 사용하면 switch만 빠져나가고, for 반복문은 계속 실행되기 때문에 "1입니다"가 
10번 출력됩니다. 따라서 for 반복문 바깥에 레이블 EXIT를 만들고, case 1:에서 goto를 사용하여 EXIT로 이동하면 
switch와 for에서 한 번에 빠져나올 수 있습니다.
==================================================================================
#include <stdio.h>
#include <stdlib.h>    // malloc, free 함수가 선언된 헤더 파일

int main()
{
    int **m = malloc(sizeof(int *) * 3);   // 이중 포인터에 (int 포인터 크기 * 세로 크기)만큼
                                           // 동적 메모리 할당. 배열의 세로

    for (int i = 0; i < 3; i++)            // 세로 크기만큼 반복
    {
        m[i] = malloc(sizeof(int) * 4);    // (int 크기 * 가로 크기)만큼 동적 메모리 할당.
                                           // 배열의 가로
    }

    m[0][0] = 1;    // 세로 인덱스 0, 가로 인덱스 0인 요소에 값 할당
    m[2][0] = 5;    // 세로 인덱스 2, 가로 인덱스 0인 요소에 값 할당
    m[2][3] = 2;    // 세로 인덱스 2, 가로 인덱스 3인 요소에 값 할당

    printf("%d\n", m[0][0]);    // 1: 세로 인덱스 0, 가로 인덱스 0인 요소의 값 출력
    printf("%d\n", m[2][0]);    // 5: 세로 인덱스 2, 가로 인덱스 0인 요소의 값 출력
    printf("%d\n", m[2][3]);    // 2: 세로 인덱스 2, 가로 인덱스 3인 요소의 값 출력

    for (int i = 0; i < 3; i++)    // 세로 크기만큼 반복
    {
        free(m[i]);                // 2차원 배열의 가로 공간 메모리 해제
    }

    free(m);    // 2차원 배열의 세로 공간 메모리 해제

    return 0;
}

#include <stdio.h>
#include <stdlib.h>    // malloc, free 함수가 선언된 헤더 파일

int main()
{
    int row, col;

    scanf("%d %d", &row, &col);

    int **m = malloc(sizeof(int *) * row);   // 이중 포인터에 (int 포인터 크기 * row)만큼
                                             // 동적 메모리 할당. 배열의 세로

    for (int i = 0; i < row; i++)            // 세로 크기만큼 반복
    {
        m[i] = malloc(sizeof(int) * col);    // (int의 크기 * col)만큼 동적 메모리 할당. 배열의 가로
    }

    for (int i = 0; i < row; i++)    // 세로 크기만큼 반복
    {
        for (int j = 0; j < col; j++)    // 가로 크기만큼 반복
        {
            m[i][j] = i + j;             // 2차원 배열의 각 요소에 i + j 값을 할당
        }
    }

    for (int i = 0; i < row; i++)    // 세로 크기만큼 반복
    {
        for (int j = 0; j < col; j++)    // 가로 크기만큼 반복
        {
            printf("%d ", m[i][j]);      // 2차원 배열의 인덱스에 반복문의 변수 i, j를 지정
        }
        printf("\n");                // 가로 요소를 출력한 뒤 다음 줄로 넘어감
    }

    for (int i = 0; i < row; i++)    // 세로 크기만큼 반복
    {
        free(m[i]);                  // 2차원 배열의 가로 공간 메모리 해제
    }

    free(m);    // 2차원 배열의 세로 공간 메모리 해제

    return 0;
}
소스를 컴파일하여 실행한 뒤 4 5를 입력하고 엔터 키를 누르세요.

실행 결과
4 5 (입력)
0 1 2 3 4
1 2 3 4 5
2 3 4 5 6
3 4 5 6 7
==================================================================================
포인터에 할당된 메모리를 3차원 배열처럼 사용하기
다음 소스 코드를 완성하여 포인터에 할당된 메모리를 높이 2, 세로 크기 3, 가로 크기 5인 3차원 배열처럼 사용할 수 있도록 만드세요.

practice_pointer_like_three_dimensional_array.c
#include <stdio.h>
#include <stdlib.h>

int main()
{
    long long ***m = malloc(sizeof(long long **) * 2);

    ①_____________________________________________________
    ...                                                   
    ______________________________________________________

    m[1][2][4] = 100;

    printf("%lld\n", m[1][2][4]);

    ②_____________________________________________________
    ...                                                   
    ______________________________________________________

    free(m);

    return 0;
}

실행 결과
100

정답
①
for (int depth = 0; depth < 2; depth++)
{
    m[depth] = malloc(sizeof(long long *) * 3);

    for (int row = 0; row < 3; row++)
    {
        m[depth][row] = malloc(sizeof(long long) * 5);
    }
}

②
for (int depth = 0; depth < 2; depth++)
{
    for (int row = 0; row < 3; row++)
    {
        free(m[depth][row]);
    }

    free(m[depth]);
}
==================================================================================
    
==================================================================================

==================================================================================
    
==================================================================================

==================================================================================
    
==================================================================================

==================================================================================
    
==================================================================================

==================================================================================
    
==================================================================================

    
