#include "stdafx.h"
#include "Component.h"
#include "GameObject.h"

GameObject* Component::GetOwner()
{
    return dynamic_cast<GameObject*>(m_Owner);
}

