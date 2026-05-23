
#include "eniesLobby.h"

using namespace std;

int main(int argc, const char * argv[]) {
    string filename = "sample_input";
    cout << ">>>>>>>> RUNNING <<<<<<<<" << endl;
    cout << "--- INITIALIZE THE BATTLE ---" << endl;
    
    EniesLobbyBattle battle(filename);
    cout << "--- PROCESSING ---" << endl;
    
    battle.runBattle();
    string result = battle.getResult();
    
    cout << "--- FINAL RESULT ---" << endl;
    cout << result << endl;
    
    return 0;
}
