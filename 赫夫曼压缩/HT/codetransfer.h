#pragma once
#ifndef CODETRANSFER_H
#define CODETRANSFER_H
#include "HuffmanTree.h"
#include <bits/stdc++.h>
using namespace std;
void string_to_hmcode(vector<char> &charlist, map<unsigned char, vector<bool>> interp,vector<bool> &boollist) {
	//ÿ���ַ���Ӧ01���ۼ�
	for (int j = 0; j < charlist.size(); j++) {
		for (auto i : interp[charlist[j]]) {
			boollist.push_back(i);
		}
	}
}

void hmcode_to_asccode(vector<bool> &boollist, int &buding,vector<unsigned char> &asccode) {
	int bl_len = boollist.size();
	int i = 0;
	unsigned char tem = 0;
	//01�봮ת����char��
	//�ҵ�i����i<=bl_len<i+8;
	while (i +8 <= bl_len) {
		tem = 0;
		for (int j = 0; j < 8; j++) {
			tem += boollist[i + j] << (7 - j);
		}
		asccode.push_back(tem);
		i += 8;
	}
	//i+8>bl_len>=i;	
	//if(bl_len==i)	nothing;	else bl_len-i=1,2,...,7;	subscript=i,...,i+6	
	if (bl_len-i) {	//buding=1~7
		tem = 0;
		for (int j = 0; j <bl_len-i; j++)
			tem += boollist[i + j] << (7 - j);
		asccode.push_back(tem);
	}
	buding = (8 + i - bl_len) % 8;
	return	;
}

void asccode_to_hmcode(vector<unsigned char> &asccode2, vector<bool> &boollist,int buding) {
	//��ASCII�����ת����01��
	for (auto s : asccode2) {
		vector <bool> a(8);
		for (int i = 0; i < 8; i++) {
			a[i] = s / (1 << (7 - i));
			s = s - a[i] * (1 << (7 - i));
		}
		for (auto i : a)
			boollist.push_back(i);
	}
	for (int i = 0; i < buding; i++)
		boollist.pop_back();
}

void hmcode_to_string(vector<bool> &boollist, vector<char> &charlist,map<vector<bool>, unsigned char>Rinterp) {
	//��01��ת����ԭ�ַ�
	//boollist.size=8k;	��Ч��boollist.size=8- buding;
	int bl_len = boollist.size();
	int count = 0;		
	map<vector<bool>,unsigned char>::iterator	tt;	
	vector<bool> bicode={};	//�洢��ǰ�ַ��ı���	
	while (count < bl_len ) {	
		bicode.push_back(boollist[count]);
		tt = Rinterp.find(bicode);
		if (tt != Rinterp.end()) {	//���ҵ��ַ������
			charlist.push_back(tt->second);
			//			cout << tt->second;
			bicode.clear();
		}
		count++;
	}
}

#endif // !CODETRANSFER_H
