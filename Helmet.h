#pragma once

class Helmet : public DefensiveItem {
public:
    int critDown;
public:
    Helmet() { //lvl parameter for balance
        srand(time(NULL));
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(1, 15);
        this->name = "Helmet";
        this->weight = rand() % 5 + 1;
        this->value = rand() % 10 + 2;
        this->baseDurability = rand() % 15 + 5;
        this->currentDurability = baseDurability;
        this->critDown = rand() % 10 + 1;
    }

    void displayItem() {
        Item::displayItem();
        std::cout << "Crit Down: " << this->critDown << std::endl;
    }
};