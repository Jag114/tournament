#pragma once

class Warrior {
public:
    std::string name;
    int hp;
    int atk = 1;
    int critRate = 1; // 1 to 100, 1 default
    float critDmg = 1.5;
public:
    void giveName(std::string newName) {
        this->name = newName;
    }
};