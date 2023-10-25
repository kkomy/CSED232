#include<iostream>
#include<string>
#include<cmath>
#include "student.h"
#include "list.h"
#include "node.h"

int main() {
	using namespace std;
	int menu = 0;
	int cat, fun = 0; // 4번 pivot에서 category와 function을 선택하기 위해 받을 입력값
	list lst;
	student stu;
	while (menu != 5) {
		cout << "----------MENU----------" << endl;
		cout << "1. Add a student" << endl;
		cout << "2. Delete a student" << endl;
		cout << "3. Print the student's list" << endl;
		cout << "4. Pivot Table" << endl;
		cout << "5. Exit" << endl;
		cout << "------------------------" << endl;
		cout << "Selection: ";
		cin >> menu;
		switch (menu) {
		case 1: // 학생정보 추가
			stu.input_info(); // node data 입력받기
			lst.save_node(stu);
			/* 예외처리 */
			if (lst.inval == true) { // 예외일 경우 inval = true가 됨.
				cout << "Invalid value. Please try again." << std::endl;
				continue;
			}
			lst.sort();
			continue;
		case 2: // 학생정보 삭제
			stu.input_info();
			lst.delete_node(stu);
			if (lst.inval == true) {
				cout << "Invalid value. Please try again." << std::endl;
			}
			continue;
		case 3: // 학생정보 출력
			lst.print_list();
			continue;
		case 4: // 학생정보 피벗하여 출력
			cout << "----------Category----------" << endl;
			cout << "1. Dept" << endl;
			cout << "2. Gender" << endl;
			cout << "3. Dept and Gender" << endl;
			cout << "----------------------------" << endl;
			cout << "Selection: ";
			cin >> cat;
			if (cat < 1 || cat > 3) { // 주어진 메뉴에 없는 번호 입력 시 
				cout << "There is no '" << cat << "'. Please try again." << endl;
				continue;
			}
			cout << "----------Function----------" << endl;
			cout << "1. Average" << endl;
			cout << "2. Max" << endl;
			cout << "3. Min" << endl;
			cout << "----------------------------" << endl;
			cout << "Selection: ";
			cin >> fun;
			if (fun < 1 || fun > 3) {  // 주어진 메뉴에 없는 번호 입력 시 
				cout << "There is no '" << fun << "'. Please try again." << endl;
				continue;
			}
			lst.pivot(cat,fun); // 피벗함수 출력
			continue;
		case 5: // 프로그램 종료
			cout << "Exit!" << endl;
			return 0;
		default: // 1~5번이 아닌 다른 번호 혹은 문자 기입 시 에러처리
			cout << "ERROR" << endl;
			cin.clear();
			cin.ignore(1000,'\n');
			continue;
		}

	}

	return 0;
}
