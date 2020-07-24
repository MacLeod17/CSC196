
#include "Enemy.h"
#include "Graphics/ParticleSystem.h"
#include "Math/Math.h"
#include "Math/Random.h"
#include "Object/Scene.h"
#include "../Game.h"
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
    void Enemy::OnCollision(Actor* actor)
    {
        if (actor->GetType() == eType::PROJECTILE)
        {
            m_destroy = true;

            //Set Game Score
            m_scene->GetGame()->AddScore(100);

            Color colors[] = { Color::white, Color::red, Color::green, Color::blue, Color::yellow };

            for (size_t i = 0; i < 30; i++)
            {
                Color color = colors[(int)random(0, 4)];
                g_particleSystem.Create(m_transform.position, 0, 180, 2, color, 1, 100, 200);
            }
            
        }
    }
}