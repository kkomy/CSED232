#include"parser.h"
#include<fstream>

std::vector<int> parser::load_image(const char* img) {
	std::vector<int> code;
	std::ifstream reading;
	std::string temp;
	std::string tmp;
	std::string ini;
	reading.open(img); // 파일 오픈
	if (reading.is_open()) { // 파일이 열려있다면
		while (!reading.eof()) // 파일 끝에 도달할 때까지
		{
			std::getline(reading, temp); // 파일을 읽고 temp에 저장한다.
		}
	}
	int len = temp.length(); // 총 문자열 길이
	for (int i = 0; i < len; i++) {
		if (temp[i] == '|') { // 픽셀 값을 구분지을 때 필요했던 '|'문자 삭제 과정
			code.push_back(stoi(tmp)); // tmp는 string이므로 int형으로 변환
			tmp = ini;
		}
		else {
			tmp += temp[i];
		}
	}
	code.push_back(stoi(tmp)); // 마지막 픽셀 삽입
	if (reading.is_open()) {
		reading.close(); // 파일 닫기
	}
	return code;
}

std::vector<std::string> parser::load_config(const char* con) {
	std::vector<std::string> code;
	std::ifstream reading;
	std::string temp;
	std::string info1;
	std::string info2;
	std::string info3;
	std::string info4;
	int flag = 0;
	reading.open(con);
	if (reading.is_open()) { // 파일 오픈
			std::getline(reading, temp);
	}
	int len = temp.length();
	for (int i = 0; i < len; i++) {
		if (temp[i] == '|') {
			flag++;
			continue;
		}
		if (flag == 0) { // 아직 '|'를 한번도 만나지 못함 => style을 저장할 차례 
			info1 += temp[i];
		}
		if (flag == 1) { // '|'를 만나고 두번째 '|'를 만나지 못함 => drawer style(d)을 저장할 차례
			info2 += temp[i];
		}
		if (flag == 2) { // x 비율 for scale
			info3 += temp[i];
		}
		if (flag == 3) { // y 비율 for scale
			info4 += temp[i];
		}
	}
	code.push_back(info1);
	code.push_back(info2);
	code.push_back(info3);
	code.push_back(info4);
	if (reading.is_open()) {
		reading.close(); // 파일 닫기
	}
	return code;
}

void parser::write_result(const char* path, const std::string& contents) {
	std::ofstream myfile;
	myfile.open(path); // output 파일 열기
	myfile << contents; // 파일에 그림 넣기
	myfile.close(); // 파일 닫기
}