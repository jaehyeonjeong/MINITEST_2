#include "ShoppingManager.h"
#include <Windows.h>
#include <conio.h>


//구매 정보 데이터 추가 함수
void ShoppingManager::Shopping_Input(ClientManager& C_ref, ProductManager& P_ref,
	int _num, string _clpk, string _prpk, int _date, int _quantatiy)
{
	//고객 등급을 string변수로 내부에서 따로 저장하는 이유는 compare함수에 "VVIP"로 작성하면 const char*로 NULL문자까지 포함시켜 버린다.
	string VVIP = "VVIP";
	string VIP = "VIP";
	string Normal = "Normal";



	for (int i = 0; i < C_ref.getCCount(); i++)
	{
		if (C_ref.clientList.at(i)->getCWord().compare(_clpk) == 0) //클라이언트 PK와 입력한 클라이언트 PK값 비교 참이면 바디 계산
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
					if (P_ref.productList.at(j)->getPId().compare(_prpk) == 0) //프로덕트 PK와 입력한 프로덕트 PK값 비교 참이면 바디 계산
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
		
							//등급별 가격 할인
							if (C_ref.clientList.at(i)->getCGrade().compare(VVIP) == 0)
							{
								price = (P_ref.productList.at(j)->getPPrice() * _quantatiy) * 0.90; //VVIP면 10퍼센트 할인
								shoppingList.push_back(new Shopping(_num,
									_clpk, _prpk, _date, _quantatiy, price)); // 위의 PK값 일치가 충족 된다면 쇼핑 리스트에 데이터 추가
								Snumber += 1;
								S_Count += 1;
								cout << "\n구매 정보 추가 완료" << endl;
							}
							if (C_ref.clientList.at(i)->getCGrade().compare(VIP) == 0)
							{
								price = (P_ref.productList.at(j)->getPPrice() * _quantatiy) * 0.95; //VIP면 5퍼센트 할인
								shoppingList.push_back(new Shopping(_num,
									_clpk, _prpk, _date, _quantatiy, price)); // 위의 PK값 일치가 충족 된다면 쇼핑 리스트에 데이터 추가
								Snumber += 1;
								S_Count += 1;
								cout << "\n구매 정보 추가 완료" << endl;
							}
							if (C_ref.clientList.at(i)->getCGrade().compare(Normal) == 0)
							{
								price = P_ref.productList.at(j)->getPPrice() * _quantatiy; //Normal이면 아무것도 없음
								shoppingList.push_back(new Shopping(_num,
									_clpk, _prpk, _date, _quantatiy, price)); // 위의 PK값 일치가 충족 된다면 쇼핑 리스트에 데이터 추가
								Snumber += 1;
								S_Count += 1;
								cout << "\n구매 정보 추가 완료" << endl;
							}
						}
					}
				}
			}
		}
	}
}

//구매 정보 리스트 순서 정리 함수
void ShoppingManager::sort()
{
	for (int i = 0; i < S_Count; i++)
	{
		shoppingList.at(i)->setSNumber(i);
	}
}

//구매 정보 리스트 공개 함수
void ShoppingManager::Shopping_Display(ClientManager& _cm, ProductManager& _pm)
{
	int num = 0;
	string PKCL, PKPR;
	int sm_date, flash = 1;
	char find_c;

	cout << "ShoppingCount : " << S_Count << endl;
	cout << "++++++++++++++++++++++++++++++구매 정보 리스트++++++++++++++++++++++++++++++" << endl;
	cout << "----------------------------------------------------------------------------" << endl;
	cout << setw(5) << "번호" << " | " << setw(10) << "고객 ID" << " | " << setw(11) << "상품 ID" << " | " << setw(11) << "구매 날짜" << " | "
		<< setw(5) << "수량" << " | " << setw(18) << "총 금액" << endl;
	cout << "----------------------------------------------------------------------------" << endl;
	for_each(shoppingList.begin(), shoppingList.end(), [](Shopping* s)
		{
			cout << setw(5) << s->getSNumber() << " | " << setw(10) << s->getSPKClient() << " | "
				<< setw(11) << s->getSPKProduct() << " | " << setw(11) << s->getSDate() <<
				" | " << setw(5) << s->getSQuan() << " | " << setw(16) << s->getSAllprice() << "원" << endl;
			cout << "----------------------------------------------------------------------------" << endl;
		});
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl << endl;


	//구매리스트 조회후 client, product, 날짜별 정보 검색
	while (num != 4)
	{
	back_search:;
		cout << "\n구매 정보 리스트에서 검색할 키워드가 있으십니까?" << endl;
		cout << "1. ClientID, 2. ProductID, 3. 날짜별 구매 정보, 4.종료 : "; cin >> num;

		if (!cin)
		{
			cout << "\n정수형 숫자를 입력해주시기 바랍니다." << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			goto back_search;
		}
		switch (num)
		{
			//ClientID의 정보의 종류를 물어보는 case문
		case 1:
			cout << "\nClientID의 정보중 어떤 정보를 원하십니까?" << endl;
			cout << "1. ClientID 정보, 2. 해당 ClientID 구매 목록 : "; cin >> find_c;
			do
			{
				find_c = _getch();
				if (find_c >= '1' && find_c <= '2')
				{
					cout << "정수형 숫자를 입력해주시기 바랍니다!!!" << endl;
					cin.ignore(INT_MAX, '\n');
					break;
				}
			} while (true);
			//ClientID 정보 공개 함수
			if (find_c == '1')
			{
				cout << "\nClientID 입력 : "; cin >> pk_cl;
				cout << "\n해당 ClientID(" << pk_cl << ")의 정보는 :";
				PKCL = pk_cl;
				auto it = find_if(_cm.clientList.begin(), _cm.clientList.end(),
					[=](Client* c) {return *c == PKCL; });
				if (it != _cm.clientList.end())
				{
					Client* c = *it;
					cout << "\n고객 성함 : " << c->getCName() << 
						", \n고객 등급 : " << c->getCGrade() <<
						", \n고객 전화번호 : " << c->getCPhone() << 
						", \n고객 이메일 : " << c->getCEmail() << endl << endl;
				}
			}
			//해당 ClientID 구매 정보 리스트
			else if (find_c == '2')
			{
				cout << "\nClientID 입력 : "; cin >> pk_cl;
				PKCL = pk_cl;
				cout << endl;
				auto it = find_if(_cm.clientList.begin(), _cm.clientList.end(),
					[=](Client* c) {return *c == PKCL; });
				if (it != _cm.clientList.end())
				{
					Client* c = *it;
					cout << "+++++++++++++++++++++++" << pk_cl <<"의 구매 정보 리스트++++++++++++++++++++++++" << endl;
					cout << "----------------------------------------------------------------------------" << endl;
					cout << setw(5) << "번호" << " | " << setw(10) << "고객 ID" << " | " << setw(11) << "상품 ID" << " | " << setw(11) << "구매 날짜" << " | "
						<< setw(5) << "수량" << " | " << setw(18) << "총 금액" << endl;
					cout << "----------------------------------------------------------------------------" << endl;
					for (int i = 0; i < S_Count; i++)
					{
						if (c->getCWord().compare(shoppingList.at(i)->getSPKClient()) == 0)
						{
							cout << setw(5) << shoppingList.at(i)->getSNumber() << " | " << setw(10);
							textcolor(LIGHTRED, BLACK);
							cout << shoppingList.at(i)->getSPKClient();
							textcolor(WHITE, BLACK);
							cout << " | " << setw(11) << shoppingList.at(i)->getSPKProduct() << " | " << setw(11) << shoppingList.at(i)->getSDate() << " | "
								<< setw(5) << shoppingList.at(i)->getSDate() << " | " << setw(18) << shoppingList.at(i)->getSAllprice() << endl;
						}
						cout << "----------------------------------------------------------------------------" << endl;
					}
					cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl << endl;
				}
			}

			//해당없는 정수형 숫자는 조회 질문으로 돌아감
			else
			{
				cout << "\n조회 질문으로 돌아가겠습니다." << endl;
				break;
			}
			break;
			//ClientID의 정보의 종류를 물어보는 case문


			//ProdcutID의 정보의 종류를 물어보는 case문
		case 2:
			cout << "\nProductID의 정보중 어떤 정보를 원하십니까?" << endl;
			cout << "1. ProductID 정보, 2. 해당 ProductID 구매 목록 : "; cin >> find_c;
			do
			{
				find_c = _getch();
				if (find_c >= '1' && find_c <= '2')
				{
					cout << "정수형 숫자를 입력해주시기 바랍니다!!!" << endl;
					cin.ignore(INT_MAX, '\n');
					break;
				}
			} while (true);
			//해당 ProdcutID의 정보 검색
			if (find_c == '1')
			{
				cout << "\nProductID 입력 :"; cin >> pk_pr;
				cout << "\n해당 ProductID(" << pk_pr << ")의 정보는 :";
				PKPR = pk_pr;
				auto it = find_if(_pm.productList.begin(), _pm.productList.end(),
					[=](Product* p) {return *p == PKPR; });
				if (it != _pm.productList.end())
				{
					Product* p = *it;
					cout << "\n상품 이름 : " << p->getPName() << 
						", \n상품 가격 : " << p->getPPrice() << endl << endl;
				}
			}

			//해당 ProductID의 구매정보 리스트 나열
			else if (find_c == '2')
			{
				cout << "\nProductID 입력 : "; cin >> pk_pr;
				PKPR = pk_pr;
				cout << endl;
				auto it = find_if(_pm.productList.begin(), _pm.productList.end(),
					[=](Product* p) {return *p == PKPR; });
				if (it != _pm.productList.end())
				{
					Product* p = *it;
					cout << "++++++++++++++++++++++++" << pk_pr << "의 구매 정보 리스트+++++++++++++++++++++++++" << endl;
					cout << "----------------------------------------------------------------------------" << endl;
					cout << setw(5) << "번호" << " | " << setw(10) << "고객 ID" << " | " << setw(11) << "상품 ID" << " | " << setw(11) << "구매 날짜" << " | "
						<< setw(5) << "수량" << " | " << setw(18) << "총 금액" << endl;
					cout << "----------------------------------------------------------------------------" << endl;
					for (int i = 0; i < S_Count; i++)
					{
						if (p->getPId().compare(shoppingList.at(i)->getSPKProduct()) == 0)
						{
							cout << setw(5) << shoppingList.at(i)->getSNumber() << " | " << setw(10) << shoppingList.at(i)->getSPKClient() << " | ";
							textcolor(LIGHTRED, BLACK);
								cout << setw(11) << shoppingList.at(i)->getSPKProduct();
								textcolor(WHITE, BLACK);
								cout << " | " << setw(11) << shoppingList.at(i)->getSDate() << " | "
								<< setw(5) << shoppingList.at(i)->getSDate() << " | " << setw(18) << shoppingList.at(i)->getSAllprice() << endl;
						}
						cout << "----------------------------------------------------------------------------" << endl;
					}
					cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl << endl;
				}
			}

			else
			{
				cout << "조회 질문으로 돌아가겠습니다." << endl;
				break;
			}
			break;
			//ProdcutID의 정보의 종류를 물어보는 case문


			//shopping list의 날짜별 구매정보 리스트 탐/검색
		case 3:
		back_date:;
			cout << "\nShopping Date입력 : "; cin >> date;
			if (!cin)
			{
				cout << "현재 입력한 정보가 정수형 데이터가 아닙니다." << endl;
				cin.ignore(INT_MAX, '\n');
				goto back_date;
			}
			sm_date = date;
			cout << endl;
			if (flash == 1)
			{
				auto it = find_if(shoppingList.begin(), shoppingList.end(), [=](Shopping* s) {return *s == sm_date; });
				if (it != shoppingList.end())
				{
					Shopping* s = *it;
					cout << "+++++++++++++++++++++++++++" << date << " 별 구매 리스트++++++++++++++++++++++++++++" << endl;
					cout << "----------------------------------------------------------------------------" << endl;
					cout << setw(5) << "번호" << " | " << setw(10) << "고객 ID" << " | " << setw(11) << "상품 ID" << " | " << setw(11) << "구매 날짜" << " | "
						<< setw(5) << "수량" << " | " << setw(18) << "총 금액" << endl;
					cout << "----------------------------------------------------------------------------" << endl;
					for (int i = 0; i < S_Count; i++)
					{
						if (s->getSDate() == shoppingList.at(i)->getSDate())
						{
							cout << setw(5) << shoppingList.at(i)->getSNumber() << " | " << setw(10) << shoppingList.at(i)->getSPKClient() << " | "
								<< setw(11) << shoppingList.at(i)->getSPKProduct() << " | ";
							textcolor(LIGHTRED, BLACK);
							cout << setw(11) << shoppingList.at(i)->getSDate();
							textcolor(WHITE, BLACK);
							cout << " | "  << setw(5) << shoppingList.at(i)->getSQuan();
								cout << " | " << setw(18) << shoppingList.at(i)->getSAllprice() << endl;
						}
						cout << "----------------------------------------------------------------------------" << endl;
					}
					cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl << endl;
				}
			}
			break;
			//shopping list의 날짜별 구매정보 리스트 탐/검색


		case 4:
			cout << "검색 프로그램 종료" << endl;
			break;
		default:
			cout << "해당하는 검색 키워드가 없습니다." << endl;
			break;
		}
	}
}

//구매 정보 삭제 함수
void ShoppingManager::Shopping_Remove(int _num)
{
	for (int i = 0; i < S_Count; i++)
	{
		if (shoppingList.at(i)->getSNumber() == _num)
		{
			shoppingList.erase(shoppingList.begin() + i);
			S_Count--;
			cout << "\n구매 정보 삭제 완료!" << endl;
		}
	}
}

//구매 정보 전체 삭제 함수
void ShoppingManager::Shopping_Remove_All(ClientManager& _cm)
{
	string EX = "EX";
	while (!shoppingList.empty())
	{
		shoppingList.erase(shoppingList.begin() + 1, shoppingList.end());
		if (shoppingList.at(0)) break;
	}
	S_Count = 1;
	Snumber = 0; //Shoppinglist count 초기화
	
	cout << "\n구매 정보 전체 삭제 완료!" << endl;
}

//구매 정보 변경 함수
void ShoppingManager::Shopping_Change(int _num, ProductManager& sh_pm)
{
	
	for (int i = 0; i < S_Count; i++)
	{
		if (shoppingList.at(i)->getSNumber() == _num)
		{
		shopping_date:;
			cout << "\n변경할 날짜 : "; cin >> date;
			if (!cin)//정수형 인자 콘솔 입력부분 경계 검사
			{
				cout << "\n등록 가격에 정수형 숫자를 입력하지 않았습니다." << endl;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				goto shopping_date;
			}
			shoppingList.at(i)->setSDate(date);
		shopping_quan:;
			cout << "변경할 수량 : "; cin >> quan;
			if (!cin)//정수형 인자 콘솔 입력부분 경계 검사
			{
				cout << "\n등록 가격에 정수형 숫자를 입력하지 않았습니다." << endl;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				goto shopping_quan;
			}
			shoppingList.at(i)->setSQuan(quan);
			cout << "고객 정보 변경 완료!!" << endl;

			for (int j = 0; j < sh_pm.getPCount(); j++)
			{
				if (sh_pm.productList.at(j)->getPId().compare(shoppingList.at(i)->getSPKProduct()) == 0)
				{
					int price = sh_pm.productList.at(j)->getPPrice() * quan;
					shoppingList.at(i)->setSAllprice(price);
					cout << "가격 변경 완료" << endl;
				}
			}
		}
	}
}

//구매 정보 저장 함수
void ShoppingManager::Shopping_Save()
{
	ofstream file;
	file.open("shoppinglist.csv");
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
	cout << "Shopping 파일 저장 완료" << endl;
}

//구매 정보 불러오기 함수
void ShoppingManager::Shopping_Load()
{
	ifstream file;
	file.open("shoppinglist.csv");

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
	cout << "Shopping 파일 불러오기 완료" << endl << endl;
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

//쇼핑 리스트에 따른 고객 총금액 탐지 함수 client->cprice->getCPrice(), shopping->getAllPrice()
	//이 함수는 각각 추가 제거 변경 기능에서 기능에 따른 고객 등급이 최신화 될 수 있도록 적용
void ShoppingManager::FindCPrice(ClientManager& _cm)
{
	//초기화할 변수값 생성 등급, 가격
	string grade;
	//int cprice = 0;

	//먼저 client가 가지고 있는 사용 금액 함수 초기화
	for (int i = 0; i < _cm.getCCount(); i++)
	{
		_cm.clientList.at(i)->setCPrice(0); //0으로 초기화
	}

	for (int j = 0; j < _cm.getCCount(); j++) //현재 설정된 고객 리스트 개수 만큼 for문으로 탐색 고객은 i
	{
		for (int i = 0; i < S_Count; i++) //현재 설정된 구매 리스트의 개수 만큼 for문으로 탐색 구매정보는 j
		{
			if (_cm.clientList.at(j)->getCWord().compare(shoppingList.at(i)->getSPKClient()) == 0) 
				//탐색한 구매 리스트 와 고객 리스트의 PK가 일치하는 지 확인후 구매 리스트의 총금액을 
				//더하며 고객등급을 초기화
			{
				//구매 정보 1행에 해당하는 값 불러오고 cprice에 누적
				//cprice += shoppingList.at(i)->getSAllprice();

				//해당하는 고객 행에 사용한 금액 누적
				_cm.clientList.at(j)->setAddCPrice(shoppingList.at(i)->getSAllprice());
			}
		}
	}

	//누적된 금액 누적 값에 따른 등급 지정
	for (int i = 0; i < _cm.getCCount(); i++)
	{
		if (_cm.clientList.at(i)->getCPrice() >= 1000000) //해당하는 고객 누적값이 1,000,000 이상인 경우
		{
			grade = "VVIP";
			_cm.clientList.at(i)->setCGrade(grade); //VVIP로 등급 설정
			//cout << "VVIP로 설정" << endl;
		}
		else if (_cm.clientList.at(i)->getCPrice() >= 500000 &&
			_cm.clientList.at(i)->getCPrice() < 1000000) //해당하는 고객 누적값이 500000 이상 1000000 미만인 경우 
		{
			grade = "VIP";
			_cm.clientList.at(i)->setCGrade(grade);//VIP로 등급 설정
			//cout << "VIP로 설정" << endl;
		}
		else if(_cm.clientList.at(i)->getCPrice() >= 0 && 
			_cm.clientList.at(i)->getCPrice() < 500000)
		{
			grade = "Normal"; //500000미만인 경우
			_cm.clientList.at(i)->setCGrade(grade);//Normal로 등급 설정
			//cout << "Normal로 설정" << endl;
		}
	}
}

void textcolor(int foreground, int background)
{
	int color = foreground + background * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}