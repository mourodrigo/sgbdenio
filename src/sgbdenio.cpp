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
#ifdef WIN32 //|| _WIN32
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

class Primary{ //Metadados e métodos de uma primary key
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

class Foreing{ //Metadados e métodos de uma foreing key
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

class Table{ //Metadados e métodos de uma tabela
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

class Database{ //Metadados e métodos de um database
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

class Column{ //Metadados e métodos de uma coluna (de uma tabela)
private:
    bool pk;
    int serial;
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

    int getSerial(){
        return this->serial;
    }

    void setSerial(int newSerial){
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

    Column(bool newPk, int newSerial, string newName, int newType, int newSize, bool newOptional, int newFk, int newTableId){
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

class Tablespace{ //Metadados e métodos de uma tablespace
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

class Condition{//Metadados e métodos de uma condição
private:
    string colName;
    string operatorType;
    string value;
public:
    string setColName(){
        return this->colName;
    }
    string getColName(){
        return this->colName;
    }

    string setOperatorType(){
        return this->operatorType;
    }
    string getOperatorType(){
        return this->operatorType;
    }

    string setValue(){
        return this->value;
    }
    string getValue(){
        return this->value;
    }

    Condition(string newName, string operatorType, string newValue){
        this->colName = newName;
        this->operatorType = operatorType;
        this->value = newValue;
    }
};

int checkDigit(string palavra){//Função que verifica se um número é inteiro ou float
    bool res;
    int flag = 0;
    if(palavra.at(palavra.length()-1)=='.')//Se o último caracter for um ponto é inválido
        return -1;
    for (int i=0;i<palavra.length();i++){
        if(flag > 1)
            return -1;
        if(palavra.at(i)=='.'){//Se for float então possui um ponto e entra nesta condição
            flag++;
        }else{
            res = isdigit(palavra.at(i));
            if(!res)
                return -1;
        }
    }
    return flag;
}

bool checkType(string palavra,int type){//Verifica se o tipo da string recebida é válido com o tipo passado
    //integer = 0 | float = 1 | bool = 2 | string = 3 | data = 4 | hora = 5
    int res;
    int flag = 0;
    bool resBool;
    switch(type){
        case 0:
            if(log){cout << "Entrou case 0 - integer" << endl;}
            res = checkDigit(palavra);
            if(res != 0)
                return false;
            else
                return true;
            break;
        case 1:
            if(log){cout << "Entrou case 1 - float" << endl;}
            res = checkDigit(palavra);
            if(res != 1)
                return false;
            else
                return true;
            break;
        case 2:
            if(log){cout << "Entrou case 2 - bool" << endl;}
            if((palavra == "0")||(palavra == "1"))//Verifica se o valor passado é true ou false
                return true;
            else
                return false;
            break;
        case 3:
            if(log){cout << "Entrou case 3 - string" << endl;}
            if(palavra == "\0")//Verifica se a string é nula
                return false;
            for(int i=0;i<palavra.length();i++){//Verifica se string é formada só se espaçoes, se for é inválida
                if(flag == 1)
                    return true;
                if(palavra.at(i)!=' ')
                    flag = 1;
            }
            if(flag ==0)
                return false;
            else
                return true;
            break;
        case 4:
            if(log){cout << "Entrou case 4 - data" << endl;}
            if(palavra.length()!=8){//Se for diferente de 8 o tamanho, não valida
                return false;
            }else{
                for(int i=0;i<palavra.length();i++){//Checa se todos os caracteres da string sao numeros
                    resBool = isdigit(palavra.at(i));
                    if(!resBool)
                        return false;
                }
                char ano[5],mes[3],dia[3];//Cria os vetores de character para a data
                for(int i2=0;i2<4;i2++){//Preenche o ano
                    ano[i2]=palavra.at(i2);
                }
                ano[4]='\0';//Finaliza o ano
                mes[0]=palavra.at(4);
                mes[1]=palavra.at(5);
                mes[2]='\0';//Finaliza o mes
                dia[0]=palavra.at(6);
                dia[1]=palavra.at(7);
                dia[2]='\0';//Finaliza o dia
                int mesInteger = atoi(mes);
                int diaInteger = atoi(dia);
                if(mesInteger>12 || mesInteger<1)
                    return false;
                if(diaInteger>31 || diaInteger<1)
                    return false;
                if(log){cout <<ano<<"-"<<mesInteger<<"-"<<diaInteger<< endl;}
                return true;
            }
            break;
        case 5:
            if(log){cout <<"Entrou case 5 - hora" << endl;}
            if(palavra.length()!=6){//Se o tamanho for diferente de 6 então invalida
                return false;
            }else{
                for(int i=0;i<palavra.length();i++){
                    resBool = isdigit(palavra.at(i));
                    if(!resBool)
                        return false;
                }
                char hours[3],minutes[3],seconds[3];//Cria os vetores para a hora
                for(int i2=0;i2<2;i2++){//Atribui os valores corretamente
                    hours[i2]=palavra.at(i2);
                    minutes[i2]=palavra.at(i2+2);
                    seconds[i2]=palavra.at(i2+4);
                }
                hours[2]='\0';//finaliza os 3 vetores
                minutes[2]='\0';
                seconds[2]='\0';
                int hourInteger = atoi(hours);//transforma para inteiro para comparaÁ„o
                int minutesInteger = atoi(minutes);
                int secondsInteger = atoi(seconds);
                if(hourInteger > 23 || hourInteger < 0)//checa se nenhum dos valores extrapola os valores possÌveis
                    return false;
                if(minutesInteger >59 || minutesInteger < 0)
                    return false;
                if(secondsInteger > 59 || secondsInteger < 0)
                    return false;
                if(log){cout << hours <<":"<< minutes <<":"<< seconds << endl;}
                return true;
            }
            break;
        default:
            return false;
            break;
    }
    return false;
}

vector<string> explode( const string& s, const string& delimiter ){ //Explode que divide uma string conforme o separador recebido
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

bool ToBool( const std::string & s ) { //Converte string para bool
    return s.at(0) == '1';
}

bool stringIsBool(string stringbool){//Converte um valor de string paga booleano
	if(stringbool=="1"){
        return  true;
	} else {
        return false;
	}
}

string intToString(int integer){//Converte de inteiro para string
    string Result;
    ostringstream convert;
    convert << integer;
    return convert.str();
}

string getCurrentPath(){//Retorna o diretório atual que o programa está rodando
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

bool fileExists(const char *filename){ //Verifica se arquivo existe
    ifstream ifile(filename);
    if (ifile) {
        return true;
    }else{
        return false;
    }
}

#pragma mark -sgbd
Tablespace checkTablespace(int idTS){//Função que verifica se uma tablespace existe e retorna os dados dela

    if(log){cout << "Tablespace encontrada." << endl;}
    string line;
    ifstream file (tspath);
    if (file.is_open()){
        while ( file.good() ){
            getline (file,line);
            if(line != "\0"){//Se a linha não for vazia então executa o procedimento,senão pega a outra linha
                vector <string> tsline;
                tsline = explode(line, separator);//Separa a linha
                int id;
                id = atoi(tsline.at(0).c_str());//Converte a string (id encontrado) para inteiro
                if(idTS == id){
                    string name = tsline.at(1);//Recebe a string do nome da tablespace
                    string location = tsline.at(2);//Recebe a string da localização da tablespace
                    Tablespace tsReaded(id,name,location);//Cria o objeto tablespace com os dados encontrados
                    file.close();
                    return tsReaded;
                }
            }
        }
        Tablespace tsReaded(-1,"","");//Se o arquivo não for "bom", cria um objeto tablespace vazio e retorna
        file.close();
        return tsReaded;
    }else{
        if(log){ cout << "Arquivo não encontrado." << endl;}
        Tablespace tsReaded(-1,"","");
        return tsReaded;
    }
}

vector<Database> getAllDatabase(){//Função que retorna todos os banco de dados cadastrados
	vector <Database> dbs;
	if(fileExists(dbpath)){
		if(log){ cout << "Arquivo database.data ja existe, fazendo leitura..."<<endl;}
		string line;
		ifstream file (dbpath);
		if (file.is_open()){
            while ( file.good() ){
		    	getline (file,line);
		        if(line != "\0"){//Se a linha for vazia, não executa o procedimento
                    vector <string> databaseline;
                    databaseline = explode(line, separator);
                    int id;
                    id = atoi(databaseline.at(0).c_str());//Converte para inteiro o id do bando
                    string name = databaseline.at(1);//Recebe a string do nome do banco
                    int tsID = atoi(databaseline.at(2).c_str());//Converte para inteiro o id da tablespace
                    bool defaultDb = stringIsBool(databaseline.at(3));//Converte para booleano o valor que identifica o banco default
                    Database dbReaded(id,name,tsID,defaultDb);//Cria o objeto database
                    dbs.push_back(dbReaded);//Coloca no vetor dos banco de dados
		        }
		    }
            file.close();
            return dbs;
		}else{
            if(log){ cout << "Erro ao abrir arquivo database.data"<<endl; }
            return dbs;
		}
	}else{
        if(log){ cout << "Arquivo database.data nao existe"<<endl;}
	}
    return dbs;
}

bool createDatabase(Database newdb){//Função que cria um Banco de Dados

	if(newdb.getName().length() == 0){//Se o tamanho do nome é zero, não cria
		return false;
	}
	string location;
    int result;

	if(fileExists(dbpath)){//Se o arquivo database.data já existe, então cria um vector com os Database existente
		vector <Database> dbs;
	    dbs = getAllDatabase();
       if(newdb.getDefault()){
            for (int x = 0; x<dbs.size(); x++){
            	if(dbs.at(x).getDefault()){
            		dbs.at(x).setDefault(0);
            	}
            }
        }

    	if(newdb.getTablespace() == 0){//Se o novo banco pertence a tablespace default, entra aqui para definir seu diretório de criação
    		location = tsdefault + "/" + newdb.getName();
    		result = MKDIR(location.c_str());
    		if (result == -1)//Se não foi possível criar o diretório, retorna erro
                return false;
        }else{//Senão verifica qual Tablespace que é
            Tablespace tsReturn = checkTablespace(newdb.getTablespace());//Verifica se a tablespace existe
            if(tsReturn.getId() != -1){//Se for diferente de -1 então cria seta o caminho do novo banco
                if(log){ cout << "Tablespace encontrada" << endl;}
                location = tsReturn.getLocation()+"/"+newdb.getName();
                result = MKDIR(location.c_str());
                if (result == -1)//Se não foi possível criar o diretório, retorna erro
                    return false;
            }else{//Se o getId retornado da tablespace for -1, então ela não foi encontrada
                if(log){ cout << "Tablespace nao encontrada" << endl;}
                return false;
            }
        }
        newdb.setId(dbs.at(dbs.size()-1).getId()+1);//Seta o id do novo banco baseado no último id + 1
        dbs.push_back(newdb);//Coloca o novo banco no vetor de bancos para ser gravado no arquivo

        ofstream file;
        file.open(dbpath);
        for (int x = 0; x<dbs.size(); x++){//Grava no arquivo
    		file << dbs.at(x).getId() << separator << dbs.at(x).getName() << separator << dbs.at(x).getTablespace()  << separator << dbs.at(x).getDefault() << "\n";
        }
        file.close();
        return true;
	}else{//Se o arquivo database.data não existe, então está sendo criado o primeiro banco
	    ofstream file;
		file.open(dbpath);
        if(newdb.getTablespace() == 0){//Se a TS do novo banco for a default então entra aqui
    		location = tsdefault + "/" + newdb.getName();
    		result = MKDIR(location.c_str());
    		if (result == -1)//Se não foi possível criar o diretório, retorna erro
                return false;
        }else{
            Tablespace tsReturn = checkTablespace(newdb.getTablespace());
            if(tsReturn.getId() != -1){//Se o ID retornado for diferente de -1
                if(log){  cout << "Tablespace encontrada" << endl;}
                location = tsReturn.getLocation()+"/"+newdb.getName();
                result = MKDIR(location.c_str());
                if (result == -1)//Se não foi possível criar o diretório, retorna erro
                    return false;
            }else{//Se o ID retornado for -1 então a TS não foi encontrada
                if(log){  cout << "Tablespace nao encontrada" << endl;}
                return false;
            }
        }
        //Grava a linha única no arquivo
		file << 0 << separator << newdb.getName() << separator << newdb.getTablespace()  << separator << 1 << "\n";
		file.close();

        if(log){cout << "Banco de dados " << newdb.getName() << " com id 0 no diretorio: \n " << newdb.getTablespace() << "\n  default 1 " << endl;} //inserção no arquivo esta ok
		return true;
	}
}

Database getDefaultDb(){//Função que verifica no arquivo database.data qual é o database default
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

vector<Tablespace> getAllTableSpace(){//Função que retorna um objeto Tablespace com todas as Tablespaces existentes no arquivo tablespace.data
	vector <Tablespace> tsData;
	if(fileExists(tspath)){
		if(log){cout << "Arquivo tablespace.data ja existe fazendo leitura";}
		string line;
		ifstream file (tspath);
		if (file.is_open()){
            while ( file.good() ){
		    	getline (file,line);
		        if(line != "\0"){//Se a linha for vazia então não executa o procedimento
                    vector <string> tsline;
                    tsline = explode(line, separator);
                    int id;
                    id = atoi(tsline.at(0).c_str());//Converte o ID da tablespace de string para inteiro
                    string name = tsline.at(1);//Recebe o nome da tablespace
                    string location = tsline.at(2);//Recebe a localização da tablespace

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
		if(log){ cout << "Arquivo tablespace.data nao existe";}
	}
    return tsData;
}

bool createTableSpace(Tablespace newts){//Função que cria uma Tablespace no banco de dados
    int result;
    ofstream file;
    if (fileExists(tspath)){//Se o arquivo existir entra entra nessa condição
        if(log){  cout << "Arquivo DATA da Tablespace existe" << endl;}
        vector <Tablespace> tsData;
        tsData = getAllTableSpace();//Pega todas as tablespaces existentes no arquivo
        if(log){ cout <<"Tamanho do vetor TS de retorno: "<< tsData.size() << endl;}
        for (int i=0; i<tsData.size();i++){
            if(newts.getName() == tsData.at(i).getName()){//Se o nome for igual a um ja existente, não cria
                if(log){ cout << "Tablespace já existe" << endl;}
                return false;
            }
        }
        if(newts.getLocation().length() == 0){//Se a localizzação tiver tamanho 0, entao coloca na localização default
    		newts.setLocation(getCurrentPath()+"/"+"ts_"+newts.getName());
    	}else{//Senão seta a localização para o caminho recebido
            newts.setLocation(newts.getLocation()+"/"+"ts_"+newts.getName());
        }

        newts.setID(tsData.at(tsData.size()-1).getId()+1);//Faz o ID da nova tablespace ser igual ao último id + 1
        tsData.push_back(newts);

        result = MKDIR(newts.getLocation().c_str());//Cria a pasta da tablespace
        if(result == 0){//Se foi posível criar então abre o arquivo tablespace.data e grava a nova ocorrencia junto com as antigas
            file.open(tspath);
            for (int x = 0; x<tsData.size(); x++){
                file << tsData.at(x).getId() << separator << tsData.at(x).getName() << separator << tsData.at(x).getLocation() << "\n";
            }
            file.close();
            return true;
        }else if(result == -1){//Se não foi possível criar o diretório então retorna false
            return false;
        }
    }else{//Se o arquivo tablespace.data não existir então será criado
        if(log){ cout << "Arquivo DATA da TableSpace nao existe" << endl;}
        Tablespace tsdef(0,"default",getCurrentPath()+"/ts_default");//Cria a tablespace default antes de criar a tablespace requerida pelo usuário
        MKDIR(tsdef.getLocation().c_str());//Cria a tablespace default no diretório onde o programa está rodando
        file.open(tspath);
        if(newts.getLocation().length() == 0){//Se a localização da nova TS for vazia então e a localização default
    		newts.setLocation(getCurrentPath()+"/"+"ts_"+newts.getName());
    	}else{//Senão, monta com o caminho recebido
            newts.setLocation(newts.getLocation()+"/"+"ts_"+newts.getName());
        }
        result = MKDIR(newts.getLocation().c_str());//Cria o diretório da tablespace recebida
		file << 0 << separator << tsdef.getName() << separator << tsdef.getLocation()  << "\n";//Grava os dados da TS default
		file << 1 << separator << newts.getName() << separator << newts.getLocation()  << "\n";//Grava os dados da TS recebida
		file.close();
		if(result == 0){//Se foir possível criar a pasta
            return true;
        }else if(result == -1){//Se não foi possível criar a pasta
            return false;
        }
    }
    return false;
}

string getPathFromTableSpace(int idTs){//Função que retorna o caminho para a tablespace recebida como parametro
    vector <Tablespace> tbs = getAllTableSpace();

    for (int x = 0; x < tbs.size(); x++) {
        if (tbs.at(x).getId()==idTs) {
            return tbs.at(x).getLocation();
        }
    }
    if(log){ cout << "Tablespace inexistente. " << endl;}
    return "";
}

string getPathFromDatabase(int dbId){//Função que retorna o caminho para um banco de dados que é recebido como parâmetro
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

vector<Table> getAllTables(){//Função que retorna um objeto Table com os dados da tabelas existentes no tables.data
	vector <Table> tablesDatas;
	if(fileExists(tablesPath)){
		if(log){ cout << "Arquivo tables.data ja existe, fazendo leitura...";}
		string line;
		ifstream file (tablesPath);
		if (file.is_open()){//Se o arquivo for aberto com sucesso
            while ( file.good() ){
		    	getline (file,line);
		        if(line != "\0"){//Se a linha for vazia então não executa o procedimento
                    vector <string> tsline;
                    tsline = explode(line, separator);

                    int id = atoi(tsline.at(0).c_str());//Converte o id da tabela para inteiro
                    string name = tsline.at(1);//Recebe o nome da tabela
                    int idDatabase = atoi(tsline.at(2).c_str());//Converte o id do banco de dados da tabela para inteiro

                    Table tableReaded(id,name,idDatabase);//Cria o novo objeto Table
                    tablesDatas.push_back(tableReaded);//Coloca no vetor de tables existente
		        }
		    }
            file.close();
            return tablesDatas;//Fecha o arquivo e retorna os dados lidos
		}else{//Se ocorrer erro ao abrir o arquivo
            if(log){  cout << "Erro ao abrir arquivo tables.data"; }
            return tablesDatas;
		}
	}else{//Se o arquivo não existir
		if(log){ cout << "Arquivo tables.data não existe."; }
	}
    return tablesDatas;
}

vector<Column> getAllColumns(int newTableId){//Função que retorna as colunas de uma tabela, se o id recebido for -1, retorna todas colunas
	vector <Column> colDatas;
	if(fileExists(columnsPath)){//Se o arquivo existir
		if(log){ cout << "Arquivo columns.data ja existe, fazendo leitura...";}
		string line;
		ifstream file (columnsPath);
		if (file.is_open()){
            while ( file.good() ){
		    	getline (file,line);
		        if(line != "\0"){//Se a linha for vazia, não executa o procedimento
                    vector <string> tsline;
                    tsline = explode(line, separator);

                    bool pk = atoi(tsline.at(0).c_str());//Converte para booleano se a coluna é PK
                    int serial = atoi(tsline.at(1).c_str());//Converte para inteiro o id serial da coluna(-1 se não for serial)
                    string name = tsline.at(2);//Recebe o nome da coluna
                    int type = atoi(tsline.at(3).c_str());//Converte para inteiro o tipo da coluna
                    int size = atoi(tsline.at(4).c_str());//Converte para inteiro o tamanho da coluna
                    bool optional = stringIsBool(tsline.at(5).c_str());//Converte para booleando se é opcional ou não
                    int fk = atoi(tsline.at(6).c_str());//Converte para inteiro o id da FK apontada(-1 se não for fk)
                    int tableId = atoi(tsline.at(7).c_str());//Converte para inteiro o ID da tabela que a coluna pertence

                    if (newTableId==-1) {//Se o ID recebido for -1 então retornará todas as colunas que receber
                        Column columnReaded(pk, serial, name, type, size, optional, fk, tableId);
                        colDatas.push_back(columnReaded);
                    }else{//Se o ID não for -1
                        if (newTableId == tableId) {//Checa se o ID vasculhado no momento é igual ao recebido, se for, então grava no vector de retorno
                            Column columnReaded(pk, serial, name, type, size, optional, fk, tableId);
                            colDatas.push_back(columnReaded);
                        }
                    }
                }
		    }

            file.close();
            return colDatas;
		}else{//Se der erro ao abrir o arquivo
            if(log){ cout << "Erro ao abrir arquivo columns.data";}
            return colDatas;
		}
	}else{//Se o arquivo não existir
		if(log){ cout << "Arquivo columns.data nao existe";}
	}
    return colDatas;
}

vector <Primary> getAllPrimary(int idPrimary){//Função que retorna um objeto Primary pelo seu id, se receber -1 retorna todos
    vector <Primary> primaryDatas;
	if(fileExists(pksPath)){
        if(log){ cout << "Arquivo pks.data ja existe, fazendo leitura..."<<endl;}
		string line;
		ifstream file (pksPath);
		if (file.is_open()){
            while ( file.good() ){
		    	getline (file,line);
		        if(line != "\0"){//Se a linha for vazia, não executa o procedimento
                    vector <string> pkline;
                    pkline = explode(line, separator);

                    int id = atoi(pkline.at(0).c_str());//Converte para inteiro o ID da chave primária
                    string name = pkline.at(1);//Recebe o nome da coluna que é primária
                    string table = pkline.at(2);//Recebe o nome da tabela que aquela coluna é primária
                    int order = atoi(pkline.at(3).c_str());//Converte para int a ordem da chave primária

                    if (idPrimary==-1) {//Se o ID recebido for -1 então coloca todos objetos no vector de retorno
                        Primary primaryReaded(id,name,table,order);
                        primaryDatas.push_back(primaryReaded);
                    }else{//Se o ID recebido for diferente de -1
                        if (idPrimary == id) {//Se o ID vaculhado no momento for igual ao recebido, grava no vector de retorno
                            Primary primaryReaded(id,name,table,order);
                            primaryDatas.push_back(primaryReaded);
                        }
                    }
		        }
		    }

            file.close();
            return primaryDatas;
		}else{//Se ocorrer erro ao abrir o arquivo
            if(log){  cout << "Erro ao abrir arquivo pks.data";}
            return primaryDatas;
		}

	}else{//Se o arquivo não existir
		if(log){ cout << "Arquivo pks.data nao existe";}
	}
    return primaryDatas;
}

vector<Foreing> getAllFks(){//Função que retorna todas as FK's existentes
    vector<Foreing> fks;
    if (fileExists(fksPath)){//Se o arquivo existir
        if(log){ cout << "Arquivo fks.data ja existe, fazendo leitura..."<<endl;}
        string line;
		ifstream file (fksPath);
		if (file.is_open()){
            while ( file.good() ){
		    	getline (file,line);
		        if(line != "\0"){//Se a linha for vazia, não executa o procedimento
                    vector <string> pkline;
                    pkline = explode(line, separator);

                    int id = atoi(pkline.at(0).c_str());//Converte para inteiro o ID da ocorrencia da FK
                    int fk = atoi(pkline.at(1).c_str());//Converte para inteiro o ID da chave primária que eé apontada

                    Foreing newforeing(id, fk);//Cria um novo objeto Foreign
                    fks.push_back(newforeing);//Coloca no vector de Foreigns
                }
		    }

            file.close();
            return fks;
        }else{//Se ocorrer algum erro ao abrir o arquivo
            if(log){ cout << "Erro ao ler arquivo fks.data."<<endl;}
            return fks;
        }
    }else{//Se o arquivo não existir
        if(log){ cout << "Arquivo fks.data nao existe."<<endl;}
        return fks;
    }
    return fks;
}

bool setForeingKey(Column col, int pk){//Função que seta uma Foreign Key

    if (pk > -1){//Se o ID recebido for maior de -1
        vector <Primary> pkData = getAllPrimary(-1);
        for (int x=0; x<pkData.size();x++){//Percorre o vector de Primary
            if (pk == pkData.at(x).getId()){//Checa se o ID existe
                if (log) {cout << "ID " << pk <<" existe na tabela PK.data" << endl;}
                vector <Column> columnData = getAllColumns(-1);//Requisita um vector de todas as colunas
                for(int x1=0;x1<columnData.size();x1++){//Percorre o vector de Column
                    if (col.getName() == columnData.at(x1).getName()){//Verifica se a column existe
                        if (col.getType()==columnData.at(x1).getType() && col.getSize()==columnData.at(x1).getSize()){//Verifica se o tamanho e o tipo são compatíveis
                            if (log) { cout << "Coluna "<<col.getName() << " existe no arquivo Columns.data." << endl;}
                            if (fileExists(fksPath)){//Se o arquivo existe faz uma destas duas coisas
                                vector<Foreing> fks = getAllFks();//Requisita todas FKS já setadas
                                if (columnData.at(x1).getFk()== -1){//Se a coluna tem -1 no atributo FK, então ela não tem FK setada ainda
                                    if (log) {cout << "Coluna ainda sem FK setada" << endl;}
                                    int newFkId = fks.at(fks.size()-1).getId()+1;//Faz o ID da nova ocorrencia ser igual ao último ID + 1
                                    if (log) {cout << "Novo id FK: " << newFkId << endl;}
                                    Foreing newFK(newFkId,pk);//Cria o objeto FK
                                    fks.push_back(newFK);
                                    ofstream filefks;
                                    filefks.open(fksPath);//Abre o arquivo fks.data
                                    for(int x2=0;x2<fks.size();x2++){//Percorre conforme o tamanho do Vector de Foreigns
                                        filefks << fks.at(x2).getId() << separator << fks.at(x2).getFk() << "\n";//Grava no arquivo fks.data
                                    }
                                    filefks.close();
                                    ofstream fileC;
                                    fileC.open(columnsPath);//Abre o arquivo columns.data
                                    for (int x2=0;x2<columnData.size();x2++){
                                        if(columnData.at(x1).getName() == columnData.at(x2).getName()){//Se a coluna percorrida é igual a requisitada, então atualiza o valor de FK para o ID do novo objeto Foreign
                                            columnData.at(x2).setFk(newFkId);
                                        }
                                        //Grava no arquivo clumns.data
                                        fileC << columnData.at(x2).getPk() << separator << columnData.at(x2).getSerial() << separator << columnData.at(x2).getName() << separator << columnData.at(x2).getType() << separator << columnData.at(x2).getSize() << separator << columnData.at(x2).getOptional() << separator << columnData.at(x2).getFk() << separator << columnData.at(x2).gettableId() << "\n" ;
                                    }
                                    filefks.close();
                                    return true;
                                }else{//Se o valor do atributo FK da coluna for diferente de -1, então somente o arquivo fks.data irá ser atualizado
                                    if (log) {cout << "Coluna com FK setada, valor deve ser mudado em FK Data" << endl;}
                                    vector<Foreing> fks = getAllFks();//Requere todas as Foreign existentes
                                    ofstream filefks;
                                    filefks.open(fksPath);//Abre o arquivo fks.data
                                    for (int i=0;i<fks.size();i++){
                                        if (fks.at(i).getId() == columnData.at(x1).getFk()){//Seta o novo valor caso seja a ocorrencia da coluna recebida
                                            fks.at(i).setFk(pk);
                                        }
                                        //Grava no arquivo fks.data
                                        filefks << fks.at(i).getId() << separator << fks.at(i).getFk() << "\n" ;
                                    }
                                    filefks.close();
                                    return true;
                                }
                            }else{//Senão cria o arquivo
                                if (log) {cout << "Arquivo FK.DATA inexistente. Sendo criado..."<<endl;}
                                ofstream filefks;
                                filefks.open(fksPath);//Grava no arquivo fks.data a nova ocorrencia da FK
                                filefks << 0 << separator << pk << "\n" ;
                                filefks.close();
                                ofstream fileC;
                                fileC.open(columnsPath);
                                for (int x2=0;x2<columnData.size();x2++){//Percorre o vetor de colunas
                                    if(columnData.at(x1).getName() == columnData.at(x2).getName()){//Grava o novo ID da FK na coluna referente
                                        columnData.at(x2).setFk(0);
                                    }
                                    //Grava no arquivo columns.data os novos dados atualizados
                                    fileC << columnData.at(x2).getPk() << separator << columnData.at(x2).getSerial() << separator << columnData.at(x2).getName() << separator << columnData.at(x2).getType() << separator << columnData.at(x2).getSize() << separator << columnData.at(x2).getOptional() << separator << columnData.at(x2).getFk() << separator << columnData.at(x2).gettableId() << "\n" ;
                                }
                                filefks.close();
                                return true;
                            }
                        }else{
                            if(log){cout << "Tipo ou tamanho da foreing key não corresponde à primary key" << endl;}
                            return false;
                        }
                    }
                }
                if(log){ cout << "Saiu do FOR das colunas, coluna inexistente" << endl;}
                return false;
            }
        }
        if(log){cout << "Saiu do FOR das primary keys, PK inexistente" << endl;}
        return false;

    }else{//Se o ID recebido for menor que 0 então cai aqui
        if(log){ cout << "ID recebido é inválido"<<endl;}
        return false;
    }

}

bool createTable(Table newTable, vector<Column> columns){//Função que cria uma tabela
    vector<Database> dbs;
    dbs = getAllDatabase();//Requisita todos os banco de dados

    if (newTable.getName().length()==0) {
        if (log) { cout << "Nome em branco" << endl; }
        return false;
    }

    for (int x = 0; x<dbs.size(); x++) {
        if (dbs.at(x).getId()==newTable.getDatabase()) {
            if (log) {cout <<"Banco selecionado: " << dbs.at(x).getName() << endl;}
            string tablespace = getPathFromTableSpace(dbs.at(x).getId())+"/";//Configura o caminho da tablespace
            string newTablePath = tablespace+dbs.at(x).getName()+"/"+newTable.getName()+".data";//Configura o caminho da nova tabela(caminho do ts + nome do banco + nova tabela)

            if (fileExists(tablesPath)){//Se o arquivo tables.path já existir
                if(log){cout<<"Arquivo tables.data existe, efetuando leitura..."<<endl;}
                vector <Table> tableReturn;
                tableReturn = getAllTables();//Requisita todas tabelas existentes
                for (int x=0;x<tableReturn.size();x++){//Percorre as tabelas existentes
                    if(log){cout << newTable.getName() << " <> "<< tableReturn.at(x).getName() << endl;}
                    if(newTable.getName() == tableReturn.at(x).getName()){//Se o nome recebido já existir
                        if(log){ cout << "Tabela ja existe" << endl;}
                        return false;
                    }
                }

                newTable.setId(tableReturn.at(tableReturn.size()-1).getId()+1);//Incrementa o id da nova tabela conforme o id atual + 1
                tableReturn.push_back(newTable);//Coloca a nova tabela no vector de objetos Table
                ofstream fileTables;
                fileTables.open(tablesPath);//Abre o arquivo tables.data
                for (int x = 0; x< tableReturn.size();x++){//Grava no arquivo tables.data
                    fileTables << tableReturn.at(x).getId() << separator << tableReturn.at(x).getName() << separator << tableReturn.at(x).getDatabase() << "\n" ;
                }
                fileTables.close();
                ofstream fileTable;
                fileTable.open(newTablePath.c_str());//Cria a nova tabela no caminho configurado antes
                fileTable.close();

                vector <Column> columnsReaded = getAllColumns(-1);//Requisita todas as colunas existentes
                for (int x = 0; x < columns.size(); x++) {//Atualiza o valor TableID das colunas com o ID da nova tabela criada
                    if (log){cout << "fk: "<< columnsReaded.at(x).getFk() << " -- name: " << columnsReaded.at(x).getName()  << " -- optional: " << columnsReaded.at(x).getOptional()  << " -- pk: " << columnsReaded.at(x).getPk()  << " -- serial: " << columnsReaded.at(x).getSerial()  << " -- size: " << columnsReaded.at(x).getSize()  << " -- getid:  " << columnsReaded.at(x).gettableId()  << " -- gettype:  " << columnsReaded.at(x).getType() << endl;}
                    columns.at(x).settableId(newTable.getId());
                    columnsReaded.push_back(columns.at(x));
                }
                ofstream fileColumn;
                fileColumn.open(columnsPath);//Abre o arquivo columns.data
                for (int x = 0; x < columnsReaded.size(); x++) {//Verifica se as colunas passadas são do tipo DATA ou HORA e então seta seus tamanhos(padrão)
                    if (columnsReaded.at(x).getType()==4) {//aqui //integer = 0 | float = 1 | bool = 2 | string = 3 | data = 4 | hora = 5
                        columnsReaded.at(x).setSize(8);
                    }
                    if (columnsReaded.at(x).getType()==5) {
                        columnsReaded.at(x).setSize(6);
                    }
                    //Grava os novos dados no arquivo columns.data
                    fileColumn << columnsReaded.at(x).getPk() << separator << columnsReaded.at(x).getSerial() << separator << columnsReaded.at(x).getName() << separator << columnsReaded.at(x).getType() << separator << columnsReaded.at(x).getSize() << separator << columnsReaded.at(x).getOptional() << separator << columnsReaded.at(x).getFk() << separator << columnsReaded.at(x).gettableId() << "\n" ;
                }

                fileColumn.close();
                vector <Primary> primaryReaded;
                primaryReaded = getAllPrimary(-1);//Requisita todas as primary keys existentes
                int newPkId = primaryReaded.at(primaryReaded.size()-1).getId()+1;//Seta o novo ID da próxima primary para o último ID + 1
                int cont = 1;
                for (int x = 0; x < columns.size(); x++){//Percorre todas as colunas
                    if(columns.at(x).getPk()){//Se a coluna for Primary Key
                        Primary pkTable(newPkId, columns.at(x).getName(), newTable.getName(), cont);//Cria um objeto Primary e coloca no vector
                        primaryReaded.push_back(pkTable);
                        cont++;//Contador para a ordem das primary keys
                        newPkId++;//incrementa o ID das primary caso exista masi de uma
                    }
                }
                ofstream filepks;
                filepks.open(pksPath);//Abre o arquivo pks.data e atualiza com os novos valores
                for(int x=0;x<primaryReaded.size();x++){
                    filepks << primaryReaded.at(x).getId() << separator << primaryReaded.at(x).getName() << separator << primaryReaded.at(x).getTable() << separator << primaryReaded.at(x).getOrder() << "\n" ;
                }
                filepks.close();
                return true;
            }else{//Se o arquivo tables.data não existir
                if(log){cout<<"Arquivo tables.data não existe, sendo criado..."<<endl;}
                ofstream fileTables;
                fileTables.open(tablesPath);//Cria o arquivo tables.data e grava a primeira ocorrência
                fileTables << 0 << separator << newTable.getName() << separator << newTable.getDatabase() << "\n" ;
                fileTables.close();
                ofstream fileTable;
                fileTable.open(newTablePath.c_str());//Cria a tabela
                fileTable.close();

                ofstream fileMeta;
                fileMeta.open(columnsPath);//Abre o arquivo columns.data
                for (int x = 0; x < columns.size(); x++){//Verifica se as colunas passadas são do tipo DATA ou HORA e então seta seus tamanhos(padrão)
                    if (columns.at(x).getType()==4) {//aqui //integer = 0 | float = 1 | bool = 2 | string = 3 | data = 4 | hora = 5
                        columns.at(x).setSize(8);
                    }
                    if (columns.at(x).getType()==5) {
                        columns.at(x).setSize(6);
                    }
                    //Grava e atualiza o arquivo columns.data
                    fileMeta << columns.at(x).getPk() << separator << columns.at(x).getSerial() << separator << columns.at(x).getName() << separator << columns.at(x).getType() << separator << columns.at(x).getSize() << separator << columns.at(x).getOptional() << separator << columns.at(x).getFk() << separator << 0 << "\n" ;
                }
                fileMeta.close();

                ofstream filepks;
                filepks.open(pksPath);//Cria o arquivo das pks.data
                int contOrdem = 1;
                int newPkIdNoData = 0;
                for (int x = 0; x < columns.size(); x++) {
                    if(columns.at(x).getPk()){//Grava no arquivo pks.data as novas pk's e incrementa seus ID e coloca na ordem recebida
                        filepks << newPkIdNoData << separator << columns.at(x).getName() << separator << newTable.getName() << separator << contOrdem << "\n" ;
                        contOrdem++;
                        newPkIdNoData++;
                    }
                }
                filepks.close();
                return true;
            }
        }
    }
    if (log) { cout << "Tabela nao pode ser criada." << endl; }
    return false;
}

bool incrementSerial(Column col){

    vector<Column> cols = getAllColumns(-1);
    for (int c = 0; c < cols.size(); c++) {

        if ((col.getName().compare(cols.at(c).getName())==0) && (col.gettableId() == cols.at(c).gettableId())) {
            int serial = cols.at(c).getSerial();
            if (serial>-1) {
                serial++;
                cols.at(c).setSerial(serial);

                ofstream fileColumn;
                fileColumn.open(columnsPath);

                for (int x = 0; x < cols.size(); x++) {
                    fileColumn << cols.at(x).getPk() << separator << cols.at(x).getSerial() << separator << cols.at(x).getName() << separator << cols.at(x).getType() << separator << cols.at(x).getSize() << separator << cols.at(x).getOptional() << separator << cols.at(x).getFk() << separator << cols.at(x).gettableId() << "\n" ;
                }

                fileColumn.close();

                return true;

            }else{
                return false;
            }
            return true;
        }
    }
    return false;
}

vector<string> getColFromTable(string tablePath, int tableIndex){
    vector <string> selectCols;

    string line;
    ifstream file (tablePath.c_str());
    if (file.is_open()){
        while ( file.good() ){
            getline (file,line);
            if(line != "\0"){//SE A LINHA FOR VAZIA ENT√O N√O FAZ ISSO, APARENTEMENTE TAVA DNADO ERRO PQ PEGAVA LIXO
                vector <string> lines;
                lines = explode(line, separator);
                selectCols.push_back(lines.at(tableIndex));
            }
        }

        file.close();


    }
    return selectCols;
}

bool returnWhere(vector<string>tuple ,vector<Condition> where, vector<Column> columns){
    bool validation = true;
    for (int t = 0; t<tuple.size(); t++) {
        for (int w = 0; w<where.size(); w++) {
            if (columns.at(t).getName().compare(where.at(w).getColName())==0) {
                if (where.at(w).getOperatorType().compare("<")==0) {
                    if (tuple.at(t).compare(where.at(w).getValue())<0) {
                        validation = true;
                    }else{
                        validation = false;
                    }
                    break;
                }
                if (where.at(w).getOperatorType().compare("<=")==0) {
                    if (tuple.at(t).compare(where.at(w).getValue())<=0) {
                        validation = true;
                    }else{
                        validation = false;
                    }
                    break;
                }
                if (where.at(w).getOperatorType().compare("=")==0) {
                    if (tuple.at(t).compare(where.at(w).getValue())==0) {
                        validation = true;
                    }else{
                        validation = false;
                    }
                    break;
                }
                if (where.at(w).getOperatorType().compare(">")==0) {
                    if (tuple.at(t).compare(where.at(w).getValue())>0) {
                        validation = true;
                    }else{
                        validation = false;
                    }
                    break;
                }
                if (where.at(w).getOperatorType().compare(">=")==0) {
                    if (tuple.at(t).compare(where.at(w).getValue())>=0) {
                        validation = true;
                    }else{
                        validation = false;
                    }
                    break;
                }
            }
        }
    }
    if (validation) {
        return true;
    }else{
        return false;
    }
}

vector<vector<string> > select(vector<string> parameters, string tableName, vector<Condition> where){
    vector <vector<string> > select;

    vector<Table> tables = getAllTables();
    for (int t = 0; t < getAllTables().size(); t++) {
        if (tables.at(t).getName().compare(tableName)==0) {
            if (tables.at(t).getDatabase()==getDefaultDb().getId()) {
                int tableId = tables.at(t).getId();
                vector<Column> columns = getAllColumns(tableId);

                Table selectTable = tables.at(t);
                string tablepath = getPathFromDatabase(getDefaultDb().getId()) + "/" + selectTable.getName() + ".data";

                string line;
                ifstream file (tablepath.c_str());

                if (parameters.size()==1 && (parameters.at(0).compare("*")==0)) {
                    string line;
                    ifstream file (tablepath.c_str());
                    if (file.is_open()){
                        while ( file.good() ){
                            getline (file,line);
                            if(line != "\0"){//SE A LINHA FOR VAZIA ENT√O N√O FAZ ISSO, APARENTEMENTE TAVA DNADO ERRO PQ PEGAVA LIXO
                                vector <string> tuple;
                                tuple = explode(line, separator);

                                if (returnWhere(tuple, where, columns)) {
                                    select.push_back(tuple);
                                }

                            }
                        }
                        file.close();
                    }
                    return select;
                }else{
                    vector <vector<string> > returnSelect;

                    string line;
                    ifstream file (tablepath.c_str());
                    if (file.is_open()){
                        while ( file.good() ){
                            getline (file,line);
                            int lineCount = 0;
                            if(line != "\0"){//SE A LINHA FOR VAZIA ENT√O N√O FAZ ISSO, APARENTEMENTE TAVA DNADO ERRO PQ PEGAVA LIXO
                                vector <string> tuple;
                                tuple = explode(line, separator);
                                select.push_back(tuple);
                                vector<string> result;

                                if (returnWhere(tuple, where, columns)) {

                                    for (int h = 0; h<parameters.size(); h++) {
                                        for (int g = 0; g<columns.size(); g++) {
                                            if (parameters.at(h).compare(columns.at(g).getName())==0) {
                                                //cout << "coluna " << columns.at(g).getName() << "[]" << parameters.at(h) << endl;
                                                result.push_back(tuple.at(g));
                                                break;
                                            }
                                        }


                                    }

                                    returnSelect.push_back(result);

                                }
                            }
                            lineCount++;
                        }
                        file.close();
                    }
                    return returnSelect;
                }
            }
        }
    }
    return select;
}

bool validateValue(vector<Column> columns,vector<string> *values,string tableName){
    bool validation= false;
    vector <int> serialId;
    for (int c = 0; c < columns.size(); c++) {
        //COMEÇA VALIDAÇÃO DO CAMPO
        if (columns.at(c).getOptional() && (values->at(c).compare("NULL")==0) && !columns.at(c).getPk()){// se campo é opcional e nulo e não é primary key

        }else{
            if (columns.at(c).getSerial()>-1) {
                values->at(c) = intToString(columns.at(c).getSerial());
                serialId.push_back(c);
            }else{
                if(!checkType(values->at(c), columns.at(c).getType())){
                    validation = false;
                    if(log){cout << "Não foi possivel inserir na coluna " << columns.at(c).getName() << ". Valor informado não é valido."<< endl;};
                    return false;
                }

                if(values->at(c).length()>columns.at(c).getSize()){
                    validation = false;
                    if(log){cout << "Não foi possivel inserir na coluna " << columns.at(c).getName() << ". Tamanho do valor inserido inválido."<< endl;};
                    return false;
                }
            }

        }

        if (columns.at(c).getPk()) {
            vector<string> parametros;
            parametros.push_back(columns.at(c).getName());
            vector<Condition> where;

            vector<vector<string> > selectResult = select(parametros, tableName, where);
            for (int tuple = 0 ; tuple<selectResult.size(); tuple++) {
                for (int col = 0; col<selectResult.at(tuple).size(); col++) {
                    if(selectResult.at(tuple).at(col).compare(values->at(c))==0) {
                        cout <<"aki no for das pk"<<endl;
                        return false;
                    }
                }
            }
        }

        if (columns.at(c).getFk()!=-1) {
            vector<Foreing> fks = getAllFks();
            for (int f = 0; f<fks.size(); f++) {
                if (fks.at(f).getId()==columns.at(c).getFk()) {
                    vector<Primary> pks= getAllPrimary(fks.at(f).getFk());
                    if (pks.size()>0) {
                        string nomeCampo = pks.at(0).getName();
                        string nomeTabela = pks.at(0).getTable();
                        vector<string> parametrospk;
                        vector<Condition> where;
                        parametrospk.push_back(nomeCampo);


                        vector<vector<string> > selectResult = select(parametrospk, nomeTabela, where);
                        cout << "tamanho: " << selectResult.size() << endl;
                        if (selectResult.size()==0) {
                            return false;
                        }else{

                            bool validationfk = false;

                            for (int tuple = 0 ; tuple<selectResult.size(); tuple++) {
                                //for (int col = 0; col<selectResult.at(tuple).size(); col++) {
                                cout << "lendo " << selectResult.at(tuple).at(0) << endl;
                                if(selectResult.at(tuple).at(0).compare(values->at(c))==0) {
                                    validationfk = true;
                                    cout << "encontrou " << selectResult.at(tuple).at(0) << endl;
                                    break;
                                }
                                cout << "naoc" << endl;
                                //}
                                if(validationfk){
                                    cout << "aqui validationfk " << validationfk << endl;
                                    validation = true;
                                    break;

                                }

                                cout << "1 Primary key ainda não encontrada" << endl;
                            }
                        }
                    }else{
                        cout << "nao há fk com aquele id" << endl;
                    }
                }
            }

        }else{
            if(!validation)
                validation = true;
        }
    }
    cout << "antes do if" << endl;
    if(validation){

        for(int i=0;i<serialId.size();i++){
            incrementSerial(columns.at(serialId.at(i)));
        }
        return true;
    }else{
        return false;
    }
}



bool insert(vector<string> values, string tableName){
    vector<Table> tables = getAllTables();
    for (int t = 0; t < getAllTables().size(); t++) {
        if (tables.at(t).getName().compare(tableName)==0) {
            if (tables.at(t).getDatabase()==getDefaultDb().getId()) {
                int tableId = tables.at(t).getId();
                vector<Column> columns = getAllColumns(tableId);
                if (columns.size()==values.size()) {
                    Table insertTable = tables.at(t);
                    string tablepath = getPathFromDatabase(getDefaultDb().getId()) + "/" + insertTable.getName() + ".data";


                    bool validation;// = true;
                    ///for (int c = 0; c < columns.size(); c++) {

                    //COMEÇA VALIDAÇÃO DO CAMPO
                    validation = validateValue(columns,&values,tableName);

                    //FIM VALIDAÇÃO CAMPOS
                    ///}
                    if (validation) {
                        ofstream fileColumn;
                        fileColumn.open(tablepath.c_str(), std::ofstream::app);
                        for (int x = 0; x < values.size(); x++) {
                            fileColumn << values.at(x);
                            if (x!=values.size()-1) {
                                fileColumn << separator;
                            }
                        }
                        fileColumn << "\n";
                        fileColumn.close();
                    }else{
                        cout << ">>>false" << endl;
                        return false;
                    }

                    //cout << "increment " << columns.at(0).getName() << endl;


                    //incrementSerial(columns.at(0));


                    /*

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


                     */

                    // cout << tablepath;
                    return true;

                }else{
                    cout << "numero de colunas não corresponde ao numero de colunas da tabela" << endl;
                    return false;
                }
            }
            return true;
        }
    }
    cout << "tabela nao encontrada";
    return false;
}


bool deleteItem(string fileName,string itemName){
    if(fileName.compare("tablespace")==0){//Se for tablespace
        if(log){cout <<"Escolheu deletar tablespace"<<endl;}
        vector <Tablespace> tsReaded = getAllTableSpace();//Pega todas tablespace
        for(int i=0;i<tsReaded.size();i++){//Percorre as tablespaces recebidas
            if(itemName.compare(tsReaded.at(i).getName())==0){//Verifica se a tablespace existe
                if(log){cout<<"Tablespace encontrada"<<endl;}
                vector <string> valuesDatabase = getColFromTable(dbpath,2);//Retorna os ID das tablespace do arquivo dpath
                for(int i2=0;i2<valuesDatabase.size();i2++){//Percorre o valor retornado
                    string tsID = intToString(tsReaded.at(i).getId());
                    if(valuesDatabase.at(i2).compare(tsID)==0){//Verifica se o ID da TS existe no database.data
                        if (log){cout<<"Encontrado Database que pertence a Tablespace. Impossivel deletar."<<endl;}
                        return false;
                    }
                }
                if (log){cout<<"Nao encontrado database vinculado a tablespace. Possivel deletar."<<endl;}
                ofstream file;
                file.open(tspath);
                for (int x = 0; x<tsReaded.size(); x++){
                    if(tsReaded.at(i).getId()==tsReaded.at(x).getId()){//Se o ID for igual ao que eu quero deletar, não faz nada

                    }else{//Se for diferente então grava no arquivo
                        file << tsReaded.at(x).getId() << separator << tsReaded.at(x).getName() << separator << tsReaded.at(x).getLocation() << "\n";
                    }
                }
                file.close();//Fecha o arquivo e retorna TRUE
                string tablespaceFolder = tsReaded.at(i).getLocation();
                rmdir(tablespaceFolder.c_str());//Deleta a pasta da tablespace
                return true;
            }
        }
        if(log){cout<<"Tablespace nao encontrada"<<endl;}
        return false;

    }else if(fileName.compare("database")==0){
        if(log){cout <<"Escolheu deletar database"<<endl;}
        vector<Database> dbReaded = getAllDatabase();//Recebe todos os itens do database.data
        for(int i=0;i<dbReaded.size();i++){//Percorre o vector de database recebido
            if(itemName.compare(dbReaded.at(i).getName())==0){//Verifica se o nome passado como parametro existe
                if(log){cout<<"Banco de dados encontrado."<<endl;}
                vector <string> tableReaded = getColFromTable(tablesPath,2);//Recebe a coluna dos ID's dos bancos que as tabelas pertecem
                for(int i2=0;i2<tableReaded.size();i2++){//Percorre o vector recebido
                    string dbID = intToString(dbReaded.at(i).getId());//Converte o ID do Banco referente para string
                    if(tableReaded.at(i2).compare(dbID)==0){//Compara ver se existe tabelas que pertecem ao banco
                        if(log){cout<<"Banco de dados possui tabelas vinculadas a ele. Impossivel deletar."<<endl;}
                        return false;
                    }

                }
                if (log){cout<<"Nao encontradas tabelas vinculado ao banco de dados. Possivel deletar."<<endl;}
                string dbFolder = getPathFromDatabase(dbReaded.at(i).getId());//Pega o caminho do database
                rmdir(dbFolder.c_str());//Deleta a pasta do database
                ofstream file;
                file.open(dbpath);
                for (int x = 0; x<dbReaded.size(); x++){
                    if(dbReaded.at(x).getId()==dbReaded.at(i).getId()){//Se o ID percorrido for igual ao que eu quero deletar, pula ele

                    }else{//Senão, grava no arquivo
                        file << dbReaded.at(x).getId() << separator << dbReaded.at(x).getName() << separator << dbReaded.at(x).getTablespace()  << separator << dbReaded.at(x).getDefault() << "\n";
                    }
                }
                file.close();//Fecha o arquivo
                return true;
            }

        }
        if(log){cout<<"Banco de dados nao encontrado"<<endl;}
        return false;

    }else if(fileName.compare("table")==0){
        if(log){cout <<"Escolheu deletar tabelas"<<endl;}
        vector<Table> tableReaded = getAllTables();//Recebe todas as tabelas que existem no tables.data
        for(int i=0;i<tableReaded.size();i++){//Percorre as tabelas recebidas
            if(itemName.compare(tableReaded.at(i).getName())==0){//Verifica se a tabela existe no tables.data
                if(log){cout<<"Tabela existe"<<endl;}
                string tablePath = getPathFromDatabase(tableReaded.at(i).getDatabase()) + "/" + itemName + ".data";
                vector<string> tableData = getColFromTable(tablePath,0);
                if(tableData.size()==0){
                    if(log){cout<<"Tabela vazia. Possivel deletar."<<endl;}
                    ofstream file;
                    file.open(tablesPath);//Abre o arquivo tables.data para gravação
                    for (int x = 0; x<tableReaded.size(); x++){
                        if(tableReaded.at(x).getId()==tableReaded.at(i).getId()){//Se o ID percorrido for igual ao que eu quero deletar, pula ele

                        }else{//Senão, grava no arquivo
                            file << tableReaded.at(x).getId() << separator << tableReaded.at(x).getName() << separator << tableReaded.at(x).getDatabase() << "\n" ;
                        }
                    }

                    file.close();//Fecha o arquivo tables.data
                    vector<Column> colReaded = getAllColumns(-1);
                    file.open(columnsPath);//Abre o arquivo column.data para gravação
                    for (int x = 0; x<colReaded.size(); x++){
                        if(colReaded.at(x).gettableId()==tableReaded.at(i).getId()){//Se o ID da tabela das colunas for igual ao que eu quero deletar, pula ele

                        }else{//Senão, grava no arquivo
                            file << colReaded.at(x).getPk() << separator << colReaded.at(x).getSerial() << separator << colReaded.at(x).getName() << separator << colReaded.at(x).getType() << separator << colReaded.at(x).getSize() << separator << colReaded.at(x).getOptional() << separator << colReaded.at(x).getFk() << separator << colReaded.at(x).gettableId() << "\n" ;

                        }
                    }

                    file.close();//Fecha o arquivo column.data
                    remove(tablePath.c_str());
                    return true;
                }
                if(log){cout<<"Tabela populada. Impossivel deletar."<<endl;}
                return false;
            }

        }
        if(log){cout<<"Tabela nao encontrada."<<endl;}
        return false;
    }

}
