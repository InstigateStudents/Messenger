#include "messenger.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	messenger m;
	m.run();
	return a.exec();
}
