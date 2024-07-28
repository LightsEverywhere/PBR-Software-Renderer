
// ProgramView.cpp: CProgramView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Program.h"
#endif

#include "ProgramDoc.h"
#include "ProgramView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CProgramView

IMPLEMENT_DYNCREATE(CProgramView, CView)

BEGIN_MESSAGE_MAP(CProgramView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
//	ON_WM_LBUTTONDOWN()
//	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_32771, &CProgramView::OnImportObj)
	ON_COMMAND(ID_32772, &CProgramView::OnLightCtrl_1)
	ON_COMMAND(ID_32773, &CProgramView::OnLightCtrl_2)
	ON_COMMAND(ID_32779, &CProgramView::OnLightCtrl_3)
	ON_COMMAND(ID_32775, &CProgramView::OnLightCtrl_4)
	ON_COMMAND(ID_32776, &CProgramView::OnAllLightsOn)
	ON_COMMAND(ID_32778, &CProgramView::OnAllLightsOff)
	ON_COMMAND(ID_32780, &CProgramView::OnPointCloudMode)
	ON_COMMAND(ID_32781, &CProgramView::OnWireFrameMode)
	ON_COMMAND(ID_32782, &CProgramView::OnPhongMode)
	ON_COMMAND(ID_32783, &CProgramView::OnPBRenderMode)
	ON_COMMAND(ID_32784, &CProgramView::OnLoadEnvironmentTex)
	ON_COMMAND(ID_32788, &CProgramView::OnPBRxIBLMode)
	ON_COMMAND(ID_32789, &CProgramView::OnMetallicZero)
	ON_COMMAND(ID_32790, &CProgramView::OnMetallicHalf)
	ON_COMMAND(ID_32791, &CProgramView::OnMetallicTotal)
	ON_COMMAND(ID_32792, &CProgramView::OnRoughnessZero)
	ON_COMMAND(ID_32794, &CProgramView::OnRoughnessTotal)
	ON_COMMAND(ID_32793, &CProgramView::OnRoughnessHalf)
	ON_COMMAND(ID_32795, &CProgramView::OnDefaultValue)
	ON_COMMAND(ID_32786, &CProgramView::OnImportAlbedo)
	ON_COMMAND(ID_32787, &CProgramView::OnImportNormal)
	ON_COMMAND(ID_PBR32796, &CProgramView::OnImportMetallic)
	ON_COMMAND(ID_PBR32797, &CProgramView::OnImportRoughness)
	ON_COMMAND(ID_PBR32798, &CProgramView::OnImportAO)
END_MESSAGE_MAP()

// CProgramView 构造/析构

CProgramView::CProgramView() noexcept
{
	// TODO: 在此处添加构造代码
	mainCamera.SetEye(70, 20);// 设置主相机
	gui.BindCamera(&mainCamera);// 将ui网格与相机绑定
	scene.camPos = &mainCamera.Eye;// 将相机绑定到场景
	isRButtonDown = FALSE;// 鼠标右键默认弹起
	model = NULL;
	drawingMode = wireFrame;// 默认线框绘制模式
	envTexture = NULL;// 默认不加载环境贴图
	skybox = NULL;// 默认不加载天空盒
	albedoTex = NULL;
	normalTex = NULL;
	roughnessTex = NULL;
	metallicTex = NULL;
	aoTex = NULL;
}

CProgramView::~CProgramView()
{
	if (model != NULL)// 释放模型对象
	{
		delete model;
		model = NULL;
	}
	if (envTexture != NULL)
	{
		delete envTexture;
		envTexture = NULL;
	}
	if (skybox != NULL)
	{
		delete skybox;
		skybox = NULL;
	}
	if (albedoTex != NULL)
	{
		delete albedoTex;
		albedoTex = NULL;
	}
	if (normalTex != NULL)
	{
		delete normalTex;
		normalTex = NULL;
	}
	if (metallicTex != NULL)
	{
		delete metallicTex;
		metallicTex = NULL;
	}
	if (roughnessTex != NULL)
	{
		delete roughnessTex;
		roughnessTex = NULL;
	}
	if (aoTex != NULL)
	{
		delete aoTex;
		aoTex = NULL;
	}
}

BOOL CProgramView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CProgramView 绘图

void CProgramView::OnDraw(CDC* pDC)
{
	CProgramDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	OffsetClientRect(pDC);
	DoubleBuffer(pDC);
	//DrawObject(pDC);
}

void CProgramView::OffsetClientRect(CDC* pDC)
{
	GetClientRect(&rect);
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowExt(rect.Width(), rect.Height());
	pDC->SetViewportExt(rect.Width(), -rect.Height());
	pDC->SetViewportOrg(rect.Width() / 2, rect.Height() / 2);
}

void CProgramView::DoubleBuffer(CDC* pDC)
{
	CDC memDC;// 声明内存DC
	memDC.CreateCompatibleDC(pDC);// 创建一个与显示DC兼容的内存DC
	CBitmap NewBitmap, * pOldBitmap;
	NewBitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());// 创建兼容内存位图
	pOldBitmap = memDC.SelectObject(&NewBitmap);// 将兼容位图选入内存DC
	//memDC.FillSolidRect(rect, pDC->GetBkColor());// 设置客户区背景色
	memDC.FillSolidRect(rect, RGB(52, 52, 52));// 深灰
	//memDC.FillSolidRect(rect, RGB(0, 0, 0));
	rect.OffsetRect(-rect.Width() / 2, -rect.Height() / 2);
	memDC.SetMapMode(MM_ANISOTROPIC);// 内存DC自定义坐标系
	memDC.SetWindowExt(rect.Width(), rect.Height());
	memDC.SetViewportExt(rect.Width(), -rect.Height());
	memDC.SetViewportOrg(rect.Width() / 2, rect.Height() / 2);

	frameBuffer = new CCanvas(rect.Width(), rect.Height());
	DrawObject(&memDC, frameBuffer);// 绘制图形
	CBitmap frameBufBitmap; 
	frameBufBitmap.CreateBitmap(rect.Width(), rect.Height(), 1, 32, frameBuffer->GetBufferData());
	memDC.SelectObject(frameBufBitmap);

	pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(),
		&memDC, -rect.Width() / 2, -rect.Height() / 2, SRCCOPY);// 将内存DC中的位图拷贝到显示DC

	memDC.SelectObject(pOldBitmap);
	NewBitmap.DeleteObject();
	memDC.DeleteDC();
	delete frameBuffer;
}

void CProgramView::DrawObject(CDC* pDC, CCanvas* frameBuffer)
{
	gui.DrawCoordinateGrid(pDC);
	if (skybox != NULL)
	{
		//skybox->envSubTex[0].GenMipMap(5);
		//skybox->envSubTex[0].ShowMipMap(pDC);
		//skybox->UnfoldSkybox(pDC);
		//skybox->UnfoldIrrBox(pDC);
		//skybox->DrawSamplePoint(pDC,&mainCamera);
		//skybox->ShowHammersley(pDC);
		//skybox->UnfoldPftBox(pDC);
		//skybox->ShowGGX(pDC, &mainCamera);
		//skybox->ShowLUT(pDC);
		//skybox->lutTex.OutputImage("lut2.hdr");

		// 输出环境立方体贴图
		//skybox->envSubTex[0].OutputImage("environment_0.hdr");
		//skybox->envSubTex[1].OutputImage("environment_1.hdr");
		//skybox->envSubTex[2].OutputImage("environment_2.hdr");
		//skybox->envSubTex[3].OutputImage("environment_3.hdr");
		//skybox->envSubTex[4].OutputImage("environment_4.hdr");
		//skybox->envSubTex[5].OutputImage("environment_5.hdr");

		// 输出irradiance图
		//skybox->irrSubTex[0].OutputImage("Irradiance_0.hdr");
		//skybox->irrSubTex[1].OutputImage("Irradiance_1.hdr");
		//skybox->irrSubTex[2].OutputImage("Irradiance_2.hdr");
		//skybox->irrSubTex[3].OutputImage("Irradiance_3.hdr");
		//skybox->irrSubTex[4].OutputImage("Irradiance_4.hdr");
		//skybox->irrSubTex[5].OutputImage("Irradiance_5.hdr");

		// 输出预滤波环境贴图
		//skybox->pftSubTex[1][0].OutputImage("pftSub\\Prefilter_r0.2_0.hdr");
		//skybox->pftSubTex[1][1].OutputImage("pftSub\\Prefilter_r0.2_1.hdr");
		//skybox->pftSubTex[1][2].OutputImage("pftSub\\Prefilter_r0.2_2.hdr");
		//skybox->pftSubTex[1][3].OutputImage("pftSub\\Prefilter_r0.2_3.hdr");
		//skybox->pftSubTex[1][4].OutputImage("pftSub\\Prefilter_r0.2_4.hdr");
		//skybox->pftSubTex[1][5].OutputImage("pftSub\\Prefilter_r0.2_5.hdr");

		//skybox->pftSubTex[2][0].OutputImage("pftSub\\Prefilter_r0.4_0.hdr");
		//skybox->pftSubTex[2][1].OutputImage("pftSub\\Prefilter_r0.4_1.hdr");
		//skybox->pftSubTex[2][2].OutputImage("pftSub\\Prefilter_r0.4_2.hdr");
		//skybox->pftSubTex[2][3].OutputImage("pftSub\\Prefilter_r0.4_3.hdr");
		//skybox->pftSubTex[2][4].OutputImage("pftSub\\Prefilter_r0.4_4.hdr");
		//skybox->pftSubTex[2][5].OutputImage("pftSub\\Prefilter_r0.4_5.hdr");

		//skybox->pftSubTex[3][0].OutputImage("pftSub\\Prefilter_r0.6_0.hdr");
		//skybox->pftSubTex[3][1].OutputImage("pftSub\\Prefilter_r0.6_1.hdr");
		//skybox->pftSubTex[3][2].OutputImage("pftSub\\Prefilter_r0.6_2.hdr");
		//skybox->pftSubTex[3][3].OutputImage("pftSub\\Prefilter_r0.6_3.hdr");
		//skybox->pftSubTex[3][4].OutputImage("pftSub\\Prefilter_r0.6_4.hdr");
		//skybox->pftSubTex[3][5].OutputImage("pftSub\\Prefilter_r0.6_5.hdr");

		//skybox->pftSubTex[4][0].OutputImage("pftSub\\Prefilter_r0.8_0.hdr");
		//skybox->pftSubTex[4][1].OutputImage("pftSub\\Prefilter_r0.8_1.hdr");
		//skybox->pftSubTex[4][2].OutputImage("pftSub\\Prefilter_r0.8_2.hdr");
		//skybox->pftSubTex[4][3].OutputImage("pftSub\\Prefilter_r0.8_3.hdr");
		//skybox->pftSubTex[4][4].OutputImage("pftSub\\Prefilter_r0.8_4.hdr");
		//skybox->pftSubTex[4][5].OutputImage("pftSub\\Prefilter_r0.8_5.hdr");

		//skybox->pftSubTex[5][0].OutputImage("pftSub\\Prefilter_r1.0_0.hdr");
		//skybox->pftSubTex[5][1].OutputImage("pftSub\\Prefilter_r1.0_1.hdr");
		//skybox->pftSubTex[5][2].OutputImage("pftSub\\Prefilter_r1.0_2.hdr");
		//skybox->pftSubTex[5][3].OutputImage("pftSub\\Prefilter_r1.0_3.hdr");
		//skybox->pftSubTex[5][4].OutputImage("pftSub\\Prefilter_r1.0_4.hdr");
		//skybox->pftSubTex[5][5].OutputImage("pftSub\\Prefilter_r1.0_5.hdr");
	}

	if (model != NULL)
	{
		switch (drawingMode)
		{
		case CProgramView::pointCloud:
			model->DrawPointCloud(pDC);
			break;
		case CProgramView::wireFrame:
			model->DrawWireframe(pDC);
			break;
		case CProgramView::phongShading:
		{
			if (false/*isRButtonDown*/)
			{
				model->DrawWireframe(pDC);
			}
			else
			{
				model->GetScreenBox();// 获取模型屏幕包围盒尺寸
				CZBuffer* pZBuffer = new CZBuffer;//申请内存
				int bufferW, bufferH;
				bufferH = min(model->screenH, rect.Height());
				bufferW = min(model->screenW, rect.Width());
				pZBuffer->SetZBufferSize(bufferW, bufferH);
				pZBuffer->InitializeZBuffer();//初始化深度缓冲器
				model->SetMaterial(&material);
				model->SetScene(&scene);
				model->SetZBuffer(pZBuffer);
				model->BlinnPhongShader(pDC, frameBuffer);
				delete pZBuffer;
			}
			break;
		}
		case CProgramView::PBR:
		{
			if (false/*isRButtonDown*/)
			{
				model->DrawWireframe(pDC);
			}
			else
			{
				model->GetScreenBox();// 获取模型屏幕包围盒尺寸
				CZBuffer* pZBuffer = new CZBuffer;//申请内存
				int bufferW, bufferH;
				bufferH = min(model->screenH, rect.Height());
				bufferW = min(model->screenW, rect.Width());
				pZBuffer->SetZBufferSize(bufferW, bufferH);
				pZBuffer->InitializeZBuffer();//初始化深度缓冲器
				model->SetMaterial(&material);
				model->SetScene(&scene);
				model->SetZBuffer(pZBuffer);
				model->PBRendering(pDC, frameBuffer);
				delete pZBuffer;
			}
			break;
		}
		case CProgramView::PBRxIBL:
		{
			if (false/*isRButtonDown*/)
			{
				model->DrawWireframe(pDC);
			}
			else
			{
				model->GetScreenBox();// 获取模型屏幕包围盒尺寸
				CZBuffer* pZBuffer = new CZBuffer;//申请内存
				int bufferW, bufferH;
				bufferH = min(model->screenH, rect.Height());
				bufferW = min(model->screenW, rect.Width());
				pZBuffer->SetZBufferSize(bufferW, bufferH);
				pZBuffer->InitializeZBuffer();//初始化深度缓冲器
				model->SetMaterial(&material);
				model->SetScene(&scene);
				model->SetZBuffer(pZBuffer);
				model->PBRenderingwithIBL(pDC, frameBuffer);
				delete pZBuffer;
			}
			break;
		}
		default:
			break;
		}
	}
}


// CProgramView 打印

BOOL CProgramView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CProgramView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CProgramView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CProgramView 诊断

#ifdef _DEBUG
void CProgramView::AssertValid() const
{
	CView::AssertValid();
}

void CProgramView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CProgramDoc* CProgramView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CProgramDoc)));
	return (CProgramDoc*)m_pDocument;
}
#endif //_DEBUG


// CProgramView 消息处理程序


void CProgramView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	isRButtonDown = TRUE;
	Invalidate(FALSE);
	CView::OnRButtonDown(nFlags, point);
}


void CProgramView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	isRButtonDown = FALSE;
	Invalidate(FALSE);
	CView::OnRButtonUp(nFlags, point);
}



void CProgramView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (isRButtonDown)
	{
		//SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEALL));
		double speed = 1800;
		double angle = 360;
		mainCamera.Phi -= (point.y - lastMousePoint.y) / speed * angle;
		mainCamera.Theta -= (point.x - lastMousePoint.x) / speed * angle;
		if (mainCamera.Phi > 180) mainCamera.Phi = 180;
		if (mainCamera.Phi < 0) mainCamera.Phi = 0;
		lastMousePoint = point;
		mainCamera.InitialParameter();
		Invalidate(FALSE);
	}
	else
	{
		lastMousePoint = point;
	}
	CView::OnMouseMove(nFlags, point);
}


BOOL CProgramView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	mainCamera.R -= zDelta ;
	if (mainCamera.R < 425) mainCamera.R = 425;
	mainCamera.InitialParameter();
	Invalidate(FALSE);
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CProgramView::OnImportObj()
{
	// TODO: 在此添加命令处理程序代码
	CFileDialog pFileDlg(TRUE, _T(""), _T(""), OFN_HIDEREADONLY, _T("OBJ Files(*.obj)|*.obj|"), this);
	if (pFileDlg.DoModal() == IDOK)
	{
		if (model != NULL) { delete model; model = NULL; }// 若添加另一个模型时首先释放第一个模型
		model = new CModel();
		model->fileName = pFileDlg.GetPathName();
		model->GatherStatistics();
		model->ReadVertex();
		model->ReadTexture();
		model->ReadNormal();
		model->ReadFace();
		model->ReadTriangle();
		transform.SetMatrix(model->vertex, model->nTotalVertex);
		transform.Translate(-model->centerPoint.x, -model->centerPoint.y, -model->centerPoint.z);//将模型移至屏幕中心点
		double scaleX = 160 / model->modelLength;//计算合适的缩放比例
		double scaleY = 160 / model->modelHeight;
		double nScale = min(scaleX, scaleY);
		model->scalar = nScale;
		transform.Scale(nScale * 1.3, nScale * 1.3, nScale * 1.3);
		model->camera = &mainCamera;// 将模型绑定到主相机
		if (albedoTex != NULL) model->BindAlbedo(albedoTex);
		if (normalTex != NULL) model->BindNormal(normalTex);
		if (roughnessTex != NULL) model->BindRoughness(roughnessTex);
		if (metallicTex != NULL) model->BindMetallic(metallicTex);
		if (aoTex != NULL) model->BindAO(aoTex);
	}
	Invalidate(FALSE);
}


void CProgramView::OnLightCtrl_1()
{
	// TODO: 在此添加命令处理程序代码
	scene.lightSource[0].lightOn = !scene.lightSource[0].lightOn;
	Invalidate(FALSE);
}


void CProgramView::OnLightCtrl_2()
{
	// TODO: 在此添加命令处理程序代码
	scene.lightSource[1].lightOn = !scene.lightSource[1].lightOn;
	Invalidate(FALSE);
}


void CProgramView::OnLightCtrl_3()
{
	// TODO: 在此添加命令处理程序代码
	scene.lightSource[2].lightOn = !scene.lightSource[2].lightOn;
	Invalidate(FALSE);
}


void CProgramView::OnLightCtrl_4()
{
	// TODO: 在此添加命令处理程序代码
	scene.lightSource[3].lightOn = !scene.lightSource[3].lightOn;
	Invalidate(FALSE);
}


void CProgramView::OnAllLightsOn()
{
	// TODO: 在此添加命令处理程序代码
	for (int nLight = 0; nLight < 4; nLight++)
	{
		scene.lightSource[nLight].lightOn = TRUE;
	}
	Invalidate(FALSE);
}


void CProgramView::OnAllLightsOff()
{
	// TODO: 在此添加命令处理程序代码
	for (int nLight = 0; nLight < 4; nLight++)
	{
		scene.lightSource[nLight].lightOn = FALSE;
	}
	Invalidate(FALSE);
}

void CProgramView::OnPointCloudMode()
{
	// TODO: 在此添加命令处理程序代码
	drawingMode = pointCloud;
	Invalidate(FALSE);
}


void CProgramView::OnWireFrameMode()
{
	// TODO: 在此添加命令处理程序代码
	drawingMode = wireFrame;
	Invalidate(FALSE);
}


void CProgramView::OnPhongMode() 
{
	// TODO: 在此添加命令处理程序代码
	drawingMode = phongShading;
	Invalidate(FALSE);
}


void CProgramView::OnPBRenderMode()
{
	// TODO: 在此添加命令处理程序代码
	drawingMode = PBR;
	Invalidate(FALSE);
}


void CProgramView::OnPBRxIBLMode()
{
	// TODO: 在此添加命令处理程序代码
	drawingMode = PBRxIBL;
	Invalidate(FALSE);
}


void CProgramView::OnLoadEnvironmentTex()
{
	// TODO: 在此添加命令处理程序代码
	CFileDialog pFileDlg(TRUE, _T(""), _T(""), OFN_HIDEREADONLY, _T("PIC Files(*.jpg;*.png;*.hdr)|*.jpg;*.png;*.hdr|"), this);
	if (pFileDlg.DoModal() == IDOK)
	{
		if (envTexture != NULL) { delete envTexture; envTexture = NULL; }// 若添加另一个环境纹理时首先释放第一个环境纹理
		if (skybox != NULL) { delete skybox; skybox = NULL; }
		envTexture = new CTexture();
		string imgPath = CT2A(pFileDlg.GetPathName());// 将CString类型的路径转为string
		envTexture->SetImagePath(imgPath);
		envTexture->ReadImagefData();
		skybox = new CSkybox();
		int envType = 0;
		if (pFileDlg.GetFileName() == "blue_photo_studio_4k.hdr") envType = 0;
		if (pFileDlg.GetFileName() == "music_hall_01_4k.hdr") envType = 1;
		skybox->ReadSubImg(envType);
		//skybox->SpheretoEnvCube(envTexture);
		//skybox->SpheretoIrrCube(envTexture);
		//skybox->SpheretoPrefilterMap(envTexture);
		//skybox->GenLookUpTexture();
		scene.skybox = skybox;

	}
	Invalidate(FALSE);
}



void CProgramView::OnMetallicZero()
{
	// TODO: 在此添加命令处理程序代码
	material.metallic = 0.0;
	material.F0 = CRGB(0.04, 0.04, 0.04);
	Invalidate(FALSE);
}


void CProgramView::OnMetallicHalf()
{
	// TODO: 在此添加命令处理程序代码
	material.metallic = 0.5;
	CRGB F0 = CRGB(0.04, 0.04, 0.04);
	material.F0 = mix(F0, material.albedo, material.metallic);
	Invalidate(FALSE);
}


void CProgramView::OnMetallicTotal()
{
	// TODO: 在此添加命令处理程序代码
	material.metallic = 0.9;
	CRGB F0 = CRGB(0.04, 0.04, 0.04);
	material.F0 = mix(F0, material.albedo, material.metallic);
	Invalidate(FALSE);
}


void CProgramView::OnRoughnessZero()
{
	// TODO: 在此添加命令处理程序代码
	material.roughness = 0.0;
	Invalidate(FALSE);
}


void CProgramView::OnRoughnessHalf()
{
	// TODO: 在此添加命令处理程序代码
	material.roughness = 0.5;
	Invalidate(FALSE);
}


void CProgramView::OnRoughnessTotal()
{
	// TODO: 在此添加命令处理程序代码
	material.roughness = 1.0;
	Invalidate(FALSE);
}

void CProgramView::OnDefaultValue()
{
	// TODO: 在此添加命令处理程序代码
	material.roughness = 0.3;
	material.metallic = 0.0;
	material.F0 = CRGB(0.04, 0.04, 0.04);
	Invalidate(FALSE);
}


void CProgramView::OnImportAlbedo()
{
	// TODO: 在此添加命令处理程序代码
	CFileDialog pFileDlg(TRUE, _T(""), _T(""), OFN_HIDEREADONLY, _T("PIC Files(*.jpg;*.png)|*.jpg;*.png|"), this);
	if (pFileDlg.DoModal() == IDOK)
	{
		if (albedoTex != NULL) { delete albedoTex; albedoTex = NULL; }// 若添加另一个环境纹理时首先释放第一个环境纹理
		albedoTex = new CTexture();
		string imgPath = CT2A(pFileDlg.GetPathName());// 将CString类型的路径转为string
		albedoTex->SetImagePath(imgPath);
		albedoTex->ReadImageData();
		model->BindAlbedo(albedoTex);
	}
	Invalidate(FALSE);
}


void CProgramView::OnImportNormal()
{
	// TODO: 在此添加命令处理程序代码
	CFileDialog pFileDlg(TRUE, _T(""), _T(""), OFN_HIDEREADONLY, _T("PIC Files(*.jpg;*.png)|*.jpg;*.png|"), this);
	if (pFileDlg.DoModal() == IDOK)
	{
		if (normalTex != NULL) { delete normalTex; normalTex = NULL; }// 若添加另一个环境纹理时首先释放第一个环境纹理
		normalTex = new CTexture();
		string imgPath = CT2A(pFileDlg.GetPathName());// 将CString类型的路径转为string
		normalTex->SetImagePath(imgPath);
		normalTex->ReadImageData();
		model->BindNormal(normalTex);
	}
	Invalidate(FALSE);
}


void CProgramView::OnImportMetallic()
{
	// TODO: 在此添加命令处理程序代码
	CFileDialog pFileDlg(TRUE, _T(""), _T(""), OFN_HIDEREADONLY, _T("PIC Files(*.jpg;*.png)|*.jpg;*.png|"), this);
	if (pFileDlg.DoModal() == IDOK)
	{
		if (metallicTex != NULL) { delete metallicTex; metallicTex = NULL; }// 若添加另一个环境纹理时首先释放第一个环境纹理
		metallicTex = new CTexture();
		string imgPath = CT2A(pFileDlg.GetPathName());// 将CString类型的路径转为string
		metallicTex->SetImagePath(imgPath);
		metallicTex->ReadImageData();
		model->BindMetallic(metallicTex);
	}
	Invalidate(FALSE);
}


void CProgramView::OnImportRoughness()
{
	// TODO: 在此添加命令处理程序代码
	CFileDialog pFileDlg(TRUE, _T(""), _T(""), OFN_HIDEREADONLY, _T("PIC Files(*.jpg;*.png)|*.jpg;*.png|"), this);
	if (pFileDlg.DoModal() == IDOK)
	{
		if (roughnessTex != NULL) { delete roughnessTex; roughnessTex = NULL; }// 若添加另一个环境纹理时首先释放第一个环境纹理
		roughnessTex = new CTexture();
		string imgPath = CT2A(pFileDlg.GetPathName());// 将CString类型的路径转为string
		roughnessTex->SetImagePath(imgPath);
		roughnessTex->ReadImageData();
		model->BindRoughness(roughnessTex);
	}
	Invalidate(FALSE);
}


void CProgramView::OnImportAO()
{
	// TODO: 在此添加命令处理程序代码
	CFileDialog pFileDlg(TRUE, _T(""), _T(""), OFN_HIDEREADONLY, _T("PIC Files(*.jpg;*.png)|*.jpg;*.png|"), this);
	if (pFileDlg.DoModal() == IDOK)
	{
		if (aoTex != NULL) { delete aoTex; aoTex = NULL; }// 若添加另一个环境纹理时首先释放第一个环境纹理
		aoTex = new CTexture();
		string imgPath = CT2A(pFileDlg.GetPathName());// 将CString类型的路径转为string
		aoTex->SetImagePath(imgPath);
		aoTex->ReadImageData();
		model->BindAO(aoTex);
	}
	Invalidate(FALSE);
}
