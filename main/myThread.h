#ifndef _MYTHREAD_H
#define _MYTHREAD_H

#include <QObject>
#include <QThread>


class my_thread:  public QThread
{
	Q_OBJECT
private:
		void run();
		
signals:
		void refresh();
};

#endif //_MYTHREAD_H
