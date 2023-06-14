#pragma once

class Item {
public:
    std::string name;
    int weight;
    int value;
    int baseDurability;
    int currentDurability;
public:
    void displayItem() {
        printf("Item Display\n");
        std::cout << "Name: " << this->name << std::endl;
        std::cout << "Weight: " << this->weight << std::endl;
        std::cout << "Value (g): " << this->value << std::endl;
        std::cout << "Durability: " << this->currentDurability << " / " << this->baseDurability << std::endl;
        std::cout << std::endl;
    }
};