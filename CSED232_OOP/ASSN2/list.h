#ifndef LIST_H_
#define LIST_H_
#include <string>
#include "node.h"
class list {
private: 
	int count;
	int dept_cnt;
	std::string dept[9];
	int dept_num[9] = {}; // �а� �ο����� �����ϱ� ���� �迭.
public:
	node* head;
	node* tail;
	bool inval = false; // ����ó����. ������ ��� true;
	void sort(); // ����Ʈ ������ ���� �Լ�
	void save_node(student stu);

	void delete_node(student stu);

	void print_list(); // ����Ʈ ��¿� �Լ�

	void pivot(int,int); // �ǹ��� �Լ�
};
#endif