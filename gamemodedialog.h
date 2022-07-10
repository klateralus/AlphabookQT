#ifndef GAMEMODEDIALOG_H
#define GAMEMODEDIALOG_H

#include <QDialog>
#include <QStringList>
#include <QString>
#include <vector>
#include <string>

using namespace std;

namespace Ui {
class GameModeDialog;
}

class GameModeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GameModeDialog(QWidget *parent = nullptr);
    GameModeDialog(const vector<wstring>& modes, QWidget *parent = nullptr);
    ~GameModeDialog();

    QString GetGameMode() const {return Mode;};

private:
    Ui::GameModeDialog *ui{nullptr};
    QStringList Modes;
    QString Mode{""};

public slots:
    void Play(bool checked);

};

#endif // GAMEMODEDIALOG_H
