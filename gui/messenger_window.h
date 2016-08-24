#ifndef MESSENGER_WINDOW_H
#define MESSENGER_WINDOW_H

#include <QDialog>

class QHBoxLayout;
class QVBoxLayout;
class QTextEdit;
class QPushButton;

class QLabel;
class QListWidget;
class QListWidgetItem;
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
    QHBoxLayout *left_layout;
    QVBoxLayout *left_left_layout;
    QStackedLayout *message_board;
    QTextEdit *vector;

    QVBoxLayout *left_right_layout;

    QWidget *right_widget;
    QVBoxLayout *right_layout;

    QTextEdit *message_text;
    QPushButton *send_button;


    void create_main_layout();

    void create_left_left_layout();
    void create_left_right_layout();

    void create_left_side();

    void create_right_side();

    void connect_signal_slot();

    //
    int user_count;
    QString *user_name;
    

    int current_user;

    QListWidget *online_users;
    QListWidgetItem *list_widget_item;
private slots:
    void set_current_user(int);


};


#endif // MESSENGER_WINDOW_H
