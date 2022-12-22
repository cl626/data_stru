#pragma once
#ifndef fileop_H
#define fileop_H

#include<bits/stdc++.h>
#include"HuffmanTree.h"
using namespace std;

void read_to_vector(string &ifname, ifstream &in, vector<char> &charlist) {	//从文件字符/二进制字符并用vector<char>存储
	string text = ifname.substr(ifname.size() - 4, ifname.size() - 1);
	unsigned char enter;		int length;
	if (text == ".txt") in.open(ifname, ifstream::in);
	else in.open(ifname, ifstream::in | ios::binary);

	in.seekg(0, ios::end);
	length = in.tellg();;
	in.seekg(0, ios::beg);
	cout << length << endl;

	char* buffer = new char[length];
	// 读取图片
	in.read(buffer, length);
	if (length > 0)
		printf("read ok!");

	//输入charlist
	charlist.assign(length, 0);
	for (int i = 0; i < length; i++)
		charlist[i] = buffer[i];
	in.close();
}

void charlist_for_buildht(vector<char> &charlist, map<unsigned char,int> &hmlist,
map<unsigned char,vector<bool>> &interp,map<vector<bool>,unsigned char> &Rinterp) {
	unsigned char enter;		
	//从charlist读取字符存入hmlsit
	for (int i = 0; i < charlist.size(); i++) {
		enter = charlist[i];
		if (hmlist.find(enter) == hmlist.end())
			hmlist.insert({ enter,1 });
		else hmlist[enter]++;
	}
	//建立huffman树与huffman编码表
	HMTree* root = (HMTree*)malloc(sizeof(HMTree));
	root = make_HuffmanTree(hmlist);
	vector<bool> inlist = {};	//存储dfs中01串
	makeASC(root, inlist, interp, Rinterp);
	preorder(root, interp);	//前序遍历输出
}
/*	while (in >> enter) {
			if (hmlist.find(enter) == hmlist.end())
				hmlist.insert({ enter,1 });
			else hmlist[enter]++;
		}
		//建立huffman树与huffman编码表
		HMTree* root = (HMTree*)malloc(sizeof(HMTree));
		root = make_HuffmanTree(hmlist);
		vector<bool> inlist = {};	//存储dfs中01串
		makeASC(root, inlist, interp, Rinterp);
		preorder(root, interp);	//前序遍历输出
		*/

void yasuo(vector<char> &charlist, int &buding, map<unsigned char, vector<bool>> &interp, ofstream &out) {
		//下面压缩
			//下面字符转为01码
	vector<bool> hmcode = {};
	string_to_hmcode(charlist, interp, hmcode);	//把输入字符串/二进制字符串转化为Huffman编码，按照前面生成的Huffman译码表
	cout << "finished str to hmcode";
	ofstream in_hm("in_hm.txt", ofstream::out);	//hm
	for (auto i : hmcode)
		in_hm << i;					//hm
	//01码转为ascii码
	vector<unsigned char> asccode = {};
	hmcode_to_asccode(hmcode, buding, asccode);	//把Huffman编码按8bits/byte转化为ASCII码
	ofstream in_asc("in_asc.txt");	//asc
	for (auto i : asccode)
		in_asc << i;				//asc
	//ascii码转为Base64编码
	vector<unsigned char> base64code = {};
	base64_encode(asccode, base64code);			//ASCII码转为base64编码，因为ASCII码不能全部打印
	//将Base64编码输出
	for (auto i : base64code)					//把base64编码输出到压缩文件.zip中
		out << i;
	out.close();
}

void jieyasuo(ifstream& in2, int buding, map<vector<bool>, unsigned char>& Rinterp,vector<char> &charlist) {
	char enter;
	vector<unsigned char> base64code2;
	vector<unsigned char> asccode2;
	vector<bool> hmcode2;
	while (in2 >> enter) {
		base64code2.push_back(enter);
	}
	//base64码转为asccode码
	base64_decode(base64code2, asccode2);
	ofstream out_asc("out_asc.txt");
	for (auto i : asccode2)	out_asc << i;
	//asccode转为01码
	asccode_to_hmcode(asccode2, hmcode2, buding);
	ofstream out_hm("out_hm.txt");
	for (auto i : hmcode2)	out_hm << i;
	//将hmcode转为原字符输出
	hmcode_to_string(hmcode2, charlist, Rinterp);
}

void vector_to_file(vector<char> &charlist, string &ofname, FILE* &out2) {	//将输出的字符/二进制字符输出到输出文件
	string text = ofname.substr(ofname.size() - 3, ofname.size() - 1);
	if (text == ".txt")	
		errno_t err = fopen_s(&out2,ofname.c_str(), "w");
	else 
		errno_t err= fopen_s(&out2,ofname.c_str(), "wb");

	int length = charlist.size();
	char* buffer = new char[length];
	for (int i = 0; i < length; i++) {
		buffer[i] = charlist[i];
	}
	fwrite(buffer, length, 1, out2);
	fclose(out2);
	delete [] buffer;
}

#endif