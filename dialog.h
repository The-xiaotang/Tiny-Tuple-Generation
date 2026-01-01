//#ifndef DIALOG_H
//#define DIALOG_H
#pragma once

#include <QDialog>
#include "analyze.h"
#include <QTreeWidget>
#include <QPixmap>
#include <QTextEdit>

QT_BEGIN_NAMESPACE

namespace Ui { class Dialog; }

QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_chooseFile_clicked();

    void on_saveFile_clicked();

    void on_analyze_clicked();

    void on_zoomIn_clicked();
    void on_zoomOut_clicked();
    void on_resetView_clicked();

private:
    Ui::Dialog *ui;
    QTextEdit *codeView;
    void traverseTree(TreeNode*, QTreeWidgetItem *);
    QPixmap bgPix;
    void updateErrorMaxHeight();
protected:
    void resizeEvent(QResizeEvent *event) override;
};
//#endif // DIALOG_H
