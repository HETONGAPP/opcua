#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QOpcUaEndpointDescription>
#include <QOpcUaProvider>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    provider = new QOpcUaProvider(this);
    //if (provider.availableBackends().isEmpty())
    client = provider->createClient(QString("open62541"));
    connect(ui->requestEndpoints,&QPushButton::clicked,this,&MainWindow::on_btn_requestEndpoints_clicked);
    connect(client,&QOpcUaClient::endpointsRequestFinished,this,&MainWindow::SLOT_endpointsRequestFinished);
    connect(client,&QOpcUaClient::stateChanged,this,&MainWindow::SLOT_stateChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_requestEndpoints_clicked()
{
    qDebug()<<"readnode";
    client->requestEndpoints(QUrl("opc.tcp://tong:4840"));
}

void MainWindow::on_btn_readnode_clicked()
{
    node->readAttributes(QOpcUa::NodeAttribute::Value);
    qDebug()<<"readnode"<<node->nodeId();
}

void MainWindow::on_btn_writeAttribute_clicked()
{
    QOpcUa::NodeAttribute attribute ;
    attribute = QOpcUa::NodeAttribute::Value;
    QVariant var=12;
    //node->writeAttribute(attribute,QString("ssss"),QOpcUa::Types::String);
    node->writeAttribute(attribute,var);
}

void MainWindow::SLOT_endpointsRequestFinished(QVector<QOpcUaEndpointDescription> endpoints, QOpcUa::UaStatusCode statusCode)
{
    qDebug()<<endpoints.at(0).endpointUrl();
    //qDebug() <<endpoints.first().endpointUrl();
    qDebug()<<statusCode;
    qDebug() << "Endpoints returned:" << endpoints.count();
    qDebug()<<endpoints.size();
    if (endpoints.size())
        client->connectToEndpoint(endpoints.at(0)); // Connect to the first endpoint in the list
}

void MainWindow::SLOT_attributeRead(QOpcUa::NodeAttributes attributes)
{
    qDebug() << "Signal for attributes:" << attributes;
    //    if (node->attributeError(QOpcUa::NodeAttribute::BrowseName) != QOpcUa::UaStatusCode::Good) {
    //        qDebug() << "Failed to read attribute:" << node->attributeError(QOpcUa::NodeAttribute::BrowseName);
    //        client->disconnectFromEndpoint();
    //    }
    //qDebug() << "Browse name:" << node->attribute(QOpcUa::NodeAttribute::BrowseName).value<QOpcUa::QQualifiedName>().name();
    qDebug()<<"value:"<<node->attribute(QOpcUa::NodeAttribute::Value);

}

void MainWindow::SLOT_stateChanged(QOpcUaClient::ClientState state)
{
    qDebug() << "Client state changed:" << state;
    if (state == QOpcUaClient::ClientState::Connected) {
        //QOpcUaNode定义
        node = client->node("ns=2;s=my.plc.s1");
        if (node)
            qDebug() << "A node object has been created";
    }
    connect(node,&QOpcUaNode::attributeRead,this,&MainWindow::SLOT_attributeRead);

}

