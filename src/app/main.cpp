// SPDX-License-Identifier: GPL-3.0-only

#include "mainwidget.hpp"
#include "dbservice.hpp"

#include <QApplication>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString dbFileName(QLatin1String("ghent-data.db"));

    // Check database file and prompt if necessary
    QFileInfo check_file(dbFileName);
    if (!check_file.exists() || !check_file.isFile()) {
        QFileDialog dialog;
        dialog.setWindowTitle("Open Ghent database file");
        dialog.setNameFilter("Sqlite3 database file (*.db)");
        dialog.setFileMode(QFileDialog::ExistingFile);
        dialog.setAcceptMode(QFileDialog::AcceptOpen);
        //dialog.setDirectory(QDir::homePath());
        if (dialog.exec() != QDialog::Accepted)
            return 0;

        dbFileName = dialog.selectedFiles()[0];
    }

    // Open database
    auto db = DbService::create(dbFileName);
    if (!db->init()) {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Icon::Critical);
        msgBox.setText(QString("Unable to open database file '%1'\n\nError: %2").arg(dbFileName, db->lastError().text()));
        return msgBox.exec();
    }

    // Show the application window
    MainWidget w(*db);
    w.show();

    return a.exec();
}
