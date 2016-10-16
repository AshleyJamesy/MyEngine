#pragma once
#include "Mesh.h"
#include "Material.h"
#include "Transform.h"

class Model
{
public:
	Mesh*		m_Mesh = nullptr;
	Material	m_Material;

};