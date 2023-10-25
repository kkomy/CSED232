#include<iostream>
#include<string>
#include<cmath>
int main() {
	using namespace std;
	char oprt[2];
	string r1, r2;
	double deci1 = 0;
	double deci2 = 0;
	cin >> oprt >> r1 >> r2;

	if (r1[0] == '0') { // 입력가능한 숫자의 종류 제한 (2, 8, 16진수만 입력가능)
		if (r1[1] == 'b') { // 2진수 -> 10진수 변환
			int dgt = r1.length(); // 입력받은 숫자의 길이 측정 => 자릿수 계산에 이용
			for (int i = 2; i < dgt; i++) {
				int k = r1[i] - 48; // r1[i]는 char형이기 때문에, 숫자가 ASCII 코드값을 지님. 따라서 ASCII코드 상에서 숫자가 시작되는 0에 해당하는 값을 빼주어야 우리가 원하는 값을 얻을 수 있다.
				deci1 += k * pow(2, dgt - 1 - i); 
			}
		}
		else if (r1[1] == 'X') {
			int dgt = r1.length();
			for (int i = 2; i < dgt; i++) {
				int k;
				if (r1[i] >= 65) { // 16진수의 A,B,C에 대한 처리
					k = r1[i] - 55;
				}
				else k = r1[i] - 48;
				deci1 += k * pow(16, dgt - 1 - i);
			}
		}
		else {
			int dgt = r1.length();
			for (int i = 1; i < dgt; i++) {
				int k = r1[i] - 48;
				deci1 += k * pow(8, dgt - 1 - i);
			}

		}
	}

	if (r2[0] == '0') { // 입력가능한 숫자의 종류 제한 (2, 8, 16진수만 입력가능)
		if (r2[1] == 'b') { // 2진수 -> 10진수 변환
			int dgt = r2.length(); // 입력받은 숫자의 길이 측정 => 자릿수 계산에 이용
			for (int i = 2; i < dgt; i++) {
				int k = r2[i] - 48; // r1[i]는 char형이기 때문에, 숫자가 ASCII 코드값을 지님. 따라서 ASCII코드 상에서 숫자가 시작되는 0에 해당하는 값을 빼주어야 우리가 원하는 값을 얻을 수 있다.
				deci2 += k * pow(2, dgt - 1 - i);
			}
		}
		else if (r2[1] == 'X') {
			int dgt = r2.length();
			for (int i = 2; i < dgt; i++) {
				int k;
				if (r2[i] >= 65) { // 16진수의 A,B,C에 대한 처리
					k = r2[i] - 55;
				}
				else k = r2[i] - 48;
				deci2 += k * pow(16, dgt - 1 - i);
			}
		}
		else {
			int dgt = r2.length();
			for (int i = 1; i < dgt; i++) {
				int k = r2[i] - 48;
				deci2 += k * pow(8, dgt - 1 - i);
			}

		}
	}

	if (oprt[0] == '+') { // + 연산자, 덧셈
		float result = deci1 + deci2;
		cout << fixed; // 소수점을 고정시켜 그 아래의 자릿수에 대해서만 다룸
		cout.precision(result == (int)result ? 0 : 3); // result(r1 + r2)가 정수로 떨어진다면, int로 표현한 값과 같을 것이다. 따라서 정수로 떨어진다면 소수점 아래 자릿수는 0개, 그것이 아니라면 3개로 표현한다.
		cout << result;
	}
	else if (oprt[0] == '-') { // - 연산자, 뺄셈
		float result = deci1 - deci2;
		cout << fixed;
		cout.precision(result == (int)result ? 0 : 3);
		cout << result;
	}
	else if (oprt[0] == '*') { // * 연산자, 곱셈
		float result = deci1 * deci2;
		cout << fixed;
		cout.precision(result == (int)result ? 0 : 3);
		cout << result;
	}
	else if (oprt[0] == '/') { // / 연산자, 나눗셈
		float result = deci1 / deci2;
		cout << fixed;
		cout.precision(result == (int)result ? 0 : 3);
		cout << result;
	}
	return 0;
}