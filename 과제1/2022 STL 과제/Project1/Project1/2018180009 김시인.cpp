#include <iostream>
#include <fstream>
#include <array>
#include <format>
#include <numeric>
#include <algorithm>

#include <time.h>	//여러가지 속도를 시험하기 위해 임시로 넣음

#define N 2'000'000

using namespace std;

class Player {
private:
	string name; // 이름, 길이[3, 15]
	int score; // 점수
	int id; // 아이디, 겹치는 아이디 있을 수 있음
	size_t num; // Free store에 확보한 바이트 갯수
	char* p; // 확보한 메모리의 시작번지

public:

	Player() : name{}, score{}, id{}, num{}, p{} {

	}

	~Player() {
		if (num)
			delete[] p;
	}

	const string& getNameRef() const {
		return name;
	}

	int getScore() const {
		return score;
	}

	int getID() const {
		return id;
	}

	size_t getNum() const {
		return num;
	}

	void write(ostream& os) {
		os.write((char*)this, sizeof(Player));
		os.write((char*)p, num);
	}

	void read(istream& is) {
		is.read((char*)this, sizeof(Player));
		p = new char[num];
		is.read((char*)p, sizeof(char) * num);
	}

	void printInfo() {
		cout << format("이름 : {0:<20} , 아이디 : {1:<10} , 점수 : {2:<10}, 자원수 : {3:<5} \n", name, id, score, num);
	}

};

array<Player, N> players;
array<Player*, N> playersSortedByID, playersSortedByName, playersSortedByScore;

int main(void) {

	ifstream in{ "2022 STL 과제 파일" , ios::binary };

	for (Player& player : players) {
		player.read(in);
	}

	// 1. 파일을 읽어 제일 마지막 객체의 정보를 다음과 같은 형식으로 출력하라.
	// 이름:jhxubuhgldh , 아이디:476109 , 점수:435832437, 자원수:969
	players.back().printInfo();

	// 2. 모든 Player의 점수 평균값을 계산하여 출력하라
	long long sum = accumulate(players.begin(), players.end(), 0LL, [](long long sum,const Player& p2) {return sum + p2.getScore(); });
	double average = (double)sum / players.size();
	cout << format("합계:{0}, 평균{1}\n", sum, average);

	// 3. 확보한 메모리 바이트 수가 999인 Player 객체를 모두 찾아“바이트 수 999”라는 이름인 파일에 복사하라.
	int saveCount = 0;
	ofstream out{ "바이트 수 999", ios::binary };
	for (auto it = players.begin(); it != players.end(); ++it) {
		if (it->getNum() == 999) {
			it->write(out);
			saveCount++;
		}
	}
	cout << "저장한 객체의 개수:" << saveCount << "\n";

	// 4. id를 입력받아 존재하는 id라면 다음 내용을 한 번에 화면 출력하라.
	transform(players.begin(), players.end(), playersSortedByID.begin(), [](Player& player) { return &player; });
	playersSortedByName = playersSortedByID;	// memcpy와 시간을 비교해본바 큰 차이 없음 (내부적으로도 memcpy를 쎃을 거라 예상)
	playersSortedByScore = playersSortedByID;

	sort(playersSortedByID.begin(), playersSortedByID.end(), [](Player* a, Player* b) { return a->getID() < b->getID(); });
	sort(playersSortedByName.begin(), playersSortedByName.end(), [](Player* a, Player* b) { return a->getNameRef() < b->getNameRef(); });
	sort(playersSortedByScore.begin(), playersSortedByScore.end(), [](Player* a, Player* b) { return a->getScore() < b->getScore(); });

	cout << endl;
	while (true)
	{
		int inputID;
		cout << "id를 입력하세요 : ";
		cin >> inputID;

		//임시탈출
		if (cin.fail()) {
			cout << "잘못된 id입니다.\n";
			cin.clear();
			cin.ignore(100, '\n');
			cout << endl << endl;
			continue;
		}

		if (inputID == -1) {
			break;
		}

		// id로 정렬된 Player 출력
		auto sIDIt = lower_bound(playersSortedByID.cbegin(), playersSortedByID.cend(), inputID, [](const Player* p, int id) { return p->getID() < id; });	// key값중 가장 왼쪽값
		auto eIDIt = upper_bound(playersSortedByID.cbegin(), playersSortedByID.cend(), inputID, [](int id, const Player* p) { return id < p->getID(); });	// key값을 초과하는 가장왼쪽값
		if (sIDIt == eIDIt) {
			cout << "해당하는 Player가 없습니다.\n";
			cout << "근접한 플레이어의 id는 ";
			if (sIDIt != playersSortedByID.begin())	// 입력한 id보다 작은 인접한 값 출력
				cout << (*(sIDIt - 1))->getID() << " ";
			if (sIDIt != playersSortedByID.end())		// 입력한 id보다 큰 인접한 값 출력
				cout << (*sIDIt)->getID() << " ";
			cout << "입니다." << endl << endl;

			continue;
		}

		Player* targetPlayer = *sIDIt;
		
		if (sIDIt != playersSortedByID.begin())
			--sIDIt;

		if (eIDIt != playersSortedByID.end())
			++eIDIt;

		cout << "# id로 정렬되었을 때:\n";
		while (sIDIt != eIDIt) {
			(*sIDIt)->printInfo();
			++sIDIt;
		}

		// name으로 정렬된 Player출력
		cout << "# name으로 정렬되었을 때:\n";
		auto nameIt = lower_bound(playersSortedByName.cbegin(), playersSortedByName.cend(), targetPlayer, [](const Player* p, const Player* target) { return p->getNameRef() < target->getNameRef(); });	// key값중 가장 왼쪽값
		if (nameIt != playersSortedByName.begin())
			(*(nameIt - 1))->printInfo();
		(*nameIt)->printInfo();
		if ((nameIt + 1) != playersSortedByName.end())
			(*(nameIt + 1))->printInfo();

		// score으로 정렬된 Player출력
		cout << "# score로 정렬되었을 때:\n";
		auto scoreIt = lower_bound(playersSortedByScore.cbegin(), playersSortedByScore.cend(), targetPlayer, [](const Player* p, const Player* target) { return p->getScore() < target->getScore(); });	// key값중 가장 왼쪽값
		if (scoreIt != playersSortedByScore.begin())
			(*(scoreIt - 1))->printInfo();
		(*scoreIt)->printInfo();
		if ((scoreIt + 1) != playersSortedByScore.end())
			(*(scoreIt + 1))->printInfo();

		cout << endl;
	}

}


