#ifndef PROMPT_H
#define PROMPT_H

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QIcon>
#include <QScrollArea>
#include <QLabel>
#include "slidingpanel.h"
#include "plugininterface.h"

namespace KU::UI::WIDGETS
{

class ChoiceWidget : public QFrame
{
    Q_OBJECT
protected:
    void mousePressEvent(QMouseEvent* event) override;

public:
    ChoiceWidget(QString const& title, QIcon const& icon, QWidget* parent = nullptr);

signals:
    void clicked();
};

class Prompt : public XB::SlidingPanel
{
    Q_OBJECT
private:
    QHBoxLayout* choicesLayout = nullptr;
    QFrame* choicesWidget = nullptr;
    QScrollArea* scrollArea = nullptr;

public:
    Prompt(int width, QWidget* parent = nullptr);

    void setChoices(QSet<KU::PLUGIN::PluginInterface*> plugins);

signals:
    void choiceMade(KU::PLUGIN::PluginInterface* plugin);
};

}

#endif // PROMPT_H
