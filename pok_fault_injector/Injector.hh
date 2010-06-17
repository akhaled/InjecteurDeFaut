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
	QFile fichier_config;//!<
	QFile fichier_entre;//!<
	QString msg;//!<messages affichés pendant la processus
	Fault *current_fault;//!<la faute à injecter
	QString pok_appli_path;//!<le chemin du répertoire dans lequel les fichiers .c devront être injectéés
	QString injector_code_path_file_name;//!<le nom du fichier .c à créer avec le code de la faute
	QString observer_code_path_file_name;//!<le nom du fichier .c à créer avec le code d’observation
	Log_creator *error_handler;//!<pour la création du rapport de la campagne de test et des messages d’erreurs
	Fault_factory *factory;//!<pour la création et la gestion de la liste de fautes à injecter
        Source_creator *source;//!<pour la génération du code source et la compilation de POK
};

#endif
