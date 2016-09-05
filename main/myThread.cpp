#include "myThread.h"

#include <vector>
#include <QVector>
#include <QString>
#include <iostream>
#include <QObject>

void my_thread::run() 
{
		while (1) {
			//std::cout << "Thread is working\n";
			emit refresh();
			//std::cout << "Thread end" << std::endl;
			sleep(5);
		}
}

