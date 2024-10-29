#pragma once

struct Effect {
    int healing;
    int damage;
    int duration;
    int damageReduction;
    Effect(int healing = 0, int damage = 0, int duration = 0, int damageReduction = 0)
        : healing(healing), damage(damage), duration(duration), damageReduction(damageReduction) { }
};