#pragma once
#include"P3.h"
#include"Face.h"
#include"Projection.h"
#include"Material.h"
#include"Vector3.h"
#include"ZBuffer.h"
#include"Triangle.h"
#include"Lighting.h"
#include"Texture.h"
#include"Canvas.h"

class CModel
{
public:
	CModel(void);
	virtual ~CModel(void);
	void GatherStatistics(void);// ͳ�Ƹ�������
	void ReadVertex(void);// ���붥����Ϣ
	void ReadTexture(void);// ������ʲ�����Ϣ
	void ReadNormal(void);// ���뷨����Ϣ
	void ReadFace(void);// ��������Ϣ
	void ReadTriangle(void);// ��ȡƬԪ��Ϣ
	void GetScreenBox(void);// ����ģ��ͶӰ�����Ļ��Χ��			//���Կ�����ΪԤ�����ֱ�ӱ����޳�+������

	void BindTexture(CTexture* targetTexture);// ���������
	void BindAlbedo(CTexture* targetAlbedo);// �󶨷�������ͼ
	void BindNormal(CTexture* targetNormal);// �󶨷�����ͼ
	void BindMetallic(CTexture* targetMetallic);// �󶨽�������ͼ
	void BindRoughness(CTexture* targetRoughness);// �󶨴ֲڶ���ͼ
	void BindAO(CTexture* targetAO);// ��AO

	void SetMaterial(CMaterial* material);
	void SetScene(CLighting* scene);
	void SetZBuffer(CZBuffer* zbuffer);
	bool InsideTriangle(float x, float y,const CP3* point);// �������ڲ��ж�

	void DrawPointCloud(CDC* pDC);// ���Ƶ���
	void DrawWireframe(CDC* pDC);// �����߿�
	void BlinnPhongShader(CDC* pDC);// Blinn-Phong�������� rasterization
	void PBRendering(CDC* pDC, CCanvas* frameBuffer);// ����������Ⱦ
	void PBRenderingwithIBL(CDC* pDC, CCanvas* frameBuffer);// ����������ȾxIBL
public:
	CString fileName;// obj�ļ���
	// ģ������
	CP3* vertex;// �������
	CT2* textureCoord;// ������������
	CVector3* normal;// �������
	CFace* face;// �����
	CTriangle* triangle;// ͼԪ(������)����
	int nTotalVertex;// ��������
	int nTotalTexture;// �������������
	int nTotalNormal;// ��������
	int nTotalFace;// ������
	int nTotalTriangle;// �����Σ�ͼԪ������
	float maxY, maxX, maxZ, minY, minX, minZ;// ģ�����Χ��
	float modelLength, modelWidth, modelHeight;// ģ�͵ĳ����
	CP3 centerPoint;//ģ�����ĵ�
	int xLeft, xRight, yTop, yBottom;// ͶӰ�����Ļ��Χ��
	int screenH, screenW;// ͶӰ����Ļ��Χ�гߴ�
	float scalar;
	// ģ������
	CMaterial* material;// �������
	CTexture* targetTexture;// Ŀ������
	CTexture* targetAlbedo;// Ŀ�귴��������
	CTexture* targetNormal;// Ŀ�귨����ͼ
	CTexture* targetMetallic;// Ŀ���������ͼ
	CTexture* targetRoughness;// Ŀ��ֲڶ���ͼ
	CTexture* targetAO;// Ŀ�껷�����ڱ���ͼ

	// ģ�������
	CZBuffer* zbuffer;// Ŀ����Ȼ�����
	CProjection* camera;// �������
	CLighting* scene;// ���ڹ��ճ���
};

