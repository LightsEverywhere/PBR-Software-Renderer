#pragma once
#include"P3.h"
#include"Face.h"
#include"Texture.h"
#include"Vector3.h"
#include"Projection.h"
#define PI 3.141592653

class CSkybox
{
public:
	CSkybox(void);
	virtual ~CSkybox(void);
	void SpheretoEnvCube(CTexture* targetTex);
	CRGB SampleEnvCubeMap(CVector3 vec3);// �������廷����ͼ�л�ȡ��ɫ��Ϣ

	void SpheretoIrrCube(CTexture* targetTex);
	CRGB SampleIrrCubeMap(CVector3 vec3);// ����������ն�ͼ�л�ȡ��ɫ��Ϣ

	void ShowHammersley(CDC* pDC);// Hammersley���п��ӻ�
	CP2 Hammersley(UINT i, UINT sampleCount);// Hammersley����
	CVector3 ImportanceSampleGGX(CP2 Xi, CVector3 N, float roughness);// GGX��Ҫ�Բ���(�ú����������Ϊһ���������H) *��Ϊ�ú�������NDF�����õ���NDF����������Ϊ���򡢰���������ֲڶ�
	void ShowGGX(CDC* pDC, CProjection* camera);// ��ʾ��Ҫ�Բ���
	void SpheretoPrefilterMap(CTexture* targetTex);
	CRGB SamplePftCubeMap(CVector3 vec3, float roughness);
	CRGB IntegrateBRDF(float NdotV, float roughness);// ����BRDF����
	void GenLookUpTexture();// ����LUT
	void ShowLUT(CDC* pDC);// ��ʾLUT
	CRGB SampleLut(float NdotV, float roughness);// ��LUT�в���


	void ReadSubImg(int envType);// ���ֳɵ���������ͼ��ȡ��ɫ��Ϣ

	void DrawSamplePoint(CDC* pDC, CProjection* camera);

	void UnfoldSkybox(CDC* pDC);
	void UnfoldIrrBox(CDC* pDC);
	void UnfoldPftBox(CDC* pDC);
	void OutPutpftBox();

	float GeometrySchlickGGX_IBL(float NdotV, float roughness);// ���㼸�κ���
	float GeometrySmith_IBL(CVector3 normal, CVector3 viewVector, CVector3 lightVector, float roughness);// ��ϼ����ڱ��뼸����Ӱ

public:
	CP3 vertex[8];
	CFace face[6];
	CTexture envSubTex[6];// ��������������
	int envTexWidth, envTexHeight;// ���������廷����ͼ�ֱ��� ����
	CTexture irrSubTex[6];// �������ն�ͼ��
	int irrTexWidth, irrTexHeight;// ������������ն�ͼ�ֱ��� ����
	//CTexture prefilterTex[6];// ����Ԥ�˲���ͼ��
	CTexture pftSubTex[6][6];// ps���������˲���ͼ
	int pftTexWidth, pftTexHeight;// ����������Ԥ�˲���ͼ�ֱ��� ����
	CTexture lutTex;// 2D��������
	int lutTexWidth, lutTexHeight;// 2D��������ķֱ��� ����
};

