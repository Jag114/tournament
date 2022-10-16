#include <iostream>
#include <string>
#include <cstdlib>

class Warrior {
public:
    std::string Name;
    unsigned int Hp = 1;
    unsigned int Atk = 1;
};

class WarriorEnemy : public Warrior {
public:
    unsigned int expAmount;
};

class WarriorPlayer : public Warrior {
public:
    unsigned int Lvl = 1;
    unsigned int availableStatPoints = 10;
    unsigned int hpToPointsRatio = 2;
    unsigned int atkToPointsRatio = 1;
    unsigned int pointsPerLvl = 2;
    int stamina = 10;
    int gold = 10;
};

int getStats(WarriorPlayer &object) {
    std::cout << "Name: " << object.Name << "\n" << "Health points: " << object.Hp << "\n" << "Atk points: " << object.Atk <<"\n";
    std::cout << "Stamina: " << object.stamina << std::endl;
    std::cout << "Gold amount: " << object.gold << std::endl;
    std::cout << "Stat points left: " << object.availableStatPoints << std::endl;
    return 0;
}

int changeStat(int type, WarriorPlayer &object) {
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
                object.Atk += addedStats * object.atkToPointsRatio;
                break;
            case 2:
                object.Hp += addedStats * object.hpToPointsRatio;
                break;
            default:
                break;
            }
            return 0;
        }
    } 

    std::cout << "Not enough stat points for "<< typeName << " enchance" << std::endl;
    return 0;
}

int changeName(WarriorPlayer &object) {
    std::string name;
    std::cout << "Set your gladiator's name: ";
    std::cin >> name;
    object.Name = name;
    std::cout << "Your gladiator's name is: " << object.Name << "\n";
    return 0;
}

int train(WarriorPlayer &object) {
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
                object.Atk++;
                std::cout << "Atk enchanced from" << object.Atk - 1 << " to " << object.Atk <<", current stamina: "<< object.stamina << std::endl;
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
                object.Hp++;
                object.stamina--;
                std::cout << "Hp enchanced from" << object.Hp - 1 << " to " << object.Hp << ", current stamina: " << object.stamina << std::endl;
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

int inn(WarriorPlayer &object) {
    int option;
    std::cout << "What do you want to do: \n1. Sleep in stable: -2G, +1 Stamina\n2. Sleep on 1st floor: -4G +5 Stamina\n3. Sleep on 2nd floor: -10G, +20 Stamina\n4. Leave\n";
    std::cin >> option;
    switch (option)
    {
    case 1:
        if (object.gold >= 2) {
            object.gold -= 2;
            object.stamina += 1;
            std::cout << "You didn't sleep well, recovered 1 stamina point, current stamina: "<<object.stamina << std::endl;
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

int church(WarriorPlayer &object) {
    int option;
    std::cout << "What do you want to do: \n1. Pray: -1 Stamina, +1 Hp\n2. Get cleansed: -5G, +3Hp\n3. Ask for blessing: -10G, +10 Hp\n4. Leave\n";
    std::cin >> option;
    switch (option)
    {
    case 1:
        if (object.stamina >= 1) {
            object.stamina -= 1;
            object.Hp += 1;
            std::cout << "You feel better, recovered 1 health point, current hp: " << object.Hp << " current stamina: " << object.stamina << std::endl;
        }
        else {
            std::cout << "Not enough stamina, current stamina: " << object.stamina << " 1 needed" << std::endl;
        }
        break;
    case 2:
        if (object.gold >= 5) {
            object.gold -= 5;
            object.Hp += 3;
            std::cout << "You feel at peace, recovered 3 health points, current Hp: " << object.Hp << std::endl;
            std::cout << "Gold left: " << object.gold << std::endl;
        }
        else {
            std::cout << "Not enough gold, " << object.gold << " in eq, 5 needed" << std::endl;
        }
        break;
    case 3:
        if (object.gold >= 10) {
            object.gold -= 10;
            object.Hp += 10;
            std::cout << "You feel better than ever, recovered 10 health points, current Hp: " << object.Hp << std::endl;
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

int jobMenu(WarriorPlayer &object) {
    printf("NO");
    return 0;
}

WarriorEnemy createEnemy(WarriorPlayer &object) {
    WarriorEnemy enemy;
    //atk, hp, exp based on player lvl
    return enemy;
}

int main()
{   
    WarriorPlayer test;
    std::cout << "Name your gladiator: " << std::endl;
    changeName(test);
    for (;;) {
        int option;
        printf("\nMain Menu\n");
        printf("1. Character stats\n2. Redistribute stat points\n3. Train\n4. Go to inn\n");
        printf("5. Go to smithy\n6. Go to church\n7. Go to arena\n8. Earn money\n9. Exit game\n");
        std::cin >> option;
        printf("\n");
        switch (option)
        {
        case 1:
            getStats(test);
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
            break;
        case 5:
            std::cout << "Smithy not yet built" << std::endl;
            break;
        case 6:
            church(test);
            break;
        case 7:
            std::cout << "Arena not yet built" << std::endl;
            break;
        case 8:
            jobMenu(test);
            break;
        case 9:
            return 0;
            break;
        default:
            break;
        }
    }
    
   
    return 0;
}

/*
    TODO:
    1.1 save/s

    2.1 eq
    2.2 shop

    3.1 arena
    3.2 enemy generator 
    3.3 death
    3.4 fight mechanics

    4.1 additional stats (crit rate, crit dmg)
    4.2 stat modifiers
    4.3 exp thresholds
    4.4 stat points gained per lvl
    4.5 abilities

    5.1 get gold
    5.2 cut wood +gold +stats, -stamina
    5.3 mine +gold +stats, -stamina
    5.4 hunt +gold (0 to +++ chance), ++stats, -stamina, -hp chance
*/

