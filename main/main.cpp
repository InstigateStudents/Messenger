#include "messenger.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	messenger m("192.168.68.111");
	m.run();
	return a.exec();
}
