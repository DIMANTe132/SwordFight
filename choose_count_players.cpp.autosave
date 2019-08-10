#include "choose_count_players.h"
#include <QBoxLayout>
#include <QSpinBox>
#include <QPushButton>

Choose_count_players::Choose_count_players(QWidget *parent)
    :QWidget (parent)
{
    if(parent)
        parent->setEnabled(false);

    Window = new QWidget(parent);

    Window->setFixedSize(500,500);
    Window->setWindowFlag(Qt::ToolTip);

    main_layout = new QVBoxLayout;
    QHBoxLayout *layot_first = new QHBoxLayout;
    QHBoxLayout *layout_second = new QHBoxLayout;

    QSpinBox *spin_box = new QSpinBox;
    spin_box->setFixedSize(100,60);
    spin_box->setRange(2,4);
    spin_box->setFont(QFont("Helvetica [Cronyx]",35,-1, true));

    QPushButton *choose_button = new QPushButton;
    choose_button->setText("Выбрать");
    choose_button->setFixedSize(300,spin_box->size().height());
    
    layot_first->addWidget(spin_box);
    layot_first->addWidget(choose_button);
    main_layout->addLayout(layot_first);

    Window->setLayout(main_layout);
    Window->setEnabled(true);
    Window->show();
}

Choose_count_players::~Choose_count_players()
{
    delete this;
}
