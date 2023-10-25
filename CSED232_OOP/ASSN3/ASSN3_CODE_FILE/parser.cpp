#include"parser.h"
#include<fstream>

std::vector<int> parser::load_image(const char* img) {
	std::vector<int> code;
	std::ifstream reading;
	std::string temp;
	std::string tmp;
	std::string ini;
	reading.open(img); // ���� ����
	if (reading.is_open()) { // ������ �����ִٸ�
		while (!reading.eof()) // ���� ���� ������ ������
		{
			std::getline(reading, temp); // ������ �а� temp�� �����Ѵ�.
		}
	}
	int len = temp.length(); // �� ���ڿ� ����
	for (int i = 0; i < len; i++) {
		if (temp[i] == '|') { // �ȼ� ���� �������� �� �ʿ��ߴ� '|'���� ���� ����
			code.push_back(stoi(tmp)); // tmp�� string�̹Ƿ� int������ ��ȯ
			tmp = ini;
		}
		else {
			tmp += temp[i];
		}
	}
	code.push_back(stoi(tmp)); // ������ �ȼ� ����
	if (reading.is_open()) {
		reading.close(); // ���� �ݱ�
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
	if (reading.is_open()) { // ���� ����
			std::getline(reading, temp);
	}
	int len = temp.length();
	for (int i = 0; i < len; i++) {
		if (temp[i] == '|') {
			flag++;
			continue;
		}
		if (flag == 0) { // ���� '|'�� �ѹ��� ������ ���� => style�� ������ ���� 
			info1 += temp[i];
		}
		if (flag == 1) { // '|'�� ������ �ι�° '|'�� ������ ���� => drawer style(d)�� ������ ����
			info2 += temp[i];
		}
		if (flag == 2) { // x ���� for scale
			info3 += temp[i];
		}
		if (flag == 3) { // y ���� for scale
			info4 += temp[i];
		}
	}
	code.push_back(info1);
	code.push_back(info2);
	code.push_back(info3);
	code.push_back(info4);
	if (reading.is_open()) {
		reading.close(); // ���� �ݱ�
	}
	return code;
}

void parser::write_result(const char* path, const std::string& contents) {
	std::ofstream myfile;
	myfile.open(path); // output ���� ����
	myfile << contents; // ���Ͽ� �׸� �ֱ�
	myfile.close(); // ���� �ݱ�
}