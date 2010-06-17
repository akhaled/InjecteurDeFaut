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


   private:
   QString pok_appli_path;
   QString pok_path;
   QString ocarina_path;
   QString injector_code_path_file_name;
   QString observer_code_path_file_name;
   QString pok_exemple_path; 
   QString config;
   QFile fichier;
   QTextStream destination;
   QString message;
   QString code;
   QString code_inj;
   QString code_obs;
   QString str1;
   QString str2;
   QString signature;
   QString* q;
  
  
};





#endif // SOURCE_CREATOR_H
