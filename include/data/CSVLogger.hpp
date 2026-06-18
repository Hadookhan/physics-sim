#pragma once

#include <fstream>
#include <string>

#include "physics/Particle.hpp"
#include "physics/Spring.hpp"
#include "physics/Orbit.hpp"

class CSVLogger
{
private:
    std::ofstream file;

public:
    CSVLogger(const std::string& path);
    ~CSVLogger();

    void writeParticleHeader();

    void writeSpringHeader();

    void writeOrbitHeader();

    void logParticle(float time, const Particle& particle);

    void logSpring(float time, const SpringMass& mass);

    void logOrbit(float time, const OrbitSystem& system);
};