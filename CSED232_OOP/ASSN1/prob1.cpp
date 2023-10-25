#include <iostream>
int main()
{
	using namespace std;
	int num; // 변환해야 할 진수 int type
	int deci; // 변환 할 10진수 int type
	char chnum[33] = {}; // 변환된 수를 출력하기 위한 문자열(change num)
	int dgt = 0; // 변환된 진수의 자릿수를 구하기 위한 변수 선언 및 초기화
	cin >> deci >> num; // 10진수와 변환해야 할 진수를 입력한다.
	switch (num) { // num의 값(2, 8, 16)에 따른 case 실행
	case 2:
	{
		int decigt = deci; // 자릿수 계산을 위해 num으로 deci를 나누어야 하기 때문에, 10진수를 임의의 변수를 선언한 후 10진수값으로 초기화를 함.
		while (decigt > 0) { // 자릿수 계산
			decigt = decigt / 2;
			dgt++;
		}
		dgt--; // 배열의 첫 번째 칸은 [0]이므로 유의미한 사용을 위해 1을 빼줌.
		if (deci == 0) { // 입력한 10진수가 0일 경우 while문이 작동되지 않아 dgt = 0으로 남고, 윗 구문 dgt--에 의해 dgt = -1이 되버리므로 다른 한자리 수와 같이 dgt를 재설정해주어야 한다.
			dgt = 0;
		}
		for (int i = dgt; i >= 0; i--) { // 자릿수만큼 문자열의 뒤에서부터 계산값을 채움. 진수 변환과정에서 10진수를 변환할 진수로 나눠주었을 때 나머지 값은 일의 자리수부터 순서대로 계산되기 때문에 뒤에서부터 채운다.
			if (deci % 2 == 0) {
				chnum[i] = 48; // 2로 나누어 떨어진다면 해당 자리는 0 --> ASCII 코드에서 '0' = 48
			}
			else {
				chnum[i] = 49; // 2로 나누어 떨어지지 않는다면 해당 자리는 1 --> ASCII 코드에서 '1' = 49
			}
			deci = deci / 2; // 다음 자리에 들어갈 숫자 계산을 위해 2로 나눠줌
		}
		for (int i = 0; i <= dgt; i++) {
			cout << chnum[i]; // 변환한 진수 출력
		}
		break;
	}
	case 8:
	{
		int decigt = deci; // case 2와 마찬가지로 자릿수 계산
		while (decigt > 0) {
			decigt = decigt / 8; // 8진수이기 때문에 8로 나눠줌
			dgt++;
		}
		dgt--;
		if (deci == 0) { // 입력한 10진수가 0일 경우 while문이 작동되지 않아 dgt = 0으로 남고, 윗 구문 dgt--에 의해 dgt = -1이 되버리므로 다른 한자리 수와 같이 dgt를 재설정해주어야 한다.
			dgt = 0;
		}
		for (int i = dgt; i >= 0; i--) {
			if (deci % 8 == 0) {
				chnum[i] = '0'; // 8로 나누어 떨어지면 해당 자리는 0
			}
			else {
				int k; // 임의의 변수 k 선언
				k = deci % 8; // k를 deci(입력받은 10진수)를 8로 나눈 나머지로 초기화.
				chnum[i] += 48 + k; // ASCII 코드 상에서 48 = '0'을 의미. 차례대로 49 = '1', 50 = '2'...이기때문에 k를 더해줌으로써 문자열에 해당 자리에 대한 값을 저장.
			}
			deci = deci / 8; // 다음 자리에 들어갈 숫자 계산을 위해 8로 나누어줌.
		}
		for (int i = 0; i <= dgt; i++) {
			cout << chnum[i]; // 변환한 수 출력
		}
		break;
	}
	case 16:
	{
		int decigt = deci; // 마찬가지로 자리수 계산
		while (decigt > 0) {
			decigt = decigt / 16; // 16진수이기 때문에 16으로 나눠줌
			dgt++;
		}
		dgt--;
		if (deci == 0) { // 입력한 10진수가 0일 경우 while문이 작동되지 않아 dgt = 0으로 남고, 윗 구문 dgt--에 의해 dgt = -1이 되버리므로 다른 한자리 수와 같이 dgt를 재설정해주어야 한다.
			dgt = 0;
		}
		for (int i = dgt; i >= 0; i--) {
			if (deci % 16 == 0){ // 16으로 나누어떨어지면 해당 자리에 들어갈 숫자는 0
				chnum[i] = '0';
			}
			else if(deci % 16 >=10){ // 16진수는 나머지가 10이 넘어가면 A,B,C...인 문자로 나머지 숫자들을 표현하기 때문에 별도의 과정이 필요하다.
				int k;
				k = deci % 16; // 임의의 변수 k를 선언하고, 16으로 나눈 나머지 값으로 초기화한다.
				chnum[i] += 55 + k; // 10을 의미하는 문자인 A는 ASCII코드 상 65를 의미하기 때문에, 나머지 값인 10을 더했을 때 65가 나와야 하므로 55에 k를 더하는 형식으로 표현했다. B의 경우 66이므로 55+11=66이 나와서 B가 저장된다.
			}
			else {
				int k;
				k = deci % 16; 
				chnum[i] += 48 + k; // 16으로 나눈 나머지가 10을 넘지 않는다면 0을 의미하는 ASCII 코드값 48에서 더해줌으로써 배열에 값을 저장한다.
			}
			deci = deci / 16; // 다음 자리에 들어갈 숫자를 계산하기 위해 16으로 나누어줌.
		}
		for (int i = 0; i <= dgt; i++) {
			cout << chnum[i]; // 출력
		}
		break;
	}
	}

	return 0;
}
