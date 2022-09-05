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

class ShoppingManager
{
public:
	void Shopping_Input(ClientManager& C_ref, ProductManager& P_ref,
		int num, string _clpk, string _prpk, int _date, int _quantatiy);
	void Shopping_Display();
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
	vector<Shopping*> shoppingList;
private:
	int S_Count = 0;
	int Snumber = 0;
	string CL_PK;
	string PR_PK;
	int date;
	int quan;
	int Allprice;
};

#endif