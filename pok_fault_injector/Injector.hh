#ifndef DEF_INJECTOR
#define DEF_INJECTOR

#include <QFile>
#include <QDir>
#include <QString>
#include "Fault.hh"
#include "Fault_factory.hh"
#include "Source_creator.hh"
#include "Log_creator.hh"


class Injector{

	public:
	Injector(Log_creator *Log, const QString & config_file, const QString & file_entry);
	~Injector();	

        QString get_pok_appli_path();
        void initialize_environment(const QString & config_file, const QString & file_entry);
	bool fault_file_is_valid(QString id_fault, QString id_cible);
	void initialize_fault_list(const QString & file_entry);
	Fault*  inject();

	private:
	QFile fichier_config;
	QFile fichier_entre;
	QString msg;
	Fault *current_fault;
	QString pok_appli_path;
	QString injector_code_path_file_name;
	QString observer_code_path_file_name;
	Log_creator *error_handler;
	Fault_factory *factory;
        Source_creator *source;
};

#endif
