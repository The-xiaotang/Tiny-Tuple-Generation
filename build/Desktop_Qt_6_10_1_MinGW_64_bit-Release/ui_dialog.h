/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *chooseFile;
    QPushButton *saveFile;
    QTextEdit *source;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *analyze;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_2;
    QTextBrowser *error;
    QTabWidget *tabWidget;
    QWidget *tabTree;
    QVBoxLayout *verticalLayout_tree;
    QTreeWidget *result;
    QWidget *tabGraph;
    QVBoxLayout *verticalLayout_graph;
    QHBoxLayout *horizontalLayout_zoom;
    QPushButton *zoomIn;
    QPushButton *zoomOut;
    QPushButton *resetView;
    QGraphicsView *graphResult;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName("Dialog");
        Dialog->resize(800, 600);
        verticalLayout_3 = new QVBoxLayout(Dialog);
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        groupBox = new QGroupBox(Dialog);
        groupBox->setObjectName("groupBox");
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox{border:0;margin:0;padding:0;}"));
        groupBox->setFlat(true);
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        chooseFile = new QPushButton(groupBox);
        chooseFile->setObjectName("chooseFile");
        chooseFile->setAutoDefault(false);

        horizontalLayout_2->addWidget(chooseFile);

        saveFile = new QPushButton(groupBox);
        saveFile->setObjectName("saveFile");
        saveFile->setAutoDefault(false);

        horizontalLayout_2->addWidget(saveFile);


        verticalLayout->addLayout(horizontalLayout_2);

        source = new QTextEdit(groupBox);
        source->setObjectName("source");

        verticalLayout->addWidget(source);


        horizontalLayout_4->addWidget(groupBox);

        groupBox_2 = new QGroupBox(Dialog);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setStyleSheet(QString::fromUtf8("QGroupBox{border:0;margin:0;padding:0;}"));
        groupBox_2->setFlat(true);
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        analyze = new QPushButton(groupBox_2);
        analyze->setObjectName("analyze");
        analyze->setAutoDefault(false);

        horizontalLayout_3->addWidget(analyze);


        verticalLayout_2->addLayout(horizontalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName("label_2");

        verticalLayout_4->addWidget(label_2);

        error = new QTextBrowser(groupBox_2);
        error->setObjectName("error");

        verticalLayout_4->addWidget(error);

        tabWidget = new QTabWidget(groupBox_2);
        tabWidget->setObjectName("tabWidget");
        tabTree = new QWidget();
        tabTree->setObjectName("tabTree");
        verticalLayout_tree = new QVBoxLayout(tabTree);
        verticalLayout_tree->setObjectName("verticalLayout_tree");
        result = new QTreeWidget(tabTree);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        result->setHeaderItem(__qtreewidgetitem);
        result->setObjectName("result");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(result->sizePolicy().hasHeightForWidth());
        result->setSizePolicy(sizePolicy);
        result->setHeaderHidden(true);

        verticalLayout_tree->addWidget(result);

        tabWidget->addTab(tabTree, QString());
        tabGraph = new QWidget();
        tabGraph->setObjectName("tabGraph");
        verticalLayout_graph = new QVBoxLayout(tabGraph);
        verticalLayout_graph->setObjectName("verticalLayout_graph");
        horizontalLayout_zoom = new QHBoxLayout();
        horizontalLayout_zoom->setObjectName("horizontalLayout_zoom");
        zoomIn = new QPushButton(tabGraph);
        zoomIn->setObjectName("zoomIn");

        horizontalLayout_zoom->addWidget(zoomIn);

        zoomOut = new QPushButton(tabGraph);
        zoomOut->setObjectName("zoomOut");

        horizontalLayout_zoom->addWidget(zoomOut);

        resetView = new QPushButton(tabGraph);
        resetView->setObjectName("resetView");

        horizontalLayout_zoom->addWidget(resetView);


        verticalLayout_graph->addLayout(horizontalLayout_zoom);

        graphResult = new QGraphicsView(tabGraph);
        graphResult->setObjectName("graphResult");
        sizePolicy.setHeightForWidth(graphResult->sizePolicy().hasHeightForWidth());
        graphResult->setSizePolicy(sizePolicy);
        graphResult->setMinimumSize(QSize(400, 260));
        graphResult->setTransformationAnchor(QGraphicsView::ViewportAnchor::AnchorUnderMouse);
        graphResult->setResizeAnchor(QGraphicsView::ViewportAnchor::AnchorViewCenter);

        verticalLayout_graph->addWidget(graphResult);

        verticalLayout_graph->setStretch(1, 1);
        tabWidget->addTab(tabGraph, QString());

        verticalLayout_4->addWidget(tabWidget);

        verticalLayout_4->setStretch(1, 1);
        verticalLayout_4->setStretch(2, 6);

        verticalLayout_2->addLayout(verticalLayout_4);


        horizontalLayout_4->addWidget(groupBox_2);


        verticalLayout_3->addLayout(horizontalLayout_4);


        retranslateUi(Dialog);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Tiny\346\211\251\345\205\205\350\257\255\350\250\200", nullptr));
        groupBox->setTitle(QString());
        chooseFile->setText(QCoreApplication::translate("Dialog", "\351\200\211\346\213\251\346\226\207\344\273\266", nullptr));
        saveFile->setText(QCoreApplication::translate("Dialog", "\344\277\235\345\255\230\346\226\207\344\273\266", nullptr));
        groupBox_2->setTitle(QString());
        analyze->setText(QCoreApplication::translate("Dialog", "\345\210\206\346\236\220\347\250\213\345\272\217", nullptr));
        label_2->setText(QCoreApplication::translate("Dialog", "\350\257\255\346\263\225\351\224\231\350\257\257", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabTree), QCoreApplication::translate("Dialog", "\350\257\255\346\263\225\346\240\221", nullptr));
        zoomIn->setText(QCoreApplication::translate("Dialog", "\346\224\276\345\244\247", nullptr));
        zoomOut->setText(QCoreApplication::translate("Dialog", "\347\274\251\345\260\217", nullptr));
        resetView->setText(QCoreApplication::translate("Dialog", "\351\207\215\347\275\256", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabGraph), QCoreApplication::translate("Dialog", "\345\233\276\345\275\242\345\214\226\350\257\255\346\263\225\346\240\221", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
