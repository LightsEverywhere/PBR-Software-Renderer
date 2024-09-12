#pragma once
#include"RGB.h"

class CMaterial
{
public:
	CMaterial(void);
	virtual ~CMaterial(void);

	void SetAmbientRef(CRGB ambientRef);// 设置环境反射率
	void SetDiffuseRef(CRGB diffuseRef);// 设置漫反射率
	void SetSpecularRef(CRGB specularRef);// 设置镜面反射率
	void SetSpecularExponent(double n);// 设置高光指数

	void SetAlbedo(CRGB albedo);// 设置反照率
	void SetMetallic(float metallic);// 设置金属度
	void SetRoughness(float roughness);// 设置粗糙度
	void SetAO(CRGB ao);// 设置环境光遮蔽
	void SetF0(CRGB F0);// 设置基础反射率
	void UpdateF0();
public:
	// Data for Blinn-Phong
	double specularExponent;// 高光指数 1~1000 as usual
	CRGB ambientRef;// 环境反射率
	CRGB diffuseRef;// 漫反射率（基础色）
	CRGB specularRef;// 镜面反射率
	CRGB emissiveCol;// 自发光颜色
	float refractionIdx;// 折射率 1.0~2.0 as usual
	float dissolve;// 透明度 0.0 total transparency, 1.0 total opacity (变量名称有待修正)

	/**
	 *  使用的光照模型
	 *	0: 颜色不开启光照。
	 *	1: 光照模型为漫反射和环境光，不包括镜面反射。
	 *	2: 光照模型为漫反射、环境光和镜面反射（即高光）。
	 */
	int illuminationModel = 2;// 当前默认全部开启

	// Data for PBR
	CRGB albedo;// 反照率
	float metallic;// 金属度
	float roughness;// 表面粗糙度
	CRGB ao;// 环境光遮蔽
	CRGB F0;// 基础反射率

	// Info
	CString name;// 材质名称


};

