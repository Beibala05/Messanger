#include "main_window.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    QFile file(CHECK_USER_NAME_FILE_PATH);
    
    file.open(QIODevice::ReadOnly);

    if (file.size() == 0)
    {
        Messanger::userName = "user";
    }
    else
    {
        Messanger::userName = file.readLine();
    }

    file.close();

    central_widget = new QWidget(this);
    this->setCentralWidget(central_widget);
    this->setMinimumSize(MAIN_WINDOW_WIDTH / 4, MAIN_WINDOW_HEIGHT / 4);
    this->setStyleSheet(styles::main_window_style);
    this->setWindowTitle("Простой мессенджер на C++");

    textBrowser = new QTextBrowser(central_widget);
    textBrowser->setGeometry(5, 5, MAIN_WINDOW_WIDTH - 10, MAIN_WINDOW_HEIGHT - 60);
    textBrowser->setStyleSheet(styles::dialog_window_btn_green_style);
    textBrowser->setFont(styles::fontTextBrowser);

    textEdit = new QLineEdit(central_widget);
    textEdit->setGeometry(5, MAIN_WINDOW_HEIGHT - 50, MAIN_WINDOW_WIDTH - 55, 40);
    textEdit->setStyleSheet(styles::dialog_window_btn_green_style);
    textEdit->setFont(styles::fontTextEdit);
    textEdit->setPlaceholderText("Введите текст");

    sendMessage = new QPushButton("=>", central_widget);
    sendMessage->setGeometry(MAIN_WINDOW_WIDTH - 45, MAIN_WINDOW_HEIGHT - 50, 40, 40);
    sendMessage->setStyleSheet(styles::dialog_window_btn_green_style);

    QMainWindow::resize(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);
    QMainWindow::show();

    mes                 = new Messanger(this);
    shortcutEnter       = new QShortcut(QKeySequence(Qt::Key_Return), sendMessage); // Нажатие на Enter
    shortcutNumpadEnter = new QShortcut(QKeySequence(Qt::Key_Enter), sendMessage);  // Нажатие на Enter (на нампдае)

    QObject::connect(sendMessage, &QPushButton::clicked, mes, &Messanger::sendMessageToBrowserSlot);
    QObject::connect(shortcutEnter, &QShortcut::activated, mes, &Messanger::sendMessageToBrowserSlot);
    QObject::connect(shortcutNumpadEnter, &QShortcut::activated, mes, &Messanger::sendMessageToBrowserSlot);

}

MainWindow::~MainWindow()
{
    delete central_widget;
    delete mes;
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    QFile file(CHECK_USER_NAME_FILE_PATH);

    file.open(QIODevice::WriteOnly);
    file.write(Messanger::userName.toUtf8());
    file.close();

    delete this;
    QMainWindow::closeEvent(event);
}

void MainWindow::resizeEvent(QResizeEvent* event)
{    
    textBrowser->setGeometry(5, 5, width() - 10, height() - 60);
    textEdit->setGeometry(5, height() - 50,  width() - 55, 40);
    sendMessage->setGeometry(width() - 45, height() - 50, 40, 40);

    QMainWindow::resizeEvent(event);
}

QString MainWindow::getTextEdit() const
{
    return textEdit->text();
}

QString MainWindow::getTextBrowser() const
{
    return textBrowser->toPlainText();
}

void MainWindow::clearTextEdit()
{
    this->textEdit->clear();
}

void MainWindow::setTextBrowser(QString text)
{
    this->textBrowser->setText(text);
}