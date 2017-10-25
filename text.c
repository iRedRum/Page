#include "typedefine.h"

int text(void)
{
	FILE *fp=fopen("1.txt","r");
	unsigned int bitmap[M]={0};
	char buff[1000];
	HPNode root=(HPNode)malloc(sizeof(HNode));
	root->num=0;
	root->next=NULL;
	root->nowp=NULL;
	root->prep=NULL;
	while(fgets(buff,1000,fp)!=NULL)
	{
		//printf("%s",buff);
		parseUrl(buff,root);
	}
	fclose(fp);
	SPNode temp=root->next;
	if(temp==NULL)
	{
		printf("No node\n");
	}
	for(;temp!=NULL;temp=temp->next)
	{
		//printf("--%d\n--%s\n",temp->num,temp->c);
		if(containUrl(temp->c,bitmap))
		{
			printf("--%s is had\n",temp->c);
		}
		else
		{
			addUrl(temp->c,bitmap);
			printf("--%s add\n",temp->c);
		}
	}
	return 0;
}
