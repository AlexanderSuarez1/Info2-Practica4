#ifndef ENRUTADOR_H
#define ENRUTADOR_H

#include <iostream>
#include <vector>
#include <map>

using namespace std;

class enrutador
{
private:
    char name;
    map<char, int> element;
    map<char, map<char, int>> path;

public:
    enrutador(char name_);

    char getName(void);

    int getLengthElements();

    void setElement(char value, int cost);

    void deleteElement(char value);

    void deletePath();

    void setPath(char value, char to, int cost);

    void updateCost(int cost, char value);

    bool existRelation(char value);

    map<char, map<char, int> > getPath();

    map<char, int> getElements(const vector<char> &m);
};

#endif // ENRUTADOR_H
