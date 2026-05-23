#include "eniesLobby.h"

/*
NOTE:
-According to the testcase of the school, the morale updating mechanic will not applied if the straw hat destroy buildings.
-According to the testcase of the school, any condition using name means the name of the class, not the attribute "name"
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
    courtDestroyed = false;
    increaseRescue = false;
    robinRescued = false;
    bridgeOpened = false;
    battleEnded = false;
    resultCode = "";
}

void BattleContext::nextTurn() {
    this->turnCount++;
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
    isLowestHP = false;
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

int Character::getIsLowestHP() const {
    return isLowestHP;
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

// Adding setter for isLowestHP
void Character::setIsLowestHP(bool isLowestHP) {
    this->isLowestHP = isLowestHP;
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

// Add boolean method for specific name check
bool Character::isLuffy() const {
    return false;
}

bool Character::isNami() const {
    return false;
}

bool Character::isLucci() const {
    return false;
}

bool Character::isJabra() const {
    return false;
}

bool Character::canUseSkill() const {
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

bool Luffy::canUseSkill() const {
    return (this->energy >= 20 && this->hp >= this->maxHp * 0.15);
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

bool Zoro::canUseSkill() const {
    return (this->energy >= 15);
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
             int speed, int energy, long long bounty) : StrawHat(name, hp, atk, def, speed, energy, bounty) {
}

int Sanji::attack(Character* target, BattleContext& context) {
    int dmg = this->atk + ceil(this->speed * 0.5);
    int hpBefore = target->getHP(); 
    int targetDef = target->getDef();

    // Bypass defense mechanics
    if (targetDef < this->def) {
        dmg += ceil(dmg * 0.1);
    }

    int actualDmg = dmg - target->getDef();
    if (actualDmg < 0) actualDmg = 0;
    target->receiveDamage(dmg);

    if (hpBefore > 0 && target->getHP() <= 0) {
        this->defeatedEnemyThisTurn = true;
    }

    return actualDmg;
}

int Sanji::specialSkill(Character* target, BattleContext& context) {
    if (this->energy < 18) {
        return 0;
    }

    this->energy -= 18;
    int dmg = ceil(2.1 * this->atk);
    int hpBefore = target->getHP();
    int actualDmg = dmg - target->getDef();
    if (actualDmg < 0) actualDmg = 0;
    target->receiveDamage(dmg);
    
    int targetDef = target->getDef();
    if (target->isJabra()) {
        target->setDef(targetDef - 12);
    }
    else {
        target->setDef(targetDef - 8);
    }

    if (hpBefore > 0 && target->getHP() <= 0) {
        this->defeatedEnemyThisTurn = true;
    }

    return actualDmg;
}

int Sanji::attack(Building* target, BattleContext& context) {
    int dmg = this->atk + ceil(this->speed * 0.5);
    target->receiveDamage(dmg);
    return dmg;
}

int Sanji::specialSkill(Building* target, BattleContext& context) {
    if (this->energy < 18) {
        return 0;
    }
    
    this->energy -= 18;
    int dmg = ceil(2.1 * this->atk);
    target->receiveDamage(dmg);
    return dmg;
}

bool Sanji::canUseSkill() const {
    return (this->energy >= 18);
}

void Sanji::endTurn(BattleContext& context) {
    if (this->defeatedEnemyThisTurn) {
        context.morale += 8;
        this->atk += ceil(this->atk * 0.1);
        defeatedEnemyThisTurn = false;

        context.morale = (context.morale < 0)? 0 : (context.morale > 100)? 100 : context.morale;
    }
}

/*
 * Nami
 */
Nami::Nami(string name, int hp, int atk, int def,
           int speed, int energy, long long bounty) : StrawHat(name, hp, atk, def, speed, energy, bounty) {
}

int Nami::attack(Character* target, BattleContext& context) {
    int dmg = this->atk;
    int targetDef = target->getDef();
    int hpBefore = target->getHP();
    target->setDef(ceil(targetDef * 0.7));
    int actualDmg = dmg - target->getDef();
    if (actualDmg < 0) actualDmg = 0;
    target->receiveDamage(dmg);
    target->setDef(targetDef);

    if (hpBefore > 0 && target->getHP() <= 0) {
        this->defeatedEnemyThisTurn = true;
        context.morale += 5;
    }

    context.morale = (context.morale < 0)? 0 : (context.morale > 100)? 100 : context.morale;
    return actualDmg;
}

int Nami::specialSkill(Character* target, BattleContext& context) {
    if (this->energy < 20) {
        return 0;
    }

    int dmg = this->atk + 40;
    int actualDmg = dmg - target->getDef();
    if (actualDmg < 0) actualDmg = 0;
    int targetSpeed = target->getSpeed();
    int targetHP = target->getHP();

    this->energy -= 20;
    target->receiveDamage(dmg);
    target->setSpeed(targetSpeed - 10); // reduce target speed
    context.alarmLevel -= 5;
    context.busterCallTimer++;
    
    if (targetHP > 0 && target->getHP() <= 0) {
        this->defeatedEnemyThisTurn = true;
        context.morale += 5;
    }

    // Make sure morale, alarmLevel and busterCallTimer in bound: [0, 100]
    context.morale = (context.morale < 0)? 0 : (context.morale > 100)? 100 : context.morale;
    context.alarmLevel = (context.alarmLevel < 0)? 0 : (context.alarmLevel > 100)? 100 : context.alarmLevel;
    context.busterCallTimer = (context.busterCallTimer < 0)? 0 : context.busterCallTimer;

    return actualDmg;
}

int Nami::attack(Building* target, BattleContext& context) {
    int dmg = ceil(this->atk * 0.5);
    target->receiveDamage(dmg);
    return dmg;
}

int Nami::specialSkill(Building* target, BattleContext& context) {
    if (this->energy < 20) {
        return 0;
    }
    
    this->energy -= 20;
    int dmg = ceil((this->atk + 40) * 1.5);
    target->receiveDamage(dmg);
    context.alarmLevel -= 5;
    context.busterCallTimer++;

    context.alarmLevel = (context.alarmLevel < 0)? 0 : (context.alarmLevel > 100)? 100 : context.alarmLevel;

    if (context.busterCallTimer < 0) {
        context.busterCallTimer = 0;
    } 

    return dmg;
}

bool Nami::canUseSkill() const {
    return (this->energy >= 20);
}

void Nami::endTurn(BattleContext& context) {
    if (this->defeatedEnemyThisTurn) {
        energy += 6;
        this->defeatedEnemyThisTurn = false;
    }
    
    this->energy = (this->energy < 0)? 0 : (this->energy > 100)? 100 : this->energy;
}

/*
 * Chopper
 */
Chopper::Chopper(string name, int hp, int atk, int def,
                 int speed, int energy, long long bounty) : StrawHat(name, hp, atk, def, speed, energy, bounty) {
    // TODO: implement
}

int Chopper::attack(Character* target, BattleContext& context) {
    int dmg = this->atk;
    int actualDmg = dmg - target->getDef();
    if (actualDmg < 0) actualDmg = 0;
    int hpBefore = target->getHP();
    target->receiveDamage(dmg);
    if (hpBefore > 0 && target->getHP() <= 0) {
        this->defeatedEnemyThisTurn = true;
        context.morale += 5;
    }

    context.morale = (context.morale < 0)? 0 : (context.morale > 100)? 100 : context.morale;

    return actualDmg;
}

int Chopper::specialSkill(Character* target, BattleContext& context) {
    if (this->energy < 15) {
        return 0;
    }

    // If not StrawHat -> not heal
    if (!target->isStrawHat()) {
        return 0;
    }

    this->energy -= 15;
    int heal = 35 + ceil(this->atk * 0.5);
    int curHp = target->getHP();
    target->setHP(curHp + heal);

    // Plus morale if target is luffy
    if (target->isLuffy()) {
        context.morale += 5;
    }

    context.morale = (context.morale < 0)? 0 : (context.morale > 100)? 100 : context.morale;

    return 0;
}

int Chopper::attack(Building* target, BattleContext& context) {
    int dmg = this->atk;
    int hpBefore = target->getHP();
    target->receiveDamage(dmg);

    return dmg;
}

bool Chopper::canUseSkill() const {
    return (this->energy >= 15);
}

void Chopper::endTurn(BattleContext& context) {
    if (this->defeatedEnemyThisTurn) {
        this->defeatedEnemyThisTurn = false;
    }
    return;
}

/*
 * Usopp
 */
Usopp::Usopp(string name, int hp, int atk, int def,
             int speed, int energy, long long bounty) : StrawHat(name, hp, atk, def, speed, energy, bounty) {
}

int Usopp::attack(Character* target, BattleContext& context) {
    int dmg = this->atk;
    int hpBefore = target->getHP();
    if (target->getSpeed() < 50) {
        dmg += ceil(0.2 * dmg);
    }
    
    int actualDmg = dmg - target->getDef();
    if (actualDmg < 0) actualDmg = 0;
    target->receiveDamage(dmg);
    
    if (hpBefore > 0 && target->getHP() <= 0) {
        defeatedEnemyThisTurn = true;
    }

    return actualDmg;
}

int Usopp::specialSkill(Character* target, BattleContext& context) {
    if (this->energy < 16) {
        return 0;
    }

    this->energy -= 16;
    int dmg = ceil(this->atk * 0.8);
    int actualDmg = dmg - target->getDef();
    if (actualDmg < 0) actualDmg = 0;
    int hpBefore = target->getHP();
    int targetSpeed = target->getSpeed();
    
    target->receiveDamage(dmg);
    target->setSpeed(targetSpeed - 12);
    context.escapeProgress += 8;

    if (hpBefore > 0 && target->getHP() <= 0) {
        defeatedEnemyThisTurn = true;
    }

    return actualDmg;
}

int Usopp::attack(Building* target, BattleContext& context) {
    int dmg = ceil(this->atk * 0.5);
    target->receiveDamage(dmg);
    return dmg;
}

int Usopp::specialSkill(Building* target, BattleContext& context) {
    if (this->energy < 16) {
        return 0;
    }

    this->energy -= 16;
    int dmg = ceil(this->atk * 0.8);
    target->receiveDamage(dmg);
    context.escapeProgress += 8;
    context.escapeProgress = (context.escapeProgress < 0)? 0 : (context.escapeProgress > 100)? 100 : context.escapeProgress;

    return dmg;
}

bool Usopp::canUseSkill() const {
    return (this->energy >= 16);
}

void Usopp::endTurn(BattleContext& context) {
    context.morale += 10;
    if (this->defeatedEnemyThisTurn) {
        this->defeatedEnemyThisTurn = false;
    }
    
    context.morale = (context.morale < 0)? 0 : (context.morale > 100)? 100 : context.morale;
}

/*
 * Franky
 */
Franky::Franky(string name, int hp, int atk, int def,
               int speed, int energy, long long bounty) : StrawHat(name, hp, atk, def, speed, energy, bounty) {
}

int Franky::coupDeVent(Character* target, BattleContext& context) {
    this->energy -= 30;
    int dmg = ceil(this->atk * 1.2);
    int actualDmg = dmg - target->getDef();
    if (actualDmg < 0) actualDmg = 0;
    int hpBefore = target->getHP();
    target->receiveDamage(dmg);

    if (hpBefore > 0 && target->getHP() <= 0) {
        defeatedEnemyThisTurn = true;
        context.morale += 5;
    }

    context.morale = (context.morale < 0)? 0 : (context.morale > 100)? 100 : context.morale;

    return actualDmg;
}

int Franky::strongRight(Character* target, BattleContext& context) {
    this->energy -= 20;
    int dmg = ceil(this->atk * 1.8);
    int targetSpeed = target->getSpeed();
    int hpBefore = target->getHP();

    if (target->isLucci()) {
        dmg += ceil(dmg * 0.2);
    } 
    
    int actualDmg = dmg - target->getDef();
    if (actualDmg < 0) actualDmg = 0;
    target->receiveDamage(dmg);
    target->setSpeed(targetSpeed - 8);

    if (hpBefore > 0 && target->getHP() <= 0) {
        defeatedEnemyThisTurn = true;
        context.morale += 5;
    }

    context.morale = (context.morale < 0)? 0 : (context.morale > 100)? 100 : context.morale;

    return actualDmg;
}

int Franky::attack(Character* target, BattleContext& context) {
    int dmg = this->atk + ceil(this->def * 0.3);
    dmg += ceil(dmg * 0.1);
    int actualDmg = dmg - target->getDef();
    if (actualDmg < 0) actualDmg = 0;
    int hpBefore = target->getHP();

    target->receiveDamage(dmg);

    if (hpBefore > 0 && target->getHP() <= 0) {
        defeatedEnemyThisTurn = true;
        context.morale += 5;
    }

    context.morale = (context.morale < 0)? 0 : (context.morale > 100)? 100 : context.morale;

    return actualDmg;
}

int Franky::specialSkill(Character* target, BattleContext& context) {
    if (this->energy >= 30) {
        return coupDeVent(target, context);
    }

    else if (this->energy >= 20) {
        return strongRight(target, context);
    }
    return 0;
}

int Franky::coupDeVent(Building* target, BattleContext& context) {
    this->energy -= 30;
    int buildingHp = target->getHP();
    target->receiveDamage(buildingHp);
    return buildingHp;
}

int Franky::strongRight(Building* target, BattleContext& context) {
    this->energy -= 20;
    int dmg = ceil(this->atk * 1.8);
    target->receiveDamage(dmg);
    return dmg;
}

int Franky::attack(Building* target, BattleContext& context) {
    int dmg = this->atk + ceil(this->def * 0.3);
    target->receiveDamage(dmg);
    return dmg;
}

int Franky::specialSkill(Building* target, BattleContext& context) {
    if (this->energy >= 30) {
        return coupDeVent(target, context);
    }

    else if (this->energy >= 20) {
        return strongRight(target, context);
    }
    return 0;
}

bool Franky::canUseSkill() const {
    return (this->energy >= 20);
}

void Franky::endTurn(BattleContext& context) {
    if (this->hp > this->maxHp * 0.7) {
        this->def += 5;
    }
    else if (this->hp < this->maxHp * 0.3 && this->hp > 0) {
        this->atk += ceil(this->atk * 0.1);
    }

    if (this->defeatedEnemyThisTurn) {
        this->defeatedEnemyThisTurn = false;
    }
}

/*
 * CP9Agent
 */
CP9Agent::CP9Agent() : Character() {
    doriki = 0;
}

CP9Agent::CP9Agent(string name, int hp, int atk, int def,
                   int speed, int energy, int doriki) : Character(name, hp, atk, def, speed, energy) {
}

bool CP9Agent::isCP9() const {
    return true;
}

string CP9Agent::str() const {
    stringstream ss;
    ss << "CP9[";
    ss << "name=" << this->name <<", ";
    ss << "hp=" << this->hp << ", ";
    ss << "atk=" << this->atk << ", ";
    ss << "def=" << this->def << ", ";
    ss << "speed=" << this->speed << ", ";
    ss << "energy=" << this->energy << ", ";
    ss << "doriki=" << this->doriki << "]";

    return ss.str();
}

/*
 * Lucci
 */
Lucci::Lucci(string name, int hp, int atk, int def,
             int speed, int energy, int doriki) : CP9Agent(name, hp, atk, def, speed, energy, doriki) {
}

int Lucci::attack(Character* target, BattleContext& context) {
    int dmg = this->atk + ceil(this->doriki * 0.05);
    int hpBefore = target->getHP();
    
    if (target->getHP() < target->getMaxHP() * 0.5) {
        dmg += ceil(dmg * 0.2);
    }
    
    int actualDmg = dmg - target->getDef();
    if (actualDmg < 0) actualDmg = 0;

    target->receiveDamage(dmg);    
    return actualDmg;
}

int Lucci::specialSkill(Character* target, BattleContext& context) {
    if (this->energy < 25) {
        return 0;
    }

    this->energy -= 25;
    int dmg = ceil(this->atk * 2.8);
    int targetDef = target->getDef();
    int hpBefore = target->getHP();
    
    target->setDef(ceil(targetDef * 0.5));
    int actualDmg = dmg - target->getDef();
    if (actualDmg < 0) actualDmg = 0;

    target->receiveDamage(dmg);
    target->setDef(targetDef);

    if (hpBefore > 0 && target->getHP() <= 0 && target->isStrawHat()) {
        context.morale -= 10;
    }

    context.morale = (context.morale < 0)? 0 : (context.morale > 100)? 100 : context.morale;
    
    return actualDmg;
}

bool Lucci::canUseSkill() const {
    return (this->energy >= 25);
}

void Lucci::endTurn(BattleContext& context) {
    if (this->hp < this->maxHp * 0.4) {
        this->atk += ceil(this->atk * 0.05);
    }
}

/*
 * Kaku
 */
Kaku::Kaku(string name, int hp, int atk, int def,
           int speed, int energy, int doriki) : CP9Agent(name, hp, atk, def, speed, energy, doriki) {
}

int Kaku::attack(Character* target, BattleContext& context) {
    int dmg = this->atk;
    int actualDmg = dmg - target->getDef();
    if (actualDmg < 0) actualDmg = 0;
    int hpBefore = target->getHP();
    
    target->receiveDamage(dmg);

    if (hpBefore > 0 && target->getHP() <= 0 && target->isStrawHat()) {
        context.morale -= 5;
    }
    
    context.morale = (context.morale < 0)? 0 : (context.morale > 100)? 100 : context.morale;
    return actualDmg;
}

int Kaku::specialSkill(Character* target, BattleContext& context) {
    if (this->energy < 20) {
        return 0;
    }

    this->energy -= 20;
    int hpBefore = target->getHP();    
    int totalDmg = 0;
    int actualDmg = 0;
    int def = target->getDef();

    // Multi-hit attack mechanic (120%, 100%, 80%) 
    if (target->isAlive()) {
        int dmg1 = ceil(this->atk * 1.2);
        target->receiveDamage(dmg1);
        actualDmg += (dmg1 - def > 0) ? (dmg1 - def) : 0;
    }
    if (target->isAlive()) {
        int dmg2 = this->atk;
        target->receiveDamage(dmg2);
        actualDmg += (dmg2 - def > 0) ? (dmg2 - def) : 0;
    }
    if (target->isAlive()) {
        int dmg3 = ceil(this->atk * 0.8);
        target->receiveDamage(dmg3);
        actualDmg += (dmg3 - def > 0) ? (dmg3 - def) : 0;
    }

    if (hpBefore > 0 && target->getHP() <= 0 && target->isStrawHat()) {
        context.morale -= 5;
    }
    
    context.morale = (context.morale < 0)? 0 : (context.morale > 100)? 100 : context.morale;

    return actualDmg;
}

bool Kaku::canUseSkill() const {
    return (this->energy >= 20);
}

void Kaku::endTurn(BattleContext& context) {
    
}

/*
 * Jabra
 */
Jabra::Jabra(string name, int hp, int atk, int def,
             int speed, int energy, int doriki) : CP9Agent(name, hp, atk, def, speed, energy, doriki) { 
}

int Jabra::attack(Character* target, BattleContext& context) {
    int dmg = this->atk;
    int actualDmg = dmg - target->getDef();
    if (actualDmg < 0) actualDmg = 0;
    int hpBefore = target->getHP();
    target->receiveDamage(dmg);

    return actualDmg;
}

int Jabra::specialSkill(Character* target, BattleContext& context) {
    if (this->energy < 18) {
        return 0;
    }

    this->energy -= 18;
    int dmg = ceil(this->atk * 1.5);
    int hpBefore = target->getHP();

    if (this->hp < this->maxHp * 0.3) {
        dmg += ceil(0.25 * dmg);
    }

    int actualDmg = dmg - target->getDef();
    if (actualDmg < 0) actualDmg = 0;

    target->receiveDamage(dmg);

    if (hpBefore > 0 && target->getHP() <= 0 && target->isStrawHat()) {
        context.morale -= 5;
    }
    
    context.morale = (context.morale < 0)? 0 : (context.morale > 100)? 100 : context.morale;

    return actualDmg;
}

bool Jabra::canUseSkill() const {
    return (this->energy >= 18);
}

void Jabra::endTurn(BattleContext& context) {
}

/*
 * Blueno
 */
Blueno::Blueno(string name, int hp, int atk, int def,
               int speed, int energy, int doriki) : CP9Agent(name, hp, atk, def, speed, energy, doriki) {
}

int Blueno::attack(Character* target, BattleContext& context) {
    
    int dmg = this->atk;
    int actualDmg = dmg - target->getDef();
    if (actualDmg < 0) actualDmg = 0;
    int hpBefore = target->getHP();
    target->receiveDamage(dmg);

    if (hpBefore > 0 && target->getHP() <= 0 && target->isStrawHat()) {
        context.morale -= 5;
    }
    
    context.morale = (context.morale < 0)? 0 : (context.morale > 100)? 100 : context.morale;
    return actualDmg;
}

int Blueno::specialSkill(Character* target, BattleContext& context) {
    
    if (this->energy < 15) {
        return 0;
    }

    this->energy -= 15;
    int dmg = ceil(this->atk * 1.3);
    int hpBefore = target->getHP();

    if (this->hp > this->maxHp * 0.5) {
        dmg += 20;
    } 

    else {
        dmg += 40;
    }

    int actualDmg = dmg - target->getDef();
    if (actualDmg < 0) actualDmg = 0;

    target->receiveDamage(dmg);

    if (hpBefore > 0 && target->getHP() <= 0 && target->isStrawHat()) {
        context.morale -= 5;
    }
    
    context.morale = (context.morale < 0)? 0 : (context.morale > 100)? 100 : context.morale;
    return actualDmg;
}

bool Blueno::canUseSkill() const {
    return (this->energy >= 15);
}

void Blueno::endTurn(BattleContext& context) {
}

/*
 * Kalifa
 */
Kalifa::Kalifa(string name, int hp, int atk, int def,
               int speed, int energy, int doriki) : CP9Agent(name, hp, atk, def, speed, energy, doriki) {
}

int Kalifa::attack(Character* target, BattleContext& context) {
    int dmg = this->atk;
    int actualDmg = dmg - target->getDef();
    if (actualDmg < 0) actualDmg = 0;
    int hpBefore = target->getHP();
    target->receiveDamage(dmg);

    return actualDmg;
}

int Kalifa::specialSkill(Character* target, BattleContext& context) { 
    if (this->energy < 18) {
        return 0;
    }

    this->energy -= 18;
    int dmg = ceil(this->atk * 1.4);
    int actualDmg = dmg - target->getDef();
    if (actualDmg < 0) actualDmg = 0;
    int targetSpeed = target->getSpeed();
    
    target->receiveDamage(dmg);
    target->setSpeed(targetSpeed - 6);
    
    if (target->isNami()) {
        context.morale -= 12;
    }

    else {
        context.morale -= 8;
    }

    context.morale = (context.morale < 0)? 0 : (context.morale > 100)? 100 : context.morale;
    return actualDmg;
}

bool Kalifa::canUseSkill() const {
    return (this->energy >= 18);
}

void Kalifa::endTurn(BattleContext& context) {
}

/*
 * Kumadori
 */
Kumadori::Kumadori(string name, int hp, int atk, int def,
                   int speed, int energy, int doriki) : CP9Agent(name, hp, atk, def, speed, energy, doriki) {
}

int Kumadori::attack(Character* target, BattleContext& context) {
    int dmg = this->atk;
    int actualDmg = dmg - target->getDef();
    if (actualDmg < 0) actualDmg = 0;
    int hpBefore = target->getHP();
    target->receiveDamage(dmg);

    if (hpBefore > 0 && target->getHP() <= 0 && target->isStrawHat()) {
        context.morale -= 5;
    }
    
    context.morale = (context.morale < 0)? 0 : (context.morale > 100)? 100 : context.morale;
    return actualDmg;
}

int Kumadori::specialSkill(Character* target, BattleContext& context) {
    if (this->energy < 16) {
        return 0;
    }

    this->energy -= 16;
    int dmg = 30 + ceil(doriki * 0.1);
    int hpBefore = target->getHP();

    if (this->hp < this->maxHp * 0.4) {
        dmg += 25;
    }

    int actualDmg = dmg - target->getDef();
    if (actualDmg < 0) actualDmg = 0;

    target->receiveDamage(dmg);

    if (hpBefore > 0 && target->getHP() <= 0 && target->isStrawHat()) {
        context.morale -= 5;
    }
    
    context.morale = (context.morale < 0)? 0 : (context.morale > 100)? 100 : context.morale;
    return actualDmg;
}

bool Kumadori::canUseSkill() const {
    return (this->energy >= 16);
}

void Kumadori::endTurn(BattleContext& context) {
}

/*
 * Fukurou
 */
Fukurou::Fukurou(string name, int hp, int atk, int def,
                 int speed, int energy, int doriki) : CP9Agent(name, hp, atk, def, speed, energy, doriki) {
}

int Fukurou::attack(Character* target, BattleContext& context) {
    int dmg = this->atk;
    int actualDmg = dmg - target->getDef();
    if (actualDmg < 0) actualDmg = 0;
    int hpBefore = target->getHP();
    target->receiveDamage(dmg);

    return actualDmg;
}

int Fukurou::specialSkill(Character* target, BattleContext& context) {
    if (this->energy < 14) {
        return 0;
    }

    this->energy -= 14;
    int dmg = ceil(this->atk * 1.3);
    int hpBefore = target->getHP();
    
    if (target->getIsLowestHP()) {
        dmg += 20;
    }
    
    int actualDmg = dmg - target->getDef();
    if (actualDmg < 0) actualDmg = 0;
    

    target->receiveDamage(dmg);

    if (hpBefore > 0 && target->getHP() <= 0 && target->isStrawHat()) {
        context.morale -= 6;
    }
    
    context.morale = (context.morale < 0)? 0 : (context.morale > 100)? 100 : context.morale;
    return actualDmg;
}

bool Fukurou::canUseSkill() const {
    return (this->energy >= 14);
}

void Fukurou::endTurn(BattleContext& context) {
}

/*
 * Building
 */
// Constructor for building
Building::Building(string name, int hp) {
    this->name = name;
    this->hp = (hp > 0)? hp : 0; // Make sure hp is not negative
    this->maxHP = hp;
    this->destroyed = (hp <= 0); // Set destroyed if hp <= 0
}

Building::~Building() {
    // TODO: implement if needed
}

// Same logic with the character, but without minus def
void Building::receiveDamage(int damage) {
    this->hp -= damage;

    if (this->hp <= 0) {
        this->hp = 0;
        this->destroyed = true;
    }
}

bool Building::isDestroyed() const {
    // Virtual method, override later
    return destroyed;
}

void Building::onDestroyed(BattleContext& context) {
    // Virtual method, override later
    return ;
}

// Adding getter for buildings
string Building::getName() const {
    return name;
}

int Building::getHP() const {
    return hp;
}

int Building::getMaxHP() const {
    return maxHP;
}

// Return info of the building
string Building::str () const {
    stringstream ss;
    ss << "Building[";
    ss << "name=" << this->name <<", ";
    ss << "hp=" << this->hp << ", ";
    ss << "maxHP=" << this->maxHP << ", ";
    ss << "destroyed=" << boolalpha << this->destroyed << "]";
    return ss.str();
}

/*
 * MainGate
 */
MainGate::MainGate(string name, int hp) : Building(name, hp) {}

void MainGate::applyEffect(BattleContext& context) {
    if (context.mainGateDestroyed) return;
}

void MainGate::onDestroyed(BattleContext& context) {
    context.mainGateDestroyed = true;
    context.increaseRescue = true; 
    context.rescueProgress += 20;
    context.morale += 5;

    context.morale = (context.morale < 0)? 0 : (context.morale > 100)? 100 : context.morale;
    context.rescueProgress = (context.rescueProgress < 0)? 0 : (context.rescueProgress > 100)? 100 : context.rescueProgress;
}

/*
 * Courthouse
 */
Courthouse::Courthouse(string name, int hp) : Building(name, hp) {}

void Courthouse::applyEffect(BattleContext& context) {
    if (this->destroyed) return;
    context.alarmLevel += 5;
    context.alarmLevel = (context.alarmLevel < 0)? 0 : (context.alarmLevel > 100)? 100 : context.alarmLevel;
}

void Courthouse::onDestroyed(BattleContext& context) {
    context.alarmLevel -= 20;
    context.alarmLevel = (context.alarmLevel < 0)? 0 : (context.alarmLevel > 100)? 100 : context.alarmLevel;
}

/*
 * TowerOfJustice
 */
TowerOfJustice::TowerOfJustice(string name, int hp) : Building(name, hp) {}

void TowerOfJustice::applyEffect(BattleContext& context) {
    if (context.mainGateDestroyed == true && !context.robinRescued && context.increaseRescue) {
        context.rescueProgress += 5;
    }

    context.rescueProgress = (context.rescueProgress < 0)? 0 : (context.rescueProgress > 100)? 100 : context.rescueProgress;
    
    if (context.rescueProgress >= 100 && !context.robinRescued) {
        context.robinRescued = true;
        context.morale += 10;
    }
    
    context.morale = (context.morale < 0)? 0 : (context.morale > 100)? 100 : context.morale;
}

/*
 * BridgeOfHesitation
 */
BridgeOfHesitation::BridgeOfHesitation(string name, int hp) : Building(name, hp) {}

void BridgeOfHesitation::applyEffect(BattleContext& context) {
    if (context.robinRescued == true) {
        context.bridgeOpened = true;
        context.escapeProgress += 5;
    }
    context.escapeProgress = (context.escapeProgress < 0)? 0 : (context.escapeProgress > 100)? 100 : context.escapeProgress;

    if (context.escapeProgress >= 100) {
        context.resultCode = "STRAW_HAT_WIN";
        return;
    }
}

/*
 * BusterCallShip
 */
BusterCallShip::BusterCallShip(string name, int hp) : Building(name, hp) {}

void BusterCallShip::applyEffect(BattleContext& context) {
    context.busterCallTimer--;
    context.busterCallTimer = (context.busterCallTimer < 0)? 0 : context.busterCallTimer;
    if (context.busterCallTimer == 0) {
        context.resultCode = "BUSTER_CALL";
    }
}

void BusterCallShip::onDestroyed(BattleContext& context) {
    context.busterCallTimer += 3;
}

/*
 * EniesLobbyBattle
 */
EniesLobbyBattle::EniesLobbyBattle(const string& filename) {
    strawHatCount = 0;
    cp9Count = 0;
    buildingCount = 0;
    strawHats = new Character*[7];
    cp9Agents = new Character*[7];
    buildings = new Building*[5];
    turnOrder = nullptr;
    loadFromFile(filename);
}

EniesLobbyBattle::~EniesLobbyBattle() {
    
    for (int i = 0; i < strawHatCount; i++) {
        delete strawHats[i];
    }
    
    for (int i = 0; i < cp9Count; i++) { 
        delete cp9Agents[i];
    }

    for (int i = 0; i < buildingCount; i++) {
        delete buildings[i];
    }

    TurnNode* current = turnOrder;
    while (current != nullptr) {
        TurnNode* nextNode = current->next; 
        delete current;                     
        current = nextNode;                 
    }
    turnOrder = nullptr;

    delete[] strawHats;
    delete[] cp9Agents;
    delete[] buildings;
}

void EniesLobbyBattle::loadFromFile(const string& filename) {
    
    ifstream inputFile(filename);
    string line;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string object;
        ss >> object;
        if (object == "CONTEXT") {
            int morale, alarmLevel, rescueProgress, escapeProgress, busterCallTimer, maxTurns;
            ss >> morale >> alarmLevel >> rescueProgress >> escapeProgress >> busterCallTimer >> maxTurns;
            context.morale = morale;
            context.alarmLevel = alarmLevel;
            context.rescueProgress = rescueProgress;
            context.escapeProgress = escapeProgress;
            context.busterCallTimer = busterCallTimer;
            this->maxTurns = maxTurns;
        }

        else if (object == "STRAW_HAT") {
            string name;
            int hp, atk, def, speed, energy;
            long long bounty;
            ss >> name >> hp >> atk >> def >> speed >> energy >> bounty;
            if (name == "Luffy") {
                Character*  luffy = new Luffy(name, hp, atk, def, speed, energy, bounty);
                addStrawHat(luffy);
            }

            else if (name == "Zoro") {
                Character* zoro = new Zoro(name, hp, atk, def, speed, energy, bounty);
                addStrawHat(zoro);
            }

            else if (name == "Sanji") {
                Character* sanji = new Sanji(name, hp, atk, def, speed, energy, bounty);
                addStrawHat(sanji);
            }

            else if (name == "Nami") {
                Character* nami = new Nami(name, hp, atk, def, speed, energy, bounty);
                addStrawHat(nami);
            }

            else if (name == "Chopper") {
                Character* chopper = new Chopper(name, hp, atk, def, speed, energy, bounty);
                addStrawHat(chopper);
            }

            else if (name == "Usopp") {
                Character* usopp = new Usopp(name, hp, atk, def, speed, energy, bounty);
                addStrawHat(usopp);
            }

            else if (name == "Franky") {
                Character* franky = new Franky(name, hp, atk, def, speed, energy, bounty);
                addStrawHat(franky);
            }
        }

        else if (object == "CP9") {
            string name;
            int hp, atk, def, speed, energy, doriki;
            ss >> name >> hp >> atk >> def >> speed >> energy >> doriki;
            if (name == "Lucci") {
                Character* lucci = new Lucci(name, hp, atk, def, speed, energy, doriki);
                addCP9Agent(lucci);
            }

            else if (name == "Kaku") {
                Character* kaku = new Kaku(name, hp, atk, def, speed, energy, doriki);
                addCP9Agent(kaku);
            }

            else if (name == "Jabra") {
                Character* jabra = new Jabra(name, hp, atk, def, speed, energy, doriki);
                addCP9Agent(jabra);
            }

            else if (name == "Blueno") {
                Character* blueno = new Blueno(name, hp, atk, def, speed, energy, doriki);
                addCP9Agent(blueno);
            }

            else if (name == "Kalifa") {
                Character* kalifa = new Kalifa(name, hp, atk, def, speed, energy, doriki);
                addCP9Agent(kalifa);
            }

            else if (name == "Kumadori") {
                Character* kumadori = new Kumadori(name, hp, atk, def, speed, energy, doriki);
                addCP9Agent(kumadori);
            }

            else if (name == "Fukurou") {
                Character* fukurou = new Fukurou(name, hp, atk, def, speed, energy, doriki);
                addCP9Agent(fukurou);
            }
        }

        else if (object == "BUILDING") {
            string name;
            int hp;
            ss >> name >> hp;
            if (name == "MainGate") {
                Building* maingate = new MainGate(name, hp);
                addBuilding(maingate);
            }

            else if (name == "Courthouse") {
                Building* courthouse = new Courthouse(name, hp);
                addBuilding(courthouse);
            }

            else if (name == "TowerOfJustice") {
                Building* towerofjustice = new TowerOfJustice(name, hp);
                addBuilding(towerofjustice);
            }

            else if (name == "BridgeOfHesitation") {
                Building* bridgeofhesitation = new BridgeOfHesitation(name, hp);
                addBuilding(bridgeofhesitation);
            }

            else if (name == "BusterCallShip") {
                Building* bustercallship = new BusterCallShip(name, hp);
                addBuilding(bustercallship);
            }
        }
    }

    buildTurnOrder();
}

void EniesLobbyBattle::addStrawHat(Character* character) {
    if (strawHatCount < 7) {
        strawHats[strawHatCount] = character;
        strawHatCount++; 
    }
}

void EniesLobbyBattle::addCP9Agent(Character* character) {
    if (cp9Count < 7) {
        cp9Agents[cp9Count] = character;
        cp9Count++; 
    }
}

void EniesLobbyBattle::addBuilding(Building* building) {
    if (buildingCount < 5) {
        buildings[buildingCount] = building;
        buildingCount++; 
    }
}

void EniesLobbyBattle::buildTurnOrder() {
    turnOrder = nullptr;
    TurnNode* tail = nullptr;

    for (int i = 0; i < strawHatCount; i++) {
        TurnNode* newNode = new TurnNode();
        newNode->data = strawHats[i];

        if (turnOrder == nullptr) {
            turnOrder = newNode;
            tail = newNode;
        }

        else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    for (int i = 0; i < cp9Count; i++) {
        TurnNode* newNode = new TurnNode();
        newNode->data = cp9Agents[i]; 
        newNode->next = nullptr;

        if (turnOrder == nullptr) {
            turnOrder = newNode;
            tail = newNode;
        } 
        
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }
}

void EniesLobbyBattle::runBattle() {
    TurnNode* cur = turnOrder;
    TurnNode* tail = turnOrder;
    int idxGate = -1;
    int idxCourt = -1;
    int idxBuster = -1;
    int idxBridge = -1;

    while (tail->next != nullptr) {
        tail = tail->next;
    }

    for (int i = 0; i < buildingCount; i++) {
        if (buildings[i]->getName() == "MainGate") idxGate = i;
        else if (buildings[i]->getName() == "Courthouse") idxCourt = i;
        else if (buildings[i]->getName() == "BusterCallShip") idxBuster = i;
        else if (buildings[i]->getName() == "BridgeOfHesitation") idxBridge = i;
    }

    while (context.battleEnded == false && context.turnCount < maxTurns) {
        if (cur == nullptr) {
            break;
        }

        Character* curChar = cur->data;
        if (curChar->isAlive()) {
            this->processTurn(curChar);
        }


        turnOrder = turnOrder->next;
        tail->next = cur;
        cur->next = nullptr;
        tail = tail->next;
        cur = turnOrder;

        this->processBuildings();
        context.nextTurn();
        this->checkEndCondition();
    }

    if (context.turnCount >= maxTurns && context.battleEnded == false) {
        context.battleEnded = true;
        context.resultCode = "TIME_OUT";
    }
}

void EniesLobbyBattle::processTurn(Character* character) {
    int lowestHP = 999999;
    int lowestIdx = -1;
    int firstStrawHatAlive = -1;
    int firstAlive = -1;

    for (int i = 0; i < cp9Count; i++) {
        if (cp9Agents[i]->isAlive()) {
            firstAlive = i;
            break;
        }
    }
    
    for (int i = 0; i < strawHatCount; i++) {
        if (strawHats[i]->isAlive()) {
            firstStrawHatAlive = i;
            break;
        }
    }
    for (int i = 0; i < strawHatCount; i++) {
        if (strawHats[i]->isAlive() && strawHats[i]->getHP() < lowestHP) {
            lowestHP = strawHats[i]->getHP();
            lowestIdx = i;
        }
    }

    int idxGate = -1;
    int idxCourt = -1;
    int idxBuster = -1;
    int idxBridge = -1;

    for (int i = 0; i < buildingCount; i++) {
        if (buildings[i]->getName() == "MainGate") idxGate = i;
        else if (buildings[i]->getName() == "Courthouse") idxCourt = i;
        else if (buildings[i]->getName() == "BusterCallShip") idxBuster = i;
        else if (buildings[i]->getName() == "BridgeOfHesitation") idxBridge = i;
    }

    bool canUseSkill = character->canUseSkill();

    string actBeforeStr = character->str() + " | alive=" + (character->isAlive() ? "true" : "false");

    if (character->isStrawHat()) {
        if (character->getName() == "Chopper" && canUseSkill) {
            character->specialSkill(strawHats[lowestIdx], context);
        }

        else if (idxGate != -1 && !buildings[idxGate]->isDestroyed()) {
            int hpBefore = buildings[idxGate]->getHP();
            if (canUseSkill) {
                character->specialSkill(buildings[idxGate], context);
            }
            
            else {
                character->attack(buildings[idxGate], context);
            }
            
            if (hpBefore > 0 && buildings[idxGate]->isDestroyed()) {
                buildings[idxGate]->onDestroyed(context);
            }
        }

        else if (context.mainGateDestroyed && context.alarmLevel >= 50 && idxCourt != -1 && !buildings[idxCourt]->isDestroyed()) {
            int hpBefore = buildings[idxCourt]->getHP();

            if (canUseSkill) {
                character->specialSkill(buildings[idxCourt], context);
            }

            else {
                character->attack(buildings[idxCourt], context);
            }

            if (hpBefore > 0 && buildings[idxCourt]->isDestroyed()) {
                context.courtDestroyed = true;
                buildings[idxCourt]->onDestroyed(context);
            }
        }

        else if (context.busterCallTimer <= 5 && idxBuster != -1 && !buildings[idxBuster]->isDestroyed()) {
            int hpBefore = buildings[idxBuster]->getHP();

            if (canUseSkill) {
                character->specialSkill(buildings[idxBuster], context);
            }

            else {
                character->attack(buildings[idxBuster], context);
            }

            if (hpBefore > 0 && buildings[idxBuster]->isDestroyed()) {
                buildings[idxBuster]->onDestroyed(context);
            }
        }

        else if (context.robinRescued == false) {
            if (canUseSkill) {
                character->specialSkill(cp9Agents[firstAlive], context);
            }
            else {
                character->attack(cp9Agents[firstAlive], context);
            }
        }

        else if (context.robinRescued) {
            if (buildings[idxBridge]->isDestroyed() || idxBridge == -1) {      
                
                if (canUseSkill) {
                    character->specialSkill(cp9Agents[firstAlive], context);
                }
                
                else {
                    character->attack(cp9Agents[firstAlive], context);
                }
            }

            else {
                int hpBefore = buildings[idxBridge]->getHP();
                if (canUseSkill) {
                    character->specialSkill(buildings[idxBridge], context);
                }
                
                else {
                    character->attack(buildings[idxBridge], context);
                }

                if (hpBefore > 0 && buildings[idxBridge]->isDestroyed()) {
                    buildings[idxBridge]->onDestroyed(context);
                }
            }
        }
    }

    else if (character->isCP9() && firstStrawHatAlive != -1) {
        if (character->getName() == "Fukurou" && firstStrawHatAlive == lowestIdx) {
            strawHats[firstStrawHatAlive]->setIsLowestHP(true);
            if (canUseSkill) {
                character->specialSkill(strawHats[firstStrawHatAlive], context);
            }

            else {
                character->attack(strawHats[firstStrawHatAlive], context);
            } 
            strawHats[firstStrawHatAlive]->setIsLowestHP(false);
        }

        else {
            if (canUseSkill) {
                character->specialSkill(strawHats[firstStrawHatAlive], context);
            }
            else {
                character->attack(strawHats[firstStrawHatAlive], context);
            }
        }
    }

    character->endTurn(context);
}

void EniesLobbyBattle::processBuildings() {
    for (int i = 0; i < buildingCount; i++) {
        if (!buildings[i]->isDestroyed()) {
            buildings[i]->applyEffect(context);
        }
    } 
}

void EniesLobbyBattle::checkEndCondition() {
    if (context.battleEnded) {
        return;
    }

    bool allStrawDead = true;
    for (int i = 0; i < strawHatCount; i++) {
        if (strawHats[i]->isAlive()) {
            allStrawDead = false;
            break;
        }
    }

    bool allCp9Dead = true;
    for (int i = 0; i < cp9Count; i++) {
        if (cp9Agents[i]->isAlive()) {
            allCp9Dead = false;
            break;
        }
    }

    if (context.robinRescued == true && context.escapeProgress >= 100) {
        context.battleEnded = true;
        context.resultCode = "STRAW_HAT_WIN";
    }

    else if (context.busterCallTimer <= 0) {
        context.battleEnded = true;
        context.resultCode = "BUSTER_CALL";
    }

    else if (allStrawDead) {
        context.battleEnded = true;
        context.resultCode = "CP9_WIN";
    }

    else if (allCp9Dead) {
        context.battleEnded = true;
        context.resultCode = "STRAW_HAT_WIN_BY_DEFEAT_CP9";
    }

    else if (context.turnCount >= maxTurns) {
        context.battleEnded = true;
        context.resultCode = "TIME_OUT";
    }
}

string EniesLobbyBattle::getResult() const {
    stringstream ss;
    ss << context.resultCode << " ";
    ss << context.turnCount << " ";
    ss << context.morale << " ";
    ss << context.alarmLevel << " ";
    ss << context.rescueProgress << " ";
    ss << context.escapeProgress << " ";
    ss << context.busterCallTimer;
    return ss.str();
}
