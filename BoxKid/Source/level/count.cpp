#include <iostream>
#include <fstream>

#include <string>
#include <vector>

using namespace std;

int main() {
    vector<int> walls_amount = {};
    vector<int> floors_amount = {};
    vector<int> boxes_amount = {};
    vector<int> goals_amount = {};

    for (int i = 0; i < 30; i++){

    
        int level = i + 1;
        string line = "level";
        string filename = "level" + to_string(level) + ".txt";
        int walls_count = 0;
        int floors_count = 0;
        int boxes_count = 0;
        int goals_count = 0;
        ifstream inputFile(filename);

        while (getline(inputFile, line)) {

            for(int i = 0; i < line.length(); ++i){
                if(line[i] == '1'){
                    walls_count++;
                }
                if(line[i] == '2'){
                    floors_count++;
                }
                if(line[i] == '3'){
                    floors_count++;
                    boxes_count++;
                }
                if(line[i] == '4'){
                    goals_count++;
                }
                if(line[i] == '5'){
                    boxes_count++;
                    goals_count++;
                }           
                if(line[i] == '6'){
                    floors_count++;
                }        
            }
        }
        inputFile.close();

        walls_amount.push_back(walls_count);
        floors_amount.push_back(floors_count);
        boxes_amount.push_back(boxes_count);
        goals_amount.push_back(goals_count);
    }

    printf("{");
    for (int j = 0; j < walls_amount.size(); j++){
        printf("%d,", walls_amount[j]);
    }
    printf("}");
    printf("\n");

    printf("{");
    for (int j = 0; j < floors_amount.size(); j++){
        printf("%d,", floors_amount[j]);
    } 
    printf("}");
    printf("\n");

    printf("{");
    for (int j = 0; j < boxes_amount.size(); j++){
        printf("%d,", boxes_amount[j]);
    }
    printf("}");
    printf("\n");

    printf("{");
    for (int j = 0; j < goals_amount.size(); j++){
        printf("%d,", goals_amount[j]);
    }
    printf("}");

    return 0;
}
