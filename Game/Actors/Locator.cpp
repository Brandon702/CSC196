#include "Locator.h"

void Locator::Update(float dt)
{
	if (m_parent)
	{
		m_transform.Update(m_parent->GetTransform().matrix);
	}
	else
	{
		m_transform.Update();
	}
}
