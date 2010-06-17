#include "Source_creator.hh"
#include <iostream>
#include <stdlib.h>
using namespace std;

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
   pok_appli_path = in.readLine();
   injector_code_path_file_name = pok_appli_path + "/hello1.c";
   observer_code_path_file_name = pok_appli_path + "/hello2.c";
   fichier.close();
}

//--------------------------------creer les fichiers C--------------------------------------------------
void Source_creator::create_C_file(QString fault_file_path){
    config = fault_file_path;
   
    fichier.setFileName(config);
    if(!fichier.open(QIODevice::ReadOnly))
    {
        message = "Impossible d'ouvrir le fichier " + fichier.fileName();
        cout << message.toStdString()<< endl;
        exit(0);
    }
    code_inj = Source_creator::concatenate("#DEBUT INJECTER# ", "#FIN INJECTER# ");
    fichier.close();
   
    fichier.setFileName(config);
    if(!fichier.open(QIODevice::ReadOnly))
    {
        message = "Impossible d'ouvrir le fichier " + fichier.fileName();
        cout << message.toStdString()<< endl;
        exit(0);
    }
    code_obs = Source_creator::concatenate("#DEBUT OBSERVER#", "#FIN OBSERVER#");
    fichier.close();
   
    fichier.setFileName(injector_code_path_file_name);
    if(!fichier.open(QIODevice::WriteOnly | QIODevice::Text)){
        message = "Impossible d'ouvrir le fichier " + fichier.fileName();
        cout << message.toStdString()<< endl;
        exit(0);
    }
    destination.setDevice(&fichier);
    destination << code_inj;
    fichier.close();

    fichier.setFileName(observer_code_path_file_name);
    if(!fichier.open(QIODevice::WriteOnly | QIODevice::Text)){
        message = "Impossible d'ouvrir le fichier " + fichier.fileName();
        cout << message.toStdString()<< endl;
        exit(0);
    }
   destination.setDevice(& fichier);
   destination << code_obs;
   fichier.close();
}


//------------------------------------------------generer code pok-----------------------------------------------------------------
bool  Source_creator::generate_pok_code(){

    //mise en place des variables d'environnement
    QString msg = "***********mise en place des variables d'environnement********";
    cout << msg.toStdString()<< endl;

    QString env1 = "export POK_PATH=" + pok_path;
    QString env2 = "export PATH=" + ocarina_path + ":$PATH";

    QString chemin = pok_appli_path; 
    //QProcess process;
    //cout << env1.toStdString()<< endl;
    //process.start("export POK_PATH=/cal/nfs3/mspcasi/ngougo/Documents/pok-20100317");
    //process.waitForFinished();

    //cout << env2.toStdString()<< endl;
    //process.start("export PATH=/cal/nfs3/mspcasi/ngougo/Documents/ocarina-2.0w-suite-x86-linux-20100610/bin:$PATH");
   // process.waitForFinished();

    QProcess process1;    
    process1.setWorkingDirectory( chemin);
    process1.start("make");
    bool var = process1.waitForFinished();
    if (var == false) { 
        return false;
    }
    else{
        chemin.append("/generated-code");
        //cout<< chemin.toStdString()<<endl;
        QDir dir_gen(chemin);
    if(!dir_gen.exists()){
          return false;
    }
    return true;
  }
}

//--------------------------------------recuperer le code entre str1 et str2-------------------------------------------------------
QString Source_creator::concatenate(QString str1, QString str2)  {

  QString s1 = str1;
  QString s2 = str2;
  destination.setDevice(&fichier);
  code = "";
  message= "";

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
