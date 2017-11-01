#include "typedefine.h"

int text(void)
{
	FILE *fp=fopen("1.txt","r");
	FILE *wfp=fopen("2.txt","w");
	unsigned int bitmap[M]={0};
	char buff[10000];
	HPNode root=(HPNode)malloc(sizeof(HNode));
	root->num=0;
	root->next=NULL;
	root->nowp=NULL;
	root->prep=NULL;
	int nodenum;	//一次缓冲区操作中，单个url所占的最大节点数 
	int maxnum=0;	//所有url所占的最大节点数 
	while(fgets(buff,10000,fp)!=NULL)
	{
		//printf("%s",buff);
		nodenum=parseUrl(buff,root);	//处理缓冲区，返回此次操作中URL所占最大节点数 
		if(maxnum<nodenum)		//修改最大值 
		{
			maxnum=nodenum;
		}
			
	}
	fclose(fp);
	char *ctemp=(char *)malloc(sizeof(char)*maxnum*SNUM);	//根据最大节点数建立URL暂存数组 
	int curnum;		//当前处理到的URL编号 
	bool flag=true;
	
	memset(ctemp,0,sizeof(char)*maxnum*SNUM);
	SPNode temp=root->next;
	//printf("%d",maxnum); 
	for(curnum=temp->num;temp!=NULL;temp=temp->next)
	{
		//printf("%s\n",temp->c);
		if(curnum==temp->num)		//该编号URL有多个节点 
		{
			if(flag)		//初次进入循环 
			{
				sprintf(ctemp,"%s",temp->c);	//初次进入循环先初始化ctemp 
				flag=false;
			}
			else
			{
				sprintf(ctemp,"%s%s",ctemp,temp->c);	//拼接多个节点构成URL 
			}
		}
		else		//前一个编号URL已经完全存入ctemp，目前读到了下一个编号URL的节点 
		{
			if(!containUrl(ctemp,bitmap))	//查重 
			{
				addUrl(ctemp,bitmap);		//非重加入 
			}
			fprintf(wfp,"%s\n",ctemp);		//文本输出结果 
			memset(ctemp,0,sizeof(char)*maxnum*SNUM);	//清空ctemp 
			sprintf(ctemp,"%s",temp->c);	//存放下一编号URL 
			curnum=temp->num;			//更改当前编号 
		}
	}
	fprintf(wfp,"%s\n",ctemp);		//输出最后一个URL 
	
	return;

}
