#pragma once

class Bag { //combine with player so its not a separate object
public:
    int bagSize = 10;
    std::vector<Item> bagItems;
public:
    Bag() {}

    void displayItems() {
        std::cout << "Bag contents:" << std::endl;
        if (bagItems.size() > 0) {
            for (int i = 0; i < bagItems.size(); i++) {
                bagItems[i].displayItem(); //jak zrobic displayitem dla konkretnego itemu?
            }
        }
        else {
            std::cout << "Empty" << std::endl;
        }
    }

    void addToEQ(Item& item) {
        std::cout << "New item\n" << item.name << std::endl;
        this->bagItems.push_back(item);
    }

    Item removeFromBag(int index) {
        Item removedItem;
        removedItem = this->bagItems.at(index);
        this->bagItems.erase(this->bagItems.begin() + index);
        std::cout << "Updated contents: " << std::endl;
        this->displayItems();
        return removedItem;
    }
};