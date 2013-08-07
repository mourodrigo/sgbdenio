//============================================================================
// Name        : sgbdenio.cpp
// Author      : Rodrigo Bueno Tomiosso & Andrey Baumhardt Ramos
// Version     :
// Copyright   : wtfpl
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <fstream>
#include <ostream>
#include <vector>
#include <sstream>
#include <utility>

using namespace std;

#define dbpath "database.data"
#define separator "&&##**"

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

#pragma mark - filemanager

bool fileExists(const char *filename){ //verifica se arquivo existe
  ifstream ifile(filename);
  return ifile;
}

#pragma mark -sgbd

vector<Database> getAllDatabase(){
	vector <Database> dbs;
	if(fileExists(dbpath)){

		cout << "Arquivo de banco de dados ja existe fazendo leitura";
		string line;
		ifstream file (dbpath);
		if (file.is_open()){
		    while ( file.good() ){
		    	getline (file,line);
		    	//cout << "line" << line << endl;

			    if(line != "\0"){//SE A LINHA FOR VAZIA ENTÃO NÃO FAZ ISSO, APARENTEMENTE TAVA DNADO ERRO PQ PEGAVA LIXO
                       vector <string> databaseline;
			           databaseline = explode(line, separator);

			           int id = atoi(databaseline.at(0).c_str());//CONVERTE STRING PARA INTEIRO
			           string name = databaseline.at(1);//
			           string dir = databaseline.at(2);//
			           bool defaultDb;
			           if(databaseline.at(3)=="1"){//ATRIBUI O VALOR BOLEANO ATRAVÉS DE UM IF
                          //cout << "DEFAULTDB EH UM"<< endl;
                          defaultDb = true; 
                          } else {
			              //cout << "DEFAULTDB NAO EH UM"<< endl;
			              defaultDb = false; 
                          }
		        
			           
                       //cout << databaseline.at(1).c_str() <<endl;
			           Database dbReaded(0,name,dir,defaultDb);
			           dbs.push_back(dbReaded);
              }
		    }
		    file.close();
		    //cout << dbs.at(0).getId() << " | " << dbs.at(0).getName() << " | " << dbs.at(0).getDir() << " | " << dbs.at(0).getDefault() ;
		    return dbs;
		}else{
		   cout << "Erro ao abrir arquivo do banco de dados";
		   return dbs;
		 }

	}
return dbs;
}

bool createDatabase(Database newdb){

	int dbid = 0;
	//if(newdb.getId()==NULL){ //tratar NULL n‹o existe em c++ ? o.O
		dbid = newdb.getId();
	//}

	if(newdb.getName().length() == 0){
		return false;
	}

	if(newdb.getDir().length() == 0){
		return false;
	}

	if(fileExists(dbpath)){
		vector <Database> dbs;
		cout << endl << "Teste" ;
        dbs = getAllDatabase();
        
		//se arquivo ja existe busca todos os dbs para inserir no lugar certo...
		//assim que corrigido o problema no getalldatabase continuar aqui

		//cout << "dbs size: " << dbs.size() << endl;
		for (int x = 0; x<dbs.size(); x++){
				cout << "id: " << dbs.at(x).getId() << "name: "<< dbs.at(x).getName()  << " dir: "<< dbs.at(x).getDir() << " default: " << dbs.at(x).getDefault() << endl;
			}

		return true;
	}else{
		cout << "Criando primeiro banco de dados"; //inser‹o no arquivo esta ok
		ofstream file;
		file.open(dbpath);
		file << 0 << separator << newdb.getName() << separator << newdb.getDir()  << separator << 1 << "\n";
		file.close();
		return true;
	}


}




int main() {



	Database dbmouro(0,"sgbdMouro","/Users/rodrigo/Desktop",true);
	createDatabase(dbmouro);

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
	Database db1(1,"banco1","/var/www/",true);  //instancia db1 do tipo database e seta os valores atravŽs do mŽtodo construtor --> Database(int newId, string newName, string newDir, bool newDefaultDb){
	Database db2(2,"banco222","/var/www/db1/",false);
	Database db3(3,"banco3333","/users/mouro/banco3/",false);
	Database db4(4,"banco44444","/root/db4",false);

	dbs.push_back(db1); //manda db1 pro vetor

for (int x = 0; x<dbs.size(); x++){
		cout << "id: " << dbs.at(x).getId() << "name: "<< dbs.at(x).getName()  << " dir: "<< dbs.at(x).getDir() << " default: " << dbs.at(x).getDefault() << endl;
	}

createDatabase(db1); //CHAMA FUNCAO CREATEDATABASE QUE POR ENQUANTO Sî VERIFICA SE UM ARQUIVO EXISTE
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
