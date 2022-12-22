#pragma once
#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H
#include<bits/stdc++.h>
#include "ZBase64.h"
using namespace std;

typedef struct HMTree {
	unsigned char letter;
	int data;
	HMTree* lchild;
	HMTree* rchild;
}HMTree;


//hmmap->huffman结点->HMTree
HMTree* make_HuffmanTree(map<unsigned char, int> hmmap) {
	vector<HMTree*> hmlist;
	for (auto i: hmmap) {
		HMTree* newr = (HMTree*)malloc(sizeof(HMTree));
		newr->letter = i.first;
		newr->data = i.second;
		newr->lchild = NULL;
		newr->rchild = NULL;
		hmlist.push_back(newr);
	}
	int i = 0;
	while (i < hmlist.size() - 1) {
		sort(hmlist.begin(), hmlist.end(), [](HMTree* a, HMTree* b) {return a->data < b->data; });
		HMTree* newr = (HMTree*)malloc(sizeof(HMTree));
		newr->lchild = hmlist[i];
		newr->rchild = hmlist[i + 1];
		newr->data = hmlist[i]->data + hmlist[i + 1]->data;
		hmlist[i + 1] = newr;
//		hmlist[i]->data = -1;
		i++;
	}
	return hmlist[hmlist.size() - 1];
}	//貌似没有问题

//生成Huffman编/译码表
void makeASC(HMTree* tra, vector<bool>&inlist, map<unsigned char, vector<bool>>&interp, map<vector<bool>, unsigned char>&Rinterp){
	if (tra->lchild==NULL&&tra->rchild==NULL) {		//到达叶节点
		interp.insert({ tra->letter, inlist });
		Rinterp.insert({inlist, tra->letter});
	}
	else {
		inlist.push_back(0);
		makeASC(tra->lchild, inlist, interp, Rinterp);
		inlist.pop_back();
		inlist.push_back(1);
		makeASC(tra->rchild, inlist, interp, Rinterp);
		inlist.pop_back();			//回溯——每次push后都要pop,不能对空的pop();
	}
	return;
}

//输出各字符出现频率
void preorder(HMTree* tra,map<unsigned char,vector<bool>>&interp) {
	if (tra->lchild == NULL && tra->rchild == NULL) {
		cout << tra->letter << ":	" << tra->data<<"		";
		for (auto i : interp[tra->letter])
			cout << i;
			cout << endl;
	}
	if (tra->lchild != NULL)	preorder(tra->lchild, interp);
	if (tra->rchild != NULL)	preorder(tra->rchild, interp);
	return	;
}
#endif