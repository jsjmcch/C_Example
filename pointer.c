* reference : https://www.youtube.com/watch?v=M7KPfIBzxZ8

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    char arr_comp[] = "Korea fighting";
    char *ptr_comp = "korea is good country";

    // 배열은 strcpy는 되지만 direct로 저장은 되지 않는다.
    // 왜냐하면 배열은 상수이기때문
    // strcpy(arr_comp, "korea good"); (o)
    // arr_comp = "korea good";        (X)
    arr_comp[3] = 's'; // 가능
    printf("arr_comp_1 = %s\n", arr_comp);
    strcpy(arr_comp, "dae han min kook");   // 가능
    printf("arr_comp_2 = %s\n", arr_comp);
    //arr_comp = "good place";  // 불가능


    // 포인터 문자열은 direct로 저장은 되지만 strcpy는 되지 않는다.
    // 왜냐면, 포인터 문자열은 데이타영역(code segment)에 저장되므로
    // const 이므로 strcpy가 되지 않음.
    // dircet 저장은 data영역에 새롭게 추가되기 때문에 가능함

    ptr_comp[3] = 's';  // 가능
    ptr_comp = "change word";   // 가능, "change word"라는 문자열이 data영역의 새로운 주소에 생성됨
    printf("ptr_comp_1 = %s\n", ptr_comp);
    strcpy(ptr_comp, "good good");  // compile은 되지만 fault에러 발생함

    return 0;
}
==============================================================================================
<two pointer>
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
==============================================================================================
#include <stdio.h>

#if 1
void swapIntPtr(int *p1, int *p2)
{
    int *tmp;
    *tmp = *p1;
    *p1 = *p2;
    *p2 = *tmp;
}
#else
void swapIntPtr_2(int **p1, int **p2)
{
    int *tmp;
    tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}
#endif

int main(void) {
    int num1=10, num2=20;
    int *ptr1, *ptr2;

    ptr1=&num1, ptr2=&num2;

    printf("*ptr1, *ptr2: %d %d\n", *ptr1, *ptr2);

    // 함수 호출 후 ptr1과 ptr2가 가리키는 값이 바뀌었는지 살펴본다.
    swapIntPtr(ptr1, ptr2);
    //swapIntPtr(&num1, &num2);
    //swapIntPtr_2(&ptr1, &ptr2);

    printf("*ptr1, *ptr2: %d %d\n", *ptr1, *ptr2);

    return 0;
}
==============================================================================================
#include <stdio.h>

#if 0
void swapIntPtr(int *p1, int *p2)
{
    int *tmp;
    *tmp = *p1;
    *p1 = *p2;
    *p2 = *tmp;
}
#else
void swapIntPtr_2(int **p1, int **p2)
{
    int *tmp;
    tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}
#endif

int main(void) {
    int num1=10, num2=20;
    int *ptr1, *ptr2;

    ptr1=&num1, ptr2=&num2;

    printf("*ptr1, *ptr2: %d %d\n", *ptr1, *ptr2);

    // 함수 호출 후 ptr1과 ptr2가 가리키는 값이 바뀌었는지 살펴본다.
    //swapIntPtr(ptr1, ptr2);
    //swapIntPtr(&num1, &num2);
    swapIntPtr_2(&ptr1, &ptr2);

    printf("*ptr1, *ptr2: %d %d\n", *ptr1, *ptr2);

    return 0;
}
==============================================================================================

==============================================================================================

==============================================================================================

==============================================================================================

==============================================================================================

==============================================================================================

==============================================================================================

==============================================================================================

==============================================================================================
