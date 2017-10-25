#include "typedefine.h"

void parseUrl(char* text,HPNode root)
{
	enum state s;//���汾��ƥ���״̬ 
	s=0;
	
	int texti=0;//������ı���ƥ��ָ��
	int savei=SNUM;
	//�洢��ָ�룬���ܴ��ڴ洢�Ĵ�СSNUM 
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
	//��ʱ�Ѿ�ƥ�����href="(���Լ��Ϻܶ�ո�)
	//Ȼ��������Ϊֻ��ƥ�䵽���·����Ҳ����
	//href="/..������ȷ��url��ʼ
	//���ԣ�֮��ƥ����ַ�Ӧ����'/' 
				if(text[texti]==' ')
					s=8;
				else if(text[texti]=='/')
					s=9; 
				else
					s=0;
				texti++; 
				break;
			case 9:
	//���״̬�¿�ʼ����url�Ĵ洢 
				if((text[texti]>='a'&&text[texti]<='z')
				||(text[texti]>='A'&&text[texti]<='Z')
				||(text[texti]>='0'&&text[texti]<='9')
				||text[texti]=='.'
				||text[texti]=='_'
				||text[texti]=='/'
				||text[texti]=='-')
				{
					if(root->nowp==NULL)
					//���ڵ���Ҫ���ж���Ĵ��� 
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
					//ͬ��url�ڵ�Ĵ洢�ռ����ˣ���Ҫ�����µĽڵ� 
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
					//��һ��url�Ѿ��洢��������Ҫ�����µ�url�洢 
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
					//����֮�����ͬһ��url,���ҽڵ�û�д���
					//ֱ�Ӽ����洢�Ϳ����� 
					{
						root->nowp->c[savei]=text[texti];
						savei++;
					}
				}
				//ƥ��ɹ���״̬,���л��� 
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
						//�Ѵ洢��ָ��ָ�����˵ĵط����
						//�������֮���µ�url�Ĳ���ʱ��������ж� 
					}
					else
					{
						root->nowp->c[savei]='\0';
						savei=SNUM;
						//�Ѵ洢��ָ��ָ�����˵ĵط����
						//�������֮���µ�url�Ĳ���ʱ��������ж�  
					}*/
					root->nowp->c[savei]=0;
				 	root->num++;//ƥ��ɹ�����Ӧ������ 
				 	root->prep=root->nowp;//ƥ��ɹ���ǰ��ָ��ָ�������ǰָ�� 
					savei=SNUM;
					s=10;//ƥ��ɹ� 
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
					
					//֮ǰ�洢������ȫ����Ҫ�ˣ�ֱ��������һ���ڵ�
					//������ʵ����Ļ���Ӧ�ð�֮ǰ�Ľڵ��ͷŵ��õ�
					
					savei=SNUM;
					//�Ѵ洢��ָ��ָ�����˵ĵط����
					//�������֮���µ�url�Ĳ���ʱ��������ж�  
					 
					s=0;
				} 
				//ֱ����ת���ʼ��ƥ��״̬ 
				texti++;
				break;
			case 10:
				
				//�洢url���� 
				s=0;
				//ֱ�ӽ���״̬��ת�����ý���ƥ���ָ��textiƫ����
				//��Ϊ״̬9�Ѿ�������ƥ���ָ��ƫ�� 
				break;
			default:
				break;
		}
	 } 
	 
	//return root; 
}
