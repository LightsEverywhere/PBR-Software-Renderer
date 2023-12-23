#pragma once
#include"P3.h"
#include"Projection.h"

class CGUI
{
public:
	CGUI(void);
	virtual ~CGUI(void);
	void BindCamera(CProjection* camera);// ���������
	void DrawCoordinateGrid(CDC* pDC);// ��������ϵ����
	void DrawCoordinateAxis(CDC* pDC);// ��������ϵ����
public:
	float coorRadius;// ��������뾶
	float coorAmount;// ����ĳһ�������������
	float coorPrecision;// ���񾫶�(ϸ����������)
	float interval, subInterval;//���

	CProjection* camera;// �������
};

