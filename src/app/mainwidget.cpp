#include "mainwidget.hpp"
#include "dbservice.hpp"

MainWidget::MainWidget(DbService& dbservice, QWidget *parent)
    : QWidget{parent}, mDbService(dbservice)
{

}
