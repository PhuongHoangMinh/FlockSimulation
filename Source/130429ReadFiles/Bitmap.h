#ifndef BITMAP_H
#define BITMAP_H



#include <stdlib.h>
#include <iostream>
#include <gl/glut.h>
using namespace std;


#pragma pack(push, 1) 
typedef struct BITMAPFILEHEADER		// ��Ʈ�� ���� ���
{
	unsigned short bfType;		//bfType : BM Signature
	unsigned long bfSize;		//bfSize : ���� ũ��
	unsigned short bfReserved1;
	unsigned short bfReserved2;
	unsigned long bfOffBits;	//bfOffBits : ������ ���� ��ġ
} FileHdr;


typedef struct BITMAPINFOHEADER		// ��Ʈ�� ���
{
	unsigned long biSize;		//biSize ; ��� ũ��
	long biWidth;				//biWidth : ���� ũ��
	long biHeight;				//biHeight : ���� ũ��
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
	Bitmap(FILE *);			//Bitmap�� ������

	BITMAPFILEHEADER FileHeader() {	return filehdr;	}
	BITMAPINFOHEADER InfoHeader() {	return infohdr;	}

	GLuint Bitmap2TextureName()const;

	~Bitmap();	
	
};

#pragma pack(pop) 
#endif