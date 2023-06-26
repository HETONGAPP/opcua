#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QOpcUaClient>
#include <QOpcUaNode>
#include <QtOpcUa>
#include <QDebug>
#include <QOpcUaEndpointDescription>
#include <QOpcUaProvider>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

    void on_btn_requestEndpoints_clicked();
    void on_btn_readnode_clicked();
    void on_btn_writeAttribute_clicked();

    void SLOT_endpointsRequestFinished (QVector<QOpcUaEndpointDescription> endpoints , QOpcUa::UaStatusCode statusCode);
    void SLOT_attributeRead ( QOpcUa::NodeAttributes attributes );
    void SLOT_stateChanged (QOpcUaClient::ClientState state );

private:

    Ui::MainWindow *ui;
    QOpcUaClient *client;
    QOpcUaProvider* provider;
    QOpcUaNode* node;
};
#endif // MAINWINDOW_H
