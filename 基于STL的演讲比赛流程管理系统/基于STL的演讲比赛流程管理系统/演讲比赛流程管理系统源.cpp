#include<iostream>
using namespace std;
#include"speechManager.h"

int main()
{
	//添加随机数种子
	srand((unsigned int)time(NULL));
	//创建管理类对象
	SpeechManager sm;

	int choice = 0;
	while (true)
	{
		sm.show_Meun();
		cout << "请输入您的选择：" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1://1.开始比赛
			sm.startSpeech();
			break;
		case 2://2.查看往届记录
			sm.showRecord();
			break;
		case 3://3.清空比赛记录
			sm.clearRecord();
			break;
		case 0://0.退出程序
			sm.exitSystem();
			break;
		default:
			break;
		}
	}

	system("pause");
	return 0;
}