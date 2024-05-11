#pragma once
#include "Powerup.h"

class PowerupMultishoot : public Powerup
{
public:
	PowerupMultishoot();
	~PowerupMultishoot();

	void activate() override;
};

