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

using namespace std;

#define debug true;
#define dbpath "database.data"
#define separator "&&##**"

class Database{
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

bool fileExists(const char *filename)
{
  ifstream ifile(filename);
  return ifile;
}

bool createDatabase(Database newdb){

	int dbid = 0;
	//if(newdb.getId()==NULL){ //tratar NULL
		dbid = newdb.getId();
	//}

	if(newdb.getName().length() == 0){
		return false;
	}

	if(newdb.getDir().length() == 0){
		return false;
	}

	if(fileExists(dbpath)){
		cout << "Arquivo ja existe";
	}else{
		cout << "Criando primeiro banco de dados";
		ofstream file;
		file.open(dbpath);
		file << 0 << separator << newdb.getName() << separator << newdb.getDir()  << separator << 1 << "\n";
		file.close();
		return true;
	}

/*

	ifstream file;
	 string line;

	  file.open ("db.data");
	  getline (file,line);
	  cout << line;
	  //filstring << myfile;
	 // myfile << newdb.getName();
	  //myfile << filstring << newdb.getName();
	  file.close();
*/
	return false;
}




int main() {



	Database dbmouro(0,"sgbdMouro","/Users/rodrigo/Desktop",true);
	cout << "resultado ao criar o banco " << createDatabase(dbmouro);

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
	Database db1(1,"banco1","/var/www/",true);  //instancia db1 do tipo database e seta os valores atrav�s do m�todo construtor --> Database(int newId, string newName, string newDir, bool newDefaultDb){
	Database db2(2,"banco222","/var/www/db1/",false);
	Database db3(3,"banco3333","/users/mouro/banco3/",false);
	Database db4(4,"banco44444","/root/db4",false);

	dbs.push_back(db1); //manda db1 pro vetor

for (int x = 0; x<dbs.size(); x++){
		cout << "id: " << dbs.at(x).getId() << "name: "<< dbs.at(x).getName()  << " dir: "<< dbs.at(x).getDir() << " default: " << dbs.at(x).getDefault() << endl;
	}

createDatabase(db1); //CHAMA FUNCAO CREATEDATABASE QUE POR ENQUANTO S� VERIFICA SE UM ARQUIVO EXISTE
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


	return 0;

}