//
//  sgbdenio.h
//  sgbdenio
//
//  Created by Rodrigo on 13/08/13.
//  Copyright (c) 2013 uffs. All rights reserved.
//

#include "sgbdenio.cpp"

vector<string> explode( const string& s, const string& delimiter ); //converte uma string para um vetor separando por um delimitador

bool stringIsBool(string stringbool); //converte string para boleano

string getCurrentPath(); //retorna o caminho raiz

bool fileExists(const char *filename); // verifica se arquivo existe

Tablespace checkTablespace(int idTS); //retorna uma tablespace de determinado id

vector<Database> getAllDatabase(); //retorna todos os banco de dados

bool createDatabase(Database newdb); //cria banco de dados (instancia do tipo banco de dados)

Database getDefaultDb(); //retorna o banco de dados padrão

vector<Tablespace> getAllTableSpace(); // retorna todos os tablespaces

bool createTableSpace(Tablespace newts); //cria um tablespace (instancia do tipo tablespace)

string getPathFromTableSpace(int idTs); // retorna o caminho de um tablespace (id do tablespace)

string getPathFromDatabase(int dbId); //retorna o caminho de um banco de dados (id do banco de dados)

vector<Table> getAllTables(); //retornas todos os metadados de tabelas

vector<Column> getAllColumns(int newTableId); // retorna todos os metatados de colunas de tabelas

vector <Primary> getAllPrimary(int idPrimary); // retorna todas primary keys (-1 retorna todas, != -1 retorna dados de uma primary key de id especifico)

bool createTable(Table newTable, vector<Column> columns); // cria uma tabela (instancia do tipo tabela, vetor de colunas)

vector<Foreing> getAllFks(); //retorna todas as primary keys

bool setForeingKey(Column col, int pk); //alter table que seta a foreing key, (coluna da foreing key, ID da primary key)

bool insertTable(vector<string> values, string tableName); // insert table

int checkDigit(string palavra);//função que verifia se é inteiro ou floar

bool checkType(string palavra,int type);//função que verifia os tipos

vector<vector<string> > select(vector<string> parameters, string tableName, vector<string> where);//função que faz select em uma tabela, efetua update no parameters da tableName conforme o where

bool deleteItem(string fileName,string itemName);//função que deleta uma tablespace, tabela ou banco de dados

bool updateTable(string colName, string tableName, vector<Condition> where, string value);//função que atualiza uma tabela

bool deleteFromTable(string tableName, vector<Condition> where);//função que deleta uam tupla da tabela

bool setDefaultDb(Database defaultDb);//função que seta o banco que está sendo trabalhado

bool dropTable(string tableName);//função que dropa uma tabela
