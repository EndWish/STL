//-----------------------------------------------------------------------------
//SAVE.CPP
//
// �Լ� save�� �����̸��� �Ѱ��ָ鰭�Ǹ� �����ϴ� 
// "2022�� 1�б� STL ��910 ��56 ��������.txt"�� ���ٿ� ����Ѵ�.
//
// 3. 3
//

#include <fstream>
#include <chrono>
#include <filesystem>
#include <vector>
#include <algorithm>
#include "save.h"

void save( std::string_view fname)
{
	// ���� ������ ����.
	std::ifstream in{ fname.data() };

	// �� ���ϵ� ����.
	std::ofstream out{ "2022�� 1�б� STL ��910 ��56 ��������.txt", std::ios::app };

	out << "\n\n";
	out << "//----------------------------------------------------------<���ο� ����>-------------------------------------------------------\n";

	// ������ ������ �̸��� ���Ͽ� ����Ѵ�
	out << "���� �̸� : " << fname << "\n";

	// ������ ������ ũ�⸦ ����Ѵ�(c++17)
	out << "����ũ��:" << std::filesystem::file_size(fname) << "\n";

	// ���� ��¥�� �ð��� ����Ѵ�.(c++20)
	auto time = floor<std::chrono::seconds>(std::chrono::system_clock::now());
	out << std::chrono::zoned_time("Asia/Seoul", time) << "\n";
	out << std::endl;


	// ���� ������ ������ �о� �� ���Ͽ� ���ٿ� ����.
	// 1. �����̳�(�ڷᱸ��) ������ ������ ���ͷ� �о�´�
	std::vector<char> v{ std::istreambuf_iterator<char>{in}, {} };

	// 2. �˰����� ����Ͽ� ���Ϳ� �ִ� ������ ���Ͽ� ����(copy �˰���)�Ѵ�.
	copy(v.begin(), v.end(), std::ostream_iterator<char>{out});

}