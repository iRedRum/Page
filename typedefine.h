#ifndef TYPEDEFINE_H
#define TYPEDEFINE_H

#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

typedef int bool;
#define false 0
#define true 1

#define SNUM 20

#define M 10 
#define SHIFT 5
#define MASK 0x1F
//位图法的设定的数，使用unsigned int数组存储，从0开始
//每增加1，表示增加32位位图 

enum state 
{
	s0=0,s1,s2,s3,s4,s5,s6,s7,s8,s9,s10
};//定义自动机的状态 

typedef struct savenode
{
	int num;
	char c[SNUM];
	struct savenode * next;
}SNode,* SPNode; 

typedef struct headnode
{
	int num;
	struct savenode * next;
	struct savenode * nowp;
	struct savenode * prep;
}HNode,* HPNode;

//typedef unsigned int (*hash_function)(char*, unsigned int len);

//parseurl.c
void parseUrl(char* text,HPNode root);

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
