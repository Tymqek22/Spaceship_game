#pragma once

#include "Powerup.h"

class PowerupShield : public Powerup
{
public:
	PowerupShield();
	~PowerupShield();

	void activate() override;

};

