SET(ICON_RES resources.qrc)
qt5_add_resources(ICON_RES_RCC ${ICON_RES})

add_custom_target(icons ALL DEPENDS ${ICON_RES_RCC})

SET(kimageannotator_ICON_RES_RCC ${ICON_RES_RCC} PARENT_SCOPE)
