//-----------------------------------------------------------------------------
//SAVE.CPP
//
// 함수 save에 파일이름을 넘겨주면강의를 저장하는 
// "2022년 1학기 STL 수910 목56 강의저장.txt"에 덧붙여 기록한다.
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
	// 읽을 파일을 연다.
	std::ifstream in{ fname.data() };

	// 쓸 파일도 연다.
	std::ofstream out{ "2022년 1학기 STL 수910 목56 강의저장.txt", std::ios::app };

	out << "\n\n";
	out << "//----------------------------------------------------------<새로운 저장>-------------------------------------------------------\n";

	// 저장할 파일의 이름을 파일에 출력한다
	out << "파일 이름 : " << fname << "\n";

	// 저장할 파일의 크기를 출력한다(c++17)
	out << "파일크기:" << std::filesystem::file_size(fname) << "\n";

	// 현재 날짜와 시간을 출력한다.(c++20)
	auto time = floor<std::chrono::seconds>(std::chrono::system_clock::now());
	out << std::chrono::zoned_time("Asia/Seoul", time) << "\n";
	out << std::endl;


	// 읽을 파일의 정보를 읽어 쓸 파일에 덧붙여 쓴다.
	// 1. 컨테이너(자료구조) 파일의 내용을 벡터로 읽어온다
	std::vector<char> v{ std::istreambuf_iterator<char>{in}, {} };

	// 2. 알고리즘을 사용하여 벡터에 있는 내용을 파일에 복사(copy 알고리즘)한다.
	copy(v.begin(), v.end(), std::ostream_iterator<char>{out});

}