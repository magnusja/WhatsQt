/*
 * This file is part of WhatsQt.
 *
 * WhatsQt is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * WhatsQt is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with WhatsQt.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "PreferencesDialog.h"
#include "ui_PreferencesDialog.h"

PreferencesDialog::PreferencesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreferencesDialog)
{
    ui->setupUi(this);

    ui->notificationButtonGroup->buttons()[preferences.getNotificationType()]->setChecked(true);

    ui->locationCheckBox->setChecked(preferences.isPermissionGranted(QWebEnginePage::Geolocation));
    ui->cameraCheckBox->setChecked(preferences.isPermissionGranted(QWebEnginePage::MediaVideoCapture));
    ui->micCheckBox->setChecked(preferences.isPermissionGranted(QWebEnginePage::MediaAudioCapture));

    connect(this, &QDialog::accepted, this, [this]() {
        qDebug() << "saving preferences";

        // see http://doc.qt.io/qt-4.8/qbuttongroup.html#addButton
        int type = qAbs(ui->notificationButtonGroup->checkedId()) - 2;
        preferences.setNotificationType((Preferences::NotificationType) type);

        preferences.setPermission(QWebEnginePage::Geolocation, ui->locationCheckBox->isChecked());
        preferences.setPermission(QWebEnginePage::MediaVideoCapture, ui->cameraCheckBox->isChecked());
        preferences.setPermission(QWebEnginePage::MediaAudioCapture, ui->micCheckBox->isChecked());
    });
}

PreferencesDialog::~PreferencesDialog()
{
    delete ui;
}
