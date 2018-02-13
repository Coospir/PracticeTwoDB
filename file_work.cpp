//
// Created by Eugene Starodubov on 13.02.2018.
//
#include "file_work.h"
#include <iostream>
#include <fstream>

using namespace std;

bool checkFile(const char* file_name) {
    ifstream file;
    file.open(file_name);
    if(!file)
    {return 0;}
    else{file.close();
        return 1;}
}
