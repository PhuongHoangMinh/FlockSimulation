#include "Bitmap.h"


Bitmap::Bitmap(FILE *file)
{
	int i,j;


	fread(&filehdr, sizeof(BITMAPFILEHEADER), 1, file);
	fread(&infohdr, sizeof(BITMAPINFOHEADER), 1, file);

	pixel = new (unsigned char [infohdr.biWidth*infohdr.biHeight*3]);

	for(i=0;i<infohdr.biWidth*infohdr.biHeight;i++)
		for(j=0;j<3;j++)
			fread(&pixel[3*i-j+2], 1, 1, file);			

	//cout<< "Width " << infohdr.biWidth<< "Height " << infohdr.biHeight;
	
	
}

GLuint Bitmap::Bitmap2TextureName()const
{
	GLuint m_textName;

	glGenTextures(1, &m_textName);
	glBindTexture(GL_TEXTURE_2D, m_textName);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);		
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, infohdr.biWidth, infohdr.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, &pixel[0]);
	

	return m_textName;

}


Bitmap::~Bitmap()
{
	delete pixel;
}