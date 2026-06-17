#pragma once

#include <fstream>
#include <string>

#include "physics/Particle.hpp"
#include "physics/Spring.hpp"

class CSVLogger
{
private:
    std::ofstream file;

public:
    CSVLogger(const std::string& path);
    ~CSVLogger();

    void writeParticleHeader();

    void writeSpringHeader();

    void logParticle(float time, const Particle& particle);

    void logSpring(float time, const SpringMass& mass);
};