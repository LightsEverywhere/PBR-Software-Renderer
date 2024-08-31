#include "pch.h"
#include "MaterialSlot.h"


CMaterialSlot::CMaterialSlot(void)
{

}

CMaterialSlot::~CMaterialSlot(void)
{

}

void CMaterialSlot::ReadMaterials(CString mtlPath)
{
	CStdioFile file;
	if (!file.Open(mtlPath, CFile::modeRead))
	{
		MessageBoxW(NULL, _T("未找到材质文件！"), _T("警告"), MB_ICONEXCLAMATION);
		return;
	}

	CString strLine;
	bool inMaterial = false;
	CMaterial newMaterial;

	while (file.ReadString(strLine))
	{
		strLine.Trim();

		if (strLine.Find(CString("newmtl")))
		{
			if (inMaterial)
				Materials.push_back(newMaterial);

			newMaterial = CMaterial();
			newMaterial.name = strLine.Mid(7);
			inMaterial = true;
		}
		else if (strLine.Left(3) == "Ns ")
		{
			newMaterial.specularExponent = static_cast<float>(_tstof(strLine.Mid(3)));
		}
		else if (strLine.Left(3) == "Ka ")
		{
			_stscanf_s(strLine.Mid(3), _T("%f, %f, %f"),
				&newMaterial.ambientRef.red,
				&newMaterial.ambientRef.green,
				&newMaterial.ambientRef.blue);
		}
		else if (strLine.Left(3) == "Kd ")
		{
			_stscanf_s(strLine.Mid(3), _T("%f, %f, %f"),
				&newMaterial.diffuseRef.red,
				&newMaterial.diffuseRef.green,
				&newMaterial.diffuseRef.blue);
		}
		else if (strLine.Left(3) == "Ks ")
		{
			_stscanf_s(strLine.Mid(3), _T("%f, %f, %f"),
				&newMaterial.specularRef.red,
				&newMaterial.specularRef.green,
				&newMaterial.specularRef.blue);
		}
		else if (strLine.Left(3) == "Ke ")
		{
			_stscanf_s(strLine.Mid(3), _T("%f, %f, %f"),
				&newMaterial.emissiveCol.red,
				&newMaterial.emissiveCol.green,
				&newMaterial.emissiveCol.blue);
		}
		else if (strLine.Left(3) == "Ni ")
		{
			newMaterial.refractionIdx = static_cast<float>(_tstof(strLine.Mid(3)));
		}
		else if (strLine.Left(2) == "D ")
		{
			newMaterial.dissolve = static_cast<float>(_tstof(strLine.Mid(2)));
		}
		else if (strLine.Left(6) == "illum ")
		{
			newMaterial.illuminationModel = _ttoi(strLine.Mid(6));
		}
	}

	if (inMaterial)
	{
		Materials.push_back(newMaterial);
	}

	file.Close();

}
