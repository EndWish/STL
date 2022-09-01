//-----------------------------------------------------------------------------
//STRING - STL 내부 동작을 관찰하려고 만든 자원을 관리하는 클래스
//		 - std::string 동작 대부분을 직접 구현하며 STL 동작방식을 이해
// 
// 2022.3.30							
//-----------------------------------------------------------------------------

#pragma once

#include <iostream>
#include <algorithm>

class STRING_iterator {
public:
	// 표준 반복자가 응답해야할 타입
	using iterator_category = std::random_access_iterator_tag;
	using value_type = char;
	using difference_type = std::ptrdiff_t;
	using pointer = char*;
	using reference = char&;

private:
	char* p;

public:
	STRING_iterator(char* p) : p{ p } { }

	difference_type operator-(const STRING_iterator& rhs) const {	//ptrdiff_t = long long을 포장한, 포인터의 차이 크기
		return p - rhs.p;
	}

	// 2022. 4. 28 sort가능하도록 연산자 추가
	auto operator<=>(const STRING_iterator& ) const = default;

	STRING_iterator& operator++() {
		++p;
		return *this;
	}

	STRING_iterator& operator--() {
		--p;
		return *this;
	}

	STRING_iterator operator+(difference_type d) const {
		return STRING_iterator{ p + d };
	}

	STRING_iterator operator-(difference_type d) const {
		return STRING_iterator{ p - d };
	}

	char& operator*() const {
		return *p;
	}

};

// 2022. 4. 27 STRING이 제공할 역방향 반복자
class STRING_reverse_iterator {
	char* p;

public:
	STRING_reverse_iterator(char* p) : p{ p } {}	//매개변수 이름을 _(언더바)로 시작하지말자

	STRING_reverse_iterator& operator++() {	//자기 자신이 변하기 때문에 const를 쓰면 안됨
		--p;
		return *this;
	}

	char& operator*() const {	//indirection 오퍼레이터 라고 부른다.
		return *(p - 1);	//reverse의 경우 p-1 번째를 리턴한다.
	}

	// <, >, <=, >=, ==, != (관계연산자, relational operator)
	// 관계연산자는 우주선연산자로 한번에 해결 - C++20
	// spaceshop operator(three-way comparison operator)
	auto operator<=>(const STRING_reverse_iterator& rhs) const = default;

	bool operator!=(const STRING_reverse_iterator& rhs) const {
		std::cout << "아마 이게 우선일껄" << "\n";
		return p != rhs.p;
	}
};

class STRING {
public:
	using iterator = STRING_iterator;
	using reverse_iterator = STRING_reverse_iterator;	//이름을 이렇게 바꿔서 쓰겠다.

private:
	size_t num;									//관리하는 자원소
	int id;										//생성 시 부여한 고유값									
	char* p;									//자원의 주소	// 메모리가 8바이트 단위로 할당해서 4(8)/8/4(8) 바이트 순으로 할경우 24바이트 할당됨(패딩!!). release에서 그러하다.
	static int gid;								//아이디 생성용	//static은 객체의 메모리와 상관없으므로 밖에서 초기화

public:
	STRING();
	STRING(const char* s);
	~STRING();

	STRING(const STRING& other);
	STRING& operator=(const STRING& other);

	// 2022. 4. 7 이동새성자/이동할당연산자
	STRING(STRING&& other) noexcept;	//noexcept : 예외를 던지지 않겠다.(안전함을 보장한다.)
	STRING& operator=(STRING&& other) noexcept;	

	STRING operator+(const STRING& rhs) const;

	// 2022. 4. 28 sort를 위해 default < 연산자 제공
	bool operator<(const STRING& rhs) const {
		return std::lexicographical_compare(begin(), end(), rhs.begin(), rhs.end());
	}

	// 2022. 5. 18 unordered_set이 요구하는 == 코딩
	bool operator==(const STRING rhs) const {
		return std::string(begin(), end()) == std::string(rhs.begin(), rhs.end());
	}

	// 2022. 4. 21 begin(), end() 제공
	iterator begin() const {
		return iterator{ p };
	}

	iterator end() const {
		return iterator{ p + num };
	}

	reverse_iterator rbegin() const {
		return reverse_iterator{ p + num };
	}

	reverse_iterator rend() const {
		return reverse_iterator{ p };
	}

	size_t getNum() const {
		return num;
	}

	void print(const char* s) const;

	friend std::ostream& operator<<(std::ostream&, const STRING&);
	// 2022. 4. 28 추가
	friend std::istream& operator>>(std::istream&, STRING&);
};


