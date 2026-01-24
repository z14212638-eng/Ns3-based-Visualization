QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    JsonHelper.cpp \
    antennas.cpp \
    ap_config.cpp \
    configgraphicsview.cpp \
    edca_config.cpp \
    main.cpp \
    mainwindow.cpp \
    node_config.cpp \
    page1_model_chose.cpp \
    simu_config.cpp \
    ppdu_timeline_view.cpp\
    ppdu_adapter.cpp\
    ppdu_visual_item.cpp\
    qt_ppdu_reader.cpp\
    shm.cpp\
    ppdu_info_overlay.cpp\
    legend_overlay.cpp\
    visualizer_config.cpp\
    utils.cpp\
    indus_widget.cpp\
    image_viewer.cpp

HEADERS += \
    JsonHelper.h \
    antennas.h \
    ap_config.h \
    configgraphicsview.h \
    edca_config.h \
    mainwindow.h \
    node_config.h \
    page1_model_chose.h \
    simu_config.h \
    ppdu_timeline_view.h\
    ppdu_adapter.h\
    ppdu_visual_item.h\
    qt_ppdu_reader.h\
    shm.h\
    ppdu_info_overlay.h\
    legend_overlay.h\
    visualizer_config.h\
    utils.h\
    indus_widget.h\
    image_viewer.h

FORMS += \
    antennas.ui \
    ap_config.ui \
    edca_config.ui \
    mainwindow.ui \
    node_config.ui \
    page1_model_chose.ui \
    simu_config.ui\

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
