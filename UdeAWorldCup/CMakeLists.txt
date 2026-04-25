cmake_minimum_required(VERSION 3.16)

project(UdeAWorldCup LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(UdeAWorldCup main.cpp
    Lista.h
    equipo.h
    equipo.cpp
    fecha.h
    fecha.cpp
    grupo.h
    grupo.cpp
    jugador.h
    jugador.cpp
    partido.h
    partido.cpp
    recursos.h
    recursos.cpp
    registrojugadorpartido.h
    registrojugadorpartido.cpp
    torneo.h
    torneo.cpp

)

include(GNUInstallDirs)
install(TARGETS UdeAWorldCup
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
