#include<iostream>
using namespace std;
#include"speechManager.h"

int main()
{
	//������������
	srand((unsigned int)time(NULL));
	//�������������
	SpeechManager sm;

	int choice = 0;
	while (true)
	{
		sm.show_Meun();
		cout << "����������ѡ��" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1://1.��ʼ����
			sm.startSpeech();
			break;
		case 2://2.�鿴�����¼
			sm.showRecord();
			break;
		case 3://3.��ձ�����¼
			sm.clearRecord();
			break;
		case 0://0.�˳�����
			sm.exitSystem();
			break;
		default:
			break;
		}
	}

	system("pause");
	return 0;
}