#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <bits/stdc++.h>

using namespace std;

int main(){

    cout << "What tournament year would you like to check?" << endl;
    int year; 
    cin >> year;
    string yearString = to_string(year);
    string runsFile = "testData/" + yearString + "runs.txt";
    string resultFile = "testData/" + yearString + "result.txt";
    ifstream brackets;
    brackets.open(runsFile, ios::in);
    ifstream actual;
    actual.open(resultFile, ios::in);
    vector<string> realBracket;
    vector<string> randBracket;
    string line, word, temp;
    int numBracketsRead = 0, prevMaxCorrect = 0, prevMaxStreak = 0, correctPicks = 0, picksFromStart = 0, espnScore = 0, bestBracket, bestRun;
    bool perfect = true;
    getline(actual, temp, '\n');

    while(getline(actual, line, '\n')){
        stringstream s(line);
        while (getline(s, word, ',')){
            realBracket.push_back(word);
        }
    }

    string a;
    while (getline(brackets, a, '\n')){
        randBracket.clear();
        int linesRead = 0;
        while(linesRead < 15 && getline(brackets, line, '\n')){
            stringstream s(line);
            while (getline(s, word, ',')){
                randBracket.push_back(word);
            }
            linesRead++;
        }

        perfect = true, correctPicks = 0, picksFromStart = 0;
        for (int i = 0; i < realBracket.size(); i++){
            if (realBracket[i] == randBracket[i] && perfect == true){
                correctPicks++;
                picksFromStart++;
            }

            else if (realBracket[i] == randBracket[i] && perfect == false){
                correctPicks++;
            }

            else {perfect = false;}
        } 

        if (numBracketsRead == 0){
            prevMaxCorrect = correctPicks;
            prevMaxStreak = picksFromStart;
        }

        if (correctPicks > prevMaxCorrect){
            prevMaxCorrect = correctPicks;
            bestBracket = numBracketsRead+1;
        }

        if (picksFromStart > prevMaxStreak){
            prevMaxStreak = picksFromStart;
            bestRun = numBracketsRead+1;
        }
        numBracketsRead++;
    }

    cout << "Max correct picks: " << prevMaxCorrect << endl;
    cout << "Max picks from start: " << prevMaxStreak << endl;
    cout << "Max Percent correct: " << ((float)prevMaxCorrect/63)*100 << endl;
    cout << "Best Bracket: " << bestBracket << ", at line " << ((bestBracket-1)*16)+2 << endl;
    cout << "Best Streak: " << bestRun << ", at line " << ((bestRun-1)*16)+2 << endl;

    return 0;
}