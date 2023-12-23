#pragma once
#include<string>
#include"RGB.h"
#include"../ImgLoad/stb_image.h"
#include"../ImgLoad/stb_image_write.h"
#include"T2.h"
#include"Vector3.h"
using namespace std;

class CTexture
{
public:
	CTexture(void);
	virtual ~CTexture(void);
	void CreateImgData(int imgWidth,int imgHeight,int nChannel);// Ϊͼ��������������ڴ�

	void SetImagePath(string imgPath);
	void ReadImagefData();
	void ReadImageData();
	CRGB SampleTexture(CT2 textureCoord);
	CRGB SampleTextureLF(CT2 textureCoord);
	int ClamptoEdge(int uv, int range);
	void ShowTexture(CDC* pDC);// ��������ʾ����Ļ��
	void ShowTexture(int scrX, int scrY, CDC* pDC);// ��������ʾ����Ļָ��λ��
	void ShowTexture(int scrX, int scrY, int showWidth, int showHeight, CDC* pDC);
	void FreeStbImg();

	void GenMipMap(int nTotalLevel);// ����mipmap
	void ShowMipMap(CDC* pDC);// ��ͼ��ĸ���mipmap��ʾ����Ļ��

	int GetImgWidth();// ��ȡͼ����
	int GetImgHeight();// ��ȡͼ��߶�
	int GetImgChannel();// ��ȡͼ��ͨ����

	CRGB SampleSphericalMap(CVector3 vec3);// ��������Ϊ�Ⱦ���״ͼ��ȡ��ɫ��Ϣ

	void OutputImage(string imgName);// ���ͼ��

public:
	string imgPath;
	float* imgfData;// ���������32λɫ��ͼ��
	unsigned char* imgData;// jpg,pngʹ��
	int imgWidth, imgHeight, nChannel;

	float** mipmap;// ͼ���Ӧ�Ķ༶��mipmap
	int nTotalLevel;// mipmap����

	BOOL isHDRi;
};

