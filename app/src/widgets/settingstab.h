#ifndef SETTINGSTAB_H
#define SETTINGSTAB_H

#include <QListWidget>
#include <QStackedWidget>
#include <QHBoxLayout>
#include <QStyledItemDelegate>
#include <QPainter>

namespace KU::UI::WIDGETS
{

class SettingsListDelegate : public QStyledItemDelegate
{
    Q_OBJECT
private:
    int iconSize;
public:
    SettingsListDelegate(int iconSize, QObject* parent = nullptr);
    void initStyleOption(QStyleOptionViewItem* option, QModelIndex const& index) const;
};

class SettingsTab : public QWidget
{
    Q_OBJECT

private:
    QListWidget* listWidget = nullptr;
    QStackedWidget* stackedWidget = nullptr;

public:
    SettingsTab(QWidget* parent = nullptr);

    void addTab(QWidget* widget, QIcon icon, QString const& name);
};

}

#endif // SETTINGSTAB_H
