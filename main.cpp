//Shanti Gharib
//Lab 5

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <limits>



enum class CreatureFields {
    
    NAME = 1,
    TYPE,
    HEALTH,
    STRENGTH,
    
    
    SIZE

};

enum class CreatureTypes { 

    MACARA,
    CEFFYL,
    NUGGLE,
    BAHAMUT


};


static const std::string NAME_DEFAULT{"n/a"};

class Creature {

private:

    
    static constexpr const int HEALTH_DEFAULT{100}, STRENGTH_DEFAULT{100};
    
    int maxHealth{HEALTH_DEFAULT}, strength{STRENGTH_DEFAULT}, 
        remainingHealth{HEALTH_DEFAULT}, secretID{0};

    std::string name{NAME_DEFAULT}, type{TYPE_DEFAULT};

    bool ValidateType(const std::string &creatureType);

    void CopyFunction(const Creature &source);


public:
    
    Creature();
    
    Creature(const Creature &source);
    void operator=(const Creature &source);
    
    Creature(const std::string &creatureName, const std::string &creatureType);
    Creature(const std::string &creatureName, const std::string &creatureType, int creatureHealth, int creatureStrength);
    
    ~Creature();


    inline int GetMaxHealth() const;
    inline int GetCurrentHealth() const;
    inline int GetStrength() const;
    inline const std::string& GetType() const;
    inline const std::string& GetName() const;
    bool ReceiveDamage(int damage);
    void HealCreature();
    int GetDamage() const;
    
    static std::string PrintHeading();
    std::string ToString() const;

    void SetCreature(const std::string &creatureName, const std::string &creatureType, int health, int strength);

    static constexpr const int TYPES_TOTAL{4}, DEFAULT_NAMES_TOTAL{16};
    static const std::string VALID_CREATURE_TYPES[TYPES_TOTAL];
    static const std::string TYPE_DEFAULT;
    static const std::string DEFAULT_CREATURE_NAMES[DEFAULT_NAMES_TOTAL];

};



class Army {
    
public:

    static constexpr const int MAX_SIZE_DEFAULT{8};

private:

    
    Creature creatures[MAX_SIZE_DEFAULT];
    Creature *pSorted[MAX_SIZE_DEFAULT]{nullptr};

    int usedSize{0}, maxSize{MAX_SIZE_DEFAULT};
    std::string name{NAME_DEFAULT};
    
    
    void SortByField(const int field);

    std::string SearchByNameTypeHelper(std::string &searchQuery) const;

    void AssignSortPointers();

    void CopyFunction(const Army &source);

public:

    
    Army();
    Army(const Army &source);
    void operator=(const Army &source);
    
    ~Army();


    inline int GetCurrentSize() const;
    inline int GetCapacity() const;
    inline const std::string &GetName() const;
    inline const Creature& GetElement(const int index) const;
    inline const Creature* GetPointerToElement(const int index) const;
    
    void AddElement(const Creature &creature);

    void OverwriteElement(const Creature &creature, const int index);

    bool ReceiveDamage(int damage, int index);

    void HealCreature(int index);

    void SetArmy(const std::string &armyName, const int size);

    void PrintArmySortedOrUnsorted(int field = -1);
    
    void PrintNameTypeSearchQueryResults() const;

    std::string ToString() const;


};



class Game {

private:
    
    Army teamA, teamB;


    void CustomizeArmy();

    static std::string ActionHeading();

    void CopyFunction(const Game &source);
    

public:

    Game();
    Game(const Game &source);
    
    void operator=(const Game &source);
    ~Game();

    void GameManager();
    std::string ActionToString(const std::string &attacker, int damage, const std::string &attackerArmyName, const std::string &defender, int remainingHealth, const std::string &defenderArmyName) const;
};



std::string PrintSeparationLine(int width);
void NormalizeString(std::string &str);

void DisplayMainMenu();
void DisplaySortSubMenu();
void SortCreaturesMenu(Army &creatures);
void HandleDefaultMenuCase();




static constexpr const int HEADING_WIDTH{82};

const std::string Creature::TYPE_DEFAULT{"VOID"};
const std::string Creature::VALID_CREATURE_TYPES[Creature::TYPES_TOTAL]{"MACARA", "CEFFYL", "NUGGLE", "BAHAMUT"};

const std::string Creature::DEFAULT_CREATURE_NAMES[Creature::DEFAULT_NAMES_TOTAL]{"Grimshade", "Hexmaw", "Voidfang", "Blightwing", "Duskfiend", "Ironwraith", "Pyrestalker", "Frostbane", 
"Nightbane", "Vilethorn", "Duskrend", "Soulrazor", "Frostclaw", "Emberfang", "Wraithkin", "Doomshade"};



int main() {

    
    srand(0);
    
    enum { PLAY = 1, QUIT };

    int option{0};

    while (option != QUIT) {
    
        
        DisplayMainMenu();
        
        std::cin >> option;

        switch (option) {
        
            case PLAY: {
                
                Game currGame;
                currGame.GameManager();

                break;
            
            }

            case QUIT: {
            
                std::cout << "\nProgram now closed\n\n";

                break;
            
            }

            default: {
            
                HandleDefaultMenuCase();

                break;
            
            }


        }
    
    
    }


}









Game::Game() {}


Game::Game(const Game &source) {

    CopyFunction(source);

}


void Game::operator=(const Game &source) {

    CopyFunction(source);

}


Game::~Game() {}


void Game::CopyFunction(const Game &source) {

    teamA = source.teamA;
    teamB = source.teamB;

}


std::string Game::ActionHeading() {

    std::ostringstream result;

    static constexpr const int WIDTH{122};

    result << "| " << std::left 
        << std::setw(20) << "Attacker" << " | " 
        << std::setw(10) << "Damage"   << " | " 
        << std::setw(20) << "Army"     << " |\t"
        << std::setw(20) << "Defender" << " | "
        << std::setw(10) << "Health"   << " | " 
        << std::setw(20) << "Army"     << " |\n" << std::right 
        << PrintSeparationLine(WIDTH);

    return result.str();

}


std::string Game::ActionToString(const std::string &attacker, int damage, const std::string &attackerArmyName, const std::string &defender, int remainingHealth, const std::string &defenderArmyName) const {

    std::ostringstream result;

    result << "| " << std::left  
        << std::setw(20) << attacker          << " | " << std::right 
        << std::setw(10) << damage            << " | " << std::left
        << std::setw(20) << attackerArmyName  << " |\t"  
        << std::setw(20) << defender          << " | " << std::right 
        << std::setw(10) << remainingHealth   << " | " << std::left
        << std::setw(20) << defenderArmyName  << " |"  << std::right;

    return result.str();

}


void Game::GameManager() {

    CustomizeArmy();
    
    //positive: team A wins; neagtive: team B wins
    int netHealth{0};

    std::cout << "\n\n" 
        << teamA.ToString() << "\n\n" 
        << teamB.ToString() << "\n\n" 
        << ActionHeading();

    for (int i = -1 + teamA.GetCurrentSize(); i >= 0; --i) {
    
        const Creature &creatureA = teamA.GetElement(i), &creatureB = teamB.GetElement(i);

        teamA.HealCreature(i); teamB.HealCreature(i);

        bool teamATurn = (rand() % 2 == 0);


        while (creatureA.GetCurrentHealth() > 0 && creatureB.GetCurrentHealth() > 0) {
        
            if (teamATurn) {

                const int DAMAGE = creatureA.GetDamage();

                teamB.ReceiveDamage(DAMAGE, i);

                std::cout 
                    << ActionToString(creatureA.GetName(), DAMAGE, teamA.GetName(), creatureB.GetName(), creatureB.GetCurrentHealth(), teamB.GetName()) 
                    << "\n";

                teamATurn = false;
            
            }
            
            else {
                
                const int DAMAGE = creatureB.GetDamage();

                teamA.ReceiveDamage(DAMAGE, i);

                std::cout 
                    << ActionToString(creatureB.GetName(), DAMAGE, teamB.GetName(), creatureA.GetName(), creatureA.GetCurrentHealth(), teamA.GetName()) 
                    << "\n";

                teamATurn = true;
            
            }
        
        }

        netHealth += (creatureA.GetCurrentHealth() - creatureB.GetCurrentHealth());
    
    }

    std::cout << "\n\nWinner: ";
    
    if (netHealth > 0) {
    
        std::cout << teamA.GetName();

    }

    else if (netHealth != 0) {
    
        std::cout << teamB.GetName();
    
    }

    else {
    
        std::cout << "Neither: Somehow it's a tie";
    
    }

    
    std::cout << "\n\n\n" << teamA.ToString() << "\n\n" << teamB.ToString() << "\n\n";

}


void Game::CustomizeArmy() {
    
    enum { YES = 1, NO };
    
    int userChoice{0};
    
    while (userChoice != YES && userChoice != NO) {
    
        std::cout << "\nFor each army, do you wish to modify their names and size\n1. Yes\n2. No\n\n";
        std::cin >> userChoice;
        
        switch (userChoice) {
        
            case YES: {
                
                std::string name1, name2;

                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "\nEnter Army 1 Name: \n\n";
                std::getline(std::cin, name1);

                std::cout << "\nEnter Army 2 Name: \n\n";
                std::getline(std::cin, name2);


                
                int size{0};
                
                while (size <= 0 || size > Army::MAX_SIZE_DEFAULT) {
                
                    std::cout << "\nEnter the size of both armies(Max: " << Army::MAX_SIZE_DEFAULT << "): \n\n";
                    std::cin >> size;
                
                }

                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                teamA.SetArmy(name1, size);
                teamB.SetArmy(name2, size);

                break;
        
            }

            case NO: {
            
                std::cout << "Using default army names and size\n\n";

                teamA.SetArmy("A", Army::MAX_SIZE_DEFAULT);
                teamB.SetArmy("B", Army::MAX_SIZE_DEFAULT);

                break;
            
            
            }

            default: {
            
                HandleDefaultMenuCase();

                break;
            
            
            }
        
        
        }
    
    }

    for (int i = -1 + teamA.GetCapacity(), offset = i + 1; i >= 0; --i) {

        teamA.AddElement(Creature(Creature::DEFAULT_CREATURE_NAMES[i], Creature::VALID_CREATURE_TYPES[rand() % Creature::TYPES_TOTAL]));
        teamB.AddElement(Creature(Creature::DEFAULT_CREATURE_NAMES[i + offset], Creature::VALID_CREATURE_TYPES[rand() % Creature::TYPES_TOTAL]));
    
    }

}
    




    
Army::Army() {

    AssignSortPointers();

}


Army::Army(const Army &source) {

    CopyFunction(source);

}


void Army::operator=(const Army &source) {

    CopyFunction(source);

}


Army::~Army() {
    
    AssignSortPointers();

    name = NAME_DEFAULT;
    maxSize = MAX_SIZE_DEFAULT;
    usedSize = 0;

}


void Army::CopyFunction(const Army &source) {

    AssignSortPointers();
    
    name = source.name;
    maxSize = source.maxSize;

    for (int i = 0; i < maxSize; ++i) {
    
        creatures[i] = source.creatures[i];
    
    }

}


void Army::SetArmy(const std::string &armyName, const int size) {

    if (size >= 0 && size < MAX_SIZE_DEFAULT) maxSize = size;

    name = armyName;

}


inline int Army::GetCurrentSize() const {
    
    
    return usedSize;
    

}


inline int Army::GetCapacity() const {
    
    return maxSize;

}


inline const std::string& Army::GetName() const {

    return name;

}


inline const Creature& Army::GetElement(const int index) const {


    return creatures[index];


}


void Army::AssignSortPointers() {

    for (int i = 0; i < usedSize; ++i) {

        pSorted[i] = &creatures[i];
    
    }

}


inline const Creature* Army::GetPointerToElement(const int index) const {


    return pSorted[index];


}


void Army::AddElement(const Creature &creature) {


    if (usedSize != MAX_SIZE_DEFAULT) {
    
        creatures[usedSize] = creature;

        ++usedSize;
    
    }

    else {
    
        std::cout << "Current Army at max capacity\n\n";

    }


}


void Army::OverwriteElement(const Creature &newCreature, const int index) {

    if (index >= 0 && index < maxSize) {
    
        creatures[index] = newCreature;
    
    }

    else {
    
        std::cout << "Out of Bounds memory access not permitted\n\n";

    }

}


void Army::SortByField(const int field) {

    
    bool sortStatus{false};


    while (!sortStatus) {
    
        sortStatus = true;

        for (int i = 1; i < usedSize; ++i) {
            
            bool isInversion{false};

            Creature *pPrev = pSorted[i - 1], *pCurr = pSorted[i];

            
            switch (field) {

                case static_cast<int>(CreatureFields::NAME): {
            
                
                    isInversion = pPrev->GetName() < pCurr->GetName();

                    break;
            
                }
            
                case static_cast<int>(CreatureFields::TYPE): {
            
                
                    isInversion = pPrev->GetType() < pCurr->GetType();

                    break;
            
                }
            
                case static_cast<int>(CreatureFields::HEALTH): {
            
                
                    isInversion = pPrev->GetMaxHealth() < pCurr->GetMaxHealth();

                    break;
            
            
                }
            
                case static_cast<int>(CreatureFields::STRENGTH): {
            
                
                    isInversion = pPrev->GetStrength() < pCurr->GetStrength();

                    break;
                        
                }
            
            }
        
            if (isInversion) {
                          
                
                sortStatus = false;

                Creature *pTemp{pSorted[i]};

                pSorted[i] = pSorted[i - 1];
                
                pSorted[i - 1] = pTemp;
                          
                        
            }
        
        }

    }

}


void Army::HealCreature(int index) {

    creatures[index].HealCreature();

}


bool Army::ReceiveDamage(int damage, int index) {

    return creatures[index].ReceiveDamage(damage);

}


void Army::PrintNameTypeSearchQueryResults() const {

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::cout << "\nEnter search query:\n\n";
    
    std::string searchQuery;
    std::getline(std::cin, searchQuery);

    NormalizeString(searchQuery);

    std::string result{SearchByNameTypeHelper(searchQuery)};

    
    if (result.empty()) {
    
        std::cout << "No matching records found";
    
    }

    else {
    
        std::cout << "\nEntries Found:\n\n" << Creature::PrintHeading() << "\n" 
                  << PrintSeparationLine(HEADING_WIDTH) << "\n"
                  << result;
    
    }

    std::cout << "\n\n";


}


std::string Army::ToString() const {

    std::ostringstream result;

    static constexpr const int WIDTH{82};

    result << "Army " << name << ":" 
           << Creature::PrintHeading() << "\n" 
           << PrintSeparationLine(WIDTH);

    for (int i = 0; i < usedSize; ++i) {
    
        result << creatures[i].ToString() << "\n";

    
    }

    return result.str();


}


std::string Army::SearchByNameTypeHelper(std::string &searchQuery) const {


    std::ostringstream result;

    
    for (int i = 0; i < usedSize; ++i) {
        
        std::string name{creatures[i].GetName()}, type{creatures[i].GetType()};
        
        if (name.find(searchQuery) != std::string::npos || type.find(searchQuery) != std::string::npos) {
        
            result << creatures[i].ToString() << "\n";

        }
    
    }


    return result.str();


}


void Army::PrintArmySortedOrUnsorted(int field) {

    std::ostringstream result;

    if (field > 0 && field < static_cast<int>(CreatureFields::SIZE)) {
    
        SortByField(field);

        for (int i = 0; i < usedSize; ++i) result << pSorted[i]->ToString() << "\n";

    }

    else {
    
        for (int i = 0; i < usedSize; ++i) result << creatures[i].ToString() << "\n";
    
    }

    
    if (result.str().empty()) {
                
        std::cout << "Creatures empty";
                
    }
                
    else {
                
        std::cout << Creature::PrintHeading() << "\n" 
            << PrintSeparationLine(HEADING_WIDTH) << result.str() << "\n" 
            << PrintSeparationLine(HEADING_WIDTH);
                
    }

    std::cout << "\n\n";

}






Creature::Creature() {}


Creature::Creature(const std::string &creatureName, const std::string &creatureType) {

    static constexpr const int RANGE{51}, MIN_VAL{50};
    
    SetCreature(creatureName, creatureType, MIN_VAL + (rand() % RANGE), MIN_VAL + (rand() % RANGE));

}


Creature::Creature(const std::string &creatureName, const std::string &creatureType, int creatureStrength, int creatureHealth) {
   
    SetCreature(creatureName, creatureType, creatureStrength, creatureHealth);

}


Creature::Creature(const Creature &source) {

    CopyFunction(source);

}


void Creature::operator=(const Creature &source) {

    CopyFunction(source);


}


Creature::~Creature() {
    
    
    SetCreature(NAME_DEFAULT, TYPE_DEFAULT, STRENGTH_DEFAULT, HEALTH_DEFAULT);

}


void Creature::CopyFunction(const Creature &source) {

    SetCreature(source.GetName(), source.GetType(), source.GetMaxHealth(), source.GetStrength());

}


bool Creature::ValidateType(const std::string &creatureType) {
    

    bool foundMatch{creatureType == TYPE_DEFAULT};

    for (int i = 0; !foundMatch && i < TYPES_TOTAL; ++i) {
    
        if (creatureType == VALID_CREATURE_TYPES[i]) {
        
            foundMatch = true;
            secretID = i;
        
        }
    
    }

    
    if (!foundMatch) {
    
        std::cout << "Type does not match any of the " << TYPES_TOTAL << " valid base types. Type now set to default\n\n";
    
    }

    return foundMatch;

}


inline int Creature::GetMaxHealth() const {
    
    return maxHealth;

}


inline int Creature::GetCurrentHealth() const {
    
    return remainingHealth;

}


inline int Creature::GetStrength() const {

    return strength;

}


inline const std::string& Creature::GetType() const {

    return type;

}


inline const std::string& Creature::GetName() const {

    return name;

}


int Creature::GetDamage() const {

    int damage = (rand() % strength) + 1;

    
    switch (secretID) {
    
        case static_cast<int>(CreatureTypes::CEFFYL): {
            
            if (rand() % 100 < 15) {
            
                damage += 25;
            
            }
            
            break;
        
        }

        case static_cast<int>(CreatureTypes::BAHAMUT): {
        
            damage += (rand() % strength) + 1;
            
            break;
        
        }

        case static_cast<int>(CreatureTypes::NUGGLE): {
        
            if (rand() % 100 < 15) {
            
                damage *= 2;    

            }

            break;
        
        }
    
    }

    return damage;

}


void Creature::HealCreature() {

    remainingHealth = maxHealth;

}


bool Creature::ReceiveDamage(int damage) {

    remainingHealth = std::max(0, remainingHealth - damage);

    return remainingHealth > 0;
    

}


void Creature::SetCreature(const std::string &creatureName, const std::string &creatureType, int creatureHealth, int creatureStrength) {

    name = creatureName;
    type = ValidateType(creatureType) ? creatureType : Creature::TYPE_DEFAULT;
    maxHealth = remainingHealth = creatureHealth;
    strength = creatureStrength;

}


std::string Creature::ToString() const {
    

    std::ostringstream result;
    
    
    result << "| " << std::left
        << std::setw(15) << name      << " | "
        << std::setw(15) << type      << " | " << std::right
        << std::setw(10) << maxHealth << " | "
        << std::setw(15) << remainingHealth << " | "
        << std::setw(10) << strength  << " | ";
    

    return result.str();


}






void HandleDefaultMenuCase() {


    std::cout << "\nInvalid option selected\n";
    
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


}


std::string Creature::PrintHeading() {
    
    std::ostringstream result;
    

    result << "\n\n| " << std::left
        << std::setw(15)  << "Name"     << " | "
        << std::setw(15)  << "Type"     << " | "
        << std::setw(10)  << "Max Health" << " | "
        << std::setw(15)  << "Current Health" << " | "
        << std::setw(10)  << "Strength" << " | " << std::right;

    
    return result.str();


}


std::string PrintSeparationLine(int width) {

    std::ostringstream result;

    result << std::setfill('-') << std::setw(width) << "" << std::setfill(' ') << "\n";

    return result.str();

}


void SortCreaturesMenu(Army &creatures) {
    
    static constexpr const int ESCAPE_OPTION{5};
    
    int option{0};

    while (option != ESCAPE_OPTION) {
    
        DisplaySortSubMenu();

        std::cin >> option;

        switch (option) {
            
            case static_cast<int>(CreatureFields::NAME):
            
            case static_cast<int>(CreatureFields::TYPE):
            
            case static_cast<int>(CreatureFields::HEALTH):
            
            case static_cast<int>(CreatureFields::STRENGTH): {
            
                
                creatures.PrintArmySortedOrUnsorted(option);

                break;
                        
            }

            case ESCAPE_OPTION: {
            
                std::cout << "Leaving sub-menu\n\n";

                break;
            
            }

            default: {
            
                HandleDefaultMenuCase();
            
            }
        
        }
    
    }


}


void NormalizeString(std::string &str) {

    static constexpr const char 
        TINY_A{'a'}, TINY_Z{'z'}, 
        ALPHA_A{'A'}, ALPHA_Z{'Z'},
        UNDERSCORE{'_'}, SPACE{' '};

    for (size_t i = 0; i < str.size(); ++i) {
        
        if (TINY_A <= str[i] && str[i] <= TINY_Z) str[i] += (ALPHA_A - TINY_A);
        
        else if (str[i] == UNDERSCORE) str[i] = SPACE;
    
    }

}


void DisplayMainMenu() {


    std::cout << "\n\nOptions:"
        
        "\n\t1. Load Game"
        
        "\n\t2. Quit\n\n";


}


void DisplaySortSubMenu() {

    std::cout << "\n\nSort Options:"
        
        "\n\t1. Name"
        
        "\n\t2. Type"
        
        "\n\t3. Health"

        "\n\t4. Strength"
        
        "\n\t5. None: Go back to outer menu\n\n";

}




//Testcases

//TestCase1: Using custom names and size
//Output:
// 
//  Options:
//          1. Load Game
//          2. Quit
//  
//  1
//  
//  For each army, do you wish to modify their names and size
//  1. Yes
//  2. No
//  
//  1
//  
//  Enter Army 1 Name:
//  
//  Warriors
//  
//  Enter Army 2 Name:
//  
//  Protectors
//  
//  Enter the size of both armies(Max: 8):
//  
//  6
//  
//  
//  Army Warriors:
//  
//  | Name            | Type            | Max Health | Current Health  | Strength   |
//  ----------------------------------------------------------------------------------
//  | Ironwraith      | NUGGLE          |         72 |              72 |         68 |
//  | Duskfiend       | CEFFYL          |         96 |              96 |         52 |
//  | Blightwing      | NUGGLE          |         85 |              85 |         76 |
//  | Voidfang        | CEFFYL          |         65 |              65 |         93 |
//  | Hexmaw          | CEFFYL          |         65 |              65 |         98 |
//  | Grimshade       | NUGGLE          |         74 |              74 |         79 |
//  
//  
//  Army Protectors:
//  
//  | Name            | Type            | Max Health | Current Health  | Strength   |
//  ----------------------------------------------------------------------------------
//  | Soulrazor       | CEFFYL          |         66 |              66 |         82 |
//  | Duskrend        | MACARA          |        100 |             100 |         89 |
//  | Vilethorn       | CEFFYL          |         70 |              70 |         70 |
//  | Nightbane       | BAHAMUT         |         99 |              99 |         81 |
//  | Frostbane       | MACARA          |         96 |              96 |         85 |
//  | Pyrestalker     | BAHAMUT         |         71 |              71 |         76 |
//  
//  
//  | Attacker             | Damage     | Army                 |    Defender             | Health     | Army                 |
//  --------------------------------------------------------------------------------------------------------------------------
//  | Pyrestalker          |         71 | Protectors           |    Grimshade            |          3 | Warriors             |
//  | Grimshade            |         78 | Warriors             |    Pyrestalker          |          0 | Protectors           |
//  | Hexmaw               |         98 | Warriors             |    Frostbane            |          0 | Protectors           |
//  | Nightbane            |         74 | Protectors           |    Voidfang             |          0 | Warriors             |
//  | Vilethorn            |         19 | Protectors           |    Blightwing           |         66 | Warriors             |
//  | Blightwing           |         60 | Warriors             |    Vilethorn            |         10 | Protectors           |
//  | Vilethorn            |         55 | Protectors           |    Blightwing           |         11 | Warriors             |
//  | Blightwing           |         69 | Warriors             |    Vilethorn            |          0 | Protectors           |
//  | Duskrend             |         57 | Protectors           |    Duskfiend            |         39 | Warriors             |
//  | Duskfiend            |         44 | Warriors             |    Duskrend             |         56 | Protectors           |
//  | Duskrend             |         43 | Protectors           |    Duskfiend            |          0 | Warriors             |
//  | Ironwraith           |          2 | Warriors             |    Soulrazor            |         64 | Protectors           |
//  | Soulrazor            |         30 | Protectors           |    Ironwraith           |         42 | Warriors             |
//  | Ironwraith           |         62 | Warriors             |    Soulrazor            |          2 | Protectors           |
//  | Soulrazor            |         23 | Protectors           |    Ironwraith           |         19 | Warriors             |
//  | Ironwraith           |         44 | Warriors             |    Soulrazor            |          0 | Protectors           |
//  
//  
//  Winner: Protectors
//  
//  
//  Army Warriors:
//  
//  | Name            | Type            | Max Health | Current Health  | Strength   |
//  ----------------------------------------------------------------------------------
//  | Ironwraith      | NUGGLE          |         72 |              19 |         68 |
//  | Duskfiend       | CEFFYL          |         96 |               0 |         52 |
//  | Blightwing      | NUGGLE          |         85 |              11 |         76 |
//  | Voidfang        | CEFFYL          |         65 |               0 |         93 |
//  | Hexmaw          | CEFFYL          |         65 |              65 |         98 |
//  | Grimshade       | NUGGLE          |         74 |               3 |         79 |
//  
//  
//  Army Protectors:
//  
//  | Name            | Type            | Max Health | Current Health  | Strength   |
//  ----------------------------------------------------------------------------------
//  | Soulrazor       | CEFFYL          |         66 |               0 |         82 |
//  | Duskrend        | MACARA          |        100 |              56 |         89 |
//  | Vilethorn       | CEFFYL          |         70 |               0 |         70 |
//  | Nightbane       | BAHAMUT         |         99 |              99 |         81 |
//  | Frostbane       | MACARA          |         96 |               0 |         85 |
//  | Pyrestalker     | BAHAMUT         |         71 |               0 |         76 |
//  



//TestCase2: Using Default name and size 
//Output:
// 
//  Options:
//          1. Load Game
//          2. Quit
//  
//  1
//  
//  For each army, do you wish to modify their names and size
//  1. Yes
//  2. No
//  
//  2
//  Using default army names and size
//  
//  
//  
//  Army A:
//  
//  | Name            | Type            | Max Health | Current Health  | Strength   |
//  ----------------------------------------------------------------------------------
//  | Frostbane       | BAHAMUT         |         61 |              61 |         76 |
//  | Pyrestalker     | BAHAMUT         |         97 |              97 |         51 |
//  | Ironwraith      | BAHAMUT         |        100 |             100 |         54 |
//  | Duskfiend       | CEFFYL          |         56 |              56 |         74 |
//  | Blightwing      | MACARA          |         79 |              79 |         77 |
//  | Voidfang        | CEFFYL          |         63 |              63 |         73 |
//  | Hexmaw          | NUGGLE          |         78 |              78 |         78 |
//  | Grimshade       | BAHAMUT         |         90 |              90 |         80 |
//  
//  
//  Army B:
//  
//  | Name            | Type            | Max Health | Current Health  | Strength   |
//  ----------------------------------------------------------------------------------
//  | Doomshade       | NUGGLE          |         89 |              89 |         94 |
//  | Wraithkin       | MACARA          |         94 |              94 |         88 |
//  | Emberfang       | CEFFYL          |         83 |              83 |         64 |
//  | Frostclaw       | NUGGLE          |         88 |              88 |         74 |
//  | Soulrazor       | NUGGLE          |         97 |              97 |         94 |
//  | Duskrend        | BAHAMUT         |         97 |              97 |         51 |
//  | Vilethorn       | NUGGLE          |         98 |              98 |         96 |
//  | Nightbane       | MACARA          |         51 |              51 |         64 |
//  
//  
//  | Attacker             | Damage     | Army                 |    Defender             | Health     | Army                 |
//  --------------------------------------------------------------------------------------------------------------------------
//  | Grimshade            |         65 | A                    |    Nightbane            |          0 | B                    |
//  | Vilethorn            |         59 | B                    |    Hexmaw               |         19 | A                    |
//  | Hexmaw               |         11 | A                    |    Vilethorn            |         87 | B                    |
//  | Vilethorn            |         38 | B                    |    Hexmaw               |          0 | A                    |
//  | Duskrend             |         80 | B                    |    Voidfang             |          0 | A                    |
//  | Blightwing           |         53 | A                    |    Soulrazor            |         44 | B                    |
//  | Soulrazor            |          4 | B                    |    Blightwing           |         75 | A                    |
//  | Blightwing           |         74 | A                    |    Soulrazor            |          0 | B                    |
//  | Duskfiend            |         69 | A                    |    Frostclaw            |         19 | B                    |
//  | Frostclaw            |         72 | B                    |    Duskfiend            |          0 | A                    |
//  | Ironwraith           |         59 | A                    |    Emberfang            |         24 | B                    |
//  | Emberfang            |         25 | B                    |    Ironwraith           |         75 | A                    |
//  | Ironwraith           |         45 | A                    |    Emberfang            |          0 | B                    |
//  | Wraithkin            |         17 | B                    |    Pyrestalker          |         80 | A                    |
//  | Pyrestalker          |         27 | A                    |    Wraithkin            |         67 | B                    |
//  | Wraithkin            |         40 | B                    |    Pyrestalker          |         40 | A                    |
//  | Pyrestalker          |         56 | A                    |    Wraithkin            |         11 | B                    |
//  | Wraithkin            |         55 | B                    |    Pyrestalker          |          0 | A                    |
//  | Doomshade            |         88 | B                    |    Frostbane            |          0 | A                    |
//  
//  
//  Winner: B
//  
//  
//  Army A:
//  
//  | Name            | Type            | Max Health | Current Health  | Strength   |
//  ----------------------------------------------------------------------------------
//  | Frostbane       | BAHAMUT         |         61 |               0 |         76 |
//  | Pyrestalker     | BAHAMUT         |         97 |               0 |         51 |
//  | Ironwraith      | BAHAMUT         |        100 |              75 |         54 |
//  | Duskfiend       | CEFFYL          |         56 |               0 |         74 |
//  | Blightwing      | MACARA          |         79 |              75 |         77 |
//  | Voidfang        | CEFFYL          |         63 |               0 |         73 |
//  | Hexmaw          | NUGGLE          |         78 |               0 |         78 |
//  | Grimshade       | BAHAMUT         |         90 |              90 |         80 |
//  
//  
//  Army B:
//  
//  | Name            | Type            | Max Health | Current Health  | Strength   |
//  ----------------------------------------------------------------------------------
//  | Doomshade       | NUGGLE          |         89 |              89 |         94 |
//  | Wraithkin       | MACARA          |         94 |              11 |         88 |
//  | Emberfang       | CEFFYL          |         83 |               0 |         64 |
//  | Frostclaw       | NUGGLE          |         88 |              19 |         74 |
//  | Soulrazor       | NUGGLE          |         97 |               0 |         94 |
//  | Duskrend        | BAHAMUT         |         97 |              97 |         51 |
//  | Vilethorn       | NUGGLE          |         98 |              87 |         96 |
//  | Nightbane       | MACARA          |         51 |               0 |         64 |
//  
//  




//TestCase3: Entering invalid sizes
//Output:
// 
//  Options:
//          1. Load Game
//          2. Quit
//  
//  1
//  
//  For each army, do you wish to modify their names and size
//  1. Yes
//  2. No
//  
//  1
//  
//  Enter Army 1 Name:
//  
//  Warriors
//  
//  Enter Army 2 Name:
//  
//  Protectors
//  
//  Enter the size of both armies(Max: 8):
//  
//  9
//  
//  Enter the size of both armies(Max: 8):
//
//  -1
//  
//  Enter the size of both armies(Max: 8):
//  
//  0
//  
//  Enter the size of both armies(Max: 8):
//  
//  1
//


//TestCase4: Quit
//Output:
// 
//  Options:
//          1. Load Game
//          2. Quit
//  
//  2
//  
//  Program now closed
//
