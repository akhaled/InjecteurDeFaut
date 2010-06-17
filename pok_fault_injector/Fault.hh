#ifndef DEF_FAULT
#define DEF_FAULT

#include <QString>
#include <QStringList>

class Fault{

	public:
	Fault(QString id_fault, QString id_target);
	QStringList get_obs_vars();
	QString get_id_fault();
	QString get_id_target();
	int *get_lengths();

	private:
	QString id_target;//!<identificateur de la cible de la faute
	QString id_fault;//!<identificateur du type de faute
        QStringList obs_vars;//!<la liste des variables à récupérer dans la RAM de QEMU par la partie observation. Lors de son instanciation, elle ira chercher cette liste dans son fichier .fault
	int lengths[];//!<un tableau d’entier contenant la taille des variables précédentes en nombre d’octet


};


#endif
