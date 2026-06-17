#include <fstream>
#include <string>

#include "physics/Particle.hpp"
#include "physics/Spring.hpp"
#include "data/CSVLogger.hpp"

#include <glm/vec2.hpp>

CSVLogger::CSVLogger(const std::string& path)
{
    file.open(path);
}

CSVLogger::~CSVLogger()
{
    if (file.is_open())
    {
        file.close();
    }
}

void CSVLogger::writeParticleHeader()
{
    file << "time,x,y,vx,vy,NetForce_x,NetForce_y,mass\n";
}

void CSVLogger::logParticle(float time, const Particle& p)
{
    file << time << ","
         << p.position.x << ","
         << p.position.y << ","
         << p.velocity.x << ","
         << p.velocity.y << ","

         << p.netForce.x << ","
         << p.netForce.y << ","

         << p.mass << "\n";
}