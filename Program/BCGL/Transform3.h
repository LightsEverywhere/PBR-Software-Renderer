#pragma once
#include"P3.h"
#include"Vector3.h"

class CTransform3
{
public:
	CTransform3(void);
	virtual ~CTransform3(void);
	void SetMatrix(CP3* P, int ptNumber);// ��ά���������ʼ��
	void SetMatrix(CP3* P, CVector3* N, int ptNumber, int nNumber);
	void Identity(void);// ��λ�����ʼ��
	void MultiplyMatrix(void);// �������

	void Translate(double tx, double ty, double tz);// ƽ�Ʊ任
	void Scale(double sx, double sy, double sz);// �����任
	void Scale(double sx, double sy, double sz, CP3 p);// ����������ı����任

	void RotateX(double theta);
	void RotateY(double theta);
	void RotateZ(double theta);
	void RotateX(double theta, CP3 p);
	void RotateY(double theta, CP3 p);
	void RotateZ(double theta, CP3 p);

	void ReflectX(void);
	void ReflectY(void);
	void ReflectZ(void);

	void ReflectXOY(void);
	void ReflectXOZ(void);
	void ReflectYOZ(void);

	void ShearX(double sy, double sz);
	void ShearY(double sx, double sz);
	void ShearZ(double sx, double sy);

public:
	double	T[4][4];// ��ά�任����
	CP3* P;// ��ά����������
	CVector3* N;// �㷨����������
	int	ptNumber;// ��ά�������
	int nNumber;// �㷨��������
};

