#include <iostream>
#include "time.h"
#include <fstream>
#include <cstdlib>
#include <cmath>

using namespace std;

int matchup(int team1Seed, int team2Seed){
    int dif,odds,num;
    int alg = rand() % 2 + 1;
    if (team1Seed > team2Seed){

        dif = team1Seed - team2Seed;

        if (alg == 1) {
            odds = (-.13 * pow(dif,2)) + (5.25 * dif) + 50; //literally just created a parabola in desmos that somewhat follows the win percentages based on seed difference and copied the expression
        }

        else {
            odds = 50 + (0.22 * pow(dif, 2));
        }

        num = rand() % 100 + 1;
        if (num < odds){
            return 2;
        } else {return 1;}
    }
    else{
        dif = team2Seed - team1Seed;

        if (alg == 1) {
            odds = (-.13 * pow(dif,2)) + (5.25 * dif) + 50;
        }
        
        else {
            odds = 50 + (0.22 * pow(dif, 2));
        }

        num = rand() % 100 + 1;
        if (num < odds){
            return 1;
        } else {return 2;}
    }
}

int main(){
    struct team{
        string name;
        int seed;
        string region;
        bool eliminated;
    };

    srand(time(0));

    int matchupOdds[16][16]; 
    matchupOdds[1][16] = 99;
    matchupOdds[2][15] = 93;
    matchupOdds[3][14] = 85; 
    matchupOdds[4][13] = 79; 
    matchupOdds[5][12] = 64;
    matchupOdds[6][11] = 61;
    matchupOdds[7][10] = 61;
    matchupOdds[8][9] = 49;
    matchupOdds[1][8] = 79;
    matchupOdds[1][9] = 91;
    matchupOdds[8][16] = 88;
    matchupOdds[9][16] = 87;
    matchupOdds[2][7] = 69;
    matchupOdds[2][10] = 59;
    matchupOdds[7][15] = 81;
    matchupOdds[10][15] = 77;
    matchupOdds[3][6] = 59;
    matchupOdds[3][11] = 66;


    team tourneyTeams[64];
    team secondRound[32];
    team sweetSixteen[16];
    team eliteEight[8];
    team finalFour[4];
    team championship[2];
    cout << "Enter the tourney year you want to generate a bracket from: " << endl;
    int year;
    cin >> year;
    string yearString = to_string(year);
    string fileName = "tourneyTeams" + yearString + ".txt";
    string outFileName = "testData/" + yearString + "runs.txt";
    const char* removeFile = outFileName.c_str();
    remove(removeFile);
    ofstream outputFile;
    outputFile.open(outFileName, ios::out | ios::app);
    outputFile << yearString;
    outputFile << "\n";


    for (int k = 0; k < 10000; k++){
        ifstream teamFile(fileName);
        //ofstream outputFile;
        outputFile.open(outFileName, ios::out | ios::app);

        int i, j;
        string region, name;
        for (i = 0; i < 4; i++){
            getline(teamFile, region);
            for (j = 0; j < 16; j++){
                getline(teamFile, name);
                tourneyTeams[j+(16*i)].region = region;
                tourneyTeams[j+(16*i)].seed = j+1;
                tourneyTeams[j+(16*i)].name = name;
                tourneyTeams[j+(16*i)].eliminated = false;
            }
        }

        // first round 
        for (i = 0; i < 4; i++){
            for (j = 0; j < 8; j++){
                int num = matchup(tourneyTeams[j+(i*16)].seed, tourneyTeams[((i+1)*16)-(j+1)].seed);
                if (num == 1){
                    outputFile << tourneyTeams[j+(i*16)].seed << tourneyTeams[j+(i*16)].region << ",";
                    //cout << tourneyTeams[j+(i*16)].seed << ". " << tourneyTeams[j+(i*16)].name << " defeats " << tourneyTeams[((i+1)*16)-(j+1)].seed << ". " << tourneyTeams[((i+1)*16)-(j+1)].name << endl;
                   // cout << tourneyTeams[j+(i*16)].seed << ". " << tourneyTeams[j+(i*16)].name << " defeats " << tourneyTeams[((i+1)*16)-(j+1)].seed << ". " << tourneyTeams[((i+1)*16)-(j+1)].name << endl;
                    secondRound[j+(i*8)].name = tourneyTeams[j+(i*16)].name;
                    secondRound[j+(i*8)].seed = tourneyTeams[j+(i*16)].seed;
                    secondRound[j+(i*8)].region = tourneyTeams[j+(i*16)].region;
                }
                else { 
                    outputFile << tourneyTeams[((i+1)*16)-(j+1)].seed << tourneyTeams[((i+1)*16)-(j+1)].region << ",";
                    //cout << tourneyTeams[((i+1)*16)-(j+1)].seed << ". " << tourneyTeams[((i+1)*16)-(j+1)].name << " defeats " << tourneyTeams[j+(i*16)].seed << ". " << tourneyTeams[j+(i*16)].name << endl;
                    secondRound[j+(i*8)].name = tourneyTeams[((i+1)*16)-(j+1)].name;
                    secondRound[j+(i*8)].seed = tourneyTeams[((i+1)*16)-(j+1)].seed;
                    secondRound[j+(i*8)].region = tourneyTeams[((i+1)*16)-(j+1)].region;
                } 
            }
            outputFile << "\n";
        }

        for (i = 0; i < 4; i++){
            for (j = 0; j < 4; j++){
                int num = matchup(secondRound[j+(i*8)].seed, secondRound[((i+1)*8)-(j+1)].seed);//rand() % 2 + 1;
                if (num == 1){
                    outputFile << secondRound[j+(i*8)].seed << secondRound[j+(i*8)].region << ",";
                    //outputFile << secondRound[j+(i*8)].seed << ". " << secondRound[j+(i*8)].name << " defeats " << secondRound[((i+1)*8)-(j+1)].seed << ". " << secondRound[((i+1)*8)-(j+1)].name << endl;
                    sweetSixteen[j+(i*4)].name = secondRound[j+(i*8)].name;
                    sweetSixteen[j+(i*4)].seed = secondRound[j+(i*8)].seed;
                    sweetSixteen[j+(i*4)].region = secondRound[j+(i*8)].region;
                }
                else {
                    outputFile << secondRound[((i+1)*8)-(j+1)].seed << secondRound[((i+1)*8)-(j+1)].region << ","; 
                    //outputFile << secondRound[((i+1)*8)-(j+1)].seed << ". " << secondRound[((i+1)*8)-(j+1)].name << " defeats " << secondRound[j+(i*8)].seed << ". " << secondRound[j+(i*8)].name << endl;
                    sweetSixteen[j+(i*4)].name = secondRound[((i+1)*8)-(j+1)].name;
                    sweetSixteen[j+(i*4)].seed = secondRound[((i+1)*8)-(j+1)].seed;
                    sweetSixteen[j+(i*4)].region = secondRound[((i+1)*8)-(j+1)].region;
                }
            }
            outputFile << "\n";
        }

        //Sweet Sixteen
        for (i = 0; i < 4; i++){
            for (j = 0; j < 2; j++){
                int num = matchup(sweetSixteen[j+(i*4)].seed, sweetSixteen[((i+1)*4)-(j+1)].seed);//rand() % 2 + 1;
                if (num == 1){
                    outputFile << sweetSixteen[j+(i*4)].seed << sweetSixteen[j+(i*4)].region << ",";
                    //outputFile << sweetSixteen[j+(i*4)].seed << ". " << sweetSixteen[j+(i*4)].name << " defeats " << sweetSixteen[((i+1)*4)-(j+1)].seed << ". " << sweetSixteen[((i+1)*4)-(j+1)].name << endl;
                    eliteEight[j+(i*2)].name = sweetSixteen[j+(i*4)].name;
                    eliteEight[j+(i*2)].seed = sweetSixteen[j+(i*4)].seed;
                    eliteEight[j+(i*2)].region = sweetSixteen[j+(i*4)].region;
                }
                else {
                    outputFile << sweetSixteen[((i+1)*4)-(j+1)].seed << sweetSixteen[((i+1)*4)-(j+1)].region << ",";
                    //outputFile << sweetSixteen[((i+1)*4)-(j+1)].seed << ". " << sweetSixteen[((i+1)*4)-(j+1)].name << " defeats " << sweetSixteen[j+(i*4)].seed << ". " << sweetSixteen[j+(i*4)].name << endl;
                    eliteEight[j+(i*2)].name = sweetSixteen[((i+1)*4)-(j+1)].name;
                    eliteEight[j+(i*2)].seed = sweetSixteen[((i+1)*4)-(j+1)].seed;
                    eliteEight[j+(i*2)].region = sweetSixteen[((i+1)*4)-(j+1)].region;
                }
            }
            outputFile << "\n";
        }

        //Elite Eight
        for (i = 0; i < 4; i++){
            int num = matchup(eliteEight[i*2].seed, eliteEight[(i*2)+1].seed);//rand() % 2 + 1;
            if (num == 1){
                outputFile << eliteEight[i*2].seed << eliteEight[i*2].region << ",";
                //outputFile << eliteEight[i*2].seed << ". " << eliteEight[i*2].name << " defeats " << eliteEight[(i*2)+1].seed << ". " << eliteEight[(i*2)+1].name << endl;
                finalFour[i].name = eliteEight[i*2].name;
                finalFour[i].seed = eliteEight[i*2].seed;
                finalFour[i].region = eliteEight[i*2].region;
            }
            else{
                outputFile << eliteEight[(i*2)+1].seed << eliteEight[(i*2)+1].region << ",";
                //outputFile << eliteEight[(i*2)+1].seed << ". " << eliteEight[(i*2)+1].name << " defeats " << eliteEight[i*2].seed << ". " << eliteEight[i*2].name << endl;
                finalFour[i].name = eliteEight[(i*2)+1].name;
                finalFour[i].seed = eliteEight[(i*2)+1].seed;
                finalFour[i].region = eliteEight[(i*2)+1].region;
            }
        }

        outputFile << endl;

        //Final Four 
        for (int i = 0; i < 2; i++){
            int num = matchup(finalFour[i*2].seed, finalFour[(i*2)+1].seed);//rand() % 2 + 1;
            if (num == 1){
                outputFile << finalFour[i*2].seed << finalFour[i*2].region << ",";
                //cout << finalFour[i*2].seed << ". " << finalFour[i*2].name << " defeats " << finalFour[(i*2)+1].seed << ". " << finalFour[(i*2)+1].name << endl;
                championship[i].name = finalFour[i*2].name;
                championship[i].seed = finalFour[i*2].seed;
                championship[i].region = finalFour[i*2].region;
            }
            else{
                outputFile << finalFour[(i*2)+1].seed << finalFour[(i*2)+1].region << ",";
                //cout << finalFour[(i*2)+1].seed << ". " << finalFour[(i*2)+1].name << " defeats " << finalFour[i*2].seed << ". " << finalFour[i*2].name << endl;
                championship[i].name = finalFour[(i*2)+1].name;
                championship[i].seed = finalFour[(i*2)+1].seed;
                championship[i].region = finalFour[(i*2)+1].region;
            }
        }
        outputFile << "\n";

        //outputFile << "\nChampionship" << endl;
        //outputFile << championship[0].seed << ". " << championship[0].name << " vs. " << championship[1].seed << ". " << championship[1].name << endl;
        string champName;
        int champSeed;

        int num = matchup(championship[0].seed, championship[1].seed);//rand() % 2 + 1;
        if (num == 1){
            outputFile << championship[0].seed << championship[0].region << "," << endl;
            /*
            outputFile << championship[0].seed << ". " << championship[0].name << " are the champions" << endl;
            outputFile << "\n";
            champName = championship[0].name;
            champSeed = championship[0].seed; */
        }
        else {
            outputFile << championship[1].seed << championship[1].region << "," << endl;
            /*
            outputFile << championship[1].seed << ". " << championship[1].name << " are the champions" << endl;
            outputFile << "\n";
            champName = championship[1].name;
            champSeed = championship[1].seed; */
        }
        outputFile << "\n";

        //outputFile << champName;
        //outputFile << ", ";
        //outputFile << champSeed;
        //outputFile << "\n";
        outputFile.close();
        teamFile.close();
    }

    return 0;
}
