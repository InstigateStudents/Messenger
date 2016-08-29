#include "messenger.h"

#include "messenger_window.h"
#include "log_in_window.h"
#include "dispatcher.hpp"

#include <cassert>
#include <iostream>

messenger::messenger(const std::string& i)
{
    m_log_in_window = new log_in_window();
    m_dispatcher = new dispatcher(i);
    connect(m_log_in_window, SIGNAL(login(const QString&, const QString&)),
            this, SLOT(login(const QString&, const QString&)), Qt::QueuedConnection);
    connect(m_dispatcher, SIGNAL(new_message(const QString&, const QString&)),
            this, SLOT(receive_message(const QString&, const QString&)), Qt::QueuedConnection);
}

void messenger::run()
{
    assert(0 != m_log_in_window);
    m_log_in_window->show();
}

QStringList messenger::fake_list_generator()
{   
    assert(0 != m_dispatcher);
    std::vector<std::string> n = m_dispatcher->get_onlines();
    QStringList l;
    for (unsigned int i = 0; i < n.size(); ++i) {
        l << QString::fromUtf8(n[i].c_str());
    }
    return l;
}

void messenger::login(const QString& u, const QString& p)
{
    assert(!u.isEmpty());
    assert(!p.isEmpty());
    assert(0 != m_dispatcher);
    bool b = m_dispatcher->login(u.toStdString(), p.toStdString()); 
    if (b) {
        assert(0 != m_log_in_window);
        m_log_in_window->hide();   
        QStringList l = fake_list_generator(); 
        m_messenger_window = new messenger_window(l);
        connect(m_messenger_window,
                SIGNAL(send_message_to_client(const QString&, const QString&)),
                this,
                SLOT(send_to_client(const QString&, const QString&)), Qt::QueuedConnection);
        assert(0 != m_messenger_window);
        m_messenger_window->show();
    } else {
        m_log_in_window->show_login_error("Incorrect username or password.");
    }
}

void messenger::send_to_client(const QString& t, const QString& m)
{
    assert(!t.isEmpty());
    assert(!m.isEmpty());
    assert(0 != m_dispatcher);
    m_dispatcher->send_to(t.toStdString(), m.toStdString());
}

void messenger::receive_message(const QString& f, const QString& m)
{
    assert(!f.isEmpty());
    assert(!m.isEmpty());
    assert(0 != m_messenger_window);
    m_messenger_window->receive_message(f, m);
}


void messenger::refresh_online_users(const std::vector<std::string>& v)
{
    QVector<QString> online;
    for (std::vector<std::string>::size_type i = 0; i < v.size(); ++i) {
        online.append(QString::fromUtf8(v[i].c_str()));
    }
    m_messenger_window->refresh_show_online_users(online);
}

