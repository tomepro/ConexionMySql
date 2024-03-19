#include <iostream>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <fstream>
#include <string>

using namespace std;

void generarCertificado(string dni, string nombre, string apellido, string matricula, string marca, string modelo, string descripcion, string counttdni) {
    // Nombre del archivo
    string nombreArchivo = nombre + apellido + "_certificado.txt";

    // Abrir el archivo en modo escritura
    ofstream archivo(nombreArchivo);

    // Verificar si el archivo se abrió correctamente
    if (archivo.is_open()) {
        // Escribir el contenido del certificado
        archivo << "╔═════════════════════════════════════════════════════════════════════════════════════════╗\n\n\n"; 
        archivo << "\t▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n";
        archivo << "\t█                                                                       █\n";
        archivo << "\t█\tCertificado de Participación en La Sagrera Motor Week\t\t█\n";
        archivo << "\t█                                                                       █\n";
        archivo << "\t█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█\n\n";
        archivo << "\tEste certificado se otorga a: " << nombre << " " << apellido;
        archivo << "\n\tCon DNI: " << dni << "\n\n";
        archivo << "\tEl cual participo con: " << marca << " " << modelo;
        archivo << "\tcon matricula " << matricula << "\n\n";
        archivo << "\tY participo en la categoria de : " << descripcion << " en " << counttdni << " eventos distintos\n\n";
        archivo << "\tCertificado entreago por su participación en el evento mencionado anteriormente.\n";
        archivo << "\t¡Felicidades y gracias por participar!\n\n\n\n";
        archivo << "╚═════════════════════════════════════════════════════════════════════════════════════════╝";

        // Cerrar el archivo
        archivo.close();

        // Printa que se a realizado correctamente
        cout << "Se ha generado el certificado correctamente en el archivo: " << nombreArchivo << endl;
    }
    else {
        // Printa un error si no se puede abrir el archivo correctamente
        cout << "Error al abrir el archivo para escribir." << endl;
    }
}

int main(int argc, char* argv[]) {
    sql::Driver* driver;
    sql::Connection* con;
    sql::Statement* stmt;
    sql::ResultSet* res;

    //string query = ("SELECT dni,nombre,apellido FROM participantes WHERE dni = %d", argv[0]);
    //string query = ("SELECT dni,nombre,apellido FROM participantes WHERE dni = '12345678I'" );
    //string query = ("SELECT p.dni,p.nombre,p.apellido,v.matricula,v.marca,v.modelo,vt.descripcion FROM participantes p join vehiculos v on p.dni = v.dni join vehiculos_tipos vt on v.tipo = vt.tipo WHERE p.dni = '34567891J'");
    //string query = ("SELECT p.dni, p.nombre, p.apellido, v.matricula, v.modelo, v.marca, vt.descripcion, count(t.dni) from participantes p join vehiculos v on p.dni = v.dni join vehiculos_tipos vt on v.tipo = vt.tipo join tiempos t on t.dni = p.dni where p.dni = '34567891J'");
    string query = ("SELECT p.dni, p.nombre, p.apellido, v.matricula, v.modelo, v.marca, vt.descripcion, count(t.dni) from participantes p join vehiculos v on p.dni = v.dni join vehiculos_tipos vt on v.tipo = vt.tipo join tiempos t on t.dni = p.dni where p.dni = %d", argv[0]);
    string dni;
    string nombre;
    string apellido;
    string matricula;
    string marca;
    string modelo;
    string descripcion;
    string counttdni;

    //dni, nombre, apellido, matricula, marca, modelo, tipo 

    try {
        driver = get_driver_instance();
        con = driver->connect("tcp://sagreragp.com:3306", "user", "password");
        con->setSchema("sagreragp");

        stmt = con->createStatement();
        res = stmt->executeQuery(query);

        while (res->next()) {
            cout << "Columna1: " << res->getString("dni") << endl;
            dni = res->getString("dni");
            cout << "Columna2: " << res->getString("nombre") << endl;
            nombre = res->getString("nombre");
            cout << "Columna3: " << res->getString("apellido") << endl;
            apellido = res->getString("apellido");
            cout << "Columna4: " << res->getString("matricula") << endl;
            matricula = res->getString("matricula");
            cout << "Columna5: " << res->getString("marca") << endl;
            marca = res->getString("marca");
            cout << "Columna6: " << res->getString("modelo") << endl;
            modelo = res->getString("modelo");
            cout << "Columna7: " << res->getString("descripcion") << endl;
            descripcion = res->getString("descripcion");
            cout << "Columna8: " << res->getString("count(t.dni)") << endl;
            counttdni = res->getString("count(t.dni)");
        }

        generarCertificado(dni, nombre, apellido, matricula, marca, modelo, descripcion, counttdni);

        delete res;
        delete stmt;
        delete con;
    }
    catch (sql::SQLException& e) {
        cout << "Error al conectar con MySQL: " << e.what() << endl;
    }

    return 0;
}