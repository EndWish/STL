#include <iostream>
#include <fstream>
#include <array>
#include <format>
#include <numeric>
#include <algorithm>

#include <time.h>	//�������� �ӵ��� �����ϱ� ���� �ӽ÷� ����

#define N 2'000'000

using namespace std;

class Player {
private:
	string name; // �̸�, ����[3, 15]
	int score; // ����
	int id; // ���̵�, ��ġ�� ���̵� ���� �� ����
	size_t num; // Free store�� Ȯ���� ����Ʈ ����
	char* p; // Ȯ���� �޸��� ���۹���

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
		cout << format("�̸� : {0:<20} , ���̵� : {1:<10} , ���� : {2:<10}, �ڿ��� : {3:<5} \n", name, id, score, num);
	}

};

array<Player, N> players;
array<Player*, N> playersSortedByID, playersSortedByName, playersSortedByScore;

int main(void) {

	ifstream in{ "2022 STL ���� ����" , ios::binary };

	for (Player& player : players) {
		player.read(in);
	}

	// 1. ������ �о� ���� ������ ��ü�� ������ ������ ���� �������� ����϶�.
	// �̸�:jhxubuhgldh , ���̵�:476109 , ����:435832437, �ڿ���:969
	players.back().printInfo();

	// 2. ��� Player�� ���� ��հ��� ����Ͽ� ����϶�
	long long sum = accumulate(players.begin(), players.end(), 0LL, [](long long sum,const Player& p2) {return sum + p2.getScore(); });
	double average = (double)sum / players.size();
	cout << format("�հ�:{0}, ���{1}\n", sum, average);

	// 3. Ȯ���� �޸� ����Ʈ ���� 999�� Player ��ü�� ��� ã�ơ�����Ʈ �� 999����� �̸��� ���Ͽ� �����϶�.
	int saveCount = 0;
	ofstream out{ "����Ʈ �� 999", ios::binary };
	for (auto it = players.begin(); it != players.end(); ++it) {
		if (it->getNum() == 999) {
			it->write(out);
			saveCount++;
		}
	}
	cout << "������ ��ü�� ����:" << saveCount << "\n";

	// 4. id�� �Է¹޾� �����ϴ� id��� ���� ������ �� ���� ȭ�� ����϶�.
	transform(players.begin(), players.end(), playersSortedByID.begin(), [](Player& player) { return &player; });
	playersSortedByName = playersSortedByID;	// memcpy�� �ð��� ���غ��� ū ���� ���� (���������ε� memcpy�� ���� �Ŷ� ����)
	playersSortedByScore = playersSortedByID;

	sort(playersSortedByID.begin(), playersSortedByID.end(), [](Player* a, Player* b) { return a->getID() < b->getID(); });
	sort(playersSortedByName.begin(), playersSortedByName.end(), [](Player* a, Player* b) { return a->getNameRef() < b->getNameRef(); });
	sort(playersSortedByScore.begin(), playersSortedByScore.end(), [](Player* a, Player* b) { return a->getScore() < b->getScore(); });

	cout << endl;
	while (true)
	{
		int inputID;
		cout << "id�� �Է��ϼ��� : ";
		cin >> inputID;

		//�ӽ�Ż��
		if (cin.fail()) {
			cout << "�߸��� id�Դϴ�.\n";
			cin.clear();
			cin.ignore(100, '\n');
			cout << endl << endl;
			continue;
		}

		if (inputID == -1) {
			break;
		}

		// id�� ���ĵ� Player ���
		auto sIDIt = lower_bound(playersSortedByID.cbegin(), playersSortedByID.cend(), inputID, [](const Player* p, int id) { return p->getID() < id; });	// key���� ���� ���ʰ�
		auto eIDIt = upper_bound(playersSortedByID.cbegin(), playersSortedByID.cend(), inputID, [](int id, const Player* p) { return id < p->getID(); });	// key���� �ʰ��ϴ� ������ʰ�
		if (sIDIt == eIDIt) {
			cout << "�ش��ϴ� Player�� �����ϴ�.\n";
			cout << "������ �÷��̾��� id�� ";
			if (sIDIt != playersSortedByID.begin())	// �Է��� id���� ���� ������ �� ���
				cout << (*(sIDIt - 1))->getID() << " ";
			if (sIDIt != playersSortedByID.end())		// �Է��� id���� ū ������ �� ���
				cout << (*sIDIt)->getID() << " ";
			cout << "�Դϴ�." << endl << endl;

			continue;
		}

		Player* targetPlayer = *sIDIt;
		
		if (sIDIt != playersSortedByID.begin())
			--sIDIt;

		if (eIDIt != playersSortedByID.end())
			++eIDIt;

		cout << "# id�� ���ĵǾ��� ��:\n";
		while (sIDIt != eIDIt) {
			(*sIDIt)->printInfo();
			++sIDIt;
		}

		// name���� ���ĵ� Player���
		cout << "# name���� ���ĵǾ��� ��:\n";
		auto nameIt = lower_bound(playersSortedByName.cbegin(), playersSortedByName.cend(), targetPlayer, [](const Player* p, const Player* target) { return p->getNameRef() < target->getNameRef(); });	// key���� ���� ���ʰ�
		if (nameIt != playersSortedByName.begin())
			(*(nameIt - 1))->printInfo();
		(*nameIt)->printInfo();
		if ((nameIt + 1) != playersSortedByName.end())
			(*(nameIt + 1))->printInfo();

		// score���� ���ĵ� Player���
		cout << "# score�� ���ĵǾ��� ��:\n";
		auto scoreIt = lower_bound(playersSortedByScore.cbegin(), playersSortedByScore.cend(), targetPlayer, [](const Player* p, const Player* target) { return p->getScore() < target->getScore(); });	// key���� ���� ���ʰ�
		if (scoreIt != playersSortedByScore.begin())
			(*(scoreIt - 1))->printInfo();
		(*scoreIt)->printInfo();
		if ((scoreIt + 1) != playersSortedByScore.end())
			(*(scoreIt + 1))->printInfo();

		cout << endl;
	}

}


