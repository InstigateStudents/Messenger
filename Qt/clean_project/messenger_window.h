#ifndef MESSENGER_WINDOW_H
#define MESSENGER_WINDOW_H

#include <QDialog>

class QHBoxLayout;
class QVBoxLayout;
class QTextEdit;
class QPushButton;

class QLabel;
class QListWidget;
class QStackedLayout;

class messenger_window : public QDialog
{
    Q_OBJECT
public:
    messenger_window(QWidget* parent = 0);

private slots:
    void send_message();

private:

    QHBoxLayout *main_layout;

    QWidget *left_widget;
    QVBoxLayout *left_layout;
    QStackedLayout *left_top_layout;
    QHBoxLayout *left_bottom_layout;

    QWidget *right_widget;
    QVBoxLayout *right_layout;

    QTextEdit *message_text;
    QPushButton *send_button;


    void create_main_layout();

    void create_left_top_layout();
    void create_left_bottom_layout();
    void create_left_side();

    void create_right_side();

    void connect_signal_slot();

    //
    int user_count;
    QString *user_name;
    QVBoxLayout *user_layout;

    int current_user;

    QListWidget *online_users;
private slots:
    void set_current_user(int);


};


#endif // MESSENGER_WINDOW_H
