/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
	QWidget* centralWidget;

	QPushButton* build; //构造后缀树
	QLineEdit* S;//原串S
	QLineEdit* T;//模式串T
	QPushButton* match;//模式串匹配
	QPushButton* count;//模式串计数
	QPushButton* lrs;//最长重复出现字串
	// Q和P的最长公共子串
	QLineEdit* Q;
	QLineEdit* P;
	QPushButton* lcs;

	QLabel* label;
	QLabel* Str;
	QLabel* Ttr;
	QLabel* Qtr;
	QLabel* Ptr;
	QLabel* tree;
	QMenuBar* menuBar;

	QMainWindow* MainWindow;


	void setupUi(QMainWindow* MainWindowClass)
	{
		MainWindow = MainWindowClass;
		if (MainWindowClass->objectName().isEmpty())
			MainWindowClass->setObjectName(QString::fromUtf8("MainWindowClass"));
		MainWindowClass->resize(520, 150);
		//MainWindowClass->setMaximumSize(520, 150);
		//MainWindowClass->setMinimumSize(520, 150);
		centralWidget = new QWidget(MainWindowClass);
		centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
		build = new QPushButton(centralWidget);
		build->setObjectName(QString::fromUtf8("build"));
		build->setGeometry(QRect(150, 20, 61, 21));
		S = new QLineEdit(centralWidget);
		S->setObjectName(QString::fromUtf8("S"));
		S->setGeometry(QRect(30, 20, 113, 21));
		T = new QLineEdit(centralWidget);
		T->setObjectName(QString::fromUtf8("T"));
		T->setGeometry(QRect(30, 50, 113, 21));
		match = new QPushButton(centralWidget);
		match->setObjectName(QString::fromUtf8("match"));
		match->setGeometry(QRect(150, 50, 61, 21));
		count = new QPushButton(centralWidget);
		count->setObjectName(QString::fromUtf8("count"));
		count->setGeometry(QRect(220, 20, 61, 21));
		lrs = new QPushButton(centralWidget);
		lrs->setObjectName(QString::fromUtf8("LRS"));
		lrs->setGeometry(QRect(220, 50, 61, 21));
		Q = new QLineEdit(centralWidget);
		Q->setObjectName(QString::fromUtf8("Q"));
		Q->setGeometry(QRect(320, 20, 113, 21));
		lcs = new QPushButton(centralWidget);
		lcs->setObjectName(QString::fromUtf8("lcs"));
		lcs->setGeometry(QRect(440, 20, 61, 21));
		P = new QLineEdit(centralWidget);
		P->setObjectName(QString::fromUtf8("P"));
		P->setGeometry(QRect(320, 50, 113, 21));
		label = new QLabel(centralWidget);
		label->setObjectName(QString::fromUtf8("label"));
		label->setGeometry(QRect(30, 90, 450, 50));
		tree = new QLabel(centralWidget);
		tree->setObjectName(QString::fromUtf8("tree"));
		Str = new QLabel(centralWidget);
		Str->setObjectName(QString::fromUtf8("Str"));
		Str->setGeometry(QRect(10, 22, 10, 15));
		Ttr = new QLabel(centralWidget);
		Ttr->setObjectName(QString::fromUtf8("Ttr"));
		Ttr->setGeometry(QRect(10, 52, 10, 15));
		Qtr = new QLabel(centralWidget);
		Qtr->setObjectName(QString::fromUtf8("Qtr"));
		Qtr->setGeometry(QRect(300, 22, 10, 15));
		Ptr = new QLabel(centralWidget);
		Ptr->setObjectName(QString::fromUtf8("Ptr"));
		Ptr->setGeometry(QRect(300, 52, 10, 15));
		MainWindowClass->setCentralWidget(centralWidget);
		menuBar = new QMenuBar(MainWindowClass);
		menuBar->setObjectName(QString::fromUtf8("menuBar"));
		menuBar->setGeometry(QRect(0, 0, 600, 26));
		MainWindowClass->setMenuBar(menuBar);

		retranslateUi(MainWindowClass);

		QMetaObject::connectSlotsByName(MainWindowClass);
	} // setupUi

	void retranslateUi(QMainWindow* MainWindowClass)
	{
		MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "SuffixTree", nullptr));
		build->setText(QApplication::translate("MainWindowClass", "build", nullptr));
		match->setText(QApplication::translate("MainWindowClass", "match", nullptr));
		lcs->setText(QApplication::translate("MainWindowClass", "lcs", nullptr));
		count->setText(QApplication::translate("MainWindowClass", "count", nullptr));
		lrs->setText(QApplication::translate("MainWindowClass", "LRS", nullptr));
		label->setText(QString());
		Str->setText(QString("S"));
		Ttr->setText(QString("T"));
		Qtr->setText(QString("Q"));
		Ptr->setText(QString("P"));
	} // retranslateUi

	// 设置组件可用
	void setStatus(bool status) {
		T->setEnabled(status);
		match->setEnabled(status);
		count->setEnabled(status);
		lrs->setEnabled(status);
	}

};

namespace Ui {
	class MainWindowClass : public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAINWINDOW_H