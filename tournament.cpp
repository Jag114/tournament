#include <iostream>
#include <string>

class Warrior {
public:
    std::string Name;
    unsigned int Hp;
    unsigned int Atk;
    unsigned int availableStatPoints;
};

void getStats(Warrior object) {
    std::cout << "Name: " << object.Name << "\n" << "Health points: " << object.Hp << "\n" << "Atk points: " << object.Atk <<"\n";
    std::cout << "Stat points left: " << object.availableStatPoints << std::endl;
}

unsigned int changeStat(int statPoint, int ratio) {
    int addedStats;
    if (statPoint > 0) {
        std::cout << "You have " << statPoint << " points to redistribute for your gladiator's statistics" << "\n";
        std::cout << "How many of them do you want to use to enhance Hp?" << std::endl;
        std::cin >> addedStats;
        statPoint--;
    }
    else {
        std::cout << "Too few stat points" << std::endl;
    }
    return addedStats * ratio;
}

std::string changeName() {
    std::string name;
    std::cout << "Set your gladiator's name: ";
    std::cin >> name;
    return name;
}


int main()
{   
    unsigned int hpToPointsRatio = 2;
    unsigned int atkToPointsRatio = 1;

    Warrior test;
    test.availableStatPoints = 10;
    test.Name = changeName(); 
    std::cout << "Your gladiator's name is: " << test.Name << "\n";
    test.Hp = changeStat(test.availableStatPoints, hpToPointsRatio);
    test.Atk = changeStat(test.availableStatPoints, atkToPointsRatio);
   
    getStats(test);
}

