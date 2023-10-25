#ifndef SHAREDPTR_H
#define SHAREDPTR_H

#include <iostream>
#include <cassert>

template<typename ObjectType>
void Deallocator(ObjectType* ptr)
{
	std::cout << "Dealloc Object" << std::endl;
	delete ptr;
}

template<typename ObjectType>
void ArrayDeallocator(ObjectType* ptr)
{
	std::cout << "Dealloc Array" << std::endl;
	delete[] ptr;
}

template<typename T>
using DeallocatorFuncType = void(T*);

// SharedPtr
template<typename ObjectType, DeallocatorFuncType<ObjectType> Dealloc = Deallocator<ObjectType> >
class SharedPtr
{
private:
	ObjectType* m_object;
	int* m_ref_counter;

	// ======= ADD CODE HERE IF NEEDED =========

public:
	////////////////////////////////////////////
	// Constructors & destructor
	SharedPtr() { // SharedPtr 생성 : SharedPtr<MyClass> ptr;
		m_object = nullptr;
		m_ref_counter = nullptr;
	}
	explicit SharedPtr(ObjectType* ptr) { // SharedPtr 생성 :SharedPtr<MyClass> ptr(new MyClass()); ptr = new myclass()와 같이 자동 형변환을 막기위해 explicit
		m_object = ptr;
		m_ref_counter = new int(0);
		(*m_ref_counter)++;
	}
	SharedPtr(const SharedPtr& ptr) { // SharedPtr 생성 : SharedPtr<MyClass> ptr2(ptr); 
		m_object = ptr.m_object;
		m_ref_counter = ptr.m_ref_counter;
		if (m_ref_counter != nullptr) { // nullptr이 아닌 m_ref_counter를 참조할 때 counter ++
			(*m_ref_counter)++;
		}

	}

	~SharedPtr() { // destructor
		if (m_ref_counter != nullptr) {
			(*m_ref_counter)--; // 참조 counter--
			if ((*m_ref_counter) == 0) {// 아무도 참조하지 않는다면 -> 더이상 사용x
				Dealloc(m_object); // 할당해제
				delete m_ref_counter;
			}
		}
	}
	////////////////////////////////////////////


		// ======= ADD CODE HERE IF NEEDED =========

		////////////////////////////////////////////
		// Assignment operator
	SharedPtr& operator=(const SharedPtr& mtr) { // 대입연산 : ptr2 = ptr
		if (m_ref_counter != nullptr) { // 만약 대입할 포인터가 nullptr이 아니면, 기존의 참조하던 포인터에 대한 정보는 없애야한다.
			(*m_ref_counter)--; // 기존 참조 포인터에대해 이제 더이상 참조 x
			if ((*m_ref_counter) == 0) {
				if (m_object != nullptr) {
					Dealloc(m_object); // 할당해제
					delete m_ref_counter;
				}
			}
		}

		m_object = mtr.m_object; // 참조
		m_ref_counter = mtr.m_ref_counter;
		if (m_ref_counter != nullptr) {
			(*m_ref_counter)++;
		}
		return *this;
	}

	////////////////////////////////////////////

	// ======= ADD CODE HERE IF NEEDED =========

	////////////////////////////////////////////
	// Pointer operators
	////////////////////////////////////////////
	// operator->
	ObjectType* operator ->() { return m_object; } // -> operator
	const ObjectType* operator ->() const { return m_object; }
	// operator*
	ObjectType& operator *() { return *m_object; } // * operator
	const ObjectType& operator *() const { return *m_object; }

	// ======= ADD CODE HERE IF NEEDED =========

	////////////////////////////////////////////
	// Array element access operators
	////////////////////////////////////////////
	// operator[]
	ObjectType& operator[](int i) { return m_object[i]; } // [] operator

	// ======= ADD CODE HERE IF NEEDED =========

	////////////////////////////////////////////
	// Array element access operators
	////////////////////////////////////////////
	// operator[]
	const ObjectType& operator[](int i) const { return m_object[i]; }

	////////////////////////////////////////////
	// Type casting operators
	////////////////////////////////////////////
	// operator ObjectType const*() const
	// operator ObjectType*()
	operator ObjectType* () const { //일반포인터로 형변환
		return m_object;
	}
	operator ObjectType const* () const {
		return m_object;
	}

	// ======= ADD CODE HERE IF NEEDED =========
};

template<typename T>
using SharedArray = SharedPtr<T, ArrayDeallocator<T> >;

#endif
