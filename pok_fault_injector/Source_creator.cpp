#include "Fault.hh"
#include <iostream>
#include <stdlib.h>


#include "Source_creator.hh"
using namespace std;

/*!
* \brief Constructeur
*
* Constructeur de la classe Source_creator
*
* \param config_file_path : le chemin absolue du fichier de configuration
*/
Source_creator::Source_creator(QString config_file_path){

   fichier.setFileName(config_file_path);

   if(!fichier.open(QIODevice::ReadOnly)){
        QString msg = "impossible d'ouvrir " + fichier.fileName();
        cout << "\033[31m" << msg.toStdString()<< endl;
        cout << "\033[30m" << endl;
        exit(0);
    }
   QTextStream in(&fichier);

   pok_path = in.readLine();
   ocarina_path = in.readLine();
   fichier.close();
}

/*!
* \brief Creer les fichiers C
*
* Creer les fichiers C du code injecteur de fautes et de l'observateur
*
* \param fault_file_path : le chemin absolue du fichier faute
*/
bool Source_creator::create_C_file(Fault* fault){
  config = fault->get_fault_file_path();
  pok_appli_path = fault->get_pok_appli_path();
  fichier.setFileName(config);
  if(!fichier.open(QIODevice::ReadOnly))
    {
      return false;
    }
  code_inj = Source_creator::concatenate("#DEBUT FICHIER# ", "#FIN FICHIER# ");
  fichier.close();
   
  fichier.setFileName(pok_appli_path + "/temp.txt");
    if(!fichier.open(QIODevice::WriteOnly | QIODevice::Text)){
        return false;
    }
    destination.setDevice(&fichier);
    destination << code_inj;
    fichier.close();

    if(!fichier.open(QIODevice::ReadOnly)){
         return false;
    }
    QTextStream in_int(&fichier);
    
    while (!in_int.atEnd())
          {
           path_temp = in_int.readLine();
           file.setFileName(path_temp);
           QString s = "/";
           int ix = path_temp.lastIndexOf(s); 
           int size = path_temp.size();
           path_temp = path_temp.right(size-ix);
           file.copy(pok_appli_path + path_temp);
          }
    fichier.remove();

    return true;
}

/*!
* \brief Generer code pok
*
* Generer le code pok à partir du model AADL et des fichiers C de l'application
*
* \return TRUE si la generation est terminée avec succés, sinon return FALSE
*/
bool Source_creator::generate_pok_code(){

    //mise en place des variables d'environnement

    QString chemin = pok_appli_path;

    QProcess process1;
    
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    
    env.insert("POK_PATH", pok_path);
    env.insert("PATH", env.value("PATH") + ":" + ocarina_path);
    process1.setProcessEnvironment(env);
    process1.setWorkingDirectory( chemin);
    process1.start("make");
    bool var = process1.waitForFinished();
    if (var == false) {
        return false;
    }
    else{
        chemin.append("/generated-code");
        QDir dir_gen(chemin);
    if(!dir_gen.exists()){
          return false;
    }
    return true;
  }
}

/*!
* \brief Recuperer le code
*
* Recuperer le code entre les tags
*
* \param str1 : tag de début de code à récupérer
* \param str2 : tag de fin de code à récupérer
* \return QString code
*/
QString Source_creator::concatenate(QString str1, QString str2) {

  QString s1 = str1;
  QString s2 = str2;
  destination.setDevice(&fichier);
  code = "";
  message= "";

  message = destination.readLine();

  while ((QString::compare(message, s1, Qt::CaseInsensitive))!=0){
    message = destination.readLine();
  }

  
  while (true){
    message = destination.readLine();
    if ((QString::compare(message, s2, Qt::CaseInsensitive))!=0){
      code.append(message);
      code.append("\n");
    }
    else break;
  }
  code.append("\0");
  return code;
}


const QString& Source_creator::get_pok_path(){
return pok_path;
}
