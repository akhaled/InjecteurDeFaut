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
	QString id_target;
	QString id_fault;
        QStringList obs_vars;
	int lengths[];


};


#endif
