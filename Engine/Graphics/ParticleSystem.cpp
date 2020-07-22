#include "pch.h"
#include "ParticleSystem.h"
#include "Math/Random.h"
#include "Math/Math.h"

gk::ParticleSystem g_particleSystem;

namespace gk
{
    void ParticleSystem::Startup()
    {
        m_size = 3000;
        m_particles = new Particle[m_size];
    }

    void ParticleSystem::Shutdown()
    {
        delete[] m_particles;
    }

    void ParticleSystem::Update(float dt)
    {
        for (size_t i = 0; i < m_size; i++)
        {
            Particle* p = &m_particles[i];
            if (p->active)
            {
                p->lifetime -= dt;
                p->active = (p->lifetime > 0);

                p->prevPosition = p->position;
                p->position += p->velocity * dt;

                p->velocity *= p->damping;
            }
        }
    }

    void ParticleSystem::Draw(Core::Graphics& graphics)
    {
        for (size_t i = 0; i < m_size; i++)
        {
            Particle* p = &m_particles[i];
            if (p->active)
            {
                graphics.SetColor(p->color);
                graphics.DrawLine(p->position.x, p->position.y, p->prevPosition.x, p->prevPosition.y);
            }
        }
    }

    void ParticleSystem::Create(const Vector2& position, float angle, float angleRange, size_t count, 
                                const Color& color, float lifetime, float speedMin, float speedMax)
    {
        for (size_t i = 0; i < count; i++)
        {
            Particle* p = GetFreeParticle();
            if (p)
            {
                p->active = true;
                p->lifetime = lifetime;
                p->position = position;
                p->prevPosition = position;
                p->color = color;

                float angleRandom = gk::DegreesToRadians(gk::random(-angleRange, angleRange));
                Vector2 direction = Vector2::rotate(Vector2::forward, angle + angleRandom);

                p->velocity = direction * gk::random(speedMin, speedMax);
            }
        }
    }

    Particle* ParticleSystem::GetFreeParticle()
    {
        Particle* freewilly{ nullptr };
        
        for (size_t i = 0; i < m_size; i++)
        {
            Particle* p = &m_particles[i];
            if (!p->active)
            {
                freewilly = p;
                break;
            }
        }

        return freewilly;
    }
}

