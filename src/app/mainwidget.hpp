#ifndef MAINWIDGET_HPP
#define MAINWIDGET_HPP

#include <QWidget>

// forwards
class DbService;

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(DbService& dbservice, QWidget *parent = nullptr);

signals:

private:
    DbService& mDbService;
};

#endif // MAINWIDGET_HPP
