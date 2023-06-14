#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <random>

#include "Item.h"
#include "Bag.h"
#include "DefensiveItem.h"
#include "OffensiveItem.h"
#include "Helmet.h"
#include "Chestplate.h"
#include "Greaves.h"
#include "Pauldron.h"
#include "Sword.h"
#include "Warrior.h"
#include "WarriorEnemy.h"
#include "WarriorPlayer.h"
#include "Shop.h"

void assignRandomStats(Item& item) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 15); //different distribution for different items, lvls
    std::cout << dist(rd);
}

int main()
{
    std::string name;
    int day = 0;
    WarriorPlayer player;
    Bag eq;
    Shop shop;

    std::cout << "Name your gladiator: " << std::endl;
    std::cin >> name;
    player.giveName(name);

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
            player.getStats();
            break;
        case 2:
            player.changeStat();
            break;
        case 3:
            player.train();
            break;
        case 4:
            player.inn();
            day++;
            break;
        case 5:
        {
            shop.displayItems();
            shop.menu(eq, player);
            break;
        }
        case 6:
            player.temple();
            break;
        case 7:
            player.arena();
            day++;
            break;
        case 8:
            player.jobMenu();
            break;
        case 9:
            eq.displayItems();
            break;
        case 10:
            return 0;
        default:
            break;
        }

        player.levelUp();
        if (player.deathCheck() == 0) {
            std::cout << "\nYou died, survived " << day << " day/s" << std::endl;
            std::cout << "Your statistics:" << std::endl;
            player.getStats();
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

