#include "stdafx.h"
#include "ParticleManager.h"
#include <memory>

#include "BulletParticle.h"
#include "Debug.h"
#include "DamageAmountParticle.h"

struct ParticleManager::Impl
{
	Array<std::shared_ptr<IParticle>> _ptr_particle_list;

	int32 _writeline_index = 4;
	int32 _bullet_particle_count = 0;
	int32 _damage_amount_particle_count = 0;

	void updateParticles(double delta_time)
	{
		//Particleのアップデートを実行
		//なおかつnot is_activeなものを削除
		_ptr_particle_list.remove_if([delta_time](const std::shared_ptr<IParticle>& ptr_particle)
		{
			bool is_particle_active = ptr_particle->update(
				delta_time,
				ptr_particle->getAccumulatedTime() + delta_time);
			return not is_particle_active;
		});
	}

	void analyzeParticles()
	{
		_bullet_particle_count = 0;
		_damage_amount_particle_count = 0;

		for (auto& ptr_particle : _ptr_particle_list)
		{
			if (auto ptr = dynamic_cast<BulletParticle*>(ptr_particle.get()))
			{
				_bullet_particle_count++;
				continue;
			}

			if (auto ptr = dynamic_cast<DamageAmountParticle*>(ptr_particle.get()))
			{
				_damage_amount_particle_count++;
				continue;
			}
		}
	}

	void writelineParticles()
	{
		Debug::getInstance().writeline(_writeline_index, U"BulletParticle Count : " + Format(_bullet_particle_count));
		Debug::getInstance().writeline(_writeline_index, U"DamageAmountParticle Count : " + Format(_damage_amount_particle_count));
	}
};

ParticleManager::ParticleManager() : p_impl(std::make_shared<Impl>())
{
}

void ParticleManager::init()
{
}

void ParticleManager::update(double delta_time)
{
	p_impl->updateParticles(delta_time);

	if (Debug::getInstance().getDebugScreenIndex() == p_impl->_writeline_index)
	{
		p_impl->analyzeParticles();
		p_impl->writelineParticles();
	}
}

void ParticleManager::draw() const
{
	for (auto& ptr_particle : p_impl->_ptr_particle_list)
	{
		ptr_particle->draw();
	}
}


void ParticleManager::addParticle(std::shared_ptr<IParticle> ptr_particle)
{
	p_impl->_ptr_particle_list << ptr_particle;
}
