# 查找当前目录下的所有源文件
aux_source_directory(./ DIR_SOURCE_SRCS)
aux_source_directory(./controller/ DIR_CONTROLLER_SRCS)

# 指定生成目标
add_executable(${GLOB_EXECNAME} 
                    ${DIR_SOURCE_SRCS} 
                    ${DIR_CONTROLLER_SRCS}
                )

# 链接库文件
target_link_libraries(${GLOB_EXECNAME} ${GLOB_FILE_LIBS})
