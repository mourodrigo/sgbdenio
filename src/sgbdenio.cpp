
//============================================================================
// Name        : sgbdenio.cpp
// Author      : Rodrigo Bueno Tomiosso & Andrey Baumhardt Ramos
// Version     :
// Copyright   : wtfpl
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "sgbdenio.h"




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
    
    if(log){cout << "Arquivo encontrado." << endl;}
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
        if(log){ cout << "Arquivo não encontrado." << endl;}
        Tablespace tsReaded(-1,"","");
        return tsReaded;
    }
    
    
    
}

vector<Database> getAllDatabase(){
	vector <Database> dbs;
	if(fileExists(dbpath)){
		if(log){ cout << "Arquivo de banco de dados ja existe fazendo leitura";}
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
            if(log){   cout << "Erro ao abrir arquivo do banco de dados"; }
            return dbs;
		}
        
	}else{
        if(log){ 	cout << "arquivo nao existe";}
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
                if(log){ cout << "Tablespace encontrada" << endl;}
                location = tsReturn.getLocation()+"/"+newdb.getName();
                result = MKDIR(location.c_str());
                if (result == -1)
                    return false;
            }else{
                if(log){ cout << "Tablespace nao encontrada" << endl;}
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
                if(log){  cout << "Tablespace encontrada" << endl;}
                location = tsReturn.getLocation()+"/"+newdb.getName();
                result = MKDIR(location.c_str());
                if (result == -1)
                    return false;
            }else{
                if(log){  cout << "Tablespace nao encontrada" << endl;}
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
            if(log){ cout << "Erro ao abrir arquivo de metadados da tablespace";}
            return tsData;
		}
        
	}else{
		if(log){ cout << "arquivo nao existe";}
	}
    return tsData;
}

bool createTableSpace(Tablespace newts){
    int result;
    ofstream file;
    if (fileExists(tspath)){
        if(log){  cout << "Arquivo DATA da Tablespace existe" << endl;}
        vector <Tablespace> tsData;
        tsData = getAllTableSpace();
        if(log){ cout <<"Tamanho do vetor TS de retorno: "<< tsData.size() << endl;}
        for (int i=0; i<tsData.size();i++){
            if(newts.getName() == tsData.at(i).getName()){
                if(log){ cout << "Tablespace já existe" << endl;}
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
        if(log){ cout << "Arquivo DATA da TableSpace nao existe" << endl;}
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

string getPathFromDatabase(int dbId){
    vector <Database> dbReaded = getAllDatabase();
    for (int i=0;i<dbReaded.size();i++){
        if (dbId == dbReaded.at(i).getId()){
            string path = getPathFromTableSpace(dbReaded.at(i).getTablespace());
            path = path + "/" + dbReaded.at(i).getName();
            return path;
        }
        
    }
    if(log){ cout << "Database inexistente. " << endl;}
    return "";
}

vector<Table> getAllTables(){
	vector <Table> tablesDatas;
	if(fileExists(tablesPath)){
		if(log){ cout << "Arquivo de banco de dados ja existe fazendo leitura";}
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
            if(log){  cout << "Erro ao abrir arquivo de metadados da tablespace"; }
            return tablesDatas;
		}
        
	}else{
		if(log){ cout << "arquivo nao existe"; }
	}
    return tablesDatas;
}

vector<Column> getAllColumns(int newTableId){
	vector <Column> colDatas;
	if(fileExists(columnsPath)){
		if(log){ cout << "Arquivo de banco de dados ja existe fazendo leitura";}
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
                            
                        }
                    }
                    
                }
		    }
            
            file.close();
            return colDatas;
		}else{
            if(log){ cout << "Erro ao abrir arquivo de metadados da tablespace";}
            return colDatas;
		}
        
	}else{
		if(log){ cout << "arquivo nao existe";}
	}
    
    return colDatas;
}

vector <Primary> getAllPrimary(int idPrimary){
    vector <Primary> primaryDatas;
	if(fileExists(pksPath)){
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
                    
                    
                    if (idPrimary==-1) {
                        Primary primaryReaded(id,name,table,order);
                        primaryDatas.push_back(primaryReaded);
                    }else{
                        if (idPrimary == id) {
                            Primary primaryReaded(id,name,table,order);
                            primaryDatas.push_back(primaryReaded);
                            break;
                        }
                    }
                    
                    
		        }
		    }
            
            file.close();
            return primaryDatas;
		}else{
            if(log){  cout << "Erro ao abrir arquivo de metadados da tablespace";}
            return primaryDatas;
		}
        
	}else{
		if(log){ cout << "arquivo nao existe";}
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
                        if(log){ cout << "Tabela ja existe" << endl;}
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
                fileTable.open(newTablePath.c_str());
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
                primaryReaded = getAllPrimary(-1);
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
                fileTable.open(newTablePath.c_str());
                fileTable.close();
                
                ofstream fileMeta;
                fileMeta.open(columnsPath);
                for (int x = 0; x < columns.size(); x++) {
                    fileMeta << columns.at(x).getPk() << separator << columns.at(x).getSerial() << separator << columns.at(x).getName() << separator << columns.at(x).getType() << separator << columns.at(x).getSize() << separator << columns.at(x).getOptional() << separator << columns.at(x).getFk() << separator << 0 << "\n" ;
                }
                fileMeta.close();
                
                ofstream filepks;
                filepks.open(pksPath);
                int contOrdem = 1;
                for (int x = 0; x < columns.size(); x++) {
                    if(columns.at(x).getPk()){
                        filepks << 0 << separator << columns.at(x).getName() << separator << newTable.getName() << separator << contOrdem << "\n" ;
                        contOrdem++;
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

vector<Foreing> getAllFks(){
    vector<Foreing> fks;
    if (fileExists(fksPath)) {
        string line;
		ifstream file (fksPath);
		if (file.is_open()){
            while ( file.good() ){
		    	getline (file,line);
		        if(line != "\0"){//SE A LINHA FOR VAZIA ENT√O N√O FAZ ISSO, APARENTEMENTE TAVA DNADO ERRO PQ PEGAVA LIXO
                    vector <string> pkline;
                    pkline = explode(line, separator);
                    
                    int id = atoi(pkline.at(0).c_str());//CONVERTE STRING PARA INTEIRO
                    int fk = atoi(pkline.at(1).c_str());//CONVERTE STRING PARA INTEIRO
                    
                    Foreing newforeing(id, fk);
                    fks.push_back(newforeing);
                }
		    }
            
            file.close();
            return fks;
        }else{
            return fks;
        }
        return fks;
    }
    return fks;
}

bool setForeingKey(Column col, int pk){
    
    if (pk != -1){
        vector <Primary> pkData = getAllPrimary(-1);
        for (int x=0; x<pkData.size();x++){
            if (pk == pkData.at(x).getId()){
                if (log) {cout << "ID " << pk <<" existe na tabela PK.data" << endl;}
                vector <Column> columnData = getAllColumns(-1);
                for(int x1=0;x1<columnData.size();x1++){
                    if (col.getName() == columnData.at(x1).getName()){
                        if (log) { cout << "Coluna "<<col.getName() << " existe no arquivo Columns.data." << endl;}
                        if (fileExists(fksPath)){//Se o arquivo existe faz uma destas duas coisas
                            vector<Foreing> fks = getAllFks();
                            if (columnData.at(x1).getFk()== -1){
                                if (log) {cout << "Coluna ainda sem FK setada" << endl;}
                                int newFkId = fks.at(fks.size()-1).getId()+1;
                                if (log) { cout << "Novo id FK: " << newFkId << endl;}
                                Foreing newFK(newFkId,pk);
                                fks.push_back(newFK);
                                ofstream filefks;
                                filefks.open(fksPath);
                                for(int x2=0;x2<fks.size();x2++){
                                    filefks << fks.at(x2).getId() << separator << fks.at(x2).getFk() << "\n";
                                }
                                filefks.close();
                                ofstream fileC;
                                fileC.open(columnsPath);
                                for (int x2=0;x2<columnData.size();x2++){
                                    if(columnData.at(x1).getName() == columnData.at(x2).getName()){
                                        columnData.at(x2).setFk(newFkId);
                                    }
                                    fileC << columnData.at(x2).getPk() << separator << columnData.at(x2).getSerial() << separator << columnData.at(x2).getName() << separator << columnData.at(x2).getType() << separator << columnData.at(x2).getSize() << separator << columnData.at(x2).getOptional() << separator << columnData.at(x2).getFk() << separator << columnData.at(x2).gettableId() << "\n" ;
                                }
                                filefks.close();
                                return true;
                                
                            }else{
                                if (log) {cout << "Coluna com FK setada, valor deve ser mudado em FK Data" << endl;}
                                vector<Foreing> fks = getAllFks();
                                ofstream filefks;
                                filefks.open(fksPath);
                                for (int i=0;i<fks.size();i++){
                                    if (fks.at(i).getId() == columnData.at(x1).getFk()){
                                        fks.at(i).setFk(pk);
                                    }
                                    filefks << fks.at(i).getId() << separator << fks.at(i).getFk() << "\n" ;
                                }
                                filefks.close();
                                return true;
                            }
                            
                            
                        }else{//Senão cria o arquivo
                            if (log) {cout << "Arquivo FK.DATA inexistente. Sendo criado..."<<endl;}
                            ofstream filefks;
                            filefks.open(fksPath);
                            filefks << 0 << separator << pk << "\n" ;
                            filefks.close();
                            ofstream fileC;
                            fileC.open(columnsPath);
                            for (int x2=0;x2<columnData.size();x2++){
                                if(columnData.at(x1).getName() == columnData.at(x2).getName()){
                                    columnData.at(x2).setFk(0);
                                }
                                fileC << columnData.at(x2).getPk() << separator << columnData.at(x2).getSerial() << separator << columnData.at(x2).getName() << separator << columnData.at(x2).getType() << separator << columnData.at(x2).getSize() << separator << columnData.at(x2).getOptional() << separator << columnData.at(x2).getFk() << separator << columnData.at(x2).gettableId() << "\n" ;
                            }
                            filefks.close();
                            return true;
                        }
                    }
                    
                    
                }
                if(log){ cout << "Saiu do FOR das colunas, Coluna inexistente" << endl;}
                return false;
            }
            
            
        }
        if(log){  cout << "Saiu do FOR das primary keys, PK inexistente" << endl;}
        return false;
        
    }else {
        return false;
    }
    
}

