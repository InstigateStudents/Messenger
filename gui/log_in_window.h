#ifndef LOG_IN_WINDOW_H
#define LOG_IN_WINDOW_H

#include <QDialog>

class QLabel;
class QLineEdit;
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;


/**
 * @brief Login/Registration window
 * 
 * @details This is the first window the user sees when running the messenger
 * application. With this window it is possible to register the first time and
 * then login using the created credentials.
 */
class log_in_window : public QDialog
{
    Q_OBJECT
private slots:
    void checking_login_fields(const QString&);
    void checkin_login();
signals:
    void login(const QString&, const QString&);

private:
    QHBoxLayout* uname_layout;
    QLabel* uname_label;
    QLineEdit* uname_line_edit;

    QHBoxLayout* upasswd_layout;
    QLabel* upasswd_label;
    QLineEdit* upasswd_line_edit;

    QHBoxLayout* error_layout;
    QLabel* error_label;

    QHBoxLayout* butt_layout;
    QPushButton* reg_button;
    QPushButton* login_button;

    void connect_signal_slot();
    void create_username_layout();
    void create_passwd_layout();
    void create_error_layout();
    void create_button_layout();
    void create_main_layout();
    
public:
    /**
     * @brief Diplays error message on the window
     * 
     * @param s - the message to display
     */
    void show_login_error(const QString& s);

    /// @name Special member functions
public:
    /**
     * @brief Constructor
     *
     * @param p - the parent window
     */
    log_in_window(QWidget* p = 0);
};

#endif // LOG_IN_WINDOW_H
