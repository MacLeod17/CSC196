
#include "Projectile.h"
#include "Graphics/ParticleSystem.h"
#include "Math/Math.h"
#include "Math/Vector2.h"
#include <fstream>

namespace gk
{
    bool Projectile::Load(const std::string& filename)
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

    void Projectile::Update(float dt)
    {
        m_lifetime -= dt;
        m_destroy = m_lifetime <= 0;
        
        Vector2 direction = Vector2::Rotate(Vector2::forward, m_transform.angle);
	    Vector2 velocity = direction * m_thrust;
        m_transform.position += velocity * dt;

        g_particleSystem.Create(m_transform.position, m_transform.angle + gk::PI, 20, 1, gk::Color::red, 0.5, 100, 200);

        m_transform.Update();
    }
    void Projectile::OnCollision(Actor* actor)
    {
        if (actor->GetType() == eType::ENEMY)
        {
            m_destroy = true;
        }
    }
}