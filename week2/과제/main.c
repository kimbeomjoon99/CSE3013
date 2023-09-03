#include "star.h"

int main(){
	long t; //테스트케이스의 횟수  정의
	scanf("%ld", &t); //테스트케이스 횟수 입력받기
	long t1, t2; //for loop안에 들어가는 변수 정의
	long arr[10]; //0부터 9까지 나온 횟수를 저장하는 배열 정의
	for (t1 = 0; t1 < t; t1++){ //테스트케이스만큼 loop를 도는 for문
		long page; //책 페이지수의 정의
		scanf("%ld", &page); //페이지수 입력받기
		for (t2 = 0; t2 < 10; t2++){ //각 loop가 시작하기 전 배열의 각 원소를 0으로 초기화
			arr[t2] = 0; //0으로 초기화
		}
		if (page < 10){ //페이지가 한자리 숫자일 때
			loop_1(page, arr); //for_loops.c에서 정의한 한자리 페이지일 때의 함수
		}
		else if (page >= 10 && page < 100){ //페이지가 두자리 숫자일 때
			loop_2(page, arr); //for_loops.c에서 정의한 두자리 페이지일 때의 함수
		}
		else if (page >= 100 && page < 1000){ //페이지가 세자리 숫자일 때
			loop_3(page, arr); //for_loops.c에서 정의한 세자리 페이지일 때의 함수
		}
		else if (page >= 1000 && page < 10000){ //페이지가 네자리 숫자일 때
			loop_4(page, arr); //for_loops.c에서 정의한 네자리 페이지일 때의 함수
		}
		else if (page >= 10000 && page < 100000){ //페이지가 다섯자리 숫자일 때
			loop_5(page, arr); //for_loops.c에서 정의한 다섯자리 페이지일 때의 함수
		}
		else if (page >= 100000 && page < 1000000){ //페이지가 여섯자리 숫자일 때
			loop_6(page, arr); //for_loops.c에서 정의한 여섯자리 페이지일 때의 함수
		}
		else if (page >= 1000000 && page < 10000000){ //페이지가 일곱자리 숫자일 때
			loop_7(page, arr); //for_loops.c에서 정의한 일곱자리 페이지일 때의 함수
		}
		else if (page >= 10000000 && page < 100000000){ //페이지가 여덟자리 숫자일 때
			loop_8(page, arr); //for_loops.c에서 정의한 여덟자리 페이지일 때의 함수
		}
		else if (page >= 100000000 && page < 1000000000){ //페이지가 아홉자리 숫자일 때
			loop_9(page, arr); //for_loops.c에서 정의한 아홉자리 페이지일 때의 함수
		}
		else { //페이지가 열자리(1,000,000,000) 숫자일 때
			loop_9(page, arr); //for_loops.c에서 정의한 아홉자리 페이지일 때의 함수
			arr[0] += 9; // 1,000,000,000에서 0이 9번 나오므로 배열의 0번째 인덱스에 9를 더함
			arr[1]++; // 1,000,000,000에서 1이 1번 나오므로 배열의 1번째 인덱스에 1을 더함
		}
		print_arr(arr); //print_arr.c에서 정의한 출력함수 사용
	}
	return 0;
}
