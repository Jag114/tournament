#include <iostream>
#include <string>

class Warrior {
public:
    std::string Name;
    unsigned int Hp = 1;
    unsigned int Atk = 1;
    unsigned int availableStatPoints = 10;
    unsigned int hpToPointsRatio = 2;
    unsigned int atkToPointsRatio = 1;
};

int getStats(Warrior &object) {
    std::cout << "Name: " << object.Name << "\n" << "Health points: " << object.Hp << "\n" << "Atk points: " << object.Atk <<"\n";
    std::cout << "Stat points left: " << object.availableStatPoints << std::endl;
    return 0;
}

int changeStat(int type, Warrior &object) {
    int addedStats;
    if (object.availableStatPoints > 0) {
        std::cout << "You have " << object.availableStatPoints << " points to redistribute for your gladiator's statistics" << "\n";
        std::cout << "How many of them do you want to use to enhance Hp?" << std::endl;
        std::cin >> addedStats;
        object.availableStatPoints = object.availableStatPoints - addedStats;
        switch (type)
        {
        case 1:
            object.Atk = addedStats * object.atkToPointsRatio;
            break;
        case 2:
            object.Hp = addedStats * object.hpToPointsRatio;
            break;
        default:
            break;
        }
    }
    else {
         std::cout << "Too few stat points" << std::endl;
        return 0;
    }

    return 0;
}

int changeName(Warrior &object) {
    std::string name;
    std::cout << "Set your gladiator's name: ";
    std::cin >> name;
    object.Name = name;
    std::cout << "Your gladiator's name is: " << object.Name << "\n";
    return 0;
}


int main()
{   
    Warrior test;
    changeName(test);
    for (;;) {
        int option;
        printf("Main Menu\n");
        printf("1. Character stats\n2. Enchance stats\n3. Quit\n");
        std::cin >> option;
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
            return 0;
            break;
        default:
            break;
        }
    }
    
   
    return 0;
}

