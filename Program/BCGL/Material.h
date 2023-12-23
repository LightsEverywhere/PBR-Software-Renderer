#pragma once
#include"RGB.h"

class CMaterial
{
public:
	CMaterial(void);
	virtual ~CMaterial(void);
	void SetAmbientRef(CRGB ambientRef);// ���û���������
	void SetDiffuseRef(CRGB diffuseRef);// ������������
	void SetSpecularRef(CRGB specularRef);// ���þ��淴����
	void SetSpecularExponent(double n);
	void SetAlbedo(CRGB albedo);// ���÷�����
	void SetMetallic(float metallic);// ���ý�����
	void SetRoughness(float roughness);// ���ôֲڶ�
	void SetAO(CRGB ao);// ���û������ڱ�
	void SetF0(CRGB F0);// ���û���������
	void UpdateF0();
public:
	// Data for Blinn-Phong
	CRGB ambientRef;// ����������
	CRGB diffuseRef;// ��������
	CRGB specularRef;// ���淴����
	double specularExponent;// �߹�ָ��
	// Data for PBR
	CRGB albedo;// ������
	float metallic;// ������
	float roughness;// ����ֲڶ�
	CRGB ao;// �������ڱ�
	CRGB F0;// ����������
};

