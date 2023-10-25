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
	SharedPtr() { // SharedPtr ���� : SharedPtr<MyClass> ptr;
		m_object = nullptr;
		m_ref_counter = nullptr;
	}
	explicit SharedPtr(ObjectType* ptr) { // SharedPtr ���� :SharedPtr<MyClass> ptr(new MyClass()); ptr = new myclass()�� ���� �ڵ� ����ȯ�� �������� explicit
		m_object = ptr;
		m_ref_counter = new int(0);
		(*m_ref_counter)++;
	}
	SharedPtr(const SharedPtr& ptr) { // SharedPtr ���� : SharedPtr<MyClass> ptr2(ptr); 
		m_object = ptr.m_object;
		m_ref_counter = ptr.m_ref_counter;
		if (m_ref_counter != nullptr) { // nullptr�� �ƴ� m_ref_counter�� ������ �� counter ++
			(*m_ref_counter)++;
		}

	}

	~SharedPtr() { // destructor
		if (m_ref_counter != nullptr) {
			(*m_ref_counter)--; // ���� counter--
			if ((*m_ref_counter) == 0) {// �ƹ��� �������� �ʴ´ٸ� -> ���̻� ���x
				Dealloc(m_object); // �Ҵ�����
				delete m_ref_counter;
			}
		}
	}
	////////////////////////////////////////////


		// ======= ADD CODE HERE IF NEEDED =========

		////////////////////////////////////////////
		// Assignment operator
	SharedPtr& operator=(const SharedPtr& mtr) { // ���Կ��� : ptr2 = ptr
		if (m_ref_counter != nullptr) { // ���� ������ �����Ͱ� nullptr�� �ƴϸ�, ������ �����ϴ� �����Ϳ� ���� ������ ���־��Ѵ�.
			(*m_ref_counter)--; // ���� ���� �����Ϳ����� ���� ���̻� ���� x
			if ((*m_ref_counter) == 0) {
				if (m_object != nullptr) {
					Dealloc(m_object); // �Ҵ�����
					delete m_ref_counter;
				}
			}
		}

		m_object = mtr.m_object; // ����
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
	operator ObjectType* () const { //�Ϲ������ͷ� ����ȯ
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
