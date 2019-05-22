#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "SuffixTree.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget* parent = Q_NULLPTR);
	~MainWindow();
private:
	Ui::MainWindowClass ui;
	SuffixTree* s;
	std::string str;
private slots:
	void build();
	void match();
	void lcs();
	void count();
	void LongestRepeatString();
};
