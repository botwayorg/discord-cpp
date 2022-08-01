cmake_minimum_required (VERSION 3.6)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(BOT_NAME "bwbot")

project(${BOT_NAME})
aux_source_directory("src" coresrc)
add_executable(${BOT_NAME} ${coresrc})

string(ASCII 27 Esc)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set_target_properties(${BOT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)
find_package(DPP)
if(APPLE)
	if(CMAKE_APPLE_SILICON_PROCESSOR)
		set(OPENSSL_ROOT_DIR "/opt/homebrew/opt/openssl")
	else()
		set(OPENSSL_ROOT_DIR "/usr/local/opt/openssl")
	endif()
	find_package(OpenSSL REQUIRED)
else()
	find_package(OpenSSL REQUIRED)
endif()

target_include_directories(${BOT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${OPENSSL_INCLUDE_DIR}
)

target_link_libraries(${BOT_NAME}
    dl
    ${CMAKE_THREAD_LIBS_INIT}
    ${OPENSSL_CRYPTO_LIBRARY} 
    ${OPENSSL_SSL_LIBRARY}
)

if (DPP_FOUND)
    target_link_libraries(${BOT_NAME} ${DPP_LIBRARIES})
    target_include_directories(${BOT_NAME} PUBLIC ${DPP_INCLUDE_DIR})
else()
    if (APPLE)
        message(WARNING "Could not find DPP install. run `curl -sL https://bit.ly/dpp-osx | bash` command")
    elseif (UNIX)
        message(WARNING "Could not find DPP install. run `curl -sL https://bit.ly/dpp-linux | bash` command")
    elseif (WIN32)
        message(WARNING "Could not find DPP install. run `irm https://bit.ly/dpp-win | iex` command")
    else()
        message(WARNING "Could not find DPP install. try building it from source")
    endif()
endif()
