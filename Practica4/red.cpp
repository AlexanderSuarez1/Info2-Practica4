#include "red.h"

red::red()
{

}

void red::newElement(char value)
{
    enrutador obj(value);
    obj.setElement(value, 0); // agregamos la relación a si mismo.

    this->setElement(obj);
}

void red::createTable()
{
    vector<char> x;

    vector<enrutador>::iterator it;
    it = this->elements.begin();
    for (; it != this->elements.end(); it++)
    {
        it->deletePath();

        vector<enrutador>::iterator i;
        i = this->elements.begin();
        for (; i != this->elements.end(); i++)
        {
            x.clear();
            x.push_back(it->getName());

            //            cout << endl;
            //            cout << endl;
            //            cout << it->getName() << " to " << i->getName() << endl;

            map<char, int> r;
            r = (this->calculatePath(*it, *i, x, 0, 0, true));

            it->setPath(r.begin()->first, i->getName(), r.begin()->second == 1000 ? -1 : r.begin()->second);
        }
    }
}

void red::viewPath()
{
    vector<enrutador>::iterator it;
    it = this->elements.begin();
    for (; it != this->elements.end(); it++)
    {
        map<char, map<char, int>> r(it->getPath());

        cout << endl;
        cout << "Tabla de enrutamiento de " << it->getName() << endl;

        for (auto const &i : r)
        {
            cout << "|" << i.first << ": ";

            map<char, int> m(i.second);

            if (m.begin()->second == -1)
            {
                cout << "  ";
            }
            else
            {
                cout << m.begin()->first << "," << m.begin()->second << " ";
            }
        }

        cout << endl;
    }
}

void red::viewElements()
{
    cout << endl;
    cout << "La red contiene " << this->elements.size() << " enrutadore(s)." << endl;

    vector<enrutador>::iterator it;
    it = this->elements.begin();
    for (; it != this->elements.end(); it++)
    {
        cout << endl;
        cout << "Enrutador " << it->getName() << endl;

        vector<char> v;
        map<char, int> m(it->getElements(v));
        for (auto const &item : m)
        {
            cout << "          |- " << item.first << " con costo de: " << item.second << endl;
        }
    }
}

int red::getCost(char eleA, char eleB)
{
    int c = -1;

    enrutador e = this->getElement(eleA);

    map<char, map<char, int>> m(e.getPath()); // obtengo las relaciones.

    // recorremos las relaciones para llegar a B y obtener el costo.
    for (auto const &item : m)
    {
        if (item.first == eleB)
        {
            map<char, int> mm(item.second);
            c = mm.begin()->second;
            break;
        }
    }

    return c;
}

void red::getBestPath(char eleA, char eleB, string &path)
{
    enrutador e = this->getElement(eleA);
    map<char, map<char, int>> m(e.getPath());

    for (auto const &item : m)
    {
        if (item.first == eleB)
        {
            map<char, int> u = item.second;

            char c = u.begin()->first;
            path += c;

            if (c == eleB)
                break;

            getBestPath(c, eleB, path);
        }
    }
}

void red::updateRelations(char value)
{
    vector<enrutador>::iterator it;
    it = this->elements.begin();

    for (; it != this->elements.end(); it++)
    {
        map<char, int> m(it->getElements({}));

        for (auto const &i : m)
        {
            if (i.first == value)
            {
                it->deleteElement(value);
            }
        }
    }

    this->createTable();
}

void red::random()
{
    string n = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz012345689";

    // número de enrutadores.
    srand(time(NULL));
    //unsigned int ne = 2 + rand() % (n.length() - 2);
    unsigned int ne = 2 + rand() % (10 - 2);

    int nr = 0; // número de relaciones.
    int co = ne;

    vector<char> ele;
    while (ele.size() < ne)
    {
        int p = rand() % (n.length() - 1);

        bool f = true;
        vector<char>::iterator it;
        it = ele.begin();
        for (; it != ele.end(); it++)
        {
            if (n.at(p) == *it) {
                f = false;
                break;
            }
        }

        if (f)
        {
            nr += (co-- - 1);
            ele.push_back(n.at(p));
            this->newElement(n.at(p)); // creamos los elementos.
        }
    }

    // obtenemos el número de relaciones.
    co = ne + rand() % (nr - ne);
    nr = 0;

    vector<char> relaciones;
    char ca;
    char cb;
    while (nr < co)
    {
        int a = rand() % ele.size();
        ca = *(ele.begin() + a); // Elemento a.

        // primera relación
        if (nr == 0)
        {
            int b = rand() % (ele.size() - 1);
            cb = *(ele.begin() + b); // Elemento b.

            if (a == b)
            {
                continue;
            }

            enrutador enr_a(this->getElement(ca));
            enrutador enr_b(this->getElement(cb));

            int costo = 1 + rand() % 19;

            enr_a.setElement(cb, costo);
            enr_b.setElement(ca, costo);

            this->updateElement(enr_a);
            this->updateElement(enr_b);

            relaciones.push_back(ca);
            relaciones.push_back(cb);

            nr++;
        }
        else
        {
            int b = rand() % (relaciones.size() -1);
            cb = *(relaciones.begin() + b);
            enrutador enr_b(this->getElement(cb));

            // validamos si existe la relación.
            if (enr_b.existRelation(ca))
            {
                continue;
            }

            // verificamos si ya está el elemento.
            bool f = false;
            vector<char>::iterator it;
            it = relaciones.begin();
            for (; it != relaciones.end(); it++)
            {
                if (*it == ca)
                {
                    f = true;
                    break;
                }
            }

            // el elemento existe.
            if (!f)
            {
                relaciones.push_back(ca);
            }

            enrutador enr_a(this->getElement(ca));

            int costo = 1 + rand() % 19;

            enr_a.setElement(cb, costo);
            enr_b.setElement(ca, costo);

            this->updateElement(enr_a);
            this->updateElement(enr_b);

            nr++;
        }
    }

    cout << "finalizamos la creacion de los enrutadores." << endl;

    this->createTable();
}

bool red::existElement(char value)
{
    bool resp = false;

    vector<enrutador>::iterator it;
    it = this->elements.begin();
    for (; it != this->elements.end(); it++)
    {
        if (value == it->getName())
        {
            resp = true;
            break;
        }
    }

    return resp;
}

void red::setElement(enrutador obj)
{
    this->elements.push_back(obj);
}

void red::updateElement(enrutador obj)
{
    vector<enrutador>::iterator it;
    it = this->elements.begin();
    for (; it != this->elements.end(); it++)
    {
        if (it->getName() == obj.getName())
        {
            *(it) = obj;
        }
    }
}

void red::deleteElement(enrutador obj)
{
    char c = obj.getName();

    vector<enrutador>::iterator it;
    it = this->elements.begin();
    for(; it != this->elements.end(); it++)
    {
        if (obj.getName() == (it)->getName())
        {
            break;
        }
    }

    this->elements.erase(it);
    this->updateRelations(c);
}

int red::loadFile(string file_name)
{
    int r = -1;

    ifstream ifs;
    ifs.open(file_name);

    if (ifs.is_open())
    {
        char c;
        bool f = false;

        string data = "";
        bool flag = false;
        while (ifs.get(c))
        {
            if (c == '\n' && f)
            {
                if (data.length() > 1) // significa que capturamos las relaciones.
                {
                    flag = true;
                }

                // creamos los enrutadores.
                if (!flag)
                {
                    this->newElement(data.at(0));
                }
                else
                {
                    // creamos las relaciones.
                    char a = data.substr(0, 1).at(0);
                    char b = data.substr(2, 1).at(0);

                    string str = data.substr(4, (data.length() - 4));
                    int v = atoi(str.c_str());

                    enrutador x = this->getElement(a);
                    enrutador y = this->getElement(b);

                    x.setElement(b, v);
                    y.setElement(a, v);

                    this->updateElement(x);
                    this->updateElement(y);
                }

                data = "";
                f = false;
            }
            else
            {
                data += c;
                f = true;
            }
        }

        // creamos la tabla.
        this->createTable();

        r = 1;
    }
    else
    {
        r = -2; // identificador del error.
    }

    ifs.close();

    return r;
}

map<char, int> red::calculatePath(enrutador ini, enrutador f, vector<char> x, int cost, int a, bool fl)
{
    map<char, int> r;
    r[ini.getName()] = 1000;

    if (ini.getName() == f.getName())
    {
        r[ini.getName()] = 0;
        return r;
    }

    map<char, int> m(ini.getElements(x)); // obtenemos las relaciones.

    int aux = 0;
    for (auto const &i : m)
    {
        if (fl && x.size() > 1)
        {
            x.pop_back();
        }

        enrutador obj = this->getElement(i.first);

        if (i.first == f.getName())
        {
            if ((aux - a) > 0)
                cost = (aux - a);

            cost += (i.second + a);

            if (cost < r.begin()->second)
            {
                r.clear(); r[i.first] = cost;
            }

            cost = 0;
        }
        else
        {
            x.push_back(i.first);

            cost += a;

            map<char, int> r_(this->calculatePath(obj, f, x, cost, i.second, false));

            if (r_.begin()->second < r.begin()->second)
            {
                r.clear(); r[i.first] = r_.begin()->second;
            }

            aux = cost;
            cost = 0;

        }
    }

    return r;
}

enrutador red::getElement(char value)
{
    vector<enrutador>::iterator it;
    it = this->elements.begin();
    for (; it != this->elements.end(); it++)
    {
        if (value == it->getName())
        {
            break;
        }
    }

    return *it;
}

vector<enrutador> red::getElement()
{
    return this->elements;
}
