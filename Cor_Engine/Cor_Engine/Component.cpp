#include "stdafx.h"
#include "GameObject.h"
#include "Component.h"

GameObject* Component::GetOwner()
{
    return dynamic_cast<GameObject*>(m_Owner);
}
