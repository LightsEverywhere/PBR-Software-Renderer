#pragma once
#include"P3.h"

class CTriangle
{
public:
	CTriangle(void);
	virtual ~CTriangle(void);
public:
	int vertexIndex[3];// ƬԪ��������
	int textureIndex[3];// ƬԪ���������
	int normalIndex[3];// ƬԪ��������
};

