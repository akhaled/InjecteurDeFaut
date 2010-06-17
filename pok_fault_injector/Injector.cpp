#include <iostream>
#include <stdlib.h>
#include "Injector.hh"
#include <QTextStream>
#include <QByteArray>
#include <QStringList>
#include <QProcess>

using namespace std;

/*!
*  \brief Constructeur
*
*  Constructeur de la classe Injector
*
*  \param *Log : le rapport
*  \param & config_file : le chemin absolue du fichier de configuration 
*  \param & file_entry : l'entrée du fichier
*/
Injector::Injector(Log_creator *Log, const QString & config_file, const QString & file_entry){

    factory = new Fault_factory();
    source = new Source_creator(config_file);
    error_handler = Log;
    initialize_environment(config_file, file_entry);
    initialize_fault_list(file_entry);   
    injector_code_path_file_name = pok_appli_path + "/send.c";
    observer_code_path_file_name = pok_appli_path + "/receive.c";

}

/*!
*  \brief return pok_appli_path
*
*  Methode qui renvoie pok_appli_path
*
*  \return QString pok_appli_path
*/
QString Injector::get_pok_appli_path(){
    return pok_appli_path;
}

/*!
*  \brief preparation de l'environnement
*
*  Methode qui initializer les parametres de l'environnement
*
*  \param & config_file : le chemin absolue du fichier de configuration 
*  \param & file_entry : l'entrée du fichier
*/
void Injector::initialize_environment(const QString & config_file, const QString & file_entry){

    error_handler->write_message(msg);

    fichier_config.setFileName(config_file);
    fichier_entre.setFileName(file_entry);

    //!Verifie que le fichier config existe
    if(fichier_config.exists()){

        //!verifie l'existence des chemins indiques dans le fichier
      fichier_config.open(QIODevice::ReadOnly);
      QTextStream in(&fichier_config);
      QString line= in.readLine();
      QDir dir;
      bool valid=true;

      while (!line.isEmpty() && valid) {
        	dir = QDir(line);
        	valid = dir.exists();
        	pok_appli_path = line;
            line= in.readLine();
    	}

    	if(valid){
          msg =  "fichier config OK";
          error_handler->write_message(msg);
    	}
    	else{
          msg = "ERREUR: repertoires manquants";
          error_handler->write_error(msg);
          exit(0);
    	}
        fichier_config.close();
    }
    else{
      msg = "ERREUR: impossible de trouver " + config_file;
      error_handler->write_error(msg);
      exit(0);
    }

    //!verifie que le fichier donne en entrée existe
    if(fichier_entre.exists()){

	/*
	A completer!!!!!!!!!!!!!!!!!
        verifier contenu de file_entry
	*/


      msg = "fichier d'entre OK";
      error_handler->write_message(msg);
    }
    else{
      msg = "ERREUR: impossible de trouver " + file_entry;
      error_handler->write_error(msg);
      exit(0);
    }
}

//creation liste de fautes ==========================================================================================
/*!
*  \brief preparation de l'environnement
*
*  Methode qui initializer les parametres de l'environnement
*
*  \param & config_file : le chemin absolue du fichier de configuration 
*  \param & file_entry : l'entrée du fichier
*/
void Injector::initialize_fault_list(const QString & file_entry){

    msg = "***************Initialisation liste de fautes**********************************";

    error_handler->write_message(msg);

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
          
          error_handler->write_message(msg);
        }
        else{
          msg = "ERREUR: impossible de trouver " + list.at(0) + "-" + list.at(1) + ".fault";
          error_handler->write_error(msg);
        }

        line = in.readLine();
    }
    entry_file.close();
}

/*!
*  \brief verifier le validité du fichier .fault
*
*  Methode qui permet de verifier le fichier .fault correspondant à la faute en cours existe
*
*  \param id_fault : identificateur du type de faute
*  \param id_target : identificateur de la cible de la faute
*  \return TRUE si le fichier .fault est valide, sinon retourne FALSE
*/
bool Injector::fault_file_is_valid(QString id_fault, QString id_target){

    QString fault_file_name = id_fault + "-" + id_target + ".fault";
    QFile fault_file(fault_file_name);
    return fault_file.exists();
}


/*!
*  \brief injection de la faute et generation du code POK
*
*  Methode qui injecte la faute et genere le code POK
*
*  \return  Fault* current_fault
*/
Fault* Injector::inject(){

    
    current_fault = factory->next_fault();
    
    if(current_fault == NULL){
        return NULL;
    }


    msg = "***************generation des fichiers C**********************************";

    error_handler->write_message(msg);
    
    QString fault_file_name = current_fault->get_id_fault() + "-" + current_fault->get_id_target() + ".fault";
    source->create_C_file(fault_file_name);

    QFile fichier_inject;
    QFile fichier_obs;
        
    fichier_inject.setFileName(injector_code_path_file_name);    	
    fichier_obs.setFileName(observer_code_path_file_name);

    bool valid = fichier_inject.exists() && fichier_obs.exists();

    if(valid){
    	msg = "fichiers.C OK";
        error_handler->write_message(msg);
    }
    else{
      msg = "ERREUR fichier.C manquants";
      error_handler->write_error(msg);
      exit(0);
    }
    
    //!generation code POK
    msg = "***************generation code POK**********************************";

    error_handler->write_message(msg);

    valid = source->generate_pok_code();
    if(valid){
        msg = "generation code POK OK";
        error_handler->write_message(msg);
    }
    else{
      msg = "ERREUR generation code POK";
      error_handler->write_error(msg);
    }

    return current_fault;
}


/*!
*  \brief Destructeur 
*/
Injector::~Injector(){
    delete factory;
    delete source;
}

