#include "bankroll.h"
#include "ui_bankroll.h"

BankRoll::BankRoll(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BankRoll)
{
    ui->setupUi(this);

    //Make two way connection between the SpinBox and the Slider of bank roll values
    QObject::connect(ui->spinBox, SIGNAL(valueChanged(int)),
                     ui->horizontalSlider, SLOT(setValue(int)));
    QObject::connect(ui->horizontalSlider, SIGNAL(valueChanged(int)),
                     ui->spinBox, SLOT(setValue(int)));

}

BankRoll::~BankRoll()
{
    delete ui;
}

/**
 * Reference to the function declaration
 * @brief BankRoll::populateUI
 * @param bkRoll
 */
void BankRoll::populateUI(int bkRoll)
{

    ui->bkRLbl->setText("Your current bank roll is: " + QString::number(bkRoll)
                        + "\nHow much you want to bet for the game:\n");

    ui->spinBox->setRange(1, bkRoll);
    ui->horizontalSlider->setRange(1, bkRoll);
    ui->spinBox->setValue(bkRoll/2);
    ui->horizontalSlider->setValue(bkRoll/2);

    show();

}

/**
 * Reference to the function declaration
 * @brief BankRoll::getBetValue
 * @return
 */
int BankRoll::getBetValue()
{
    return ui->spinBox->value();
}

void BankRoll::on_doneButton_clicked()
{
    emit processBetValue();
    hide();
}

/**
 * Handling the default close button of this dialog
 * @brief BankRoll::closeEvent
 * @param event
 */
void BankRoll::closeEvent(QCloseEvent* event){

    emit processBetValue();
    event->accept();

}



