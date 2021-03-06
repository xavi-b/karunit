#include "settingstab.h"

namespace KU::UI::WIDGETS
{

void SettingsTab::addAppTab()
{
    //TODO
    //this->addTab()
}

SettingsTab::SettingsTab(QWidget* parent)
    : QWidget(parent)
{
    QHBoxLayout* layout = new QHBoxLayout(this);
    QVBoxLayout* leftLayout = new QVBoxLayout;

    this->listWidget = new QListWidget(this);
    this->listWidget->setItemDelegate(new IconDelegate(40));
    this->listWidget->setFlow(QListView::TopToBottom);
    this->listWidget->setFixedWidth(200);
    leftLayout->addWidget(this->listWidget, 1);

    QPushButton* quitButton = new QPushButton;
    quitButton->setText(tr("Quit"));
    connect(quitButton, &QPushButton::clicked, this, [=]()
    {
        if(QMessageBox::question(this, tr("Close request"), tr("Are you sure about closing ?"))
        == QMessageBox::Yes)
        {
            QCoreApplication::instance()->quit();
        }
    });
    leftLayout->addWidget(quitButton);

    layout->addLayout(leftLayout);

    this->stackedWidget = new QStackedWidget(this);
    layout->addWidget(this->stackedWidget, 1);

    connect(this->listWidget, &QListWidget::clicked, this, [=](QModelIndex const& index)
    {
        this->stackedWidget->setCurrentIndex(index.row());
    });

    this->setLayout(layout);

    this->addAppTab();
}

void SettingsTab::addTab(QWidget* widget, QIcon icon, QString const& name)
{
    QListWidgetItem* item = new QListWidgetItem(icon, name);
    item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    item->setSizeHint(QSize(80, 50));
    this->listWidget->addItem(item);
    this->stackedWidget->addWidget(widget);
}

}
