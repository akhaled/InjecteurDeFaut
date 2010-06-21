#ifndef SOURCE_CREATOR_H
#define SOURCE_CREATOR_H

#include <QtCore/qtextstream.h>
#include <QtCore/qfile.h>
#include "QtGui/qmessagebox.h"
#include <QtCore/qdir.h>
#include <QtCore/qprocess.h>


class Source_creator
{
   public:
   Source_creator(QString config_file_path);

   public:
   void create_C_file(QString fault_file_path);
   bool generate_pok_code();
   QString concatenate(QString str1, QString str2);
   const QString & get_pok_path();


   private:
   QString pok_appli_path;//!<le chemin du répertoire dans lequel les fichiers .c devront être créés
   QString pok_path;//!<le chemin vers le répertoire des sources de POK
   QString ocarina_path;//!<le chemin du répertoire des binaires d’ocarina (pour permettre la configuration de l’environnement avant la compilation)
   QString injector_code_path_file_name;//!<le nom du fichier .c à créer avec le code de la faute
   QString observer_code_path_file_name;//!<le nom du fichier .c à créer avec le code d’observation
   QString pok_exemple_path;
   QString config;//!<variable interne du processus
   QFile fichier;//!<variable interne du processus
   QTextStream destination;//!<variable interne du processus
   QString message;//!<chaine de caractere du message à afficher
   QString code;//!<code à récupérer
   QString code_inj;//!<<variable interne du processus
   QString code_obs;//!<<variable interne du processus
   QString str1;//!<tag de début de code à récupérer
   QString str2;//!<tag de fin de code à récupérer
   QString signature;//!<<variable interne du processus
   QFile file;
   QString path_temp; 
  
};





#endif // SOURCE_CREATOR_H
