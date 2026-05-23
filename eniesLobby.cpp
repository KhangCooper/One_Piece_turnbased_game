#include "eniesLobby.h"

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
             int speed, int energy, long long bounty) { 
    // TODO: implement
}

int Luffy::attack(Character* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

int Luffy::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

int Luffy::attack(Building* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

int Luffy::specialSkill(Building* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

void Luffy::endTurn(BattleContext& context) {
    // TODO: implement
}

/*
 * Zoro
 */
Zoro::Zoro(string name, int hp, int atk, int def,
           int speed, int energy, long long bounty) {
    // TODO: implement
}

int Zoro::attack(Character* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

int Zoro::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

int Zoro::attack(Building* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

int Zoro::specialSkill(Building* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

void Zoro::endTurn(BattleContext& context) {
    // TODO: implement
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
