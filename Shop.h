#pragma once

class Shop {
private:
    std::vector<Item> shopItems;

public:
    Shop() {
        Helmet helmet;
        Chestplate chestplate;
        Helmet helmet2;
        shopItems.push_back(helmet);
        shopItems.push_back(chestplate);
        shopItems.push_back(helmet2);
    };

    void menu(Bag& eq, WarriorPlayer& player) {
        int option;
        bool wrongAnswer = true;
        std::cout << "What do you want to do?" << std::endl;
        std::cout << "1 - Buy\n2 - Sell\n";
        do {
            std::cin >> option;
            if (option != 1 && option != 2) {
                std::cout << "Wrong option chosen" << std::endl;
                std::cin.clear();
                std::cin.ignore(100, '\n');
            }
            else {
                wrongAnswer = false;
            }
        } while (wrongAnswer == true);

        if (option == 1) {
            if (buyItem(eq, player) == true) {
                //restock if bought sth
                Helmet helm;
                this->shopItems.push_back(helm);
            }
        }
        else if (option == 2) {
            sellItem(eq, player);
        }
    }

    void displayItems() {
        for (Item item : this->shopItems) {
            item.displayItem();
        }
    }

    bool buyItem(Bag& eq, WarriorPlayer& player) {
        int itemIndex;
        std::cout << "Which item do you want to buy?" << std::endl;
        std::cin >> itemIndex;
        Item removedItem = shopItems.at(itemIndex);
        if (removedItem.value <= player.gold) {
            eq.addToEQ(removedItem);
            player.gold -= removedItem.value;
            return true;
        }
        else {
            std::cout << "Not enough gold for purchase" << std::endl;
            return false;
        }
        return false;
    }

    void sellItem(Bag& eq, WarriorPlayer& player) {
        printf("Cant sell here traveler\n");
    }
};