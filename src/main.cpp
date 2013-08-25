//============================================================================
// Name        : sgbdenio.cpp
// Author      : Rodrigo Bueno Tomiosso & Andrey Baumhardt Ramos
// Version     :
// Copyright   : wtfpl
// Description : Hello World in C++, Ansi-style
//============================================================================


//#include <stdlib.h>
#include "sgbdenio.h"
//#include "sgbdenio.cpp"


int main() {
    /*
     string palavra = "";
     cout << checkType(palavra,4)<< endl;
     */
    /*
     // ======= TABLESPACE =======

     //AO CRIAR A PRIMEIRA TABLESPACE TAMBÉM SERÁ CRIADA UMA TABLESPACE PADRÃO NO DIRETÓRIO RAIZ

     Tablespace newTS(0,"TableSpace0",""); //tablespace que será criado no diretório raiz
     createTableSpace(newTS);

     Tablespace newTS1(0,"TableSpace1","/Users/rodrigo/Desktop"); //tablespace criado em /Users/rodrigo/Desktop
     createTableSpace(newTS1);




     // ======= DATABASE =======

     Database db(555,"loja",0,true); //cria uma instancia de database com o nome loja, no tablespace de ID 0(Tablespace0), definido como database padrão
     createDatabase(db); //cria o database apartir da instancia

     Database db1(555,"locadora",1,true); //cria uma instancia de database com o nome locadora, no tablespace de ID 1(Tablespace1), definido como tablespace padrão, sendo este o novo DB padrão.
     createDatabase(db1);




     // ======= TABELAS =======

     Table tabelacliente(0,"cliente", 1); //nova instancia do tipo tabela (0 será o ID, que pode mudar dependendo do numero de tabelas já existentes, nome cliente, 1 pois é uma tabela que será definida como default)

     vector <Column> colunasTabelaCliente;

     //     Column(bool newPk, bool newSerial, string newName, int newType, int newSize, bool newOptional, string newValue, int newFk, int newTableId){

     Column idCliente(true, 0, "idCliente", 0, 10, false, -1, -1); // primarykey(sim), serial(sim), nome da coluna(idCliente), tipo(int), tamanho(10), opcional(nao), foreingkey(nao), id da tabela (será sempre -1 na criação da tabela)

     Column nomeCliente(false, -1, "nomeCliente", 1, 255, false, -1, -1); // primarykey(nao), serial(nao), nome da coluna(nomeCLiente), tipo(string), tamanho(255), opcional(nao), foreingkey(nao), id da tabela (será sempre -1 na criação da tabela)

     Column cpfCliente(false, -1, "cpfCliente", 0, 30, false, -1, -1);// primarykey(nao), serial(nao), nome da coluna(cpfCliente), tipo(int), tamanho(30), opcional(nao), foreingkey(nao), id da tabela (será sempre -1 na criação da tabela)

     Column especialCliente(false, -1, "especialCliente", 2, 1, true, -1, -1);// primarykey(nao), serial(nao), nome da coluna(especialCliente), tipo(boolean), tamanho(1), opcional(nao), foreingkey(nao), id da tabela (será sempre -1 na criação da tabela)

     colunasTabelaCliente.push_back(idCliente);  //insere todas as colunas num "vetor de colunas"
     colunasTabelaCliente.push_back(nomeCliente);
     colunasTabelaCliente.push_back(cpfCliente);
     colunasTabelaCliente.push_back(especialCliente);

     createTable(tabelacliente, colunasTabelaCliente); //cria a tabela com o objeto table e o vetor de colunas.





     Table tabelafilme(0,"filme", 1);
     vector <Column> colunasTabelaFilme;

     Column idFilme(true, 0, "idFilme", 0, 10, false, -1, -1);
     Column nomeFilme(false, -1, "nomeFilme", 1, 255, false, -1, -1);
     Column diretor(false, -1, "diretor", 1, 255, true, -1, -1);
     Column locado(false, -1, "locado", 2, 1, false, -1, -1);


     colunasTabelaFilme.push_back(idFilme);
     colunasTabelaFilme.push_back(nomeFilme);
     colunasTabelaFilme.push_back(diretor);
     colunasTabelaFilme.push_back(locado);

     createTable(tabelafilme, colunasTabelaFilme);



     Table tabelalocacao(0,"locacao", 1);
     vector <Column> colunasTabelalocacao;


     Column idLocacao(true, 0, "idLocacao", 0, 10, false, -1, -1);
     Column idFilmeLocacao(false, -1, "idFilme", 1, 255, false, -1, -1);
     Column idClienteLocacao(false, -1, "idCliente", 1, 255, true, -1, -1);
     Column dataLocacao(false, -1, "locado", 2, 1, false, -1, -1);


     colunasTabelaFilme.push_back(idLocacao);
     colunasTabelaFilme.push_back(idFilmeLocacao);
     colunasTabelaFilme.push_back(idClienteLocacao);
     colunasTabelaFilme.push_back(dataLocacao);

     createTable(tabelalocacao, colunasTabelalocacao);

     // ======= FOREING KEY =======


     Column idClientefk(true, 0, "nomeCliente", 0, 10, false, -1, 1); //cria foreing key para nomeCliente
     setForeingKey(idCliente, 0);

     */

    // ======= INSERT =======

    //inserindo na tabela
    /*
    vector<string> values;
    values.push_back("01");
    values.push_back("02");
    values.push_back("03");
    values.push_back("04");

    insert(values, "filme");
    */

    //    string palavra = "19000";
    //    cout << checkDigit(palavra) << endl;

    // ======= SELECT =======

    vector<string> values;

    values.push_back("idFilme");
  //  values.push_back("nomeFilme");
    values.push_back("diretor");
    values.push_back("locado");

    //values.push_back("*");

    vector<vector<string> > selectResult =  select(values, "filme", values);

    for (int tuple = 0 ; tuple<selectResult.size(); tuple++) {
        for (int col = 0; col<selectResult.at(tuple).size(); col++) {
            cout << selectResult.at(tuple).at(col) << " - ";
        }
        cout << endl;
    }

    system("pause");
    return 0;

}
