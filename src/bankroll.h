#ifndef BANKROLL_H
#define BANKROLL_H

#include <QDialog>
#include <QCloseEvent>

namespace Ui {
class BankRoll;
}

class BankRoll : public QDialog
{
    Q_OBJECT

private:
    Ui::BankRoll *ui;

public:
    explicit BankRoll(QWidget *parent = 0);
    ~BankRoll();

    /**
     * This function sets up the components for the BankRoll dialog
     * @brief populateUI
     * @param bkRoll
     */
    void populateUI(int bkRoll = 0);

    /**
     * This function returns the bet value that user had chosen
     * @brief getBetValue
     * @return
     */
    int getBetValue();

protected:

    /**
     * Handling the default close button of this dialog
     * @brief BankRoll::closeEvent
     */
    virtual void closeEvent(QCloseEvent*);

signals:

    /*This bet-value signal is generated after the done button was clicked*/
    void processBetValue();


private slots:
    void on_doneButton_clicked();
};

#endif // BANKROLL_H
