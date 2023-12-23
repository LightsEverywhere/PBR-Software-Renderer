#pragma once
#include"Material.h"
#include"LightSource.h"
#include"Vector3.h"
#include"Skybox.h"

class CLighting
{
public:
	CLighting(void);
	virtual ~CLighting(void);
	void SetLightSource(CLightSource* lightSource);// ���ù�Դ
	CRGB SimpleIlluminate(CP3 point, CP3 mainCamPos, CVector3 normal, const CMaterial* material);
	CRGB PBR(CP3 point, CMaterial* material, CVector3 normal);
	CRGB EnvPBR(CP3 point, CMaterial* material, CVector3 normal);
	CRGB EnvNewPBR(CP3 point, CMaterial* material, CVector3 normal);

	CRGB Radiance(CP3 point,CLightSource light);// ���������(�������˾���˥��)
	CRGB CookTorranceBRDF(CP3 point, CP3 lightPos, CMaterial* material, CVector3 normal);
	CRGB EnvCTBRDF(CP3 point, CP3 lightPos, CMaterial* material, CVector3 normal);
	CRGB FresnelSchlick(float cosTheta, CRGB F0);// ����Fresnel��
	CRGB FresnelSchlickRoughness(float cosTheta, CRGB F0, float roughness);// ����Fresnel��(���Ǵֲڶ�)
	float DistributionGGX(CVector3 normal, CVector3 H, float roughness);// ���㷨�߷ֲ�����
	float GeometrySchlickGGX(float NdotV, float roughness);// ���㼸�κ���
	float GeometrySmith(CVector3 normal, CVector3 viewVector, CVector3 lightVector, float roughness);// ��ϼ����ڱ��뼸����Ӱ
	float GeometrySchlickGGX_IBL(float NdotV, float roughness);// ���㼸�κ���
	float GeometrySmith_IBL(CVector3 normal, CVector3 viewVector, CVector3 lightVector, float roughness);// ��ϼ����ڱ��뼸����Ӱ

public:
	CLightSource* lightSource;// ��Դ
	CP3* camPos;// ���λ��
	CSkybox* skybox;
};

