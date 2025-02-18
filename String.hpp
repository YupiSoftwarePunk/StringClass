#pragma once


#pragma once

#include <iostream>
#include <stdlib.h>

class String
{
public:

	String();
	explicit String(int num);
	String(char* str);

	// Правило 3
	~String(); // деструктор
	String(const String& other);   // Конструктор копирования
	String& operator=(const String& other);  // оператор присваивания копирования


	// Правило 5
	// Если в вашем коде возникает конструктор переносом или оператор присваивания переноса, то нужно реализовать их оба
	// Конструктор переноса - данный конструтор физически не может вызвать исключений
	// Элементы правила 5 называются  -  move семантикой
	String(String&& other)noexcept;     // конструктор переноса
	String& operator=(String&& other);  //  ссылка на скороживущий объект (двойная ссылка)   оператор присваивания

	void reverse(int new_capacity);
	void shrink_to_fit();
	void clean();
	bool empty()const;

	int capcity()const;
	int size()const;

	String& operator+= (const String& other);
	String& operator+= (char ch);
	friend String& operator+ (const String& lsd, const String& rsd);
	friend String& operator+ (const String& lsd, char ch);
	friend String& operator+ (char ch, const String& rsd);


	//При перегрузке опараторов нельзя менять поведение оператора, если оно действует также как встроенный оператор
	char& operator[](int)noexcept;   // обязательство не вызывать исключение в блоке кода
	const char& operator[](int i)const noexcept;

	char& at(int i);
	const char& at(int i)const;


	//friend bool operator<<(std::ostream& out, const String& rsd);
	//friend bool operator>>(std::istream& out, const String& rsd);


	friend bool operator<(const String& lsd, const String& rsd);
	friend bool operator>(const String& lsd, const String& rsd);
	friend bool operator<=(const String& lsd, const String& rsd);
	friend bool operator>=(const String& lsd, const String& rsd);
	friend bool operator!=(const String& lsd, const String& rsd);
	friend bool operator==(const String& lsd, const String& rsd);

	char* data();
	const char* c_str() const;

	class iterator {};
	class const_iterator {};
	class right_iterator {};
	class const_right_iterator {};

	iterator begin();
	iterator end();

	right_iterator rbegin();
	right_iterator rend();

	const_iterator cend()const;
	const_iterator cbegin()const;

	const_right_iterator crbegin()const;
	const_right_iterator crend()const;

	void insert(iterator& obj, char ch);
	void emplace(iterator& obj, char ch);

	void push_back(char ch);
	void emplace_back(char ch);


	// Операторы ввода и вывода
	// вывод
	friend std::ostream& operator<<(std::ostream& out, const String& obj);
	// ввод
	friend std::istream& operator>>(std::istream& in, const String& obj);

private:
	struct {
		char* allocate(int size)
		{
			char(*place) = new char[size];
			return place;
		}
		void deallocate(char* place)
		{
			delete[] place;
		}
		void reallocate(char*& place, int old_size, int new_size)
		{
			char *place2 = new char[new_size];
			for (int i = 0; i < new_size; i++)
			{
				place2[i] = place[i];
			}
			delete[] place;
			place = place2;
			
		}
	
	}allocator_;

	char* str_;
	int capacity_;
};
