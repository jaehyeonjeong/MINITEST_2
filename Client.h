#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <iostream>
using namespace std;

class Client
{
public:
	//고객 클래스 복사 생성자
	Client(string _word = "", string _name = "",
		string _phone = "", string _email = "", string _grade = "", int _cprice = 0)
		:C_Custom_Word(_word), C_Name(_name),
		C_Phone(_phone), C_Email(_email), C_Grade(_grade), Client_price(_cprice)
	{

	}
	string getCWord();
	void setCWord(string& _custom);
	string getCName();
	void setCName(string& _name);
	string getCPhone();
	void setCPhone(string& _phone);
	string getCEmail();
	void setCEmail(string& _email);

	//고객 등급 변수 get set함수
	string getCGrade() { return C_Grade; }
	void setCGrade(string _grade) { C_Grade = _grade; }

	//고객이 사용한 금액 get set함수
	int getCPrice() { return Client_price; }
	void setCPrice(int _price) { Client_price = _price; }

	//고객이 사용한 금액 누적하는 set함수
	void setAddCPrice(int _addprice) { Client_price += _addprice; }

	bool operator==(string str) const;
private:
	//고객 기본 데이터 설정
	string C_Custom_Word;
	string C_Name;
	string C_Phone;
	string C_Email;


	//휘하 두 데이터는 파일 저장을 위해 복사 생성자에서 초기화할 필요가 있음
	//고객 등급 변수 설정
	string C_Grade;
	//고객이 사용한 금액 저장
	int Client_price;
};

#endif