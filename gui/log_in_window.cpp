#include "log_in_window.h"

//#include <QApplication>

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QErrorMessage>
#include <unistd.h>

#define HORIZONTAL_MOVE_LIMIT 20

log_in_window::log_in_window(QWidget* p)
    : QDialog(p)
{
	create_username_layout();
	create_passwd_layout();
	create_button_layout();
	create_error_layout();
	connect_signal_slot();
	create_main_layout();
}

void log_in_window::checking_login_fields(const QString& s)
{
	if (m_uname_line_edit->text().isEmpty() ||
            m_upasswd_line_edit->text().isEmpty()) {
		m_login_button->setEnabled(false);
		m_reg_button->setEnabled(false);
	} else {
		m_login_button->setEnabled(true);
		m_reg_button->setEnabled(true);
	}
}

void log_in_window::checkin_login()
{
	emit login(m_uname_line_edit->text(), m_upasswd_line_edit->text());
}

void log_in_window::new_registration()
{
	emit registration(m_uname_line_edit->text(), m_upasswd_line_edit->text());
}

void log_in_window::create_username_layout()
{
	m_uname_label = new QLabel("User name");
	m_uname_line_edit = new QLineEdit;
	m_uname_layout = new QHBoxLayout;
	m_uname_layout->addWidget(m_uname_label);
	m_uname_layout->addWidget(m_uname_line_edit);
}

void log_in_window::create_passwd_layout()
{
	m_upasswd_label = new QLabel("Password");
	m_upasswd_line_edit = new QLineEdit;
	m_upasswd_line_edit ->setEchoMode(QLineEdit::Password);
	m_upasswd_layout = new QHBoxLayout;
	m_upasswd_layout -> addWidget(m_upasswd_label);
	m_upasswd_layout -> addStretch();
	m_upasswd_layout -> addWidget(m_upasswd_line_edit);
}

void log_in_window::create_error_layout()
{
	m_error_layout = new QHBoxLayout;
	m_error_label  = new QLabel(/*"Erro"*/);
	m_error_layout->addWidget(m_error_label);
}

void log_in_window::show_login_error(const QString &s)
{
	m_error_label->setAlignment(Qt::AlignRight);
	m_error_label->setText(s);
	QRect r = geometry();
	int x = r.x();
	int y = r.y();
	for (int i = 0; i < 70; ++i) {
		move(r.x() + HORIZONTAL_MOVE_LIMIT, r.y());
		sleep(0.8);
		move(x, y);
		move(r.x() - HORIZONTAL_MOVE_LIMIT, r.y());
	}
	move(x,y);
}

void log_in_window::create_button_layout()
{
	m_reg_button = new QPushButton("Registration");
	m_reg_button->setEnabled(false);
	m_login_button = new QPushButton("LogIn");
	m_login_button->setEnabled(false);
	m_butt_layout = new QHBoxLayout;
	m_butt_layout->addWidget(m_reg_button);
	m_butt_layout->addWidget(m_login_button);
}

void log_in_window::create_main_layout()
{
	QVBoxLayout* reg_layout = new QVBoxLayout;
	reg_layout->addLayout(m_uname_layout);
	reg_layout->addLayout(m_upasswd_layout);
	reg_layout->addLayout(m_error_layout);
	reg_layout->addLayout(m_butt_layout);
	setLayout(reg_layout);
	setWindowTitle("ITC Local Messenger");
	setFixedHeight(sizeHint().height());
	setFixedWidth(sizeHint().width());
}

void log_in_window::connect_signal_slot()
{
	QObject::connect(m_uname_line_edit,SIGNAL(textChanged(const QString&)),
			this, SLOT(checking_login_fields(const QString&)));
	QObject::connect(m_upasswd_line_edit,SIGNAL(textChanged(const QString&)),
			this, SLOT(checking_login_fields(const QString&)));
	QObject::connect(m_login_button, SIGNAL(clicked()),
			this, SLOT(checkin_login()));
	QObject::connect(m_reg_button,SIGNAL(clicked()),
			this, SLOT(new_registration()));
}

