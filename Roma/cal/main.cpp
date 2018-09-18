#include <iostream>
#include <cstring>
#include <string>
using namespace std;

/**
*@brief Roman numeral calculator (�θ� ���� ����)
*@author Minsu Kim (��μ�)
*@since 2017.09.13
*/

int convert(char letter) { //Convert from roman to numeric (�θ��ڿ��� ���ڷ� ��ȯ) 
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

int isValid(char *str) { //Determine it it is a valid symbol (��ȿ�� ��ȣ���� �Ǵ�)
	if (*str == 'I' || *str == 'V' || *str == 'X' || *str == 'L' || *str == 'C' || *str == 'D' || *str == 'M' || *str == 'Z') { 
		return 1; //Returns 1 if it is a Roman numeral (�θ����� ��� 1�� ��ȯ)
	}
	if (*str == '+' || *str == '-' || *str == '*' || *str == '/' || *str == '\0') { 
		return 2;//Returns 2 if it is a space or arithmetic operator (����� ����������� ��� 2�� ��ȯ)
	}
	return 0;// Returns 0 if it is a invalid symbol(��ȿ�� ��ȣ�� �ƴ� �� 0�� ��ȯ)
}

void convertC(int result, char* resultC) { // Contvert from numeric to Roman (���ڸ� �θ��ڷ� ��ȯ)
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


int range(int n) { // Determine if it is a valid range (��ȿ�� ���� ���� �������� �Ǵ�)
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
	*@param num Number of expressions to be received (�ްԵ� �ĵ��� ��)
	*@param count Counter of string (���ڿ��� ���)
	*@param result Program result (������ ���� ���α׷��� ����� ��)
	*@param pre Value of the preceding character in the string when comparing Roman letters (�θ��� �񱳽� ���ڿ����� ���� ������ ��)
	*@param post Value of the following character in the string when comparing Roman letters (�θ��� �񱳽� ���ڿ����� ���� ������ ��)
	*@param temp Temporary variable (�ӽ� �뵵 ����)
	*@param escape Loop escape variable (�ݺ��� Ż�� �뵵�� ����)
	*@param resultC Sinrg of the left hand value (������ ���� ��ȯ�� ���ڿ�)
	*@param awnswerC String of the right hand value (������ ���� ��ȯ�� ���ڿ�)
	*@param str String to be used(����� ���ڿ�)
	*/

	cin >> num; // Number of test cases (ù��° �Է°�, �׽�Ʈ ���̽��� ����)

	for (int i = 0; i < num; i++) {
		cin >> str; 

		//cout << str << endl;
		// ���ڿ��� ����� ���Դ��� Ȯ�ο� �ڵ�


		count = 0;
		result = 0;
		escape = 0;

		while (isValid(&str[count]) != 2) { // ���� �����ڰ� ���� ������ ó��

			if (str[count] == str[count + 1] && str[count + 1] == str[count + 2] && str[count + 2] == str[count + 3]) {
				result = 0;
				while (isValid(&str[count]) != 2) {
					count++;
				}
			}// 4�� �ݺ� ���� ó�� ex) IIII

			if (isValid(&str[count])==1 && isValid(&str[count+1]) == 1 && isValid(&str[count + 2]) == 1 && convert(str[count]) < convert(str[count+2])) {
				result = 0;
				while (isValid(&str[count]) != 2) {
					count++;
				}
			}// ��ȿ�� ����, �����ʴ� ���� ����ó�� ex) IIVI

			if (isValid(&str[count]) == 0) {
				result = 0;
				while (isValid(&str[count]) != 2) {
					count++;
				}
			}// ��ȿ���� ���� ���� ����ó�� ex) VB



			if (isValid(&str[count]) == 1 && isValid(&str[count + 1]) == 1) { // �Ǵ� ���ڿ� �� ���ڰ� ��� �θ���
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
			else if(isValid(&str[count]) == 1 && isValid(&str[count+1]) == 2){ // �Ǵ� ���ڴ� �θ���, �� ���ڴ� �����ڳ� \0
				result += convert(str[count]);
				count++;
			}
			else if (isValid(&str[count]) == 1 && isValid(&str[count + 1]) == 0) { // �Ǵ� ���ڴ� �θ���, �� ���ڴ� ��ȿ���� ���� ����
				count++;
			}

			//cout << result << endl; 
			//�θ� ���� ��ȯ �׽�Ʈ
		}

		if (range(result) == 0) { // ������� ����� ���ڰ� �θ����� ���� ���̸� 0���� ó��
			result = 0;
		}

		while (escape != -1) {
			temp = 0;

			if (str[count] == '\0') { // ���ڿ� ������ ���� ���� �� �ٽ� �޾ƿ�
				cin >> str;
				count = 0;
			}

			if (str[count] == '+') {
				if (str[count + 1] == '\0') { // �����ڿ� ���� ���� ���� �� �ٽ� �޾ƿ�
					cin >> str;
					count = -1;
				}
				count++;

				while (isValid(&str[count]) != 2) { // ���� �����ڰ� ���� ������ ó��
					if (str[count] == str[count+1] && str[count+1] == str[count+2] && str[count+2] == str[count+3]) {
						result = 0;
						temp = 0;
						while (isValid(&str[count]) != 2) {
							count++;
						}
					}// 4�� �ݺ� ���� ó�� ex) IIII

					if (isValid(&str[count]) == 1 && isValid(&str[count + 1]) == 1 && isValid(&str[count + 2]) == 1 && convert(str[count]) < convert(str[count + 2])) {
						result = 0;
						temp = 0;
						while (isValid(&str[count]) != 2) {
							count++;
						}
					}// ��ȿ�� ����, �����ʴ� ���� ����ó�� ex) IIVI

					if (isValid(&str[count]) == 0) {
						result = 0;
						temp = 0;
						while (isValid(&str[count]) != 2) {
							count++;
						}
					}// ��ȿ���� ���� ���� ����ó�� ex) VB

					if (isValid(&str[count]) == 1 && isValid(&str[count + 1]) == 1) { // �Ǵ� ���ڿ� �� ���ڰ� ��� �θ���
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
					else if(isValid(&str[count]) == 1 && isValid(&str[count+1]) == 2){ // �Ǵ� ���ڴ� �θ���, �� ���ڴ� �����ڳ� \0
						temp += convert(str[count]);
						count++;
					}
					else if (isValid(&str[count]) == 1 && isValid(&str[count + 1]) == 0) { // �Ǵ� ���ڴ� �θ���, �� ���ڴ� ��ȿ���� ���� ����
						count++;
					}

					//cout << temp << endl; 
					//�θ� ���� ��ȯ �׽�Ʈ
				}

				if (range(temp) == 0) { // ���� ������� ���ڰ� �θ����� ���� ���̸� 0���� ó��
					temp = 0;
					result = 0;
				}

				result += temp;

				if (range(result) == 0) { // ������� ����� ���ڰ� �θ����� ���� ���̸� 0���� ó��
					result = 0;
				}


			}
			else if (str[count] == '-') {
				if (str[count + 1] == '\0') { // �����ڿ� ���� ���� ���� �� �ٽ� �޾ƿ�
					cin >> str;
					count = -1;
				}
				count++;

				while (isValid(&str[count]) != 2) { // ���� �����ڰ� ���� ������ ó��
					if (str[count] == str[count + 1] && str[count + 1] == str[count + 2] && str[count + 2] == str[count + 3]) {
						result = 0;
						temp = 0;
						while (isValid(&str[count]) != 2) {
							count++;
						}
					}// 4�� �ݺ� ���� ó�� ex) IIII

					if (isValid(&str[count]) == 1 && isValid(&str[count + 1]) == 1 && isValid(&str[count + 2]) == 1 && convert(str[count]) < convert(str[count + 2])) {
						result = 0;
						temp = 0;
						while (isValid(&str[count]) != 2) {
							count++;
						}
					}// ��ȿ�� ����, �����ʴ� ���� ����ó�� ex) IIVI

					if (isValid(&str[count]) == 0) {
						result = 0;
						temp = 0;
						while (isValid(&str[count]) != 2) {
							count++;
						}
					}// ��ȿ���� ���� ���� ����ó�� ex) VB

					if (isValid(&str[count]) == 1 && isValid(&str[count + 1]) == 1) { // �Ǵ� ���ڿ� �� ���ڰ� ��� �θ���
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
					else if(isValid(&str[count]) == 1 && isValid(&str[count + 1]) == 2){ // �Ǵ� ���ڴ� �θ���, �� ���ڴ� �����ڳ� \0
						temp += convert(str[count]);
						count++;
					}
					else if (isValid(&str[count]) == 1 && isValid(&str[count + 1]) == 0) { // �Ǵ� ���ڴ� �θ���, �� ���ڴ� ��ȿ���� ���� ����
						count++;
					}
					//cout << temp << endl; 
					//�θ� ���� ��ȯ �׽�Ʈ
				}

				if (range(temp) == 0) { // ���� ������� ���ڰ� �θ����� ���� ���̸� 0���� ó��
					temp = 0;
					result = 0;
				}

				result -= temp;

				if (range(result) == 0) { // ������� ����� ���ڰ� �θ����� ���� ���̸� 0���� ó��
					result = 0;
				}
			}
			else if (str[count] == '*') {
				if (str[count + 1] == '\0') { // �����ڿ� ���� ���� ���� �� �ٽ� �޾ƿ�
					cin >> str;
					count = -1;
				}
				count++;

				while (isValid(&str[count]) != 2) { // ���� �����ڰ� ���� ������ ó��
					if (str[count] == str[count + 1] && str[count + 1] == str[count + 2] && str[count + 2] == str[count + 3]) {
						result = 0;
						temp = 0;
						while (isValid(&str[count]) != 2) {
							count++;
						}
					}// 4�� �ݺ� ���� ó�� ex) IIII

					if (isValid(&str[count]) == 1 && isValid(&str[count + 1]) == 1 && isValid(&str[count + 2]) == 1 && convert(str[count]) < convert(str[count + 2])) {
						result = 0;
						temp = 0;
						while (isValid(&str[count]) != 2) {
							count++;
						}
					}// ��ȿ�� ����, �����ʴ� ���� ����ó�� ex) IIVI

					if (isValid(&str[count]) == 0) {
						result = 0;
						temp = 0;
						while (isValid(&str[count]) != 2) {
							count++;
						}
					}// ��ȿ���� ���� ���� ����ó�� ex) VBI

					if (isValid(&str[count+1]) == 1 && isValid(&str[count + 1]) == 1) { // �Ǵ� ���ڿ� �� ���ڰ� ��� �θ���
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
					else if(isValid(&str[count]) == 1 && isValid(&str[count + 1]) == 2){ // �Ǵ� ���ڴ� �θ���, �� ���ڴ� �����ڳ� \0
						temp += convert(str[count]);
						count++;
					}
					else if (isValid(&str[count]) == 1 && isValid(&str[count + 1]) == 0) { // �Ǵ� ���ڴ� �θ���, �� ���ڴ� ��ȿ���� ���� ����
						count++;
					}

					//cout << temp << endl; 
					//�θ� ���� ��ȯ �׽�Ʈ
				}

				if (range(temp) == 0) { // ���� ������� ���ڰ� �θ����� ���� ���̸� 0���� ó��
					temp = 0;
					result = 0;
				}

				result *= temp;

				if (range(result) == 0) { // ������� ����� ���ڰ� �θ����� ���� ���̸� 0���� ó��
					result = 0;
				}
			}
			else if (str[count] == '/') {
				if (str[count + 1] == '\0') { // �����ڿ� ���� ���� ���� �� �ٽ� �޾ƿ�
					cin >> str;
					count = -1;
				}
				count++;

				while (isValid(&str[count]) != 2) { // ���� �����ڰ� ���� ������ ó��
					if (str[count] == str[count + 1] && str[count + 1] == str[count + 2] && str[count + 2] == str[count + 3]) {
						result = 0;
						temp = 0;
						while (isValid(&str[count]) != 2) {
							count++;
						}
					}// 4�� �ݺ� ���� ó�� ex) IIII

					if (isValid(&str[count]) == 1 && isValid(&str[count + 1]) != 2 && isValid(&str[count + 2]) == 1 && convert(str[count]) < convert(str[count + 2])) {
						result = 0;
						temp = 0;
						while (isValid(&str[count]) != 2) {
							count++;
						}
					}// ��ȿ�� ����, �����ʴ� ���� ����ó�� ex) IIVI

					if (isValid(&str[count]) == 0) {
						result = 0;
						temp = 0;
						while (isValid(&str[count]) != 2) {
							count++;
						}
					}// ��ȿ���� ���� ���� ����ó�� ex) VBI

					if (isValid(&str[count+1]) == 1 && isValid(&str[count + 1]) == 1) { // �Ǵ� ���ڿ� �� ���ڰ� ��� �θ���
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
					else if(isValid(&str[count]) == 1 && isValid(&str[count + 1]) == 2){ // �Ǵ� ���ڴ� �θ���, �� ���ڴ� �����ڳ� \0
						temp += convert(str[count]);
						count++;
					}
					else if (isValid(&str[count]) == 1 && isValid(&str[count + 1]) == 0) { // �Ǵ� ���ڴ� �θ���, �� ���ڴ� ��ȿ���� ���� ����
						count++;
					}

					//cout << temp << endl; 
					//�θ� ���� ��ȯ �׽�Ʈ
				}

				if (range(temp) == 0) { // ���� ������� ���ڰ� �θ����� ���� ���̸� 0���� ó��
					temp = 0;
					result = 0;
				}

				if (temp == 0) {
					result = 0;
				}
				else {
					result /= temp;
				}
				if (range(result) == 0) { // ������� ����� ���ڰ� �θ����� ���� ���̸� 0���� ó��
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
				// ���α׷� ��갪�� ����� ���� �� Ȯ��

				convertC(result, resultC);


				if (!strcmp(resultC, awnserC)) { //Compare two strings,  Output(�� ���ڿ� ��, ��� ���)
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

