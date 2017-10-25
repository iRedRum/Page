#include "typedefine.h"

void parseUrl(char* text,HPNode root)
{
	enum state s;//保存本次匹配的状态 
	s=0;
	
	int texti=0;//读入的文本的匹配指针
	int savei=SNUM;
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
					s=8;
				else if(text[texti]==' ')
					s=7;
				else
					s=0;
				texti++;
				break;
			case 8:
	//此时已经匹配的是href="(可以加上很多空格)
	//然后我们认为只有匹配到相对路径，也就是
	//href="/..才是正确的url开始
	//所以，之后匹配的字符应该是'/' 
				if(text[texti]==' ')
					s=8;
				else if(text[texti]=='/')
					s=9; 
				else
					s=0;
				texti++; 
				break;
			case 9:
	//这个状态下开始进行url的存储 
				if((text[texti]>='a'&&text[texti]<='z')
				||(text[texti]>='A'&&text[texti]<='Z')
				||(text[texti]>='0'&&text[texti]<='9')
				||text[texti]=='.'
				||text[texti]=='_'
				||text[texti]=='/'
				||text[texti]=='-')
				{
					if(root->nowp==NULL)
					//根节点需要进行额外的处理 
					{
						savei=0; 
						SPNode tmp=(SPNode)malloc(sizeof(SNode));
						tmp->next=NULL;
						tmp->num=root->num+1;
						tmp->c[savei]=text[texti];
						root->next=tmp;
						root->nowp=tmp; 
						savei++;
					}
					else if((root->nowp->num-1)==root->num
						&&savei==(SNUM-1))
					//同个url节点的存储空间满了，需要申请新的节点 
					{
						root->nowp->c[savei]=0;
						SPNode tmp=(SPNode)malloc(sizeof(SNode));
						savei=0;
						tmp->next=NULL;
						tmp->num=root->nowp->num;
						tmp->c[savei]=text[texti];
						root->nowp->next=tmp;
						root->nowp=tmp; 
						savei++;
					}
					else if (root->nowp->num==root->num
						  &&savei==SNUM)
					//上一个url已经存储结束，需要进行新的url存储 
					{
						SPNode tmp=(SPNode)malloc(sizeof(SNode));
						savei=0;
						tmp->next=NULL;
						tmp->num=root->nowp->num+1;
						tmp->c[savei]=text[texti];
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
					/*if(savei==SNUM)
					{
						SPNode tmp=(SPNode)malloc(sizeof(SNode));
						savei=0;
						tmp->next=NULL;
						tmp->num=root->nowp->num;
						tmp->c[savei]='\0';
						root->nowp->next=tmp;
						root->nowp=tmp;
						
						savei=SNUM;
						//把存储的指针指向满了的地方最后
						//方便进行之后新的url的插入时候的条件判断 
					}
					else
					{
						root->nowp->c[savei]='\0';
						savei=SNUM;
						//把存储的指针指向满了的地方最后
						//方便进行之后新的url的插入时候的条件判断  
					}*/
					root->nowp->c[savei]=0;
				 	root->num++;//匹配成功总数应该增加 
				 	root->prep=root->nowp;//匹配成功后前置指针指向这个当前指针 
					savei=SNUM;
					s=10;//匹配成功 
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
	 
	//return root; 
}
