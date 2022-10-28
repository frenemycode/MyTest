#include"speechManager.h"

//构造函数
SpeechManager::SpeechManager()
{
	//初始化容器和属性
	this->initSpeech();

	//创建选手
	this->createSpeaker();

	//读取记录
	this->loadRecord();
}

//菜单展示
void SpeechManager::show_Meun()
{
	cout << "**********************************" << endl;
	cout << "*********欢迎参加演比赛***********" << endl;
	cout << "*********1.开始演讲比赛***********" << endl;
	cout << "*********2.查看往届记录***********" << endl;
	cout << "*********3.清空比赛记录***********" << endl;
	cout << "*********0.退出比赛程序***********" << endl;
	cout << endl;
}

//初始化属性
void SpeechManager::initSpeech()
{
	//保证容器为空
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();

	//初始化比赛轮次为第一轮
	this->m_Index = 1;
	//将记录的容器  也清空
	this->m_Record.clear();
}

//初始化创建12名选手
void SpeechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < 12; i++)
	{
		string name = "选手";
		name += nameSeed[i];

		Speaker sp;
		sp.m_Name = name;
		for (int i = 0; i < 2; i++)
		{
			sp.m_Score[i] = 0;
		}

		//12名选手编号
		this->v1.push_back(i + 10001);

		//选手编号  以及对应的选手  存放到map容器中
		this->m_Speaker.insert(make_pair(i + 10001, sp));

	}
}

//开始比赛   比赛流程控制
void SpeechManager::startSpeech()
{
	//第一轮比赛
	//1.抽签
	this->speechDraw();
	//2.比赛
	this->speechContest();
	//3.显示晋级结果
	this->showScore();

	//第二轮比赛
	this->m_Index++;
	 
	//1.抽签
	this->speechDraw();
	//2.比赛
	this->speechContest();
	//3.显示最终结果
	this->showScore();
	//4.保存分数
	this->saveRecord();

	//重置比赛   原因：下面的三行代码刚开始放在构造函数中，
	// 当程序执行时，便会自动执行 但构造函数只执行一次，当再次进行比赛时，
	// 容器和属性得不到初始化 所以我们要把它放到比赛流程这块
	//初始化容器和属性
	this->initSpeech();
	//创建选手
	this->createSpeaker();
	//读取记录
	this->loadRecord();

	cout << "本届比赛完毕" << endl;
	system("pause");
	system("cls");
}

//抽签
void SpeechManager::speechDraw()
{
	cout << "第《" << this->m_Index << "》轮比赛选手正在抽签" << endl;
	cout << "--------------------------------" << endl;
	cout << "抽签后演讲顺序如下：" << endl;

	if (this->m_Index == 1) {
		//第一轮比赛
		random_shuffle(v1.begin(), v1.end());//打乱顺序，起到随机抽签的规则
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		//第二轮比赛
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << "-----------------------------------" << endl;
	system("pause");
}

//比赛
void SpeechManager::speechContest()
{
	cout << "-------------第" << this->m_Index << " 轮比赛正式开始———————" << endl;

	//准备临时容器  存放小组成绩
	multimap<double, int, greater<double>> groupScore;

	int num = 0; //记录人员个数   6人一组

	vector<int>v_Src;//比赛选手容器
	if (this->m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}
	//遍历所有选手进行比赛
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;
		//评委打分
		deque<double>d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f; //600~1000
			//cout << score << " ";
			d.push_back(score);
		}
		sort(d.begin(), d.end(), greater<double>()); //排序
		d.pop_front(); //去除最高分
		d.pop_back(); //去除最低分

		double sum = accumulate(d.begin(), d.end(), 0.0f);//总分
		double avg = sum / (double)d.size(); //平均分
		//将平均分放入到map容器中
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

		//将打分数据  放入到临时小组容器中
		groupScore.insert(make_pair(avg, *it)); //key是得分   value是具体选手编号
		//每6人取出前三名
		if (num % 6 == 0)
		{
			cout << "第" << num / 6 << "小组比赛名次：" << endl;
			
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "编号：" << it->second << "\t姓名：" << this->m_Speaker[it->second].m_Name <<
					"\t成绩：" << this->m_Speaker[it->second].m_Score[this->m_Index - 1] << endl;
			}
			//取走前三名
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator dit = groupScore.begin(); dit != groupScore.end() && count < 3; dit++, count++)
			{
				if (this->m_Index == 1)
				{
					v2.push_back((*dit).second);
				}
				else
				{
					vVictory.push_back((*dit).second);
				}
			}
			groupScore.clear(); //小组容器清空
		}
	}
	cout << "第" << this->m_Index << "轮比赛完毕!-------------------" << endl;
	system("pause");
}

//显示比赛结果
void SpeechManager::showScore()
{
	cout << "------------------第" << this->m_Index << "轮晋级选手信息如下：----------------" << endl;
	vector<int>v;
	if (this->m_Index == 1)
	{
		v = v2;//如果是第一轮比赛结束后，获胜者将放在v2里
	}
	else
	{
		v = vVictory;//如果是第二轮比赛结束后，获胜者将放在vVictory里
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "选手编号：" << *it << "\t姓名：" << this->m_Speaker[*it].m_Name << "\t得分：" <<
			this->m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->show_Meun();
}

//保存记录
void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);//以追加的方式写文件  csv可用excel打开

	//将每个选手数据写到文件中去
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;

	//关闭
	ofs.close();
	cout << "记录已保存" << endl;

	//有记录了  文件不为空
	this->fileIsEmpty = false;
}

//读取记录
void SpeechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);//读文件

	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}
	//文件被清空了
	char ch;
	ifs >> ch;
	if (ifs.eof()) //ifs.eof表示文件结尾
	{
		cout << "文件为空" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	//文件不为空
	this->fileIsEmpty = false;
	ifs.putback(ch); //将上面读取的单个字符  放回来

	string data;
	int index = 0; //记录届数
	while (ifs >> data)
	{
		//cout << data << endl;

		vector<string>v;//存放6个string的字符串
		int pos = -1;//记录找到的“，”的位置
		int start = 0;
		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				//没有找到
				break;
			}
			string temp = data.substr(start, pos - start);
			//cout << temp << endl;
			v.push_back(temp);
			start = pos + 1;//接着找下一个逗号
		}
		this->m_Record.insert(make_pair(index, v));//放到记录往届信息的map容器中
		index++;
	}
	ifs.close();
}

//显示往届记录
void SpeechManager::showRecord()
{
	if (this->fileIsEmpty)
	{
		cout << "文件为空或者不存在" << endl;
	}
	for (int i = 0; i < this->m_Record.size(); i++)
	{
		cout << "第" << i + 1 << "届"
			<< "冠军编号：" << this->m_Record[i][0] << "得分：" << this->m_Record[i][1] << " "
			<< "亚军编号：" << this->m_Record[i][2] << "得分：" << this->m_Record[i][3] << " "
			<< "季军编号：" << this->m_Record[i][4] << "得分：" << this->m_Record[i][5] << endl;
	}
	system("pause");
	system("cls");
}

//清空记录
void SpeechManager::clearRecord()
{
	cout << "确认清空？" << endl;
	cout << "1、确认" << endl;
	cout << "2、返回" << endl;

	int select = 0;
	cin >> select;
	if (select == 1)
	{
		//打开模式  ios::trunc 如果存在删除文件并重新创建
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		//初始化容器和属性
		this->initSpeech();

		//创建选手
		this->createSpeaker();

		//读取记录
		this->loadRecord();

		cout << "清空成功！" << endl;
	}
	system("pause");
	system("cls");
}
//退出程序
void SpeechManager::exitSystem()
{
	cout << "已成功退出系统，欢迎下次使用" << endl;
	system("pause");
	exit(0);
}
//析构函数
SpeechManager::~SpeechManager()
{

}