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

//�����ݽ������Ĺ�����
class SpeechManager
{
public:
	//��Ա������
	
	//���캯��
	SpeechManager();

	//�˵�չʾ
	void show_Meun();

	//��ʼ������
	void initSpeech();

	//��ʼ������12��ѡ��
	void createSpeaker();

	//��ʼ����   �������̿���
	void startSpeech();

	//��ǩ
	void speechDraw();

	//����
	void speechContest();

	//��ʾ�������
	void showScore();

	//�����¼
	void saveRecord();

	//��ȡ��¼
	void loadRecord();

	//��ʾ�����¼
	void showRecord();

	//��ռ�¼
	void clearRecord();

	//�ļ�Ϊ�յı�־
	bool fileIsEmpty;

	//��������¼������
	map<int, vector<string>> m_Record;

	//�˳�����
	void exitSystem();
	
	//��������
	~SpeechManager();


	//��Ա���ԣ�
	//����ѡ��  ���� 12 ��
	vector<int>v1;

	//��һ�ֽ�������  6��
	vector<int>v2;

	//ʤ��ǰ��������  3��
	vector<int>vVictory;

	//��ű���Լ���Ӧ�ľ���ѡ�� ����
	map<int, Speaker>m_Speaker;

	//��¼��������
	int m_Index;
};