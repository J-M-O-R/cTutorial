#ifndef SWARM_H
#define SWARM_H

#include <array>
#include "particle.h"
using namespace std;

namespace cTutorial {

class Swarm {
public:
    constexpr static size_t NPARTICLES{5000};

    Swarm();
    virtual ~Swarm();

    array<Particle,NPARTICLES>& getParticles() { return m_particles; }
    void update(int elapsed);
private:
    array<Particle,NPARTICLES> m_particles;

    int lastTime;

};

}
#endif // SWARM_H
