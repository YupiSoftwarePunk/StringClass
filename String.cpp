#include "String.hpp"


// constructors

// Обычные конструкторы
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

// Конструктор копирования
String::String(const String& other)
{
	capacity_ = other.capacity_;
	for (int i = 0; i < capacity_; i++)
	{
		str_[i] = other.str_[i];
	}
}

// конструктор оператор присваивания копирования
String& String::operator=(const String& other)
{
	allocator_.deallocate(str_);
	capacity_ = other.capacity_;
	str_ = allocator_.allocate(capacity_);
	for (int i = 0; i < capacity_; i++)
	{
		std::swap(str_[i], other.str_[i]);
	}
	return *this;
}

// конструктор переноса
String::String(String&& other) noexcept
{
	str_ = nullptr;
	capacity_ = 0;
	
	std::swap(str_, other.str_);
	std::swap(capacity_, other.capacity_);

}

// конструктор оператор присваивания
String& String::operator=(String&& other)
{
	allocator_.deallocate(str_);
	capacity_ = other.size();
	str_ = other.str_;
	other.str_ = nullptr;
	return *this;
}



// destructor
String::~String()
{
	if (capacity_ > 0)
	{
		allocator_.deallocate(str_);
	}
}


// Оператор вывода
std::ostream& operator<<(std::ostream& out, const String& obj)
{
	if (obj.str_ == nullptr)
	{
		return out;
	}
	out << obj.str_;
	return out;
}

// Оператор ввода
std::istream& operator>>(std::istream& in, const String& obj)
{
	in >> obj;
	return in;
}
