//-----------------------------------------------------------------------------
//STRING - STL ���� ������ �����Ϸ��� ���� �ڿ��� �����ϴ� Ŭ����
//		 - std::string ���� ��κ��� ���� �����ϸ� STL ���۹���� ����
// 
// 2022.3.30							
//-----------------------------------------------------------------------------

#include<iostream>
#include "STRING.h"

bool ����{ false };						// �����޽��� ������ True
int STRING::gid{};						// class static 

STRING::STRING() : num{}, p{}, id{ ++gid }
{
	if (����)
		print("����Ʈ");
}

//,�� ���� ������ �Ҵ��Ҷ� ������ ������� �ʾƼ� p�� ���� �Ҵ��Ѵ�.
STRING::STRING(const char* s) : num{ strlen(s) }
{		//��Һ�ȯ : �޸�ũ�Ⱑ �۾����鼭 �����Ͱ� �۾����� �����Ƿ� size_t�� ���
	p = new char[num];
	id = ++gid;
	memcpy(p, s, num);	//memcpy�� ���DMA �� ����

	if (����)
		print("������(*)");

	// �����޽�Ƽ on
}

STRING::~STRING() 
{
	// �����޽�Ƽ on
	if (����) {
		print("�Ҹ���");
	}
	if (num) {
		delete[] p;
	}
}

STRING::STRING(const STRING& other) : id{ ++gid }, num{ other.num }
{
	p = new char[num];
	memcpy(p, other.p, num);
	if (����)
		print("�������");
}

STRING& STRING::operator=(const STRING& other)
{
	if (this == &other)
		return *this;

	if (num)
		delete[] p;

	num = other.num;
	p = new char[num];
	memcpy(p, other.p, num);

	if (����)
		print("�����Ҵ�");

}

// 2022. 4. 7 �̵�������/�̵��Ҵ翬����
STRING::STRING(STRING&& other) noexcept : id { ++gid }
{
	num = other.num;
	p = other.p;

	other.num = 0;
	other.p = nullptr;

	if (����) {
		print("�̵�����");
	}

}

STRING& STRING::operator=(STRING&& other) noexcept {
	if (this != &other) {
		if (num) {
			delete[] p;
		}

		num = other.num;
		p = other.p;

		other.num = 0;
		other.p = nullptr;
	}

	if (����) {
		print("�̵��Ҵ�");
	}

	return *this;
}

STRING STRING::operator+(const STRING& rhs) const
{
	STRING temp;	//�ӽð�ü�� ����� ������ ����
	temp.num = num + rhs.num;
	temp.p = new char[temp.num];

	memcpy(temp.p, p, num);
	memcpy(temp.p + num, rhs.p, rhs.num);
	return temp;
}

void STRING::print(const char* s) const
{
	std::cout << s << " [" << id << "] ��ü:" << this;
	if (num) {
		std::cout << " - �ڿ� : " << num << " �ּ� : " << (void*)p;	// ĳ���� �����ʹ°���� ������̶� ���ڿ��� �Էµȴ�.
	}
	else {
		std::cout << " - �ڿ�����";
	}
	std::cout << std::endl;
}

std::ostream& operator<<(std::ostream& os, const STRING& s)
{
	for (int i{}; i < s.num; ++i) {
		os << s.p[i];
	}
	return os;
}

// 2022. 4. 28 �߰�
std::istream& operator>>(std::istream& is, STRING& s)
{
	std::string str;
	is >> str;
	s = STRING(str.c_str());
	return is;
}
