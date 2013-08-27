//
//  sgbdenio.h
//  sgbdenio
//
//  Created by Rodrigo on 13/08/13.
//  Copyright (c) 2013 uffs. All rights reserved.
//
/*
 #include <stdlib.h>
 #include <iostream>
 #include <string>
 #include <fstream>
 #include <ostream>
 #include <vector>
 #include <sstream>
 #include <utility>
 #include <dirent.h>
 #include <limits.h>
 #include <unistd.h>
 #include <stdio.h>
 #ifdef WIN32 || _WIN32
 #include <direct.h>
 #define MKDIR(a) _mkdir(a)
 #else
 #include <sys/stat.h>
 #define MKDIR(a) mkdir(a, 0777)  //Aqui o 0777 define o modo como igual ao umask, ou seja as permissões que resultariam de um mkdir na shell
 #endif
 //#include "sgbdenio.cpp"

 #define tsdefault getCurrentPath() + "/ts_default"
 #define tspath "tablespace.data"
 #define dbpath "database.data"
 #define columnsPath "columns.data"
 #define tablesPath "tables.data"
 #define pksPath "pks.data"
 #define fksPath "fks.data"

 #define separator "|>#<|"

 #ifndef sgbdenio_sgbdenio_h
 #define sgbdenio_sgbdenio_h
 #endif

 #define log 1 // se for 1 imprime mensagens de debug
 */
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

bool insert(vector<string> values, string tableName); // insert table

int checkDigit(string palavra);

bool checkType(string palavra,int type);

vector<vector<string> > select(vector<string> parameters, string tableName, vector<string> where);

bool deleteItem(string fileName,string itemName);
