#pragma once
#include "Material.h"

class CMaterialSlot
{
public:
	CMaterialSlot(void);
	virtual ~CMaterialSlot(void);

	void ReadMaterial(CString mtlPath);

public:
	std::vector<CMaterial> Materials;

};

