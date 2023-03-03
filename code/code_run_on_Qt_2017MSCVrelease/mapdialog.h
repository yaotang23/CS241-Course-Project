#ifndef MAPDIALOG_H
#define MAPDIALOG_H

#include <QDialog>
#include<QWebEngineView>
namespace Ui {
class MapDialog;
}

class MapDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MapDialog(QWidget *parent = nullptr);
    ~MapDialog();

private:
    Ui::MapDialog *ui;
    QWebEngineView *m_view;
    QString exepath;
};

#endif // MAPDIALOG_H
