#pragma once

class CBmp
{
public:
	BITMAPFILEHEADER m_bmpFileHeader;
	BITMAPINFOHEADER m_bmpInfoHeader;
	RGBQUAD *m_rgbQuad;

	BYTE *m_bmpData;  //ͼ������

	float fWidthHeightRate;
private:
	float m_fXPositionInDC;       //��¼ͼ����DC�е���ʼλ�ã�����Draw��������
	float m_fYPositionInDC;
public:
	CBmp(void);
	CBmp(int x, int y, int n);
	~CBmp(void);


	void set_m_fXPositionInDC(float fXPosition);
	float get_m_fXPositionInDC();
	void set_m_fYPositionInDC(float fXPosition);
	float get_m_fYPositionInDC();
	
	void LoadBmp(CString m_strFileName);
	void SaveBmp(CString m_strFileName);
	bool IsNull();
	void ReleaseBmp();
	void Draw(HDC hdc, int x, int y);
	void Draw(HDC hdc, int x, int y, int nwidth, int nheight);
	void DrawCenter(HWND hWnd, HDC hdc, int nwidth, int nheight);
	void Resize(CBmp *dstBmp,int nWidth, int nHeight);
	void Resize(CBmp *dstBmp,float nRate);
		 
};

