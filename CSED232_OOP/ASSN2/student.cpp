#include<iostream>
#include<string>
#include"student.h"

void student::input_info() { // �л� ���� �Է�
	std::cin.ignore(); // getline ��� �� ���۸� ����ֱ� ���� ignore() �̿�
	std::cout << "Dept: ";
	getline(std::cin, dept);

	std::cout << "Gender: ";
	getline(std::cin, gender);

	std::cout << "Name: ";
	getline(std::cin, name);


	std::cout << "Age: ";
	std::cin >> age;
	std::cin.clear(); // ���̿� ���� �Է� �� ���� �߻��� ���� ���� ���� ������ ����
	std::cin.ignore(1000, '\n');
}

int student::blank_check(){ // ����Ȯ�ο� �Լ�, Dept, Gender, name�� �˻���
	if (dept.find(' ') != -1) {
		return 0;
	}
	else if (gender.find(' ') != -1) {
		return 0;
	}
	else if (name.find(' ') != -1) {
		return 0;
	}
		return 1;
}

std::string student::show_dept() { // dept ���� �޾ƿ��� ���� �Լ�
	return dept;
}

std::string student::show_gender() { // gender ���� �޾ƿ��� ���� �Լ�
	return gender;
}

std::string student::show_name() { // name ���� �޾ƿ��� ���� �Լ�
	return name;
}

int student::show_age() {// age ���� �޾ƿ��� ���� �Լ�
	return age;
}