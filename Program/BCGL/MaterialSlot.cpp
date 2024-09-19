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
	bool bInMaterial = false;
	CMaterial newMaterial;

	while (file.ReadString(strLine))
	{
		strLine.Trim();

		if (strLine.Left(7) == "newmtl ")
		{
			if (bInMaterial)
				Materials.push_back(newMaterial);

			newMaterial = CMaterial();
			newMaterial.name = strLine.Mid(7);
			bInMaterial = true;
		}
		else if (strLine.Left(3) == "Ns ")
		{
			newMaterial.specularExponent = static_cast<float>(_tstof(strLine.Mid(3)));
		}
		else if (strLine.Left(3) == "Ka ")
		{
			_stscanf_s(strLine.Mid(3), _T("%lf %lf %lf"),
				&newMaterial.ambientRef.red,
				&newMaterial.ambientRef.green,
				&newMaterial.ambientRef.blue);
		}
		else if (strLine.Left(3) == "Kd ")
		{
			_stscanf_s(strLine.Mid(3), _T("%lf %lf %lf"),
				&newMaterial.diffuseRef.red,
				&newMaterial.diffuseRef.green,
				&newMaterial.diffuseRef.blue);
		}
		else if (strLine.Left(3) == "Ks ")
		{
			_stscanf_s(strLine.Mid(3), _T("%lf %lf %lf"),
				&newMaterial.specularRef.red,
				&newMaterial.specularRef.green,
				&newMaterial.specularRef.blue);
		}
		else if (strLine.Left(3) == "Ke ")
		{
			_stscanf_s(strLine.Mid(3), _T("%lf %lf %lf"),
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
		else if (strLine.Left(7) == "map_Ka ")
		{
			newMaterial.ambientTextureName = strLine.Mid(7);
		}
		else if (strLine.Left(7) == "map_Kd ")
		{
			newMaterial.diffuseTextureName = strLine.Mid(7);
		}
		else if (strLine.Left(7) == "map_Ks ")
		{
			newMaterial.specularTextureName = strLine.Mid(7);
		}
		else if (strLine.Left(7) == "map_Ke ")
		{
			newMaterial.emissiveTextureName = strLine.Mid(7);
		}
		else if (strLine.Left(9) == "map_bump ")
		{
			newMaterial.normalTextureName = strLine.Mid(9);
		}
		else if (strLine.Left(5) == "bump ")
		{
			newMaterial.normalTextureName = strLine.Mid(5);
		}
	}

	if (bInMaterial)
	{
		Materials.push_back(newMaterial);
	}

	file.Close();

}
