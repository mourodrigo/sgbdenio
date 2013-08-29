//============================================================================
// Name        : main.cpp
// Author      : Rodrigo Bueno Tomiosso & Andrey Baumhardt Ramos
// Version     :
// Copyright   : wtfpl http://www.wtfpl.net/
// Description : Sistema Gerenciador de Banco de dados C++, Ansi-style
//============================================================================


#include "sgbdenio.h"


int main() {

/*

     // ======= TABLESPACE =======

     //AO CRIAR A PRIMEIRA TABLESPACE TAMBÉM SERÁ CRIADA UMA TABLESPACE PADRÃO NO DIRETÓRIO RAIZ

     Tablespace newTS(0,"TableSpace0",""); //tablespace que será criado no diretório raiz
     createTableSpace(newTS);

     Tablespace newTS1(0,"TableSpace1","/Users/rodrigo/Desktop"); //tablespace criado em /Users/rodrigo/Desktop
     createTableSpace(newTS1);


     // ======= DATABASE =======

     Database db(0,"loja",0,true); //cria uma instancia de database com o nome loja, no tablespace de ID 0(Tablespace0), definido como database padrão
     createDatabase(db); //cria o database apartir da instancia

     Database db1(0,"locadora",1,true); //cria uma instancia de database com o nome locadora, no tablespace de ID 1(Tablespace1), definido como tablespace padrão, sendo este o novo DB padrão.
     createDatabase(db1);

     Database db2(0,"revendora",2, false); //cria uma instancia de database com o nome locadora, no tablespace de ID 1(Tablespace1), definido como tablespace padrão, sendo este o novo DB padrão.
     createDatabase(db2);


     // ======= TABELAS =======

     Table tabelacliente(0,"cliente", 1); //nova instancia do tipo tabela (0 será o ID, que pode mudar dependendo do numero de tabelas já existentes, nome cliente, 1 pois é uma tabela que será definida como default)

     vector <Column> colunasTabelaCliente;

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




     // ======= FOREING KEY =======


     //Os valores válidos nesse caso devem ser: nome da coluna, tipo e tamanho

     Column idClientefk(true, 0, "idCliente", 0, 10, false, -1, 2); //cria foreing key para nomeCliente
     setForeingKey(idClientefk, 0);

     Column idFilmefk(true, 0, "idFilme", 0, 10, false, -1, 2); //cria foreing key para nomeCliente
     setForeingKey(idFilmefk, 1);




    // ======= INSERT =======

    vector<string> valuesc1;
    valuesc1.push_back("999");
    valuesc1.push_back("Andrey");
    valuesc1.push_back("1298372435");
    valuesc1.push_back("1");

    insertTable(valuesc1, "cliente");
    cout << "TABELA CLIENTE" << endl;


    vector<string> valuesc2;
    valuesc2.push_back("999");
    valuesc2.push_back("Rodrigo");
    valuesc2.push_back("239487132");
    valuesc2.push_back("1");

    insertTable(valuesc2, "cliente");
    cout << "TABELA CLIENTE" << endl;

    vector<string> valuesc3;
    valuesc3.push_back("999");
    valuesc3.push_back("Felipe");
    valuesc3.push_back("4539845");
    valuesc3.push_back("0");

    insertTable(valuesc3, "cliente");
    cout << "TABELA CLIENTE" << endl;

    vector<string> valuesc4;
    valuesc4.push_back("999");
    valuesc4.push_back("Marcelo");
    valuesc4.push_back("3452320");
    valuesc4.push_back("0");

    insertTable(valuesc4, "cliente");
    cout << "TABELA CLIENTE" << endl;



    vector<string> valuesf1;
    valuesf1.push_back("999");
    valuesf1.push_back("Laranja Mecânica");
    valuesf1.push_back("Stanley Kubrick");
    valuesf1.push_back("0");

    insertTable(valuesf1, "filme");
    cout << "TABELA FILME" << endl;

    vector<string> valuesf2;
    valuesf2.push_back("999");
    valuesf2.push_back("O poderoso chefão");
    valuesf2.push_back("Francis Ford Coppola");
    valuesf2.push_back("1");

    insertTable(valuesf2, "filme");
    cout << "TABELA FILME" << endl;

    vector<string> valuesf3;
    valuesf3.push_back("999");
    valuesf3.push_back("Pulp Fiction");
    valuesf3.push_back("Quentin Tarantino");
    valuesf3.push_back("1");

    insertTable(valuesf3, "filme");
    cout << "TABELA FILME" << endl;

    vector<string> valuesf4;
    valuesf4.push_back("999");
    valuesf4.push_back("Jango");
    valuesf4.push_back("Quentin Tarantino");
    valuesf4.push_back("0");

    insertTable(valuesf4, "filme");
    cout << "TABELA FILME" << endl;

    vector<string> valuesf5;
    valuesf5.push_back("999");
    valuesf5.push_back("Star Wars");
    valuesf5.push_back(" George Lucas");
    valuesf5.push_back("1");

    insertTable(valuesf5, "filme");
    cout << "TABELA FILME" << endl;



    vector<string> valuesl1;
    valuesl1.push_back("0");
    valuesl1.push_back("0");
    valuesl1.push_back("1");
    valuesl1.push_back("0");
    valuesl1.push_back("05.00");
    valuesl1.push_back("20130815");
    valuesl1.push_back("123000");

    insertTable(valuesl1, "locacao");
    cout << "TABELA LOCACAO" << endl;

    vector<string> valuesl2;
    valuesl2.push_back("0");
    valuesl2.push_back("1");
    valuesl2.push_back("1");
    valuesl2.push_back("1");
    valuesl2.push_back("3.20");
    valuesl2.push_back("20130815");
    valuesl2.push_back("133000");

    insertTable(valuesl2, "locacao");
    cout << "TABELA LOCACAO" << endl;

    vector<string> valuesl3;
    valuesl3.push_back("1");
    valuesl3.push_back("1");
    valuesl3.push_back("2");
    valuesl3.push_back("0");
    valuesl3.push_back("05.00");
    valuesl3.push_back("20130815");
    valuesl3.push_back("153623");

    insertTable(valuesl3, "locacao");
    cout << "TABELA LOCACAO" << endl;

    vector<string> valuesl4;
    valuesl4.push_back("1");
    valuesl4.push_back("0");
    valuesl4.push_back("1");
    valuesl4.push_back("0");
    valuesl4.push_back("04.00");
    valuesl4.push_back("20130215");
    valuesl4.push_back("143000");

    insertTable(valuesl4, "locacao");
    cout << "TABELA LOCACAO" << endl;

    vector<string> valuesl5;
    valuesl5.push_back("2");
    valuesl5.push_back("1");
    valuesl5.push_back("1");
    valuesl5.push_back("0");
    valuesl5.push_back("05.00");
    valuesl5.push_back("20130815");
    valuesl5.push_back("153000");

    insertTable(valuesl5, "locacao");
    cout << "TABELA LOCACAO" << endl;

    vector<string> valuesl6;
    valuesl6.push_back("1");
    valuesl6.push_back("1");
    valuesl6.push_back("2");
    valuesl6.push_back("1");
    valuesl6.push_back("04.20");
    valuesl6.push_back("20130816");
    valuesl6.push_back("183000");

    insertTable(valuesl6, "locacao");

    */
    /*

    //=============SELECT============

    vector<string> valuesSC1;

    valuesSC1.push_back("*");
    //valuesSC1.push_back("nomeCliente");
    //valuesSC1.push_back("cpfCliente");

    vector<Condition> whereSC1;
    whereSC1.push_back(Condition("especialCliente", "=", "0"));

    vector<vector<string> > selectResultSC1 =  select(valuesSC1, "cliente", whereSC1);

    cout << endl << endl << "SELECT * FROM Cliente" << endl << endl;

    for (int tuple = 0 ; tuple<selectResultSC1.size(); tuple++) {
        for (int col = 0; col<selectResultSC1.at(tuple).size(); col++) {
            cout << selectResultSC1.at(tuple).at(col) << " - ";
        }
        cout << endl;
    }








    vector<string> valuesF1;

    valuesF1.push_back("*");

    //values.push_back("*");

    vector<Condition> whereSFC1;
    //        where.push_back(Condition("especialCliente", "=", "0"));

    vector<vector<string> > selectResultSFC1 =  select(valuesF1, "filme", whereSFC1);

    cout << endl << endl << "SELECT * FROM FILME" << endl << endl;

    for (int tuple = 0 ; tuple<selectResultSFC1.size(); tuple++) {
        for (int col = 0; col<selectResultSFC1.at(tuple).size(); col++) {
            cout << selectResultSFC1.at(tuple).at(col) << " - ";
        }
        cout << endl;
    }


    // ======= SELECT =======
    cout << "SELECT * FROM LOCACAO WHERE 1" << endl;

    vector<string> values;

    values.push_back("*");

    vector<Condition> where;

    vector<vector<string> > selectResult =  select(values, "locacao", where);

    cout << endl << endl << "TABELA LOCAÇÃO" << endl << endl;

    for (int tuple = 0 ; tuple<selectResult.size(); tuple++) {
        for (int col = 0; col<selectResult.at(tuple).size(); col++) {
            cout << selectResult.at(tuple).at(col) << " - ";
        }
        cout << endl;
    }


    cout << "SELECT idLocacao, horaLocacao, valor, dataLocacao FROM LOCACAO WHERE valor > 3.00" << endl;

    vector<string> valuesS1;

    valuesS1.push_back("idLocacao");
    valuesS1.push_back("horaLocacao");
    valuesS1.push_back("valor");
    valuesS1.push_back("dataLocacao");

    //values.push_back("*");

    vector<Condition> whereS1;
    where.push_back(Condition("valor", ">", "3.00"));

    vector<vector<string> > selectResultS1 =  select(valuesS1, "locacao", whereS1);


    for (int tuple = 0 ; tuple<selectResultS1.size(); tuple++) {
        for (int col = 0; col<selectResultS1.at(tuple).size(); col++) {
            cout << selectResultS1.at(tuple).at(col) << " - ";
        }
        cout << endl;
    }







    cout << endl << endl << endl << "SELECT idLocacao, idFilme, idCliente, dataLocacao, promocao FROM LOCACAO WHERE producao = 0 AND idFILME = 1" << endl;

        vector<string> valuesS2;

        valuesS2.push_back("idLocacao");
        valuesS2.push_back("idFilme");
        valuesS2.push_back("idCliente");
        valuesS2.push_back("dataLocacao");
        valuesS2.push_back("promocao");

        //valuesS2.push_back("*");

        vector<Condition> whereS2;
        whereS2.push_back(Condition("promocao", "=", "0"));
        whereS2.push_back(Condition("idFilme", "=", "1"));

        vector<vector<string> > selectResultS2 =  select(valuesS2, "locacao", whereS2);


        for (int tuple = 0 ; tuple<selectResultS2.size(); tuple++) {
            for (int col = 0; col<selectResultS2.at(tuple).size(); col++) {
                cout << selectResultS2.at(tuple).at(col) << " - ";
            }
            cout << endl;
        }



        */

        //===========UPDATE===============
        vector <Condition> where;
        where.push_back(Condition("valor", ">", "03.20"));

        updateTable("valor","locacao",where,"04.20");

        //vector <Condition> where2;
        //where.push_back(Condition("cpfCliente", "=", "239487132"));







        //================DELETE================


        //    deleteItem("table","locacao");
        //    deleteItem("table","estoque");

        //    deleteItem("database","locadora");
        //    deleteItem("database","loja");

        //    deleteItem("tablespace","TableSpace0");
        //    deleteItem("tablespace","TableSpace0");



        //  dropTable("cliente");
        //  dropTable("locacao");
        //  dropTable("filme");

        //     deleteItem("table","locacao");
        //    deleteItem("table","estoque");

        //    deleteItem("database","locadora");
        //    deleteItem("database","loja");

        //    deleteItem("tablespace","TableSpace0");
        //    deleteItem("tablespace","TableSpace0");




    system("pause");
    return 0;

}
