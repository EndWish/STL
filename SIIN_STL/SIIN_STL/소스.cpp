//---------------------------------<금일 강의 목표>----------------------------
// 2022년 1학기 STL	6.15	수910목56 (최종정리)
// Generic Programming의 개념을 설명할 수 있다.   : 자료형에 무관하게 코딩할 수 있는 기법
// c++에서 템플릿을 이용하여 클래스와 함수를 만들 수 있다.
// 이렇게 만든 클래스와 함수는 무슨 자료형이 넘겨지더라도 문제가 없다.
// 
// C++의 특징 : 밑바닥까지 손댈 수 있다.(포인터)
// 
// range for 는 begin와 end가 정의 되어 있어야한다.
// move, &, && = l-value 래퍼런스, r-value 래퍼런스, 이동연사자
// 
// r-value 래퍼런스 : move문법을 완성하기 위해나옴, 
// const : 값을 바꾸지 않는 다는 것을 명시하는 역할
// lambda : 함수호출을 오버로딩한 이름없는 클래스
// concept : 템플릿에 제약을 주기위한것
// range : 컨셉을 이용하여 함수를 다시 정의한것
// view : 
// 
// 스마트 포인터 : 포인터를 한번더 감싸서 메모리 해제를 알아서 해주는 객체
// 
// 호출가능 타입 : operator()() ,  lambda, 함수포인터
// 
// STRING을 만들어 가며 STL의 장동원리를 이해 하였다 : 
//      생성자, 소멸자, 복사생성, 복사 할당, 이동생성, 이동할당
//      begin, end를 제공하는 반복자를 만들어봄 (iterator의 조건이 있다, 특질:어떤 특성들을 가지고 있나.)
// 
// 컨테이너의 종류 : sequence 컨테이너, associative 컨테이너, Unordered associative 컨테이너
// 반복자의 종류 : cotiguous, random_access, bidrection, forward, input, output
// 알고리즘 작동방식을 설명할 수 있다 : begin, end로 접근하여 원소를 수정하지 않는 알고리즘, 원소를 수정하는 알고리즘, 정렬하는 알고리즘이 있다.
// 
// 직접 작성한 for loop 보다 알고리즘 함수를 사용하는 것이 좋다는 것을 안다.
// C++20의 concept으로 재작성된 constrained 알고리즘 함수가 있다. : 타입에 따라 적절한 함수를 컴파일 타임에 선택할 수 있어 에러를 줄일 수 있다.
// C++20의 range/view concept를 사용하면 함수를 쉽게 조합하고 projection을 통해 좀더 편하게 코딩가능
// 
// &와 const를 잘 이해하고 쓰면 어디 가서도 기본은 할 수 있다.
// 
// C++ core guidelines 참고
// modoocode.com 참고
// 
//-----------------------------------------------------------------------------

#include <iostream>
#include "save.h"

using namespace std;

//---------------------------
int main()
//---------------------------
{
    //save("소스.cpp");
}