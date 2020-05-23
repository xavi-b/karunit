#include "icondelegate.h"

namespace KU::UI::WIDGETS
{

IconDelegate::IconDelegate(int iconSize, QObject* parent)
    : QStyledItemDelegate(parent), iconSize(iconSize)
{

}

void IconDelegate::initStyleOption(QStyleOptionViewItem* option, QModelIndex const& index) const
{
    QStyledItemDelegate::initStyleOption(option, index);
    option->decorationSize = QSize(this->iconSize, this->iconSize);
}

}
