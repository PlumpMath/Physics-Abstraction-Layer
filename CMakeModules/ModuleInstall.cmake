# INSTALL commands, borrowed from OSG's ModuleInstall

# Required Vars:
# ${LIB_NAME}
# ${LIB_PUBLIC_HEADERS}

SET(INSTALL_INCDIR include)
IF(WIN32)
    SET(INSTALL_BINDIR bin/${SYSTEM_AOL}/\${CMAKE_INSTALL_CONFIG_NAME})
    SET(INSTALL_LIBDIR bin/${SYSTEM_AOL}/\${CMAKE_INSTALL_CONFIG_NAME})
    SET(INSTALL_ARCHIVEDIR lib/${SYSTEM_AOL}/\${CMAKE_INSTALL_CONFIG_NAME})
ELSE()
    SET(INSTALL_BINDIR bin/${SYSTEM_AOL})
    SET(INSTALL_LIBDIR lib${LIB_POSTFIX}/${SYSTEM_AOL})
    SET(INSTALL_ARCHIVEDIR lib${LIB_POSTFIX}/${SYSTEM_AOL})
ENDIF()

INSTALL(
    TARGETS ${LIB_NAME}
    RUNTIME DESTINATION ${INSTALL_BINDIR} COMPONENT libpal
    LIBRARY DESTINATION ${INSTALL_LIBDIR} COMPONENT libpal
    ARCHIVE DESTINATION ${INSTALL_ARCHIVEDIR} COMPONENT libpal-dev
)

# Separately define install rules for headers since they're not in the same dir
INSTALL(
    FILES ${HEADERS_BASE}
    DESTINATION ${INSTALL_INCDIR}/pal/${HEADERS_BASE_DIR_NAME}
    COMPONENT libpal-dev
)
INSTALL(
    FILES ${HEADERS_FRAMEWORK}
    DESTINATION ${INSTALL_INCDIR}/pal/${HEADERS_FRAMEWORK_DIR_NAME}
    COMPONENT libpal-dev
)
INSTALL(
    FILES ${HEADERS_IMPL}
    DESTINATION ${INSTALL_INCDIR}/pal/${HEADERS_IMPL_DIR_NAME}
    COMPONENT libpal-dev
)
