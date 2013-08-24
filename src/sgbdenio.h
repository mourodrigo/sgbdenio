//
//  sgbdenio.h
//  sgbdenio
//
//  Created by Rodrigo on 13/08/13.
//  Copyright (c) 2013 uffs. All rights reserved.
//

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
#define MKDIR(a) mkdir(a, 0777)  /*Aqui o 0777 define o modo como igual ao umask, ou seja as permissões que resultariam de um mkdir na shell */
#endif


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


using namespace std;

class Primary{ //metadados de uma primary key
private:
    int id;
    string name;
    string table;
    int order;
    
public:
    int getId(){
        return this->id;
    }
    string getName(){
        return this->name;
    }
    string getTable(){
        return this->table;
    }
    int getOrder(){
        return this->order;
    }
    void setId(int newId){
        this->id = newId;
    }
    void setName(string newName){
        this->name = newName;
    }
    void setTable(string newTable){
        this->table = newTable;
    }
    void setOrder(int newOrder){
        this->order= newOrder;
    }
    Primary(int newId, string newName, string newTable,int newOrder){
        this->id = newId;
        this->name = newName;
        this->table = newTable;
        this->order = newOrder;
    }
};

class Foreing{ //metadados de uma foreing key
private:
    int id;
    int fk;
public:
    int getId(){
        return this->id;
    }
    void setId(int newId){
        this->id = newId;
    }
    int getFk(){
        return this->fk;
    }
    void setFk(int newFk){
        this->fk = newFk;
    }
    Foreing(int newId, int newFk){
        this->id = newId;
        this->fk = newFk;
    }
};

class Table{ //metadados de uma tabela
private:
    int id;
    string name;
    int dbId;
    
public:
    int getId(){
        return this->id;
    }
    string getName(){
        return this->name;
    }
    int getDatabase(){
        return this->dbId;
    }
    void setId(int newId){
        this->id = newId;
    }
    void setName(string newName){
        this->name = newName;
    }
    void setDatabase(int newDb){
        this->dbId = newDb;
    }
    
    Table(int newId, string newName, int newDb){
        this->id = newId;
        this->name = newName;
        this->dbId = newDb;
    }
};

class Database{ ///metadados de um database
private:
    int id;
    string name;
    int tsID;
    bool defaultDb;
    
public:
    int getId(){
        return this->id;
    }
    string getName(){
        return this->name;
    }
    int getTablespace(){
        return this->tsID;
    }
    bool getDefault(){
        return this->defaultDb;
    }
    void setId(int newId){
        this->id = newId;
    }
    void setName(string newName){
        this->name = newName;
    }
    void setTablespace(int newTsID){
        this->tsID = newTsID;
    }
    void setDefault(bool newDefault){
        this->defaultDb = newDefault;
    }
    
    
    Database(int newId, string newName, int newTsID, bool newDefaultDb){
        this->id = newId;
        this->name = newName;
        this->tsID = newTsID;
        this->defaultDb = newDefaultDb;
    }
};

class Column{ //metadados de uma coluna (de uma tabela)
private:
    bool pk;
    bool serial;
    string name;
    int type;
    int size;
    bool optional;
    int fk;
    int tableId;
    
public:
    bool getPk(){
        return this->pk;
    }
    
    void setPk(bool newPk){
        this->pk = newPk;
    }
    
    bool getSerial(){
        return this->serial;
    }
    
    void setSerial(bool newSerial){
        this->serial = newSerial;
    }
    
    string getName(){
        return this->name;
    }
    void setName(string newName){
        this->name = newName;
    }
    
    int getType(){
        return this->type;
    }
    void setType(int newType){
        this->type = newType;
    }
    
    int getSize(){
        return this->size;
    }
    void setSize(int newSize){
        this->size = newSize;
    }
    
    bool getOptional(){
        return this->optional;
    }
    void setOptional(bool newOptional){
        this->optional = newOptional;
    }
    
    int getFk(){
        return this->fk;
    }
    void setFk(int newFk){
        this->fk = newFk;
    }
    
    int gettableId(){
        return this->tableId;
    }
    void settableId(int newTableId){
        this->tableId = newTableId;
    }
    
    Column(bool newPk, bool newSerial, string newName, int newType, int newSize, bool newOptional, int newFk, int newTableId){
        this->pk = newPk;
        this->serial = newSerial;
        this->name = newName;
        this->type = newType;
        this->size = newSize;
        this->optional = newOptional;
        this->fk = newFk;
        this->tableId = newTableId;
    }
    
};

class Tablespace{ //metadados de uma tablespace
private:
    int id;
    string name;
    string location;
    
public:
    int getId(){
        return this->id;
    }
    string getName(){
        return this->name;
    }
    string getLocation(){
        return this->location;
    }
    void setID(int newId){
        this->id = newId;
    }
    void setName(string newName){
        this->name = newName;
    }
    void setLocation(string newLocation){
        this->location = newLocation;
    }
    
    Tablespace(int newId,string newName, string newLocation){
        this->id = newId;
        this->name = newName;
        this->location = newLocation;
    }
};



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
