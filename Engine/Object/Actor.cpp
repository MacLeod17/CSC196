
#include "pch.h"
#include "Actor.h"
#include <fstream>

namespace gk
{
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
}
