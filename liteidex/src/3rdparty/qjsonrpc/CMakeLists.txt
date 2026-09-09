# Set version
set(QJSONRPC_VERSION 1.1.0)

set(TGT qjsonrpc)

set(HEADERS
	src/http-parser/http_parser.h
	src/qjsonrpcservice_p.h
	src/qjsonrpcsocket_p.h
	src/qjsonrpcabstractserver_p.h
	src/qjsonrpcservicereply_p.h
	src/qjsonrpchttpserver_p.h
	src/qjsonrpcmessage.h
    src/qjsonrpcservice.h
    src/qjsonrpcsocket.h
    src/qjsonrpcserviceprovider.h
    src/qjsonrpcabstractserver.h
    src/qjsonrpclocalserver.h
    src/qjsonrpctcpserver.h
    src/qjsonrpcglobal.h
    src/qjsonrpcservicereply.h
    src/qjsonrpchttpclient.h
    src/qjsonrpchttpserver.h
    src/qjsonrpcmetatype.h
)

set (SOURCES
    src/http-parser/http_parser.c
    src/qjsonrpcmessage.cpp
    src/qjsonrpcservice.cpp
    src/qjsonrpcsocket.cpp
    src/qjsonrpcserviceprovider.cpp
    src/qjsonrpcabstractserver.cpp
    src/qjsonrpclocalserver.cpp
    src/qjsonrpctcpserver.cpp
    src/qjsonrpcservicereply.cpp
    src/qjsonrpchttpclient.cpp
    src/qjsonrpchttpserver.cpp
)

add_library(${TGT} STATIC ${HEADERS} ${SOURCES})

target_include_directories(${TGT} PUBLIC 
    ./src
    ./src/http-parser
    ../
)

target_link_libraries(${TGT} PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Network
    ${QT5_COMPAT_LIB}
)

# Headers include <private/qobject_p.h>; Qt6 requires the CorePrivate module target.
if(QT_VERSION_MAJOR EQUAL 6)
    target_link_libraries(${TGT} PUBLIC Qt6::CorePrivate)
endif()

### set marco QJSONRPC_STATIC
target_compile_definitions(${TGT} PUBLIC QJSONRPC_STATIC)
