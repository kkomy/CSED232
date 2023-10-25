#include<iostream>
#include<string>
#include"list.h"

void list::save_node(student stu) { // 학생정보 저장 함수
	node* temp;
	node* new_code = new node; // 리스트에 추가할 노드. 해당 노드는 입력한 정보를 저장하고 리스트에 들어간다.
	new_code->data = stu;
	new_code->next = NULL;
	std::string srt_dept = new_code->data.show_dept();
	std::string srt_name = new_code->data.show_name();
	std::string srt_gend = new_code->data.show_gender();
	int srt_age = new_code->data.show_age();
	inval = false; // 에러처리용 변수 초기화. true일 경우 에러메세지를 출력하도록 한다.

	/* 공백 예외처리 */
	if (stu.blank_check() == 0) {
		inval = true;
		return;
	}
	/* Age 범위 예외처리 */
	if (srt_age < 18 || srt_age > 30) {
		inval = true;
		return;
	}
	if (srt_age)
	/* Gender M,F 예외처리 */
	if (srt_gend != "M" && srt_gend != "F") {
		inval = true;
		return;
	}
	/* Dept 대문자 예외처리 */
	for (int i = 0; srt_dept[i] != NULL; i++) {
		if (srt_dept[i] < 65 || srt_dept[i] > 90) {
			inval = true;
			return;
		}
	}

	if (count == 0) { // 리스트에 노드가 아무것도 없다면
		head = new_code;
		tail = new_code;
		tail->next = NULL;
		count = 1; // 노드 갯수 1개
		dept_cnt = 1; // 학과 갯수 1개
		dept[0] = srt_dept; // 학과 정보를 저장하는 배열에 입력됨
		dept_num[0] += 1; // 학과인원추가
		std::cout << "A student is added in table!" << std::endl;
		return;
	}
	else { // 리스트에 노드가 이미 존재한다면
		/* 중복검사 */
		for (temp = head; temp != NULL; temp = temp->next) {
			if (srt_dept == temp->data.show_dept()) {
				if (srt_gend == temp->data.show_gender()) {
					if (srt_name == temp->data.show_name()) {
						if (srt_age == temp->data.show_age()) {
							std::cout << "The student already exists." << std::endl; // 중복된 노드가 존재한다면 이미 있음을 알림
							return; // 이후 함수 종료
						}
					}
				}
			}
		}

		int check_samedept = 0; // 추가한 노드의 학과가 이미 있는지 조사. 0이면 새로운 학과임
		for (temp = head; temp != NULL; temp = temp->next) {
			for (int i = 0; i < dept_cnt; i++) {
				if (temp->data.show_dept() == srt_dept) { // 만약 학과가 같은 게 있다면?
					check_samedept++; // check_samedept에 1추가. 새로운 학과가 아님을 의미
				}
			}
		}
		if (check_samedept == 0) { // 새로운 학과라면
			if (dept_cnt == 9) { // 9개의 학과가 모두 찼다면
				/* 학과갯수 예외처리 */
				inval = true; 
				return;
			}
			else {// 아직 학과가 9개가 안되었다면 dept배열 사전순정리
				int over = 0;
				for (int i = 0; i < dept_cnt; i++) {
					if (srt_dept.compare(dept[i]) < 0) {
						for (int j = dept_cnt; j > i; j--) { // 새로운 node의 학과 크기가 더 작다면 하나씩 밀고 그 자리에 넣음
							dept[j] = dept[j - 1];
							dept_num[j] = dept_num[j - 1];
						}
						dept_cnt++;
						over++;
						dept[i] = srt_dept; // 학과배열에 새로운 학과 추가
                        dept_num[i] = 1; // 새로운 학과에 대한 인원수 1명 입력
                        break;
					}
				}
				if (over == 0) { // dept 배열의 끝까지 갔음에도 srt_dept가 배열에 들어가지 않았다면 가장 큰 길이이므로 가장 마지막에 넣는다.
					dept[dept_cnt] = srt_dept;
					dept_num[dept_cnt] = 1;
					dept_cnt++;
				}
			}
		}
		else { // 이미 있는 학과라면
			/* 학과학생 10000명 예외처리 */
			for (int i = 0; i < dept_cnt; i++) {
				if (dept[i] == srt_dept) {
					if (dept_num[i] > 9999) { // 10000명이 넘으면 예외처리
						inval = true;
						return;
					}
					else { // 10000명이 안넘으면 인원추가
						dept_num[i] += 1;
					}
				}
			}
		}
		if (inval == false) { // 혹시라도 inval이 true가 상태로 이 구문에 도착하면 오류를 범할 수 있으므로 제한을 건다.
				new_code->next = head; // 리스트의 앞부분, 즉 헤드에 새로운 정보의 노드를 추가한다.
				head = new_code;
				
				std::cout << "A student is added in table!" << std::endl; // 추가됨을 알린다.
				std::cout << dept_num[0];
		}

	}
	count++; // 노드 갯수를 증가시킨다.
}


void list::delete_node(student stu) { // 학생 정보 삭제 함수
	node* temp; 
	node* new_code = new node; // 삭제하고자 하는 학생의 정보가 담긴 노드. 이 노드를 리스트의 모든 노드들과 비교하면서 삭제 대상인 노드를 찾는다.
	new_code->data = stu;
	new_code->next = NULL;
	std::string srt_dept = new_code->data.show_dept();
	std::string srt_name = new_code->data.show_name();
	std::string srt_gend = new_code->data.show_gender();
	int srt_age = new_code->data.show_age();
	inval = false;

	/* 공백 예외처리 */
	if (stu.blank_check() == 0) {
		inval = true;
		return;
	}
	/* Age 범위 예외처리 */
	if (srt_age < 18 || srt_age > 30) {
		inval = true;
		return;
	}
	/* Gender M,F 예외처리 */
	if (srt_gend != "M" && srt_gend != "F") {
		inval = true;
		return;
	}
	/* Dept 대문자 예외처리 */
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
					if (srt_age == temp->data.show_age()) { // 만약 모든 정보가 같다면, 삭제하고자 하는 노드를 찾은 것을 의미.
						if (count == 1) { // 리스트의 노드가 하나뿐이라면
							delete(temp); // 해당 노드를 삭제하고
							head = NULL; // 더이상 리스트에는 노드가 존재하지 않으므로 head와 tail 모두 NULL로 처리한다.
							tail = NULL;
							count--; // 노드 갯수를 하나 줄인다.
							dept_num[0] -= 1; // 학과의 인원수 또한 줄인다.
							dept[0] = '\0'; // 학과의 인원수가 0명이므로, 해당 학과는 삭제처리된다.
							std::cout << "Deleted!" << std::endl; // 삭제되었음을 알림
							return; // 삭제가 완료되었으므로 함수를 종료한다.
						}
						if (temp == head) { // 만약 삭제 노드가 head라면
							node* change = NULL; // 새로운 노드를 선언,
							change = head->next; // 해당 노드에 head의 다음 노드의 정보를 저장해 놓는다.
							delete(head); // 삭제 노드인 head를 삭제하고,
							head = change; // head가 사라졌으므로 head의 다음 노드를 새로운 head로 설정한다.
						}
						else if (temp == tail) { // 만약 삭제노드가 tail이라면
							node* orary; // 새로운 노드를 선언
							orary = head; // 노드를 head로 지정하고,
							while (orary->next != tail) { // tail의 바로 이전 노드로 변경
								orary = orary->next;
							}
							orary->next = NULL; // tail 직전 노드의 next를 NULL을 가리키도록 한다.
							delete(temp); // tail을 삭제한다.
							tail = orary; // 새로운 tail을 설정한다.
						}
						else { // head도 tail도 아닌 중간의 노드를 삭제한다면
							node* orary; // 새로운 노드를 선언
							orary = head; // 헤드에 고정하고
							while (orary->next != temp) { // 삭제 노드의 바로 이전 노드로 변경
								orary = orary->next;
							}
							orary->next = temp->next; // 삭제 노드의 이전 노드 next가 삭제노드의 다음 노드를 가리키도록 한다.
							delete(temp); // 그렇게 되면 삭제 노드가 리스트에서 분리되고, 해당 노드를 삭제한다.
						}
						for (int i = 0; i < dept_cnt; i++) { 
							if (dept[i] == srt_dept) { 
								dept_num[i] -= 1; // 학과의 인원수를 한명 줄인다.
								if (dept_num[i] == 0) { // 인원 수를 줄였을 때 해당 학과가 더이상 한명도 남아있지 않다면
									for (int j = i; j < dept_cnt; j++) { 
										dept_num[j] = dept_num[j + 1]; //, 학과 배열을 정렬함과 동시에 학과 인원수도 재정렬한다.
										if (j + 1 < 9) {
											dept[j] = dept[j + 1]; // 학과 배열에서 해당 학과를 삭제한다. 삭제한 배열을 지우고 이후 배열들을 하나씩 앞으로 밀어주는 형식으로 정렬을 한다,
										}
										else if (j + 1 == 9) {
											dept[j] = '\0'; //dept[8]의 경우 dept[9]의 정보가 필요하다. 그러나 dept[9]가 없으므로 해당 조건에서는 dept[8]을 비우도록 한다.
										}
									}
									dept[dept_cnt - 1] = '\0'; // dept[dept_cnt - 1]은 재정렬 이후 새로운 학과 배열이다. 이때 해당 배열은 아무것도 가리키지 않으므로 비워준다.
									dept_num[dept_cnt - 1] = 0; // 역시 dept[dept_cnt -1]의 인원수도 0으로 설정해준다.
									dept_cnt--; // 학과갯수를 1개 삭제한다.
								}
							}
						}
						count--; // 노드 갯수 1개 줄임
						std::cout << "Deleted!" << std::endl; // 삭제됨을 알림
						return; // 함수종료
					}
				}
			}

		}
	}// for문이 끝날동안 입력받은 노드와 같은 노드를 찾지 못하면 함수가 return되지 않고 for문을 빠져나온다.
	std::cout << "Can't Delete it" << std::endl; // 같은 노드가 없으므로 입력받은 정보는 지울 수 없다.
	return;
}

void list::sort() { // 정렬 함수. 새로운 노드를 입력받은 후 바로 sort를 진행한다.
	/* 새롭게 추가한 노드는 save_node 함수에 의해 head에 저장된다. 따라서 리스트를 정렬하는 것은 우리는 head에 있는 정보를 순서에 맞게 sorting 해야 하는 것과 같다*/
	std::string srt_dept = head->data.show_dept();
	std::string srt_name = head->data.show_name();
	std::string srt_gend = head->data.show_gender();
	int srt_age = head->data.show_age();
	node* temp; // 이 노드를 움직이면서 최종적인 위치를 나타낼 것이다.
	node* new_node = new node;
	new_node->data = head->data;
	new_node->next = NULL;
	if (count == 1l) { //노드가 1개뿐인 경우 
		return;
	}

	for (temp = head; temp != NULL; temp = temp->next) { // 리스트의 처음부터 끝까지 조사. temp 이용
		if (temp->next == NULL) { // 끝까지 돌았는데 정렬되지 못했다 -> 가장 뒷값이다
			temp->next = new_node; // 해당 노드의 다음값, 즉 리스트에 끝에 new_node를 추가시킨다.
			new_node->next = NULL; 
			tail = new_node; // 마지막이므로 새롭게 tail 설정
			break;
		}
		/* insertion sort을 이용했다 */
		if (srt_dept.compare(temp->next->data.show_dept()) <= 0) { // 학과 비교 : 새 노드 <= temp라면
			if (srt_dept.compare(temp->next->data.show_dept()) < 0) { // 새노드 <= temp라면 temp보다 앞에 있어야 하는 것이 분명하므로 앞에 노드를 넣는다.
				new_node->next = temp->next;
				temp->next = new_node;
				break;
			}

			else if (srt_dept.compare(temp->next->data.show_dept()) == 0) { // 새노드 = temp라면, 무엇이 앞인지 아직 모르므로 다음 비교대상인 gender을 비교해야 한다.
				if (srt_gend.compare(temp->next->data.show_gender()) <= 0) { // 성별 비교 : 새노드 <= temp라면
					if (srt_gend.compare(temp->next->data.show_gender()) < 0) { // 새노드 < temp라면 새노드가 temp 앞에 있는게 분명하므로 temp 앞에 노드를 넣는다.
						new_node->next = temp->next;
						temp->next = new_node;
						break;
					}

					else if (srt_gend.compare(temp->next->data.show_gender()) == 0) { // 새노드 = temp라면, 무엇이 앞인지 아직 모르므로 다음 비교대상인 name을 비교해야 한다.
						if (srt_name.compare(temp->next->data.show_name()) <= 0) { // 이름 비교 : 새노드 <= temp라면
							if (srt_name.compare(temp->next->data.show_name()) < 0) { // 새노드 < temp라면 순서가 분명하므로 temp 앞에 노드를 넣는다.
								new_node->next = temp->next;
								temp->next = new_node;
								break;
							}

							else if (srt_name.compare(temp->next->data.show_name()) == 0) { // 새노드 = temp라면, 무엇이 앞인지 아직 모르므로 마지막 비교대상인 age를 비교해야 한닫.
								if (srt_age <= temp->next->data.show_age()) { // 나이 비교 : 새노드 <= temp라면
									if (srt_age < temp->next->data.show_age()) { // 나이가 temp보다 작다면 앞에 와야 하므로 앞에 노드를 넣는ㄷ다.
										new_node->next = temp->next;
										temp->next = new_node;
										break;
									}
									else { // 그게 아니라면 모든 정보가 같은 것이다. 정보가 중복되므로 예외처리를 진행한다.
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
	/* 헤드 노드값이 정렬 과정에서 새롭게 추가되므로 헤드 없애주기*/
	node* replace_head;
	replace_head = head;
	if (head != NULL) {
		head = head->next;
	}
	delete(replace_head);
	
}

void list::pivot(int cat, int fun) { // 4번 기능인 피벗을 위한 함수이다. category 번호와 function 번호를 argument로 받는다.
	double dept_value[9] = {}; // 학과에 따른 나이 저장에 이용
	double gend_value[2] = {}; // 성별에 따른 나이 저장에 이용
	int man = 0; // 남자 인원수 계산
	int	wan = 0; // 여자 인원수 계산
	node* temp;
	if (count == 0) { // 만약에 노드가 없다면
		std::cout << "We don't have any information to pivot. Please try again." << std::endl; // pivot할 게 없으므로 실행불가메세지 전달
		return;
	}
	std::cout << std::fixed; //소수점자리 고정을 위한 작업
	std::cout.precision(1); // 소수점 한자리까지 반올림 하여 나타낸다.
	switch (cat) { // 카테고리 번호
	case 1: // 1번 : 학과
		std::cout << "Dept" << '\t';
		switch (fun) { // 함수 번호
		case 1: // 1번 : 평균
			std::cout << "Average" << std::endl;
			for (int i = 0; i < dept_cnt; i++) {
				for (temp = head; temp != NULL; temp = temp->next) {
					if (dept[i] == temp->data.show_dept()) { 
						dept_value[i] += temp->data.show_age(); // 전체 리스트를 조사하면서 학과 구성원의 나이를 dept_value 배열에 더해간다.
					}
				}
				dept_value[i] /= dept_num[i]; // 나이의 총합을 학과 구성원수로 나누어 평균을 계산한다.
			}
			for (int i = 0; i < dept_cnt; i++) {
				std::cout << dept[i] << '\t';
				std::cout << dept_value[i] << std::endl; // 평균을 출력한다.
			}
			return;
		case 2: // 2번 : 최댓값
			std::cout << "Max" << std::endl;
			for (int i = 0; i < dept_cnt; i++){
				for (temp = head; temp != NULL; temp = temp->next) {
					if(dept[i] == temp->data.show_dept()){
						if (dept_value[i] < temp->data.show_age()) {
							dept_value[i] = temp->data.show_age(); //리스트를 조사하면서 해당 학과 구성원들의 나이를 비교하며 최댓값을 찾는다.
						}
					}
				}
			}
			for (int i = 0; i < dept_cnt; i++) {
				std::cout << dept[i] << '\t' << dept_value[i] << std::endl; // 최댓값을 출력한다.
			}
			return;
		case 3: // 3번 : 최솟값
			std::cout << "Min" << std::endl;
			for (int i = 0; i < 9; i++) {
				dept_value[i] = 31;
			}
			for (int i = 0; i < dept_cnt; i++) {
				for (temp = head; temp != NULL; temp = temp->next) {
					if (dept[i] == temp->data.show_dept()) {
						if (dept_value[i] > temp->data.show_age()) {
							dept_value[i] = temp->data.show_age(); // 리스트 전체를 조사하며 학과별 최소값을 찾는다.
						}
					}
				}
			}
			for (int i = 0; i < dept_cnt; i++) {
				std::cout << dept[i] << '\t' << dept_value[i] << std::endl; // 출력
			}
			return;
		}
	case 2: // 2번 : 성별
		std::cout << "Gender" << '\t';
		switch (fun) {
		case 1: // 1번 : 평균
			std::cout << "Average" << std::endl;
				for (temp = head; temp != NULL; temp = temp->next) {
					if (temp->data.show_gender() == "F") { // 여자라면
						gend_value[0] += temp->data.show_age(); 
						wan++; 
						
					}
					else if(temp->data.show_gender() == "M"){ // 남자라면
						gend_value[1] += temp->data.show_age();
						man++;
				    }
			    }
				gend_value[0] /= wan; // 각 성별의 나이 합을 인원수로 나누어 평균을 구한다.
				gend_value[1] /= man;
				if (wan != 0) {// 인원수가 0일 경우 출력하지 않으므로
					std::cout << "F" << '\t' << gend_value[0] << std::endl; 
				}
				if (man != 0) {// 인원수가 0일 경우 출력하지 않으므로
					std::cout << "M" << '\t' << gend_value[1] << std::endl;
				}
			return;

		case 2: // 2번 : 최댓값
			std::cout << "Max" << std::endl;
			for (temp = head; temp != NULL; temp = temp->next) {
				if (temp->data.show_gender() == "F") { 
					if (gend_value[0] < temp->data.show_age()) {
						gend_value[0] = temp->data.show_age(); // 여자 배열에 대한 최댓값 갱신
					}
					wan++;

				}
				else if (temp->data.show_gender() == "M") {
					if (gend_value[1] < temp->data.show_age()) {
						gend_value[1] = temp->data.show_age(); // 남자 배열에 대한 최댓값 갱신
					}
					man++;
				}
			}
			if (wan != 0) { // 출력
				std::cout << "F" << '\t' << gend_value[0] << std::endl;
			}
			if (man != 0) {
				std::cout << "M" << '\t' << gend_value[1] << std::endl;
			}
			return;

		case 3: // 3번 : 최솟값
			gend_value[0] = 31; // 최댓값의 경우 가장 처음에 초기화 값인 0과 비교하여 값을 갱신하나, 
			gend_value[1] = 31; // 최솟값은 0과 비교하면 0이 들어가므로 나이 범위보다 큰 값인 31로 초기화하여 최솟값을 비교했다.
			std::cout << "Min" << std::endl;
			for (temp = head; temp != NULL; temp = temp->next) { // 방식은 2번 최댓값과 매우 유사하다
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

	case 3: // 3번 : 학과 및 성별
		std::cout << "Dept" << '\t' << "Gender" << '\t';
		switch (fun) { 
		case 1: // 1번 : 평균
			std::cout << "Average" << std::endl;
			for (int i = 0; i < dept_cnt; i++) {
				man = 0;
				wan = 0;
				for (temp = head; temp != NULL; temp = temp->next) {
					if (dept[i] == temp->data.show_dept()) { // 학과에 따라서
						if (temp->data.show_gender() == "F") { // 여자일 경우 여자 배열에 나이 추가
							gend_value[0] += temp->data.show_age();
							wan++;
						}
						else if (temp->data.show_gender() == "M") { // 남자일 경우 남자 배열에 나이 추가
							gend_value[1] += temp->data.show_age();
							man++;
						}
					}
				}
				gend_value[0] /= wan; // 인원수로 나누어 평균 산정
				gend_value[1] /= man;
				if (wan != 0) { // 인원수가 0이 아니라면 출력
					std::cout << dept[i] << '\t' << "F" << '\t' << gend_value[0] << std::endl;
				}
				if (man != 0) {
					std::cout << dept[i] << '\t' << "M" << '\t' << gend_value[1] << std::endl;
				}
				gend_value[0] = 0; // 다음 학과의 성별 별 나이계산을 위해 초기화
				gend_value[1] = 0;
			}
			return;
		case 2: // 2번 : 최댓값
			std::cout << "Max" << std::endl;
			for (int i = 0; i < dept_cnt; i++) {
				man = 0;
				wan = 0;
				for (temp = head; temp != NULL; temp = temp->next) {
					if (dept[i] == temp->data.show_dept()) { // 학과에 따라
						if (temp->data.show_gender() == "F") { // 여자의 경우
							if (gend_value[0] < temp->data.show_age()) {
								gend_value[0] = temp->data.show_age(); //여성 나이 최댓값 갱신
							}
							wan++;
						}
						else if (temp->data.show_gender() == "M") { // 남자의 겨웅
							if (gend_value[1] < temp->data.show_age()) {
								gend_value[1] = temp->data.show_age(); // 남성 나이 최댓값 갱신
							}
							man++;
						}
					}
				}
				if (wan != 0) { // 인원수가 0이 아니면 출력
					std::cout << dept[i] << '\t' << "F" << '\t' << gend_value[0] << std::endl;
				}
				if (man != 0) {
					std::cout << dept[i] << '\t' << "M" << '\t' << gend_value[1] << std::endl;
				}
				gend_value[0] = 0; // 다음 학과 출력을 위해 초기화
				gend_value[1] = 0;
			}

			return;
		case 3: // 3번 : 최솟값
			std::cout << "Min" << std::endl;
			gend_value[0] = 31; // 카테고리 2번의 3번처럼 동일한 이유로 31로 초기화함.
			gend_value[1] = 31;
			for (int i = 0; i < dept_cnt; i++) {
				man = 0;
				wan = 0;
				for (temp = head; temp != NULL; temp = temp->next) { // 아래 기능은 카테고리 3번의 2번 최댓값과 유사함.
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


void list::print_list() { // 리스트 출력 함수
	node* temp;
	std::cout << "Dept" << "\t" << "Gender" << "\t" << "Name" << "\t" << "Age" << std::endl;
	for (temp = head; temp != NULL; temp = temp->next) {
		std::cout << temp->data.show_dept() << "\t" << temp->data.show_gender() << "\t"
			<< temp->data.show_name() << "\t" << temp->data.show_age() << std::endl;
	}
}