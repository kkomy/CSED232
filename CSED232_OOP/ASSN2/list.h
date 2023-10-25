#ifndef LIST_H_
#define LIST_H_
#include <string>
#include "node.h"
class list {
private: 
	int count;
	int dept_cnt;
	std::string dept[9];
	int dept_num[9] = {}; // 학과 인원수를 저장하기 위한 배열.
public:
	node* head;
	node* tail;
	bool inval = false; // 예외처리용. 예외인 경우 true;
	void sort(); // 리스트 정렬을 위한 함수
	void save_node(student stu);

	void delete_node(student stu);

	void print_list(); // 리스트 출력용 함수

	void pivot(int,int); // 피벗용 함수
};
#endif