#include "StdAfx.h"
#include "Bmp.h"


CBmp::CBmp(void)
{
}
/*********************************************************
** ������:
** �䡡��: x,y,n
**������x---ͼ����
**������y---ͼ��߶�
**������n---ͼ��λ��
** �䡡��: ��
**������
** ��������:
** ȫ�ֱ���:
** ����ģ��:
** ������:
** �ա���:
** �ޡ���:
**      ��¼1:
**      ��¼2:
** �ա���:
** ��  ��:
*******************************************************/

CBmp::CBmp(int x, int y, int n)
{
	
	if(n==8)
	{
		this->m_rgbQuad=(RGBQUAD *)malloc(265*4);
		this->m_bmpData=(BYTE *)malloc(((((x*8)+31)&~31)/8)*y);
	}
	
	if (n==24)
	{
		this->m_bmpData=(BYTE *)malloc(((((x*24)+31)&~31)/8)*y);

	}
}



CBmp::~CBmp(void)
{
	this->ReleaseBmp();
}


void CBmp::set_m_fXPositionInDC(float fXPosition)
{
	this->m_fXPositionInDC=fXPosition;
}
void CBmp::set_m_fYPositionInDC(float fYPostion)
{
	this->m_fYPositionInDC=fYPostion;
}

float CBmp::get_m_fXPositionInDC()
{
	return this->m_fXPositionInDC;
}
float CBmp::get_m_fYPositionInDC()
{
	return this->m_fYPositionInDC;
}


void CBmp::LoadBmp(CString m_strFileName)
{
	FILE *fp=fopen(m_strFileName,"rb");
	fread(&(this->m_bmpFileHeader),sizeof(BITMAPFILEHEADER),1,fp);
	fread(&(this->m_bmpInfoHeader),sizeof(BITMAPINFOHEADER),1,fp);
	int dstBmpSizeImage=((((this->m_bmpInfoHeader.biWidth*this->m_bmpInfoHeader.biBitCount)
		                 +31)&~31)/8)*this->m_bmpInfoHeader.biHeight;                                 //ͼ�����ش�С

	if(this->m_bmpInfoHeader.biBitCount!=8&&this->m_bmpInfoHeader.biBitCount!=24)
	{

	}
	if (this->m_bmpInfoHeader.biBitCount==8)
	{
		this->m_rgbQuad=new RGBQUAD[256];
		fread((this->m_rgbQuad),256*4,1,fp);
		int m_bmpSize=dstBmpSizeImage;
		this->m_bmpData=new BYTE[m_bmpSize];
		fread(this->m_bmpData,m_bmpSize,1,fp);

	}
	else if (this->m_bmpInfoHeader.biBitCount==24)
	{
		int m_bmpSize=dstBmpSizeImage;
		this->m_bmpData=new BYTE[m_bmpSize];
		fread(this->m_bmpData,m_bmpSize,1,fp);
	}
	fclose(fp);
}

void CBmp::SaveBmp(CString m_strFileName)
{
	FILE *fp=fopen(m_strFileName,"wb");
	int dstBmpSizeImage=((((this->m_bmpInfoHeader.biWidth*
		                 this->m_bmpInfoHeader.biBitCount)+31)&~31)/8)*this->m_bmpInfoHeader.biHeight;    //ͼ�����ش�С

	fwrite(&(this->m_bmpFileHeader),sizeof(this->m_bmpFileHeader),1,fp);
	fwrite(&(this->m_bmpInfoHeader),sizeof(this->m_bmpInfoHeader),1,fp);
	if(this->m_bmpInfoHeader.biBitCount!=8&&this->m_bmpInfoHeader.biBitCount!=24)
	{

	}
	if (this->m_bmpInfoHeader.biBitCount==8)
	{
		fwrite((this->m_rgbQuad),256*4,1,fp);               //8λͼƬ��ɫ���СΪ256*4
		int m_bmpSize=dstBmpSizeImage;
		
		fwrite(this->m_bmpData,m_bmpSize,1,fp);

	}
	else if (this->m_bmpInfoHeader.biBitCount==24)
	{
		int m_bmpSize=dstBmpSizeImage;
		
		fwrite(this->m_bmpData,1,m_bmpSize,fp);
	}
	fclose(fp);
}
bool CBmp::IsNull()
{
	if (this->m_bmpInfoHeader.biHeight!=0&&this->m_bmpInfoHeader.biWidth!=0)
	{
		return false;
	}
	else
	{
		return true;
	}
}
void CBmp::ReleaseBmp()
{
	memset(&(this->m_bmpFileHeader),0,sizeof(this->m_bmpFileHeader));
	memset(&(this->m_bmpInfoHeader),0,sizeof(this->m_bmpInfoHeader));
	if (this->m_bmpInfoHeader.biBitCount==8)
	{
		delete [] this->m_rgbQuad;
		delete [] this->m_bmpData;
	}
	else if (this->m_bmpInfoHeader.biBitCount==24)
	{
		delete [] this->m_bmpData;
	}
	
}

void CBmp::Draw(HDC hdc, int x, int y)
{
	BITMAPINFO *m_bitMapInfo=(BITMAPINFO *)malloc(sizeof(this->m_bmpInfoHeader)+256*4);      //�ο�BITMAPINFO�ṹ������λͼ��Ϣͷ�͵�ɫ��
	
	memcpy(m_bitMapInfo,&(this->m_bmpInfoHeader),sizeof(this->m_bmpInfoHeader));
	if (this->m_bmpInfoHeader.biBitCount==8)
	{
		memcpy(m_bitMapInfo->bmiColors,this->m_rgbQuad,
			sizeof(this->m_rgbQuad)*256
			);
	}
	
	SetDIBitsToDevice(hdc,x,y,this->m_bmpInfoHeader.biWidth,
		this->m_bmpInfoHeader.biHeight,0,0,0,
		this->m_bmpInfoHeader.biHeight,this->m_bmpData,
		m_bitMapInfo, DIB_RGB_COLORS);

	set_m_fXPositionInDC(0);
	set_m_fYPositionInDC(0);
	free(m_bitMapInfo);
	
}

void CBmp::Draw(HDC hdc, int x, int y, int nwidth, int nheight)
{
	BITMAPINFO *m_bitMapInfo=(BITMAPINFO *)malloc(sizeof(this->m_bmpInfoHeader)+256*4);      //�ο�BITMAPINFO�ṹ������λͼ��Ϣͷ�͵�ɫ��

	memcpy(m_bitMapInfo,&(this->m_bmpInfoHeader),sizeof(this->m_bmpInfoHeader));
	if (this->m_bmpInfoHeader.biBitCount==8)
	{
		memcpy(m_bitMapInfo->bmiColors,this->m_rgbQuad,
			sizeof(this->m_rgbQuad)*256
			);
	}
	SetStretchBltMode(hdc,COLORONCOLOR);
	StretchDIBits(hdc,x,y,nwidth,nheight,0,0,
		          this->m_bmpInfoHeader.biWidth,this->m_bmpInfoHeader.biHeight,
				  this->m_bmpData,m_bitMapInfo,DIB_RGB_COLORS, SRCCOPY);

	set_m_fXPositionInDC(x);
	set_m_fYPositionInDC(y);
	

	free(m_bitMapInfo);

}

void CBmp::DrawCenter(HWND hWnd, HDC hdc, int nwidth, int nheight)
{
	int m_nXPosition;    //��ʼ��X������                                                        
	int m_nYPosition;    //��ʼ��Y������

	CRect m_rc;
	GetClientRect(hWnd,&m_rc);

	m_nXPosition=(m_rc.Width()-nwidth)/2;
	m_nYPosition=(m_rc.Height()-nheight)/2;

	Draw(hdc, m_nXPosition, m_nYPosition, nwidth, nheight);

}



void CBmp::Resize(CBmp *dstBmp,int nWidth, int nHeight)
{
	float fWidthRate=float(nWidth)/float(this->m_bmpInfoHeader.biWidth);               //������ű���
	float fHeightRate=float(nHeight)/float(this->m_bmpInfoHeader.biHeight);            //�߶����ű���

	int dstBmpSizeImage=((((nWidth*this->m_bmpInfoHeader.biBitCount)+31)&~31)/8)*nHeight;                //Ŀ��ͼƬ���ݴ�С
	int nScanWidth=((((nWidth*this->m_bmpInfoHeader.biBitCount)+31)&~31)/8);           //windows ɨ���У�4�ֽڶ���

	memcpy(&(dstBmp->m_bmpFileHeader),&(this->m_bmpFileHeader),sizeof(this->m_bmpFileHeader));
	if (this->m_bmpInfoHeader.biBitCount==8)
	{
		dstBmp->m_bmpFileHeader.bfSize=14+40+256*4+dstBmpSizeImage;
		dstBmp->m_bmpFileHeader.bfOffBits=14+40+256*4;
	}
	if (this->m_bmpInfoHeader.biBitCount==24)
	{
		dstBmp->m_bmpFileHeader.bfSize=14+40+dstBmpSizeImage;
		dstBmp->m_bmpFileHeader.bfOffBits=14+40;
	}
	memcpy(&(dstBmp->m_bmpInfoHeader),&(this->m_bmpInfoHeader),sizeof(this->m_bmpInfoHeader));
	dstBmp->m_bmpInfoHeader.biWidth=nWidth;
	dstBmp->m_bmpInfoHeader.biHeight=nHeight;
	dstBmp->m_bmpInfoHeader.biSizeImage=dstBmpSizeImage;

	if (this->m_bmpInfoHeader.biBitCount==8)
	{
		memcpy(dstBmp->m_rgbQuad,this->m_rgbQuad,sizeof(this->m_rgbQuad)*256);

	}

	if (this->m_bmpInfoHeader.biBitCount==8)
	{
		for (int i=0;i<nHeight;i++)
		{
			for (int j=0;j<nScanWidth;j++)
			{
				dstBmp->m_bmpData[i*nWidth+j]=this->m_bmpData[int(i/fHeightRate)*
					                           this->m_bmpInfoHeader.biWidth+int(j/fWidthRate)];
					
			}
		}
		
	} 
	if (this->m_bmpInfoHeader.biBitCount==24)
	{
		for (int i=0;i<nHeight;i++)
		{
			for (int j=0;j<nScanWidth/3;j++)
			{
				dstBmp->m_bmpData[i*nScanWidth+j*3]=this->m_bmpData[int(i/fHeightRate)*
					this->m_bmpInfoHeader.biWidth*3+int(j/fWidthRate)*3];
				dstBmp->m_bmpData[i*nScanWidth+j*3+1]=this->m_bmpData[int(i/fHeightRate)*
					this->m_bmpInfoHeader.biWidth*3+int(j/fWidthRate)*3+1];
				dstBmp->m_bmpData[i*nScanWidth+j*3+2]=this->m_bmpData[int(i/fHeightRate)*
					this->m_bmpInfoHeader.biWidth*3+int(j/fWidthRate)*3+2];
			}
		}

	}

}

void CBmp::Resize(CBmp *dstBmp,float nRate)
{
	Resize(dstBmp,int(nRate*this->m_bmpInfoHeader.biWidth),int(nRate*this->m_bmpInfoHeader.biHeight));
}