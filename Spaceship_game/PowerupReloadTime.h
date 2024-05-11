#pragma once
#include "Powerup.h"

//activation in a spaceship class

class PowerupReloadTime : public Powerup
{
public:
	PowerupReloadTime();
	~PowerupReloadTime();

	void activate() override;
};

