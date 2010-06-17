#include <iostream>
#include <stdlib.h>
#include "Injector.hh"
<<<<<<< HEAD
#include<QTextStream>
#include<QByteArray>
#include<QStringList>
#include<QProcess>
=======
#include <QTextStream>
#include <QByteArray>
#include <QStringList>
#include <QProcess>
>>>>>>> 3f2203b66795c640bbbf9216d4e03d884443fe25

using namespace std;


Injector::Injector(Log_creator *Log, const QString & config_file, const QString & file_entry){

    factory = new Fault_factory();
    source = new Source_creator(config_file);
    error_handler = Log;
    initialize_environment(config_file, file_entry);
    initialize_fault_list(file_entry);   
    injector_code_path_file_name = pok_appli_path + "/hello1.c";
    observer_code_path_file_name = pok_appli_path + "/hello2.c";
}

QString Injector::get_pok_appli_path(){
    return pok_appli_path;
}

//preparation de l'environnement====================================================================================
void Injector::initialize_environment(const QString & config_file, const QString & file_entry){

    msg = QString("************Preparation de l'environement********************");
    cout << msg.toStdString()<< endl;
<<<<<<< HEAD
    error_handler->write_message(msg);
=======
    error_handler->write(msg);
>>>>>>> 3f2203b66795c640bbbf9216d4e03d884443fe25

    fichier_config.setFileName(config_file);
    fichier_entre.setFileName(file_entry);

    //Verifie que le fichier config existe
    if(fichier_config.exists()){

        //verifie l'existence des chemins indiques dans le fichier
        fichier_config.open(QIODevice::ReadOnly);
        QTextStream in(&fichier_config);
        QString line= in.readLine();
	QDir dir;
    	bool valid=true;

   	while (!line.isEmpty() && valid) {
        	dir = QDir(line);
        	valid = dir.exists();
        	pok_appli_path = line;
<<<<<<< HEAD
                line= in.readLine();
    	}

    	if(valid){
        	msg =  "fichier config OK";
		cout << msg.toStdString()<< endl;
        	error_handler->write_message(msg);
    	}
    	else{
          msg = "ERREUR: repertoires manquants";
          cout << "\033[31m" << msg.toStdString()<< endl;
          cout << "\033[30m" << endl;
          error_handler->write_error(msg);
          exit(0);
    	}
        fichier_config.close();
    }
    else{
      msg = "ERREUR: impossible de trouver " + config_file;
      cout << "\033[31m" << msg.toStdString()<< endl;
      cout << "\033[30m" << endl;
      error_handler->write_error(msg);
      exit(0);
=======
                line= in.readLine();	
    	}
	
    	if(valid){
        	msg =  "fichier config OK";
		cout << msg.toStdString()<< endl;
        	error_handler->write(msg);		
    	}
    	else{
		msg = "ERREUR: repertoires manquants";
		cout << "\033[31m" << msg.toStdString()<< endl;
		cout << "\033[30m" << endl;
        	error_handler->write_error(msg);
        	exit(0);
    	}
	fichier_config.close();
    }
    else{
       	msg = "ERREUR: impossible de trouver " + config_file;
	cout << "\033[31m" << msg.toStdString()<< endl;
	cout << "\033[30m" << endl;
        error_handler->write_error(msg);
        exit(0);
>>>>>>> 3f2203b66795c640bbbf9216d4e03d884443fe25
    }

    //verifie que le fichier donne en entrée existe
    if(fichier_entre.exists()){

	/*
	A completer!!!!!!!!!!!!!!!!!
        verifier contenu de file_entry
	*/


<<<<<<< HEAD
      msg = "fichier d'entre OK";
      cout << msg.toStdString()<< endl;
      error_handler->write_message(msg);
    }
    else{
      msg = "ERREUR: impossible de trouver " + file_entry;
      cout << "\033[31m" << msg.toStdString()<< endl;
      cout << "\033[30m" << endl;
      error_handler->write_error(msg);
      exit(0);
=======
        msg = "fichier d'entre OK";
	cout << msg.toStdString()<< endl;
        error_handler->write(msg);
    }
    else{
        msg = "ERREUR: impossible de trouver " + file_entry;
	cout << "\033[31m" << msg.toStdString()<< endl;
	cout << "\033[30m" << endl;
        error_handler->write_error(msg);
        exit(0);
>>>>>>> 3f2203b66795c640bbbf9216d4e03d884443fe25
    }
}

//creation liste de fautes ==========================================================================================
void Injector::initialize_fault_list(const QString & file_entry){

    msg = "***************Initialisation liste de fautes**********************************";
    cout << msg.toStdString()<< endl;
<<<<<<< HEAD
    error_handler->write_message(msg);
=======
    error_handler->write(msg);
>>>>>>> 3f2203b66795c640bbbf9216d4e03d884443fe25

    QFile entry_file(file_entry);
    entry_file.open(QIODevice::ReadOnly);
    QTextStream in(&entry_file);
    QString line= in.readLine();
    QStringList list;

    while (!line.isEmpty()) {

        list = line.split(",");

        bool valid = fault_file_is_valid(list.at(0), list.at(1));

        if(valid){

            factory->add_fault(list.at(0), list.at(1));
            msg = "Ajout de " + list.at(0) + "-" + list.at(1) + " a la liste de fautes";
	    cout << msg.toStdString()<< endl;
<<<<<<< HEAD
            error_handler->write_message(msg);
        }
        else{
          msg = "ERREUR: impossible de trouver " + list.at(0) + "-" + list.at(1) + ".fault";
          cout << "\033[31m" << msg.toStdString()<< endl;
          cout << "\033[30m" << endl;
          error_handler->write_error(msg);
=======
            error_handler->write(msg);
        }
        else{
            msg = "ERREUR: impossible de trouver " + list.at(0) + "-" + list.at(1) + ".fault";
	    cout << "\033[31m" << msg.toStdString()<< endl;
            cout << "\033[30m" << endl;
            error_handler->write_error(msg);
>>>>>>> 3f2203b66795c640bbbf9216d4e03d884443fe25
        }

        line = in.readLine();
    }
    entry_file.close();
}


//permet de verifier le fichier .fault correspondant à la faute en cours existe=================================================================
bool Injector::fault_file_is_valid(QString id_fault, QString id_target){

    QString fault_file_name = id_fault + "-" + id_target + ".fault";
    QFile fault_file(fault_file_name);
    return fault_file.exists();
}


//injection de la faute et genration du code POK==========================================================================
Fault* Injector::inject(){

    msg = "***************generation des fichiers C**********************************";
    cout << msg.toStdString()<< endl;
<<<<<<< HEAD
    error_handler->write_message(msg);
=======
    error_handler->write(msg);
>>>>>>> 3f2203b66795c640bbbf9216d4e03d884443fe25
    
    current_fault = factory->next_fault();
    
    if(current_fault == NULL){
        return NULL;
    }
    
    QString fault_file_name = current_fault->get_id_fault() + "-" + current_fault->get_id_target() + ".fault";
    source->create_C_file(fault_file_name);

    QFile fichier_inject;
    QFile fichier_obs;
        
    fichier_inject.setFileName(injector_code_path_file_name);    	
    fichier_obs.setFileName(observer_code_path_file_name);

    bool valid = fichier_inject.exists() && fichier_obs.exists();

    if(valid){
    	msg = "fichiers.C OK";
        cout << msg.toStdString()<< endl;
<<<<<<< HEAD
        error_handler->write_message(msg);
    }
    else{
      msg = "ERREUR fichier.C manquants";
      cout << "\033[31m" << msg.toStdString()<< endl;
      cout << "\033[30m" << endl;
      error_handler->write_error(msg);
      exit(0);
=======
        error_handler->write(msg);
    }
    else{
        msg = "ERREUR fichier.C manquants";
	cout << "\033[31m" << msg.toStdString()<< endl;
	cout << "\033[30m" << endl;
        error_handler->write_error(msg);
        exit(0);
>>>>>>> 3f2203b66795c640bbbf9216d4e03d884443fe25
    }
    
    //generation code POK
    msg = "***************generation code POK**********************************";
    cout << msg.toStdString()<< endl;
<<<<<<< HEAD
    error_handler->write_message(msg);
=======
    error_handler->write(msg);
>>>>>>> 3f2203b66795c640bbbf9216d4e03d884443fe25

    valid = source->generate_pok_code();
    if(valid){
        msg = "generation code POK OK";
        cout << msg.toStdString()<< endl;
<<<<<<< HEAD
        error_handler->write_message(msg);
    }
    else{
      msg = "ERREUR generation code POK";
      cout << "\033[31m" << msg.toStdString()<< endl;
      cout << "\033[30m" << endl;
      error_handler->write_error(msg);
=======
        error_handler->write(msg);
    }
    else{
        msg = "ERREUR generation code POK";
	cout << "\033[31m" << msg.toStdString()<< endl;
	cout << "\033[30m" << endl;
        error_handler->write_error(msg);
>>>>>>> 3f2203b66795c640bbbf9216d4e03d884443fe25
    }

    return current_fault;
}


//liberation de la memoire=======================================================================
Injector::~Injector(){
    delete factory;
    delete source;
    delete current_fault;
}

<<<<<<< HEAD
=======















>>>>>>> 3f2203b66795c640bbbf9216d4e03d884443fe25
