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
    void passInitialState (unsigned char dimensions, unsigned char plies);

private:
    Ui::MiniGoClass ui;
    State* activeState;
    State* primaryState;
    QBrush brush;
    unsigned char plies;
	bool pass;
	void updateListWidget();

public slots:
    void on_previewButton_clicked();
    void on_moveButton_clicked();
    void on_listWidget_currentItemChanged (QListWidgetItem * item);
    void on_passButton_clicked ();

protected:
    virtual void paintEvent (QPaintEvent *e);
};

#endif // MINIGO_H
