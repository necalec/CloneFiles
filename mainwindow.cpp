#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QFileInfoList>
#include <QFileInfo>
#include <QFile>
#include <QCryptographicHash>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("TestWork");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_selectDirectoryButton1_clicked()
{
    directory1 = QFileDialog::getExistingDirectory(this, tr("Select Dir 1"), QDir::homePath());
    ui->label->setText(directory1);
}

void MainWindow::on_selectDirectoryButton2_clicked()
{
    directory2 = QFileDialog::getExistingDirectory(this, tr("Select Dir 2"), QDir::homePath());
    ui->label_2->setText(directory2);
}

void MainWindow::on_pushButton_clicked()
{
    if (!directory1.isEmpty() && !directory2.isEmpty()) {
        processDir(directory1, directory2);
    } else {
        QMessageBox::warning(this, tr("Warning"), tr("Not select!"));
    }
}

void MainWindow::processDir(const QString &dir1, const QString &dir2)
{
    findClones(dir1, dir2);
}

void MainWindow::findClones(const QString &directory1, const QString &directory2)
{
    QDir dir1(directory1);
    QDir dir2(directory2);

    QFileInfoList fileList1 = dir1.entryInfoList(QDir::Files);
    QFileInfoList fileList2 = dir2.entryInfoList(QDir::Files);

    QMap<QByteArray, QStringList> hashToFileMap;

    for (const QFileInfo &fileInfo : fileList1) {
        QByteArray fileHash = hashFile(fileInfo.absoluteFilePath());
        hashToFileMap[fileHash].append(fileInfo.absoluteFilePath());
    }

    QStringList clones;

    for (const QFileInfo &fileInfo : fileList2) {
        QByteArray fileHash = hashFile(fileInfo.absoluteFilePath());
        if (hashToFileMap.contains(fileHash)) {
            for (const QString &cloneFile : hashToFileMap[fileHash]) {
                clones.append(tr("Clones:\n%1\n%2").arg(cloneFile, fileInfo.absoluteFilePath()));
            }
        }
    }

    if (clones.isEmpty()) {
        QMessageBox::information(this, tr("Nothing"), tr("Clons not found"));
    } else {
        QMessageBox::information(this, tr("Clones"), clones.join("\n\n"));
    }
}

QByteArray MainWindow::hashFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, tr("Error"), tr("Cannot open file: %1").arg(filePath));
        return QByteArray();
    }

    QCryptographicHash hash(QCryptographicHash::Sha256);
    if (hash.addData(&file)) {
        return hash.result();
    }

    return QByteArray();
}
