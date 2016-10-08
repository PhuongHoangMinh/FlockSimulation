#ifndef BITMAP_H
#define BITMAP_H



#include <stdlib.h>
#include <iostream>
#include <gl/glut.h>
using namespace std;


#pragma pack(push, 1) 
typedef struct BITMAPFILEHEADER		// 비트맵 파일 헤더
{
	unsigned short bfType;		//bfType : BM Signature
	unsigned long bfSize;		//bfSize : 파일 크기
	unsigned short bfReserved1;
	unsigned short bfReserved2;
	unsigned long bfOffBits;	//bfOffBits : 데이터 시작 위치
} FileHdr;


typedef struct BITMAPINFOHEADER		// 비트맵 헤더
{
	unsigned long biSize;		//biSize ; 헤더 크기
	long biWidth;				//biWidth : 가로 크기
	long biHeight;				//biHeight : 세로 크기
	unsigned short biPlanes;
	unsigned short biBitCount;
	unsigned long biCompression;
	unsigned long biSizeImage;
	long biXPelsPerMeter;
	long biYPelsPerMeter;
	unsigned long biClrUsed;
	unsigned long biClrImportant;
} InfoHdr;


class Bitmap
{
	FileHdr filehdr;
	InfoHdr infohdr;
	unsigned char *pixel;

public:
	Bitmap(FILE *);			//Bitmap의 생성자

	BITMAPFILEHEADER FileHeader() {	return filehdr;	}
	BITMAPINFOHEADER InfoHeader() {	return infohdr;	}

	GLuint Bitmap2TextureName()const;

	~Bitmap();	
	
};

#pragma pack(pop) 
#endif