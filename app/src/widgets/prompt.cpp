#include "prompt.h"

namespace KU::UI::WIDGETS
{

void ChoiceWidget::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        emit clicked();
        event->accept();
        return;
    }
    QFrame::mousePressEvent(event);
}

ChoiceWidget::ChoiceWidget(QString const& title, QIcon const& icon, QWidget* parent)
    : QFrame(parent)
{
    this->setFixedSize(80, 80);
    this->setFrameShape(QFrame::Shape::Box);
    this->setCursor(Qt::PointingHandCursor);

    QLabel* iconLabel = new QLabel;
    iconLabel->setPixmap(icon.pixmap(50, 50));
    iconLabel->setAlignment(Qt::AlignCenter);

    QLabel* titleLabel = new QLabel;
    titleLabel->setText(title);
    titleLabel->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->addWidget(iconLabel, 1, Qt::AlignCenter);
    layout->addWidget(titleLabel, 0, Qt::AlignHCenter | Qt::AlignBottom);

    this->setLayout(layout);
}

Prompt::Prompt(int width, QWidget* parent)
    : XB::SlidingPanel(width, parent)
{
    this->choicesLayout = new QHBoxLayout;

    this->choicesWidget = new QFrame;
    this->choicesWidget->setLayout(this->choicesLayout);

    this->scrollArea = new QScrollArea;
    this->scrollArea->setWidgetResizable(true);
    this->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    this->scrollArea->setWidget(this->choicesWidget);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->addWidget(this->scrollArea);
    this->setLayout(layout);
}

void Prompt::setChoices(QSet<PLUGIN::PluginInterface*> plugins)
{
    while(QLayoutItem* i = this->choicesLayout->takeAt(0))
    {
        this->choicesLayout->removeItem(i);
        if(i->widget())
            i->widget()->deleteLater();
    }

    this->choicesLayout->addStretch(1);
    for(auto& p : plugins)
    {
        ChoiceWidget* choiceWidget = new ChoiceWidget(p->name(), p->icon());
        connect(choiceWidget, &ChoiceWidget::clicked,
                this, [=]()
        {
            emit choiceMade(p);
            this->slideUp();
        });
        this->choicesLayout->addWidget(choiceWidget);
    }
    this->choicesLayout->addStretch(1);

    this->choicesLayout->update();
    this->scrollArea->setFixedHeight(this->choicesWidget->sizeHint().height() + 10);
}

}
