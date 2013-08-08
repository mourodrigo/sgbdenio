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
//#include <sys/dir.h>
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

#define dbpath "database.data"
#define separator "|>#<|"
#define log 1




class Database{ //classe do tipo database
private:
    int id;
    string name;
    string dir;
    bool defaultDb;
    
public:
    int getId(){
        return this->id;
    }
    string getName(){
        return this->name;
    }
    string getDir(){
        return this->dir;
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
    void setDir(string newDir){
        this->dir = newDir;
    }
    void setDefault(bool newDefault){
        this->defaultDb = newDefault;
    }
    
    
    Database(int newId, string newName, string newDir, bool newDefaultDb){
        this->id = newId;
        this->name = newName;
        this->dir = newDir;
        this->defaultDb = newDefaultDb;
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
                    string dir;
                    if(databaseline.at(2)!=""){
                        dir = databaseline.at(2);//
                    }else{
                        dir = getCurrentPath()+"/"+databaseline.at(1);
                    }
                    bool defaultDb = stringIsBool(databaseline.at(3));
                    Database dbReaded(id,name,dir,defaultDb);
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
    
	int dbid = 0;
    dbid = newdb.getId();
    
	if(newdb.getName().length() == 0){
		return false;
	}
    
    
	if(fileExists(dbpath)){
		vector <Database> dbs;
	    dbs = getAllDatabase();
        int indexIdNewDatabase = dbs.size()+1;
        if(newdb.getDefault()){
            for (int x = 0; x<dbs.size(); x++){
            	if(dbs.at(x).getDefault()){
            		dbs.at(x).setDefault(0);
            	}
            }
            
        }
        
        
    	if(newdb.getDir().length() == 0){
    		newdb.setDir(getCurrentPath()+"/"+newdb.getName());
    	}else{
            newdb.setDir(newdb.getDir()+"/"+newdb.getName());
        }
        
        newdb.setId(indexIdNewDatabase);
        dbs.push_back(newdb);
        
        ofstream file;
        
        file.open(dbpath);
        
        for (int x = 0; x<dbs.size(); x++){
    		file << dbs.at(x).getId() << separator << dbs.at(x).getName() << separator << dbs.at(x).getDir()  << separator << dbs.at(x).getDefault() << "\n";
        }
        
        file.close();
        
        string strPath = newdb.getDir();
        
        cout << "\n\n\n a criar " << strPath << endl;
        
        MKDIR(strPath.c_str());

        if(log){cout << "Bando de dados " << newdb.getName() << " com id 0 no diretorio: \n " << newdb.getDir() << "\n  default 1 " << endl;} //inserção no arquivo esta ok

        
        return true;
	}else{
		ofstream file;
		file.open(dbpath);
        if(newdb.getDir().length() == 0){
    		newdb.setDir(getCurrentPath()+"/"+newdb.getName());
    	}else{
            newdb.setDir(newdb.getDir()+"/"+newdb.getName());
        }
        MKDIR(newdb.getDir().c_str());
		file << 0 << separator << newdb.getName() << separator << newdb.getDir()  << separator << 1 << "\n";
		file.close();
        
        if(log){cout << "Bando de dados " << newdb.getName() << " com id 0 no diretorio: \n " << newdb.getDir() << "\n  default 1 " << endl;} //inserção no arquivo esta ok
		
        
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
    return  Database(-1, "", "", false); //nao consigo retornar null
}

#pragma globals

//extern Database defaultDb;  //variavel global? aqui nao funcionou


int main() {
    

    
    /*  //CRIANDO ALGUNS DATABASES
    
    Database dbmouro2(6666,"mouro1","",false);
	createDatabase(dbmouro2);

    
	Database dbmouro(6666,"sgbdeniooo","",true);
	createDatabase(dbmouro);
    
    
    Database dbmouro3(6666,"mouro2","/Users/Desenvolvimento/Desktop",true);
	createDatabase(dbmouro3);
    
    Database dbmouro4(6666,"moueo3","/Users/Desenvolvimento/Desktop",false);
	createDatabase(dbmouro4);
    
    */
    
    
    
    
    //SETANDO DATABASE DEFAULT
    
    Database defaultDb = getDefaultDb(); //declarando defaultdb aqui pois nao consegui declarar com global ainda
    
    cout << "db default: \n" << defaultDb.getId() << " - " << defaultDb.getName() << " - " << defaultDb.getDir();
    
    
    
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
