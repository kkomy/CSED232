#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <cstdint>
#include <cassert>
#include "SharedPtr.h"

///////////////////////////////////////////////////////////////////////////
// RGB pixel type
//    Usage:
//      - RGB<float> rgb(0.5f, 0.1f, 0.3f);
//        rgb[0] = 0.2f; // or equivalently, rgb.r = 0.2f;
template<typename ValType>
struct RGB
{
	union {
		ValType data[3];
		struct {
			ValType r, g, b;
		};
	};

	RGB() {}
	RGB(ValType r_, ValType g_, ValType b_) : r(r_), g(g_), b(b_) {}

	ValType operator[](int idx) const { return data[idx]; }
	ValType& operator[](int idx) { return data[idx]; }
};

typedef RGB<uint8_t>	RGB8b;
typedef RGB<float>		RGBf;


///////////////////////////////////////////////////////////////////////////
// Image class template
//
template<typename PixelType>
class Image
{
private:
	// ======= ADD CODE HERE IF NEEDED =========
	SharedArray<PixelType> m_buff; // rgb 데이터값을 저장할 배열
	size_t m_width; // 이미지 너비I
	size_t m_height; // 이미지 높이


public:
	////////////////////////////////////////////
	// constructors & destructor
	////////////////////////////////////////////
	Image() { // default constructor
		m_width = 0;
		m_height = 0;
	}
	Image(size_t _width, size_t _height) { // 이미지 크기만큼 메모리할당
		m_width = _width;
		m_height = _height;
		m_buff = SharedArray<PixelType>(new PixelType[_width * _height]); // 너비 x 높이만큼의 배열크기 할당

	}
	Image(size_t _width, size_t _height, const PixelType& val) { // 할당 후 val로 초기화
		m_width = _width;
		m_height = _height;
		m_buff = SharedArray<PixelType>(new PixelType[_width * _height]);

		for (int i = 0; i < _width * _height; i++) {
			m_buff[i] = val; // val로 초기화
		} // initialization

	}
	Image(const Image<PixelType>& img) { //copy constructor(deep copy)
		m_width = img.m_width; // 너비 복사
		m_height = img.m_height; // 높이 복사
		m_buff = SharedArray<PixelType>(new PixelType[m_width * m_height]); // 복사를 위해 이미지크기만큼 메모리할당 => deep copy

		for (int i = 0; i < m_width * m_height; i++) {
			m_buff[i] = img.m_buff[i]; // 복사
		} // initialization
	}
	~Image() {
	}
	// ======= ADD CODE HERE IF NEEDED =========

	////////////////////////////////////////////
	// assignment operator
	////////////////////////////////////////////
	Image& operator=(const Image& img) { //대입연산자 (deep copy)
		m_width = img.m_width; // 너비복사
		m_height = img.m_height; // 높이 복사
		m_buff = SharedArray<PixelType>(new PixelType[m_width * m_height]); // 메모리 할당
		for (int i = 0; i < m_width * m_height; i++) {
			m_buff[i] = img.m_buff[i]; // 복사 deep copy
		}
		return *this;
	}
	// ======= ADD CODE HERE IF NEEDED =========

	////////////////////////////////////////////
	// element access operators
	////////////////////////////////////////////
	PixelType* operator[](int y) { return &m_buff[y * m_width]; }
	const PixelType* operator[](int y) const { return &m_buff[y * m_width]; }

	////////////////////////////////////////////
	// other methods
	////////////////////////////////////////////
	//   - width(), height()
	size_t width() const { // private member인 width 값 리턴
		return m_width;
	}
	size_t height() const { // private member인 height 값 리턴
		return m_height;
	}

	// ======= ADD CODE HERE IF NEEDED =========
};

// ======= ADD CODE HERE IF NEEDED =========


// Miscellaneous functions
void convert_pixel_type(const Image<RGB8b>& src, Image<RGBf>& dst);
void convert_pixel_type(const Image<RGBf>& src, Image<RGB8b>& dst);

bool load_bmp(const char* path, Image<RGB8b>& img);
bool save_bmp(const char* path, const Image<RGB8b>& img);

#endif
