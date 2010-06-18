#ifndef DEF_FAULT_FACTORY
#define DEF_FAULT_FACTORY

#include <QString>
#include <QList>
#include "Fault.hh"

class Fault_factory{

	public:
	Fault_factory();
	void add_fault(QString id_fault, QString id_target, QString pok_path);
	Fault* next_fault();

	private:
	QList<Fault *>  faults;//!la liste des fautes à injecter
};

#endif
