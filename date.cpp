//
// Created by Eugene Starodubov on 13.02.2018.
//
#include "date.h"
#include <iostream>
#include <fstream>

using namespace std;


time_t Date() {
    tm * result_date;
    bool flag;
    int year = 0, month = 0, day = 0;
    cout << "Adding year \n";
    do {
        cout << "Enter year: ";
        cin >> year;
        if(!cin){
            flag = true;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }else{
            if(cin.get() != '\n'){
                flag = true;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else{
                if(year <= 1976 || year >= 2100) {
                    flag = true;
                    cout << "Bad enter!\n";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }else
                    flag = false;
            }
        }
    }while(flag);


    cout << "Adding month \n";
    do {
        cout << "Enter month: ";
        cin >> month;
        if(!cin){
            flag = true;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }else{
            if(cin.get() != '\n'){
                flag = true;
            }
            else{
                if(month < 1 || month > 12) {
                    flag = true;
                    cout << "Bad enter!\n";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }else
                    flag = false;
            }
        }
    }while(flag);


    cout << "Adding day \n";
    do {
        cout << "Enter day: ";
        cin >> day;
        if(!cin){
            flag = true;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }else{
            if(cin.get() != '\n'){
                flag = true;
            }else{
                bool check = false;

                if (month % 2 != 0 && month != 2 && day >= 1 && day <= 31) // Нечетность месяца
                {check = true;}

                if (month % 2 == 0 && month != 2 && day >= 1 && day <= 30) // Четность месяца
                {check = true;}

                if(month == 2){
                    if((year % 4 || (!(year % 100) && year % 400)) && day >= 1 && day <= 28)
                    {check = true;}
                    if(!(year % 4 || (!(year % 100) && year % 400)) && day >= 1 && day <= 29)
                    {check = true;}
                }

                if (!check)
                {
                    flag = true;
                    cout << "Bad enter!\n";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }else
                    flag = false;
            }
        }
    }
    while(flag);

    time_t result;
    time (&result);
    result_date=localtime(&result);
    result_date->tm_year = year-1900;
    result_date->tm_mon = month-1;
    result_date->tm_mday = day;
    return mktime(result_date);
}

