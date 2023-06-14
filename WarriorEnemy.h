#pragma once

class WarriorEnemy : public Warrior {
public:
    int expAmount;
    int goldAmount;
public:
    void giveStats(int atk, int hp) {
        srand(time(NULL));
        this->atk = rand() % this->atk + 1;
        this->hp = rand() % this->hp + 5;
        this->expAmount = rand() % 8 + 2;
        this->goldAmount = rand() % 5 + 1;
    }
};