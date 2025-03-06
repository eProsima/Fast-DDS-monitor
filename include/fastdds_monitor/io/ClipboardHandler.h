#ifndef CLIPBOARDHANDLER_H
#define CLIPBOARDHANDLER_H

#include <QClipboard>
#include <QQmlEngine>
#include <QGuiApplication>

class ClipboardHandler : public QObject
{
    Q_OBJECT
public:
    explicit ClipboardHandler(QObject *parent = nullptr)
        : QObject(parent)
    {}

    // Expose the clipboard object directly to QML
    Q_INVOKABLE void setClipboardText(const QString &text)
    {
        QClipboard *clipboard = QGuiApplication::clipboard();
        clipboard->setText(text);
    }

    Q_INVOKABLE QString getClipboardText()
    {
        QClipboard *clipboard = QGuiApplication::clipboard();
        return clipboard->text();
    }
};

#endif // CLIPBOARDHANDLER_H