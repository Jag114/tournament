#pragma once

class Chestplate : public DefensiveItem {
public:
    int maxHpUp;
public:
    Chestplate() { //lvl parameter for balance
        srand(time(NULL));
        name = "Chestplate";
        weight = rand() % 8 + 2;
        value = rand() % 15 + 5;
        baseDurability = rand() % 30 + 10;
        currentDurability = baseDurability;
    }

    void displayItem() {
        Item::displayItem();
        std::cout << "Max Hp up: " << this->maxHpUp << std::endl;
    }
};