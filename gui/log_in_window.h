#ifndef LOG_IN_WINDOW_H
#define LOG_IN_WINDOW_H

#include <QDialog>

class QLabel;
class QLineEdit;
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;



class log_in_window : public QDialog
{
        Q_OBJECT
public:
        log_in_window(QWidget* parent = 0);

private slots:
        void checking_login();
signals:
	void login(const QString&, const QString&);

private:
        QHBoxLayout *uname_layout;
        QLabel *uname_label;
        QLineEdit *uname_line_edit;

        QHBoxLayout *upasswd_layout;
        QLabel *upasswd_label;
        QLineEdit *upasswd_line_edit;

	QHBoxLayout *error_layout;
	QLabel *error_label;

        QHBoxLayout *butt_layout;
        QPushButton *reg_button;
        QPushButton *login_button;

        void connect_signal_slot();
        void create_username_layout();
        void create_passwd_layout();
        void create_button_layout();
        void create_main_layout();
};

#endif // LOG_IN_WINDOW_H
