QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# SFML stuff
sfml_version      = "2.5.1"

sfml_basePath     = "../../extern/SFML-$$sfml_version"
sfml_includePath  = "$$sfml_basePath/include"
sfml_binPath      = "$$sfml_basePath/bin"
sfml_libs_debug   = "$$sfml_binPath/Debug/lib/libsfml-audio-d.a" \
                    "$$sfml_binPath/Debug/lib/libsfml-graphics-d.a" \
                    "$$sfml_binPath/Debug/lib/libsfml-main-d.a" \
                    "$$sfml_binPath/Debug/lib/libsfml-network-d.a" \
                    "$$sfml_binPath/Debug/lib/libsfml-system-d.a" \
                    "$$sfml_binPath/Debug/lib/libsfml-window-d.a"

sfml_libs_release = "$$sfml_binPath/Release/lib/libsfml-audio.a" \
                    "$$sfml_binPath/Release/lib/libsfml-graphics.a" \
                    "$$sfml_binPath/Release/lib/libsfml-main.a" \
                    "$$sfml_binPath/Release/lib/libsfml-network.a" \
                    "$$sfml_binPath/Release/lib/libsfml-system.a" \
                    "$$sfml_binPath/Release/lib/libsfml-window.a"


CONFIG(release, debug|release): sfml_libs = $$sfml_libs_release
CONFIG(debug, debug|release):   sfml_libs = $$sfml_libs_debug
# End SFML stuff

# box2d stuff
box2DInclude = extern/box2d/include
box2DSrc     = extern/box2d/src
# End box2d stuff
srcPath = src
incPath = inc

INCLUDEPATH += $$sfml_includePath \
               $$box2DInclude \
               $$box2DSrc \
               $$incPath \
               $$incPath/utility 
			   
DEPENDPATH  += $$sfml_includePath \
               $$sfml_includePath \
               $$box2DInclude
LIBS        += $$sfml_libs




SOURCES += \
    $$srcPath/gameEngine.cpp \
	$$srcPath/utility/vector.cpp \
	$$srcPath/utility/timer.cpp \
    $$srcPath/collider.cpp \
	$$srcPath/RectCollider.cpp \
	$$srcPath/circleCollider.cpp \
    $$srcPath/controller.cpp \
	$$srcPath/keyController.cpp \
	$$srcPath/gravityController.cpp \
    $$srcPath/painter.cpp \
    $$srcPath/gameObject.cpp \
    main.cpp \
    mainwindow.cpp \
    src/utility/vectorFunction.cpp



HEADERS += \
    $$incPath/gameEngine.h \
    $$incPath/utility/vector.h \
    $$incPath/utility/timer.h \
    $$incPath/collider.h \
    $$incPath/RectCollider.h \
    $$incPath/circleCollider.h \
    $$incPath/controller.h \
    $$incPath/keyController.h \
	$$incPath/gravityController.h \
	$$incPath/painter.h \
	$$incPath/gameObject.h \
    inc/utility/vectorFunction.h \
    mainwindow.h

FORMS += \
    mainwindow.ui
	
SOURCES += \
	$$box2DSrc/dynamics/b2_body.cpp \
    $$box2DSrc/dynamics/b2_chain_circle_contact.cpp \
    $$box2DSrc/dynamics/b2_chain_polygon_contact.cpp \
    $$box2DSrc/dynamics/b2_circle_contact.cpp \
    $$box2DSrc/dynamics/b2_contact.cpp \
    $$box2DSrc/dynamics/b2_contact_manager.cpp \
    $$box2DSrc/dynamics/b2_contact_solver.cpp \
    $$box2DSrc/dynamics/b2_distance_joint.cpp \
    $$box2DSrc/dynamics/b2_edge_circle_contact.cpp \
    $$box2DSrc/dynamics/b2_edge_polygon_contact.cpp \
    $$box2DSrc/dynamics/b2_fixture.cpp \
    $$box2DSrc/dynamics/b2_friction_joint.cpp \
    $$box2DSrc/dynamics/b2_gear_joint.cpp \
    $$box2DSrc/dynamics/b2_island.cpp \
    $$box2DSrc/dynamics/b2_joint.cpp \
    $$box2DSrc/dynamics/b2_motor_joint.cpp \
    $$box2DSrc/dynamics/b2_mouse_joint.cpp \
    $$box2DSrc/dynamics/b2_polygon_circle_contact.cpp \
    $$box2DSrc/dynamics/b2_polygon_contact.cpp \
    $$box2DSrc/dynamics/b2_prismatic_joint.cpp \
    $$box2DSrc/dynamics/b2_pulley_joint.cpp \
    $$box2DSrc/dynamics/b2_revolute_joint.cpp \
    $$box2DSrc/dynamics/b2_weld_joint.cpp \
    $$box2DSrc/dynamics/b2_wheel_joint.cpp \
    $$box2DSrc/dynamics/b2_world.cpp \
    $$box2DSrc/dynamics/b2_world_callbacks.cpp \
    $$box2DSrc/collision/b2_broad_phase.cpp \
    $$box2DSrc/collision/b2_chain_shape.cpp \
    $$box2DSrc/collision/b2_circle_shape.cpp \
    $$box2DSrc/collision/b2_collide_circle.cpp \
    $$box2DSrc/collision/b2_collide_edge.cpp \
    $$box2DSrc/collision/b2_collide_polygon.cpp \
    $$box2DSrc/collision/b2_collision.cpp \
    $$box2DSrc/collision/b2_distance.cpp \
    $$box2DSrc/collision/b2_dynamic_tree.cpp \
    $$box2DSrc/collision/b2_edge_shape.cpp \
    $$box2DSrc/collision/b2_polygon_shape.cpp \
    $$box2DSrc/collision/b2_time_of_impact.cpp \
    $$box2DSrc/common/b2_block_allocator.cpp \
    $$box2DSrc/common/b2_draw.cpp \
    $$box2DSrc/common/b2_math.cpp \
    $$box2DSrc/common/b2_settings.cpp \
    $$box2DSrc/common/b2_stack_allocator.cpp \
    $$box2DSrc/common/b2_timer.cpp


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
