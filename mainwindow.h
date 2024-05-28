#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QCryptographicHash>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_selectDirectoryButton1_clicked();
    void on_selectDirectoryButton2_clicked();
    void on_pushButton_clicked();

private:
    void processDir(const QString &dir1, const QString &dir2);
    void findClones(const QString &directory1, const QString &directory2);
    QByteArray hashFile(const QString &filePath);

    Ui::MainWindow *ui;
    QString directory1;
    QString directory2;
};

#endif // MAINWINDOW_H
