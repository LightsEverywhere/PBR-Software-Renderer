#pragma once
#include"P3.h"

class CVector3
{
public:
	CVector3(void);
	virtual ~CVector3(void);
	CVector3(double x, double y, double z);
	CVector3(const CP3& P);
	CVector3(const CP3& P0, const CP3& P1);
	CVector3(const CP2& P);
	CVector3(const CP2& P0, const CP2& P1);
	double Norm();// ����ȡģ
	void Normalize();// ������λ�����ı�����
	CVector3 Normalized();// ��������ĵ�λ�����������ı�����

	friend double DotProduct(const CVector3& V0, const CVector3& V1);// �������
	friend CVector3 CrossProduct(const CVector3& V0, const CVector3& V1);// �������

	friend CVector3 operator+(const CVector3& V0, const CVector3& V1);
	friend CVector3 operator-(const CVector3& V0, const CVector3& V1);
	friend CVector3 operator*(const CVector3& V, double scalar);
	friend CVector3 operator*(double scalar, const CVector3& V);
	friend CVector3 operator/(const CVector3& V, double scalar);
	friend CVector3 operator+=(const CVector3& V0, const CVector3& V1);
	friend CVector3 operator-=(const CVector3& V0, const CVector3& V1);
	friend CVector3 operator*=(const CVector3& V, double scalar);
	friend CVector3 operator/=(const CVector3& V, double scalar);

public:
	double x, y, z;// ��������
	double w;// �������
};

