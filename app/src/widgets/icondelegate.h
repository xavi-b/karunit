#ifndef ICONDELEGATE_H
#define ICONDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>

namespace KU::UI::WIDGETS
{

class IconDelegate : public QStyledItemDelegate
{
    Q_OBJECT
private:
    int iconSize;
public:
    IconDelegate(int iconSize, QObject* parent = nullptr);
    void initStyleOption(QStyleOptionViewItem* option, QModelIndex const& index) const;
};

}

#endif // ICONDELEGATE_H
