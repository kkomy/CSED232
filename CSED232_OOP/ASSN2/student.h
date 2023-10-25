#ifndef STUDENT_H_
#define STUDENT_H_
#include <string>

class student {
private:
	std::string dept, name, gender; 
	int age = 0;
public:
	void input_info();
	std::string show_dept(); // show_함수들은 모두 private 함수의 값을 받아오기 위한 함수이다.
	std::string show_name();
	std::string show_gender();
	int show_age();
	int blank_check(); // 공백확인용 함수
};
#endif