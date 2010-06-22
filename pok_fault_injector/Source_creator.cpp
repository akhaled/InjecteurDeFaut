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
   //pok_appli_path = in.readLine();
   //injector_code_path_file_name = pok_appli_path + "/send.c";
   //observer_code_path_file_name = pok_appli_path + "/receive.c";
   fichier.close();
}

/*!
* \brief creer les fichiers C
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
    
    
   
    /*fichier.setFileName(config);
    if(!fichier.open(QIODevice::ReadOnly))
    {
        message = "Impossible d'ouvrir le fichier " + fichier.fileName();
        cout << message.toStdString()<< endl;
        exit(0);
    }
    code_obs = Source_creator::concatenate("#DEBUT OBSERVER#", "#FIN OBSERVER#");
    fichier.close();*/
   
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
    //cout << "path_appli_path= " + pok_appli_path.toStdString()<< endl;
    
    while (!in_int.atEnd())
          {
           path_temp = in_int.readLine();
           //cout << "path_temp= " + path_temp.toStdString()<< endl; 
           file.setFileName(path_temp);
           QString s = "/";
           int ix = path_temp.lastIndexOf(s); 
           //cout << "ix = " + ix<< endl;
           int size = path_temp.size();
           //cout << "size = " + size<< endl;
           path_temp = path_temp.right(size-ix);
           //cout << "path_temp_con= " + path_temp.toStdString()<< endl;
           file.copy(pok_appli_path + path_temp);
          }
    fichier.remove();

    /*fichier.setFileName(observer_code_path_file_name);
    if(!fichier.open(QIODevice::WriteOnly | QIODevice::Text)){
        message = "Impossible d'ouvrir le fichier " + fichier.fileName();
        cout << message.toStdString()<< endl;
        exit(0);
    }
   destination.setDevice(& fichier);
   destination << code_obs;
   fichier.close();*/
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

  //    QString env1 = "POK_PATH=" + pok_path;
  //    QString env2 = "PATH=" + ocarina_path + ":" + getenv("PATH");

    QString chemin = pok_appli_path;
    //QProcess process;
    //cout << env1.toStdString()<< endl;
    //process.start("export POK_PATH=/cal/nfs3/mspcasi/ngougo/Documents/pok-20100317");
    //process.waitForFinished();

    //cout << env2.toStdString()<< endl;
    //process.start("export PATH=/cal/nfs3/mspcasi/ngougo/Documents/ocarina-2.0w-suite-x86-linux-20100610/bin:$PATH");
   // process.waitForFinished();

    /*
    putenv(env1.toAscii().data());
    putenv(env2.toAscii().data());

    cout << getenv("PATH") << endl
         << getenv("POK_PATH") << endl;
    */
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
* \brief recuperer le code
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
