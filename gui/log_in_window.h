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
	void new_registration();
signals:
    void login(const QString&, const QString&);
	void registration(const QString& u, const QString& p);
private:
    QHBoxLayout* m_uname_layout;
    QLabel* m_uname_label;
    QLineEdit* m_uname_line_edit;

    QHBoxLayout* m_upasswd_layout;
    QLabel* m_upasswd_label;
    QLineEdit* m_upasswd_line_edit;

    QHBoxLayout* m_error_layout;
    QLabel* m_error_label;

    QHBoxLayout* m_butt_layout;
    QPushButton* m_reg_button;
    QPushButton* m_login_button;
private:
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
