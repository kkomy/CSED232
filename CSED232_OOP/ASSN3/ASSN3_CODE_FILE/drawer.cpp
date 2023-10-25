#include"drawer.h"
#include<iostream>

drawer::drawer() {
	wid = 0;
	hei = 0;
	map = {};
}

drawer::~drawer() {
	delete art; // main 함수에서 할당되었던 art 할당 해제
}

drawer::drawer(artist* a) {
	art = a; // artist 타입 object 저장
	wid = a->call_width(); // 그림 너비 저장
	hei = a->call_height(); // 그림 높이 저장
	for (int i = 0; i < a->call_height(); i++) {
		for (int j = 0; j < a->call_width(); j++) {
			map.push_back(a->mapper(j, i)); // mapper 함수를 통해 문자 변환
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
			map.push_back(a->mapper(j, i));// mapper 함수를 통해 문자 변환
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
			map.push_back(a->mapper(j, i));// mapper 함수를 통해 문자 변환
		}
	}
}

std::string drawer::draw() {
	std::string pic;
	for (int i = 0; i < hei; i++) {
		for (int j = 0; j < wid; j++) {
			pic += map.at(i * wid + j);
		}
		pic += '\n'; // 다음 줄을 표현할 때마다 줄바꿈
	}
	return pic;
}

std::string downsample::draw() {
	std::string pic;

	for (int i = 0; i < hei; i++) {
		for (int j = 0; j < wid; j++) {
			if (i % 2 == 0 && j % 2 == 0) { // 가로 세로 각각 절반씩 축소하므로, 좌표값이 모두 짝수일 때의 픽셀만을 출력
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
		for (int k = 0; k < 2; k++) { // 세로 두배
			for (int j = 0; j < wid; j++) {
				pic += map.at(i * wid + j); // 가로 두배
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
			map.push_back(a->mapper(j, i));// mapper 함수를 통해 문자 변환
		}
	}
}

std::string scale::draw() {
	std::vector<char> scaling;
	std::string pic;
	if (x > 0 && y > 0) { // 너비 높이 둘다 확대일 때
		for (int i = 0; i < hei; i++) { 
			for (int m = 0; m < y; m++) { // 높이 y배
				for (int j = 0; j < wid; j++) {
					for (int k = 0; k < x; k++) { // 너비 x배
						pic += map.at(i * wid + j);
					}
				}
				pic += '\n';
			}
		}
	}
	else if (x > 0 && y < 0) { // 너비는 확대, 높이는 축소
		for (int i = 0; i < hei; i++) {
			for (int j = 0; j < wid; j++) {
				if(i % (-y) == 0){ // 픽셀 좌표 y축이 y의 배수일 때만 출력하도록 함
					scaling.push_back(map.at(i * wid + j));
				}
			}
		}
		for (int i = 0; i < hei/(-y); i++) {
			for (int j = 0; j < wid; j++) {
				for (int k = 0; k < x;k++) { // 너비 x배
					pic += scaling.at(i * wid + j);
				}
			}
			pic += '\n';
		}
	}

	else if (x < 0 && y > 0) { // 너비는 축소, 높이는 확대
		for (int i = 0; i < hei; i++) {
			for (int k = 0; k < y; k++) { // 높이 y배
				for (int j = 0; j < wid; j++) {

					scaling.push_back(map.at(i * wid + j));

				}
			}
		}
		for (int i = 0; i < hei*y; i++) {
			for (int j = 0; j < wid; j++) {
				if (j % (-x) == 0) { // 픽셀 좌표 x축이 x의 배수일 때만 출력하도록 함
					pic += scaling.at(i * wid + j);
				}
			}
			
			pic += '\n';
		}
	}

	else if (x < 0 && y < 0) { // 모두 축소
		for (int i = 0; i < hei; i++) {
			for (int j = 0; j < wid; j++) {
				if (i % (-y) == 0) { // 픽셀 좌표 y축이 y의 배수일 때만 출력하도록 함
					scaling.push_back(map.at(i * wid + j));
				}
			}
		}
		for (int i = 0; i < (hei/(-y)); i++) {
			for (int j = 0; j < wid; j++) {
				if (i % (-x) == 0) { // 픽셀 좌표 x축이 x의 배수일 때만 출력하도록 함
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