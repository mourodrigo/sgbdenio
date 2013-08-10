//============================================================================
// Name        : sgbdenio.cpp
// Author      : Rodrigo Bueno Tomiosso & Andrey Baumhardt Ramos
// Version     :
// Copyright   : wtfpl
// Description : Hello World in C++, Ansi-style
//============================================================================


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

using namespace std;

#define tsdefault getCurrentPath() + "/ts_default"
#define tspath "tablespace.data"
#define dbpath "database.data"
#define columnsPath "columns.data"
#define tablesPath "tables.data"
#define pksPath "pks.data"

#define separator "|>#<|"
#define log 1

class Primary{
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

class Table{
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

class Database{ //classe do tipo database
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

class Column{
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

class Tablespace{
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
#pragma mark - stringManagement


vector<string> explode( const string& s, const string& delimiter ){ //explode
    vector<string> result;
    string::size_type from = 0;
    string::size_type to = 0;
    
    while ( to != string::npos ){
        to = s.find( delimiter, from );
        if ( from < s.size() && from != to ){
            result.push_back( s.substr( from, to - from ) );
        }
        from = to + delimiter.size();
    }
    return result;
}

bool ToBool( const std::string & s ) { //converte string para bool
    return s.at(0) == '1';
}

bool stringIsBool(string stringbool){
	if(stringbool=="1"){
        return  true;
	} else {
        return false;
	}
}

string getCurrentPath(){
	char *cwd;
	string str;
	stringstream ss;
    if ((cwd = getcwd(NULL, 64)) == NULL) {
        return str;
    }else{
        ss << cwd;
        ss >> str;
        return str;
    }
}

#pragma mark - filemanager

bool fileExists(const char *filename){ //verifica se arquivo existe
    ifstream ifile(filename);
    if (ifile) {
        return true;
    }else{
        return false;
    }
    
}

#pragma mark -sgbd
Tablespace checkTablespace(int idTS){
    
    //cout << "Arquivo encontrado." << endl;
    string line;
    ifstream file (tspath);
    if (file.is_open()){
        while ( file.good() ){
            getline (file,line);
            if(line != "\0"){//SE A LINHA FOR VAZIA ENT√O N√O FAZ ISSO, APARENTEMENTE TAVA DNADO ERRO PQ PEGAVA LIXO
                vector <string> tsline;
                tsline = explode(line, separator);
                int id;
                id = atoi(tsline.at(0).c_str());//CONVERTE STRING PARA INTEIRO
                if(idTS == id){
                    string name = tsline.at(1);//
                    string location = tsline.at(2);
                    Tablespace tsReaded(id,name,location);
                    file.close();
                    return tsReaded;
                }
            }
        }
        Tablespace tsReaded(-1,"","");
        file.close();
        return tsReaded;
    }else{
        cout << "Arquivo não encontrado." << endl;
        Tablespace tsReaded(-1,"","");
        return tsReaded;
    }
    
    
    
}

vector<Database> getAllDatabase(){
	vector <Database> dbs;
	if(fileExists(dbpath)){
		//cout << "Arquivo de banco de dados ja existe fazendo leitura";
		string line;
		ifstream file (dbpath);
		if (file.is_open()){
            while ( file.good() ){
		    	getline (file,line);
		        if(line != "\0"){//SE A LINHA FOR VAZIA ENT√O N√O FAZ ISSO, APARENTEMENTE TAVA DNADO ERRO PQ PEGAVA LIXO
                    vector <string> databaseline;
                    databaseline = explode(line, separator);
                    int id;
                    id = atoi(databaseline.at(0).c_str());//CONVERTE STRING PARA INTEIRO
                    string name = databaseline.at(1);//
                    int tsID = atoi(databaseline.at(2).c_str());
                    bool defaultDb = stringIsBool(databaseline.at(3));
                    Database dbReaded(id,name,tsID,defaultDb);
                    dbs.push_back(dbReaded);
		        }
		    }
            
            file.close();
            
            return dbs;
		}else{
            cout << "Erro ao abrir arquivo do banco de dados";
            return dbs;
		}
        
	}else{
		cout << "arquivo nao existe";
	}
    return dbs;
}

bool createDatabase(Database newdb){
    
	//int dbid = 0;
    //dbid = newdb.getId();
    
	if(newdb.getName().length() == 0){
		return false;
	}
	string location;
    int result;
    
	if(fileExists(dbpath)){
		vector <Database> dbs;
	    dbs = getAllDatabase();
     
        // int indexIdNewDatabase = dbs.size()+1;
        if(newdb.getDefault()){
            for (int x = 0; x<dbs.size(); x++){
            	if(dbs.at(x).getDefault()){
            		dbs.at(x).setDefault(0);
            	}
            }
            
        }
        
        
    	if(newdb.getTablespace() == 0){
    		location = tsdefault + "/" + newdb.getName();
    		result = MKDIR(location.c_str());
    		if (result == -1)
                return false;
        }else{
            Tablespace tsReturn = checkTablespace(newdb.getTablespace());;
            if(tsReturn.getId() != -1){
                cout << "Tablespace encontrada" << endl;
                location = tsReturn.getLocation()+"/"+newdb.getName();
                result = MKDIR(location.c_str());
                if (result == -1)
                    return false;
            }else{
                cout << "Tablespace nao encontrada" << endl;
                return false;
            }
        }
        
        
        
        newdb.setId(dbs.at(dbs.size()-1).getId()+1);
        dbs.push_back(newdb);
        
        ofstream file;
        
        file.open(dbpath);
        
        for (int x = 0; x<dbs.size(); x++){
    		file << dbs.at(x).getId() << separator << dbs.at(x).getName() << separator << dbs.at(x).getTablespace()  << separator << dbs.at(x).getDefault() << "\n";
        }
        
        file.close();
        
        /*      string strPath = newdb.getDir();
         
         cout << "\n\n\n a criar " << strPath << endl;
         
         MKDIR(strPath.c_str());
         
         if(log){cout << "Bando de dados " << newdb.getName() << " com id 0 no diretorio: \n " << newdb.getDir() << "\n  default 1 " << endl;} //inserção no arquivo esta ok
         */
        
        return true;
	}else{
	    ofstream file;
		file.open(dbpath);
        if(newdb.getTablespace() == 0){
    		location = tsdefault + "/" + newdb.getName();
    		result = MKDIR(location.c_str());
    		if (result == -1)
                return false;
        }else{
            Tablespace tsReturn = checkTablespace(newdb.getTablespace());;
            if(tsReturn.getId() != -1){
                cout << "Tablespace encontrada" << endl;
                location = tsReturn.getLocation()+"/"+newdb.getName();
                result = MKDIR(location.c_str());
                if (result == -1)
                    return false;
            }else{
                cout << "Tablespace nao encontrada" << endl;
                return false;
            }
        }
        
		file << 0 << separator << newdb.getName() << separator << newdb.getTablespace()  << separator << 1 << "\n";
		file.close();
        
        if(log){cout << "Banco de dados " << newdb.getName() << " com id 0 no diretorio: \n " << newdb.getTablespace() << "\n  default 1 " << endl;} //inserção no arquivo esta ok
        
        
		return true;
	}
}

Database getDefaultDb(){
    if(fileExists(dbpath)){
        vector <Database> dbs;
        dbs = getAllDatabase();
        for (int x = 0; x<dbs.size(); x++){
            if(dbs.at(x).getDefault()){
                return dbs.at(x);
            }
        }
    }
    return  Database(-1, "", -1, false); //nao consigo retornar null
}

vector<Tablespace> getAllTableSpace(){
	vector <Tablespace> tsData;
	if(fileExists(tspath)){
		//cout << "Arquivo de banco de dados ja existe fazendo leitura";
		string line;
		ifstream file (tspath);
		if (file.is_open()){
            while ( file.good() ){
		    	getline (file,line);
		        if(line != "\0"){//SE A LINHA FOR VAZIA ENT√O N√O FAZ ISSO, APARENTEMENTE TAVA DNADO ERRO PQ PEGAVA LIXO
                    vector <string> tsline;
                    tsline = explode(line, separator);
                    int id;
                    id = atoi(tsline.at(0).c_str());//CONVERTE STRING PARA INTEIRO
                    string name = tsline.at(1);//
                    string location = tsline.at(2);
                    
                    Tablespace tsReaded(id,name,location);
                    tsData.push_back(tsReaded);
		        }
		    }
            
            file.close();
            return tsData;
		}else{
            cout << "Erro ao abrir arquivo de metadados da tablespace";
            return tsData;
		}
        
	}else{
		cout << "arquivo nao existe";
	}
    return tsData;
}

bool createTableSpace(Tablespace newts){
    int result;
    ofstream file;
    if (fileExists(tspath)){
        cout << "Arquivo DATA da Tablespace existe" << endl;
        vector <Tablespace> tsData;
        tsData = getAllTableSpace();
        cout <<"Tamanho do vetor TS de retorno: "<< tsData.size() << endl;
        for (int i=0; i<tsData.size();i++){
            if(newts.getName() == tsData.at(i).getName()){
                //cout << "Tablespace já existe" << endl;
                return false;
            }
        }
        if(newts.getLocation().length() == 0){
    		newts.setLocation(getCurrentPath()+"/"+"ts_"+newts.getName());
    	}else{
            newts.setLocation(newts.getLocation()+"/"+"ts_"+newts.getName());
        }
        
        newts.setID(tsData.at(tsData.size()-1).getId()+1);
        tsData.push_back(newts);
        
        result = MKDIR(newts.getLocation().c_str());
        if(result == 0){
            file.open(tspath);
            
            for (int x = 0; x<tsData.size(); x++){
                file << tsData.at(x).getId() << separator << tsData.at(x).getName() << separator << tsData.at(x).getLocation() << "\n";
            }
            
            file.close();
            return true;
        }else if(result == -1){
            return false;
        }
        
    }else {
        cout << "Arquivo DATA da TableSpace nao existe" << endl;
        Tablespace tsdef(0,"default",getCurrentPath()+"/ts_default");
        MKDIR(tsdef.getLocation().c_str());
        file.open(tspath);
        if(newts.getLocation().length() == 0){
    		newts.setLocation(getCurrentPath()+"/"+"ts_"+newts.getName());
    	}else{
            newts.setLocation(newts.getLocation()+"/"+"ts_"+newts.getName());
        }
        result = MKDIR(newts.getLocation().c_str());
		file << 0 << separator << tsdef.getName() << separator << tsdef.getLocation()  << "\n";
		file << 1 << separator << newts.getName() << separator << newts.getLocation()  << "\n";
		file.close();
		if(result == 0){
            return true;
        }else if(result == -1){
            return false;
        }
    }
    return false;
}

string getPathFromTableSpace(int idTs){
    vector <Tablespace> tbs = getAllTableSpace();
    
    for (int x = 0; x < tbs.size(); x++) {
        if (tbs.at(x).getId()==idTs) {
            return tbs.at(x).getLocation();
        }
    }
    return "";
}

vector<Table> getAllTables(){
	vector <Table> tablesDatas;
	if(fileExists(tablesPath)){
		//cout << "Arquivo de banco de dados ja existe fazendo leitura";
		string line;
		ifstream file (tablesPath);
		if (file.is_open()){
            while ( file.good() ){
		    	getline (file,line);
		        if(line != "\0"){//SE A LINHA FOR VAZIA ENT√O N√O FAZ ISSO, APARENTEMENTE TAVA DNADO ERRO PQ PEGAVA LIXO
                    vector <string> tsline;
                    tsline = explode(line, separator);
                    
                    int id = atoi(tsline.at(0).c_str());//CONVERTE STRING PARA INTEIRO
                    string name = tsline.at(1);//
                    int idDatabase = atoi(tsline.at(2).c_str());//CONVERTE STRING PARA INTEIRO
                    
                    Table tableReaded(id,name,idDatabase);
                    tablesDatas.push_back(tableReaded);
		        }
		    }
            
            file.close();
            return tablesDatas;
		}else{
            cout << "Erro ao abrir arquivo de metadados da tablespace";
            return tablesDatas;
		}
        
	}else{
		cout << "arquivo nao existe";
	}
    return tablesDatas;
}

vector<Column> getAllColumns(int newTableId){
	vector <Column> colDatas;
	if(fileExists(columnsPath)){
		//cout << "Arquivo de banco de dados ja existe fazendo leitura";
		string line;
		ifstream file (columnsPath);
		if (file.is_open()){
            while ( file.good() ){
		    	getline (file,line);
		        if(line != "\0"){//SE A LINHA FOR VAZIA ENT√O N√O FAZ ISSO, APARENTEMENTE TAVA DNADO ERRO PQ PEGAVA LIXO
                    vector <string> tsline;
                    tsline = explode(line, separator);
                    
                    bool pk = atoi(tsline.at(0).c_str());
                    bool serial = stringIsBool(tsline.at(1));
                    string name = tsline.at(2);
                    int type = atoi(tsline.at(3).c_str());
                    int size = atoi(tsline.at(4).c_str());
                    bool optional = stringIsBool(tsline.at(5).c_str());
                    int fk = atoi(tsline.at(6).c_str());
                    int tableId = atoi(tsline.at(7).c_str());
                    
    //                Column(bool newPk, bool newSerial, string newName, int newType, int newSize, bool newOptional, int newFk, int newTableId){
                    
                    if (newTableId==-1) {
                        Column columnReaded(pk, serial, name, type, size, optional, fk, tableId);
                        colDatas.push_back(columnReaded);
                    }else{
                        if (newTableId == tableId) {
                            Column columnReaded(pk, serial, name, type, size, optional, fk, tableId);
                            colDatas.push_back(columnReaded);
                            break;
                        }
                    }
                    
                }
		    }
            
            file.close();
            return colDatas;
		}else{
            cout << "Erro ao abrir arquivo de metadados da tablespace";
            return colDatas;
		}
        
	}else{
		cout << "arquivo nao existe";
	}
    
    return colDatas;
}

vector <Primary> getAllPrimary(){
    vector <Primary> primaryDatas;
	if(fileExists(pksPath)){
		//cout << "Arquivo de banco de dados ja existe fazendo leitura";
		string line;
		ifstream file (pksPath);
		if (file.is_open()){
            while ( file.good() ){
		    	getline (file,line);
		        if(line != "\0"){//SE A LINHA FOR VAZIA ENT√O N√O FAZ ISSO, APARENTEMENTE TAVA DNADO ERRO PQ PEGAVA LIXO
                    vector <string> pkline;
                    pkline = explode(line, separator);
                    
                    int id = atoi(pkline.at(0).c_str());//CONVERTE STRING PARA INTEIRO
                    string name = pkline.at(1);//
                    string table = pkline.at(2);
                    int order = atoi(pkline.at(3).c_str());//CONVERTE STRING PARA INTEIRO
                    
                    Primary primaryReaded(id,name,table,order);
                    primaryDatas.push_back(primaryReaded);
		        }
		    }
            
            file.close();
            return primaryDatas;
		}else{
            cout << "Erro ao abrir arquivo de metadados da tablespace";
            return primaryDatas;
		}
        
	}else{
		cout << "arquivo nao existe";
	}
    return primaryDatas;
    
}

bool createTable(Table newTable, vector<Column> columns){
    vector<Database> dbs;
    dbs = getAllDatabase();
    
    if (newTable.getName().length()==0) {
        if (log) { cout << "Nome em branco" << endl; }
        return false;
    }
    
        for (int x = 0; x<dbs.size(); x++) {
            if (dbs.at(x).getId()==newTable.getDatabase()) {
                //if (log) {cout << "banco selecionado " << dbs.at(x).getName() << endl;}
                
                string tablespace = getPathFromTableSpace(dbs.at(x).getId())+"/";
            
                string newTablePath = tablespace+dbs.at(x).getName()+"/"+newTable.getName()+".data";
                
                if (fileExists(tablesPath)) {
                    //cout << getAllTables().at(0).getId() << " -- " << getAllTables().at(0).getName() << " -- " << getAllTables().at(0).getDatabase() << endl;
                    vector <Table> tableReturn;
                    tableReturn = getAllTables();
                    for (int x=0;x<tableReturn.size();x++){
                        cout << newTable.getName() << " <> "<< tableReturn.at(x).getName() << endl;
                        if(newTable.getName() == tableReturn.at(x).getName()){
                            cout << "Tabela ja existe" << endl;
                            return false;
                        }
                        
                    }
                    
                    newTable.setId(tableReturn.at(tableReturn.size()-1).getId()+1);//incrementa o id da nova tabela conforme o id atual + 1
                    tableReturn.push_back(newTable);
                    ofstream fileTables;
                    fileTables.open(tablesPath);
                    for (int x = 0; x< tableReturn.size();x++){
                        fileTables << tableReturn.at(x).getId() << separator << tableReturn.at(x).getName() << separator << tableReturn.at(x).getDatabase() << "\n" ;
                    }
                    fileTables.close();
                    ofstream fileTable;
                    fileTable.open(newTablePath);
                    fileTable.close();
                
                    vector <Column> columnsReaded = getAllColumns(-1);
                    for (int x = 0; x < columns.size(); x++) {
                        if (log) {
                            cout << "fk: "<< columnsReaded.at(x).getFk() << " -- name: " << columnsReaded.at(x).getName()  << " -- optional: " << columnsReaded.at(x).getOptional()  << " -- pk: " << columnsReaded.at(x).getPk()  << " -- serial: " << columnsReaded.at(x).getSerial()  << " -- size: " << columnsReaded.at(x).getSize()  << " -- getid:  " << columnsReaded.at(x).gettableId()  << " -- gettype:  " << columnsReaded.at(x).getType() << endl;
                        }
                        columns.at(x).settableId(newTable.getId());
                        columnsReaded.push_back(columns.at(x));
                    }
                    
                    
                    ofstream fileColumn;
                    fileColumn.open(columnsPath);
                    
                    
                    for (int x = 0; x < columnsReaded.size(); x++) {
                        fileColumn << columnsReaded.at(x).getPk() << separator << columnsReaded.at(x).getSerial() << separator << columnsReaded.at(x).getName() << separator << columnsReaded.at(x).getType() << separator << columnsReaded.at(x).getSize() << separator << columnsReaded.at(x).getOptional() << separator << columnsReaded.at(x).getFk() << separator << columnsReaded.at(x).gettableId() << "\n" ;
                        
                    }
                    
                    fileColumn.close();
                    vector <Primary> primaryReaded;
                    primaryReaded = getAllPrimary();
                    int newPkId = primaryReaded.at(primaryReaded.size()-1).getId()+1;
                    int cont = 1;
                    for (int x = 0; x < columns.size(); x++) {
                        if(columns.at(x).getPk()){
                            Primary pkTable(newPkId, columns.at(x).getName(), newTable.getName(), cont) ;
                            primaryReaded.push_back(pkTable);
                            cont++;
                        }
                    }
                    ofstream filepks;
                    filepks.open(pksPath);
                    for(int x=0;x<primaryReaded.size();x++){
                        filepks << primaryReaded.at(x).getId() << separator << primaryReaded.at(x).getName() << separator << primaryReaded.at(x).getTable() << separator << primaryReaded.at(x).getOrder() << "\n" ;
                    }
                    filepks.close();
                    
                    
                    return true;
                    
                    
                }else{

                    ofstream fileTables;
                    fileTables.open(tablesPath);
                    fileTables << 0 << separator << newTable.getName() << separator << newTable.getDatabase() << "\n" ;
                    fileTables.close();
                    ofstream fileTable;
                    fileTable.open(newTablePath);
                    fileTable.close();
                    
                    ofstream fileMeta;
                    fileMeta.open(columnsPath);
                    for (int x = 0; x < columns.size(); x++) {
                        fileMeta << columns.at(x).getPk() << separator << columns.at(x).getSerial() << separator << columns.at(x).getName() << separator << columns.at(x).getType() << separator << columns.at(x).getSize() << separator << columns.at(x).getOptional() << separator << columns.at(x).getFk() << separator << 0 << "\n" ;
                    }
                    fileMeta.close();
                    
                    ofstream filepks;
                    filepks.open(pksPath);
                    int cont = 1;
                    for (int x = 0; x < columns.size(); x++) {
                        if(columns.at(x).getPk()){
                            filepks << 0 << separator << columns.at(x).getName() << separator << newTable.getName() << separator << cont << "\n" ;
                            cont++;
                        }
                    }
                    filepks.close();
                    
                    
                    return true;
                }
                
                
            }
        }
    
    
    if (log) { cout << "banco nao existe" << endl; }
    return false;
}



#pragma globals

Database defaultDb = getDefaultDb();  //variavel global? aqui nao funcionou


int main() {
    
    /*
    
    bool result;
    Tablespace newTS(0,"tablespace0","");
    result = createTableSpace(newTS);

    Tablespace newTS1(0,"tablespace1","/Users/rodrigo/Desktop");
    result = createTableSpace(newTS1);

    Tablespace newTS2(0,"tablespace2","/Users/rodrigo/Desktop");
    result = createTableSpace(newTS2);

    Database db(6666,"loja",0,true);
    createDatabase(db);

    Database db1(6666,"locadora",1,true);
    createDatabase(db1);

    Database db3(6666,"revendedora",3,false);
    createDatabase(db3);

    */
    
    
    
    
    
    Table tabelacliente(0,"cliente", 1);
    vector <Column> colunasTabelaCliente;
    
    //     Column(bool newPk, bool newSerial, string newName, int newType, int newSize, bool newOptional, string newValue, int newFk, int newTableId){
    
    Column idCliente(true, true, "idCliente", 0, 10, false, -1, -1);
    Column nomeCliente(false, false, "nomeCliente", 255, 255, false, -1, -1);
    Column cpfCliente(false, false, "cpfCliente", 0, 30, false, -1, -1);
    Column especialCliente(false, false, "especialCliente", 2, 1, true, -1, -1);
    
    
     
    colunasTabelaCliente.push_back(idCliente);
    colunasTabelaCliente.push_back(nomeCliente);
    colunasTabelaCliente.push_back(cpfCliente);
    colunasTabelaCliente.push_back(especialCliente);

    createTable(tabelacliente, colunasTabelaCliente);
    
    
    
    
    
    
    
    Table tabelafilme(0,"filme", 1);
    vector <Column> colunasTabelaFilme;
    
    //     Column(bool newPk, bool newSerial, string newName, int newType, int newSize, bool newOptional, string newValue, int newFk, int newTableId){
    
    Column idFilme(true, true, "idFilme", 0, 10, false, -1, -1);
    Column nomeFilme(false, false, "nomeFilme", 1, 255, false, -1, -1);
    Column diretor(false, false, "diretor", 1, 255, true, -1, -1);
    Column locado(false, false, "locado", 2, 1, false, -1, -1);
    
    
    colunasTabelaFilme.push_back(idFilme);
    colunasTabelaFilme.push_back(nomeFilme);
    colunasTabelaFilme.push_back(diretor);
    colunasTabelaFilme.push_back(locado);
    
    createTable(tabelafilme, colunasTabelaFilme);
    
    /*

    Table tabelalocacao(0,"locacao", 1);
    vector <Column> colunasTabelalocacao;
    
    //     Column(bool newPk, bool newSerial, string newName, int newType, int newSize, bool newOptional, string newValue, int newFk, int newTableId){
    
    Column idLocacao(true, true, "idLocacao", 0, 10, false, -1, -1);
    Column idFilme(false, false, "idFilme", 1, 255, false, -1, -1);
    Column idCliente(false, false, "idCliente", 1, 255, true, -1, -1);
    Column dataLocacao(false, false, "locado", 2, 1, false, -1, -1);
    
    
    colunasTabelaFilme.push_back(idFilme);
    colunasTabelaFilme.push_back(nomeFilme);
    colunasTabelaFilme.push_back(diretor);
    colunasTabelaFilme.push_back(locado);
    
    createTable(tabelalocacao, colunasTabelalocacao);
*/
    
//    Table tabelalocacao(0,"locacao", 1);
    
    
//    Table tabelafilme(0,"filme", 1);
    
    
    
    
    
    //cout << "db default: \n" << defaultDb.getId() << " - " << defaultDb.getName() << " - " << defaultDb.getTablespace();
    
    
    
	//ABAIXO COMENTARIOS PARA NAO ESQUECER A SINTAXE DAS COISAS
    
    
    //	vector<Database> dbs; //vetor de classes do tipo database
    
    
    //	cout << "Hello" << endl; // prints Hello
    
    /*
     cout << "ints size: " << ints.size() << endl;
     ints.push_back(123);
     cout << "ints size: " << ints.size() << " value: "<< ints.at(0) << endl;
     ints.pop_back();
     cout << "ints size: " << ints.size() << endl;
     */
    
    /*
     Database db1(1,"banco1","/var/www/",true);  //instancia db1 do tipo database e seta os valores através do método construtor --> Database(int newId, string newName, string newDir, bool newDefaultDb){
     Database db2(2,"banco222","/var/www/db1/",false);
     Database db3(3,"banco3333","/users/mouro/banco3/",false);
     Database db4(4,"banco44444","/root/db4",false);
     
     dbs.push_back(db1); //manda db1 pro vetor
     
     for (int x = 0; x<dbs.size(); x++){
     cout << "id: " << dbs.at(x).getId() << "name: "<< dbs.at(x).getName()  << " dir: "<< dbs.at(x).getDir() << " default: " << dbs.at(x).getDefault() << endl;
     }
     
     createDatabase(db1); //CHAMA FUNCAO CREATEDATABASE QUE POR ENQUANTO SÓ VERIFICA SE UM ARQUIVO EXISTE
     createDatabase(db2);
     createDatabase(db3);
     
     
     /*   //TENTATIVA DE GRAVAR O VETOR DE BANCOS NO ARQUIVO, AINDA NAO FUNCIONA
     
     ostream outpuf_file("dbs.data");
     std:ofstream_iterator <Database> output_iterator(outpuf_file, "\n");
     //	cout << "db " << dbs.at(2) << endl;
     */
    
    /*
     std::vector<std::string> example;
     example.push_back("this");
     example.push_back("is");
     example.push_back("a");
     example.push_back("test");
     
     std::ofstream output_file("./example.txt");
     std::ostreambuf_iterator<std::string> output_iterator_tag;
     std::copy(example.begin(), example.end(), output_iterator_tag);
     
     */
    
    //	cout << "database name: " << db1.getName() << "dir: " << db1.getDir() << endl;
    
    system("pause");
	return 0;
    
}
