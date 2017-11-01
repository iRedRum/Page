#include "typedefine.h"

int parseUrl(char* text,HPNode root)
{
	enum state s;//保存本次匹配的状态 
	s=0;
	
	int texti=0;//读入的文本的匹配指针
	int savei=SNUM;
	//上个节点存储完毕，进行新的节点申请进行存储
	//为了不同缓冲区的读取 
	int nodenum=0;	//存放当前单个URL的节点数 
	int maxnum=0;		//存档单个URL最大的节点数 
	//存储的指针，不能大于存储的大小SNUM 
	while(text[texti]!='\0')
	{

		switch(s)
		{
			case 0:
				if(text[texti]=='<')
					s=1;
				texti++;
				break;
			case 1:
				if(text[texti]=='a')
					s=2;
				else if(text[texti]==' ')
					s=1;
				else
					s=0;
				texti++; 
				break;
			case 2:
				if(text[texti]=='>')
					s=0;
				else if(text[texti]=='h')
					s=3;
				else
					s=2;
				texti++;
				break;
			case 3:
				if(text[texti]=='r')
					s=4;
				else if(text[texti]=='>')
					s=0;
				else
					s=2;
				texti++; 
				break;
			case 4:
				if(text[texti]=='e')
					s=5;
				else if(text[texti]=='>')
					s=0;
				else
					s=2;
				texti++;
				break;
			case 5:
				if(text[texti]=='f')
					s=6;
				else if(text[texti]=='>')
					s=0;
				else
					s=2;
				texti++;
				break;
			case 6:
				if(text[texti]=='=')
					s=7;
				else if(text[texti]=='>')
					s=0;
				else
					s=2;
				texti++;
				break;
			case 7:
				if(text[texti]=='"')
					s=9;
				else if(text[texti]==' ')
					s=7;
				else if(text[texti]=='>')	//到底应该返回什么状态 
					s=0;					//原来为else s=0; 
				else						//网页应该都是正确的语法 
					s=2;					//因此特殊的情况应该可以不考虑 
				texti++;
				break;
			/*case 11:
			 	if(text[texti]=='h')
					s=12;
				else
					s=2;
				texti++;
				break;
			case 12:
			 	if(text[texti]=='t')
					s=13;
				else
					s=2;
				texti++;
				break;
			case 13:
			 	if(text[texti]=='t')
					s=14;
				else
					s=2;
				texti++;
				break;
			case 14:
			 	if(text[texti]=='p')
					s=15;
				else
					s=2;
				texti++;
				break;
			case 15:
			 	if(text[texti]==':')
					s=16;
				else
					s=2;
				texti++;
				break;
			case 16:
			 	if(text[texti]=='/')
					s=8;
				else
					s=2;
				texti++;
				break;
			case 8:
				if(text[texti]=='/')
					s=9; 
				else
					s=2;
				texti++; 
				break;
			*/
			case 9:
	//此时已经匹配到href="
	//在此之后存放的就是我们需要的URL信息 
	//因此在这个状态下开始进行url的存储 
				if((text[texti]>='a'&&text[texti]<='z')
				||(text[texti]>='A'&&text[texti]<='Z')
				||(text[texti]>='0'&&text[texti]<='9')
				||text[texti]=='.'
				||text[texti]=='_'
				||text[texti]=='/'
				||text[texti]=='-'
				||text[texti]==':')
				{
					if(root->nowp==NULL)
					//根节点需要进行额外的处理 
					{
						savei=0; 
						SPNode tmp=(SPNode)malloc(sizeof(SNode));
						nodenum++;		//节点数增加 
						tmp->next=NULL;
						tmp->num=root->num+1;
						//表示这个缓冲区里面的第几个url
						tmp->c[savei]=text[texti];
						//存储url的字符 
						root->next=tmp;
						root->nowp=tmp;
						savei++;
					}
					else if((root->nowp->num-1)==root->num
						&&savei==(SNUM-1))
					//同个url节点的存储空间满了，需要申请新的节点 
					{
						root->nowp->c[savei]=0;
						//给上一个进行结尾加入终止符号 
						SPNode tmp=(SPNode)malloc(sizeof(SNode));
						nodenum++;	// 节点数增加
						savei=0;
						tmp->next=NULL;
						tmp->num=root->nowp->num;
						//表示这个缓冲区里面的第几个url
						tmp->c[savei]=text[texti];
						//存储url的字符 
						root->nowp->next=tmp;
						root->nowp=tmp; 
						savei++;
					}
					else if (root->nowp->num==root->num
						  &&savei==SNUM)
					//上一个url已经存储结束，需要进行新的url存储 
					{
						SPNode tmp=(SPNode)malloc(sizeof(SNode));
						nodenum++;	//节点数增加 
						savei=0;
						tmp->next=NULL;
						tmp->num=root->nowp->num+1;	
						//表示这个缓冲区里面的第几个url
						tmp->c[savei]=text[texti];
						//存储url的字符
						root->nowp->next=tmp;
						root->nowp=tmp; 
						savei++;
					}
					else
					//除此之外就是同一个url,而且节点没有存满
					//直接继续存储就可以了 
					{
						root->nowp->c[savei]=text[texti];
						savei++;
					}
				}
				//匹配成功的状态,进行缓存 
				else if(text[texti]=='"')
				{
					root->nowp->c[savei]=0;
					//加入截止符号 
				 	root->num++;
					 //匹配成功总数应该增加 
				 	root->prep=root->nowp;
					 //匹配成功后前置指针指向这个当前指针 
					savei=SNUM;
					if(nodenum > maxnum)	
					//保存最大的节点数 
					{
						maxnum=nodenum;
					}
					nodenum=0;			
					//当前节点数归零 
					s=10;
					//匹配成功 
				}
				else
				{
					if(root->prep==NULL)
					{
						root->next=NULL;
						root->nowp=NULL;
					}
					else
					{
						root->nowp=root->prep;
						root->nowp->next=NULL;
					}
					
					//之前存储的内容全部不要了，直接跳回上一个节点
					//这里其实负责的话，应该把之前的节点释放掉好点
					nodenum=0;
					//每次存储完一个url进行一次置0的操作，之后继续计算最大节点数 
					savei=SNUM;
					//把存储的指针指向满了的地方最后
					//方便进行之后新的url的插入时候的条件判断  
					 
					s=0;
				} 
				//直接跳转到最开始的匹配状态 
				texti++;
				break;
			case 10:
				
				//存储url链接 
				s=0;
				//直接进行状态跳转，不用进行匹配的指针texti偏移了
				//因为状态9已经进行了匹配的指针偏移 
				break;
			default:
				break;
		}
	 } 

	return maxnum; 
}
