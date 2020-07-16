
#include "Enemy.h"
#include "Math/Math.h"
#include <fstream>

namespace gk
{
    bool Enemy::Load(const std::string& filename)
    {
        bool success = false;

        std::ifstream stream(filename);
        if (stream.is_open())
        {
            success = true;

            // load the base actor members
            Actor::Load(stream);

            stream >> m_thrust;

            stream.close();
        }

        return success;
    }

    void Enemy::Update(float dt)
    {
	    gk::Vector2 direction = m_target->GetTransform().position - m_transform.position;
	    direction.normalize();
	    gk::Vector2 velocity = direction * m_thrust;
        m_transform.position += velocity * dt;
        m_transform.angle = std::atan2(direction.y, direction.x) + gk::DegreesToRadians(90);

        m_transform.Update();
    }
}