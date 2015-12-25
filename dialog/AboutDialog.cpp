#include "AboutDialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    setFixedSize(size());
    connect(ui->okButton, &QPushButton::clicked, this, &QDialog::accept);

    ui->infoLabel->setText(ui->infoLabel->text().arg(APP_VERSION));
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
