#pragma once
#include"P3.h"

class CProjection
{
public:
	CProjection(void);
	virtual ~CProjection(void);
	void SetEye(double Phi,double Theta);// �����ӵ�
	CP3 GetEye(void);// ����ӵ�
	void InitialParameter(void);
	CP3 PerspectiveProjection(CP3 WorldPoint);

	CP3 ViewTransform(CP3 WorldPoint);// View�任
	CP3 PerspTransform(CP3 ViewPoint);// ͸��Projection�任
	CP3 InverseViewTransform(CP3 ViewPoint);// ��View�任
public:
	CP3 Eye;// �ӵ�
	double R, Phi, Theta, d;//�ӵ�������
	double k[8];// ͸��ͶӰ����

	double zNear, zFar;// ��Զ������
};

