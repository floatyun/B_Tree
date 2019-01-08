#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
#include <exception>
#include <algorithm>
#include "B_Tree.h"
#include "student.h"
using namespace std;

B_Tree<student, student_comparator, student_printer> stus;
string helpDoc;

void getHelpDocAndShow() {
	ifstream in("help.txt");
	string t_cmd;
	if (in) {
		while (true) {
			getline(in, t_cmd);
			if (in.fail()) {
				in.close();
				break;
			}
			helpDoc += t_cmd + '\n';
		}
	}
	cout << helpDoc << endl;
	in.close();
}

string cmd;
student tmp;
student *res;
student t;
string json;
string t_cmd;
ifstream in;
ofstream out;

int main(int argc, char *argv[])
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int count = 0;
	//cout << "B树测试" << endl;
	if (argc == 1) {
		cout << "无参数版本" << endl;
		in.open("in.txt");
	}
	else {
		cout << "参数1 " << argv[1] << endl;
		in.open(argv[1]);
	}

	getHelpDocAndShow();

	if (argc < 3) {
		//cout << "使用屏幕输出" << endl;
		//cout << "使用默认的out.txt" << endl;
		out.open("out.txt");
	}
	else {
		cout << "参数2 " << argv[2] << endl;
		out.open(argv[2]);
	}

	if ((!in) || (!out)) {
		cout << "文件打开错误";
		return 0;
	}
	while (1) {
		cin >> t_cmd;
		cmd = "";
		//transform(t_cmd.begin(), t_cmd.end(), back_inserter(cmd), ::tolower);
		try {
			if ("exit" == cmd || "quit" == cmd) {
				break;
			}
			else if ("insert" == cmd || "add" == cmd) {
				cin >> tmp;
				stus.insert(tmp);
				cout << tmp << "已经成功插入" << endl;
			}
			else if ("remove" == cmd || "delete" == cmd) {
				cin >> tmp.name;
				stus.remove(tmp);
				cout << "已经成功删除" << tmp.name << endl;
			}
			else if ("find" == cmd || "query" == cmd) {
				cin >> tmp.name;
				res = stus.find(tmp);
				if (nullptr == res)
					cout << tmp.name << "不存在" << endl;
				else
					cout << "已成功找到" << *res << endl;
			}
			else if ("change" == cmd) {
				cin >> tmp;
				res = stus.find(tmp);
				if (nullptr == res) {
					cout << tmp.name << "不存在，";
					cout << "将直接插入这条记录。" << tmp;
					stus.insert(tmp);
					cout << "已经成功插入" << endl;
				}
				else {
					t = *res;
					stus.remove(t);
					stus.insert(tmp);
					cout << "已成功将" << tmp.name << "的成绩由" << t.score << "修改为" << tmp.score << endl;
				}
			}
			else if ("help" == cmd) {
				cout << helpDoc << endl;
			}
			else {
				cout << cmd << "命令不存在" << endl;
			}
		}
		catch (invalid_argument e) {
			cout << e.what() << endl;
		}
		
		/*logflow << "Log" << lineCount << endl;
		stus.check(logflow, stus.get_root());*/
		/*B_TreeOut << "开始打印B树" << endl;
		stus.print(B_TreeOut,stus.get_root());
		B_TreeOut << endl << "结束打印" << endl;*/
	}
	/*logflow.close();*/
	in.close();
	out.close();
	return 0;
}