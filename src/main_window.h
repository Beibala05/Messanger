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

#define MAIN_WINDOW_WIDTH  1200
#define MAIN_WINDOW_HEIGHT 800

class Messanger;

class MainWindow final : public QMainWindow
{
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow(); 

public:
    QString getTextEdit() const;
    void clearTextEdit();
    void setTextBrowser(QString text);

protected:
    void resizeEvent(QResizeEvent* event) override;
    void closeEvent(QCloseEvent* event)   override;

private:
    QWidget*        central_widget;
    QPushButton*    sendMessage;
    QLineEdit*      textEdit;
    QTextBrowser*   textBrowser;
    Messanger*      mes;
};

#endif  //MAIN_WINDOW