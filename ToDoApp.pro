# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# The name of your application
TARGET = ToDoApp

CONFIG += sailfishapp

SOURCES += src/ToDoApp.cpp \
    src/categorylist.cpp \
    src/datastorer.cpp \
    src/task.cpp \
    src/tasklistmodel.cpp \
    src/tasklistview.cpp

DISTFILES += qml/ToDoApp.qml \
    Task.md \
    qml/cover/CoverPage.qml \
    qml/dialogs/FilterChooserDialog.qml \
    qml/dialogs/NewCategoryDialog.qml \
    qml/dialogs/TaskEditorDialog.qml \
    qml/pages/CategoryListPage.qml \
    qml/pages/TaskListCompletedPage.qml \
    qml/pages/TaskListNonCompletedPage.qml \
    qml/pages/TaskViewCompletedPage.qml \
    qml/pages/TaskViewPage.qml \
    rpm/ToDoApp.changes.in \
    rpm/ToDoApp.changes.run.in \
    rpm/ToDoApp.spec \
    rpm/ToDoApp.yaml \
    translations/*.ts \
    ToDoApp.desktop

SAILFISHAPP_ICONS = 86x86 108x108 128x128 172x172

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n

# German translation is enabled as an example. If you aren't
# planning to localize your app, remember to comment out the
# following TRANSLATIONS line. And also do not forget to
# modify the localized app name in the the .desktop file.
TRANSLATIONS += translations/ToDoApp-de.ts

HEADERS += \
    src/categorylist.h \
    src/datastorer.h \
    src/task.h \
    src/tasklistmodel.h \
    src/tasklistview.h
