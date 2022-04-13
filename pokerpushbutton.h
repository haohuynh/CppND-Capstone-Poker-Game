#ifndef POKERPUSHBUTTON_H
#define POKERPUSHBUTTON_H

#include <QPushButton>
#include <QMouseEvent>
#include <Qt>
#include <QObject>

class PokerPushButton : public QPushButton
{

    Q_OBJECT

private:

    /*The gif-file management object */
    QMovie* iMovie;

public:

    /*The constructor of this Poker Push Button*/
    explicit PokerPushButton(const QString ifName = NULL, QWidget* parent = 0);

    /*The destructor of this class*/
    ~PokerPushButton();

signals:


public slots:

    /**
     * Updating the poker push button icon
     * @brief updateIcon
     * @param cFrame : the current frame of the input gif file
     */
    void updateIcon(int cFrame);
};

#endif // POKERPUSHBUTTON_H
