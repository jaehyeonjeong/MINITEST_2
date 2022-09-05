#ifndef _SHOPPING_MANAGER_H_
#define _SHOPPING_MANAGER_H_

#include "Shopping.h"
#include "ClientManager.h"
#include "ProductManager.h"
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <iomanip>

#define BLACK 0
#define WHITE 15
#define LIGHTRED 12

void textcolor(int foreground, int background);

class ShoppingManager
{
public:
	void Shopping_Input(ClientManager& C_ref, ProductManager& P_ref,
		int num, string _clpk, string _prpk, int _date, int _quantatiy);
	void Shopping_Display(ClientManager& _cm, ProductManager& _pm);
	int getSNumber() { return Snumber; }
	void setSNumber(int _Snumber) { Snumber = _Snumber; }
	void sort();
	void Shopping_Remove(int _num);
	void Shopping_Remove_All(ClientManager& _cm);
	void Shopping_Change(int _num, ProductManager& sh_pm);
	void Shopping_Save();
	void Shopping_Load();


	//구매 리스트 get, set 함수구현
	int getAllPrice() { return Allprice; }
	void setAllPrice(int _price);

	//쇼핑 리스트에 따른 고객 총금액 탐지 함수 client->cprice->getCPrice(), shopping->getAllPrice()
	//이 함수는 각각 추가 제거 변경 기능에서 기능에 따른 고객 등급이 최신화 될 수 있도록 적용
	void FindCPrice(ClientManager& _cm);
	//main 함수 에서는 sm.FindCPrice(cm) 으로 각 case마다 호출

	vector<string> parseCSV(istream& file, char delimiter);
private:
	vector<Shopping*> shoppingList;
private:
	//구매정보 리스트 넘버 PK와 구매 정보 카운트 저장 변수
	int S_Count = 0;
	int Snumber = 0;

	//구매정보 리스트의 변경함수 내부 변경 데이터
	int date; //또한 날짜를 입력받아 해당하는 날짜에 데이터를 찾음
	int quan;

	//shopping list의 pk의 값을 찾기위한 데이터
	string pk_cl;
	string pk_pr;

	
	int Allprice;
};

#endif