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
  QProcess qemu_process;//!<le processus du lancement de QEMU
  Observer* observer;
  int obs_loops_nb;//!


public:
  Launcher(Log_creator* log, int loop_nb = 5);
  ~Launcher();
  bool run_qemu(const QString& pok_appli_path);
  void exit_qemu();
  // Only meaningfull if we do not start qemu with "make run"
  //  QProcess::ProcessState qemu_state(); 
  void start_observation(Fault* fault);
};

#endif
