#include "MainWindow.h"
#include <qdebug.h>

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	s = nullptr;
	// 建立信号槽
	connect(ui.build, &QPushButton::clicked, this, &MainWindow::build);
	connect(ui.match, &QPushButton::clicked, this, &MainWindow::match);
	connect(ui.lcs, &QPushButton::clicked, this, &MainWindow::lcs);
	connect(ui.count, &QPushButton::clicked, this, &MainWindow::count);
	connect(ui.lrs, &QPushButton::clicked, this, &MainWindow::LongestRepeatString);

	ui.setStatus(false);
	ui.S->setFocus();
}

MainWindow::~MainWindow() { if (s)	delete s; }

void MainWindow::build() {
	QString S = ui.S->text();
	if (s != nullptr)	delete s;
	str = std::string(S.toLocal8Bit().data());
	// 构造后缀树
	s = new SuffixTree(&str[0]);
	ui.label->setText(QString(str.c_str()) + ", building done!");
	ui.setStatus(true);
}

void MainWindow::match() {
	if (s == nullptr)	return;
	// 获取字符串
	QString T = ui.T->text();
	std::string tmp(T.toLocal8Bit().data());
	int sz = s->find(tmp.c_str());
	if (~sz)	ui.label->setText("Ok, position starts at " + QString(std::to_string(sz).c_str()));
	else ui.label->setText("Not found");
}

void MainWindow::count() {
	if (s == nullptr)	return;
	QString T = ui.T->text();
	ui.label->setText(std::to_string(s->count(T.toLocal8Bit().data())).c_str());
}

void MainWindow::lcs() {
	// 获取字符串
	QString Q = ui.Q->text();
	QString P = ui.P->text();
	std::string QQ(Q.toLocal8Bit().data());
	SuffixTree tmp(QQ.c_str());
	std::string res;
	res.resize(QQ.length());
	tmp.lcs(P.toLocal8Bit().data(), &res[0]);
	ui.label->setText(res.c_str());
}

void MainWindow::LongestRepeatString() {
	if (s == nullptr)	return;
	std::string res;
	res.resize(str.length());
	int sz = s->LongestRepetitiveSubstring(&res[0]);
	if (~sz)	ui.label->setText(res.c_str());
	else ui.label->setText("No such the longest repatitive string");
}