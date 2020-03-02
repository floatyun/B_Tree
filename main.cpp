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

B_Tree<student, student_comparator, student_printer> stus(3);
string helpDoc;

#include <atltime.h>

// ����ʱ���left-right���Ժ������
uint64_t TimeDiff(SYSTEMTIME &left, SYSTEMTIME &right)

{
	CTime tmLeft(left.wYear, left.wMonth, left.wDay, 0, 0, 0);
	CTime tmRight(right.wYear, right.wMonth, right.wDay, 0, 0, 0);
	CTimeSpan sp = tmLeft - tmRight;
	long MillisecondsL = (left.wHour * 3600 + left.wMinute * 60 + left.wSecond) * 1000 + left.wMilliseconds;
	long MillisecondsR = (right.wHour * 3600 + right.wMinute * 60 + right.wSecond) * 1000 + right.wMilliseconds;
	return  (uint64_t)sp.GetDays() * 86400000 + (MillisecondsL - MillisecondsR);
}

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
	cout << helpDoc << '\n';
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

void save() {
	ofstream out("B_Tree_data.txt");
	if (out) {
		stus.print(out, stus.get_root());
	}
	else {
		cout << "�޷�����" << endl;
	}
}

void load() {
	ifstream in("B_Tree_data.txt");
	if (in) {
		stus.load(in);
		in.close();
	}
}

int main(int argc, char *argv[])
{
	ios::sync_with_stdio(0);
	in.tie(0);
	int count = 0;
	//load(); ע����ֻ�����ļ����뷽�����
	//out << "B������" << '\n';
	if (argc == 1) {
		out << "�޲����汾" << '\n';
		in.open("input.txt");
	}
	else {
		out << "����1 " << argv[1] << '\n';
		in.open(argv[1]);
	}

	getHelpDocAndShow();

	if (argc < 3) {
		//out << "ʹ����Ļ���" << '\n';
		//out << "ʹ��Ĭ�ϵ�out.txt" << '\n';
		out.open("out.txt");
	}
	else {
		out << "����2 " << argv[2] << '\n';
		out.open(argv[2]);
	}

	if ((!in) || (!out)) {
		out << "�ļ��򿪴���";
		return 0;
	}

	SYSTEMTIME  before, after;

	GetSystemTime(&before);
	while (1) {
		in >> t_cmd;
		if (in.fail())
			break;
		cmd = t_cmd;
		//transform(t_cmd.begin(), t_cmd.end(), back_inserter(cmd), ::tolower);
		try {
			if ("exit" == cmd || "quit" == cmd) {
				break;
			}
			else if ("insert" == cmd || "add" == cmd) {
				in >> tmp;
				stus.insert(tmp);
				out << tmp << "�Ѿ��ɹ�����" << '\n';
			}
			else if ("remove" == cmd || "delete" == cmd) {
				in >> tmp.name;
				stus.remove(tmp);
				out << "�Ѿ��ɹ�ɾ��" << tmp.name << '\n';
			}
			else if ("find" == cmd || "query" == cmd) {
				in >> tmp.name;
				res = stus.find(tmp);
				if (nullptr == res)
					out << tmp.name << "������" << '\n';
				else
					out << "�ѳɹ��ҵ�" << *res << '\n';
			}
			else if ("change" == cmd) {
				in >> tmp;
				res = stus.find(tmp);
				if (nullptr == res) {
					out << tmp.name << "�����ڣ�";
					out << "��ֱ�Ӳ���������¼��" << tmp;
					stus.insert(tmp);
					out << "�Ѿ��ɹ�����" << '\n';
				}
				else {
					t = *res;
					stus.remove(t);
					stus.insert(tmp);
					out << "�ѳɹ���" << tmp.name << "�ĳɼ���" << t.score << "�޸�Ϊ" << tmp.score << '\n';
				}
			}
			else if ("help" == cmd) {
				out << helpDoc << '\n';
			}
			else {
				out << cmd << "�������" << '\n';
			}
		}
		catch (invalid_argument e) {
			out << e.what() << '\n';
		}
		
		/*logflow << "Log" << lineCount << '\n';
		stus.check(logflow, stus.get_root());*/
		/*B_TreeOut << "��ʼ��ӡB��" << '\n';
		stus.print(B_TreeOut,stus.get_root());
		B_TreeOut << '\n' << "������ӡ" << '\n';*/
	}
	/*logflow.close();*/
	GetSystemTime(&after);
	cout << TimeDiff(after, before)<<"ms\n";
	in.close();
	out.close();
	save();
	return 0;
}