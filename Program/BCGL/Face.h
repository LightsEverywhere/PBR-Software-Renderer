#pragma once
#include"P3.h"

class CFace
{
public:
	CFace(void);
	virtual ~CFace(void);
	void InitializeQueue(void);

public:
	int vertexNumber;// 面顶点数
	int* vertexIndex;
	int* normalIndex;
	int* textureIndex;

	CString materialName;// 面材质名称
};

