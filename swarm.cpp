#include "swarm.h"

namespace cTutorial {

Swarm::Swarm(): lastTime{0} {
}

Swarm::~Swarm(){
}

void Swarm::update(int elapsed){
    /* For avoiding running the simulation at different speeds depending
     * on the speed of the PC. The displacement of the particles will be
     * based on actual time. So faster and slower PC will run the animation
     * at the same speed.
     */
    int interval {elapsed - lastTime};

    for(auto& particle: m_particles) {
        particle.update(interval);
    }
    lastTime = elapsed;
}

}
