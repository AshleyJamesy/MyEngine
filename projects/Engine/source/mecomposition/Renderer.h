#pragma once
#include "Component.h"
#include "source\metypes\Mesh.h"
#include "source\metypes\Material.h"

class Renderer : public Component
{
public:
	Mesh*		m_Mesh = nullptr;
	Material	m_Material;

private:


};