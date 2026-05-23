#include "eniesLobby.h"

/*
NOTE:
-According to the testcase of the school, the morale updating mechanic will not applied if the straw hat destroy buildings.
*/

/*
 * BattleContext
 */
BattleContext::BattleContext() {
    turnCount = 0;
    morale = 0;
    alarmLevel = 0;
    rescueProgress = 0;
    escapeProgress = 0;
    busterCallTimer = 0;
    mainGateDestroyed = false;
    robinRescued = false;
    bridgeOpened = false;
    battleEnded = false;
    resultCode = "";
}

void BattleContext::nextTurn() {
    // TODO: implement
}

/*
 * Character
 */
Character::Character() {
    name = "";
    hp = 0;
    maxHp = 0;
    atk = 0;
    def = 0;
    speed = 0;
    energy = 0;
    alive = false;
}

// Constructor for class Character with parameters
Character::Character(string name, int hp, int atk, int def, int speed, int energy) {
    this->name = name;
    this->hp = (hp < 0)? 0 : hp;
    this->atk = atk;
    this->def = def;
    this->speed = speed;
    this->energy = (energy < 0) ? 0 : (energy > 100) ? 100 : energy; // Make sure 0 <= energy <= 100
    this->maxHp = this->hp;
    this->isLowestHP = false;
    if (this->hp > 0) {
        this->alive = true; // Character is alive if hp > 0
    } 
    
    else {
        this->alive = false; // Character is dead if hp <= 0
    }
}

Character::~Character() {
    // TODO: implement if needed
}

int Character::attack(Building* target, BattleContext& context) {
    return 0;
}

int Character::specialSkill(Building* target, BattleContext& context) {
    return 0;
}

void Character::endTurn(BattleContext& context) {
    return ;
}

// Method which makes character recieve damage
void Character::receiveDamage(int damage) {
    if (!this->alive) {
        return; // If is already dead, don't deal damage
    }

    // Calculate the lost hp: lostHp = damage - def of target
    int hpLost = (damage - this->def > 0)? damage - this->def : 0;
    // Deal damage
    this->hp -= hpLost;

    if (hp <= 0) {
        this->hp = 0; // Set hp = 0 in case the damage > current hp
        this->alive = false; // Set the character to dead if hp 
    }
}

bool Character::isAlive() const {
    // TODO: implement
    return alive;
}

/*
GETTER
*/
string Character::getName() const {
    // TODO: implement
    return name;
}

int Character::getHP() const {
    // TODO: implement
    return hp;
}

int Character::getEnergy() const {
    // TODO: implement
    return energy;
}

// Adding getter for def
int Character::getDef() const {
    return def;
}

// Adding getter for maxHP
int Character::getMaxHP() const {
    return maxHp;
}

// Adding getter for atk
int Character::getAtk() const {
    return atk;
}

// Adding getter for speed
int Character::getSpeed() const {
    return speed;
}

/*
SETTER 
*/
// Adding setter for def
void Character::setDef(int def) {
    this->def = def;
    if (this->def < 0) {
        this->def = 0;
    }
}

// Adding setter for hp
void Character::setHP(int hp) {
    if (!this->isAlive()) {
        return;
    }
    this->hp = hp;
    if (this->hp > this->maxHp) {
        this->hp = this->maxHp;
    }

    if (this->hp <= 0) {
        this->hp = 0;
        this->alive = false;
    }
}

// Adding setter for speed
void Character::setSpeed(int speed) {
    this->speed = (speed < 0)? 0 : speed;
}

/*
BOOLEAN METHOD
*/
bool Character::isStrawHat() const {
    return false;
}

bool Character::isCP9() const {
    return false;
}

/*
 * StrawHat
 */
StrawHat::StrawHat() : Character() {
    bounty = 0;
}

StrawHat::StrawHat(string name, int hp, int atk, int def, // Make class StrawHat inherit the Character's attributes and methods
                   int speed, int energy, long long bounty) : Character(name, hp, atk, def, speed, energy) {
    // Assign value for StrawHat's new attribute
    this->defeatedEnemyThisTurn = false; // Set false by default
    this->bounty = bounty;
}

bool StrawHat::isStrawHat() const {
    return true; // Return true if the character is StrawHat   
}

string StrawHat::str() const {
    // This function return the info of StrawHat
    stringstream ss;
    ss << "StrawHat[";
    ss << "name=" << this->name <<", ";
    ss << "hp=" << this->hp << ", ";
    ss << "atk=" << this->atk << ", ";
    ss << "def=" << this->def << ", ";
    ss << "speed=" << this->speed << ", ";
    ss << "energy=" << this->energy << ", ";
    ss << "bounty=" << this->bounty << "]";
    return ss.str(); // Concatenate string and return
}

/*
 * Luffy
 */
Luffy::Luffy(string name, int hp, int atk, int def,
             int speed, int energy, long long bounty) : StrawHat(name, hp, atk, def, speed, energy, bounty) { // Luffy inherited attributes and methods of StrawHat
}

int Luffy::attack(Character* target, BattleContext& context) {
    int dmg;
    int hpBefore = target->getHP(); // Hp before of the target

    if (this->hp > this->maxHp * 0.5) {
        dmg = this->atk; // If hp is above 50%, damage = atk
    }

    else if (this->hp > this->maxHp * 0.3 && this->hp <= this->maxHp * 0.5) {
        dmg = ceil(this->atk * 1.15); // If hp is above 30% and not more than 50%, deal extra 15% damage
    }

    else if (this->hp <= this->maxHp * 0.3) {
        dmg = ceil(this->atk * 1.3); // If hp is not more than 30%, deal extra 30% damage
    }

    int actualDmg = dmg - target->getDef(); // Return the actual dmg
    if (actualDmg < 0) actualDmg = 0; // Make sure the damage not negative
    target->receiveDamage(dmg);

    if (hpBefore > 0 && target->getHP() <= 0) { // Check if the target hp <= 0 and make sure not to hit the dead character
        context.morale += 5; // +5 morale after defeat enemy
    }

    context.alarmLevel = (context.alarmLevel < 0)? 0 : (context.alarmLevel > 100)? 100 : context.alarmLevel; // Make sure the morale in bound

    return actualDmg;
}

int Luffy::specialSkill(Character* target, BattleContext& context) {
    if (this->energy < 20 || this->hp < this->maxHp * 0.15) { // Check skill condition
        return 0; // If the condition is not satisfied, do nothing
    }
    
    int dmg = this->atk * 2; // damage = 200% atk
    int hpLost = ceil(0.08 * this->maxHp); // Luffy lost 8% of his MAX hp
    int hpBefore = target->getHP();
    int actualDmg = dmg - target->getDef();
    if (actualDmg < 0) actualDmg = 0;
    
    this->energy -= 20;
    this->hp -= hpLost;
    target->receiveDamage(dmg);
    
    // Buff stat after using skill
    this->speed += 15;
    this->atk += 15;
    context.alarmLevel += 10;

    if (hpBefore > 0 && target->getHP() <= 0) {
        this->defeatedEnemyThisTurn = true; // Flag if has defeated enemy this turn
    }

    context.alarmLevel = (context.alarmLevel < 0)? 0 : (context.alarmLevel > 100)? 100 : context.alarmLevel;
    return actualDmg;
}

int Luffy::attack(Building* target, BattleContext& context) {
    // Overloading attack for building target
    int dmg;
    if (this->hp > this->maxHp * 0.5) {
        dmg = this->atk;
    }

    else if (this->hp > this->maxHp * 0.3 && this->hp <= this->maxHp * 0.5) {
        dmg = ceil(this->atk * 1.15);
    }

    else if (this->hp <= this->maxHp * 0.3) {
        dmg = ceil(this->atk * 1.3);
    }

    target->receiveDamage(dmg);
    return dmg;
}

int Luffy::specialSkill(Building* target, BattleContext& context) {
    // Overloading special skill for building target
    if (this->energy < 20 || this->hp < this->maxHp * 0.15) {
        return 0;
    }
    
    int dmg = this->atk * 2;
    int hpLost = ceil(0.08 * this->maxHp);
    int hpBefore = target->getHP();
     
    
    this->energy -= 20;
    this->hp -= hpLost;
    context.alarmLevel += 10;
    target->receiveDamage(dmg);
    this->speed += 15;
    this->atk += 15;

    context.alarmLevel = (context.alarmLevel < 0)? 0 : (context.alarmLevel > 100)? 100 : context.alarmLevel;
    return dmg;
}

void Luffy::endTurn(BattleContext& context) {
    if (this->hp <= this->maxHp * 0.3) {
        context.morale += 3; // +3 morale if hp is not more than 30%
    }

    // Endturn effect if defeat enemy
    if (this->defeatedEnemyThisTurn) {
        this->energy += 5; 
        this->defeatedEnemyThisTurn = false; // Reset flag
    }

    // Make sure the energy and morale in bound: [0, 100]
    this->energy = (this->energy < 0)? 0 : (this->energy > 100)? 100 : this->energy; 
    context.morale = (context.morale < 0)? 0 : (context.morale > 100)? 100 : context.morale;
}

/*
 * Zoro
 */
Zoro::Zoro(string name, int hp, int atk, int def,
           int speed, int energy, long long bounty) : StrawHat(name, hp, atk, def, speed, energy, bounty) {
}

int Zoro::attack(Character* target, BattleContext& context) {
    int dmg = this->atk + ceil(this->def * 0.2); // Gain damage base on defense
    int hpBefore = target->getHP();

    if (target->getHP() < target->getMaxHP() * 0.4) {
        dmg = dmg + ceil(0.15 * this->atk); // Increase damage if target has low hp
    }

    int actualDmg = dmg - target->getDef();
    if (actualDmg < 0) actualDmg = 0;
    target->receiveDamage(dmg);

    if (hpBefore > 0 && target->getHP() <= 0) {
        this->defeatedEnemyThisTurn = true;
    }

    return actualDmg;
}

int Zoro::specialSkill(Character* target, BattleContext& context) {
    if (this->energy < 15) {
        return 0;
    }

    int hpBefore = target->getHP();
    int targetMaxHp = target->getMaxHP();
    int dmg = ceil(this->atk * 2.2);

    this->energy -= 15;
    if (hpBefore < targetMaxHp * 0.5) {
        dmg += ceil(dmg * 0.5);
    }
    
    int actualDmg = dmg - target->getDef();
    if (actualDmg < 0) actualDmg = 0;
    target->receiveDamage(dmg);

    // Special effect if defeat enemy using skill
    if (hpBefore > 0 && target->getHP() <= 0) {
        context.morale += 4;
        this->energy += 8;
        this->atk += ceil(this->atk * 0.05);
    }

    this->energy = (this->energy < 0)? 0 : (this->energy > 100)? 100 : this->energy;
    context.morale = (context.morale < 0)? 0 : (context.morale > 100)? 100 : context.morale;

    return actualDmg;
}

int Zoro::attack(Building* target, BattleContext& context) {
    // Overloading function for building
    int dmg = this->atk + ceil(this->def * 0.2);
    int hpBefore = target->getHP();

    if (target->getHP() < target->getMaxHP() * 0.4) {
        dmg = dmg + ceil(0.15 * this->atk);
    }

    target->receiveDamage(dmg);

    return dmg;
}

int Zoro::specialSkill(Building* target, BattleContext& context) {
    // Overloading function for building
    if (this->energy < 15) {
        return 0;
    }

    int hpBefore = target->getHP();
    int targetMaxHp = target->getMaxHP();
    int dmg = (this->atk * 22 + 9) / 10.0;

    this->energy -= 15;
    if (hpBefore < targetMaxHp * 0.5) {
        dmg += ceil(dmg * 0.5);
    }
    
    target->receiveDamage(dmg);
    return dmg;
}

void Zoro::endTurn(BattleContext& context) {
    if (this->defeatedEnemyThisTurn) {
        context.morale += 6;
        this->atk += ceil(this->atk * 0.05);
        defeatedEnemyThisTurn = false;

        context.morale = (context.morale < 0)? 0 : (context.morale > 100)? 100 : context.morale;
    }
}

/*
 * Sanji
 */
Sanji::Sanji(string name, int hp, int atk, int def,
             int speed, int energy, long long bounty) {
    // TODO: implement
}

int Sanji::attack(Character* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

int Sanji::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

int Sanji::attack(Building* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

int Sanji::specialSkill(Building* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

void Sanji::endTurn(BattleContext& context) {
    // TODO: implement
}

/*
 * Nami
 */
Nami::Nami(string name, int hp, int atk, int def,
           int speed, int energy, long long bounty) {
    // TODO: implement
}

int Nami::attack(Character* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

int Nami::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

int Nami::attack(Building* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

int Nami::specialSkill(Building* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

void Nami::endTurn(BattleContext& context) {
    // TODO: implement
}

/*
 * Chopper
 */
Chopper::Chopper(string name, int hp, int atk, int def,
                 int speed, int energy, long long bounty) {
    // TODO: implement
}

int Chopper::attack(Character* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

int Chopper::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

int Chopper::attack(Building* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

void Chopper::endTurn(BattleContext& context) {
    // TODO: implement
}

/*
 * Usopp
 */
Usopp::Usopp(string name, int hp, int atk, int def,
             int speed, int energy, long long bounty) {
    // TODO: implement
}

int Usopp::attack(Character* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

int Usopp::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

int Usopp::attack(Building* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

int Usopp::specialSkill(Building* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

void Usopp::endTurn(BattleContext& context) {
    // TODO: implement
}

/*
 * Franky
 */
Franky::Franky(string name, int hp, int atk, int def,
               int speed, int energy, long long bounty) {
    // TODO: implement
}

int Franky::attack(Character* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

int Franky::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

int Franky::attack(Building* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

int Franky::specialSkill(Building* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

void Franky::endTurn(BattleContext& context) {
    // TODO: implement
}

/*
 * CP9Agent
 */
CP9Agent::CP9Agent() : Character() {
    doriki = 0;
}

CP9Agent::CP9Agent(string name, int hp, int atk, int def,
                   int speed, int energy, int doriki) {
    // TODO: implement
}

bool CP9Agent::isCP9() const {
    // TODO: implement
}

string CP9Agent::str() const {
    // TODO: implement
    return "";
}

/*
 * Lucci
 */
Lucci::Lucci(string name, int hp, int atk, int def,
             int speed, int energy, int doriki) {
    // TODO: implement
}

int Lucci::attack(Character* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

int Lucci::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

void Lucci::endTurn(BattleContext& context) {
    // TODO: implement
}

/*
 * Kaku
 */
Kaku::Kaku(string name, int hp, int atk, int def,
           int speed, int energy, int doriki) {
    // TODO: implement
}

int Kaku::attack(Character* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

int Kaku::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

void Kaku::endTurn(BattleContext& context) {
    // TODO: implement
}

/*
 * Jabra
 */
Jabra::Jabra(string name, int hp, int atk, int def,
             int speed, int energy, int doriki) {
    // TODO: implement
}

int Jabra::attack(Character* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

int Jabra::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

void Jabra::endTurn(BattleContext& context) {
    // TODO: implement
}

/*
 * Blueno
 */
Blueno::Blueno(string name, int hp, int atk, int def,
               int speed, int energy, int doriki) {
    // TODO: implement 
}

int Blueno::attack(Character* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

int Blueno::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

void Blueno::endTurn(BattleContext& context) {
    // TODO: implement
}

/*
 * Kalifa
 */
Kalifa::Kalifa(string name, int hp, int atk, int def,
               int speed, int energy, int doriki) {
    // TODO: implement
}

int Kalifa::attack(Character* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

int Kalifa::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

void Kalifa::endTurn(BattleContext& context) {
    // TODO: implement
}

/*
 * Kumadori
 */
Kumadori::Kumadori(string name, int hp, int atk, int def,
                   int speed, int energy, int doriki) {
    // TODO: implement
}

int Kumadori::attack(Character* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

int Kumadori::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

void Kumadori::endTurn(BattleContext& context) {
    // TODO: implement
}

/*
 * Fukurou
 */
Fukurou::Fukurou(string name, int hp, int atk, int def,
                 int speed, int energy, int doriki) {
    // TODO: implement
}

int Fukurou::attack(Character* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

int Fukurou::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

void Fukurou::endTurn(BattleContext& context) {
    // TODO: implement
}

/*
 * Building
 */
Building::Building(string name, int hp) {
    // TODO: implement
}

Building::~Building() {
    // TODO: implement if needed
}

void Building::receiveDamage(int damage) {
    // TODO: implement
}

bool Building::isDestroyed() const {
    // TODO: implement
    return destroyed;
}

void Building::onDestroyed(BattleContext& context) {
    return ;
}

string Building::str () const {
    // TODO: implement
    return "";
}

/*
 * MainGate
 */
MainGate::MainGate(string name, int hp) : Building(name, hp) {}

void MainGate::applyEffect(BattleContext& context) {
    // TODO: implement
}

void MainGate::onDestroyed(BattleContext& context) {
    // TODO: implement
}

/*
 * Courthouse
 */
Courthouse::Courthouse(string name, int hp) : Building(name, hp) {}

void Courthouse::applyEffect(BattleContext& context) {
    // TODO: implement
}

void Courthouse::onDestroyed(BattleContext& context) {
    // TODO: implement
}

/*
 * TowerOfJustice
 */
TowerOfJustice::TowerOfJustice(string name, int hp) : Building(name, hp) {}

void TowerOfJustice::applyEffect(BattleContext& context) {
    // TODO: implement
}

/*
 * BridgeOfHesitation
 */
BridgeOfHesitation::BridgeOfHesitation(string name, int hp) : Building(name, hp) {}

void BridgeOfHesitation::applyEffect(BattleContext& context) {
    // TODO: implement
}

/*
 * BusterCallShip
 */
BusterCallShip::BusterCallShip(string name, int hp) : Building(name, hp) {}

void BusterCallShip::applyEffect(BattleContext& context) {
    // TODO: implement
}

void BusterCallShip::onDestroyed(BattleContext& context) {
    // TODO: implement
}

/*
 * EniesLobbyBattle
 */
EniesLobbyBattle::EniesLobbyBattle(const string& filename) {
    // TODO: implement
}

EniesLobbyBattle::~EniesLobbyBattle() {
    // TODO: implement
}

void EniesLobbyBattle::loadFromFile(const string& filename) {
    // TODO: implement
}

void EniesLobbyBattle::addStrawHat(Character* character) {
    // TODO: implement
}

void EniesLobbyBattle::addCP9Agent(Character* character) {
    // TODO: implement
}

void EniesLobbyBattle::addBuilding(Building* building) {
    // TODO: implement
}

void EniesLobbyBattle::buildTurnOrder() {
    // TODO: implement
}

void EniesLobbyBattle::runBattle() {
    // TODO: implement
}

void EniesLobbyBattle::processTurn(Character* character) {
    // TODO: implement
}

void EniesLobbyBattle::processBuildings() {
    // TODO: implement
}

void EniesLobbyBattle::checkEndCondition() {
    // TODO: implement
}

string EniesLobbyBattle::getResult() const {
    // TODO: implement
    return "";
}
