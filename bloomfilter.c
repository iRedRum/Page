#include "typedefine.h"
 
void setBit(int pos,unsigned int* bitmap)
{
	/*�������˼���� 
	int nBytePos=pos/32;
	//����ֽ�λ�� 
	int nBitPos=pos&31;
	//���λ��λ�� 
	unsigned short val=1<<nBitPos;
	 
	bitmap[nBytePos]=bitmap[nBytePos]|val;
	*/
	bitmap[pos>>SHIFT]|=(1<<(pos&MASK));
} 

bool getBit(int pos,unsigned int* bitmap)
{
	return bitmap[pos>>SHIFT]&(1<<(pos&MASK));
	//����bitmap��posλ����ĵ����ǲ���1
	//1�����棬0���ؼ� 
}

bool containUrl(char* url,int* bitmap)
{
	if(url==NULL)
		return false;
	bool ret=true;
	//��������url���ַ�������K�ι�ϣ���ж϶�Ӧλ�õ�
	//����ֵ�ǲ����Ѿ����ڣ�����������ˣ����ǰ�����
	//�����һ�������ھ���û�а������url�ַ���
	int len=strlen(url);
	ret=ret&&getBit(RSHash(url,len)%(M*32),bitmap);
	ret=ret&&getBit(JSHash(url,len)%(M*32),bitmap);
	ret=ret&&getBit(PJWHash(url,len)%(M*32),bitmap);	
	ret=ret&&getBit(ELFHash(url,len)%(M*32),bitmap);	
	ret=ret&&getBit(BKDRHash(url,len)%(M*32),bitmap);
	ret=ret&&getBit(SDBMHash(url,len)%(M*32),bitmap);
	ret=ret&&getBit(DJBHash(url,len)%(M*32),bitmap);
	ret=ret&&getBit(DEKHash(url,len)%(M*32),bitmap);
	ret=ret&&getBit(BPHash(url,len)%(M*32),bitmap);
	ret=ret&&getBit(FNVHash(url,len)%(M*32),bitmap);
	ret=ret&&getBit(APHash(url,len)%(M*32),bitmap);
	
	return ret; 
}

void addUrl(char* url,int* bitmap) 
{
	int len=strlen(url);
	setBit(RSHash(url,len)%(M*32),bitmap);
	setBit(JSHash(url,len)%(M*32),bitmap);
	setBit(PJWHash(url,len)%(M*32),bitmap);
	setBit(ELFHash(url,len)%(M*32),bitmap);
	setBit(BKDRHash(url,len)%(M*32),bitmap);
	setBit(SDBMHash(url,len)%(M*32),bitmap);
	setBit(DJBHash(url,len)%(M*32),bitmap);
	setBit(DEKHash(url,len)%(M*32),bitmap);
	setBit(BPHash(url,len)%(M*32),bitmap);
	setBit(FNVHash(url,len)%(M*32),bitmap);
	setBit(APHash(url,len)%(M*32),bitmap); 
}

void BloomFilter(char** urls,int ulen,int* bitmap)
{
	int i;
	for(i=0;i<ulen;i++)
	{
		if(containUrl(urls[i],bitmap))
		{
		//������url�Ѿ���������
			printf("Contains:%s",urls[i]);
			continue;
		}
		
		addUrl(urls[i],bitmap);
		//û�еĻ�����������url��λͼ���� 
			 
	}
}

