#include<iostream>
#include<string>
#include"list.h"

void list::save_node(student stu) { // �л����� ���� �Լ�
	node* temp;
	node* new_code = new node; // ����Ʈ�� �߰��� ���. �ش� ���� �Է��� ������ �����ϰ� ����Ʈ�� ����.
	new_code->data = stu;
	new_code->next = NULL;
	std::string srt_dept = new_code->data.show_dept();
	std::string srt_name = new_code->data.show_name();
	std::string srt_gend = new_code->data.show_gender();
	int srt_age = new_code->data.show_age();
	inval = false; // ����ó���� ���� �ʱ�ȭ. true�� ��� �����޼����� ����ϵ��� �Ѵ�.

	/* ���� ����ó�� */
	if (stu.blank_check() == 0) {
		inval = true;
		return;
	}
	/* Age ���� ����ó�� */
	if (srt_age < 18 || srt_age > 30) {
		inval = true;
		return;
	}
	if (srt_age)
	/* Gender M,F ����ó�� */
	if (srt_gend != "M" && srt_gend != "F") {
		inval = true;
		return;
	}
	/* Dept �빮�� ����ó�� */
	for (int i = 0; srt_dept[i] != NULL; i++) {
		if (srt_dept[i] < 65 || srt_dept[i] > 90) {
			inval = true;
			return;
		}
	}

	if (count == 0) { // ����Ʈ�� ��尡 �ƹ��͵� ���ٸ�
		head = new_code;
		tail = new_code;
		tail->next = NULL;
		count = 1; // ��� ���� 1��
		dept_cnt = 1; // �а� ���� 1��
		dept[0] = srt_dept; // �а� ������ �����ϴ� �迭�� �Էµ�
		dept_num[0] += 1; // �а��ο��߰�
		std::cout << "A student is added in table!" << std::endl;
		return;
	}
	else { // ����Ʈ�� ��尡 �̹� �����Ѵٸ�
		/* �ߺ��˻� */
		for (temp = head; temp != NULL; temp = temp->next) {
			if (srt_dept == temp->data.show_dept()) {
				if (srt_gend == temp->data.show_gender()) {
					if (srt_name == temp->data.show_name()) {
						if (srt_age == temp->data.show_age()) {
							std::cout << "The student already exists." << std::endl; // �ߺ��� ��尡 �����Ѵٸ� �̹� ������ �˸�
							return; // ���� �Լ� ����
						}
					}
				}
			}
		}

		int check_samedept = 0; // �߰��� ����� �а��� �̹� �ִ��� ����. 0�̸� ���ο� �а���
		for (temp = head; temp != NULL; temp = temp->next) {
			for (int i = 0; i < dept_cnt; i++) {
				if (temp->data.show_dept() == srt_dept) { // ���� �а��� ���� �� �ִٸ�?
					check_samedept++; // check_samedept�� 1�߰�. ���ο� �а��� �ƴ��� �ǹ�
				}
			}
		}
		if (check_samedept == 0) { // ���ο� �а����
			if (dept_cnt == 9) { // 9���� �а��� ��� á�ٸ�
				/* �а����� ����ó�� */
				inval = true; 
				return;
			}
			else {// ���� �а��� 9���� �ȵǾ��ٸ� dept�迭 ����������
				int over = 0;
				for (int i = 0; i < dept_cnt; i++) {
					if (srt_dept.compare(dept[i]) < 0) {
						for (int j = dept_cnt; j > i; j--) { // ���ο� node�� �а� ũ�Ⱑ �� �۴ٸ� �ϳ��� �а� �� �ڸ��� ����
							dept[j] = dept[j - 1];
							dept_num[j] = dept_num[j - 1];
						}
						dept_cnt++;
						over++;
						dept[i] = srt_dept; // �а��迭�� ���ο� �а� �߰�
                        dept_num[i] = 1; // ���ο� �а��� ���� �ο��� 1�� �Է�
                        break;
					}
				}
				if (over == 0) { // dept �迭�� ������ �������� srt_dept�� �迭�� ���� �ʾҴٸ� ���� ū �����̹Ƿ� ���� �������� �ִ´�.
					dept[dept_cnt] = srt_dept;
					dept_num[dept_cnt] = 1;
					dept_cnt++;
				}
			}
		}
		else { // �̹� �ִ� �а����
			/* �а��л� 10000�� ����ó�� */
			for (int i = 0; i < dept_cnt; i++) {
				if (dept[i] == srt_dept) {
					if (dept_num[i] > 9999) { // 10000���� ������ ����ó��
						inval = true;
						return;
					}
					else { // 10000���� �ȳ����� �ο��߰�
						dept_num[i] += 1;
					}
				}
			}
		}
		if (inval == false) { // Ȥ�ö� inval�� true�� ���·� �� ������ �����ϸ� ������ ���� �� �����Ƿ� ������ �Ǵ�.
				new_code->next = head; // ����Ʈ�� �պκ�, �� ��忡 ���ο� ������ ��带 �߰��Ѵ�.
				head = new_code;
				
				std::cout << "A student is added in table!" << std::endl; // �߰����� �˸���.
				std::cout << dept_num[0];
		}

	}
	count++; // ��� ������ ������Ų��.
}


void list::delete_node(student stu) { // �л� ���� ���� �Լ�
	node* temp; 
	node* new_code = new node; // �����ϰ��� �ϴ� �л��� ������ ��� ���. �� ��带 ����Ʈ�� ��� ����� ���ϸ鼭 ���� ����� ��带 ã�´�.
	new_code->data = stu;
	new_code->next = NULL;
	std::string srt_dept = new_code->data.show_dept();
	std::string srt_name = new_code->data.show_name();
	std::string srt_gend = new_code->data.show_gender();
	int srt_age = new_code->data.show_age();
	inval = false;

	/* ���� ����ó�� */
	if (stu.blank_check() == 0) {
		inval = true;
		return;
	}
	/* Age ���� ����ó�� */
	if (srt_age < 18 || srt_age > 30) {
		inval = true;
		return;
	}
	/* Gender M,F ����ó�� */
	if (srt_gend != "M" && srt_gend != "F") {
		inval = true;
		return;
	}
	/* Dept �빮�� ����ó�� */
	for (int i = 0; srt_dept[i] != NULL; i++) {
		if (srt_dept[i] < 65 && srt_dept[i] > 90) {
			inval = true;
			return;
		}
	}

	for (temp = head; temp != NULL; temp = temp->next) {
		if (srt_dept.compare(temp->data.show_dept()) == 0) {
			if (srt_gend.compare(temp->data.show_gender()) == 0) {
				if (srt_name.compare(temp->data.show_name()) == 0) {
					if (srt_age == temp->data.show_age()) { // ���� ��� ������ ���ٸ�, �����ϰ��� �ϴ� ��带 ã�� ���� �ǹ�.
						if (count == 1) { // ����Ʈ�� ��尡 �ϳ����̶��
							delete(temp); // �ش� ��带 �����ϰ�
							head = NULL; // ���̻� ����Ʈ���� ��尡 �������� �����Ƿ� head�� tail ��� NULL�� ó���Ѵ�.
							tail = NULL;
							count--; // ��� ������ �ϳ� ���δ�.
							dept_num[0] -= 1; // �а��� �ο��� ���� ���δ�.
							dept[0] = '\0'; // �а��� �ο����� 0���̹Ƿ�, �ش� �а��� ����ó���ȴ�.
							std::cout << "Deleted!" << std::endl; // �����Ǿ����� �˸�
							return; // ������ �Ϸ�Ǿ����Ƿ� �Լ��� �����Ѵ�.
						}
						if (temp == head) { // ���� ���� ��尡 head���
							node* change = NULL; // ���ο� ��带 ����,
							change = head->next; // �ش� ��忡 head�� ���� ����� ������ ������ ���´�.
							delete(head); // ���� ����� head�� �����ϰ�,
							head = change; // head�� ��������Ƿ� head�� ���� ��带 ���ο� head�� �����Ѵ�.
						}
						else if (temp == tail) { // ���� ������尡 tail�̶��
							node* orary; // ���ο� ��带 ����
							orary = head; // ��带 head�� �����ϰ�,
							while (orary->next != tail) { // tail�� �ٷ� ���� ���� ����
								orary = orary->next;
							}
							orary->next = NULL; // tail ���� ����� next�� NULL�� ����Ű���� �Ѵ�.
							delete(temp); // tail�� �����Ѵ�.
							tail = orary; // ���ο� tail�� �����Ѵ�.
						}
						else { // head�� tail�� �ƴ� �߰��� ��带 �����Ѵٸ�
							node* orary; // ���ο� ��带 ����
							orary = head; // ��忡 �����ϰ�
							while (orary->next != temp) { // ���� ����� �ٷ� ���� ���� ����
								orary = orary->next;
							}
							orary->next = temp->next; // ���� ����� ���� ��� next�� ��������� ���� ��带 ����Ű���� �Ѵ�.
							delete(temp); // �׷��� �Ǹ� ���� ��尡 ����Ʈ���� �и��ǰ�, �ش� ��带 �����Ѵ�.
						}
						for (int i = 0; i < dept_cnt; i++) { 
							if (dept[i] == srt_dept) { 
								dept_num[i] -= 1; // �а��� �ο����� �Ѹ� ���δ�.
								if (dept_num[i] == 0) { // �ο� ���� �ٿ��� �� �ش� �а��� ���̻� �Ѹ� �������� �ʴٸ�
									for (int j = i; j < dept_cnt; j++) { 
										dept_num[j] = dept_num[j + 1]; //, �а� �迭�� �����԰� ���ÿ� �а� �ο����� �������Ѵ�.
										if (j + 1 < 9) {
											dept[j] = dept[j + 1]; // �а� �迭���� �ش� �а��� �����Ѵ�. ������ �迭�� ����� ���� �迭���� �ϳ��� ������ �о��ִ� �������� ������ �Ѵ�,
										}
										else if (j + 1 == 9) {
											dept[j] = '\0'; //dept[8]�� ��� dept[9]�� ������ �ʿ��ϴ�. �׷��� dept[9]�� �����Ƿ� �ش� ���ǿ����� dept[8]�� ��쵵�� �Ѵ�.
										}
									}
									dept[dept_cnt - 1] = '\0'; // dept[dept_cnt - 1]�� ������ ���� ���ο� �а� �迭�̴�. �̶� �ش� �迭�� �ƹ��͵� ����Ű�� �����Ƿ� ����ش�.
									dept_num[dept_cnt - 1] = 0; // ���� dept[dept_cnt -1]�� �ο����� 0���� �������ش�.
									dept_cnt--; // �а������� 1�� �����Ѵ�.
								}
							}
						}
						count--; // ��� ���� 1�� ����
						std::cout << "Deleted!" << std::endl; // �������� �˸�
						return; // �Լ�����
					}
				}
			}

		}
	}// for���� �������� �Է¹��� ���� ���� ��带 ã�� ���ϸ� �Լ��� return���� �ʰ� for���� �������´�.
	std::cout << "Can't Delete it" << std::endl; // ���� ��尡 �����Ƿ� �Է¹��� ������ ���� �� ����.
	return;
}

void list::sort() { // ���� �Լ�. ���ο� ��带 �Է¹��� �� �ٷ� sort�� �����Ѵ�.
	/* ���Ӱ� �߰��� ���� save_node �Լ��� ���� head�� ����ȴ�. ���� ����Ʈ�� �����ϴ� ���� �츮�� head�� �ִ� ������ ������ �°� sorting �ؾ� �ϴ� �Ͱ� ����*/
	std::string srt_dept = head->data.show_dept();
	std::string srt_name = head->data.show_name();
	std::string srt_gend = head->data.show_gender();
	int srt_age = head->data.show_age();
	node* temp; // �� ��带 �����̸鼭 �������� ��ġ�� ��Ÿ�� ���̴�.
	node* new_node = new node;
	new_node->data = head->data;
	new_node->next = NULL;
	if (count == 1l) { //��尡 1������ ��� 
		return;
	}

	for (temp = head; temp != NULL; temp = temp->next) { // ����Ʈ�� ó������ ������ ����. temp �̿�
		if (temp->next == NULL) { // ������ ���Ҵµ� ���ĵ��� ���ߴ� -> ���� �ް��̴�
			temp->next = new_node; // �ش� ����� ������, �� ����Ʈ�� ���� new_node�� �߰���Ų��.
			new_node->next = NULL; 
			tail = new_node; // �������̹Ƿ� ���Ӱ� tail ����
			break;
		}
		/* insertion sort�� �̿��ߴ� */
		if (srt_dept.compare(temp->next->data.show_dept()) <= 0) { // �а� �� : �� ��� <= temp���
			if (srt_dept.compare(temp->next->data.show_dept()) < 0) { // ����� <= temp��� temp���� �տ� �־�� �ϴ� ���� �и��ϹǷ� �տ� ��带 �ִ´�.
				new_node->next = temp->next;
				temp->next = new_node;
				break;
			}

			else if (srt_dept.compare(temp->next->data.show_dept()) == 0) { // ����� = temp���, ������ ������ ���� �𸣹Ƿ� ���� �񱳴���� gender�� ���ؾ� �Ѵ�.
				if (srt_gend.compare(temp->next->data.show_gender()) <= 0) { // ���� �� : ����� <= temp���
					if (srt_gend.compare(temp->next->data.show_gender()) < 0) { // ����� < temp��� ����尡 temp �տ� �ִ°� �и��ϹǷ� temp �տ� ��带 �ִ´�.
						new_node->next = temp->next;
						temp->next = new_node;
						break;
					}

					else if (srt_gend.compare(temp->next->data.show_gender()) == 0) { // ����� = temp���, ������ ������ ���� �𸣹Ƿ� ���� �񱳴���� name�� ���ؾ� �Ѵ�.
						if (srt_name.compare(temp->next->data.show_name()) <= 0) { // �̸� �� : ����� <= temp���
							if (srt_name.compare(temp->next->data.show_name()) < 0) { // ����� < temp��� ������ �и��ϹǷ� temp �տ� ��带 �ִ´�.
								new_node->next = temp->next;
								temp->next = new_node;
								break;
							}

							else if (srt_name.compare(temp->next->data.show_name()) == 0) { // ����� = temp���, ������ ������ ���� �𸣹Ƿ� ������ �񱳴���� age�� ���ؾ� �Ѵ�.
								if (srt_age <= temp->next->data.show_age()) { // ���� �� : ����� <= temp���
									if (srt_age < temp->next->data.show_age()) { // ���̰� temp���� �۴ٸ� �տ� �;� �ϹǷ� �տ� ��带 �ִ¤���.
										new_node->next = temp->next;
										temp->next = new_node;
										break;
									}
									else { // �װ� �ƴ϶�� ��� ������ ���� ���̴�. ������ �ߺ��ǹǷ� ����ó���� �����Ѵ�.
										inval = true;
										return;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	/* ��� ��尪�� ���� �������� ���Ӱ� �߰��ǹǷ� ��� �����ֱ�*/
	node* replace_head;
	replace_head = head;
	if (head != NULL) {
		head = head->next;
	}
	delete(replace_head);
	
}

void list::pivot(int cat, int fun) { // 4�� ����� �ǹ��� ���� �Լ��̴�. category ��ȣ�� function ��ȣ�� argument�� �޴´�.
	double dept_value[9] = {}; // �а��� ���� ���� ���忡 �̿�
	double gend_value[2] = {}; // ������ ���� ���� ���忡 �̿�
	int man = 0; // ���� �ο��� ���
	int	wan = 0; // ���� �ο��� ���
	node* temp;
	if (count == 0) { // ���࿡ ��尡 ���ٸ�
		std::cout << "We don't have any information to pivot. Please try again." << std::endl; // pivot�� �� �����Ƿ� ����Ұ��޼��� ����
		return;
	}
	std::cout << std::fixed; //�Ҽ����ڸ� ������ ���� �۾�
	std::cout.precision(1); // �Ҽ��� ���ڸ����� �ݿø� �Ͽ� ��Ÿ����.
	switch (cat) { // ī�װ� ��ȣ
	case 1: // 1�� : �а�
		std::cout << "Dept" << '\t';
		switch (fun) { // �Լ� ��ȣ
		case 1: // 1�� : ���
			std::cout << "Average" << std::endl;
			for (int i = 0; i < dept_cnt; i++) {
				for (temp = head; temp != NULL; temp = temp->next) {
					if (dept[i] == temp->data.show_dept()) { 
						dept_value[i] += temp->data.show_age(); // ��ü ����Ʈ�� �����ϸ鼭 �а� �������� ���̸� dept_value �迭�� ���ذ���.
					}
				}
				dept_value[i] /= dept_num[i]; // ������ ������ �а� ���������� ������ ����� ����Ѵ�.
			}
			for (int i = 0; i < dept_cnt; i++) {
				std::cout << dept[i] << '\t';
				std::cout << dept_value[i] << std::endl; // ����� ����Ѵ�.
			}
			return;
		case 2: // 2�� : �ִ�
			std::cout << "Max" << std::endl;
			for (int i = 0; i < dept_cnt; i++){
				for (temp = head; temp != NULL; temp = temp->next) {
					if(dept[i] == temp->data.show_dept()){
						if (dept_value[i] < temp->data.show_age()) {
							dept_value[i] = temp->data.show_age(); //����Ʈ�� �����ϸ鼭 �ش� �а� ���������� ���̸� ���ϸ� �ִ��� ã�´�.
						}
					}
				}
			}
			for (int i = 0; i < dept_cnt; i++) {
				std::cout << dept[i] << '\t' << dept_value[i] << std::endl; // �ִ��� ����Ѵ�.
			}
			return;
		case 3: // 3�� : �ּڰ�
			std::cout << "Min" << std::endl;
			for (int i = 0; i < 9; i++) {
				dept_value[i] = 31;
			}
			for (int i = 0; i < dept_cnt; i++) {
				for (temp = head; temp != NULL; temp = temp->next) {
					if (dept[i] == temp->data.show_dept()) {
						if (dept_value[i] > temp->data.show_age()) {
							dept_value[i] = temp->data.show_age(); // ����Ʈ ��ü�� �����ϸ� �а��� �ּҰ��� ã�´�.
						}
					}
				}
			}
			for (int i = 0; i < dept_cnt; i++) {
				std::cout << dept[i] << '\t' << dept_value[i] << std::endl; // ���
			}
			return;
		}
	case 2: // 2�� : ����
		std::cout << "Gender" << '\t';
		switch (fun) {
		case 1: // 1�� : ���
			std::cout << "Average" << std::endl;
				for (temp = head; temp != NULL; temp = temp->next) {
					if (temp->data.show_gender() == "F") { // ���ڶ��
						gend_value[0] += temp->data.show_age(); 
						wan++; 
						
					}
					else if(temp->data.show_gender() == "M"){ // ���ڶ��
						gend_value[1] += temp->data.show_age();
						man++;
				    }
			    }
				gend_value[0] /= wan; // �� ������ ���� ���� �ο����� ������ ����� ���Ѵ�.
				gend_value[1] /= man;
				if (wan != 0) {// �ο����� 0�� ��� ������� �����Ƿ�
					std::cout << "F" << '\t' << gend_value[0] << std::endl; 
				}
				if (man != 0) {// �ο����� 0�� ��� ������� �����Ƿ�
					std::cout << "M" << '\t' << gend_value[1] << std::endl;
				}
			return;

		case 2: // 2�� : �ִ�
			std::cout << "Max" << std::endl;
			for (temp = head; temp != NULL; temp = temp->next) {
				if (temp->data.show_gender() == "F") { 
					if (gend_value[0] < temp->data.show_age()) {
						gend_value[0] = temp->data.show_age(); // ���� �迭�� ���� �ִ� ����
					}
					wan++;

				}
				else if (temp->data.show_gender() == "M") {
					if (gend_value[1] < temp->data.show_age()) {
						gend_value[1] = temp->data.show_age(); // ���� �迭�� ���� �ִ� ����
					}
					man++;
				}
			}
			if (wan != 0) { // ���
				std::cout << "F" << '\t' << gend_value[0] << std::endl;
			}
			if (man != 0) {
				std::cout << "M" << '\t' << gend_value[1] << std::endl;
			}
			return;

		case 3: // 3�� : �ּڰ�
			gend_value[0] = 31; // �ִ��� ��� ���� ó���� �ʱ�ȭ ���� 0�� ���Ͽ� ���� �����ϳ�, 
			gend_value[1] = 31; // �ּڰ��� 0�� ���ϸ� 0�� ���Ƿ� ���� �������� ū ���� 31�� �ʱ�ȭ�Ͽ� �ּڰ��� ���ߴ�.
			std::cout << "Min" << std::endl;
			for (temp = head; temp != NULL; temp = temp->next) { // ����� 2�� �ִ񰪰� �ſ� �����ϴ�
				if (temp->data.show_gender() == "F") {
					if (gend_value[0] > temp->data.show_age()) {
						gend_value[0] = temp->data.show_age();
					}
					wan++;

				}
				else if (temp->data.show_gender() == "M") {
					if (gend_value[1] > temp->data.show_age()) {
						gend_value[1] = temp->data.show_age();
					}
					man++;
				}
			}
			if (wan != 0) {
				std::cout << "F" << '\t' << gend_value[0] << std::endl;
			}
			if (man != 0) {
				std::cout << "M" << '\t' << gend_value[1] << std::endl;
			}
			return;
		}

	case 3: // 3�� : �а� �� ����
		std::cout << "Dept" << '\t' << "Gender" << '\t';
		switch (fun) { 
		case 1: // 1�� : ���
			std::cout << "Average" << std::endl;
			for (int i = 0; i < dept_cnt; i++) {
				man = 0;
				wan = 0;
				for (temp = head; temp != NULL; temp = temp->next) {
					if (dept[i] == temp->data.show_dept()) { // �а��� ����
						if (temp->data.show_gender() == "F") { // ������ ��� ���� �迭�� ���� �߰�
							gend_value[0] += temp->data.show_age();
							wan++;
						}
						else if (temp->data.show_gender() == "M") { // ������ ��� ���� �迭�� ���� �߰�
							gend_value[1] += temp->data.show_age();
							man++;
						}
					}
				}
				gend_value[0] /= wan; // �ο����� ������ ��� ����
				gend_value[1] /= man;
				if (wan != 0) { // �ο����� 0�� �ƴ϶�� ���
					std::cout << dept[i] << '\t' << "F" << '\t' << gend_value[0] << std::endl;
				}
				if (man != 0) {
					std::cout << dept[i] << '\t' << "M" << '\t' << gend_value[1] << std::endl;
				}
				gend_value[0] = 0; // ���� �а��� ���� �� ���̰���� ���� �ʱ�ȭ
				gend_value[1] = 0;
			}
			return;
		case 2: // 2�� : �ִ�
			std::cout << "Max" << std::endl;
			for (int i = 0; i < dept_cnt; i++) {
				man = 0;
				wan = 0;
				for (temp = head; temp != NULL; temp = temp->next) {
					if (dept[i] == temp->data.show_dept()) { // �а��� ����
						if (temp->data.show_gender() == "F") { // ������ ���
							if (gend_value[0] < temp->data.show_age()) {
								gend_value[0] = temp->data.show_age(); //���� ���� �ִ� ����
							}
							wan++;
						}
						else if (temp->data.show_gender() == "M") { // ������ �ܿ�
							if (gend_value[1] < temp->data.show_age()) {
								gend_value[1] = temp->data.show_age(); // ���� ���� �ִ� ����
							}
							man++;
						}
					}
				}
				if (wan != 0) { // �ο����� 0�� �ƴϸ� ���
					std::cout << dept[i] << '\t' << "F" << '\t' << gend_value[0] << std::endl;
				}
				if (man != 0) {
					std::cout << dept[i] << '\t' << "M" << '\t' << gend_value[1] << std::endl;
				}
				gend_value[0] = 0; // ���� �а� ����� ���� �ʱ�ȭ
				gend_value[1] = 0;
			}

			return;
		case 3: // 3�� : �ּڰ�
			std::cout << "Min" << std::endl;
			gend_value[0] = 31; // ī�װ� 2���� 3��ó�� ������ ������ 31�� �ʱ�ȭ��.
			gend_value[1] = 31;
			for (int i = 0; i < dept_cnt; i++) {
				man = 0;
				wan = 0;
				for (temp = head; temp != NULL; temp = temp->next) { // �Ʒ� ����� ī�װ� 3���� 2�� �ִ񰪰� ������.
					if (dept[i] == temp->data.show_dept()) {
						if (temp->data.show_gender() == "F") {
							if (gend_value[0] > temp->data.show_age()) {
								gend_value[0] = temp->data.show_age();
							}
							wan++;
						}
						else if (temp->data.show_gender() == "M") {
							if (gend_value[1] > temp->data.show_age()) {
								gend_value[1] = temp->data.show_age();
							}
							man++;
						}
					}
				}
				if (wan != 0) {
					std::cout << dept[i] << '\t' << "F" << '\t' << gend_value[0] << std::endl;
				}
				if (man != 0) {
					std::cout << dept[i] << '\t' << "M" << '\t' << gend_value[1] << std::endl;
				}
				gend_value[0] = 31;
				gend_value[1] = 31;
			}
			return;
		}
	}
}


void list::print_list() { // ����Ʈ ��� �Լ�
	node* temp;
	std::cout << "Dept" << "\t" << "Gender" << "\t" << "Name" << "\t" << "Age" << std::endl;
	for (temp = head; temp != NULL; temp = temp->next) {
		std::cout << temp->data.show_dept() << "\t" << temp->data.show_gender() << "\t"
			<< temp->data.show_name() << "\t" << temp->data.show_age() << std::endl;
	}
}