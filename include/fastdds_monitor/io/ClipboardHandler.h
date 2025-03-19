#ifndef CLIPBOARDHANDLER_H
#define CLIPBOARDHANDLER_H

#include <QClipboard>
#include <QQmlEngine>
#include <QGuiApplication>

class ClipboardHandler : public QObject
{
    Q_OBJECT

public:

    ClipboardHandler(
            QObject* parent = nullptr);

    ~ClipboardHandler();

    // Expose the clipboard object directly to QML
    Q_INVOKABLE void setClipboardText(
            const QString& text);

    Q_INVOKABLE QString getClipboardText();

};

#endif // CLIPBOARDHANDLER_H