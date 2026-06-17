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
    file << "time,x,y,vx,vy,Dfx,Dfy,Gfx,Gfy,Hfx,Hfy,Nfx,Nfy,mass\n";
}

void CSVLogger::logParticle(float time, const Particle& p, glm::vec2 dragForce, glm::vec2 gravityForce, glm::vec2 horizontalForce)
{
    file << time << ","
         << p.position.x << ","
         << p.position.y << ","
         << p.velocity.x << ","
         << p.velocity.y << ","

         << dragForce.x << ","
         << dragForce.y << ","

         << gravityForce.x << "," // I understand this is useless, however I want to capture the complete vector
         << gravityForce.y << ","

         << horizontalForce.x << ","
         << horizontalForce.y << "," // I understand this is useless too, same reason

         << p.netForce.x << ","
         << p.netForce.y << ","

         << p.mass << "\n";
}