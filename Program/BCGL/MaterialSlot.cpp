#include "pch.h"
#include "MaterialSlot.h"

CMaterialSlot::CMaterialSlot(void)
{

}

CMaterialSlot::~CMaterialSlot(void)
{

}

void CMaterialSlot::ReadMaterial(CString mtlPath)
{
	CStdioFile file;
	if (!file.Open(mtlPath, CFile::modeRead))
	{
		MessageBoxW(NULL, _T("未找到材质文件！"), _T("警告"), MB_ICONEXCLAMATION);
		return;
	}
	CString strLine;

	while (file.ReadString(strLine))
	{
		strLine.Trim();
		if (strLine.Find(CString("newmtl")))// if(strLine.Left(7)=="newmtl "
		{

		}
	}

}
