#include "enrutador.h"

enrutador::enrutador(char name_)
{
    this->name = name_;
}

char enrutador::getName()
{
    return this->name;
}

int enrutador::getLengthElements()
{
    map<char, int> r = this->element;
    r.erase(this->getName());

    return r.size();
}

void enrutador::setElement(char value, int cost)
{
    this->element[value] = cost;
}

void enrutador::deletePath()
{
    this->path.clear();
}

void enrutador::setPath(char value, char to, int cost)
{
    map<char, int> m;
    m[value] = cost;

    this->path[to] = m;
}

void enrutador::updateCost(int cost, char value)
{
    this->element[value] = cost;
}

bool enrutador::existRelation(char value)
{
    bool r = false;

    for (auto const &i : this->element)
    {
        if (i.first == value)
        {
            r = true;
            break;
        }
    }

    return r;
}

void enrutador::deleteElement(char value)
{
    this->element.erase(value);
}

map<char, map<char, int>> enrutador::getPath()
{
    return this->path;
}

map<char, int> enrutador::getElements(const vector<char> &m)
{
    map<char, int> ret = this->element;

    vector<char>::const_iterator it;
    it = m.begin();
    for (; it != m.end(); it++)
    {
        ret.erase(*(it));
    }

    return ret;
}
