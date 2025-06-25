cmake_minimum_required(VERSION 3.3)

project (uUtils)

if( CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT )
  message(STATUS "Setting default CMAKE_INSTALL_PREFIX path to ../")
  set(CMAKE_INSTALL_PREFIX "../" CACHE STRING "The path to use for make install" FORCE)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TEST_INI_FILE sources/testapps/test_iniparser/src/test.ini)
set(TESTEX_INI_FILE sources/testapps/test_iniparser/src/testex.ini)

SET(INSTALL_WIN_APP_DIR      "bin/windows")
SET(INSTALL_LINUX_APP_DIR    "bin/linux")

if(MSVC OR MSYS OR MINGW)
    SET(INSTALL_DIR     ${INSTALL_WIN_APP_DIR})
else()
    SET(INSTALL_DIR     ${INSTALL_LINUX_APP_DIR})
endif()

add_subdirectory(sources)

install ( TARGETS test_hexdumper            DESTINATION ${INSTALL_DIR} )
install ( TARGETS test_hexlify              DESTINATION ${INSTALL_DIR} )
install ( TARGETS test_numeric              DESTINATION ${INSTALL_DIR} )
install ( TARGETS test_string               DESTINATION ${INSTALL_DIR} )
install ( TARGETS test_flagparser           DESTINATION ${INSTALL_DIR} )
install ( TARGETS test_pluginloader         DESTINATION ${INSTALL_DIR} )
install ( TARGETS test_iniparser            DESTINATION ${INSTALL_DIR} )
install ( TARGETS test_iniparserex          DESTINATION ${INSTALL_DIR} )
install ( TARGETS test_boolexprparser       DESTINATION ${INSTALL_DIR} )
install ( TARGETS test_boolexprparser       DESTINATION ${INSTALL_DIR} )
install ( TARGETS test_boolexprparserthrow  DESTINATION ${INSTALL_DIR} )
install ( TARGETS test_calculator           DESTINATION ${INSTALL_DIR} )
install ( TARGETS test_fileviewer           DESTINATION ${INSTALL_DIR} )
install ( TARGETS test_filelister           DESTINATION ${INSTALL_DIR} )
install ( TARGETS calculator                DESTINATION ${INSTALL_DIR} )


install(FILES ${TEST_INI_FILE} DESTINATION ${INSTALL_DIR})
install(FILES ${TESTEX_INI_FILE} DESTINATION ${INSTALL_DIR})
