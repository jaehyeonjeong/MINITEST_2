#include "ShoppingManager.h"

//���� ���� ������ �߰� �Լ�
void ShoppingManager::Shopping_Input(ClientManager& C_ref, ProductManager& P_ref,
	int _num, string _clpk, string _prpk, int _date, int _quantatiy)
{
	string VVIP = "VVIP";
	string VIP = "VIP";
	string Normal = "Normal";
	for (int i = 0; i < C_ref.getCCount(); i++)
	{
		if (C_ref.clientList.at(i)->getCWord().compare(_clpk) == 0) //Ŭ���̾�Ʈ PK�� �Է��� Ŭ���̾�Ʈ PK�� �� ���̸� �ٵ� ���
		{
			string C_Word = C_ref.clientList.at(i)->getCWord();
			auto it1 = find_if(C_ref.clientList.begin(), C_ref.clientList.end(),
				[=](Client* c) {return *c == C_Word; });
			if (it1 != C_ref.clientList.end())
			{
				Client* c = *it1;
				cout << "ADD Client Prime Key : " << c->getCWord() << endl;
				for (int j = 0; j < P_ref.getPCount(); j++)
				{
					if (P_ref.productList.at(j)->getPId().compare(_prpk) == 0) //���δ�Ʈ PK�� �Է��� ���δ�Ʈ PK�� �� ���̸� �ٵ� ���
					{
						string P_Id = P_ref.productList.at(j)->getPId();
						auto it2 = find_if(P_ref.productList.begin(),
							P_ref.productList.end(),
							[=](Product* p) {return *p == P_Id; });
						if (it2 != P_ref.productList.end())
						{
							Product* p = *it2;
							cout << "ADD Prodcut Prime Key : " << p->getPId() << endl;
							double price;
		
							//��޺� ���� ����
							if (C_ref.clientList.at(i)->getCGrade().compare(VVIP) == 0)
							{
								price = (P_ref.productList.at(j)->getPPrice() * _quantatiy) * 0.90; //VVIP�� 10�ۼ�Ʈ ����
								shoppingList.push_back(new Shopping(_num,
									_clpk, _prpk, _date, _quantatiy, price)); // ���� PK�� ��ġ�� ���� �ȴٸ� ���� ����Ʈ�� ������ �߰�
								Snumber += 1;
								S_Count += 1;
								cout << "\n���� ���� �߰� �Ϸ�" << endl;
							}
							if (C_ref.clientList.at(i)->getCGrade().compare(VIP) == 0)
							{
								price = (P_ref.productList.at(j)->getPPrice() * _quantatiy) * 0.95; //VIP�� 5�ۼ�Ʈ ����
								shoppingList.push_back(new Shopping(_num,
									_clpk, _prpk, _date, _quantatiy, price)); // ���� PK�� ��ġ�� ���� �ȴٸ� ���� ����Ʈ�� ������ �߰�
								Snumber += 1;
								S_Count += 1;
								cout << "\n���� ���� �߰� �Ϸ�" << endl;
							}
							if (C_ref.clientList.at(i)->getCGrade().compare(Normal) == 0)
							{
								price = P_ref.productList.at(j)->getPPrice() * _quantatiy; //Normal�̸� �ƹ��͵� ����
								shoppingList.push_back(new Shopping(_num,
									_clpk, _prpk, _date, _quantatiy, price)); // ���� PK�� ��ġ�� ���� �ȴٸ� ���� ����Ʈ�� ������ �߰�
								Snumber += 1;
								S_Count += 1;
								cout << "\n���� ���� �߰� �Ϸ�" << endl;
							}
						}
					}
				}
			}
		}
	}
}

//���� ���� ����Ʈ ���� ���� �Լ�
void ShoppingManager::sort()
{
	for (int i = 0; i < S_Count; i++)
	{
		shoppingList.at(i)->setSNumber(i);
	}
}

//���� ���� ����Ʈ ���� �Լ�
void ShoppingManager::Shopping_Display()
{
	cout << "ShoppingCount : " << S_Count << endl;
	cout << "++++++++++++++++++++++++++++++���� ���� ����Ʈ++++++++++++++++++++++++++++++" << endl;
	cout << "----------------------------------------------------------------------------" << endl;
	cout << setw(5) << "��ȣ" << " | " << setw(10) << "�� ID" << " | " << setw(11) << "��ǰ ID" << " | " << setw(11) << "���� ��¥" << " | "
		<< setw(5) << "����" << " | " << setw(18) << "�� �ݾ�" << endl;
	cout << "----------------------------------------------------------------------------" << endl;
	for_each(shoppingList.begin(), shoppingList.end(), [](Shopping* s)
		{
			cout << setw(5) << s->getSNumber() << " | " << setw(10) << s->getSPKClient() << " | "
				<< setw(11) << s->getSPKProduct() << " | " << setw(11) << s->getSDate() <<
				" | " << setw(5) << s->getSQuan() << " | " << setw(16) << s->getSAllprice() << "��" << endl;
			cout << "----------------------------------------------------------------------------" << endl;
		});
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl << endl;
}

//���� ���� ���� �Լ�
void ShoppingManager::Shopping_Remove(int _num)
{
	for (int i = 0; i < S_Count; i++)
	{
		if (shoppingList.at(i)->getSNumber() == _num)
		{
			shoppingList.erase(shoppingList.begin() + i);
			S_Count--;
			cout << "\n���� ���� ���� �Ϸ�!" << endl;
		}
	}
}

//���� ���� ��ü ���� �Լ�
void ShoppingManager::Shopping_Remove_All(ClientManager& _cm)
{
	string EX = "EX";
	while (!shoppingList.empty())
	{
		shoppingList.erase(shoppingList.begin() + 1, shoppingList.end());
		if (shoppingList.at(0)) break;
	}
	S_Count = 1;
	Snumber = 0; //Shoppinglist count �ʱ�ȭ
	
	cout << "\n���� ���� ��ü ���� �Ϸ�!" << endl;
}

//���� ���� ���� �Լ�
void ShoppingManager::Shopping_Change(int _num, ProductManager& sh_pm)
{
	
	for (int i = 0; i < S_Count; i++)
	{
		if (shoppingList.at(i)->getSNumber() == _num)
		{
		shopping_date:;
			cout << "\n������ ��¥ : "; cin >> date;
			if (!cin)//������ ���� �ܼ� �Էºκ� ��� �˻�
			{
				cout << "\n��� ���ݿ� ������ ���ڸ� �Է����� �ʾҽ��ϴ�." << endl;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				goto shopping_date;
			}
			shoppingList.at(i)->setSDate(date);
		shopping_quan:;
			cout << "������ ���� : "; cin >> quan;
			if (!cin)//������ ���� �ܼ� �Էºκ� ��� �˻�
			{
				cout << "\n��� ���ݿ� ������ ���ڸ� �Է����� �ʾҽ��ϴ�." << endl;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				goto shopping_quan;
			}
			shoppingList.at(i)->setSQuan(quan);
			cout << "�� ���� ���� �Ϸ�!!" << endl;

			for (int j = 0; j < sh_pm.getPCount(); j++)
			{
				if (sh_pm.productList.at(j)->getPId().compare(shoppingList.at(i)->getSPKProduct()) == 0)
				{
					int price = sh_pm.productList.at(j)->getPPrice() * quan;
					shoppingList.at(i)->setSAllprice(price);
					cout << "���� ���� �Ϸ�" << endl;
				}
			}
		}
	}
}

//���� ���� ���� �Լ�
void ShoppingManager::Shopping_Save()
{
	ofstream file;
	file.open("shoppinglist.txt");
	if (!file.fail())
	{
		for (const auto& s : shoppingList)
		{
			file << s->getSNumber() << ',';
			file << s->getSPKClient() << ',';
			file << s->getSPKProduct() << ',';
			file << s->getSDate() << ',';
			file << s->getSQuan() << ',';
			file << s->getSAllprice() << ',';
			file << S_Count << endl;
		}
		file << endl;
	}
	file.close();
	cout << "Shopping ���� ���� �Ϸ�" << endl;
}

//���� ���� �ҷ����� �Լ�
void ShoppingManager::Shopping_Load()
{
	ifstream file;
	file.open("shoppinglist.txt");

	if (!file.fail())
	{
		while (!file.eof())
		{
			vector<string> row = parseCSV(file, ',');
			if (row.size())
			{
				int snum = atoi(row[0].c_str());
				int date = atoi(row[3].c_str());
				int quan = atoi(row[4].c_str());
				int price = atoi(row[5].c_str());
				int count = atoi(row[6].c_str());
				Shopping* s = new Shopping(snum, row[1],
					row[2], date, quan, price);
				shoppingList.push_back(s);
				S_Count = count;
				Snumber = count;
			}
		}
	}
	file.close();
	cout << "Shopping ���� �ҷ����� �Ϸ�" << endl << endl;
}

vector<string> ShoppingManager::parseCSV(istream& file, char delimiter)
{
	stringstream ss;
	vector<string> row;
	string t = " \n\r\t";

	while (!file.eof())
	{
		char c = file.get();
		if (c == delimiter || c == '\r' || c == '\n')
		{
			if (file.peek() == '\n') file.get();
			string s = ss.str();
			s.erase(0, s.find_first_not_of(t));
			s.erase(s.find_last_not_of(t) + 1);
			row.push_back(s);
			ss.str("");
			if (c != delimiter) break;
		}
		else
		{
			ss << c;
		}
	}
	return row;
}

void ShoppingManager::setAllPrice(int _price)
{
	Allprice = _price;
}

//���� ����Ʈ�� ���� �� �ѱݾ� Ž�� �Լ� client->cprice->getCPrice(), shopping->getAllPrice()
	//�� �Լ��� ���� �߰� ���� ���� ��ɿ��� ��ɿ� ���� �� ����� �ֽ�ȭ �� �� �ֵ��� ����
void ShoppingManager::FindCPrice(ClientManager& _cm)
{
	//�ʱ�ȭ�� ������ ���� ���, ����
	string grade;
	//int cprice = 0;

	//���� client�� ������ �ִ� ��� �ݾ� �Լ� �ʱ�ȭ
	for (int i = 0; i < _cm.getCCount(); i++)
	{
		_cm.clientList.at(i)->setCPrice(0); //0���� �ʱ�ȭ
	}

	for (int j = 0; j < _cm.getCCount(); j++) //���� ������ �� ����Ʈ ���� ��ŭ for������ Ž�� ���� i
	{
		for (int i = 0; i < S_Count; i++) //���� ������ ���� ����Ʈ�� ���� ��ŭ for������ Ž�� ���������� j
		{
			if (_cm.clientList.at(j)->getCWord().compare(shoppingList.at(i)->getSPKClient()) == 0) 
				//Ž���� ���� ����Ʈ �� �� ����Ʈ�� PK�� ��ġ�ϴ� �� Ȯ���� ���� ����Ʈ�� �ѱݾ��� 
				//���ϸ� ������� �ʱ�ȭ
			{
				//���� ���� 1�࿡ �ش��ϴ� �� �ҷ����� cprice�� ����
				//cprice += shoppingList.at(i)->getSAllprice();

				//�ش��ϴ� �� �࿡ ����� �ݾ� ����
				_cm.clientList.at(j)->setAddCPrice(shoppingList.at(i)->getSAllprice());
			}
		}
	}

	//������ �ݾ� ���� ���� ���� ��� ����
	for (int i = 0; i < _cm.getCCount(); i++)
	{
		if (_cm.clientList.at(i)->getCPrice() >= 1000000) //�ش��ϴ� �� �������� 1,000,000 �̻��� ���
		{
			grade = "VVIP";
			_cm.clientList.at(i)->setCGrade(grade); //VVIP�� ��� ����
			//cout << "VVIP�� ����" << endl;
		}
		else if (_cm.clientList.at(i)->getCPrice() >= 500000 &&
			_cm.clientList.at(i)->getCPrice() < 1000000) //�ش��ϴ� �� �������� 500000 �̻� 1000000 �̸��� ��� 
		{
			grade = "VIP";
			_cm.clientList.at(i)->setCGrade(grade);//VIP�� ��� ����
			//cout << "VIP�� ����" << endl;
		}
		else if(_cm.clientList.at(i)->getCPrice() >= 0 && 
			_cm.clientList.at(i)->getCPrice() < 500000)
		{
			grade = "Normal"; //500000�̸��� ���
			_cm.clientList.at(i)->setCGrade(grade);//Normal�� ��� ����
			//cout << "Normal�� ����" << endl;
		}
	}
}