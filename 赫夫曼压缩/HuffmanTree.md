Huffman树实验大概可以分为两部分——建立Huffman树并据此生成转换表+读取文件与base64编码相互转化

##### 充实的debug🐶🐶

- 编码树的回溯——每次push后pop()一次~~
- 封装顺眼~~

###建立Huffman树

##### 存储输入字符串

```cpp
map<char,int> hmlist;
map<char,vector<int>> interp;
map<vector<int>,char> Rinterp;
char enter;
while(data>>chaa){
	if(hmlist.find(chaa)==hmlist.end())
		hmlist.insert({chaa,1});
	else hmlist[chaa]++;
}
```

##### Huffman树的构造

```cpp
typedef struct HmTree{
    char letter;
    int data;
    HmTree *lchild;
    HmTree *rchild;
}HmTree;
vector<node*> list;
//对每个字符建立结点
for(auto i:hmlist){
 	HmTree* newr=malloc();
 	newr->letter=i->first;
 	newr->data=i->second;
 	newr->lchild=NULL;
 	newr->rchild=NULL;
	list.push_back(newr);
}  
```

##### 从map生成huffman树

```cpp
不能用链表，用结构体表示各个结点
int i=0;
while(i<list.size()-1){
	sort(list)at the order of node->data;
	HmTree* newr=malloc();
  	newr->lchild=list[i];
  	newr->rchild=list[i+1];
  	newr->data=list[0]->data+list[1]->data;
  	list[i+1]=newr;
  	list[i]->data=-1;	//保证不会操作已合并掉的结点
  	i++;
}
return list[list.size()-1]；
```

##### 生成Huffman编/译码表

```cpp
makeASC(Huffman* tra,vector<int>inlist,map<char,vector<int>> interp,map<vector<int>,char> Rinterp)
if(tra->left==NULL)		//到达叶节点
	interp.insert(tra->char,inlist);
	R_interp.insert(inlist,tra->char);
	return;
else
  	inlist.push_back(0);
	makeASC(tra->left,inlist,interp,Rinterp);
	inlist.pop_back();	
	inlist.push_back(1);
	makeASC(tra->left,inlist,interp,Rinterp);
	inlist.pop_back();	
	return ;
```

##### 输出编码文本

```cpp
while(data>>enter)
	out<<interp[enter]<<endl	//huffman编码中没有一个是包含另一个的，不用＋“#”间隔
```

##### 译码

```cpp
vector<char> list;
vector<int> currs;
vector<char> pres; 
while(data>>chas)
	list.push_back(chas);
for(auto i:list){
	if(i=="#")
		out<<Rinterp(currs)<<endl;
  		currs.clear();
 	else currs.push_back(i);
}
```

###编码转化

1. 可以01码每8bit转化为base64编码
2. 从网上刨了string到base64编码的转化，也可以把01码——ASCII码——base64码——ASCII码——

* but 01码转化成ASCII码可能要补0，补0的ASCII码转化为01码00会对应字符，

  把结尾字符串要补的0数目作为参数传递即可

* 先把01码变成string再调用即可

* ascii变成base64码要用到base64_chars函数——base64_chars[64]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"

##### 伪码

```cpp
void zo_to_base64(ifstream &in,outstring &out,int &remain){
	int a=0;
  	int i=0;
  	int j=0;
  	int newzo;
  	char alpha;
  	unsigned char char_array_3[3];
  	unsigned char char_array_4[4];	//0x00~0x3f
  	base64_chars[64]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";	
  	string ret;
 	while(cin>>newzo){
	alpha=alpah<<1+newzo;
   	a++;
    if(a==8)	{
    	char_array_3[i++]=alpha;
   	 	a=0;
    }
    if(i==3){
      char_array_4[0]=(char_array_3[0]&0xfc)>>2;
      char_array_4[1]=(char_array_3[0]&0x03)<<4+(char_array_3[1]&0xf0)>>4;
      char_array_4[2]=(char_array_3[1]&0x0f)<<2+(char_array_3[2]&0xc0)>>6;
      char_array_4[3]=char_array_3[2]&0x3f;
      i=0;
    }
    for(int k=0;k<3;k++){
 		ret+=base64_chars[char_array_4[k]];     
    }
  }
  	if(i){
  		if(a)	remain=8-a;
      	for(j=i;j<3;j++){
        
      	}
  }
}
```