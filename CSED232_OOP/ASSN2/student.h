#ifndef STUDENT_H_
#define STUDENT_H_
#include <string>

class student {
private:
	std::string dept, name, gender; 
	int age = 0;
public:
	void input_info();
	std::string show_dept(); // show_�Լ����� ��� private �Լ��� ���� �޾ƿ��� ���� �Լ��̴�.
	std::string show_name();
	std::string show_gender();
	int show_age();
	int blank_check(); // ����Ȯ�ο� �Լ�
};
#endif