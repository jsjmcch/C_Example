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
==============================================================================================
#include <stdio.h>
#include <stdlib.h>

#define ROW 3 //행의 길이
#define COL 5 //열의 길이

int** make_2dArray(int row, int col);
void free_2dArray(int **arr, int row);

int main() {
	/*
	 * 2차원 배열 처럼 활용 할 수 있도록 메모리를 할당 받아서
	 * 주소를 이중 포인터에 저장한다.
	 */
    int **arr = make_2dArray(ROW, COL);

    if(arr==NULL)
    {
    	puts("메모리 할당 실패\n");
    	return 0;
    }

    /* 2차원 배열 처럼 활용한다. */
	arr[0][0] = 6;
    arr[1][1] = 3;
    arr[2][3] = 2;

    printf("%d\n", arr[0][0]);
    printf("%d\n", arr[1][1]);
    printf("%d\n", arr[2][3]);

	/*
	 * 메모리 leak이 일어나지 않게 메모리를 해제한다.
	 */
    free_2dArray(arr, ROW);

    return 0;
}

/* 행의 길이(row), 열의 길이(col)를 입력 받아서
 * 2차원 배열과 같이 활용 할 수 있도록 메모리를 할 당 한 후
 * 메모리의 주소를 return 한다.
 */
int** make_2dArray(int row, int col)
{
	/* 행 길이*포인터크기 만큼 메모리를 할당 한다. */
    int **td_arr = malloc(sizeof(int *) * row);

    if(td_arr != NULL) {

		/* 행 길이 만큼 반복 하면서 열 길이 만큼 메모리를 할당 한다. */
		for (int i = 0; i<row; i++)
		{
			td_arr[i] = malloc(sizeof(int) * col);
			if(td_arr[i]==NULL)
				return NULL;
		}
    }
    return td_arr;
}

/* 할당 받은 메모리를 해제한다.
 */
void free_2dArray(int **arr, int row)
{
	/* 행 길이 만큼 반복하면서 메모리를 해제한다 */
    for (int i = 0; i < row; i++)
        free(arr[i]);

    /* 이중 포인터에 할당 된 메모리를 해제한다 */
    free(arr);
}

==============================================================================================

==============================================================================================

==============================================================================================

==============================================================================================

==============================================================================================

==============================================================================================

==============================================================================================

==============================================================================================
