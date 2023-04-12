set (COMPONENT_SRCS "ham_bo_sung.c")
set (COMPONENT_INCLUDEDIRS "include")
idf_component_register(SRCS ${COMPONENT_SRCS}
                    INCLUDE_DIRS ${COMPONENT_INCLUDEDIRS})