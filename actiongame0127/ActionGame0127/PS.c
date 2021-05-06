//Header file related to the implementation
#include "PS.h"

#include "Emitter.h"
#include "Particle.h"

void ParticleSystemInit(void)
{
	EmitterInit();
}
void ParticleSystemUpdate(float dt)
{
	EmitterUpdate(dt);
	EmitterDelete();
}
void ParticleSystemDraw(void)
{
	EmitterDraw();
}
void ParticleSystemShutdown(void)
{
	EmitterAllDelete();
}