#include <iostream>
#include "red.h"
#include "enrutador.h"

using namespace std;

red r;

bool pedirEnrutadores(char * e);
bool pedirEnrutadores(char * e)
{
    // pedimos al usuario que ingrese los dos enrutadores.
    bool k = true;

    for (int i = 0; i < 2; i++)
    {
        cout << endl;
        cout << "Ingrese el nombre del enrutador: " << endl;
        cin >> e[i];

        if (!r.existElement(e[i]))
        {
            cout << endl;
            cout << "INFORMACION: " << endl;
            cout << "******* Usuario, el enrutador " << e[i] << " no existe. *******" << endl;
            k = false;
            break;
        }
    }

    return k;
}

int main()
{
    char s = 0;
    do
    {
        cout << endl;
        cout << "MENU PRINCIPAL" << endl;
        cout << "SELECCIONE UNA OPCION: " << endl;
        cout << "A- AGREGAR ENRUTADOR" << endl;
        cout << "B- ELIMINAR ENRUTADOR" << endl;
        cout << "C- VER ENRUTADOR" << endl;
        cout << "D- VER TABLA" << endl;
        cout << "E- AGREGAR RELACION" << endl;
        cout << "F- VER COSTO" << endl;
        cout << "G- VER RUTA" << endl;
        cout << "H- CARGAR ARCHIVO" << endl;
        cout << "I- CAMBIAR COSTO" << endl;
        cout << "J- GENERAR RED" << endl;

        cin >> s;

        if (s == 'A')
        {
            cout << endl;
            cout << "INFORMACION: " << endl;
            cout << "******* Usuario, Usuario, ingrese 0 para terminar el proceso." << endl;

            bool exist = false;
            char c;

            vector<enrutador>::iterator it;
            while (true)
            {
                exist = false;

                cout << endl;
                cout << "Ingrese el nombre del enrutador: " << endl;
                cin >> c;

                // terminamos el ciclo.
                if (c == '0') {
                    break;
                }

                it = r.getElement().begin();
                for (; it != r.getElement().end(); it++)
                {
                    if (c == it->getName())
                    {
                        exist = true;
                        cout << endl;
                        cout << "INFORMACION: " << endl;
                        cout << "******* Usuario, el nombre '" << c << "' ya esta siendo utilizado." << endl;
                        break;
                    }
                }

                if (!exist) {
                    r.newElement(c); // creamos el elemento.
                }
            }
        }
        else if (s == 'B')
        {
            char name;

            cout << endl;
            cout << "Ingrese el nombre del enrutador: " << endl;
            cin >> name;

            if (r.existElement(name))
            {
                r.deleteElement(r.getElement(name));
            }
            else
            {
                cout << endl;
                cout << "INFORMACION: " << endl;
                cout << "******* Usuario, el enrutador " << name << " no existe. *******" << endl;
            }
        }
        else if (s == 'C')
        {
            r.viewElements();
        }
        else if (s == 'D')
        {
            r.viewPath();
        }
        else if (s == 'E')
        {
            char e[2] = {};
            int c = 0;

            if (!pedirEnrutadores(e))
            {
                continue;
            }

            cout << endl;
            cout << "Ingrese el costo de la relacion: " << endl;
            cin >> c;

            // validamos que el costo no sea menor que cero.
            if (c > 0)
            {
                enrutador a = r.getElement(e[0]);
                enrutador b = r.getElement(e[1]);

                a.setElement(e[1], c);
                b.setElement(e[0], c);

                // actualizamos los elementos en la red.
                r.updateElement(a);
                r.updateElement(b);

                // creamos la tabla de enretamiento.
                r.createTable();
            }
            else
            {
                cout << endl;
                cout << "INFORMACION: " << endl;
                cout << "******* Usuario, el costo no puede ser menor o igual a cero. *******" << endl;
            }
        }
        else if (s == 'F')
        {
            char e[2] = {};
            if (!pedirEnrutadores(e))
            {
                continue; // Uno de los enrutadores ingresados no existe.
            }

            int resp = r.getCost(e[0], e[1]); // obtenemos el costo.

            if (resp == -1)
            {
                cout << endl;
                cout << "Usuario, los elementos " <<  e[0] << " y " << e[1] << " no estan relacionados." << endl;
            }
            else
            {
                cout << endl;
                cout << "El costo de enviar de " << e[0] << " a " << e[1] << " es: " << resp << endl;
            }
        }
        else if (s == 'G')
        {

            char e[2] = {};

            if (!pedirEnrutadores(e))
            {
                continue;
            }

            string str = "";
            r.getBestPath(e[0], e[1], str); // obtenemos la mejor ruta.

            cout << endl;
            cout << "La mejor ruta para enviar un paquete de " << e[0] << " a " << e[1] << " es: " << str << endl;
        }
        else if (s == 'H')
        {
            string f = "";
            cout << endl;
            cout << "Ingrese el nombre del archivo: " << endl;
            cin >> f;

            int re = r.loadFile("C:/Users/danie/Dropbox/Entregable Lab 4/Ejercicio/" + f);

            if (re == -1)
            {
                cout << endl;
                cout << "INFORMACION: " << endl;
                cout << "******* Usuario, ha ocurrido un error leyendo el archivo. *******" << endl;
            }
            else if (re == -2)
            {
                cout << endl;
                cout << "INFORMACION: " << endl;
                cout << "******* Usuario, no se ha podido abrir el archivo. *******" << endl;
            }
        }
        else if (s == 'I')
        {
            char e[2] = {};

            if (!pedirEnrutadores(e))
            {
                continue;
            }

            enrutador a = r.getElement(e[0]);
            enrutador b = r.getElement(e[1]);

            if (!a.existRelation(e[1]))
            {
                cout << endl;
                cout << "INFORMACION: " << endl;
                cout << "******* Usuario, los enrutadores no estan relacionados. *******" << endl;
            }
            else
            {
                int c = 0;
                cout << endl;
                cout << "Ingrese el costo: " << endl;
                cin >> c;

                if (c <= 0)
                {
                    cout << endl;
                    cout << "INFORMACION: " << endl;
                    cout << "******* Usuario, el costo no puede ser menor o igual a cero. *******" << endl;
                }
                else
                {
                    a.updateCost(c, e[1]);
                    b.updateCost(c, e[0]);

                    // actualizamos los elementos en la red.
                    r.updateElement(a);
                    r.updateElement(b);

                    r.createTable();
                }
            }
        }
        else if (s == 'J')
        {
            r.random();
        }

    } while(s != 'Z');

    return 0;
}
