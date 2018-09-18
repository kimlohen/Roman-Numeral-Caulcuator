#include <iostream>
#include <cstring>
#include <string>
using namespace std;

/**
*@brief Roman numeral calculator (로마 숫자 계산기)
*@author Minsu Kim (김민수)
*@since 2017.09.13
*/

int convert(char letter) { //Convert from roman to numeric (로마자에서 숫자로 변환) 
	if (letter == 'I') { // I = 1, V = 5, X = 10, L = 50, C  =100 D = 500, M = 1000, Z = 0
		return 1;
	}
	if (letter == 'V') {
		return 5;
	}
	if (letter == 'X') {
		return 10;
	}
	if (letter == 'L') {
		return 50;
	}
	if (letter == 'C') {
		return 100;
	}
	if (letter == 'D') {
		return 500;
	}
	if (letter == 'M') {
		return 1000;
	}
	if (letter == 'Z') {
		return 0;
	}
	else {
		return -10000;
	}
}

int isValid(char *str) { //Determine it it is a valid symbol (유효한 기호인지 판단)
	if (*str == 'I' || *str == 'V' || *str == 'X' || *str == 'L' || *str == 'C' || *str == 'D' || *str == 'M' || *str == 'Z') { 
		return 1; //Returns 1 if it is a Roman numeral (로마자인 경우 1을 반환)
	}
	if (*str == '+' || *str == '-' || *str == '*' || *str == '/' || *str == '\0') { 
		return 2;//Returns 2 if it is a space or arithmetic operator (공백과 산술연산자인 경우 2를 반환)
	}
	return 0;// Returns 0 if it is a invalid symbol(유효한 기호가 아닐 시 0을 반환)
}

void convertC(int result, char* resultC) { // Contvert from numeric to Roman (숫자를 로마자로 변환)
	int k = 0;
	if (result == 0) {
		resultC[k] = 'Z';
		k++;
	}
	if (result / 1000 != 0) {
		for (int l = 0; l < result / 1000; l++) {
			resultC[k] = 'M';
			k++;
		}
		result = result % 1000;
	}
	if (result / 100 != 0) {
		if (result / 100 == 9) {
			resultC[k] = 'C';
			k++;
			resultC[k] = 'M';
			k++;
			result = result % 100;
		}
		if (result / 100 == 4) {
			resultC[k] = 'C';
			k++;
			resultC[k] = 'D';
			k++;
			result = result % 100;
		}
		if (result / 500 == 1) {
			resultC[k] = 'D';
			k++;
			result = result % 500;
		}
		for (int l = 0; l < result / 100; l++) {
			resultC[k] = 'C';
			k++;
		}
		result = result % 100;
	}
	if (result / 10 != 0) {
		if (result / 10 == 9) {
			resultC[k] = 'X';
			k++;
			resultC[k] = 'C';
			k++;
			result = result % 10;
		}
		if (result / 10 == 4) {
			resultC[k] = 'X';
			k++;
			resultC[k] = 'L';
			k++;
			result = result % 10;
		}
		if (result / 50 == 1) {
			resultC[k] = 'L';
			k++;
			result = result % 50;
		}
		for (int l = 0; l < result / 10; l++) {
			resultC[k] = 'X';
			k++;
		}
		result = result % 10;
	}
	if (result != 0) {
		if (result % 10 == 9) {
			resultC[k] = 'I';
			k++;
			resultC[k] = 'X';
			k++;
			result = 0;
		}
		if (result % 10 == 4) {
			resultC[k] = 'I';
			k++;
			resultC[k] = 'V';
			k++;
			result = 0;
		}
		if (result / 5 == 1) {
			resultC[k] = 'V';
			k++;
			result = result % 5;
		}
		for (int l = 0; l < result ; l++) {
			resultC[k] = 'I';
			k++;
		}
	}
	resultC[k] = '\0';
}


int range(int n) { // Determine if it is a valid range (유효한 범위 안의 숫자인지 판단)
	if (n >= 0 && n<4000) {
		return 1;
	}
	else {
		return 0;
	}
}

int main()
{
	int num, count, result, pre, post, temp, escape;
	char resultC[20], awnserC[20];
	string str;

	/**
	*@param num Number of expressions to be received (받게될 식들의 수)
	*@param count Counter of string (문자열의 계수)
	*@param result Program result (좌항의 식을 프로그램이 계산한 값)
	*@param pre Value of the preceding character in the string when comparing Roman letters (로마자 비교시 문자열에서 앞의 문자의 값)
	*@param post Value of the following character in the string when comparing Roman letters (로마자 비교시 문자열에서 뒤의 문자의 값)
	*@param temp Temporary variable (임시 용도 변수)
	*@param escape Loop escape variable (반복문 탈출 용도의 변수)
	*@param resultC Sinrg of the left hand value (좌항의 값이 변환된 문자열)
	*@param awnswerC String of the right hand value (우항의 값이 변환된 문자열)
	*@param str String to be used(사용할 문자열)
	*/

	cin >> num; // Number of test cases (첫번째 입력값, 테스트 케이스의 개수)

	for (int i = 0; i < num; i++) {
		cin >> str; 

		//cout << str << endl;
		// 문자열이 제대로 들어왔는지 확인용 코드


		count = 0;
		result = 0;
		escape = 0;

		while (isValid(&str[count]) != 2) { // 다음 연산자가 오기 전까지 처리

			if (str[count] == str[count + 1] && str[count + 1] == str[count + 2] && str[count + 2] == str[count + 3]) {
				result = 0;
				while (isValid(&str[count]) != 2) {
					count++;
				}
			}// 4번 반복 예외 처리 ex) IIII

			if (isValid(&str[count])==1 && isValid(&str[count+1]) == 1 && isValid(&str[count + 2]) == 1 && convert(str[count]) < convert(str[count+2])) {
				result = 0;
				while (isValid(&str[count]) != 2) {
					count++;
				}
			}// 유효한 문자, 맞지않는 형식 예외처리 ex) IIVI

			if (isValid(&str[count]) == 0) {
				result = 0;
				while (isValid(&str[count]) != 2) {
					count++;
				}
			}// 유효하지 않은 문자 예외처리 ex) VB



			if (isValid(&str[count]) == 1 && isValid(&str[count + 1]) == 1) { // 판단 문자와 뒤 문자가 모두 로마자
				pre = convert(str[count]);
				post = convert(str[count + 1]);
				if (pre < post && (pre * 5 == post || pre * 10 == post)) { 
					result -= pre; 
				}
				else {
					result += pre;
				}
				count++;
			}
			else if(isValid(&str[count]) == 1 && isValid(&str[count+1]) == 2){ // 판단 문자는 로마자, 뒤 문자는 연산자나 \0
				result += convert(str[count]);
				count++;
			}
			else if (isValid(&str[count]) == 1 && isValid(&str[count + 1]) == 0) { // 판단 문자는 로마자, 뒤 문자는 유효하지 않은 문자
				count++;
			}

			//cout << result << endl; 
			//로마 숫자 변환 테스트
		}

		if (range(result) == 0) { // 현재까지 계산한 숫자가 로마숫자 범위 밖이면 0으로 처리
			result = 0;
		}

		while (escape != -1) {
			temp = 0;

			if (str[count] == '\0') { // 숫자와 연산자 사이 띄어쓰기 시 다시 받아옴
				cin >> str;
				count = 0;
			}

			if (str[count] == '+') {
				if (str[count + 1] == '\0') { // 연산자와 숫자 사이 띄어쓰기 시 다시 받아옴
					cin >> str;
					count = -1;
				}
				count++;

				while (isValid(&str[count]) != 2) { // 다음 연산자가 오기 전까지 처리
					if (str[count] == str[count+1] && str[count+1] == str[count+2] && str[count+2] == str[count+3]) {
						result = 0;
						temp = 0;
						while (isValid(&str[count]) != 2) {
							count++;
						}
					}// 4번 반복 예외 처리 ex) IIII

					if (isValid(&str[count]) == 1 && isValid(&str[count + 1]) == 1 && isValid(&str[count + 2]) == 1 && convert(str[count]) < convert(str[count + 2])) {
						result = 0;
						temp = 0;
						while (isValid(&str[count]) != 2) {
							count++;
						}
					}// 유효한 문자, 맞지않는 형식 예외처리 ex) IIVI

					if (isValid(&str[count]) == 0) {
						result = 0;
						temp = 0;
						while (isValid(&str[count]) != 2) {
							count++;
						}
					}// 유효하지 않은 문자 예외처리 ex) VB

					if (isValid(&str[count]) == 1 && isValid(&str[count + 1]) == 1) { // 판단 문자와 뒤 문자가 모두 로마자
						pre = convert(str[count]);
						post = convert(str[count + 1]);
						if (pre < post && (pre * 5 == post || pre * 10 == post)) {
							temp -= pre;
						}
						else {
							temp += pre;
						}
						count++;
					}
					else if(isValid(&str[count]) == 1 && isValid(&str[count+1]) == 2){ // 판단 문자는 로마자, 뒤 문자는 연산자나 \0
						temp += convert(str[count]);
						count++;
					}
					else if (isValid(&str[count]) == 1 && isValid(&str[count + 1]) == 0) { // 판단 문자는 로마자, 뒤 문자는 유효하지 않은 문자
						count++;
					}

					//cout << temp << endl; 
					//로마 숫자 변환 테스트
				}

				if (range(temp) == 0) { // 현재 계산중인 숫자가 로마숫자 범위 밖이면 0으로 처리
					temp = 0;
					result = 0;
				}

				result += temp;

				if (range(result) == 0) { // 현재까지 계산한 숫자가 로마숫자 범위 밖이면 0으로 처리
					result = 0;
				}


			}
			else if (str[count] == '-') {
				if (str[count + 1] == '\0') { // 연산자와 숫자 사이 띄어쓰기 시 다시 받아옴
					cin >> str;
					count = -1;
				}
				count++;

				while (isValid(&str[count]) != 2) { // 다음 연산자가 오기 전까지 처리
					if (str[count] == str[count + 1] && str[count + 1] == str[count + 2] && str[count + 2] == str[count + 3]) {
						result = 0;
						temp = 0;
						while (isValid(&str[count]) != 2) {
							count++;
						}
					}// 4번 반복 예외 처리 ex) IIII

					if (isValid(&str[count]) == 1 && isValid(&str[count + 1]) == 1 && isValid(&str[count + 2]) == 1 && convert(str[count]) < convert(str[count + 2])) {
						result = 0;
						temp = 0;
						while (isValid(&str[count]) != 2) {
							count++;
						}
					}// 유효한 문자, 맞지않는 형식 예외처리 ex) IIVI

					if (isValid(&str[count]) == 0) {
						result = 0;
						temp = 0;
						while (isValid(&str[count]) != 2) {
							count++;
						}
					}// 유효하지 않은 문자 예외처리 ex) VB

					if (isValid(&str[count]) == 1 && isValid(&str[count + 1]) == 1) { // 판단 문자와 뒤 문자가 모두 로마자
						pre = convert(str[count]);
						post = convert(str[count + 1]);
						if (pre < post && (pre * 5 == post || pre * 10 == post)) {
							temp -= pre;
						}
						else {
							temp += pre;
						}
						count++;
					}
					else if(isValid(&str[count]) == 1 && isValid(&str[count + 1]) == 2){ // 판단 문자는 로마자, 뒤 문자는 연산자나 \0
						temp += convert(str[count]);
						count++;
					}
					else if (isValid(&str[count]) == 1 && isValid(&str[count + 1]) == 0) { // 판단 문자는 로마자, 뒤 문자는 유효하지 않은 문자
						count++;
					}
					//cout << temp << endl; 
					//로마 숫자 변환 테스트
				}

				if (range(temp) == 0) { // 현재 계산중인 숫자가 로마숫자 범위 밖이면 0으로 처리
					temp = 0;
					result = 0;
				}

				result -= temp;

				if (range(result) == 0) { // 현재까지 계산한 숫자가 로마숫자 범위 밖이면 0으로 처리
					result = 0;
				}
			}
			else if (str[count] == '*') {
				if (str[count + 1] == '\0') { // 연산자와 숫자 사이 띄어쓰기 시 다시 받아옴
					cin >> str;
					count = -1;
				}
				count++;

				while (isValid(&str[count]) != 2) { // 다음 연산자가 오기 전까지 처리
					if (str[count] == str[count + 1] && str[count + 1] == str[count + 2] && str[count + 2] == str[count + 3]) {
						result = 0;
						temp = 0;
						while (isValid(&str[count]) != 2) {
							count++;
						}
					}// 4번 반복 예외 처리 ex) IIII

					if (isValid(&str[count]) == 1 && isValid(&str[count + 1]) == 1 && isValid(&str[count + 2]) == 1 && convert(str[count]) < convert(str[count + 2])) {
						result = 0;
						temp = 0;
						while (isValid(&str[count]) != 2) {
							count++;
						}
					}// 유효한 문자, 맞지않는 형식 예외처리 ex) IIVI

					if (isValid(&str[count]) == 0) {
						result = 0;
						temp = 0;
						while (isValid(&str[count]) != 2) {
							count++;
						}
					}// 유효하지 않은 문자 예외처리 ex) VBI

					if (isValid(&str[count+1]) == 1 && isValid(&str[count + 1]) == 1) { // 판단 문자와 뒤 문자가 모두 로마자
						pre = convert(str[count]);
						post = convert(str[count + 1]);
						if (pre < post && (pre * 5 == post || pre * 10 == post)) { 
							temp -= pre;
						}
						else {
							temp += pre;
						}
						count++;
					}
					else if(isValid(&str[count]) == 1 && isValid(&str[count + 1]) == 2){ // 판단 문자는 로마자, 뒤 문자는 연산자나 \0
						temp += convert(str[count]);
						count++;
					}
					else if (isValid(&str[count]) == 1 && isValid(&str[count + 1]) == 0) { // 판단 문자는 로마자, 뒤 문자는 유효하지 않은 문자
						count++;
					}

					//cout << temp << endl; 
					//로마 숫자 변환 테스트
				}

				if (range(temp) == 0) { // 현재 계산중인 숫자가 로마숫자 범위 밖이면 0으로 처리
					temp = 0;
					result = 0;
				}

				result *= temp;

				if (range(result) == 0) { // 현재까지 계산한 숫자가 로마숫자 범위 밖이면 0으로 처리
					result = 0;
				}
			}
			else if (str[count] == '/') {
				if (str[count + 1] == '\0') { // 연산자와 숫자 사이 띄어쓰기 시 다시 받아옴
					cin >> str;
					count = -1;
				}
				count++;

				while (isValid(&str[count]) != 2) { // 다음 연산자가 오기 전까지 처리
					if (str[count] == str[count + 1] && str[count + 1] == str[count + 2] && str[count + 2] == str[count + 3]) {
						result = 0;
						temp = 0;
						while (isValid(&str[count]) != 2) {
							count++;
						}
					}// 4번 반복 예외 처리 ex) IIII

					if (isValid(&str[count]) == 1 && isValid(&str[count + 1]) != 2 && isValid(&str[count + 2]) == 1 && convert(str[count]) < convert(str[count + 2])) {
						result = 0;
						temp = 0;
						while (isValid(&str[count]) != 2) {
							count++;
						}
					}// 유효한 문자, 맞지않는 형식 예외처리 ex) IIVI

					if (isValid(&str[count]) == 0) {
						result = 0;
						temp = 0;
						while (isValid(&str[count]) != 2) {
							count++;
						}
					}// 유효하지 않은 문자 예외처리 ex) VBI

					if (isValid(&str[count+1]) == 1 && isValid(&str[count + 1]) == 1) { // 판단 문자와 뒤 문자가 모두 로마자
						pre = convert(str[count]);
						post = convert(str[count + 1]);
						if (pre < post && (pre * 5 == post || pre * 10 == post)) {
							temp -= pre;
						}
						else {
							temp += pre;
						}
						count++;
					}
					else if(isValid(&str[count]) == 1 && isValid(&str[count + 1]) == 2){ // 판단 문자는 로마자, 뒤 문자는 연산자나 \0
						temp += convert(str[count]);
						count++;
					}
					else if (isValid(&str[count]) == 1 && isValid(&str[count + 1]) == 0) { // 판단 문자는 로마자, 뒤 문자는 유효하지 않은 문자
						count++;
					}

					//cout << temp << endl; 
					//로마 숫자 변환 테스트
				}

				if (range(temp) == 0) { // 현재 계산중인 숫자가 로마숫자 범위 밖이면 0으로 처리
					temp = 0;
					result = 0;
				}

				if (temp == 0) {
					result = 0;
				}
				else {
					result /= temp;
				}
				if (range(result) == 0) { // 현재까지 계산한 숫자가 로마숫자 범위 밖이면 0으로 처리
					result = 0;
				}
			}
			else if (str[count] == '=') {
				if (str[count + 1] == '\0') {
					cin >> str;
					count = 0;
					for (int j = 0; str[count] != '\0'; j++, count++) {
						awnserC[j] = str[count];
						awnserC[j + 1] = '\0';
					}
				}
				else {
					count++;
					for (int j = 0; str[count] != '\0'; j++, count++) {
						awnserC[j] = str[count];
						awnserC[j + 1] = '\0';
					}
				}

				// cout << result << endl;
				// 프로그램 계산값이 예상과 같은 지 확인

				convertC(result, resultC);


				if (!strcmp(resultC, awnserC)) { //Compare two strings,  Output(두 문자열 비교, 결과 출력)
					printf("%d-(%s, %s) PASS\n", i + 1, resultC, awnserC);
				}
				else {
					printf("%d-(%s, %s) FAIL\n", i + 1, resultC, awnserC);
				}
				escape = -1;
			}else {
				result = 0;
				temp = 0;

				while (isValid(&str[count]) != 2) {
					count++;
				}
				
			}

		}
	}

	return 0;
}

