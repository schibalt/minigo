#ifndef MINIGO_H
#define MINIGO_H

#include <QtWidgets/QMainWindow>
#include "ui_MiniGo.h"
#include "State.h"

class MiniGo : public QMainWindow
{
    Q_OBJECT

public:
    MiniGo (QWidget *parent = 0);
    ~MiniGo();
    void passInitialState (State* initialState);

private:
    Ui::MiniGoClass ui;
    void draw();
    State* activeState;
    State* primaryState;
    /*QBrush blackBrush(Qt::GlobalColor::black);
    QBrush whiteBrush(Qt::GlobalColor::white);*/

public slots:
    void on_previewButton_clicked();
    void on_moveButton_clicked();
    void on_listWidget_itemClicked (QListWidgetItem * item);

protected:
    virtual void paintEvent (QPaintEvent *e);
};

#endif // MINIGO_H
