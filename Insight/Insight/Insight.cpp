#include "Insight.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QToolBar>
#include <QToolButton>
#include <QIcon>
#include <QString>
#include <QTimer>
#include <QDateTime>


Insight::Insight(QWidget *parent)
	: QMainWindow(parent)
{
	setStyleSheet();
	ui.setupUi(this);
	this->centralWidget()->setMouseTracking(true);	//鼠标不按下的情况捕捉moueMoveEvent()
	this->setMouseTracking(true);
	this->setWindowTitle(QStringLiteral("MainWindow"));
	this->setWindowIcon(QIcon("../src/qie.jpg"));
	createMenu();
	createToolBar();
	createStatusBar();
	createOutputDocWidget();
	createMdi();
	


}


void Insight::createMenu()
{
	pMenuBar = menuBar();


	QMenu* pMenuBarFile = new QMenu(QStringLiteral("&文件"), this);

	QAction *p2 = pMenuBarFile->addAction(QStringLiteral("属性"));
	connect(p2, &QAction::triggered, [=]()
	{
		QDialog *dlg2 = new QDialog;
		dlg2->resize(400, 200);
		dlg2->setAttribute(Qt::WA_DeleteOnClose);
		dlg2->setWindowTitle(QStringLiteral("属性"));
		dlg2->show();
	});

	//新建场景
	QAction* buildAction = pMenuBarFile->addAction(QStringLiteral("&新建场景"));
	//pMenuBarFile->addAction(buildAction);
	//打开场景
	QAction* openAction = new QAction(QStringLiteral("&打开场景"), this);
	pMenuBarFile->addAction(openAction);
	//保存场景
	QAction* saveAction = new QAction(QStringLiteral("&保存场景"), this);
	pMenuBarFile->addAction(saveAction);
	//另存为场景
	QAction* saveasAction = new QAction(QStringLiteral("&另存为场景"), this);
	pMenuBarFile->addAction(saveasAction);
	//关闭场景
	QAction* closeAction = new QAction(QStringLiteral("&关闭场景"), this);
	pMenuBarFile->addAction(closeAction);
	//最近访问场景
	QAction* visitAction = new QAction(QStringLiteral("&最近访问场景"), this);
	pMenuBarFile->addAction(visitAction);
	//退出
	QAction* exitAction = new QAction(QStringLiteral("&退出"), this);
	pMenuBarFile->addAction(exitAction);

	pMenuBar->addMenu(pMenuBarFile);

	QMenu* pMenuBarView = new QMenu(QStringLiteral("&视图"), this);
	//新建二维视图
	QAction* pTwoViewAction = new QAction(QStringLiteral("&新建二维视图"), this);
	pMenuBarView->addAction(pTwoViewAction);
	//新建三维视图
	QAction* pThreeViewAction = new QAction(QStringLiteral("&新建三维视图"), this);
	pMenuBarView->addAction(pThreeViewAction);
	//------------中断线
	pMenuBarView->addSeparator();
	//对象浏览器
	QAction* pObjViewAction = new QAction(QStringLiteral("&对象浏览器"), this);
	pMenuBarView->addAction(pObjViewAction);
	//时间轴
	QAction* pTimeLineAction = new QAction(QStringLiteral("&时间轴"), this);
	pMenuBarView->addAction(pTimeLineAction);
	//消息查看器
	QAction* pMessageViewAction = new QAction(QStringLiteral("&消息查看器"), this);
	pMenuBarView->addAction(pMessageViewAction);
	//环境背景
	QAction* pEnvBackAction = new QAction(QStringLiteral("&环境背景"), this);
	pMenuBarView->addAction(pEnvBackAction);
	//环境背景子菜单开始
	QMenu* pEnvBackActionChild = new QMenu();
	QAction* pEnvBackActionChildAction1 = new QAction(QStringLiteral("&星空背景"), this);
	pEnvBackActionChild->addAction(pEnvBackActionChildAction1);

	QAction* pEnvBackActionChildAction2 = new QAction(QStringLiteral("&卫星背景"), this);
	pEnvBackActionChild->addAction(pEnvBackActionChildAction2);

	pEnvBackAction->setMenu(pEnvBackActionChild);
	//环境背景子菜单结束

	pMenuBar->addMenu(pMenuBarView);

	QMenu* pMenuBarInsert = new QMenu(QStringLiteral("&插入"), this);
	//新建
	QAction* pNewBuildAction = new QAction(QStringLiteral("&新建"), this);
	pMenuBarInsert->addAction(pNewBuildAction);
	//从文件
	QAction* pFromFileAction = new QAction(QStringLiteral("从文件"), this);
	pMenuBarInsert->addAction(pFromFileAction);

	pMenuBar->addMenu(pMenuBarInsert);

	QMenu* pMenuBarAnalysis = new QMenu(QStringLiteral("&分析"), this);
	//传感覆盖分析
	QAction* pSensorAction = new QAction(QStringLiteral("&传感覆盖分析"), this);
	pMenuBarAnalysis->addAction(pSensorAction);

	//传感覆盖分析子菜单开始
	QMenu* pSensorChild = new QMenu();
	
	QAction* pSensorAction1 = new QAction(QStringLiteral("&载荷对单目标的覆盖分析"), this);
	pSensorChild->addAction(pSensorAction1);

	QAction* pSensorAction2 = new QAction(QStringLiteral("&载荷对区域目标的覆盖分析"), this);
	pSensorChild->addAction(pSensorAction2);

	QAction* pSensorAction3 = new QAction(QStringLiteral("&载荷对移动目标的覆盖分析"), this);
	pSensorChild->addAction(pSensorAction3);

	pSensorAction->setMenu(pSensorChild);
	//传感覆盖分析子菜单结束

	//业务预报分析
	QAction* pBusForecastAction = new QAction(QStringLiteral("&业务预报分析"), this);
	pMenuBarAnalysis->addAction(pBusForecastAction);

	//业务预报分析子菜单开始
	QMenu* pBusForecastChild = new QMenu();
	
	QAction* pBusForecastAction1 = new QAction(QStringLiteral("&日凌预报"), this);
	pBusForecastChild->addAction(pBusForecastAction1);

	QAction* pBusForecastAction2 = new QAction(QStringLiteral("&地影预报"), this);
	pBusForecastChild->addAction(pBusForecastAction2);

	QAction* pBusForecastAction3 = new QAction(QStringLiteral("&月影预报"), this);
	pBusForecastChild->addAction(pBusForecastAction3);

	QAction* pBusForecastAction4 = new QAction(QStringLiteral("&可见预报"), this);
	pBusForecastChild->addAction(pBusForecastAction4);

	QAction* pBusForecastAction5 = new QAction(QStringLiteral("&干扰预报"), this);
	pBusForecastChild->addAction(pBusForecastAction5);
	
	pBusForecastAction->setMenu(pBusForecastChild);
	//业务预报分析子菜单结束

	//控制计算
	QAction* pCtrlCalcAction = new QAction(QStringLiteral("&控制计算"), this);
	pMenuBarAnalysis->addAction(pCtrlCalcAction);

	//控制计算子菜单开始
	QMenu* pCtrlCalcChild = new QMenu();
	
	QAction* pCtrlCalcAction1 = new QAction(QStringLiteral("&单次变轨"), this);
	pCtrlCalcChild->addAction(pCtrlCalcAction1);

	QAction* pCtrlCalcAction2 = new QAction(QStringLiteral("&双脉冲变轨"), this);
	pCtrlCalcChild->addAction(pCtrlCalcAction2);
	
	QAction* pCtrlCalcAction3 = new QAction(QStringLiteral("&脉冲机动分析"), this);
	pCtrlCalcChild->addAction(pCtrlCalcAction3);

	pCtrlCalcChild->addSeparator();
	
	QAction* pCtrlCalcAction4 = new QAction(QStringLiteral("&轨道姿态预报"), this);
	pCtrlCalcChild->addAction(pCtrlCalcAction4);
	
	pCtrlCalcAction->setMenu(pCtrlCalcChild);
	//控制计算子菜单结束

	//电波传播分析
	QAction* pOnDemandAction = new QAction(QStringLiteral("&电波传播分析"), this);
	pMenuBarAnalysis->addAction(pOnDemandAction);

	//电波传播分析子菜单开始
	QMenu* pOnDemandChild = new QMenu();
	
	QAction* pOnDemandAction1 = new QAction(QStringLiteral("&S/N"), this);
	pOnDemandChild->addAction(pOnDemandAction1);

	QAction* pOnDemandAction2 = new QAction(QStringLiteral("&G/T"), this);
	pOnDemandChild->addAction(pOnDemandAction2);

	QAction* pOnDemandAction3 = new QAction(QStringLiteral("&EIRP"), this);
	pOnDemandChild->addAction(pOnDemandAction3);

	QAction* pOnDemandAction4 = new QAction(QStringLiteral("&最大作用距离"), this);
	pOnDemandChild->addAction(pOnDemandAction4);

	QAction* pOnDemandAction5 = new QAction(QStringLiteral("&空间传输损耗"), this);
	pOnDemandChild->addAction(pOnDemandAction5);
	
	pOnDemandAction->setMenu(pOnDemandChild);
	//电波传播分析子菜单结束

	//空间目标分析
	QAction* pSpaceTargetAction = new QAction(QStringLiteral("&空间目标分析"), this);
	pMenuBarAnalysis->addAction(pSpaceTargetAction);

	//空间目标分析子菜单开始
	QMenu* pSpaceTargetChild = new QMenu();

	QAction* pSpaceTargetAction1 = new QAction(QStringLiteral("&空间态势分析"), this);
	pSpaceTargetChild->addAction(pSpaceTargetAction1);

	QAction* pSpaceTargetAction2 = new QAction(QStringLiteral("&碎片观测分析"), this);
	pSpaceTargetChild->addAction(pSpaceTargetAction2);
	
	pSpaceTargetAction->setMenu(pSpaceTargetChild);
	//空间目标分析子菜单结束

	pMenuBar->addMenu(pMenuBarAnalysis);

	QMenu* pMenuBarAlgorithm = new QMenu(QStringLiteral("&算法库"), this);
	//时空转换
	QAction* pTimeSapceAction = new QAction(QStringLiteral("&时空转换"), this);
	pMenuBarAlgorithm->addAction(pTimeSapceAction);

	//时空转换子菜单开始
	QMenu* pTimeSapceChild = new QMenu();
	
	QAction* pTimeSapceAction1 = new QAction(QStringLiteral("&时间转换"), this);
	pTimeSapceChild->addAction(pTimeSapceAction1);

	QAction* pTimeSapceAction2 = new QAction(QStringLiteral("&坐标转换"), this);
	pTimeSapceChild->addAction(pTimeSapceAction2);

	QAction* pTimeSapceAction3 = new QAction(QStringLiteral("&星下点计算"), this);
	pTimeSapceChild->addAction(pTimeSapceAction3);

	QAction* pTimeSapceAction4 = new QAction(QStringLiteral("&行星星历计算"), this);
	pTimeSapceChild->addAction(pTimeSapceAction4);

	QAction* pTimeSapceAction5 = new QAction(QStringLiteral("&深空坐标系转换"), this);
	pTimeSapceChild->addAction(pTimeSapceAction5);
	
	pTimeSapceAction->setMenu(pTimeSapceChild);
	//时空转换子菜单结束

	//轨道预报
	QAction* pOrbitForecastAction = new QAction(QStringLiteral("&轨道预报"), this);
	pMenuBarAlgorithm->addAction(pOrbitForecastAction);

	//轨道预报子菜单开始
	QMenu* pOrbitForecastChild = new QMenu();

	QAction* pOrbitForecastAction1 = new QAction(QStringLiteral("&二体轨道预报"), this);
	pOrbitForecastChild->addAction(pOrbitForecastAction1);

	QAction* pOrbitForecastAction2 = new QAction(QStringLiteral("&SGP4/SDP4轨道预报"), this);
	pOrbitForecastChild->addAction(pOrbitForecastAction2);

	QAction* pOrbitForecastAction3 = new QAction(QStringLiteral("&解析法轨道预报"), this);
	pOrbitForecastChild->addAction(pOrbitForecastAction3);

	QAction* pOrbitForecastAction4 = new QAction(QStringLiteral("&数值法轨道预报"), this);
	pOrbitForecastChild->addAction(pOrbitForecastAction4);
	
	pOrbitForecastAction->setMenu(pOrbitForecastChild);
	//轨道预报子菜单结束

	//根数转换
	QAction* pRootConversionAction = new QAction(QStringLiteral("&根数转换"), this);
	pMenuBarAlgorithm->addAction(pRootConversionAction);
	//轨道设计
	QAction* pOrbitDesignAction = new QAction(QStringLiteral("&轨道设计"), this);
	pMenuBarAlgorithm->addAction(pOrbitDesignAction);
	//数据仿真
	QAction* pDataSimulationAction = new QAction(QStringLiteral("&数据仿真"), this);
	pMenuBarAlgorithm->addAction(pDataSimulationAction);

	//数据仿真子菜单开始
	QMenu* pDataSimulationChild = new QMenu();
	
	QAction* pDataSimulationAction1 = new QAction(QStringLiteral("&外侧数据仿真"), this);
	pDataSimulationChild->addAction(pDataSimulationAction1);

	QAction* pDataSimulationAction2 = new QAction(QStringLiteral("&光学数据仿真"), this);
	pDataSimulationChild->addAction(pDataSimulationAction2);

	QAction* pDataSimulationAction3 = new QAction(QStringLiteral("&GPS数据仿真"), this);
	pDataSimulationChild->addAction(pDataSimulationAction3);

	pDataSimulationAction->setMenu(pDataSimulationChild);
	//数据仿真子菜单结束

	//初轨确定
	QAction* pOrbitDeterminationAction = new QAction(QStringLiteral("&初轨确定"), this);
	pMenuBarAlgorithm->addAction(pOrbitDeterminationAction);
	//精度评估
	QAction* pAccAssessmentAction = new QAction(QStringLiteral("&精度评估"), this);
	pMenuBarAlgorithm->addAction(pAccAssessmentAction);

	pMenuBar->addMenu(pMenuBarAlgorithm);

	QMenu* pMenuBarTool = new QMenu(QStringLiteral("&工具箱"), this);
	//天文常数更新
	QAction* pAstUpdateAction = new QAction(QStringLiteral("&天文常数更新"), this);
	pMenuBarTool->addAction(pAstUpdateAction);
	//SP3文件下载
	QAction* pFileDownloadAction = new QAction(QStringLiteral("&SP3文件下载"), this);
	pMenuBarTool->addAction(pFileDownloadAction);
	//空间目标信息库更新
	QAction* pDatabaseUpdateAction = new QAction(QStringLiteral("&空间目标信息库更新"), this);
	pMenuBarTool->addAction(pDatabaseUpdateAction);
	//弹道比较
	QAction* pBallisticCmpAction = new QAction(QStringLiteral("&弹道比较"), this);
	pMenuBarTool->addAction(pBallisticCmpAction);

	pMenuBar->addMenu(pMenuBarTool);

	QMenu* pMenuBarConfig = new QMenu(QStringLiteral("&配置"), this);
	//全局设置
	QAction* pSettingAction = new QAction(QStringLiteral("全局设置"), this);
	pMenuBarConfig->addAction(pSettingAction);

	//全局设置子菜单开始
	QMenu* pSettingChild = new QMenu();

	QAction* pSettingAction1 = new QAction(QStringLiteral("&工作目录设置"), this);
	pSettingChild->addAction(pSettingAction1);

	QAction* pSettingAction2 = new QAction(QStringLiteral("&碎片文件设置"), this);
	pSettingChild->addAction(pSettingAction2);

	pSettingAction->setMenu(pSettingChild);
	//全局设置子菜单结束

	pMenuBar->addMenu(pMenuBarConfig);

	QMenu* pMenuBarWindows = new QMenu(QStringLiteral("&窗口"), this);
	//关闭顶层
	QAction* pCloseTopAction = new QAction(QStringLiteral("&关闭顶层"), this);
	pMenuBarWindows->addAction(pCloseTopAction);
	//关闭所有
	QAction* pCloseAllAction = new QAction(QStringLiteral("&关闭所有"), this);
	pMenuBarWindows->addAction(pCloseAllAction);
	//排列窗口
	QAction* pArrangeWinAction = new QAction(QStringLiteral("&排列窗口"), this);
	pMenuBarWindows->addAction(pArrangeWinAction);
	//层叠窗口
	QAction* pCascadeWinAction = new QAction(QStringLiteral("&层叠窗口"), this);
	pMenuBarWindows->addAction(pCascadeWinAction);
	//全屏显示
	QAction* pFullScreenAction = new QAction(QStringLiteral("全屏显示"), this);
	pMenuBarWindows->addAction(pFullScreenAction);

	pMenuBar->addMenu(pMenuBarWindows);

	QMenu* pMenuBarHelp = new QMenu(QStringLiteral("&帮助"), this);
	//帮助
	QAction* pHelpAction = new QAction(QStringLiteral("&帮助"), this);
	pMenuBarHelp->addAction(pHelpAction);
	//关于...
	QAction* pOnAction = new QAction(QStringLiteral("&关于"), this);
	pMenuBarHelp->addAction(pOnAction);
	//语言
	QAction* pLanguageAction = new QAction(QStringLiteral("&语言"), this);
	pMenuBarHelp->addAction(pLanguageAction);
	//语言子菜单开始
	QMenu* pLanguageChild = new QMenu();
	QAction* pLanguageAction1 = new QAction(QStringLiteral("&中文"), this);
	pLanguageChild->addAction(pLanguageAction1);
	pLanguageAction->setMenu(pLanguageChild);
	//语言子菜单结束
	//皮肤
	QAction* pSkinAction = new QAction(QStringLiteral("&皮肤"), this);
	pMenuBarHelp->addAction(pSkinAction);

	//皮肤子菜单开始
	QMenu* pSkinActionChild = new QMenu();
	QAction* pSkinActionAction1 = new QAction(QStringLiteral("&浅蓝色"), this);
	pSkinActionChild->addAction(pSkinActionAction1);

	QAction* pSkinActionAction2 = new QAction(QStringLiteral("&深蓝色"), this);
	pSkinActionChild->addAction(pSkinActionAction2);

	pSkinAction->setMenu(pSkinActionChild);
	//皮肤子菜单结束

	pMenuBar->addMenu(pMenuBarHelp);
}

void Insight::createToolBar()
{
	
	pToolBar = addToolBar("");

	QToolButton* pBuildViewAction = new QToolButton(this);
	pBuildViewAction->setIcon(QIcon("../src/recent.png"));
	pBuildViewAction->setToolTip(QStringLiteral("新建场景"));
	pToolBar->addWidget(pBuildViewAction);

	QToolButton* pOpenViewAction = new QToolButton(this);
	pOpenViewAction->setIcon(QIcon("../src/open.png"));
	pOpenViewAction->setToolTip(QStringLiteral("打开场景"));
	pToolBar->addWidget(pOpenViewAction);

	QToolButton* pSaveViewAction = new QToolButton(this);
	pSaveViewAction->setIcon(QIcon("../src/save.png"));
	pSaveViewAction->setToolTip(QStringLiteral("保存场景"));
	pToolBar->addWidget(pSaveViewAction);

	pToolBar->addSeparator();

	QToolButton* pInsertObjAction = new QToolButton(this);
	pInsertObjAction->setIcon(QIcon("../src/editable.ico"));
	pInsertObjAction->setToolTip(QStringLiteral("插入对象"));
	pToolBar->addWidget(pInsertObjAction);

	pToolBar->addSeparator();

	QToolButton* pReportAction = new QToolButton(this);
	pReportAction->setIcon(QIcon("../src/checkOTP.ico"));
	pReportAction->setToolTip(QStringLiteral("报表和图表管理"));
	pToolBar->addWidget(pReportAction);

	QToolButton* pVisibilityAction = new QToolButton(this);
	pVisibilityAction->setIcon(QIcon("../src/erase.ico"));
	pVisibilityAction->setToolTip(QStringLiteral("可见性"));
	pToolBar->addWidget(pVisibilityAction);

	QToolButton* pSensorVisAction = new QToolButton(this);
	pSensorVisAction->setIcon(QIcon("../src/editable.ico"));
	pSensorVisAction->setToolTip(QStringLiteral("传感器可见性"));
	pToolBar->addWidget(pSensorVisAction);

	QToolButton* pDebrisObservationAction = new QToolButton(this);
	pDebrisObservationAction->setIcon(QIcon("../src/disconnect.ico"));
	pDebrisObservationAction->setToolTip(QStringLiteral("碎片观测分析"));
	pToolBar->addWidget(pDebrisObservationAction);

	pToolBar->addSeparator();

	QToolButton* pDatabaseUpdateAction = new QToolButton(this);
	pDatabaseUpdateAction->setIcon(QIcon("../src/cleanOTP.ico"));
	pDatabaseUpdateAction->setToolTip(QStringLiteral("空间目标信息库更新"));
	pToolBar->addWidget(pDatabaseUpdateAction);

	pToolBar->addSeparator();

	QToolButton* pFullScreenAction = new QToolButton(this);
	pFullScreenAction->setIcon(QIcon("../src/check.ico"));
	pFullScreenAction->setToolTip(QStringLiteral("全屏显示"));
	pToolBar->addWidget(pFullScreenAction);

	QToolButton* pCascadeWinAction = new QToolButton(this);
	pCascadeWinAction->setIcon(QIcon("../src/read.ico"));
	pCascadeWinAction->setToolTip(QStringLiteral("层叠窗口"));
	pToolBar->addWidget(pCascadeWinAction);

	QToolButton* pArrangeWinAction = new QToolButton(this);
	pArrangeWinAction->setIcon(QIcon("../src/readOTP.ico"));
	pArrangeWinAction->setToolTip(QStringLiteral("排列窗口"));
	pToolBar->addWidget(pArrangeWinAction);

	pToolBar->addSeparator();

	QToolButton* pTimeLineAction = new QToolButton(this);
	pTimeLineAction->setIcon(QIcon("../src/downloadOTP.ico"));
	pTimeLineAction->setToolTip(QStringLiteral("时间轴"));
	pToolBar->addWidget(pTimeLineAction);

	pToolBar->addSeparator();

	this->addToolBarBreak(Qt::TopToolBarArea);

	pToolBar2 = addToolBar("");
	pLineEdit = new QLineEdit();
	pLineEdit->setMaximumSize(QSize(pLineWidth, pLineHight));
	pLineEdit->setPlaceholderText(QStringLiteral("搜索"));	//设置默认提示语

	pToolBar2->addWidget(pLineEdit);

	
	QPushButton* pSearchButton = new QPushButton(this);
	pSearchButton->setIcon(QIcon("../src/cleanOTP.ico"));
	pToolBar2->addWidget(pSearchButton);

	pToolBar2->addSeparator();

	QPushButton* pButton1 = new QPushButton(this);
	pButton1->setIcon(QIcon("../src/1.jpg"));

	QPushButton* pButton2 = new QPushButton(this);
	pButton2->setIcon(QIcon("../src/2.jpg"));

	QPushButton* pButton3 = new QPushButton(this);
	pButton3->setIcon(QIcon("../src/3.jpg"));

	QPushButton* pButton4 = new QPushButton(this);
	pButton4->setIcon(QIcon("../src/4.jpg"));

	QPushButton* pButton5 = new QPushButton(this);
	pButton5->setIcon(QIcon("../src/5.jpg"));

	QPushButton* pButton6 = new QPushButton(this);
	pButton6->setIcon(QIcon("../src/6.jpg"));

	QPushButton* pButton7 = new QPushButton(this);
	pButton7->setIcon(QIcon("../src/7.jpg"));

	QPushButton* pButton8 = new QPushButton(this);
	pButton8->setIcon(QIcon("../src/8.jpg"));
	
	pToolBar2->addWidget(pButton1);
	pToolBar2->addWidget(pButton2);
	pToolBar2->addWidget(pButton3);
	pToolBar2->addWidget(pButton4);
	pToolBar2->addWidget(pButton5);
	pToolBar2->addWidget(pButton6);
	pToolBar2->addWidget(pButton7);
	pToolBar2->addWidget(pButton8);
}

void Insight::createStatusBar()
{
	pStatusBar = statusBar();
	//获取鼠标位置(mouseMoveEvent(QMouseEvent* e))
	pPosLabel = new QLabel();
	pStatusBar->addPermanentWidget(pPosLabel);


	//获取当前时间
	pTimeLabel = new QLabel();
	pStatusBar->addPermanentWidget(pTimeLabel);

	QTimer *pTimer = new QTimer(this);
	pTimer->start(1000);
	connect(pTimer, SIGNAL(timeout()), this, SLOT(timeUpdate_Slot()));

	//程序里写死步长
	QLabel *pWelCome = new QLabel(QStringLiteral("步长:   60.000秒"));
	pStatusBar->addPermanentWidget(pWelCome);
}

void Insight::createOutputDocWidget()
{
	pDocWidget = new QDockWidget(QStringLiteral("对象浏览器"), this);
	
	pDocWidget->setWindowFlags(Qt::WindowStaysOnTopHint);

	pDocWidget->setFeatures(QDockWidget::AllDockWidgetFeatures | QDockWidget::DockWidgetMovable);
	pDocWidget->setMinimumWidth(300);
	


	//pDocWidget->setWindowFlags(pDocWidget->windowFlags() | Qt::Window);
	//pDocWidget->showNormal();
	//pDocWidget->setVisible(true);
	
	//能往悬浮窗中以行的形式添加信息
	//this->pLine->append("../src/4.jpg");
	//this->pLine->append("../src/5.jpg");
	//this->pLine->append("../src/6.jpg");
	//pLine->setStyleSheet("border-image: url(../src/15.jpg)");
	pLine = new QTextEdit();
	pLine->setMinimumWidth(300);
	pLine->setMaximumHeight(1000);
	pDocWidget->setWidget(pLine);	
	addDockWidget(Qt::LeftDockWidgetArea, pDocWidget);


	//pDocWidget2 = new QDockWidget(QStringLiteral("3D Earth 1"), this);
	//pDocWidget2->setFeatures(QDockWidget::AllDockWidgetFeatures);
	//pDocWidget2->setMinimumWidth(300);

	//QTextEdit* pLine2 = new QTextEdit();
	//pLine2->setStyleSheet("border-image: url(../src/15.jpg)");
	//pLine2->setMinimumWidth(300);
	//pLine2->setMaximumHeight(1000);
	//pDocWidget2->setWidget(pLine2);

	//addDockWidget(Qt::RightDockWidgetArea, pDocWidget2);


}


void Insight::createMdi()
{
	mdiArea = new QMdiArea;
	mdiArea->setMouseTracking(true);
	this->setCentralWidget(mdiArea);

	//QTextEdit* pTextEdit = new QTextEdit();
	//this->mdiArea->addSubWindow(pTextEdit);	//添加子窗体到多文档界面
	//pTextEdit->showMaximized();	//将子窗体最大化


	QPixmap pixmap("../src/qie.jpg");
	QGraphicsScene* m_MainScene = new QGraphicsScene;
	m_MainScene->addPixmap(pixmap);
	QGraphicsView * myView = new QGraphicsView();
	myView->setScene(m_MainScene);

	QPixmap pixmap2("../src/qie.jpg");
	QGraphicsScene* m_MainScene2 = new QGraphicsScene;
	m_MainScene2->addPixmap(pixmap2);
	QGraphicsView * myView2 = new QGraphicsView();
	myView2->setScene(m_MainScene2);


	this->mdiArea->addSubWindow(myView);
	this->mdiArea->addSubWindow(myView2);
}

void Insight::timeUpdate_Slot()
{
	QDateTime currentTime = QDateTime::currentDateTime();
	QString timeStr = currentTime.toString(QStringLiteral("yyyy年MM月dd日 hh:mm:ss"));

	pTimeLabel->setText(timeStr);
}

void Insight::mouseMoveEvent(QMouseEvent *e)
{
	QString sendMsg = "(" + QString::number(e->x()) + "," + QString::number(e->y()) + ")";
	pPosLabel->setText(sendMsg);
}

void Insight::setStyleSheet()
{
	qApp->setStyleSheet("QMenuBar{background-color: rgb(200, 200, 200);}" \
		"QToolBar{background-color: rgb(200,200,200);}" \
		"QLineEdit{color: rgb(255, 0, 0);}" \
		"QLineEdit{font-family: Times New Roman;}" \
		"QMainWindow{ \
			background: rgb(200, 10, 200);}" \
	);
	//qApp->setStyleSheet("QToolBar{background-color: red;}");
}