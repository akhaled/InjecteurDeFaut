#include <iostream>
#include <QDir>
#include <unistd.h>
#include "Launcher.hh"
#define QEMU_COMMAND "make -C generated-code run"
#define TIME 1000000
#define RAM_FILE_NAME "qemu_ram"
//#define QEMU_COMMAND "qemu -cdrom xubuntu-10.04-desktop-i386.iso"

Launcher::Launcher(Log_creator* log, const QString& pok_ap_path,
                   int loop_nb): log_creator(log),
                                 pok_appli_path(pok_ap_path),
                                 obs_loops_nb(loop_nb)
{

  // Create the observer
  observer= new Observer();
}


Launcher::~Launcher()
{ 
  delete observer;
}


bool Launcher::run_qemu() {
  QString command(QEMU_COMMAND);

  //Go in the pok appli path to launch the command
  QDir::setCurrent(pok_appli_path);
  
  // Redirect QEMU output : doesn't work yet
  // qemu_process.setStandardOutputFile(QString("QemuOutput"));
  // qemu_process.setStandardErrorFile(QString("QemuError"));


  return qemu_process.startDetached(command);

}

void Launcher::exit_qemu() {
  observer->exit_qemu();
}

/* This method is usefull if we launch qemu ourselves, not with "make run"
QProcess::ProcessState Launcher::qemu_state() {
  return qemu_process.state();
}
*/

void Launcher::start_observation(Fault* fault) {

  log_creator->set_fault(fault);

  // Launch QEMU with POK
  if(!run_qemu())
    {
      log_creator->write_error(QString("Can't launch QEMU."));
      return;
    }
  else log_creator->write_message(QString("QEMU launched"));

  // Connect to QEMU monitor
  if(!observer->connect_to_qemu())
    {
      log_creator->write_error(QString("Can't connect to QEMU."));
      exit_qemu();
      return;
    }
  else log_creator->write_message(QString("Connected to QEMU"));
  
  
  for(int i = 0; i < obs_loops_nb; i++)
    {
      // Copy QEMU ram into file RAM_FILE_NAME and parse it to find the variables
      observer->ram_to_file(RAM_FILE_NAME);
      if(!log_creator->parse_ram(RAM_FILE_NAME))
        {
          log_creator->write_error("Can't find the tag in the ram.");
        }
      else
        {
          log_creator->write_obs_vars();
        }
        usleep(TIME);
    }


  
  exit_qemu();
  log_creator->write_message("exit QEMU");


}
