#include "messenger.h"
#include <QApplication>



int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	messenger ob("123");
	ob.run();
	return a.exec();
}
