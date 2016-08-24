#include "log_in_window.h"

//#include <QApplication>

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QErrorMessage>



log_in_window::log_in_window(QWidget* parent) :QDialog(parent)
{
	create_username_layout();

	create_passwd_layout();

	create_button_layout();

	connect_signal_slot();

	create_main_layout();
	
}

void log_in_window::checking_login()
{
	if (uname_line_edit->text().isEmpty() || upasswd_line_edit->text().isEmpty()) {
		QErrorMessage *error = new QErrorMessage;
		error->showMessage("User nmae or Password fild \n is empty");
	} else {
		emit login(uname_line_edit->text(), upasswd_line_edit->text());
	}
}

void log_in_window::create_username_layout()
{
	uname_label = new QLabel("User name");
	uname_line_edit = new QLineEdit;

	uname_layout = new QHBoxLayout;
	uname_layout -> addWidget(uname_label);
	uname_layout -> addWidget(uname_line_edit);
}

void log_in_window::create_passwd_layout()
{
	upasswd_label = new QLabel("Password");
	upasswd_line_edit = new QLineEdit;
	upasswd_line_edit ->setEchoMode(QLineEdit::Password);

	upasswd_layout = new QHBoxLayout;
	upasswd_layout -> addWidget(upasswd_label);
	upasswd_layout -> addStretch();
	upasswd_layout -> addWidget(upasswd_line_edit);
}

void log_in_window::create_button_layout()
{
	reg_button = new QPushButton("Registration");
	login_button = new QPushButton("LogIn");

	butt_layout = new QHBoxLayout;
	butt_layout -> addWidget(reg_button);
	butt_layout -> addWidget(login_button);
}

void log_in_window::create_main_layout()
{
	QVBoxLayout* reg_layout = new QVBoxLayout;
	reg_layout -> addLayout(uname_layout);
	reg_layout -> addLayout(upasswd_layout);
	reg_layout -> addLayout(butt_layout);

	setLayout(reg_layout);
	setWindowTitle("ITC Local Messenger");
	setFixedHeight(sizeHint().height());
	setFixedWidth(sizeHint().width());
}

void log_in_window::connect_signal_slot()
{
    //connecion
    QObject::connect(login_button, SIGNAL(clicked()),
                    this, SLOT(checking_login()));


}
