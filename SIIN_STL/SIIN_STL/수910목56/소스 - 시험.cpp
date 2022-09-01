#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

// [프로그램 환경] Release, x64, 프로젝트 속성 C++ 언어: 미리 보기 - 최신 C++ 초안의 기능(/std:c++latest)

//---------
int main( )
//---------
{
    ifstream in{ "이상한 나라의 앨리스.txt" };

    vector<string> v;

    // [문제 1] 파일 "이상한 나라의 앨리스.txt"에 있는 모든 단어를 읽어 컨테이너 v에 저장하라.
    // 모두 몇 개의 단어를 읽었는지 화면에 출력하고 출력결과를 답지에도 적어라.   (15, 5)                             
    // (주의) v는 이미 생성되어있다.
     

  
    // [문제 2]  v에서 "rabbit" 이라는 단어는 모두 몇 개인가? 
    // 몇 개인지 화면에 출력하고 답지에 출력된 개수도 적어라.                    (20, 5)
    // (주의) rabbit은 대소문자를 구분하지 않는다 
    // (예) rabbit Rabbit RABBIT Rabbit-Hole - 여기에서 rabbit은 3개이다.
   


    // 다음과 같이 v를 단어사전으로 만들었다.
  
    sort( v.begin( ), v.end( ) );
    v.erase( unique( v.begin( ), v.end( ) ), v.end( ) );
    cout << "사전으로 만든 v의 단어 수 - " << v.size( ) << endl;
    // (출력) 사전으로 만든 v의 단어 수 - 5295


    // [문제 3] 사전을 단어의 길이 기준 오름차순으로 정렬하라.
    // 사전의 첫 단어와 마지막 단어를 화면에 출력하고 답안지에도 적어라. 	(15, 5)				
    // (주의) 길이가 같은 단어들 끼리는 오름차순으로 정렬되어야 한다.
    // (참고) 다음은 문제를 해결한 후 2001번째 부터 10개 단어를 출력한 것이다.
    // '--you 'After 'Begin 'Boots 'Bring 'Can't 'Come, 'DRINK 'Dear, 'Don't




    // "단어들.txt"를 words에 저장한다.
    ifstream in2{ "단어들.txt" };
    vector<string> words{ istream_iterator<string>{in2}, {} };
    cout << "단어들.txt - " << words.size( ) << endl;
    // (출력) 단어들.txt - 369882

    vector<string> v2;              // v의 단어가 "단어들.txt"에 있는 단어라면 여기에 저장한다.

    // [문제 4] v에 있는 단어 중에서 "단어들.txt"에 있는 단어를 찾아 v2에 저장하라.              
    // v2에 모두 몇 단어가 있는지 출력하고 답지에도 써라.  (20, 5)




    // [문제 5] 다음과 표준 알고리즘함수 copy를 호출하면 v2의 모든 단어가 역순으로 바뀐다.
    // 필요한 코딩을 추가하라.                                                (40)
    // (예) v2의 단어가 다음과 같다고 하자.    Alice was beginning to 
    // copy 호출 후에는 다음과 같이 바뀐다.    ecilA saw gninnigeb ot

    copy( v2.begin( ), v2.end( ), REV(v2.begin()) );
}
