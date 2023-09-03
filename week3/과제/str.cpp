#include "Str.h"

Str::Str(int leng){ // 문자열의 길이를 입력받는 생성자
	if (leng < 0){  // 문자열의 길이가 0보다 작으면 에러 메시지 출력
		std::cout << "String length must be greater than zero!" << "\n";
		len = 0;
	}
	else{
		str = new char[leng + 1]; // leng + 1만큼 메모리 할당
		int t1;
		for (t1 = 0; t1 <= leng; t1++){ //새로 할당한 문자열을 leng만큼의 공백으로 채움
			str[t1] = ' ';
		}
		str[leng] = '\0';
		len = leng;
	}
}

Str::Str(char *neyong){ // 문자열을 직접 입력받는 생성자
	if (neyong == NULL){ // 빈 문자열이 들어왔을 때 에러 메시지 출력
		std::cout << "The string is null!" << "\n";
		str = new char[1];
		str[0] = '\0';
		len = 0;
	}
	else{ // 문자열을 메모리 할당받아 생성하고 인자로 받은 문자열을 복사하여 넣음
		str = new char[strlen(neyong) + 1];
		len = strlen(neyong);
		strcpy(str, neyong);
	}
}

Str::~Str(){ // 소멸자
	delete[] str;
}

int Str::length(){ // 문자열의 길이를 반환
	return len;
}

char *Str::contents(){ // 문자열의 내용을 반환
	return str;
}

int Str::compare(class Str& s){ // 입력받은 문자열과 기존 문자열의 내용을 비교
	int i = strcmp(str, s.contents());
	return i;
}

int Str::compare(char *s){ // 입력받은 문자열과 기존 문자열의 내용을 비교
	int i = strcmp(str, s);
	return i;
}

void Str::operator=(char *s){ // 입력받은 문자열의 내용을 기존 문자열에 복사
	if (s == NULL){ // 입력받은 문자열의 내용이 존재하지 않을 경우 에러 메시지 출력
		std::cout << "The string argument is null!" << "\n";
		delete[] str;
		str = new char[1];
		str[0] = '\0';
		len = 0;
	}
	else{
		if (len < strlen(s)){ // 입력받은 문자열의 길이가 기존 문자열보다 긴 경우
			delete[] str; // 기존 문자열을 메모리 해제하고
			str = new char[strlen(s) + 1]; // 입력받은 문자열의 길이만큼 다시 메모리를 할당하여
			strcpy(str, s); // 문자열을 복사한다
			len = strlen(str);
		}
		else{ // 입력받은 문자열의 길이가 기존 문자열보다 길지 않은 경우
			strcpy(str, s); // 문자열을 복사
			len = strlen(str);
		}
	}
}

void Str::operator=(class Str&s){ // 입력받은 문자열의 내용을 기존 문자열에 복사
	if (len >= s.length()){ // 입력받은 문자열의 길이가 기존 문자열보다 길지 않은 경우
		strcpy(str, s.contents()); // 문자열을 복사
		len = strlen(str);
	}
	else{ // 입력받은 문자열의 길이가 기존 문자열보다 긴 경우
		delete[] str; // 기존 문자열을 메모리 해제하고
		str = new char[strlen(s.contents()) + 1]; // 입력받은 문자열의 길이만큼 다시 메모리를 할당하여
		strcpy(str, s.contents()); // 문자열을 복사
		len = strlen(str);
	}
}








