#include "star.h"

void loop_1(long page, long* arr){ //한자리 숫자일 경우 사용하는 함수
	long t1; //for loop에 들어가는 변수 정의
	for(t1 = 1; t1 <= page; t1++){ //페이지 수만큼 for loop 실행
		arr[t1]++; //각 페이지수에 해당되는 개수만큼 count
	}
}

void loop_2(long page, long* arr){ //두자리 숫자일 경우 사용하는 함수
	long t1; //for loop에 들어가는 함수 정의
	loop_1(9, arr); //한자리 페이지까지 count
	for (t1 = 10; t1 <= page; t1++){ //두 자리 숫자에 해당하는 경우만 for loop에서 count
		arr[t1 / 10]++; //두 자리 페이지 숫자의 10의 자리 count
		arr[t1 % 10]++; //두 자리 페이지 숫자의 1의 자리 count
	}
}

void loop_3(long page, long* arr){ //세자리 숫자일 경우 사용하는 함수
	long t1; //for loop에 들어가는 변수 정의
	loop_2(99, arr); //두 자리 페이지까지 count
	for (t1 = 100; t1 <= page; t1++){ //세자리 숫자에 해당하는 경우만 for loop에서 count
		arr[t1 / 100]++; //세 자리 페이지 숫자의 100의 자리 count
		arr[(t1 % 100) / 10]++; //세 자리 페이지 숫자의 10의 자리 count
		arr[t1 % 10]++; //세 자리 페이지 숫자의 1의 자리 count
	}
}

void loop_4(long page, long* arr){ //네자리 숫자일 경우 사용하는 함수
	long t1; //for loop에 들어가는 변수 정의
	loop_3(999, arr); //세 자리 페이지까지 count
	for(t1 = 1000; t1 <= page; t1++){ //네자리 숫자에 해당하는 경우만 for loop에서 count
		arr[t1 / 1000]++; //네 자리 페이지 숫자의 1000의 자리 count
		arr[(t1 % 1000) / 100]++; //네 자리 페이지 숫자의 100의 자리 count
		arr[(t1 % 100) / 10]++; //네 자리 페이지 숫자의 10의 자리 count
		arr[t1 % 10]++; //네 자리 페이지 숫자의 1의 자리 count
	}
}

void loop_5(long page, long* arr){ //다섯자리 숫자일 경우 사용하는 함수
	long t1; //for loop에 들어가는 변수 정의
	loop_4(9999, arr); //네자리 페이지까지 count
	for (t1 = 10000; t1 <= page; t1++){ //다섯자리 숫자에 해당하는 경우만 for loop에서 count
		arr[t1 / 10000]++; //다섯자리 페이지 숫자의 10000의 자리 count
		arr[(t1 % 10000) / 1000]++; //다섯자리 페이지 숫자의 1000의 자리 count
		arr[(t1 % 1000) / 100]++; //다섯자리 페이지 숫자의 100의 자리 count
		arr[(t1 % 100) / 10]++; //다섯자리 페이지 숫자의 10의 자리 count
		arr[t1 % 10]++; //다섯자리 페이지 숫자의 1의 자리 count
	}
}

void loop_6(long page, long* arr){ //여섯자리 숫자일 경우 사용하는 함수
	long t1;  //for loop에 들어가는 변수 정의
	loop_5(99999, arr); //다섯자리 페이지까지 count
	for (t1 = 100000; t1 <= page; t1++){ //여섯자리 숫자에 해당하는 경우만 for loop에서 count
		arr[t1 / 100000]++; //여섯자리 페이지 숫자의 100000의 자리 count
		arr[(t1 % 100000) / 10000]++; //여섯자리 페이지 숫자의 10000의 자리 count
		arr[(t1 % 10000) / 1000]++; //여섯자리 페이지 숫자의 1000의 자리 count
		arr[(t1 % 1000) / 100]++; //여섯자리 페이지 숫자의 100의 자리 count
		arr[(t1 % 100)/ 10]++; //여섯자리 페이지 숫자의 10의 자리 count
		arr[t1 % 10]++; //여섯자리 페이지 숫자의 1의 자리 count
	}
} 

void loop_7(long page, long* arr){ //일곱자리 숫자일 경우 사용하는 함수
	long t1; //for loop에 들어가는 변수 정의
	loop_6(999999, arr); //여섯자리 페이지까지 count
	for (t1 = 1000000; t1 <= page; t1++){ //일곱자리 숫자에 해당하는 경우만 for loop에서 count
		arr[t1 / 1000000]++; //일곱자리 페이지 숫자의 1000000의 자리 count
		arr[(t1 % 1000000) / 100000]++; //일곱자리 페이지 숫자의 100000의 자리 count
		arr[(t1 % 100000) / 10000]++; //일곱자리 페이지 숫자의 10000의 자리 count
		arr[(t1 % 10000) / 1000]++; //일곱자리 페이지 숫자의 1000의 자리 count
		arr[(t1 % 1000) / 100]++; //일곱자리 페이지 숫자의 100의 자리 count
		arr[(t1 % 100) / 10]++; //일곱자리 페이지 숫자의 10의 자리 count
		arr[t1 % 10]++; //일곱자리 페이지 숫자의 1의 자리 count
	}
}

void loop_8(long page, long* arr){ //여덟자리 숫자일 경우 사용하는 함수
	long t1; //for loop에 들어가는 변수 정의
	loop_7(9999999, arr); //일곱자리 페이지까지 count
	for (t1 = 10000000; t1 <= page; t1++){ //여덟자리 숫자에 해당하는 경우만 for loop에서 count
		arr[t1 / 10000000]++; //여덟자리 페이지 숫자의 10000000의 자리 count
		arr[(t1 % 10000000) / 1000000]++; //여덟자리 페이지 숫자의 1000000의 자리 count
		arr[(t1 % 1000000) / 100000]++; //여덟자리 페이지 숫자의 100000의 자리 count
		arr[(t1 % 100000) / 10000]++; //여덟자리 페이지 숫자의 10000의 자리 count
		arr[(t1 % 10000) / 1000]++; //여덟자리 페이지 숫자의 1000의 자리 count
		arr[(t1 % 1000) / 100]++; //여덟자리 페이지 숫자의 100의 자리 count
		arr[(t1 % 100) / 10]++; //여덟자리 페이지 숫자의 10의 자리 count
		arr[t1 % 10]++; //여덟자리 페이지 숫자의 1의 자리 count
	}
}

void loop_9(long page, long* arr){ //아홉자리 숫자일 경우 사용하는 함수
	long t1; //for loop에 들어가는 변수 정의
	loop_8(99999999, arr); //여덟자리 페이지까지 count
	for(t1 = 100000000; t1 <= page; t1++){ //아홉자리 숫자에 해당하는 경우만 for loop에서 count
		arr[t1 / 100000000]++; //아홉자리 페이지 숫자의 100000000의 자리 count
		arr[(t1 % 100000000) / 10000000]++; //아홉자리 페이지 숫자의 10000000의 자리 count
		arr[(t1 % 10000000) / 1000000]++; //아홉자리 페이지 숫자의 1000000의 자리 count
		arr[(t1 % 1000000) / 100000]++; //아홉자리 페이지 숫자의 100000의 자리 count
		arr[(t1 % 100000) / 10000]++; //아홉자리 페이지 숫자의 10000의 자리 count
		arr[(t1 % 10000) / 1000]++; //아홉자리 페이지 숫자의 1000의 자리 count
		arr[(t1 % 1000) / 100]++; //아홉자리 페이지 숫자의 100의 자리 count
		arr[(t1 % 100) / 10]++; //아홉자리 페이지 숫자의 10의 자리 count
		arr[t1 % 10]++; //아홉자리 페이지 숫자의 1의 자리 count
	}
} 
