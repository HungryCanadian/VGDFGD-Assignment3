#include "Rooms.h"
#include "Character.h"
#include "Inventory.h"
#include "Enemy.h"
#include "combat.h"   

//bool skipDelays = false;
void delay(int milliseconds);

Room::Room(string name, string description, bool firstVisit, float attackChance)
    : mName(name), mDescription(description), mFirstVisit(firstVisit), mAttackChance(attackChance) { }


void Room::AddExit(Room* room) {
    mExits.push_back(room);
}

vector<Room*> Room::GetExits() {
    return mExits;
}

int Room::GetNumberOfExits() {
    return mExits.size();
}

void Room::ListExits() {
    if (mExits.empty()) {
        cout << "There is no escape!\n";
    }
    else {
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "  You see the following exits: \n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        for (size_t i = 0; i < mExits.size(); i++) {
            cout << i + 1 << ". " << mExits[i]->GetName() << "\n";
        }
    }
    cout << "\n"; // Blank line for readability
}

string Room::GetName() {
    return mName;
}

void Room::DisplayRoom(Character& player, Inventory& inventory) {
    cout << GetName() << "\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << mDescription << "\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

    if (IsFirstVisit()) {
        if (GetName() == "Tavern") {
            cout << "You wake up in your cozy bed at the tavern, the smell of breakfast wafting through the air.\n";
            delay(3 * 1000);
            cout << "You can hear the chatter of patrons and the clinking of mugs, but your head is pounding.\n";
            delay(3 * 1000);
            cout << "As you sit up, a wave of nausea hits you, and you remember last night's revelry.\n";
            delay(3 * 1000);
            cout << "You feel dehydrated and your mouth is dry; you crave water.\n";
            delay(3 * 1000);
            cout << "A faint light coming through the window only intensifies your headache.\n";
            delay(3 * 1000);
            cout << "You get up slowly and gather your things.\n";
            delay(1 * 1000);
            inventory.displayPlayerInventory();
            delay(5 * 1000);
            cout << "You meander your way out of the room and down the stairs to the tavern.\n\n";
            delay(2 * 1000);
            cout << "'Rough night eh? Well, I would have a hangover too if I drank " << std::rand() % 50 + 1 << " bottles of rum as well.'\n\n";
            delay(2 * 1000);
        }
        else if (GetName() == "Town Center") {
            char tutorial;
            cout << "Hang on! Before you leave! You may need a bit of information.\nDo you know how to fight in these lands? (y/n): ";
            cin >> tutorial;

            if (tutorial == 'n' || tutorial == 'N') {
                cout << "Well then! Hi there, my name is Ryder. \nI will be the friendly voice in your head that helps you out!\n";
                delay(3 * 1000);
                cout << "Don't look around like that; people are going to think you're weird.\n";
                delay(3 * 1000);
                cout << "Let me teach you some things about how combat works in the world of Caspira.\n";
                delay(3 * 1000);

                cout << "\nChoose an action:\n";
                cout << "[1] Attack\n";
                cout << "[2] Defend\n";
                cout << "[3] Use Item\n";
                cout << "[4] Run\n\n";
                delay(3 * 1000);

                cout << "This is what you will see when you enter combat, \nYou don't need to choose anything right now; I'm just giving you an example!\n";
                delay(3 * 1000);
                cout << "[1] Attack should be self-explanatory; \nyou will attack with whatever weapon you have equipped currently.\n";
                delay(3 * 1000);
                cout << "[2] Defend; you will raise your weapon or shield into a defensive position, \nyou will reduce any incoming damage to '1 damage' for that round.\n";
                delay(3 * 1000);
                cout << "[3] Use Item; this will open your inventory and let you choose from a list of usable items, such as potions. \nYou then give up your turn to use that item.\n";
                delay(3 * 1000);
                cout << "[4] Run; you will try to run away from the fight. \nIt is only a 75 percent chance you will run away, and if you fail, the enemy will get a free attack on you.\n";
                delay(3 * 1000);
                cout << "Now that we have gone over the basics of the system. You are now free to explore the world!\n\n";
                delay(2 * 1000);
            }
			else {
				cout << "The Town Center of Caspira pulses with life and activity, serving as the heart of the community.\n";
				delay(3 * 1000);
                cout << "Cobblestone streets radiate from a central square, where a grand fountain bubbles cheerfully, its\n";
                delay(3 * 1000);
                cout << "water shimmering in the sunlight. Surrounding the square, charming buildings with colorful facades\n";
                delay(3 * 1000);
                cout << "house an array of shops and stalls, each overflowing with goods that reflect the town’s vibrant\n";
                delay(3 * 1000);
                cout << "culture. Merchants hawk their wares, from fresh produce and fragrant spices to handmade crafts and\n";
                delay(3 * 1000);
                cout << "shimmering trinkets, creating a lively atmosphere filled with laughter and friendly banter.\n\n";
                delay(3 * 1000);
                cout << "At the center of it all, townsfolk gather to share news and stories, their voices blending into a\n";
                delay(3 * 1000);
                cout << "harmonious chorus. Children dart between stalls, their laughter mingling with the enticing aromas\n";
                delay(3 * 1000);
                cout << "wafting from nearby food vendors who serve steaming bowls of hearty stew and freshly baked\n";
                delay(3 * 1000);
                cout << "pastries. The Town Center is not just a marketplace but a gathering place, where community events\n";
                delay(3 * 1000);
                cout << "and celebrations are held, bringing everyone together in joyous unity. With its vibrant energy and\n";
                delay(3 * 1000);
                cout << "rich tapestry of life, the Town Center embodies the spirit of Caspira—a place where connections are\n";
                delay(3 * 1000);
                cout << "forged and memories are made.\n\n";
			}
            //else {
            //    cout << "\nWatch out!\n";
            //    cout << "Ambush!\nYou were ambushed the moment you exited the town!\n";
            //}

            //Enemy enemy("Goblin", 2, 10);
            //auto inv = inventory.getInv();
            //Combat combat(player, enemy, inv);
            //combat.start();

            //if (!player.isAlive()) {
            //    cout << "Game over man! Game over!\n\n";
            //    exit(0);
            //}
            //else {
            //    cout << "Congratulations on your first victory!";
            //}
            //return; // Exit if combat was initiated
        }
        else if (GetName() == "West Road") {
			cout << "The road begins at the edge of the quaint wooden town, where the last remnants of civilization fade\n";
			delay(3 * 1000);
			cout << "into the wild. Weathered cobblestones, slick with moss and littered with fallen leaves, peek through\n";
			delay(3 * 1000);
			cout << "the thick underbrush that encroaches upon the path. Gnarled roots of ancient trees snake across the\n";
			delay(3 * 1000);
			cout << "way, creating a labyrinthine effect that seems to pull travelers deeper into the forest. The air is thick\n";
			delay(3 * 1000);
			cout << "with the scent of damp earth and decaying foliage, and the distant cawing of crows adds an\n";
			delay(3 * 1000);
			cout << "unsettling note to the atmosphere. Sunlight filters through the dense canopy, casting dappled\n";
			delay(3 * 1000);
			cout << "shadows that dance ominously along the road, hinting at secrets long forgotten.\n\n";
			delay(3 * 1000);
			cout << "As the path winds its way through the undergrowth, the surrounding foliage grows increasingly wild.\n";
			delay(3 * 1000);
			cout << "Briars and thorny vines reach out like skeletal fingers, grasping at anyone brave enough to traverse\n";
			delay(3 * 1000);
            cout << "this forsaken trail. The sound of rustling leaves and the occasional snap of a twig underfoot create an\n";
            delay(3 * 1000);
            cout << "uneasy symphony, making it clear that this road is rarely traveled. A sense of foreboding hangs in the\n";
            delay(3 * 1000);
            cout << "air, as if the very land mourns the passage of those who once journeyed this way. An unsettling chill\n";
            delay(3 * 1000);
            cout << "seeps in, urging travelers to reconsider their venture.\n\n";
            delay(3 * 1000);
            cout << "Eventually, the road opens up to a clearing, revealing the graveyard at its end. Crumbling\n";
            delay(3 * 1000);
            cout << "headstones, some adorned with creeping ivy, stand as solemn sentinels in the fading light. The once-\n";
            delay(3 * 1000);
            cout << "vibrant colors of the town feel distant here, replaced by the muted grays and browns of stone and\n";
            delay(3 * 1000);
            cout << "earth. An eerie silence envelops the graveyard, broken only by the occasional whisper of the wind\n";
            delay(3 * 1000);
            cout << "that carries the tales of those interred beneath the soil. Here, the overgrown road serves as a\n";
            delay(3 * 1000);
            cout << "reminder of mortality, drawing a stark line between the vibrancy of life in the town and the haunting\n";
            delay(3 * 1000);
            cout << "stillness of the resting place that awaits all.3\n";
   		}
        else if (GetName() == "Graveyard") {
            cout << "The graveyard sprawls across a gently undulating hillside, its uneven terrain dotted with aged\n";
            delay(3 * 1000);
            cout << "headstones that lean at precarious angles, as if bowing to the weight of time. At its center, a once-\n";
            delay(3 * 1000);
            cout << "grand crypt stands in a state of disrepair, its imposing structure now draped in creeping vines and\n";
            delay(3 * 1000);
            cout << "moss. Once a monument to the town's esteemed figures—heroes, benefactors, and those of\n";
            delay(3 * 1000);
            cout << "considerable wealth—the crypt's stone facade is now weathered and cracked, with ornate carvings\n";
            delay(3 * 1000);
            cout << "barely discernible beneath the layers of lichen. The heavy iron door, once polished to a brilliant\n";
            delay(3 * 1000);
            cout << "shine, hangs ajar, rusted and forgotten, inviting whispers of curiosity and caution.\n\n";
            delay(3 * 1000);
            cout << "Surrounding the crypt, the ground is uneven, with tombs bearing the names of those who once\n";
            delay(3 * 1000);
            cout << "walked proudly among the living. A thick carpet of moss blankets the earth, softening the harsh\n";
            delay(3 * 1000);
            cout << "edges of the stones, while the air hangs heavy with the scent of damp foliage and decay. Wisps of\n";
            delay(3 * 1000);
            cout << "fog curl around the crypt, lending an ethereal quality to the atmosphere as the ancient oak tree\n";
            delay(3 * 1000);
            cout << "nearby stretches its gnarled branches protectively over the site. Lanterns, long extinguished, dangle\n";
            delay(3 * 1000);
            cout << "from the tree’s limbs, remnants of ceremonies that celebrated the lives of the illustrious dead,\n";
            delay(3 * 1000);
            cout << "casting fleeting shadows that dance across the stones and crypt alike.\n\n";
        }
        else if (GetName() == "Hall of Ancestors") {
            cout << "The interior of the Hall of Ancestors exudes an air of faded grandeur, where time seems to stand still\n";
            delay(3 * 1000);
            cout << "amidst the encroaching shadows. Tall stone columns, once polished and adorned with intricate\n";
            delay(3 * 1000);
            cout << "carvings, now bear the scars of neglect, their surfaces rough and chipped. Dim light filters through\n";
            delay(3 * 1000);
            cout << "narrow, arched windows, casting an ethereal glow that dances across the cold stone floor,\n";
            delay(3 * 1000);
            cout << "illuminating the dust motes that hang suspended in the air. The walls are lined with ornate niches,\n";
            delay(3 * 1000);
            cout << "each housing a stone sarcophagus that tells the story of those interred within—wealthy merchants,\n";
            delay(3 * 1000);
            cout << "valiant heroes, and wise leaders—each engraved with symbols of their deeds and legacies. Cobwebs\n\n";
            delay(3 * 1000);
            cout << "drape like tattered banners over these resting places, whispering of the memories that linger in this\n";
            delay(3 * 1000);
            cout << "hallowed space.\n\n";
            delay(3 * 1000);
            cout << "At the far end of the hall, a grand altar stands, its once-impressive marble surface now dulled by age\n";
            delay(3 * 1000);
            cout << "and wear. The altar, dedicated to the ancestors, is littered with remnants of offerings: dried flowers,\n";
            delay(3 * 1000);
            cout << "faded tokens of respect, and candles long burnt down to mere stubs. A sense of reverence hangs in\n";
            delay(3 * 1000);
            cout << "the air, mingled with a poignant sadness for the grandeur that once was. The atmosphere is thick\n";
            delay(3 * 1000);
            cout << "with the echoes of whispered prayers and quiet reflections, inviting those who enter to contemplate\n";
            delay(3 * 1000);
            cout << "their own legacies. Here, in the Hall of Ancestors, the past intertwines with the present, reminding all\n";
            delay(3 * 1000);
            cout << "who tread its sacred ground of the importance of honor, memory, and the enduring bonds that tie\n";
            delay(3 * 1000);
            cout << "generations together.\n";
        }
        else if (GetName() == "East road") {
            cout << "The road leading out of town twists and bends like a lazy river, its uneven cobblestones giving way\n";
            delay(3 * 1000);
            cout << "to patches of grass that peek through the cracks. Wildflowers bloom haphazardly along the edges,\n";
            delay(3 * 1000);
            cout << "their vibrant colors a stark contrast to the drab surroundings. As the path meanders toward the\n";
            delay(3 * 1000);
            cout << "rundown neighborhood, the laughter of children echoes like a joyful melody, their playful shouts\n";
            delay(3 * 1000);
            cout << "mingling with the rustling leaves overhead. They race along the road, kicking up dust and weaving\n";
            delay(3 * 1000);
            cout << "through the tall grass, their carefree spirits a reminder of the innocence that flourishes even in less-\n";
            delay(3 * 1000);
            cout << "than-ideal circumstances.\n\n";
        }
        else if (GetName() == "Docks Outskirts") {
            cout << "The atmosphere shifts as the road leads deeper into the neighborhood. Parents linger on\n";
            delay(3 * 1000);
            cout << "porches, their expressions sour and grumpy as they cast wary glances at passersby. Their furrowed\n";
            delay(3 * 1000);
            cout << "brows and crossed arms paint a picture of discontent, a stark contrast to the joy emanating from the\n";
            delay(3 * 1000);
            cout << "children. Dilapidated houses line the street, their paint peeling and windows cracked, but the\n";
            delay(3 * 1000);
            cout << "resilience of life persists. In this juxtaposition, the road serves as a boundary between the carefree\n";
            delay(3 * 1000);
            cout << "laughter of youth and the weary burdens of adulthood, a winding path that reflects the complexities\n";
            delay(3 * 1000);
            cout << "of life in a community striving to endure amid its struggles.\n\n";
        }
        else if (GetName() == "Caspiran Docks") {
            cout << "From the heart of the rundown neighborhood, a marvelous stone gatehouse rises majestically, its\n";
            delay(3 * 1000);
            cout << "formidable walls encircling the Official Caspiran Docks like a guardian of prosperity. The entrance,\n";
            delay(3 * 1000);
            cout << "adorned with intricate carvings of maritime symbols, stands as a striking contrast to the surrounding\n";
            delay(3 * 1000);
            cout << "dilapidation, beckoning travelers and townsfolk alike to experience the allure within. As one passes\n";
            delay(3 * 1000);
            cout << "through the arched gates, the atmosphere shifts dramatically, revealing a bustling hub of activity\n";
            delay(3 * 1000);
            cout << "that breathes life into the port city.\n\n";
            delay(3 * 1000);
            cout << "Inside the walls, the docks present an epitome of wealth and extravagance, with wide stone wharfs\n";
            delay(3 * 1000);
            cout << "stretching out toward the shimmering waters. Several opulent ships are anchored in the harbor, their\n";
            delay(3 * 1000);
            cout << "sails furled and decks alive with crew members unloading cargo of all kinds. The air is filled with the\n";
            delay(3 * 1000);
            cout << "sounds of shouts and laughter, mingling with the creaking of wood and the sloshing of waves\n";
            delay(3 * 1000);
            cout << "against the hulls. Merchants barter energetically, their voices rising above the din as they display\n";
            delay(3 * 1000);
            cout << "their wares—exotic spices, silks, and shimmering trinkets, all promising tales of distant lands and\n";
            delay(3 * 1000);
            cout << "adventures untold.\n\n";
            delay(3 * 1000);
            cout << "As the sun bathes the docks in golden light, the delightful aroma of freshly cooked food wafts\n";
            delay(3 * 1000);
            cout << "through the air, mingling with the rich scent of ale poured from tankards at nearby taverns. The\n";
            delay(3 * 1000);
            cout << "laughter of patrons spills into the streets, creating a vibrant backdrop to the industriousness of the\n";
            delay(3 * 1000);
            cout << "docks. Here, amidst the contrast of wealth and the bustling life of the port, one can feel the pulse of\n";
            delay(3 * 1000);
            cout << "the city—a place where dreams of adventure and fortune intertwine, drawing in both the weary and\n";
            delay(3 * 1000);
            cout << "the hopeful to partake in its splendor.\n\n";
            }
        else if (GetName() == "North Road") {
            cout << "Leaving the town center, the north road slices through what was once a lush and vibrant forest, now\n";
            delay(3 * 1000);
            cout << "marred by the recent sounds of axes and saws. Tall trees that once danced in the breeze have been\n";
            delay(3 * 1000);
            cout << "felled, their trunks stacked along the roadside like silent sentinels awaiting their fate. Horses, sturdy\n";
            delay(3 * 1000);
            cout << "and hardworking, pull heavy carts laden with logs, their hooves thudding rhythmically against the\n";
            delay(3 * 1000);
            cout << "earth as they trek away from the town. The scent of fresh timber fills the air, mingling with the earthy\n";
            delay(3 * 1000);
            cout << "aroma of disturbed soil, a testament to the forest's transformation into raw materials for the\n";
            delay(3 * 1000);
            cout << "burgeoning industry.\n\n";
            delay(3 * 1000);
            cout << "As the road winds further, it opens up to reveal the bustling lumberyard, a hive of activity where\n";
            delay(3 * 1000);
            cout << "laborers work diligently amidst towering stacks of timber. The yard is alive with the sounds of saws\n";
            delay(3 * 1000);
            cout << "cutting through wood, the chatter of workers coordinating their efforts, and the occasional shout of\n";
            delay(3 * 1000);
            cout << "a foreman overseeing the operations. Large planks destined for shipbuilding and sturdy masts are\n";
            delay(3 * 1000);
            cout << "neatly arranged, ready to be transported to the docks. The vibrant energy of the lumberyard is\n";
            delay(3 * 1000);
            cout << "palpable, a thriving testament to the importance of Caspira's forests and the vital role they play in\n";
            delay(3 * 1000);
            cout << "the town’s economy and maritime endeavors.\n";
		}
		else if (GetName() == "Heartwood Grove") {
			cout << "The Heartwood Grove is a place of serene beauty, where the ancient trees stand as silent sentinels\n";
			delay(3 * 1000);
			cout << "over the vibrant undergrowth. The air is thick with the scent of moss and wildflowers, and the\n";
			delay(3 * 1000);
			cout << "sounds of birdsong and rustling leaves create a symphony of nature that soothes the soul. Sunlight\n";
			delay(3 * 1000);
			cout << "filters through the canopy, casting dappled shadows on the forest floor, where delicate ferns and\n";
			delay(3 * 1000);
			cout << "mushrooms thrive in the cool, damp earth.\n\n";
			delay(3 * 1000);
			cout << "As you wander deeper into the grove, the trees seem to whisper secrets to one another, their leaves\n";
			delay(3 * 1000);
			cout << "rustling in the gentle breeze. The ancient oaks and towering pines create a cathedral-like canopy\n";
			delay(3 * 1000);
			cout << "above, their branches intertwined in a dance of life and growth. The forest floor is a tapestry of\n";
			delay(3 * 1000);
			cout << "color and texture, where delicate flowers bloom and small creatures scurry among the roots. Here,\n";
			delay(3 * 1000);
			cout << "amidst the tranquility of the Heartwood Grove, one can feel the pulse of the land, a reminder of the\n";
			delay(3 * 1000);
			cout << "interconnectedness of all living things and the enduring beauty of the natural world.\n\n";
			}
        else if (GetName() == "Lumberyard") {
			cout << "The lumberyard is a place of industry and activity, where the sounds of axes and saws echo through\n";
			delay(3 * 1000);
			cout << "the air. Stacks of timber line the rugged path, their fresh scent mingling with the earthy aroma of\n";
			delay(3 * 1000);
			cout << "sawdust. Workers move with purpose among the trees, their muscles flexing as they fell the mighty\n";
			delay(3 * 1000);
			cout << "oaks and pines that have stood for centuries. The air is filled with the sounds of labor and the\n";
			delay(3 * 1000);
			cout << "crackling of fires, as the lumberyard hums with the energy of progress and growth.\n\n";
			delay(3 * 1000);
			cout << "As you make your way through the lumberyard, the towering stacks of timber create a maze of\n";
			delay(3 * 1000);
			cout << "shadows and light, where the sun filters through the canopy above, casting a golden glow on the\n";
			delay(3 * 1000);
			cout << "work of the lumberjacks. The trees, once proud and tall, now lie in pieces, their trunks stripped of\n";
			delay(3 * 1000);
			cout << "bark and branches, ready to be transformed into the structures that will shape the town. The\n";
			delay(3 * 1000);
			cout << "lumberyard is a place of transformation and creation, where the raw materials of the forest are\n";
			delay(3 * 1000);
			cout << "hewn into the tools of civilization, a testament to the ingenuity and industry of those who toil in its\n";
			delay(3 * 1000);
			cout << "midst.\n\n";
        }



    }

    ListExits(); // Show exits
}

    

//void delay(int milliseconds) {
//    if (!skipDelays) {
//        clock_t goal = milliseconds + clock();
//        while (goal > clock());
//
//    }
//}

bool Room::IsFirstVisit() {
    if (mFirstVisit) {
        mFirstVisit = false; // Set to false after first visit
        return true; // Indicate this is the first visit
    }
    return false; // Indicate this is not the first visit
}

void Room::HandleAttack(Character& player, Inventory& inventory) {
    cout << "An enemy appears!\n";
    Enemy enemies[] = {
        Enemy("Goblin", 2, 10, 3, 25),
        Enemy("Orc", 4, 15, 6, 50),
        Enemy("Troll", 3, 20, 25, 100),
        Enemy("Skeleton", 1, 5, 1, 50),
        Enemy("Werewolf", 4, 40, 100, 250)
    };

    // Generate a random index between 0 and 4 (inclusive)
    int randomIndex = rand() % 5;

    // Select a random enemy
    auto inv = inventory.getInv();
    Enemy selectedEnemy = enemies[randomIndex];
	cout << "You have encountered a " << selectedEnemy.getName() << "!" << "\n";
    Combat combat(player, selectedEnemy, inv);
    combat.start();
    if (!player.isAlive()) {
        cout << "Game over, man! Game over!\n\n";
        exit(0); // Exit the game if the player is dead
    }
    else {
        cout << "You have defeated the " << selectedEnemy.getName() << "!\n";
        cout << "You have gained " << selectedEnemy.getExp() << " experience points!\n";
        player.addExp(selectedEnemy.getExp());
        cout << "You now have " << player.getExp() << " experience points!\n";
        cout << "You have gained " << selectedEnemy.getGold() << " gold!\n";
        player.addGold(selectedEnemy.getGold());
        cout << "You now have " << player.getGold() << " gold!\n";
    }
}

void Room::HandlePlayerAction(Room* room, Character& player, Inventory& inventory) {
    // Store the current room for reference
    // Check for specific room interactions first


    if (GetName() == "General Store") {
        inventory.runGeneralStore(player);
        return; // Exit this method after handling store logic
    }

    if (GetName() == "Blacksmith") {
        inventory.runBlacksmith(player);
        return; // Exit this method after handling store logic
    }

    // Check for attack chance immediately upon entering the room
    if (static_cast<float>(rand()) / RAND_MAX < mAttackChance) {
        cout << "You have been attacked!\n";
        HandleAttack(player, inventory); // Call combat here
    }

    DisplayRoom(player, inventory); // Show the room description 

    // Prompt the player for their action
    while (true) {
        cout << "\nWhat would you like to do?\n";
        cout << "[1] Open Inventory\n";
        cout << "[2] Move to another room\n";
        cout << "[3] Check room description\n";
        cout << "[4] Investigate your Surroundings\n";
        cout << "[0] Quit Game!\n";
        int choice;
        cin >> choice;

        switch (choice) {
        case 1: // Open inventory
            inventory.openInventory(player); // Call the inventory function
            break;
        case 2: {
            Room* nextRoom = ChooseExit(); // Get the next room from ChooseExit
            if (nextRoom) { // If the next room is valid
                nextRoom->HandlePlayerAction(room, player, inventory); // Pass inventory to the next room
            }
            break;
        }
        case 3:
            DisplayRoom(player, inventory); // Show room description
            break;
        case 4:
            // Implement the logic for investigating surroundings
            cout << "You look around carefully...\n";
            // Add any findings or interactions here
            break;
        case 0: // Exit the Game
            exit(0);
            return;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    }
}
    



Room* Room::ChooseExit() {
    ListExits(); // List the exits for the current room

    int choice = 0;
    cout << "Choose an exit (enter the number): ";
    cin >> choice;

    // Validate input
    if (choice < 1 || choice > GetNumberOfExits()) {
        cout << "Invalid choice. Please try again.\n";
        return nullptr; // Return null if invalid choice
    }

    return mExits[choice - 1]; // Return the chosen room
}

Room* Room::createTown() {
    Room* tavern = new Room("Tavern", "A lively tavern filled with sounds of laughter and music.", true, 0.0f);
    Room* townCenter = new Room("Town Center", "The bustling center of town, with shops and stalls.", true, 0.00f);
    Room* generalStore = new Room("General Store", "A shop filled with various supplies and goods.", true, 0.0f); // No attack chance
    Room* blacksmith = new Room("Blacksmith", "The forge is hot, and the blacksmith is hard at work.", true, 0.0f);
    Room* docks = new Room("Caspiran Docks", "A bustling waterfront where ships come and go, carrying the rich scents of salt and adventure. \nYou are surrounded by the sounds of seagulls and the chatter of merchants.", true, 0.0f);
    Room* heartwood = new Room("Heartwood Grove", "A serene, enchanted forest filled with ancient trees whose vibrant leaves whisper secrets, \ninviting wanderers to explore its hidden paths.", true, 0.0f);
    Room* crypt = new Room("Hall of Ancestors", "Once a majestic structure, the Hall of Ancestors now stands in decay. \nThe crumbling stone walls and overgrown vines, its faded carvings barely visible. \nIt quietly bears witness to the forgotten memories of those it once honored.", true, 0.5f);

    // Create roads
    Room* roadEast = new Room("East Road", "A dusty road leading east out of town.", true, 0.25f);
    Room* roadWest = new Room("West Road", "A quiet road leading west towards the forest.", true, 0.25f);
    Room* roadNorth = new Room("North Road", "A path leading north towards the mountains.", true, 0.25f);
    Room* roadEast2 = new Room("Docks Outskirts", "A bustling area where the docks meet the land, filled with the sounds of waves and the cries of seagulls.", true, 0.25f);
    Room* roadWest2 = new Room("Graveyard", "A solemn place shrouded in mist, with weathered tombstones and the faint sound of rustling leaves.", true, 0.25f);
    Room* roadNorth2 = new Room("Lumberyard", "A rugged path lined with stacks of timber, echoing with the sounds of axes and saws as workers tend to their trade.", true, 0.25f);

    // Set connections
    tavern->AddExit(townCenter);
    townCenter->AddExit(tavern);

    townCenter->AddExit(generalStore);
    generalStore->AddExit(townCenter);

    townCenter->AddExit(blacksmith);
    blacksmith->AddExit(townCenter);

    townCenter->AddExit(roadEast);
    roadEast->AddExit(townCenter);

    townCenter->AddExit(roadWest);
    roadWest->AddExit(townCenter);

    townCenter->AddExit(roadNorth);
    roadNorth->AddExit(townCenter);

    roadNorth2->AddExit(roadNorth);
    roadNorth->AddExit(roadNorth2);

    roadEast2->AddExit(roadEast);
    roadEast->AddExit(roadEast2);

    roadWest2->AddExit(roadWest);
    roadWest->AddExit(roadWest2);

    roadNorth2->AddExit(heartwood);
    heartwood->AddExit(roadNorth2);

    roadWest2->AddExit(crypt);
    crypt->AddExit(roadWest2);

    roadEast2->AddExit(docks);
    docks->AddExit(roadEast2);


    return tavern; // Start in the tavern
}

void Room::handleRoomEvents(Room* currentRoom, Character& player, Inventory inventory) {
    if (currentRoom->IsFirstVisit()) { // Check if it's the first visit
        if (currentRoom->GetName() == "Tavern") {
            cout << "You wake up in your cozy bed at the tavern, the smell of breakfast wafting through the air.\n";
            delay(3 * 1000);
            cout << "You can hear the chatter of patrons and the clinking of mugs, but your head is pounding.\n";
            delay(3 * 1000);
            cout << "As you sit up, a wave of nausea hits you, and you remember last night's revelry.\n";
            delay(3 * 1000);
            cout << "You feel dehydrated and your mouth is dry, you crave water.\n";
            delay(3 * 1000);
            cout << "A faint light coming through the window only intensifies your headache.\n";
            delay(3 * 1000);
            cout << "You get up slowly and gather your things.\n";
            delay(1 * 1000);
            inventory.displayPlayerInventory();
            delay(5 * 1000);
            cout << "You meander your way out of the room and down the stairs to the tavern.\n\n";
            delay(2 * 1000);
            cout << "'Rough night eh? Well, I would have a hangover too if I drank " << std::rand() % 50 + 1 << " bottles of rum as well.'\n\n";
            delay(2 * 1000);
        }
        else if (currentRoom->GetName() == "Town Center") {
            char tutorial;
            cout << "Hang on! before you leave! You may need a bit of information.\nDo you know how to fight in these lands? (y/n): ";
            cin >> tutorial;
            if (tutorial == 'n' || tutorial == 'N') {
                cout << "Well then! Hi there, my name is Ryder. \nI will be the friendly voice in your head that helps you out!\n";
                delay(3 * 1000);
                cout << "Don't look around like that, people are going to think you're weird\ndon't bother trying to talk either, you will just look like you are talking to yourself.\n";
                delay(3 * 1000);
                cout << "Let me teach you some things about how combat works in the world of caspira.\n";
                delay(3 * 1000);

                cout << "\nChoose an action:\n";
                cout << "[1] Attack\n";
                cout << "[2] Defend\n";
                cout << "[3] Use Item\n";
                cout << "[4] Run\n\n";
                delay(3 * 1000);

                cout << "This is what you will see when you enter combat, \nYou don't need to choose anything right now i am just giving you an example!\n";
                delay(3 * 1000);
                cout << "Now, [1] Attack, should be self explanatory, \nyou will attack with whatever weapon you have equipped currently.\n";
                delay(3 * 1000);
                cout << "Next, [2] Defend, you will raise your weapon or shield into a defensive position, \nyou will reduce any incoming damage to '1 damage' for that round.\n";
                delay(3 * 1000);
                cout << "Next, [3] Use Item, this will open your inventory and let you choose from a list of useable items, such as potions, \nyou then give up your turn to use that item.\n";
                delay(3 * 1000);
                cout << "Finally, [4] Run, you will try to run away from the fight. \nit is only a percentage chance you will run away and if you fail the enemy will get a free attack on you.\n";
                delay(3 * 1000);
                cout << "Now that we have gone over the basics of the system, let's get you some hands on experience!\n\n";
                delay(2 * 1000);
                cout << "A Random Goblin appears in front of you! \nIt looks angry and hungry.\n";
                delay(4 * 1000);
            }

            else {
                cout << "\nWatch out!\n";
                cout << "Ambush!\nYou were ambushed the moment you exited the town!\n";
            }
            Enemy enemy("Goblin", 2, 10);
            auto inv = inventory.getInv();
            Combat combat(player, enemy, inv);
            combat.start();
            if (player.isAlive() == false) {
                cout << "Game over man! Game over!\n\n";
                exit(0);
            }
            else {
                cout << "Congratulation on your first victory!";
            }
            return;
        }
    }
    // Add more room-specific logic as needed
}