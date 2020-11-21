set(BUILD_SHARED_LIBS OFF)
set(BUILD_TESTING OFF)

#--------------------------------
# OpenSSL
#--------------------------------

if(NOT TARGET ssl)
    if(MINGW AND UNIX)
        set(CROSS=ON)
        set(CROSS_TARGET=mingw)
    endif()
    set(BUILD_OPENSSL=ON)
    set(OPENSSL_BRANCH=OpenSSL_1_1_0g)
    set(SYSTEM_OPENSSL=OFF)

    add_subdirectory(openssl)
endif()
