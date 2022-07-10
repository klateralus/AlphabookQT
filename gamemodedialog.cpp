#include "gamemodedialog.h"
#include "ui_gamemodedialog.h"
#include <QObject>
#include <QAbstractButton>

GameModeDialog::GameModeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameModeDialog)
{
    ui->setupUi(this);
}

GameModeDialog::GameModeDialog(const vector<wstring>& modes, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::GameModeDialog)
{
    ui->setupUi(this);

    Modes.clear();
    for(const wstring& wstr: modes)
    {
        Modes.append(QString::fromStdWString(wstr));
    }

    ui->comboBox->clear();
    ui->comboBox->addItems(Modes);
    QObject::connect(ui->playButton, &QAbstractButton::clicked, this, &GameModeDialog::Play);

    show();
    exec();
}

void GameModeDialog::Play(bool checked)
{
    Mode = ui->comboBox->currentText();
    accept();
}

GameModeDialog::~GameModeDialog()
{
    delete ui;
}
