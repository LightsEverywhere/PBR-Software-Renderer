#pragma once
#include"P3.h"

class CFace
{
public:
	CFace(void);
	virtual ~CFace(void);
	void InitializeQueue(void);

public:
	int vertexNumber;// �涥����
	int* vertexIndex;
	int* normalIndex;
	int* textureIndex;
};

