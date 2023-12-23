#pragma once
#include"P3.h"

class CZBuffer
{
public:
	CZBuffer(void);
	virtual ~CZBuffer(void);
	void SetZBufferSize(int nWidth, int nHeight);
	void InitializeZBuffer();
public:
	double** depthBuffer;// ��Ȼ�����
	CRGB** colorBuffer;// ��ɫ������
	int nWidth, nHeight;// ��������ȡ��߶�
};

