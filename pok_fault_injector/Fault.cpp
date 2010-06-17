#include "Fault.hh"

Fault::Fault(QString id_fault, QString id_target){

    Fault::id_fault = id_fault;
    Fault::id_target = id_target;

}

QStringList Fault::get_obs_vars(){
	return Fault::obs_vars;
}

QString Fault::get_id_fault(){
	return Fault::id_fault;
}

QString Fault::get_id_target(){
	return Fault::id_target;
}

int* Fault::get_lengths(){
	return Fault::lengths;
}
