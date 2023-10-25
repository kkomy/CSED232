#include"drawer.h"
#include<iostream>

drawer::drawer() {
	wid = 0;
	hei = 0;
	map = {};
}

drawer::~drawer() {
	delete art; // main �Լ����� �Ҵ�Ǿ��� art �Ҵ� ����
}

drawer::drawer(artist* a) {
	art = a; // artist Ÿ�� object ����
	wid = a->call_width(); // �׸� �ʺ� ����
	hei = a->call_height(); // �׸� ���� ����
	for (int i = 0; i < a->call_height(); i++) {
		for (int j = 0; j < a->call_width(); j++) {
			map.push_back(a->mapper(j, i)); // mapper �Լ��� ���� ���� ��ȯ
		}
	}
}

downsample::downsample() {
	wid = 0;
	hei = 0;
	map = {};
}

downsample::~downsample() {
}

downsample::downsample(artist* a) {
	art = a;
	wid = a->call_width();
	hei = a->call_height();
	for (int i = 0; i < a->call_height(); i++) {
		for (int j = 0; j < a->call_width(); j++) {
			map.push_back(a->mapper(j, i));// mapper �Լ��� ���� ���� ��ȯ
		}
	}
}
upsample::upsample() {
	wid = 0;
	hei = 0;
	map = {};
}

upsample::~upsample() {
}

upsample::upsample(artist* a) {
	wid = a->call_width();
	hei = a->call_height();
	for (int i = 0; i < a->call_height(); i++) {
		for (int j = 0; j < a->call_width(); j++) {
			map.push_back(a->mapper(j, i));// mapper �Լ��� ���� ���� ��ȯ
		}
	}
}

std::string drawer::draw() {
	std::string pic;
	for (int i = 0; i < hei; i++) {
		for (int j = 0; j < wid; j++) {
			pic += map.at(i * wid + j);
		}
		pic += '\n'; // ���� ���� ǥ���� ������ �ٹٲ�
	}
	return pic;
}

std::string downsample::draw() {
	std::string pic;

	for (int i = 0; i < hei; i++) {
		for (int j = 0; j < wid; j++) {
			if (i % 2 == 0 && j % 2 == 0) { // ���� ���� ���� ���ݾ� ����ϹǷ�, ��ǥ���� ��� ¦���� ���� �ȼ����� ���
				pic += map.at(i * wid + j);
			}
		}
		if (i % 2 == 0)
		pic += '\n';
	}
	return pic;
}

std::string upsample::draw() {
	std::string pic;
	for (int i = 0; i < hei; i++) {
		for (int k = 0; k < 2; k++) { // ���� �ι�
			for (int j = 0; j < wid; j++) {
				pic += map.at(i * wid + j); // ���� �ι�
				pic += map.at(i * wid + j);
			}
			pic += '\n';
		}
	}
	return pic;
}

scale::scale() {
	x = 0;
	y = 0;
	wid = 0;
	hei = 0;
	map = {};
}

scale::~scale() {
}

scale::scale(artist* a, int xx, int yy){
	art = a;
	x = xx;
	y = yy;
	wid = a->call_width();
	hei = a->call_height();
	for (int i = 0; i < a->call_height(); i++) {
		for (int j = 0; j < a->call_width(); j++) {
			map.push_back(a->mapper(j, i));// mapper �Լ��� ���� ���� ��ȯ
		}
	}
}

std::string scale::draw() {
	std::vector<char> scaling;
	std::string pic;
	if (x > 0 && y > 0) { // �ʺ� ���� �Ѵ� Ȯ���� ��
		for (int i = 0; i < hei; i++) { 
			for (int m = 0; m < y; m++) { // ���� y��
				for (int j = 0; j < wid; j++) {
					for (int k = 0; k < x; k++) { // �ʺ� x��
						pic += map.at(i * wid + j);
					}
				}
				pic += '\n';
			}
		}
	}
	else if (x > 0 && y < 0) { // �ʺ�� Ȯ��, ���̴� ���
		for (int i = 0; i < hei; i++) {
			for (int j = 0; j < wid; j++) {
				if(i % (-y) == 0){ // �ȼ� ��ǥ y���� y�� ����� ���� ����ϵ��� ��
					scaling.push_back(map.at(i * wid + j));
				}
			}
		}
		for (int i = 0; i < hei/(-y); i++) {
			for (int j = 0; j < wid; j++) {
				for (int k = 0; k < x;k++) { // �ʺ� x��
					pic += scaling.at(i * wid + j);
				}
			}
			pic += '\n';
		}
	}

	else if (x < 0 && y > 0) { // �ʺ�� ���, ���̴� Ȯ��
		for (int i = 0; i < hei; i++) {
			for (int k = 0; k < y; k++) { // ���� y��
				for (int j = 0; j < wid; j++) {

					scaling.push_back(map.at(i * wid + j));

				}
			}
		}
		for (int i = 0; i < hei*y; i++) {
			for (int j = 0; j < wid; j++) {
				if (j % (-x) == 0) { // �ȼ� ��ǥ x���� x�� ����� ���� ����ϵ��� ��
					pic += scaling.at(i * wid + j);
				}
			}
			
			pic += '\n';
		}
	}

	else if (x < 0 && y < 0) { // ��� ���
		for (int i = 0; i < hei; i++) {
			for (int j = 0; j < wid; j++) {
				if (i % (-y) == 0) { // �ȼ� ��ǥ y���� y�� ����� ���� ����ϵ��� ��
					scaling.push_back(map.at(i * wid + j));
				}
			}
		}
		for (int i = 0; i < (hei/(-y)); i++) {
			for (int j = 0; j < wid; j++) {
				if (i % (-x) == 0) { // �ȼ� ��ǥ x���� x�� ����� ���� ����ϵ��� ��
					pic += scaling.at(i * wid + j);
				}
			}
			if (i % (-x) == 0) {
				pic += '\n';
			}
		}
	}
	return pic;
}