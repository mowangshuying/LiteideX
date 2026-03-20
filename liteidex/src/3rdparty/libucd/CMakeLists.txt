cmake_minimum_required(VERSION 3.10)

# Set target name
set(TGT libucd)

# Create static library
add_library(${TGT} STATIC
    # Source files
    src/CharDistribution.cpp
    src/JpCntx.cpp
    src/LangBulgarianModel.cpp
    src/LangCyrillicModel.cpp
    src/LangCzechModel.cpp
    src/LangFinnishModel.cpp
    src/LangFrenchModel.cpp
    src/LangGermanModel.cpp
    src/LangGreekModel.cpp
    src/LangHebrewModel.cpp
    src/LangHungarianModel.cpp
    src/LangPolishModel.cpp
    src/LangSpanishModel.cpp
    src/LangSwedishModel.cpp
    src/LangThaiModel.cpp
    src/LangTurkishModel.cpp
    src/nsBig5Prober.cpp
    src/nsCharSetProber.cpp
    src/nsEscCharsetProber.cpp
    src/nsEscSM.cpp
    src/nsEUCJPProber.cpp
    src/nsEUCKRProber.cpp
    src/nsEUCTWProber.cpp
    src/nsGB2312Prober.cpp
    src/nsHebrewProber.cpp
    src/nsLatin1Prober.cpp
    src/nsMBCSGroupProber.cpp
    src/nsMBCSSM.cpp
    src/nsSBCharSetProber.cpp
    src/nsSBCSGroupProber.cpp
    src/nsSJISProber.cpp
    src/nsUniversalDetector.cpp
    src/nsUTF8Prober.cpp
    src/ucdapi.cpp
    
    # Header files (for IDE recognition)
    src/CharDistribution.h
    src/JpCntx.h
    src/nsBig5Prober.h
    src/nsCharSetProber.h
    src/nsCodingStateMachine.h
    src/nscore.h
    src/nsDebug.h
    src/nsEscCharsetProber.h
    src/nsEUCJPProber.h
    src/nsEUCKRProber.h
    src/nsEUCTWProber.h
    src/nsGB2312Prober.h
    src/nsHebrewProber.h
    src/nsLatin1Prober.h
    src/nsMBCSGroupProber.h
    src/nsPkgInt.h
    src/nsSBCharSetProber.h
    src/nsSBCSGroupProber.h
    src/nsSJISProber.h
    src/nsUniversalDetector.h
    src/nsUTF8Prober.h
    src/prmem.h
    include/libucd.h
)

# Include common configuration
#include(../../liteideutils.cmake)

# Set header include paths
target_include_directories(${TGT} PUBLIC
   ./
   ./include
   ./src
)

# Link dependencies (no find_package)
target_link_libraries(${TGT} PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)

# Install configuration (optional)
#install(TARGETS ${TGT}
#    ARCHIVE DESTINATION lib
#    LIBRARY DESTINATION lib
#)

#install(FILES
#    include/libucd.h
#    DESTINATION include/libucd
#)

# Distribute data files (optional, equivalent to DISTFILES)
#install(FILES
#    src/Big5Freq.tab
#    src/EUCKRFreq.tab
#    src/EUCTWFreq.tab
#    src/GB2312Freq.tab
#    src/JISFreq.tab
#    DESTINATION share/libucd
#)