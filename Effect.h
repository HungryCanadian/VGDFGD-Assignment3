#pragma once

struct Effect {
	int healing;
	int damage;
	int duration;

	Effect(int healing = 0, int damage = 0, int duration = 0)
		:healing(healing), damage(damage), duration(duration) {	}

};