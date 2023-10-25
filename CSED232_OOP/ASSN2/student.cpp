#include<iostream>
#include<string>
#include"student.h"

void student::input_info() { // 학생 정보 입력
	std::cin.ignore(); // getline 사용 시 버퍼를 비워주기 위해 ignore() 이용
	std::cout << "Dept: ";
	getline(std::cin, dept);

	std::cout << "Gender: ";
	getline(std::cin, gender);

	std::cout << "Name: ";
	getline(std::cin, name);


	std::cout << "Age: ";
	std::cin >> age;
	std::cin.clear(); // 나이에 문자 입력 시 오류 발생을 막기 위해 버퍼 비우려고 도입
	std::cin.ignore(1000, '\n');
}

int student::blank_check(){ // 공백확인용 함수, Dept, Gender, name을 검사함
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

std::string student::show_dept() { // dept 값을 받아오기 위한 함수
	return dept;
}

std::string student::show_gender() { // gender 값을 받아오기 위한 함수
	return gender;
}

std::string student::show_name() { // name 값을 받아오기 위한 함수
	return name;
}

int student::show_age() {// age 값을 받아오기 위한 함수
	return age;
}