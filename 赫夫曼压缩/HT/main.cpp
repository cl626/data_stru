#include <bits/stdc++.h>
#include <Windows.h>
#include "HuffmanTree.h"
#include "ZBase64.h"
#include "codetransfer.h"
#include "fileop.h"
using namespace std;

int main() {
	clock_t start, end;	double runtime;
	string ifname, ofname,name, path,exit;
	

//类似于缓存
	map<string, map<unsigned char, vector<bool>>> intlist;	//huffman编码列表
	map<string, map<vector<bool>, unsigned char>> Rintlist;//huffman译码列表
	map<string, int> bdlist;

	while (1) {
		cout << "1.压缩；2.解压；输入你的选项:";
		int act;
		cin >> act;
		if (act == 1) {
			cout << "请输入待压缩文件路径:";
			cin >> path;
			cout << "输入待压缩文件名称:";
			cin >> name;
			ifname = path + name;
			cout << "输入压缩文件位置:";
			cin >> exit;
			ofname =exit + name + ".zip";
			ifstream in;
			ofstream out(ofname);
			int buding = 0;
			//your program
			vector<char> charlist;
			map<unsigned char, int> hmlist;	//<字符,出现次数>对
			map<unsigned char, vector<bool>> interp;	//huffman编码表
			map<vector<bool>, unsigned char> Rinterp;//huffman译码表
			char enter;
			//从string.txt读取字符存入hmlsit
			start = clock();
			read_to_vector(ifname, in, charlist);	//文件存入vector<charlist>
			charlist_for_buildht(charlist, hmlist, interp, Rinterp);	//根据charlist建huffman表
			cout << "finish build hmlist" << endl;
			Rintlist.insert({ ofname,Rinterp });	//存储字符串对应的译码表
//			in.close();
//			in.open(ifname, ifstream::in);	//in打开
			yasuo(charlist, buding, interp, out);	//压缩为二进制文件并输出
			cout << "finish compress";
			bdlist.insert({ ofname,buding });		//存储ofname_buding 
			in.close();
			end = clock();
			runtime = (double)(end - start) / CLOCKS_PER_SEC;
			cout << "压缩用时=" << fixed << setprecision(8) << runtime << "秒" << endl;
		}
		else {
			//下面解压缩
			cout << "请输入解压缩文件路径:";
			cin >> path;
			cout << "输入解压缩文件名称:";
			cin >> name;
			ifname = path + name;
			cout << "输入解压文件位置:";
			cin >> exit;
			ofname = exit+name.substr(0, name.size() - 4);
			ifstream in2(ifname);
			FILE* out2;
			vector<char> charlist;
			start = clock();
			jieyasuo(in2, bdlist[ifname], Rintlist[ifname], charlist);
			vector_to_file(charlist, ofname, out2);
			end = clock();
			runtime = (double)(end - start) / CLOCKS_PER_SEC;
			cout << "压缩用时=" << fixed << setprecision(8) << runtime << "秒" << endl;
		}
	}
};
