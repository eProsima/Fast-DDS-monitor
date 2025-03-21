#include <fastdds_monitor/io/ClipboardHandler.h>

ClipboardHandler::ClipboardHandler(
        QObject* parent)
    : QObject(parent)
{
}

ClipboardHandler::~ClipboardHandler()
{
}

void ClipboardHandler::setClipboardText(
        const QString& text)
{
    QClipboard* clipboard = QGuiApplication::clipboard();
    clipboard->setText(text);
}

QString ClipboardHandler::getClipboardText()
{
    QClipboard* clipboard = QGuiApplication::clipboard();
    return clipboard->text();
}
