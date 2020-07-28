#include "Locator.h"

void gk::Locator::Update(float dt)
{
	//Matrix * parent_matrix
	if (m_parent)
	{
		m_transform.Update(m_parent->GetTransform().matrix);
	}
	else
	{
		m_transform.Update();
	}
}
