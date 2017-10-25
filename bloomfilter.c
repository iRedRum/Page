#include "typedefine.h"
 
void setBit(int pos,unsigned int* bitmap)
{
	/*具体的意思就是 
	int nBytePos=pos/32;
	//算出字节位置 
	int nBitPos=pos&31;
	//算出位的位置 
	unsigned short val=1<<nBitPos;
	 
	bitmap[nBytePos]=bitmap[nBytePos]|val;
	*/
	bitmap[pos>>SHIFT]|=(1<<(pos&MASK));
} 

bool getBit(int pos,unsigned int* bitmap)
{
	return bitmap[pos>>SHIFT]&(1<<(pos&MASK));
	//返回bitmap中pos位上面的到底是不是1
	//1返回真，0返回假 
}

bool containUrl(char* url,int* bitmap)
{
	if(url==NULL)
		return false;
	bool ret=true;
	//接下来对url的字符串进行K次哈希，判断对应位置的
	//布尔值是不是已经存在，如果都存在了，就是包含了
	//如果有一个不存在就是没有包含这个url字符串
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
		//如果这个url已经包含过了
			printf("Contains:%s",urls[i]);
			continue;
		}
		
		addUrl(urls[i],bitmap);
		//没有的话，就添加这个url到位图里面 
			 
	}
}

