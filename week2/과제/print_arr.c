#include "star.h"

void print_arr(long* arr){
	long t1; //for loop에 들어가는 변수 정의
	for (t1 = 0; t1 < 10; t1++){ //0부터 9까지의 count가 arr의 0에서 9 인덱스에 저장되어 있으므로 0-9까지 loop
		printf("%ld ", arr[t1]); // t1번째 인덱스의 count
	}
	printf("\n"); //줄바꿈
}
