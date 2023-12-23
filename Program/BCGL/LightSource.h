#pragma once
#include"P3.h"

class CLightSource
{
public:
	CLightSource(void);
	virtual ~CLightSource(void);
	void SetLightPosition(CP3 lightPosition);// ���ù�Դλ��
	void SetAmbientInten(CRGB ambientInten);// ���û�������ɫ
	void SetDiffuseInten(CRGB diffuseInten);// �������������ɫ
	void SetSpecularInten(CRGB specularInten);// ���þ������ɫ
public:
	CRGB ambientInten;// ��������ɫ
	CRGB diffuseInten;// ���������ɫ
	CRGB specularInten;// �������ɫ

	CRGB lightColor;// �����ɫ
	CP3 lightPosition;// ��Դλ��
	double f;// ˥��ϵ��
	BOOL lightOn;// ��Դ�����ж�
};

