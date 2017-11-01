#ifndef TYPEDEFINE_H
#define TYPEDEFINE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

typedef int bool;
#define false 0
#define true 1

#define SNUM 10

#define M 10 
#define SHIFT 5 
#define MASK 0x1F
//λͼ�����趨������ʹ��unsigned int����洢����0��ʼ
//ÿ����1����ʾ����32λλͼ 

enum state 
{
	s0=0,s1,s2,s3,s4,s5,s6,s7,s8,s9,s10
};//�����Զ�����״̬ 

typedef struct savenode//url�Ĵ洢�ṹ 
{
	int num;
	//��ǰ�ڵ����ڵڼ���url
	 
	char c[SNUM];
	//url���ַ� 
	
	struct savenode * next;
	
}SNode,* SPNode; 

typedef struct headnode//url�洢�ṹ��ͷ��� 
{
	int num;
	//�Ѿ��洢�Ľڵ���Ŀ 
	
	struct savenode * next;
	//ͷ���ָ�����һ���ڵ�
	 
	struct savenode * nowp;
	//��ǰ���в����Ľڵ�
	 
	struct savenode * prep;
	//��һ����Ҫ���в����Ľڵ� 
	
}HNode,* HPNode;

//typedef unsigned int (*hash_function)(char*, unsigned int len);

//parseurl.c
int parseUrl(char* text,HPNode root);

//bloomfilter.c
void setBit(int pos,unsigned int* bitmap);
bool getBit(int pos,unsigned int* bitmap);
bool containUrl(char* url,int* bitmap);
void addUrl(char* url,int* bitmap);
void BloomFilter(char** urls,int ulen,int* bitmap);

//GeneralHashFunctions.c 
unsigned int RSHash  (const char* str, unsigned int len);
unsigned int JSHash  (const char* str, unsigned int len);
unsigned int PJWHash (const char* str, unsigned int len);
unsigned int ELFHash (const char* str, unsigned int len);
unsigned int BKDRHash(const char* str, unsigned int len);
unsigned int SDBMHash(const char* str, unsigned int len);
unsigned int DJBHash (const char* str, unsigned int len);
unsigned int DEKHash (const char* str, unsigned int len);
unsigned int BPHash  (const char* str, unsigned int len);
unsigned int FNVHash (const char* str, unsigned int len);
unsigned int APHash  (const char* str, unsigned int len);

#endif 
