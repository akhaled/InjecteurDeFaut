#ifndef LAUNCHER_HH
#define LAUNCHER_HH

#include <QString>
#include <QProcess>

#include "Observer.hh"
#include "Log_creator.hh"

class Launcher
{
private:
  Log_creator* log_creator;
  QString pok_appli_path;
  QProcess qemu_process;
  Observer* observer;
  int obs_loops_nb;


public:
  Launcher(Log_creator* log, const QString& pok_app_path, int loop_nb = 1);
  ~Launcher();
  bool run_qemu();
  void exit_qemu();
  // Only meaningfull if we do not start qemu with "make run"
  //  QProcess::ProcessState qemu_state(); 
  void start_observation(Fault* fault);
};

#endif
