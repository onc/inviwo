#--------------------------------------------------------------------
# Inviwo discrete data Module
ivw_module(DiscreteData)

#--------------------------------------------------------------------
# Add header files
set(HEADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/analyticchannel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/bufferchannel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/channeliterator.h
    ${CMAKE_CURRENT_SOURCE_DIR}/channeliterator.inl
    ${CMAKE_CURRENT_SOURCE_DIR}/connectioniterator.h
    ${CMAKE_CURRENT_SOURCE_DIR}/connectionmap.h
    ${CMAKE_CURRENT_SOURCE_DIR}/connectivity.h
    ${CMAKE_CURRENT_SOURCE_DIR}/datachannel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/datachannel.inl
    ${CMAKE_CURRENT_SOURCE_DIR}/dataset.h
    ${CMAKE_CURRENT_SOURCE_DIR}/dataset.inl
    ${CMAKE_CURRENT_SOURCE_DIR}/elementiterator.h
    ${CMAKE_CURRENT_SOURCE_DIR}/explicitconnectivity.h
    ${CMAKE_CURRENT_SOURCE_DIR}/simplexconnectivity.h
    ${CMAKE_CURRENT_SOURCE_DIR}/structuredgrid.h
    ${CMAKE_CURRENT_SOURCE_DIR}/util.h
)
#~ ivw_group("Header Files" ${HEADER_FILES})

#--------------------------------------------------------------------
# Add source files
set(SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/connectioniterator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/connectionmap.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/connectivity.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/datachannel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/dataset.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/elementiterator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/explicitconnectivity.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/simplexconnectivity.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/structuredgrid.cpp
)
ivw_group("Sources" ${SOURCE_FILES} ${HEADER_FILES})


#--------------------------------------------------------------------
## Add shaders
#set(SHADER_FILES
#)
#ivw_group("Shader Files" ${SHADER_FILES})


#--------------------------------------------------------------------
# Add Unittests
set(TEST_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/unittests/data-unittest-main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/unittests/data-test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/unittests/dataset-test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/unittests/data-access-test.cpp
)
ivw_add_unittest(${TEST_FILES})

#--------------------------------------------------------------------
# Create module
ivw_create_module(${SOURCE_FILES} ${HEADER_FILES})

#--------------------------------------------------------------------
# Add shader directory to pack
# ivw_add_to_module_pack(${CMAKE_CURRENT_SOURCE_DIR}/glsl)
