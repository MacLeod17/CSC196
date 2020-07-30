
#include "pch.h"
#include "Actor.h"
#include <fstream>

namespace gk
{
    void Actor::Destroy()
    {
        for (auto child : m_children)
        {
            delete child;
        }
        m_children.clear();
    }

    bool Actor::Load(const std::string& filename)
    {
        bool success = false;

        std::ifstream stream(filename);
        if (stream.is_open())
        {
            success = true;
            
            Load(stream);

            stream.close();
        }

        return success;
    }

    void Actor::Load(std::istream& stream)
    {
        stream >> m_transform;

        std::string shapename;
        stream >> shapename;
        m_shape.Load(shapename);
    }

    void Actor::Update(float dt)
    {

    }

    void Actor::Draw(Core::Graphics& graphics)
    {
        m_shape.Draw(graphics, m_transform);
    }

    float Actor::GetRadius()
    {
        return m_shape.GetRadius() * m_transform.scale;
    }

    void Actor::AddChild(Actor* child)
    {
        child->m_parent = this;
        m_children.push_back(child);
    }
}

