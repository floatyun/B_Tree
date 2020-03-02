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
	//cout << "B������" << endl;
	if (argc == 1) {
		cout << "�޲����汾" << endl;
		in.open("in.txt");
	}
	else {
		cout << "����1 " << argv[1] << endl;
		in.open(argv[1]);
	}

	getHelpDocAndShow();

	if (argc < 3) {
		//cout << "ʹ����Ļ���" << endl;
		//cout << "ʹ��Ĭ�ϵ�out.txt" << endl;
		out.open("out.txt");
	}
	else {
		cout << "����2 " << argv[2] << endl;
		out.open(argv[2]);
	}

	if ((!in) || (!out)) {
		cout << "�ļ��򿪴���";
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
				cout << tmp << "�Ѿ��ɹ�����" << endl;
			}
			else if ("remove" == cmd || "delete" == cmd) {
				cin >> tmp.name;
				stus.remove(tmp);
				cout << "�Ѿ��ɹ�ɾ��" << tmp.name << endl;
			}
			else if ("find" == cmd || "query" == cmd) {
				cin >> tmp.name;
				res = stus.find(tmp);
				if (nullptr == res)
					cout << tmp.name << "������" << endl;
				else
					cout << "�ѳɹ��ҵ�" << *res << endl;
			}
			else if ("change" == cmd) {
				cin >> tmp;
				res = stus.find(tmp);
				if (nullptr == res) {
					cout << tmp.name << "�����ڣ�";
					cout << "��ֱ�Ӳ���������¼��" << tmp;
					stus.insert(tmp);
					cout << "�Ѿ��ɹ�����" << endl;
				}
				else {
					t = *res;
					stus.remove(t);
					stus.insert(tmp);
					cout << "�ѳɹ���" << tmp.name << "�ĳɼ���" << t.score << "�޸�Ϊ" << tmp.score << endl;
				}
			}
			else if ("help" == cmd) {
				cout << helpDoc << endl;
			}
			else {
				cout << cmd << "�������" << endl;
			}
		}
		catch (invalid_argument e) {
			cout << e.what() << endl;
		}
		
		/*logflow << "Log" << lineCount << endl;
		stus.check(logflow, stus.get_root());*/
		/*B_TreeOut << "��ʼ��ӡB��" << endl;
		stus.print(B_TreeOut,stus.get_root());
		B_TreeOut << endl << "������ӡ" << endl;*/
	}
	/*logflow.close();*/
	in.close();
	out.close();
	return 0;
}