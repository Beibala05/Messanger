#ifndef MAIN_WINDOW
#define MAIN_WINDOW

#include "style.h"
#include "messanger.h"

#include <QMainWindow>
#include <QString>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTextBrowser>
#include <QResizeEvent>
#include <QCloseEvent>
#include <QDebug>
#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QFont>

#define MAIN_WINDOW_WIDTH           1200
#define MAIN_WINDOW_HEIGHT          800
#define CHECK_USER_NAME_FILE_PATH   "../../Messanger/data/checkUserName.txt"

class Messanger;

class MainWindow final : public QMainWindow
{
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow(); 

public:
    QString         getTextEdit()    const;
    QString         getTextBrowser() const;
    void            clearTextEdit();
    void            setTextBrowser(QString text);
    void            setTextSize(int new_size);

protected:
    void            resizeEvent(QResizeEvent* event) override;
    void            closeEvent(QCloseEvent* event)   override;

private:
    QWidget*        central_widget;
    QPushButton*    sendMessage;
    QLineEdit*      textEdit;
    QTextBrowser*   textBrowser;
    QFont           font;
    Messanger*      mes;
};

#endif  //MAIN_WINDOW