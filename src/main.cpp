//============================================================================
// Name        : sgbdenio.cpp
// Author      : Rodrigo Bueno Tomiosso & Andrey Baumhardt Ramos
// Version     :
// Copyright   : wtfpl
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "sgbdenio.h"


int main() {


     /*
     // ======= TABLESPACE =======

     //AO CRIAR A PRIMEIRA TABLESPACE TAMBÉM SERÁ CRIADA UMA TABLESPACE PADRÃO NO DIRETÓRIO RAIZ

     Tablespace newTS(0,"TableSpace0",""); //tablespace que será criado no diretório raiz
     createTableSpace(newTS);

     Tablespace newTS1(0,"TableSpace1","C:/Users/Andrey/Desktop"); //tablespace criado em /Users/rodrigo/Desktop
     createTableSpace(newTS1);


     // ======= DATABASE =======

     Database db(555,"loja",0,true); //cria uma instancia de database com o nome loja, no tablespace de ID 0(Tablespace0), definido como database padrão
     createDatabase(db); //cria o database apartir da instancia

     Database db1(555,"locadora",1,true); //cria uma instancia de database com o nome locadora, no tablespace de ID 1(Tablespace1), definido como tablespace padrão, sendo este o novo DB padrão.
     createDatabase(db1);

     Database db2(555,"revendora",2,true); //cria uma instancia de database com o nome locadora, no tablespace de ID 1(Tablespace1), definido como tablespace padrão, sendo este o novo DB padrão.
     createDatabase(db2);



     // ======= TABELAS =======

     Table tabelacliente(0,"cliente", 1); //nova instancia do tipo tabela (0 será o ID, que pode mudar dependendo do numero de tabelas já existentes, nome cliente, 1 pois é uma tabela que será definida como default)

     vector <Column> colunasTabelaCliente;

     //     Column(bool newPk, bool newSerial, string newName, int newType, int newSize, bool newOptional, int newFk, int newTableId){

     Column idCliente(true, 0, "idCliente", 0, 10, false, -1, -1); // primarykey(sim), serial(sim), nome da coluna(idCliente), tipo(int), tamanho(10), opcional(nao), foreingkey(nao), id da tabela (será sempre -1 na criação da tabela)

     Column nomeCliente(false, -1, "nomeCliente", 3, 255, false, -1, -1); // primarykey(nao), serial(nao), nome da coluna(nomeCLiente), tipo(string), tamanho(255), opcional(nao), foreingkey(nao), id da tabela (será sempre -1 na criação da tabela)

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
     Column nomeFilme(false, -1, "nomeFilme", 3, 255, false, -1, -1);
     Column diretor(false, -1, "diretor", 3, 255, true, -1, -1);
     Column locado(false, -1, "locado", 2, 1, false, -1, -1);


     colunasTabelaFilme.push_back(idFilme);
     colunasTabelaFilme.push_back(nomeFilme);
     colunasTabelaFilme.push_back(diretor);
     colunasTabelaFilme.push_back(locado);

     createTable(tabelafilme, colunasTabelaFilme);


     Table tabelalocacao(0,"locacao", 1);
     vector <Column> colunasTabelalocacao;


     Column idLocacao(true, 0, "idLocacao", 0, 10, false, -1, -1);
     Column idFilmeLocacao(false, -1, "idFilme", 0, 10, false, -1, -1);
     Column idClienteLocacao(false, -1, "idCliente", 0, 10, false, -1, -1);
     Column promocaoLocacao(false, -1, "promocao", 2, 1, false, -1, -1);
     Column valorLocacao(false, -1, "valor", 1, 8, false, -1, -1);
     Column dataLocacao(false, -1, "dataLocacao", 4, 8, false, -1, -1);
     Column horaLocacao(false, -1, "horaLocacao", 5, 6, true, -1, -1);


     colunasTabelalocacao.push_back(idLocacao);
     colunasTabelalocacao.push_back(idFilmeLocacao);
     colunasTabelalocacao.push_back(idClienteLocacao);
     colunasTabelalocacao.push_back(promocaoLocacao);
     colunasTabelalocacao.push_back(valorLocacao);
     colunasTabelalocacao.push_back(dataLocacao);
     colunasTabelalocacao.push_back(horaLocacao);
     createTable(tabelalocacao, colunasTabelalocacao);

    */
    /*
     // ======= FOREING KEY =======


        //Os valores válidos nesse caso devem ser: nome da coluna, tipo e tamanho
     Column idClientefk(true, 0, "idCliente", 0, 10, false, -1, 1); //cria foreing key para nomeCliente
     setForeingKey(idClientefk, 0);

     Column idFilmefk(true, 0, "idFilme", 0, 10, false, -1, 1); //cria foreing key para nomeCliente
     setForeingKey(idFilmefk, 1);
    */



    // ======= INSERT =======

    //inserindo na tabela
    /*
     vector<string> values;
     values.push_back("999");
     values.push_back("Andrey");
     values.push_back("420420");
     values.push_back("0");
     vector<string> values2;
     values2.push_back("999");
     values2.push_back("Rodrigo");
     values2.push_back("666");
     values2.push_back("0");
     vector<string> values3;
     values3.push_back("999");
     values3.push_back("Brasileirinhas");
     values3.push_back("RedTube");
     values3.push_back("0");
     vector<string> values4;
     values4.push_back("999");
     values4.push_back("Como viver 200 anos");
     values4.push_back("Hebe");
     values4.push_back("0");

     insertTable(values, "cliente");
     insertTable(values2, "cliente");
     insertTable(values3, "filme");
     insertTable(values4, "filme");
     */

    // ======= SELECT =======
    /*
     vector<string> valuesS;

     //values.push_back("*");
     valuesS.push_back("horaLocacao");
     valuesS.push_back("valor");
     valuesS.push_back("dataLocacao");
     valuesS.push_back("idLocacao");

     //values.push_back("*");

    vector<Condition> where;
    where.push_back(Condition("idLocacao", "<", "94"));
    where.push_back(Condition("valor", "<=", "30.00"));
    //where.push_back(Condition("idLocacao", "=", "92"));

     vector<vector<string> > selectResult =  select(valuesS, "locacao", where);

     for (int tuple = 0 ; tuple<selectResult.size(); tuple++) {
     for (int col = 0; col<selectResult.at(tuple).size(); col++) {
     cout << selectResult.at(tuple).at(col) << " - ";
     }
     cout << endl;
     }
     */

     //===UPDATE
     //vector <Condition> where;
     //where.push_back(Condition("cpfCliente", "=", "420420"));

    //updateTable("nomeCliente","cliente",where,"Canhabes");

     //vector <Condition> where;
     //where.push_back(Condition("cpfCliente", "=", "420420"));

     //deleteFromTable("cliente",where);

    //deleteItem("tablespace","TableSpace1");
    //deleteItem("table", "locacao");


    system("pause");
    return 0;

}
