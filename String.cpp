#include "String.hpp"


// constructors

// ������� ������������
String::String() :String(0) {}

String::String(int num): capacity_(num)
{
	capacity_ = num;
	str_ = allocator_.allocate(capacity_);
}

String::String(char* str): str_(str)
{
	capacity_ = strlen(str);
	str_ = allocator_.allocate(capacity_);
	memcpy(str_, str, capacity_);
}

// ����������� �����������
String::String(const String& other)
{
	capacity_ = other.capacity_;
	for (int i = 0; i < capacity_; i++)
	{
		str_[i] = other.str_[i];
	}
}

// �������� ������������ �����������
String& String::operator=(const String& other)
{
	for (int i = 0; i < capacity_; i++)
	{
		std::swap(str_[i], other.str_[i]);
	}
	//std::swap(capacity_, other.capacity_);
	return 0;
}

// ����������� ��������
String::String(String&& other) noexcept
{
	str_ = nullptr;
	capacity_ = 0;
	
	std::swap(str_, other.str_);
	std::swap(capacity_, other.capacity_);

}



// destructor
String::~String()
{
	if (capacity_ > 0)
	{
		allocator_.deallocate(str_);
	}
}
