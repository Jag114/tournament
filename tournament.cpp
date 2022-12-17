#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

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
};

class Item {
public:
    std::string name;
    int weight;
    int value;
    int baseDurability;
    int currentDurability;

    Item() { //lvl parameter for balance
        srand(time(NULL));
        name = "test_helmet";
        weight = rand() % 5 + 1;
        value = rand() % 10 + 2;
        baseDurability = rand() % 15 + 5;
        currentDurability = baseDurability;
    }
};

class Bag {
public:
    int bagSize = 10;
    std::vector<Item> bagItems;

    Bag() {}
    
    void displayItems() {
        for (int i = 0; i < bagItems.size(); i++) {
            std::cout << "Name: " << bagItems[i].name << std::endl;
            std::cout << "Weight: " << bagItems[i].weight << std::endl;
            std::cout << "Value (g): " << bagItems[i].value << std::endl;
            std::cout << "Durability: " << bagItems[i].currentDurability << " / " << bagItems[i].baseDurability << std::endl;
        }
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
};

class Chestplate : public DefensiveItem {
public:
    int maxHpUp;
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



WarriorEnemy createEnemy(WarriorPlayer& object) { //better name generation
    WarriorEnemy enemy;
    enemy.name = "Enemy";
    srand(time(NULL));
    enemy.atk = rand() % object.atk + 1;
    enemy.hp = rand() % object.hp + 5;
    enemy.expAmount = rand() % 8 + 2;
    enemy.goldAmount = rand() % 5 + 1;
    return enemy;
}

int changeStat(int type, WarriorPlayer& object) {
    int addedStats;
    std::string typeName = (type == 1) ? "Atk" : "Hp";
    if (object.availableStatPoints > 0) {
        std::cout << "You have " << object.availableStatPoints << " points to redistribute for your gladiator's statistics" << "\n";
        std::cout << "How many of them do you want to use to enhance " << typeName << "?" << std::endl;
        std::cin >> addedStats;
        if (addedStats <= object.availableStatPoints) {

            object.availableStatPoints = object.availableStatPoints - addedStats;
            switch (type)
            {
            case 1:
                object.atk += addedStats * object.atkToPointsRatio;
                break;
            case 2:
                object.maxHp += addedStats * object.hpToPointsRatio;
                break;
            default:
                break;
            }
            return 0;
        }
    }

    std::cout << "Not enough stat points for " << typeName << " enchance" << std::endl;
    return 0;
}

int changeName(Warrior& object) {
    std::string newName;
    std::cout << "Set your gladiator's name: ";
    std::cin >> newName;
    object.name = newName;
    std::cout << "Your gladiator's name is: " << object.name << "\n";
    return 0;
}

int train(WarriorPlayer& object) {
    int stat, chance;
    if (object.stamina > 0) {
        srand(time(NULL));
        std::cout << "Which statistic do you want to train?\n1. Atk\n2. Hp\n3. Leave\n";
        std::cin >> stat;
        switch (stat)
        {
        case 1:
            object.stamina--;
            chance = rand() % 100 + 1;
            if (chance <= 8) {
                object.atk++;
                std::cout << "atk enchanced from" << object.atk - 1 << " to " << object.atk << ", current stamina: " << object.stamina << std::endl;
                return 0;
            }
            else {
                std::cout << "Nothing happened, current stamina: " << object.stamina << std::endl;
                return 0;
            }
            break;
        case 2:
            object.stamina--;
            chance = rand() % 100 + 1;
            if (chance <= 8) {
                object.hp++;
                object.stamina--;
                std::cout << "Hp enchanced from" << object.hp - 1 << " to " << object.hp << ", current stamina: " << object.stamina << std::endl;
                return 0;
            }
            else {
                std::cout << "Nothing happened, current stamina: " << object.stamina << std::endl;
                return 0;
            }
        case 3:
            return 0;
            break;
        default:
            break;
        }
    }
    else {
        std::cout << "Not enough stamina" << std::endl;
        return 0;
    }
}

int inn(WarriorPlayer& object) {
    int option;
    std::cout << "What do you want to do: \n1. Sleep in stable: -2G, +1 Stamina\n2. Sleep on 1st floor: -4G +5 Stamina\n3. Sleep on 2nd floor: -10G, +20 Stamina\n4. Leave\n";
    std::cin >> option;
    switch (option)
    {
    case 1:
        if (object.gold >= 2) {
            object.gold -= 2;
            object.stamina += 1;
            std::cout << "You didn't sleep well, recovered 1 stamina point, current stamina: " << object.stamina << std::endl;
            std::cout << "Gold left: " << object.gold << std::endl;
        }
        else {
            std::cout << "Not enough gold, " << object.gold << " in eq, 2 needed" << std::endl;
        }
        break;
    case 2:
        if (object.gold >= 4) {
            object.gold -= 4;
            object.stamina += 5;
            std::cout << "You slept well, recovered 5 stamina points, current stamina: " << object.stamina << std::endl;
            std::cout << "Gold left: " << object.gold << std::endl;
        }
        else {
            std::cout << "Not enough gold, " << object.gold << " in eq, 4 needed" << std::endl;
        }
        break;
    case 3:
        if (object.gold >= 10) {
            object.gold -= 10;
            object.stamina += 20;
            std::cout << "You had the best night of your life, recovered 20 stamina points, current stamina: " << object.stamina << std::endl;
            std::cout << "Gold left: " << object.gold << std::endl;
        }
        else {
            std::cout << "Not enough gold, " << object.gold << " in eq, 10 needed" << std::endl;
        }
        break;
    case 4:
        std::cout << "You leave the inn" << std::endl;
        return 0;
        break;
    default:
        break;
    }
    return 0;
}

int church(WarriorPlayer& object) {
    int option;
    std::cout << "What do you want to do: \n1. Pray: -1 Stamina, +1 Hp\n2. Get cleansed: -5G, +3Hp\n3. Ask for blessing: -10G, +10 Hp\n4. Leave\n";
    std::cin >> option;
    switch (option)
    {
    case 1:
        if (object.stamina >= 1) {
            object.stamina -= 1;
            object.hp += 1;
            std::cout << "You feel better, recovered 1 health point, current Hp: " << object.hp << " current stamina: " << object.stamina << std::endl;
        }
        else {
            std::cout << "Not enough stamina, current stamina: " << object.stamina << " 1 needed" << std::endl;
        }
        break;
    case 2:
        if (object.gold >= 5) {
            object.gold -= 5;
            object.hp += 3;
            std::cout << "You feel at peace, recovered 3 health points, current Hp: " << object.hp << std::endl;
            std::cout << "Gold left: " << object.gold << std::endl;
        }
        else {
            std::cout << "Not enough gold, " << object.gold << " in eq, 5 needed" << std::endl;
        }
        break;
    case 3:
        if (object.gold >= 10) {
            object.gold -= 10;
            object.hp += 10;
            std::cout << "You feel better than ever, recovered 10 health points, current Hp: " << object.hp << std::endl;
            std::cout << "Gold left: " << object.gold << std::endl;
        }
        else {
            std::cout << "Not enough gold, " << object.gold << " in eq, 10 needed" << std::endl;
        }
        break;
    case 4:
        std::cout << "You leave the church" << std::endl;
        return 0;
        break;
    default:
        break;
    }
    return 0;
}

int battle(WarriorPlayer& playerObject, WarriorEnemy& enemyObject, int& date) {
    int turn = 0;
    if (playerObject.stamina > 0) {
        for (;;) {
            std::cout << "\nPlayer stats: " << std::endl;
            std::cout << "Atk: " << playerObject.atk << std::endl;
            std::cout << "Hp: " << playerObject.hp << "/" << playerObject.maxHp << std::endl;
            std::cout << "Stamina: " << playerObject.stamina << std::endl;

            std::cout << "Enemy stats: " << std::endl;
            std::cout << "Atk: " << enemyObject.atk << std::endl;
            std::cout << "Hp: " << enemyObject.hp << std::endl;

            if (playerObject.hp <= 0 || enemyObject.hp <= 0) {
                std::string winner = (enemyObject.hp <= 0) ? playerObject.name : enemyObject.name;
                std::cout << winner << " wins!" << std::endl;
                if (winner == playerObject.name) {
                    playerObject.exp += enemyObject.expAmount;
                    playerObject.gold += enemyObject.goldAmount;
                }
                date++;
                return 0;
            }
            else {
                if (turn % 2 == 0) {
                    if (playerObject.stamina <= 0) {
                        playerObject.stamina += 2;
                    }
                    else {
                        std::cout << "Player attacks" << std::endl;
                        int crit = rand() % 100 + 1; // 1 - 100
                        if (crit <= playerObject.critRate) {
                            enemyObject.hp -= playerObject.atk * playerObject.critDmg;
                            printf("HOLY SHIT IT ACTUALLY CRITS LOOK HERE - ");
                        }
                        else {
                            enemyObject.hp -= playerObject.atk;
                        }
                        playerObject.stamina--;
                    }
                }
                else {
                    std::cout << "Enemy attacks" << std::endl;
                    playerObject.hp -= enemyObject.atk;
                }
                turn++;
            }
        }
    }
    else {
        std::cout << "Not enough stamina to fight: " << playerObject.stamina << std::endl;
    }

    return 0;
}

int jobMenu(WarriorPlayer& object) {
    printf("Job menu");
    printf("1. Cut wood, +3G, -3 Stamina, some stats up or sth");
    int option;
    std::cin >> option;
    switch (option)
    {
    case 1:
        object.gold += 3;
        object.stamina -= 3;
        break;
    default:
        break;
    }
    return 0;
}

int arena(WarriorPlayer& object, int& date) { //stamina req, more rewards, some kind of progress, bosses
    printf("Arena");
    WarriorEnemy enemy = createEnemy(object);
    battle(object, enemy, date);
    return 0;
}

int smithy(WarriorPlayer& object) {
    printf("Smithy");
    return 0;
}

int checkEQ(Bag& eq) {
    Item j;

    for (int i = 0; i < eq.bagItems.size(); i++)
    {
        eq.displayItems();
    }

    return 0;
}

int addToEQ(Bag& eq, Item& item) {

    eq.bagItems.push_back(item);

    return 0;
}

int changeCheck() {
        

    return 0;
}

int main()
{
    std::string name;
    int day = 0;
    WarriorPlayer test;
    Bag eq;

    Helmet helmet;
    addToEQ(eq, helmet);

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
            changeStat(1, test);
            changeStat(2, test);
            break;
        case 3:
            train(test);
            break;
        case 4:
            inn(test);
            day++;
            break;
        case 5:
            smithy(test);
            break;
        case 6:
            church(test);
            break;
        case 7:
            arena(test, day);
            break;
        case 8:
            jobMenu(test);
            break;
        case 9:
            checkEQ(eq);
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

