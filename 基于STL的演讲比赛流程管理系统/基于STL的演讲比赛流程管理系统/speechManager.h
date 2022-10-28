#pragma once
#include<iostream>
using namespace std;
#include<vector>
#include<map>
#include"speaker.h"
#include<algorithm>
#include<deque>
#include<numeric>
#include<fstream>

//创建演讲比赛的管理类
class SpeechManager
{
public:
	//成员函数：
	
	//构造函数
	SpeechManager();

	//菜单展示
	void show_Meun();

	//初始化属性
	void initSpeech();

	//初始化创建12名选手
	void createSpeaker();

	//开始比赛   比赛流程控制
	void startSpeech();

	//抽签
	void speechDraw();

	//比赛
	void speechContest();

	//显示比赛结果
	void showScore();

	//保存记录
	void saveRecord();

	//读取记录
	void loadRecord();

	//显示往届记录
	void showRecord();

	//清空记录
	void clearRecord();

	//文件为空的标志
	bool fileIsEmpty;

	//存放往届记录的容器
	map<int, vector<string>> m_Record;

	//退出程序
	void exitSystem();
	
	//析构函数
	~SpeechManager();


	//成员属性：
	//比赛选手  容器 12 人
	vector<int>v1;

	//第一轮晋级容器  6人
	vector<int>v2;

	//胜利前三名容器  3人
	vector<int>vVictory;

	//存放编号以及对应的具体选手 容器
	map<int, Speaker>m_Speaker;

	//记录比赛轮数
	int m_Index;
};