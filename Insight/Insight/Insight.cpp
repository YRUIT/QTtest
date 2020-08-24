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
	this->centralWidget()->setMouseTracking(true);	//��겻���µ������׽moueMoveEvent()
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


	QMenu* pMenuBarFile = new QMenu(QStringLiteral("&�ļ�"), this);

	QAction *p2 = pMenuBarFile->addAction(QStringLiteral("����"));
	connect(p2, &QAction::triggered, [=]()
	{
		QDialog *dlg2 = new QDialog;
		dlg2->resize(400, 200);
		dlg2->setAttribute(Qt::WA_DeleteOnClose);
		dlg2->setWindowTitle(QStringLiteral("����"));
		dlg2->show();
	});

	//�½�����
	QAction* buildAction = pMenuBarFile->addAction(QStringLiteral("&�½�����"));
	//pMenuBarFile->addAction(buildAction);
	//�򿪳���
	QAction* openAction = new QAction(QStringLiteral("&�򿪳���"), this);
	pMenuBarFile->addAction(openAction);
	//���泡��
	QAction* saveAction = new QAction(QStringLiteral("&���泡��"), this);
	pMenuBarFile->addAction(saveAction);
	//���Ϊ����
	QAction* saveasAction = new QAction(QStringLiteral("&���Ϊ����"), this);
	pMenuBarFile->addAction(saveasAction);
	//�رճ���
	QAction* closeAction = new QAction(QStringLiteral("&�رճ���"), this);
	pMenuBarFile->addAction(closeAction);
	//������ʳ���
	QAction* visitAction = new QAction(QStringLiteral("&������ʳ���"), this);
	pMenuBarFile->addAction(visitAction);
	//�˳�
	QAction* exitAction = new QAction(QStringLiteral("&�˳�"), this);
	pMenuBarFile->addAction(exitAction);

	pMenuBar->addMenu(pMenuBarFile);

	QMenu* pMenuBarView = new QMenu(QStringLiteral("&��ͼ"), this);
	//�½���ά��ͼ
	QAction* pTwoViewAction = new QAction(QStringLiteral("&�½���ά��ͼ"), this);
	pMenuBarView->addAction(pTwoViewAction);
	//�½���ά��ͼ
	QAction* pThreeViewAction = new QAction(QStringLiteral("&�½���ά��ͼ"), this);
	pMenuBarView->addAction(pThreeViewAction);
	//------------�ж���
	pMenuBarView->addSeparator();
	//���������
	QAction* pObjViewAction = new QAction(QStringLiteral("&���������"), this);
	pMenuBarView->addAction(pObjViewAction);
	//ʱ����
	QAction* pTimeLineAction = new QAction(QStringLiteral("&ʱ����"), this);
	pMenuBarView->addAction(pTimeLineAction);
	//��Ϣ�鿴��
	QAction* pMessageViewAction = new QAction(QStringLiteral("&��Ϣ�鿴��"), this);
	pMenuBarView->addAction(pMessageViewAction);
	//��������
	QAction* pEnvBackAction = new QAction(QStringLiteral("&��������"), this);
	pMenuBarView->addAction(pEnvBackAction);
	//���������Ӳ˵���ʼ
	QMenu* pEnvBackActionChild = new QMenu();
	QAction* pEnvBackActionChildAction1 = new QAction(QStringLiteral("&�ǿձ���"), this);
	pEnvBackActionChild->addAction(pEnvBackActionChildAction1);

	QAction* pEnvBackActionChildAction2 = new QAction(QStringLiteral("&���Ǳ���"), this);
	pEnvBackActionChild->addAction(pEnvBackActionChildAction2);

	pEnvBackAction->setMenu(pEnvBackActionChild);
	//���������Ӳ˵�����

	pMenuBar->addMenu(pMenuBarView);

	QMenu* pMenuBarInsert = new QMenu(QStringLiteral("&����"), this);
	//�½�
	QAction* pNewBuildAction = new QAction(QStringLiteral("&�½�"), this);
	pMenuBarInsert->addAction(pNewBuildAction);
	//���ļ�
	QAction* pFromFileAction = new QAction(QStringLiteral("���ļ�"), this);
	pMenuBarInsert->addAction(pFromFileAction);

	pMenuBar->addMenu(pMenuBarInsert);

	QMenu* pMenuBarAnalysis = new QMenu(QStringLiteral("&����"), this);
	//���и��Ƿ���
	QAction* pSensorAction = new QAction(QStringLiteral("&���и��Ƿ���"), this);
	pMenuBarAnalysis->addAction(pSensorAction);

	//���и��Ƿ����Ӳ˵���ʼ
	QMenu* pSensorChild = new QMenu();
	
	QAction* pSensorAction1 = new QAction(QStringLiteral("&�غɶԵ�Ŀ��ĸ��Ƿ���"), this);
	pSensorChild->addAction(pSensorAction1);

	QAction* pSensorAction2 = new QAction(QStringLiteral("&�غɶ�����Ŀ��ĸ��Ƿ���"), this);
	pSensorChild->addAction(pSensorAction2);

	QAction* pSensorAction3 = new QAction(QStringLiteral("&�غɶ��ƶ�Ŀ��ĸ��Ƿ���"), this);
	pSensorChild->addAction(pSensorAction3);

	pSensorAction->setMenu(pSensorChild);
	//���и��Ƿ����Ӳ˵�����

	//ҵ��Ԥ������
	QAction* pBusForecastAction = new QAction(QStringLiteral("&ҵ��Ԥ������"), this);
	pMenuBarAnalysis->addAction(pBusForecastAction);

	//ҵ��Ԥ�������Ӳ˵���ʼ
	QMenu* pBusForecastChild = new QMenu();
	
	QAction* pBusForecastAction1 = new QAction(QStringLiteral("&����Ԥ��"), this);
	pBusForecastChild->addAction(pBusForecastAction1);

	QAction* pBusForecastAction2 = new QAction(QStringLiteral("&��ӰԤ��"), this);
	pBusForecastChild->addAction(pBusForecastAction2);

	QAction* pBusForecastAction3 = new QAction(QStringLiteral("&��ӰԤ��"), this);
	pBusForecastChild->addAction(pBusForecastAction3);

	QAction* pBusForecastAction4 = new QAction(QStringLiteral("&�ɼ�Ԥ��"), this);
	pBusForecastChild->addAction(pBusForecastAction4);

	QAction* pBusForecastAction5 = new QAction(QStringLiteral("&����Ԥ��"), this);
	pBusForecastChild->addAction(pBusForecastAction5);
	
	pBusForecastAction->setMenu(pBusForecastChild);
	//ҵ��Ԥ�������Ӳ˵�����

	//���Ƽ���
	QAction* pCtrlCalcAction = new QAction(QStringLiteral("&���Ƽ���"), this);
	pMenuBarAnalysis->addAction(pCtrlCalcAction);

	//���Ƽ����Ӳ˵���ʼ
	QMenu* pCtrlCalcChild = new QMenu();
	
	QAction* pCtrlCalcAction1 = new QAction(QStringLiteral("&���α��"), this);
	pCtrlCalcChild->addAction(pCtrlCalcAction1);

	QAction* pCtrlCalcAction2 = new QAction(QStringLiteral("&˫������"), this);
	pCtrlCalcChild->addAction(pCtrlCalcAction2);
	
	QAction* pCtrlCalcAction3 = new QAction(QStringLiteral("&�����������"), this);
	pCtrlCalcChild->addAction(pCtrlCalcAction3);

	pCtrlCalcChild->addSeparator();
	
	QAction* pCtrlCalcAction4 = new QAction(QStringLiteral("&�����̬Ԥ��"), this);
	pCtrlCalcChild->addAction(pCtrlCalcAction4);
	
	pCtrlCalcAction->setMenu(pCtrlCalcChild);
	//���Ƽ����Ӳ˵�����

	//�粨��������
	QAction* pOnDemandAction = new QAction(QStringLiteral("&�粨��������"), this);
	pMenuBarAnalysis->addAction(pOnDemandAction);

	//�粨���������Ӳ˵���ʼ
	QMenu* pOnDemandChild = new QMenu();
	
	QAction* pOnDemandAction1 = new QAction(QStringLiteral("&S/N"), this);
	pOnDemandChild->addAction(pOnDemandAction1);

	QAction* pOnDemandAction2 = new QAction(QStringLiteral("&G/T"), this);
	pOnDemandChild->addAction(pOnDemandAction2);

	QAction* pOnDemandAction3 = new QAction(QStringLiteral("&EIRP"), this);
	pOnDemandChild->addAction(pOnDemandAction3);

	QAction* pOnDemandAction4 = new QAction(QStringLiteral("&������þ���"), this);
	pOnDemandChild->addAction(pOnDemandAction4);

	QAction* pOnDemandAction5 = new QAction(QStringLiteral("&�ռ䴫�����"), this);
	pOnDemandChild->addAction(pOnDemandAction5);
	
	pOnDemandAction->setMenu(pOnDemandChild);
	//�粨���������Ӳ˵�����

	//�ռ�Ŀ�����
	QAction* pSpaceTargetAction = new QAction(QStringLiteral("&�ռ�Ŀ�����"), this);
	pMenuBarAnalysis->addAction(pSpaceTargetAction);

	//�ռ�Ŀ������Ӳ˵���ʼ
	QMenu* pSpaceTargetChild = new QMenu();

	QAction* pSpaceTargetAction1 = new QAction(QStringLiteral("&�ռ�̬�Ʒ���"), this);
	pSpaceTargetChild->addAction(pSpaceTargetAction1);

	QAction* pSpaceTargetAction2 = new QAction(QStringLiteral("&��Ƭ�۲����"), this);
	pSpaceTargetChild->addAction(pSpaceTargetAction2);
	
	pSpaceTargetAction->setMenu(pSpaceTargetChild);
	//�ռ�Ŀ������Ӳ˵�����

	pMenuBar->addMenu(pMenuBarAnalysis);

	QMenu* pMenuBarAlgorithm = new QMenu(QStringLiteral("&�㷨��"), this);
	//ʱ��ת��
	QAction* pTimeSapceAction = new QAction(QStringLiteral("&ʱ��ת��"), this);
	pMenuBarAlgorithm->addAction(pTimeSapceAction);

	//ʱ��ת���Ӳ˵���ʼ
	QMenu* pTimeSapceChild = new QMenu();
	
	QAction* pTimeSapceAction1 = new QAction(QStringLiteral("&ʱ��ת��"), this);
	pTimeSapceChild->addAction(pTimeSapceAction1);

	QAction* pTimeSapceAction2 = new QAction(QStringLiteral("&����ת��"), this);
	pTimeSapceChild->addAction(pTimeSapceAction2);

	QAction* pTimeSapceAction3 = new QAction(QStringLiteral("&���µ����"), this);
	pTimeSapceChild->addAction(pTimeSapceAction3);

	QAction* pTimeSapceAction4 = new QAction(QStringLiteral("&������������"), this);
	pTimeSapceChild->addAction(pTimeSapceAction4);

	QAction* pTimeSapceAction5 = new QAction(QStringLiteral("&�������ϵת��"), this);
	pTimeSapceChild->addAction(pTimeSapceAction5);
	
	pTimeSapceAction->setMenu(pTimeSapceChild);
	//ʱ��ת���Ӳ˵�����

	//���Ԥ��
	QAction* pOrbitForecastAction = new QAction(QStringLiteral("&���Ԥ��"), this);
	pMenuBarAlgorithm->addAction(pOrbitForecastAction);

	//���Ԥ���Ӳ˵���ʼ
	QMenu* pOrbitForecastChild = new QMenu();

	QAction* pOrbitForecastAction1 = new QAction(QStringLiteral("&������Ԥ��"), this);
	pOrbitForecastChild->addAction(pOrbitForecastAction1);

	QAction* pOrbitForecastAction2 = new QAction(QStringLiteral("&SGP4/SDP4���Ԥ��"), this);
	pOrbitForecastChild->addAction(pOrbitForecastAction2);

	QAction* pOrbitForecastAction3 = new QAction(QStringLiteral("&���������Ԥ��"), this);
	pOrbitForecastChild->addAction(pOrbitForecastAction3);

	QAction* pOrbitForecastAction4 = new QAction(QStringLiteral("&��ֵ�����Ԥ��"), this);
	pOrbitForecastChild->addAction(pOrbitForecastAction4);
	
	pOrbitForecastAction->setMenu(pOrbitForecastChild);
	//���Ԥ���Ӳ˵�����

	//����ת��
	QAction* pRootConversionAction = new QAction(QStringLiteral("&����ת��"), this);
	pMenuBarAlgorithm->addAction(pRootConversionAction);
	//������
	QAction* pOrbitDesignAction = new QAction(QStringLiteral("&������"), this);
	pMenuBarAlgorithm->addAction(pOrbitDesignAction);
	//���ݷ���
	QAction* pDataSimulationAction = new QAction(QStringLiteral("&���ݷ���"), this);
	pMenuBarAlgorithm->addAction(pDataSimulationAction);

	//���ݷ����Ӳ˵���ʼ
	QMenu* pDataSimulationChild = new QMenu();
	
	QAction* pDataSimulationAction1 = new QAction(QStringLiteral("&������ݷ���"), this);
	pDataSimulationChild->addAction(pDataSimulationAction1);

	QAction* pDataSimulationAction2 = new QAction(QStringLiteral("&��ѧ���ݷ���"), this);
	pDataSimulationChild->addAction(pDataSimulationAction2);

	QAction* pDataSimulationAction3 = new QAction(QStringLiteral("&GPS���ݷ���"), this);
	pDataSimulationChild->addAction(pDataSimulationAction3);

	pDataSimulationAction->setMenu(pDataSimulationChild);
	//���ݷ����Ӳ˵�����

	//����ȷ��
	QAction* pOrbitDeterminationAction = new QAction(QStringLiteral("&����ȷ��"), this);
	pMenuBarAlgorithm->addAction(pOrbitDeterminationAction);
	//��������
	QAction* pAccAssessmentAction = new QAction(QStringLiteral("&��������"), this);
	pMenuBarAlgorithm->addAction(pAccAssessmentAction);

	pMenuBar->addMenu(pMenuBarAlgorithm);

	QMenu* pMenuBarTool = new QMenu(QStringLiteral("&������"), this);
	//���ĳ�������
	QAction* pAstUpdateAction = new QAction(QStringLiteral("&���ĳ�������"), this);
	pMenuBarTool->addAction(pAstUpdateAction);
	//SP3�ļ�����
	QAction* pFileDownloadAction = new QAction(QStringLiteral("&SP3�ļ�����"), this);
	pMenuBarTool->addAction(pFileDownloadAction);
	//�ռ�Ŀ����Ϣ�����
	QAction* pDatabaseUpdateAction = new QAction(QStringLiteral("&�ռ�Ŀ����Ϣ�����"), this);
	pMenuBarTool->addAction(pDatabaseUpdateAction);
	//�����Ƚ�
	QAction* pBallisticCmpAction = new QAction(QStringLiteral("&�����Ƚ�"), this);
	pMenuBarTool->addAction(pBallisticCmpAction);

	pMenuBar->addMenu(pMenuBarTool);

	QMenu* pMenuBarConfig = new QMenu(QStringLiteral("&����"), this);
	//ȫ������
	QAction* pSettingAction = new QAction(QStringLiteral("ȫ������"), this);
	pMenuBarConfig->addAction(pSettingAction);

	//ȫ�������Ӳ˵���ʼ
	QMenu* pSettingChild = new QMenu();

	QAction* pSettingAction1 = new QAction(QStringLiteral("&����Ŀ¼����"), this);
	pSettingChild->addAction(pSettingAction1);

	QAction* pSettingAction2 = new QAction(QStringLiteral("&��Ƭ�ļ�����"), this);
	pSettingChild->addAction(pSettingAction2);

	pSettingAction->setMenu(pSettingChild);
	//ȫ�������Ӳ˵�����

	pMenuBar->addMenu(pMenuBarConfig);

	QMenu* pMenuBarWindows = new QMenu(QStringLiteral("&����"), this);
	//�رն���
	QAction* pCloseTopAction = new QAction(QStringLiteral("&�رն���"), this);
	pMenuBarWindows->addAction(pCloseTopAction);
	//�ر�����
	QAction* pCloseAllAction = new QAction(QStringLiteral("&�ر�����"), this);
	pMenuBarWindows->addAction(pCloseAllAction);
	//���д���
	QAction* pArrangeWinAction = new QAction(QStringLiteral("&���д���"), this);
	pMenuBarWindows->addAction(pArrangeWinAction);
	//�������
	QAction* pCascadeWinAction = new QAction(QStringLiteral("&�������"), this);
	pMenuBarWindows->addAction(pCascadeWinAction);
	//ȫ����ʾ
	QAction* pFullScreenAction = new QAction(QStringLiteral("ȫ����ʾ"), this);
	pMenuBarWindows->addAction(pFullScreenAction);

	pMenuBar->addMenu(pMenuBarWindows);

	QMenu* pMenuBarHelp = new QMenu(QStringLiteral("&����"), this);
	//����
	QAction* pHelpAction = new QAction(QStringLiteral("&����"), this);
	pMenuBarHelp->addAction(pHelpAction);
	//����...
	QAction* pOnAction = new QAction(QStringLiteral("&����"), this);
	pMenuBarHelp->addAction(pOnAction);
	//����
	QAction* pLanguageAction = new QAction(QStringLiteral("&����"), this);
	pMenuBarHelp->addAction(pLanguageAction);
	//�����Ӳ˵���ʼ
	QMenu* pLanguageChild = new QMenu();
	QAction* pLanguageAction1 = new QAction(QStringLiteral("&����"), this);
	pLanguageChild->addAction(pLanguageAction1);
	pLanguageAction->setMenu(pLanguageChild);
	//�����Ӳ˵�����
	//Ƥ��
	QAction* pSkinAction = new QAction(QStringLiteral("&Ƥ��"), this);
	pMenuBarHelp->addAction(pSkinAction);

	//Ƥ���Ӳ˵���ʼ
	QMenu* pSkinActionChild = new QMenu();
	QAction* pSkinActionAction1 = new QAction(QStringLiteral("&ǳ��ɫ"), this);
	pSkinActionChild->addAction(pSkinActionAction1);

	QAction* pSkinActionAction2 = new QAction(QStringLiteral("&����ɫ"), this);
	pSkinActionChild->addAction(pSkinActionAction2);

	pSkinAction->setMenu(pSkinActionChild);
	//Ƥ���Ӳ˵�����

	pMenuBar->addMenu(pMenuBarHelp);
}

void Insight::createToolBar()
{
	
	pToolBar = addToolBar("");

	QToolButton* pBuildViewAction = new QToolButton(this);
	pBuildViewAction->setIcon(QIcon("../src/recent.png"));
	pBuildViewAction->setToolTip(QStringLiteral("�½�����"));
	pToolBar->addWidget(pBuildViewAction);

	QToolButton* pOpenViewAction = new QToolButton(this);
	pOpenViewAction->setIcon(QIcon("../src/open.png"));
	pOpenViewAction->setToolTip(QStringLiteral("�򿪳���"));
	pToolBar->addWidget(pOpenViewAction);

	QToolButton* pSaveViewAction = new QToolButton(this);
	pSaveViewAction->setIcon(QIcon("../src/save.png"));
	pSaveViewAction->setToolTip(QStringLiteral("���泡��"));
	pToolBar->addWidget(pSaveViewAction);

	pToolBar->addSeparator();

	QToolButton* pInsertObjAction = new QToolButton(this);
	pInsertObjAction->setIcon(QIcon("../src/editable.ico"));
	pInsertObjAction->setToolTip(QStringLiteral("�������"));
	pToolBar->addWidget(pInsertObjAction);

	pToolBar->addSeparator();

	QToolButton* pReportAction = new QToolButton(this);
	pReportAction->setIcon(QIcon("../src/checkOTP.ico"));
	pReportAction->setToolTip(QStringLiteral("�����ͼ�����"));
	pToolBar->addWidget(pReportAction);

	QToolButton* pVisibilityAction = new QToolButton(this);
	pVisibilityAction->setIcon(QIcon("../src/erase.ico"));
	pVisibilityAction->setToolTip(QStringLiteral("�ɼ���"));
	pToolBar->addWidget(pVisibilityAction);

	QToolButton* pSensorVisAction = new QToolButton(this);
	pSensorVisAction->setIcon(QIcon("../src/editable.ico"));
	pSensorVisAction->setToolTip(QStringLiteral("�������ɼ���"));
	pToolBar->addWidget(pSensorVisAction);

	QToolButton* pDebrisObservationAction = new QToolButton(this);
	pDebrisObservationAction->setIcon(QIcon("../src/disconnect.ico"));
	pDebrisObservationAction->setToolTip(QStringLiteral("��Ƭ�۲����"));
	pToolBar->addWidget(pDebrisObservationAction);

	pToolBar->addSeparator();

	QToolButton* pDatabaseUpdateAction = new QToolButton(this);
	pDatabaseUpdateAction->setIcon(QIcon("../src/cleanOTP.ico"));
	pDatabaseUpdateAction->setToolTip(QStringLiteral("�ռ�Ŀ����Ϣ�����"));
	pToolBar->addWidget(pDatabaseUpdateAction);

	pToolBar->addSeparator();

	QToolButton* pFullScreenAction = new QToolButton(this);
	pFullScreenAction->setIcon(QIcon("../src/check.ico"));
	pFullScreenAction->setToolTip(QStringLiteral("ȫ����ʾ"));
	pToolBar->addWidget(pFullScreenAction);

	QToolButton* pCascadeWinAction = new QToolButton(this);
	pCascadeWinAction->setIcon(QIcon("../src/read.ico"));
	pCascadeWinAction->setToolTip(QStringLiteral("�������"));
	pToolBar->addWidget(pCascadeWinAction);

	QToolButton* pArrangeWinAction = new QToolButton(this);
	pArrangeWinAction->setIcon(QIcon("../src/readOTP.ico"));
	pArrangeWinAction->setToolTip(QStringLiteral("���д���"));
	pToolBar->addWidget(pArrangeWinAction);

	pToolBar->addSeparator();

	QToolButton* pTimeLineAction = new QToolButton(this);
	pTimeLineAction->setIcon(QIcon("../src/downloadOTP.ico"));
	pTimeLineAction->setToolTip(QStringLiteral("ʱ����"));
	pToolBar->addWidget(pTimeLineAction);

	pToolBar->addSeparator();

	this->addToolBarBreak(Qt::TopToolBarArea);

	pToolBar2 = addToolBar("");
	pLineEdit = new QLineEdit();
	pLineEdit->setMaximumSize(QSize(pLineWidth, pLineHight));
	pLineEdit->setPlaceholderText(QStringLiteral("����"));	//����Ĭ����ʾ��

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
	//��ȡ���λ��(mouseMoveEvent(QMouseEvent* e))
	pPosLabel = new QLabel();
	pStatusBar->addPermanentWidget(pPosLabel);


	//��ȡ��ǰʱ��
	pTimeLabel = new QLabel();
	pStatusBar->addPermanentWidget(pTimeLabel);

	QTimer *pTimer = new QTimer(this);
	pTimer->start(1000);
	connect(pTimer, SIGNAL(timeout()), this, SLOT(timeUpdate_Slot()));

	//������д������
	QLabel *pWelCome = new QLabel(QStringLiteral("����:   60.000��"));
	pStatusBar->addPermanentWidget(pWelCome);
}

void Insight::createOutputDocWidget()
{
	pDocWidget = new QDockWidget(QStringLiteral("���������"), this);
	
	pDocWidget->setWindowFlags(Qt::WindowStaysOnTopHint);

	pDocWidget->setFeatures(QDockWidget::AllDockWidgetFeatures | QDockWidget::DockWidgetMovable);
	pDocWidget->setMinimumWidth(300);
	


	//pDocWidget->setWindowFlags(pDocWidget->windowFlags() | Qt::Window);
	//pDocWidget->showNormal();
	//pDocWidget->setVisible(true);
	
	//���������������е���ʽ�����Ϣ
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
	//this->mdiArea->addSubWindow(pTextEdit);	//����Ӵ��嵽���ĵ�����
	//pTextEdit->showMaximized();	//���Ӵ������


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
	QString timeStr = currentTime.toString(QStringLiteral("yyyy��MM��dd�� hh:mm:ss"));

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