#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <limits>
#include <ctime>
#include <locale>
#include "file_work.h"
#include "date.h"

using namespace std;

struct football_match {
    football_match *prev;
    time_t date;
    string first_team;
    string second_team;
    string score;
    string place;
    football_match *next;
};

void sFile(football_match *&first) {
    ofstream out("matches.txt");
    if(out) {
        football_match *buf;
        buf = first;
        bool flag = true;
        while (buf != NULL) {
            int len;
            len = first->first_team.length();

            out.write((char*)&len, sizeof(len));
            if(!out){flag = false;}

            if(flag)
                out.write(buf->first_team.c_str(), len);
            if(!out){flag = false;}

            len = buf->second_team.length();

            if(flag)
                out.write((char*)&len, sizeof(len));
            if(!out){flag = false;}

            if(flag)
                out.write(buf->second_team.c_str(), len);
            if(!out){flag = false;}

            len = first->score.length();

            out.write((char*)&len, sizeof(len));
            if(!out){flag = false;}

            if(flag)
                out.write(buf->score.c_str(), len);
            if(!out){flag = false;}

            len = buf->place.length();

            out.write((char*)&len, sizeof(len));
            if(!out){flag = false;}

            if(flag)
                out.write(buf->place.c_str(), len);
            if(!out){flag = false;}

            if (flag)
                out.write((char*)&first->date,sizeof(first->date));      //time_t
            if (!out){flag = false;}

            buf = buf->next;
        }
    } else {
        cout << "ERROR: open file";
    }
}

void lFile(football_match *&first, football_match *&last){
    first = NULL;
    if(checkFile("matches.txt")) {
        football_match *f;
        bool flag;
        flag = true;
        ifstream in("matches.txt");
        while((!in.eof())&&(flag)) {
            if(f = new football_match) {
                int i, len;
                char chr;

                f->first_team = "";
                in.read((char *)&len, sizeof(len));
                if(!in){flag = false;}

                if((!in.eof())&&(flag)){
                    for(i = 0; i < len; i++) {
                        in.read((char *)&chr, 1);
                        if(!in) {
                            flag = false;
                        } else {
                            f->first_team = f->first_team + chr;
                        }
                    }
                }

                f->second_team = "";
                in.read((char *)&len, sizeof(len));
                if(!in){
                    flag = false;
                } else {
                    for(i = 0; i < len; i++){
                        in.read((char *)&chr, 1);
                        f->second_team = f->second_team + chr;
                    }
                }

                f->score = "";
                in.read((char *)&len, sizeof(len));
                if(!in){
                    flag = false;
                } else {
                    for(i = 0; i < len; i++){
                        in.read((char *)&chr, 1);
                        f->score = f->score + chr;
                    }
                }

                f->place = "";
                in.read((char *)&len, sizeof(len));
                if(!in){
                    flag = false;
                } else {
                    for(i = 0; i < len; i++){
                        in.read((char *)&chr, 1);
                        f->place = f->place + chr;
                    }
                }

                if ((!in.eof())&&(flag)){
                    in.read((char*)&f->date,sizeof(f->date));
                    if (!in){flag = false;}}

                if((!in.eof())&&(flag)){
                    if(first == NULL){
                        first = f;
                        last = first;
                    } else {
                        last->next = f;
                        f->prev = last;
                        last = last->next;
                    }
                    f->next = NULL;
                }
            } else { cout << "ERROR: file memory access\n";}
        }
        if(!flag){cout << "ERROR: read file\n";}
    }
}

void enterInfo(football_match *&buff){
    cout << "Enter first team name: ";
    getline(std::cin, buff->first_team);
    if(!cin){}

    cout << "Enter second team name: ";
    getline(std::cin, buff->second_team);

    cout << "Enter score of game('number : number' format): ";
    getline(std::cin, buff->score);

    cout << "Enter, where was the football game: ";
    getline(std::cin, buff->place);

    cout << "Enter date of football match: ";
    buff->date = Date();
}

void addInfo(football_match *&first, football_match *&last){
    football_match *buf = 0;
    buf = new football_match;
    enterInfo(buf);
    if(first == NULL){
        first = buf;
        last = first;
    } else {
        last->next = buf;
        buf->prev = last;
        last = last->next;
    }
    sFile(first);
}

int showInfo(football_match *&first){
    football_match *buf;
    int records = 0;
    buf = first;
    int i = 1;
    while (buf != NULL){
        records++;
        cout << "[" << i << "] " << "[Team 1: " << buf->first_team << "][Team 2: " << buf->second_team << "][Score:  " << buf->score << "][Place: " << buf->place << "]";
        char mbstr[100];
        if (std::strftime(mbstr,sizeof(mbstr),"%A %c",std::localtime(&buf->date))){
            cout << " [Date: " << mbstr<< ']\n';
        }
        buf = buf->next;
        i++;
    }
    return records;
}

void deleteInfo(football_match *&first, football_match *&last){
    int records;
    bool end = false;
    records = showInfo(first);
    cout << "["<<records + 1 << "]Exit\n";
    bool flag;
    int number = 0;
    do {
        cout << "Records number: ";
        cin >> number;
        if(!cin){
            flag = true;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            if(cin.get() != '\n'){
                flag = true;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } else {
                if(number < 1 || number > records) {
                    if(number = records = 1){
                        end = true;
                        flag = false;
                    } else {
                        flag = true;
                        cout << "Bad enter!\n";
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                } else flag = false;
            }
        }
    }while(flag);
    if(!end) {
        int i;
        football_match *f = first;
        for(i = 1; i < number; i++){
            f = f->next;
        }
        if(f->prev != NULL){
            f->prev->next = f->next;
        }
        if(f->next != NULL){
            f->next->prev = f->prev;
        }
        if(f == first){
            first = f->next;
        }
        if(f == last){
            last = f->prev;
        }
        delete f;
        sFile(first);
    }
}

void editInfo(football_match *&first){
    int records;
    bool end = false;
    records = showInfo(first);
    cout << "["<<records + 1 << "]Exit\n";
    bool flag;
    int number = 0;
    do {
        cout << "Record's number: ";
        cin >> number;
        if(!cin){
            flag = true;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            if(cin.get() != '\n'){
                flag = true;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } else {
                if(number < 1 || number > records){
                    if(number == records + 1){
                        end = true;
                        flag = false;
                    } else {
                        flag = true;
                        cout << "Bad enter!\n";
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                } else flag = false;
            }
        }
    } while(flag);
    if(!end){
        int i;
        football_match *f = first;
        for(i = 1; i < number; i++){
            f = f->next;
        }
        enterInfo(f);
    }
    sFile(first);
}


int main() {


}