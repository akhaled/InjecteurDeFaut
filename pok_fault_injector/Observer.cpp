#include <iostream>
#include <QDataStream>
#include <QByteArray>
#include <QString>
#include <QChar>
#include "unistd.h"
#include "Observer.hh"

#define SOCKET_PATH "/tmp/socket"
#define QEMU_FIRST_STRING_LENGTH 63
//#define GET_RAM_COMMAND "xp "
#define RAM_TO_FILE_COMMAND "pmemsave"
#define RAM_SIZE 128*1024*1024
#define RAM_START 0
#define EXIT_COMMAND "quit"


Observer::Observer() {
  socket_path = QString(SOCKET_PATH);
  qemu_server.listen(socket_path);
}

Observer::~Observer()
{
  qemu_server.close();
  qemu_socket->disconnectFromServer();
  delete qemu_socket;
}


// Wait for QEMU to connect to our local server: qemu_server
// Return false if we waited too long
bool Observer::connect_to_qemu() {
  int time = 0;

  while(!qemu_server.waitForNewConnection() && time < 10)
    {
      usleep(1000000);
      time++;
    }  
  qemu_socket = qemu_server.nextPendingConnection();

  if(time < 10)
    {
      qemu_socket->waitForReadyRead();
    }

  return (time < 10);
}


void Observer::disconnect_from_qemu() {
  qemu_socket->disconnectFromServer();
}

void Observer::exit_qemu() {
  QDataStream in(qemu_socket);
  QString command(EXIT_COMMAND);
  command.append('\n');

  in << command.toAscii();
  
  qemu_socket->waitForBytesWritten();
  qemu_socket->waitForReadyRead();

}

// Copy QEMU RAM into a file
void Observer::ram_to_file(const QString& file_path)
{  
  // int readen = 0;
  QDataStream in(qemu_socket);
  QString converter;
  QString command(RAM_TO_FILE_COMMAND);
  command.append(' ');
  command.append(converter.setNum(RAM_START));
  command.append(' ');
  command.append(converter.setNum(RAM_SIZE));
  command.append(' ');
  command.append(file_path);
  command.append('\n');

  in << command.toAscii();

  // Wait for the file to be written
  qemu_socket->waitForBytesWritten();
  qemu_socket->waitForReadyRead();

}
