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
	int nodenum;	//һ�λ����������У�����url��ռ�����ڵ��� 
	int maxnum=0;	//����url��ռ�����ڵ��� 
	while(fgets(buff,10000,fp)!=NULL)
	{
		//printf("%s",buff);
		nodenum=parseUrl(buff,root);	//�������������ش˴β�����URL��ռ���ڵ��� 
		if(maxnum<nodenum)		//�޸����ֵ 
		{
			maxnum=nodenum;
		}
			
	}
	fclose(fp);
	char *ctemp=(char *)malloc(sizeof(char)*maxnum*SNUM);	//�������ڵ�������URL�ݴ����� 
	int curnum;		//��ǰ������URL��� 
	bool flag=true;
	
	memset(ctemp,0,sizeof(char)*maxnum*SNUM);
	SPNode temp=root->next;
	//printf("%d",maxnum); 
	for(curnum=temp->num;temp!=NULL;temp=temp->next)
	{
		//printf("%s\n",temp->c);
		if(curnum==temp->num)		//�ñ��URL�ж���ڵ� 
		{
			if(flag)		//���ν���ѭ�� 
			{
				sprintf(ctemp,"%s",temp->c);	//���ν���ѭ���ȳ�ʼ��ctemp 
				flag=false;
			}
			else
			{
				sprintf(ctemp,"%s%s",ctemp,temp->c);	//ƴ�Ӷ���ڵ㹹��URL 
			}
		}
		else		//ǰһ�����URL�Ѿ���ȫ����ctemp��Ŀǰ��������һ�����URL�Ľڵ� 
		{
			if(!containUrl(ctemp,bitmap))	//���� 
			{
				addUrl(ctemp,bitmap);		//���ؼ��� 
			}
			fprintf(wfp,"%s\n",ctemp);		//�ı������� 
			memset(ctemp,0,sizeof(char)*maxnum*SNUM);	//���ctemp 
			sprintf(ctemp,"%s",temp->c);	//�����һ���URL 
			curnum=temp->num;			//���ĵ�ǰ��� 
		}
	}
	fprintf(wfp,"%s\n",ctemp);		//������һ��URL 
	
	return;

}
