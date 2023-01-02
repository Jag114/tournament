#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <random>

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


class DefensiveItem : public Item {
public:
    int armorStat;
};

class OffensiveItem : public Item {
public:
    int atkStat;
};

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
        this->critDown = rand() % 5 + 1;
    }

    void displayItem() {
        Item::displayItem();
        std::cout << "Crit Down: " << this->critDown << std::endl;
    }
};

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
        std::cout << "Name: " << this->name << std::endl;
        std::cout << "Weight: " << this->weight << std::endl;
        std::cout << "Value (g): " << this->value << std::endl;
        std::cout << "Durability: " << this->currentDurability << " / " << this->baseDurability << std::endl;
        std::cout << "Crit Down: " << this->maxHpUp << std::endl;
    }
};

class Greaves : public DefensiveItem {
public:
    int staminaCostDown;
};

class Pauldron : public DefensiveItem {
public:
    int extraTurnChanceUp;
};

class Sword : public OffensiveItem {
public:
    int bleedChance;
};

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

class WarriorPlayer : public Warrior {
public:
    int maxHp = 10; //10 default
    int lvl = 1;
    int exp = 0;
    int availableStatPoints = 10;
    int hpToPointsRatio = 2;
    int atkToPointsRatio = 1;
    int pointsPerLvl = 2;
    int stamina = 10; //10 default
    int gold = 10;

public:
    WarriorPlayer() {
        this->hp = maxHp;
    }

    void levelUp() {
        while (this->exp >= 10)
        {
            std::cout << "Level up!" << std::endl;
            this->lvl++;
            this->exp -= 10;
            this->availableStatPoints += 2;
            this->hp = this->maxHp;
        }
    }

    int deathCheck() {
        if (this->hp <= 0) {
            return 0;
        }
        return 1;
    }

    void getStats() {
        std::cout << "Name: " << this->name << std::endl;
        std::cout << "Health points: " << this->hp << "/" << this->maxHp << std::endl;
        std::cout << "Attack points: " << this->atk << std::endl;
        std::cout << "Level: " << this->lvl << std::endl;
        std::cout << "Experience: " << this->exp << std::endl;
        std::cout << "Crit rate: " << this->critRate << std::endl;
        std::cout << "Stamina: " << this->stamina << std::endl;
        std::cout << "Gold amount: " << this->gold << std::endl;
        std::cout << "Stat points left: " << this->availableStatPoints << std::endl;
    }

    WarriorEnemy createEnemy() { //better name generation
        std::string enemyName = "Enemy";
        WarriorEnemy enemy;
        enemy.giveName(enemyName);
        enemy.giveStats(this->atk, this->hp);
        return enemy;
    }

    void changeStat() {
        int type;
        int addedStats;
        std::string typeName;
        int atkBefore;
        int hpBefore;
        if (this->availableStatPoints > 0) {
            std::cout << "You have " << this->availableStatPoints << " points to redistribute for your gladiator's statistics" << "\n";
            std::cout << "Which stat do you want to enchance?" << std::endl;
            std::cout << "1 - Atk\n2 - Max Hp\n";
            std::cin >> type;
            if (type != 1 && type != 2) {
                std::cout << "Invalid option" << std::endl;
                return;
            }
            std::cout << "How many of them do you want to use?" << std::endl;
            std::cin >> addedStats;
            if (addedStats <= this->availableStatPoints) {
                this->availableStatPoints = this->availableStatPoints - addedStats;
                switch (type)
                {
                case 1:
                    atkBefore = this->atk;
                    this->atk += addedStats * this->atkToPointsRatio;
                    std::cout << "Atk changed from: " << atkBefore << ", to: " << this->atk << std::endl;
                    return;
                case 2:
                    hpBefore = this->maxHp;
                    this->maxHp += addedStats * this->hpToPointsRatio;
                    std::cout << "Max Hp changed from: " << hpBefore << ", to: " << this->maxHp << std::endl;
                    return;
                default:
                    std::cout << "Zly wybor" << std::endl;
                    return;
                }
            }
        }
        std::cout << "Not enough stat points for " << typeName << " enchance" << std::endl;
        return;
    }

    void inn() {
        int option;
        std::cout << "What do you want to do: \n1. Sleep in stable: -2G, +1 Stamina\n2. Sleep on 1st floor: -4G +5 Stamina\n3. Sleep on 2nd floor: -10G, +20 Stamina\n4. Leave\n";
        std::cin >> option;
        switch (option)
        {
        case 1:
            if (this->gold >= 2) {
                this->gold -= 2;
                this->stamina += 1;
                std::cout << "You didn't sleep well, recovered 1 stamina point, current stamina: " << this->stamina << std::endl;
                std::cout << "Gold left: " << this->gold << std::endl;
            }
            else {
                std::cout << "Not enough gold, " << this->gold << " in eq, 2 needed" << std::endl;
            }
            break;
        case 2:
            if (this->gold >= 4) {
                this->gold -= 4;
                this->stamina += 5;
                std::cout << "You slept well, recovered 5 stamina points, current stamina: " << this->stamina << std::endl;
                std::cout << "Gold left: " << this->gold << std::endl;
            }
            else {
                std::cout << "Not enough gold, " << this->gold << " in eq, 4 needed" << std::endl;
            }
            break;
        case 3:
            if (this->gold >= 10) {
                this->gold -= 10;
                this->stamina += 20;
                std::cout << "You had the best night of your life, recovered 20 stamina points, current stamina: " << this->stamina << std::endl;
                std::cout << "Gold left: " << this->gold << std::endl;
            }
            else {
                std::cout << "Not enough gold, " << this->gold << " in eq, 10 needed" << std::endl;
            }
            break;
        case 4:
            std::cout << "You leave the inn" << std::endl;
            return;
            break;
        default:
            break;
        }
        return;
    }

    void changeName() {
        std::string newName;
        std::cout << "Set your gladiator's name: ";
        std::cin >> newName;
        this->name = newName;
        std::cout << "Your gladiator's name is: " << this->name << "\n";
        return;
    }

    void train() {
        int stat, chance;
        if (this->stamina > 0) {
            srand(time(NULL));
            std::cout << "Which statistic do you want to train?\n1. Atk\n2. Hp\n3. Leave\n";
            std::cin >> stat;
            switch (stat)
            {
            case 1:
                this->stamina--;
                chance = rand() % 100 + 1;
                if (chance <= 8) { //base it on luck (literally as in luck stat)?
                    this->atk++;
                    std::cout << "atk enchanced from" << this->atk - 1 << " to " << this->atk << ", current stamina: " << this->stamina << std::endl;
                    return;
                }
                else {
                    std::cout << "Nothing happened, current stamina: " << this->stamina << std::endl;
                    return;
                }
                break;
            case 2:
                this->stamina--;
                chance = rand() % 100 + 1;
                if (chance <= 8) {
                    this->hp++;
                    this->stamina--;
                    std::cout << "Hp enchanced from" << this->hp - 1 << " to " << this->hp << ", current stamina: " << this->stamina << std::endl;
                    return;
                }
                else {
                    std::cout << "Nothing happened, current stamina: " << this->stamina << std::endl;
                    return;
                }
            case 3:
                return;
                break;
            default:
                break;
            }
        }
        else {
            std::cout << "Not enough stamina" << std::endl;
            return;
        }
        return;
    }

    void temple() {
        int option;
        std::cout << "What do you want to do: \n1. Pray: -1 Stamina, +1 Hp\n2. Get cleansed: -5G, +3Hp\n3. Ask for blessing: -10G, +10 Hp\n4. Leave\n";
        std::cin >> option;
        switch (option)
        {
        case 1:
            if (this->stamina >= 1) {
                this->stamina -= 1;
                this->hp += 1;
                std::cout << "You feel better, recovered 1 health point, current Hp: " << this->hp << " current stamina: " << this->stamina << std::endl;
            }
            else {
                std::cout << "Not enough stamina, current stamina: " << this->stamina << " 1 needed" << std::endl;
            }
            break;
        case 2:
            if (this->gold >= 5) {
                this->gold -= 5;
                this->hp += 3;
                std::cout << "You feel at peace, recovered 3 health points, current Hp: " << this->hp << std::endl;
                std::cout << "Gold left: " << this->gold << std::endl;
            }
            else {
                std::cout << "Not enough gold, " << this->gold << " in eq, 5 needed" << std::endl;
            }
            break;
        case 3:
            if (this->gold >= 10) {
                this->gold -= 10;
                this->hp += 10;
                std::cout << "You feel better than ever, recovered 10 health points, current Hp: " << this->hp << std::endl;
                std::cout << "Gold left: " << this->gold << std::endl;
            }
            else {
                std::cout << "Not enough gold, " << this->gold << " in eq, 10 needed" << std::endl;
            }
            break;
        case 4:
            std::cout << "You leave the church" << std::endl;
            return;
            break;
        default:
            break;
        }
        return;
    }

    void battle(WarriorEnemy& enemyObject) {
        int turn = 0;
        if (this->stamina > 0) {
            for (;;) {
                std::cout << "\nPlayer stats: " << std::endl;
                std::cout << "Atk: " << this->atk << std::endl;
                std::cout << "Hp: " << this->hp << "/" << this->maxHp << std::endl;
                std::cout << "Stamina: " << this->stamina << std::endl;

                std::cout << "Enemy stats: " << std::endl;
                std::cout << "Atk: " << enemyObject.atk << std::endl;
                std::cout << "Hp: " << enemyObject.hp << std::endl;

                if (this->hp <= 0 || enemyObject.hp <= 0) {
                    std::string winner = (enemyObject.hp <= 0) ? this->name : enemyObject.name;
                    std::cout << winner << " wins!" << std::endl;
                    if (winner == this->name) {
                        this->exp += enemyObject.expAmount;
                        this->gold += enemyObject.goldAmount;
                    }
                    return;
                }
                else {
                    if (turn % 2 == 0) {
                        if (this->stamina <= 0) {
                            this->stamina += 2;
                        }
                        else {
                            std::cout << "Player attacks" << std::endl;
                            int crit = rand() % 100 + 1; // 1 - 100
                            if (crit <= this->critRate) {
                                enemyObject.hp -= this->atk * this->critDmg;
                                printf("HOLY SHIT IT ACTUALLY CRITS LOOK HERE - ");
                            }
                            else {
                                enemyObject.hp -= this->atk;
                            }
                            this->stamina--;
                        }
                    }
                    else {
                        std::cout << "Enemy attacks" << std::endl;
                        this->hp -= enemyObject.atk;
                    }
                    turn++;
                }
            }
        }
        else {
            std::cout << "Not enough stamina to fight: " << this->stamina << std::endl;
        }

        return;
    }

    void arena() { //stamina req, more rewards, some kind of progress, bosses
        std::cout << "Arena" << std::endl;
        WarriorEnemy enemy;
        this->battle(enemy);
        return;
    }

    void jobMenu() {
        printf("Job menu");
        printf("1. Cut wood, +3G, -3 Stamina, some stats up or sth");
        int option;
        std::cin >> option;
        switch (option)
        {
        case 1:
            this->gold += 3;
            this->stamina -= 3;
            break;
        default:
            break;
        }
        return;
    }
};

class Shop {
private:
    Bag shopItems;

    Bag createShop() {
        Bag shop;
        Helmet helmet;
        Chestplate chestplate;
        shop.addToEQ(helmet);
        shop.addToEQ(chestplate);
        return shop;
    }
public:
    Shop() {
        this->shopItems = createShop();
    };

    void menu(Bag& eq) {
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
            buyItem(eq);
            Helmet helm;
            this->shopItems.addToEQ(helm);
        }
        else if(option == 2) {
            sellItem(eq);
        }
    }

    void displayItems() {
        this->shopItems.displayItems();
    }

    void buyItem(Bag& eq) {
        int itemIndex;
        std::cout << "Which item do you want to buy?" << std::endl;
        std::cin >> itemIndex;
        Item removedItem = this->shopItems.removeFromBag(itemIndex);
        eq.addToEQ(removedItem);
    }

    void sellItem(Bag& eq) {
        printf("Cant sell here traveler\n");
    }
};



int main()
{
    {
        //separate function
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(1, 15); //different distribution for different items
        std::cout << dist(rd);
    }

    std::string name;
    int day = 0;
    WarriorPlayer test;
    Bag eq;
    Shop shop;

    std::cout << "Name your gladiator: " << std::endl;
    std::cin >> name;
    test.giveName(name);

    for (;;) {
        srand(time(NULL));
        int option;
        printf("\nMain Menu\n");
        std::cout << "Day: " << day << std::endl;
        printf("1. Character stats\n2. Redistribute stat points\n3. Train\n4. Go to inn\n");
        printf("5. Go to smithy\n6. Go to church\n7. Go to arena\n8. Earn money\n9. EQ\n10. Exit\n");
        std::cin >> option;
        printf("\n");
        switch (option)
        {
        case 1:
            test.getStats();
            break;
        case 2:
            test.changeStat();
            break;
        case 3:
            test.train();
            break;
        case 4:
            test.inn();
            day++;
            break;
        case 5:
        {
            shop.displayItems();
            shop.menu(eq);
            break;
        }
        case 6:
            test.temple();
            break;
        case 7:
            test.arena();
            day++;
            break;
        case 8:
            test.jobMenu();
            break;
        case 9:
            eq.displayItems();
            break;
        case 10:
            return 0;
        default:
            break;
        }

        test.levelUp();
        if (test.deathCheck() == 0) {
            std::cout << "\nYou died, survived " << day << " day/s" << std::endl;
            std::cout << "Your statistics:" << std::endl;
            test.getStats();
        }


    }
    return 0;
}



/*
    TODO:
    1.1 save/s

    2.1 eq
    2.2 shop
    2.3 fix healing

    3.1 fight mechanics

    4.1 additional stats (crit rate, crit dmg?, dodge chance)
    4.2 stat modifiers
    4.3 exp thresholds
    4.4 stat points gained per lvl
    4.5 abilities
    4.6 max hp

    5.1 get gold
    5.2 cut wood +gold +stats, -stamina
    5.3 mine +gold +stats, -stamina
    5.4 hunt +gold (0 to +++ chance), ++stats, -stamina, -hp chance
*/

