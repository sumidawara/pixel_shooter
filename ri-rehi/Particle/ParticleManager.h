#pragma once
#include "IParticle.h"
//#include <memory>

class ParticleManager
{
public:
	ParticleManager();
	void init();
	void update(double delta_time);
	void draw() const;

	void addParticle(std::shared_ptr<IParticle> ptr_particle);

private:
	struct Impl;
	std::shared_ptr<Impl> p_impl;
};

