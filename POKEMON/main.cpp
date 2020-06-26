//
//  main.cpp
//  Lab 09: Pokémon
//


#include <iostream>
#include <sstream>
#include <fstream>
#include "Set.h"
#include "HashMap.h"
using namespace std;

int main(int argc, const char * argv[]) {
    //Open input and output files
    if (argc < 3) {
        cout << "Please provide name of input and output files";
    }
    cout << "Input file: " << argv[1] << endl;
    ifstream inFile;
    inFile.open(argv[1]);
    if (inFile.is_open()) {
        cout << "Input file was opened." << endl;
    }
    else {
        cout << "Input file was NOT opened." << endl;
        return 1;
    }
    cout << "Output file: " << argv[2] << endl;
    ofstream outFile;
    outFile.open(argv[2]);
    if (outFile.is_open()) {
        cout << "Output file was opened." << endl;
    }
    else {
        cout << "Input file was NOT opened." << endl;
        return 999;
    }
    
    HashMap<string, string> pokemonMap;
    HashMap<string, string> moveMap;
    HashMap<string, Set<string>> efficiencyMap;
    HashMap<string, Set<string>> inefficiencyMap;
    
    //Declare variables
    ostringstream oSS;
    //istringstream iSS;
    string command = "";
    string stringItem = "";
    string line = "";
    string data = "";
    string attackType = "";
    string pokemonName = "";
    string pMove = "";
    string moveType = "";
    string attack = "";
    string pType = "";
    string battlePokemon1 = "";
    string battlePokemon2 = "";
    string battleMove1 = "";
    string battleMove2 = "";
    
    while (inFile >> command) {
        Set<string> testSetOfStrings;
        if (command == "Set:") {
            getline(inFile, line);
            istringstream iSS(line);
            oSS << "Set: " << line << endl;
            oSS << "[";
            while (iSS >> data) {
                testSetOfStrings.insert(data);
            }
            oSS << testSetOfStrings << "]" << endl;
        }
        else if (command == "Pokemon:") {
            inFile >> pokemonName;
            inFile >> attackType;
            pokemonMap[pokemonName] = attackType;
            oSS << "Pokemon: " << pokemonName << " " << attackType << endl;
        }
        else if (command == "Move:") {
            inFile >> pMove;
            inFile >> moveType;
            moveMap[pMove] = moveType;
            oSS << "Move: " << pMove << " " << moveType << endl;
        }
        else if (command == "Pokemon") {
            oSS << endl;
            oSS << "Pokemon: " << pokemonMap.size() << "/" << pokemonMap.max_size() << endl;
            oSS << pokemonMap.toString();
        }
        else if (command == "Moves") {
            oSS << endl;
            oSS << "Moves: " << moveMap.size() << "/" << moveMap.max_size() << endl;
            oSS << moveMap.toString();
        }
        else if (command == "Effective:") {
            inFile >> attack;
            oSS << "Effective: " << attack << " ";
            getline(inFile, line);
            istringstream iSS(line);
            while (iSS >> pType) {
                efficiencyMap[attack].insert(pType);
                oSS << pType << " ";
            }
            oSS << endl;
        }
        else if (command == "Ineffective:") {
            inFile >> attack;
            oSS << "Ineffective: " << attack << " ";
            getline(inFile, line);
            istringstream iSS(line);
            while (iSS >> pType) {
                inefficiencyMap[attack].insert(pType);
                oSS << pType << " ";
            }
            oSS << endl;
        }
        else if (command == "Effectivities") {
            oSS << endl;
            oSS << "Effectivities: " << efficiencyMap.size() << "/" << efficiencyMap.max_size() << endl;
            oSS << efficiencyMap.toString();
        }
        else if (command == "Ineffectivities") {
            oSS << endl;
            oSS << "Ineffectivities: " << inefficiencyMap.size() << "/" << inefficiencyMap.max_size() << endl;
            oSS << inefficiencyMap.toString();
        }
        else if (command == "Battle:") {
            inFile >> battlePokemon1;
            inFile >> battleMove1;
            inFile >> battlePokemon2;
            inFile >> battleMove2;
            long long damage1To2 = 0;
            long long damage2To1 = 0;
            oSS << endl;
            //Report battle specifics
            oSS << "Battle: " << battlePokemon1 << " " << battleMove1 << " " << battlePokemon2 << " " << battleMove2 << endl;
            oSS << battlePokemon1 << " (" << battleMove1 << ") vs " << battlePokemon2 << " (" << battleMove2 << ")" << endl;
            oSS << battlePokemon1 << " is a " << pokemonMap[battlePokemon1] << " type Pokemon." << endl;
            oSS << battlePokemon2 << " is a " << pokemonMap[battlePokemon2] << " type Pokemon." << endl;
            oSS << battleMove1 << " is a " << moveMap[battleMove1] << " type move." << endl;
            oSS << battleMove2 << " is a " << moveMap[battleMove2] << " type move." << endl;
            oSS << battleMove1 << " is super effective against [" << efficiencyMap[moveMap[battleMove1]] << "] type Pokemon." << endl;
            oSS << battleMove1 << " is ineffective against [" << inefficiencyMap[moveMap[battleMove1]] << "] type Pokemon." << endl;
            
            if (efficiencyMap[moveMap[battleMove1]].count(pokemonMap[battlePokemon2]) == 1) {
                oSS << battlePokemon1 << "'s " << battleMove1 << " is super effective against " << battlePokemon2 << endl;
            }
            else if (inefficiencyMap[moveMap[battleMove1]].count(pokemonMap[battlePokemon2]) == 1) {
                oSS << battlePokemon1 << "'s " << battleMove1 << " is ineffective against " << battlePokemon2 << endl;
            }
            else {
                oSS << battlePokemon1 << "'s " << battleMove1 << " is effective against " << battlePokemon2 << endl;
            }
            oSS << battleMove2 << " is super effective against [" << efficiencyMap[moveMap[battleMove2]] << "] type Pokemon." << endl;
            oSS << battleMove2 << " is ineffective against [" << inefficiencyMap[moveMap[battleMove2]] << "] type Pokemon." << endl;
            
            if (efficiencyMap[moveMap[battleMove2]].count(pokemonMap[battlePokemon1]) == 1) {
                oSS << battlePokemon2 << "'s " << battleMove2 << " is super effective against " << battlePokemon1 << endl;
            }
            else if (inefficiencyMap[moveMap[battleMove2]].count(pokemonMap[battlePokemon1]) == 1) {
                oSS << battlePokemon2 << "'s " << battleMove2 << " is ineffective against " << battlePokemon1 << endl;
            }
            else {
                oSS << battlePokemon2 << "'s " << battleMove2 << " is effective against " << battlePokemon1 << endl;
            }
            //Calculate damage
            damage1To2 = efficiencyMap[moveMap[battleMove1]].count(pokemonMap[battlePokemon2]) - inefficiencyMap[moveMap[battleMove1]].count(pokemonMap[battlePokemon2]);
            damage2To1 = efficiencyMap[moveMap[battleMove2]].count(pokemonMap[battlePokemon1]) - inefficiencyMap[moveMap[battleMove2]].count(pokemonMap[battlePokemon1]);
            //Report winner
            if ((damage1To2 - damage2To1) > 0) {
                oSS << "In the battle between " << battlePokemon1 << " and " << battlePokemon2 << ", " << battlePokemon1 << " wins!" << endl << endl;
            }
            else if ((damage1To2 - damage2To1) < 0) {
                oSS << "In the battle between " << battlePokemon1 << " and " << battlePokemon2 << ", " << battlePokemon2 << " wins!" << endl << endl;
            }
            else {
                oSS << "The battle between " << battlePokemon1 << " and " << battlePokemon2 << " is a tie." << endl;
            }
        }
        else {
            break;
        }
    }
    
    outFile << oSS.str();
    return 0;
}
