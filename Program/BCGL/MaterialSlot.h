#pragma once
#include "Material.h"
#include <vector>

class CMaterialSlot
{
public:
	CMaterialSlot(void);
	virtual ~CMaterialSlot(void);

	void ReadMaterials(CString mtlPath);

public:
	std::vector<CMaterial> Materials;

};

