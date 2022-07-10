#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include <memory>
#include <string>

#include "GameFactory.h"
#include "gamemodedialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "AlphabookQT_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    UGameFactory factory;
    for(;;)
    {
        GameModeDialog gmd(factory.Modes());

        if(gmd.result() == gmd.Rejected)
        {
            break;
        }

        wstring mode_name{gmd.GetGameMode().toStdWString()};
        shared_ptr<IGameMode> game_mode = factory.GameMode(mode_name);
        if(game_mode.get())
        {
            game_mode->StartGame();
        }
    }

    return 0;
}
