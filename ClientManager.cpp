#include "ClientManager.h"

//main������ �������� ���� �����Ͱ� ���� �Լ�
void ClientManager::Client_Input(string _word,
	string _name, string _phone, string _email)
{
	clientList.push_back(new Client(_word, _name, _phone, _email));
	ClientManager::C_Count += 1;
	Client_PK(_word);
	cout << "\n���� ���� �Է� �Ϸ�" << endl;
}

//���� ���� ����Ʈ ���� �Լ�
void ClientManager::Client_Display()
{
	cout << "ClientCount : " << C_Count << endl;
	cout << "+++++++++++++++++++++++���� ���� ����Ʈ+++++++++++++++++++++++++++" << endl;
	cout << "------------------------------------------------------------------" << endl;
	cout << setw(11) << "����ID" << " | " << setw(10) << "���� ����" << " | " << setw(15) << "���� ��ȭ��ȣ" << " | " 
		<< setw(20) << "���� �̸���" << " | " << setw(12) << "���� ���" << endl;
	cout << "------------------------------------------------------------------" << endl;
	for_each(clientList.begin(), clientList.end(), [](Client* c)
		{
			cout << setw(11) << c->getCWord() << " | " << setw(10) << c->getCName() << " | "
				<< setw(15) << c->getCPhone() << " | " << setw(20) << c->getCEmail() << " | " 
				
				//��� Ȯ�ΰ� ������ �ѱݾ��� Ȯ���ϴ� �Լ�
				<< setw(12) << c->getCGrade() << " : " << c->getCPrice() << endl;
			cout << "------------------------------------------------------------------" << endl;
		});
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl << endl;
}

//���� ���� ���� �Լ�
void ClientManager::Client_Remove(string _word, string _name)
{
	for (int i = 0; i < C_Count; i++)
	{
		if ((clientList.at(i)->getCWord().compare(_word) == 0) &&
			(clientList.at(i)->getCName().compare(_name) == 0))
		{
			clientList.erase(clientList.begin() + i);
			ClientManager::C_Count -= 1;
			cout << "\n���� ���� ���� �Ϸ�" << endl;
		}
	}
}

//���� ���� ��ü ���� �Լ�
void ClientManager::Client_Remove_All()
{
	while (!clientList.empty())
	{
		clientList.erase(clientList.begin(), clientList.end());
	}
	ClientManager::C_Count = 0;
	cout << "\n���� ���� ��ü ���� �Ϸ�" << endl;
}

//���� ���� ���� �Լ�
void ClientManager::Client_Change(string _word, string _name)
{
	for (int i = 0; i < ClientManager::C_Count; i++)
	{
		if ((clientList.at(i)->getCWord().compare(_word) == 0) &&
			(clientList.at(i)->getCName().compare(_name) == 0))
		{
			cout << "\n������ ���� ID : "; cin >> ClientManager::CM_Word;
			clientList.at(i)->setCWord(ClientManager::CM_Word);
			cout << "������ ���� ���� : "; cin >> ClientManager::CM_Name;
			clientList.at(i)->setCName(ClientManager::CM_Name);
			cout << "������ ���� ��ȭ��ȣ : "; cin >> ClientManager::CM_Phone;
			clientList.at(i)->setCPhone(ClientManager::CM_Phone);
			cout << "������ ���� �̸��� : "; cin >> ClientManager::CM_Email;
			clientList.at(i)->setCEmail(ClientManager::CM_Email);
			cout << "���� ���� ���� �Ϸ�!!" << endl;
		}
	}
}

void ClientManager::Client_PK(string _word)
{
	string C_WORD = _word;
	auto it = find_if(clientList.begin(), clientList.end(),
		[=](Client* p) {return *p == C_WORD; });
	if (it != clientList.end())
	{
		Client* c = *it;
		cout << "Client Prime Key : " << c->getCWord() << endl;
	}
}

//���� ���� ���Ϸ� ���� �Լ�
void ClientManager::Client_Save()
{
	ofstream file;
	file.open("clientlist.txt");
	if (!file.fail()) {
		for (const auto& c : clientList) {
			file << c->getCWord() << ',';
			file << c->getCName() << ',';
			file << c->getCPhone() << ',';
			file << c->getCEmail() << ',';

			//���Ϸ� ��ް� ������ �ݾ� ����
			file << c->getCGrade() << ',';
			file << c->getCPrice() << ',';
			file << C_Count << endl;
		}
		file << endl;
	}
	file.close();
	cout << "Client ���� ���� �Ϸ�" << endl;
}

//���� ���� ���Ϸ� �ҷ����� �Լ�
void ClientManager::Client_Load()
{
	//vector<Client*> vecList;
	ifstream file; //input
	file.open("clientlist.txt");
	if (!file.fail()) {
		while (!file.eof()) {
			vector<string> row = parseCSV(file, ',');
			if (row.size()) {
				//�ش� ������ ����� �ݾ� int ������ ��ȯ
				int cprice = atoi(row[5].c_str());

				int count = atoi(row[6].c_str());

				//row[4]�� cprice���� client�����ڿ� ���Ͽ� ���Ͽ��� �ҷ��帲
				Client* c = new Client(row[0], row[1],
					row[2], row[3], row[4], cprice);
				clientList.push_back(c);
				C_Count = count;
			}
		}
	}
	file.close();
	cout << "Client ���� �ҷ����� �Ϸ�" << endl;
}

vector<string> ClientManager::parseCSV(istream& file,
	char delimiter)
{
	stringstream ss;
	vector<string> row;
	string t = " \n\r\t";

	while (!file.eof()) {
		char c = file.get();
		if (c == delimiter || c == '\r' || c == '\n') {
			if (file.peek() == '\n') file.get();
			string s = ss.str();
			s.erase(0, s.find_first_not_of(t));
			s.erase(s.find_last_not_of(t) + 1);
			row.push_back(s);
			ss.str("");
			if (c != delimiter) break;
		}
		else {
			ss << c;
		}
	}
	return row;
}