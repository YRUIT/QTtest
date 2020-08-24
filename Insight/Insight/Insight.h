#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Insight.h"
#include <QLabel>
//#include <QPoint>
#include <QMouseEvent>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
//#include <QHBoxLayout>
#include <QDockWidget>
#include <QTextEdit>
#include <QMdiArea>
//#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>


#define pLineHight 30
#define pLineWidth 240

class Insight : public QMainWindow
{
    Q_OBJECT

public:
    Insight(QWidget *parent = Q_NULLPTR);

private:
    Ui::InsightClass ui;

private:
	void createMenu();
	void createToolBar();
	void createStatusBar();
	void mouseMoveEvent(QMouseEvent* e);	//重写mouseMoveEvent()鼠标移动事件
	void createOutputDocWidget();
	void createMdi();
	void setStyleSheet();

private:
	QMenuBar* pMenuBar;
	QToolBar* pToolBar;
	QToolBar* pToolBar2;
	QStatusBar* pStatusBar;
	QDockWidget* pDocWidget;
	QDockWidget* pDocWidget2;
	QLabel* pTimeLabel;
	QLabel* pPosLabel;
	QLineEdit* pLineEdit;
	QTextEdit* pLine;
	QTextEdit* pLine2;
	QMdiArea* mdiArea;
	//QWidget* centralWidget;

public:
	QAction* pAction;
private slots:
	void timeUpdate_Slot();
};
