#ifndef RED_H
#define RED_H

#include "enrutador.h"
#include <time.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

class red
{
private:
    vector<enrutador> elements;

public:
    red();

    void newElement(char value);

    void setElement(enrutador obj);

    void updateElement(enrutador obj);

    void deleteElement(enrutador obj);

    void createTable();

    void viewPath();

    void viewElements();

    void getBestPath(char eleA, char eleB, string &path);

    void updateRelations(char value);

    void random(void);

    int loadFile(string file_name);

    int getCost(char eleA, char eleB);

    enrutador getElement(char value);

    bool existElement(char value);

    vector<enrutador> getElement();

    map<char, int> calculatePath(enrutador ini, enrutador f, vector<char> x, int cost, int a, bool fl);
};

#endif // RED_H
