find_package(Qt5DBus)
set(ADDITIONAL_QT_MODULES DBus)

qt5_add_dbus_interface(SOURCE_FILES notification/linux/org.freedesktop.Notifications.xml FreedesktopNotifications)

list(APPEND SOURCE_FILES
        notification/linux/FreedesktopNotificationService.cpp)