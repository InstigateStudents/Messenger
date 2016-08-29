#include "messenger.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	// TODO specify the IP of the main server
	messenger m("123");
	m.run();
	return a.exec();
}
