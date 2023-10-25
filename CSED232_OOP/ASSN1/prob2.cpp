#include<iostream>
#include<cmath> // sqrt를 사용하기 위한 헤더파일
#include<cstring> // strcmp를 사용하기 위한 헤더파일
int main() {
	using namespace std;
	char oprt[10]; // 연산자를 입력받는 char형 array
	float r1, r2; // 두 개의 수
	cin >> oprt; // 연산자를 입력받는다.
	if (oprt[1] == '\0') { // 만약 연산자가 한글자라면(+,-,*,/) -> oprt[0]에 연산자가 들어가고, 해당 문자열을 끝마치게 되므로 다음 칸인 oprt[1]에 NULL이 들어갈 것이다.
		cin >> r1 >> r2; // (+,-,*,/)들은 2개의 숫자를 입력받아야 한다.
		if (oprt[0] == '+') { // + 연산자, 덧셈
			float result = r1 + r2; 
			cout << fixed; // 소수점을 고정시켜 그 아래의 자릿수에 대해서만 다룸
			cout.precision(result == (int)result ? 0 : 3); // result(r1 + r2)가 정수로 떨어진다면, int로 표현한 값과 같을 것이다. 따라서 정수로 떨어진다면 소수점 아래 자릿수는 0개, 그것이 아니라면 3개로 표현한다.
			cout << result;
		}
		else if (oprt[0] == '-') { // - 연산자, 뺄셈
			float result = r1 - r2;
			cout << fixed; 
			cout.precision(result == (int)result ? 0 : 3); 
			cout << result;
		}
		else if (oprt[0] == '*') { // * 연산자, 곱셈
			float result = r1 * r2;
			cout << fixed;
			cout.precision(result == (int)result ? 0 : 3);
			cout << result;
		}
		else if (oprt[0] == '/') { // / 연산자, 나눗셈
			float result = r1 / r2;
			cout << fixed;
			cout.precision(result == (int)result ? 0 : 3);
			cout << result;
		}
	}
	else { // 입력받은 연산자가 한글자가 아니라면, sqrt 또는 square이다. 
		cin >> r1; // sqrt와 square은 1개의 숫자만을 필요로 한다.
		if(!strcmp(oprt,"sqrt")){ // 제곱근 연산자, oprt와 문자열 "sqrt"가 일치한다면 strcmp에서는 0을 반환한다. if는 1이어야 실행되므로 논리 부정 연산자 !를 붙여준다.
			float result = sqrt(r1); // cmath 헤더파일을 통해 제곱근을 계산한다.
			cout << fixed;
			cout.precision(result == (int)result ? 0 : 3); // 만약 제곱근의 결과값(result)가 정수로 떨어진다면 소수점 아래 수가 없으므로 result의 정수형(int)와 값이 일치할 것이다. 그렇게 되면 소수점 아래 자리를 0개로, 그것이 아니라면 3개로 표현한다.
			cout << result;
		}
		else if (!strcmp(oprt, "square")) { // 제곱 연산자
			float result = r1 * r1;
			cout << fixed;
			cout.precision(result == (int)result ? 0 : 3);
			cout << result;
		}
	} 

	return 0;
}
