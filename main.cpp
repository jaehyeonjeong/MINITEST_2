#include "ClientManager.h"
#include "ProductManager.h"
#include "ShoppingManager.h"

int main()
{
	//main ���� ����ġ ���� ���� ����� �ȵ�
	int L_number = 0, S_number;

	//client cin ����
	string c_word, c_name, c_phone, c_email;

	//product cin ����
	string p_id, p_name; int p_price;

	//shopping cin ����
	string pk_cl, pk_pr; int s_date, s_quan, s_num;

	ClientManager cm;
	ProductManager pm;
	ShoppingManager sm;

	//Client Product Shopping �ؽ�Ʈ �ҷ�����
	cm.Client_Load();
	pm.Product_Load();
	sm.Shopping_Load();
	cout << "�ȳ��Ͻʴϱ�? Dentist Center �Դϴ�." << endl;
	while (L_number != 4)
	{
		sm.FindCPrice(cm); //���� ó������ �Լ��� ȣ���ϸ� �˾Ƽ� ó�� ���� ������
		cout << "\n�Ʒ��� �ش��ϴ� ��ȣ�� �Է��Ͽ� ���Ͻô� ������ Ȱ���Ͻʽÿ�." << endl;
		cout << "1. �� ���� ����, 2. ��ǰ ���� ����, 3.���� ���� ����, 4.����" << endl;
		cout << "��ȣ�� �Է��Ͽ� �ּ��� : "; cin >> L_number;

		if (!cin) //������ ���� �ܼ� �Էºκ� ��� �˻�
		{
			cout << "\n1 ~ 4�� ���� ������ ���ڸ� �Է°��� �մϴ�." << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}

		switch (L_number)
		{

		//�� ���� ����ġ
		case 1:
		client:;
			cout << "\n1.�� ���� ����" << endl;
			cout << "1.�Է�, 2.��ȸ, 3.����, 4.��λ���, 5.����" << endl;
			cout << "�ش��ϴ� ��ȣ�� �Է����ּ��� : "; cin >> S_number;

			if (!cin) //������ ���� �ܼ� �Էºκ� ��� �˻�
			{
				cout << "\n�� ���� ������ ������ ���ڸ� �Է����� �ʾҽ��ϴ�." << endl;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				goto client;
			}

			switch (S_number)
			{
			case 1:
				cout << "\n�� ���� �Է�" << endl;
				cout << "�� ��� ID : "; cin >> c_word;
				cout << "�� ��� �̸� : "; cin >> c_name;
				cout << "�� ��� ��ȭ��ȣ : "; cin >> c_phone;
				cout << "�� ��� �̸��� : "; cin >> c_email;
				cm.Client_Input(c_word, c_name, c_phone, c_email);
				break;
			case 2:
				cm.Client_Display();
				break;
			case 3:
				cm.Client_Display();
				cout << "\nID�� ������ �Է��ϸ� ������ �����˴ϴ�." << endl;
				cout << "������ �� ID �Է� : "; cin >> c_word;
				cout << "������ �� ������ �Է� : "; cin >> c_phone;
				cm.Client_Remove(c_word, c_phone); cout << endl;
				break;
			case 4:
				cm.Client_Remove_All();
				cm.Client_Display();
				break;
			case 5:
				cm.Client_Display();
				cout << "\nID�� ������ �Է��ϸ� ������ ����˴ϴ�." << endl;
				cout << "����� �� ID�� �Է� : "; cin >> c_word;
				cout << "����� �� ������ �Է� : "; cin >> c_name;
				cm.Client_Change(c_word, c_name); cout << endl;
				break;
			default:
				cout << "\n�Է��Ͻ� �� ���� ���� ��ȣ�� �����ϴ�." << endl;
				break;
			}
			break;

		//��ǰ ���� ����ġ
		case 2:
		product:;
			cout << "\n2.��ǰ ���� ����" << endl;
			cout << "1.�Է�, 2.��ȸ, 3.����, 4.��λ���, 5.����" << endl;
			cout << "�ش��ϴ� ��ȣ�� �Է����ּ��� : "; cin >> S_number;

			if (!cin)//������ ���� �ܼ� �Էºκ� ��� �˻�
			{
				cout << "\n��ǰ ���� ������ ������ ���ڸ� �Է����� �ʾҽ��ϴ�." << endl;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				goto product;
			}

			switch (S_number)
			{
			case 1:
			
				cout << "\n��ǰ ���� �Է�" << endl;
				cout << "��ǰ ��� ID : "; cin >> p_id;
				cout << "��ǰ ��� �̸� : "; cin >> p_name;
			product_1:;
				cout << "��ǰ ��� ���� : "; cin >> p_price;
				if (!cin)//������ ���� �ܼ� �Էºκ� ��� �˻�
				{
					cout << "\n��� ���ݿ� ������ ���ڸ� �Է����� �ʾҽ��ϴ�." << endl;
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					goto product_1;
				}
				pm.Product_Input(p_id, p_name, p_price);
				break;
			case 2:
				pm.Product_Display();
				break;
			case 3:
				pm.Product_Display();
				cout << "\nID�� �Է��ϸ� ������ �����˴ϴ�." << endl;
				cout << "������ ��ǰ ID �Է� : "; cin >> p_id;
				pm.Product_Remove(p_id); cout << endl;
				break;
			case 4:
				pm.Product_Remove_All();
				pm.Product_Display();
				break;
			case 5:
				pm.Product_Display();
				cout << "\nID�� �Է��ϸ� ������ ����˴ϴ�." << endl;
				cout << "����� ��ǰ ID�� �Է� : "; cin >> p_id;
				pm.Product_Change(p_id);
				break;
			default:
				cout << "�Է��Ͻ� ��ǰ ���� ���� ��ȣ�� �����ϴ�." << endl;
				break;
			}
			break;


		//���� ���� ����ġ
		case 3:
		shopping:;
			sm.sort();
			cout << "\n3.���� ���� ����" << endl;
			cout << "1.�ֹ�, 2.��ȸ, 3.����, 4.��ü����, 5.����" << endl;
			cout << "��ȣ�� �Է����ּ��� : "; cin >> S_number;
			if (!cin)//������ ���� �ܼ� �Էºκ� ��� �˻�
			{
				cout << "\n���� ���� ������ ������ ���ڸ� �Է����� �ʾҽ��ϴ�." << endl;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				goto shopping;
			}
			switch (S_number)
			{
			case 1:
				cm.Client_Display();
				pm.Product_Display();
				cout << "���� ����Ʈ�� ���� �ش��ϴ� ��ǰ�� �������� �Է��ϼ���." << endl;
				cout << "���� ��� ID : "; cin >> pk_cl;
				cout << "��ǰ�� ��� ID : "; cin >> pk_pr;
				shopping_1:;
				cout << "���ų�¥(�� : 220830, 210578, YYMMDD) : "; cin >> s_date;
				if (!cin)
				{
					cout << "\n���ų�¥�� ������ ���ڸ� �Է����� �ʾҽ��ϴ�." << endl;
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					goto shopping_1;
				}
				shopping_2:;
				cout << "���ż��� : "; cin >> s_quan; cout << endl;
				if (!cin)
				{
					cout << "\n���ż����� ������ ���ڸ� �Է����� �ʾҽ��ϴ�." << endl;
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					goto shopping_2;
				}
				sm.Shopping_Input(cm, pm, sm.getSNumber(), pk_cl,
					pk_pr, s_date, s_quan); cout << endl;
				//sm.FindCPrice(cm);
				break;
			case 2:
				sm.Shopping_Display(); cout << endl;
				break;
			case 3:
				sm.Shopping_Display();
			shopping_3:;
				cout << "\n������ ���� ��ȣ�� �Է����ּ��� : "; cin >> s_num;
				if (!cin)//������ ���� �ܼ� �Էºκ� ��� �˻�
				{
					cout << "\n��ȣ�� ������ ���ڸ� �Է����� �ʾҽ��ϴ�." << endl;
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					goto shopping_3;
				}
				sm.Shopping_Remove(s_num); 
				//sm.FindCPrice(cm);
				break;
			case 4:
				sm.Shopping_Remove_All(cm);
				sm.Shopping_Display();
				//sm.FindCPrice(cm);
				break;
			case 5:
			shopping_4:;
				sm.Shopping_Display();
				cout << "\n������ ���� ��ȣ�� �Է����ּ��� : "; cin >> s_num;
				if (!cin)//������ ���� �ܼ� �Էºκ� ��� �˻�
				{
					cout << "\n��ȣ�� ������ ���ڸ� �Է����� �ʾҽ��ϴ�." << endl;
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					goto shopping_4;
				}
				sm.Shopping_Change(s_num, pm);
				//sm.FindCPrice(cm);
				break;
			default:
				cout << "�Է��Ͻ� ���� ���� ���� ��ȣ�� �����ϴ�." << endl;
				break;
			}
			break;

		//���α׷� ���� ����ġ	
		case 4:
			char push;
			cout << "\n������ ���α׷��� �����Ͻðڽ��ϱ�? (y/n) : "; cin >> push;
			if (push == 'y' || push == 'Y')
			{
				cm.Client_Save();
				pm.Product_Save();
				sm.Shopping_Save();
				cout << "���α׷� ����!!" << endl << endl;
				exit(1);
				break;
			}
			cout << "���α׷� ����!!" << endl << endl;
			exit(1);
			break;

		default:
			cout << "\n�ش� ��ȣ�� �����ϴ�!\n" << endl;
			break;
		}
	}

	return 0;
}