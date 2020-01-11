#include "settingstab.h"

namespace KU::UI::WIDGETS
{

SettingsListDelegate::SettingsListDelegate(int iconSize, QObject* parent)
    : QStyledItemDelegate(parent), iconSize(iconSize)
{

}

void SettingsListDelegate::initStyleOption(QStyleOptionViewItem* option, QModelIndex const& index) const
{
    QStyledItemDelegate::initStyleOption(option, index);
    option->decorationSize = QSize(this->iconSize, this->iconSize);
}

SettingsTab::SettingsTab(QWidget* parent)
    : QWidget(parent)
{
    QHBoxLayout* layout = new QHBoxLayout(this);

    this->listWidget = new QListWidget(this);
    this->listWidget->setItemDelegate(new SettingsListDelegate(40));
    this->listWidget->setFlow(QListView::TopToBottom);
    this->listWidget->setFixedWidth(200);
    layout->addWidget(this->listWidget);

    this->stackedWidget = new QStackedWidget(this);
    layout->addWidget(this->stackedWidget, 1);

    connect(this->listWidget, &QListWidget::clicked, this, [=](QModelIndex const& index)
    {
        this->stackedWidget->setCurrentIndex(index.row());
    });

    this->setLayout(layout);
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
