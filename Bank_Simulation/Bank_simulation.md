[TOC]

#### 1. 代码构思

```
事件分为四种类型:0——事件到达，1——事件从队伍1离开，2——从队伍2离开，3——从队伍1切换到2
凡是离开都要renew total,totaltime,进入customer++;
0——插入事件(en.OccurTime+interval<closetime)：状态0，time=en.Occur+interval
 ——新到customer插入wait1
 ——if(wait1.length==1&&(QueueLength(wait2)==0?1:(total+GetHead(wait2)->bill<0)))
	 ——if:total+GetHead(wait1)->bill>=0:
		插入事件(wait1.length=1)：当前的从队伍1离开——状态=1，time=en.Occur+qnew->duration
 	 ——else:total+GetHead(wait1)->bill<0:
 		插入事件：状态=3,time=en.Occur;
//1这里有必然触发的事件吗
1——if(wait2!=0&&total+wait2.head->bill>=0)
	  	插入事件：状态=2，time=en.occur+wait2.head->duration
   else  if(wait1.length!=0)：
  			if(total+gethead(wait1)->bill>=0)
  				插入事件：状态=1，time=en.occur+gethead(wait1)->duration
  			else 插入事件：状态=3，time=en.occur
  else 啥都干不了啦
2——if(wait2!=0&&total+wait2.head->bill>=0)	//wait2还能接着出先出wait2
	  	插入事件：状态=2，time=en.occur+wait2.head->duration 
   else if(wait1.length!=0)：	//wait1不空的话能出出，不能移走
  			if(total+gethead(wait1)->bill>=0)
  				插入事件：状态=1，time=en.occur+gethead(wait1)->duration
  			else 插入事件：状态=3，time=en.occur
3——if(wait1.length!=0)：	//wait1不空的话能出出，不能移走
  			if(total+gethead(wait1)->bill>=0)
  				插入事件：状态=1，time=en.occur+gethead(wait1)->duration
  			else 插入事件：状态=3，time=en.occur
```

####2.艰难debug

1. rand生成一样的bill和interval

* srand()写在循环外面

2. customer=0

- [x] 维护：insert\del\init 都要改变head/tail

3. 到达即离开

- [x] duration=rand()%10+1


4. 计算人均用时

* 结束时，对wait2中的每个队伍wait1中的成员a最后都会分到wait2，total+=closetime-a->arrivtime;

5. QueueLength(wait2)异常，

* whyQueueLength(wait1)没问题，

* a=0xFFFFFFFFFFF7还会进行a!=NULL判断，说明rear->next!=NULL;没分配？

  ```
  //将wait1首转入wait2,
  qnew=GetHead(wait1);
  DelQueue(wait1);	//这步作死把qnew释放了，qnew变为野指针,后面QueueLength(wait2)赋给a,会出现a=0xF..F7
  EnQueue(wait2,qnew);
  ```

* DelQueu()定义中杠掉free(fr)即可

6. 一个老问题——循环中用链表长度做边界，而这个边界是会随着链表的删减变动的呀！

```
	for (int i = 0; i < QueueuLength(wait2); i++) {	
		Totaltime += closetime - GetHead(wait2)->Arrivtime;
		DelQueue(wait2);
		printf("这是第%d次\n", i);
	}	
//解决方案：for循环前把QueueLength(wait2)赋给变量，后作为边界
```



####3.代码解释



####4.运行结果（从能跑开始)

#####只有借款

```
下面这个没细想,mkQNode函数中令
mk->bill=rand()%(max_save-max_lend)+(max_save-max_lend)/2,
但可以说明入队1没问题
实际应是
mk->bill=rand()%(max_save-max_lend)+max_lend,才有借款取款,更正后的运行结果在此之后
且为了能出现从1移到2，total初始化=0；
```

![](C:\Users\c1826\Pictures\数据结构实验\bank.png)

| time | customer_number           | total        | totaltime      |
| ---- | ------------------------- | ------------ | -------------- |
| 0    | 1(1号，daration=6,bill=24)  | 1000         | 0              |
| 5    | 2(2号duration=6,bill=31)   | 1000         | 0              |
| 6    | 2(1号离开)                   | 1000+24=1024 | 0+(6-0)=6      |
| 10   | 3(3号，duration=3,bill=28)  | 1024         | 6              |
| 12   | 3(2号离开)                   | 1024+31=1055 | 6+(12-5)=13    |
| 15   | 3(3号离开)                   | 1055+28=1083 | 13+(15-10)=18  |
| 17   | 4(4号，duration=9,bill=18)  | 1083         | 18             |
| 24   | 5(5号，duration=10,bill=16) | 1083         | 18             |
| 25   | 6(6号，duration=3,bill=18)  | 1083         | 18             |
| 26   | 6(4号离开)                   | 1083+18=1101 | 18+(26-17)=27  |
| 27   | 7(7号，duration=6,bill=28)  | 1101         | 27             |
| 36   | 7(5号离开)                   | 1101+16=1117 | 27+(36-24)=39  |
| 39   | 7(6号离开)                   | 1117+18=1135 | 39+(39-25)=53  |
| 45   | 7(7号离开)                   | 1135+28=1163 | 53+(45-27)=71  |
| 总    | 7                         | 1163         | 71；平均用时71/10=7 |

更正后，

#####借款+还款

但是因为上面的问题5、6换队操作QueueLength(wait2)会出问题

![](C:\Users\c1826\Pictures\数据结构实验\取款.png)

#####借款+还款+换队+(从二队出队失败)

解决5.6后，可计算答案的正确性，

![](C:\Users\c1826\Pictures\数据结构实验\finalbank.png)

末尾的aaa，wait2长度，这是第i次是debug所用，但这个例子比较难出，就不更了

相关代码：

![](C:\Users\c1826\Pictures\数据结构实验\debug.png)

115行调用了如下QueueLength()，才会出现aaa aaa aaa



![](C:\Users\c1826\Pictures\数据结构实验\dede.png)

##### 可从二队出队版

![](C:\Users\c1826\Pictures\数据结构实验\Ntype==2有问题.png)

![](C:\Users\c1826\Pictures\数据结构实验\Ntype2.png)

上面在5和13到达的同时在16离开，是因为4号离开后，wait1=0,wait2=2,在wati2出队的时候错误地让这期间到达的5号也出队，修改到达即离开的限定条件为

```
QueueLength(wait1)==1&&(QueueLength(wait2)==0?1:(total+GetHead(wait2)->bill<0)
```

##### 规范wait1到达即出队条件后版

![](C:\Users\c1826\Pictures\数据结构实验\期待下一个错误.png)
