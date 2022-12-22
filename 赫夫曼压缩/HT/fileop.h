#pragma once
#ifndef fileop_H
#define fileop_H

#include<bits/stdc++.h>
#include"HuffmanTree.h"
using namespace std;

void read_to_vector(string &ifname, ifstream &in, vector<char> &charlist) {	//���ļ��ַ�/�������ַ�����vector<char>�洢
	string text = ifname.substr(ifname.size() - 4, ifname.size() - 1);
	unsigned char enter;		int length;
	if (text == ".txt") in.open(ifname, ifstream::in);
	else in.open(ifname, ifstream::in | ios::binary);

	in.seekg(0, ios::end);
	length = in.tellg();;
	in.seekg(0, ios::beg);
	cout << length << endl;

	char* buffer = new char[length];
	// ��ȡͼƬ
	in.read(buffer, length);
	if (length > 0)
		printf("read ok!");

	//����charlist
	charlist.assign(length, 0);
	for (int i = 0; i < length; i++)
		charlist[i] = buffer[i];
	in.close();
}

void charlist_for_buildht(vector<char> &charlist, map<unsigned char,int> &hmlist,
map<unsigned char,vector<bool>> &interp,map<vector<bool>,unsigned char> &Rinterp) {
	unsigned char enter;		
	//��charlist��ȡ�ַ�����hmlsit
	for (int i = 0; i < charlist.size(); i++) {
		enter = charlist[i];
		if (hmlist.find(enter) == hmlist.end())
			hmlist.insert({ enter,1 });
		else hmlist[enter]++;
	}
	//����huffman����huffman�����
	HMTree* root = (HMTree*)malloc(sizeof(HMTree));
	root = make_HuffmanTree(hmlist);
	vector<bool> inlist = {};	//�洢dfs��01��
	makeASC(root, inlist, interp, Rinterp);
	preorder(root, interp);	//ǰ��������
}
/*	while (in >> enter) {
			if (hmlist.find(enter) == hmlist.end())
				hmlist.insert({ enter,1 });
			else hmlist[enter]++;
		}
		//����huffman����huffman�����
		HMTree* root = (HMTree*)malloc(sizeof(HMTree));
		root = make_HuffmanTree(hmlist);
		vector<bool> inlist = {};	//�洢dfs��01��
		makeASC(root, inlist, interp, Rinterp);
		preorder(root, interp);	//ǰ��������
		*/

void yasuo(vector<char> &charlist, int &buding, map<unsigned char, vector<bool>> &interp, ofstream &out) {
		//����ѹ��
			//�����ַ�תΪ01��
	vector<bool> hmcode = {};
	string_to_hmcode(charlist, interp, hmcode);	//�������ַ���/�������ַ���ת��ΪHuffman���룬����ǰ�����ɵ�Huffman�����
	cout << "finished str to hmcode";
	ofstream in_hm("in_hm.txt", ofstream::out);	//hm
	for (auto i : hmcode)
		in_hm << i;					//hm
	//01��תΪascii��
	vector<unsigned char> asccode = {};
	hmcode_to_asccode(hmcode, buding, asccode);	//��Huffman���밴8bits/byteת��ΪASCII��
	ofstream in_asc("in_asc.txt");	//asc
	for (auto i : asccode)
		in_asc << i;				//asc
	//ascii��תΪBase64����
	vector<unsigned char> base64code = {};
	base64_encode(asccode, base64code);			//ASCII��תΪbase64���룬��ΪASCII�벻��ȫ����ӡ
	//��Base64�������
	for (auto i : base64code)					//��base64���������ѹ���ļ�.zip��
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
	//base64��תΪasccode��
	base64_decode(base64code2, asccode2);
	ofstream out_asc("out_asc.txt");
	for (auto i : asccode2)	out_asc << i;
	//asccodeתΪ01��
	asccode_to_hmcode(asccode2, hmcode2, buding);
	ofstream out_hm("out_hm.txt");
	for (auto i : hmcode2)	out_hm << i;
	//��hmcodeתΪԭ�ַ����
	hmcode_to_string(hmcode2, charlist, Rinterp);
}

void vector_to_file(vector<char> &charlist, string &ofname, FILE* &out2) {	//��������ַ�/�������ַ����������ļ�
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