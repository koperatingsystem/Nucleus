# SPDX-License-Identifier: MIT

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/staging)

find_program(XORRISO_PATH xorriso REQUIRED)
find_program(GRUBMKRESCUE_PATH grub-mkrescue REQUIRED)

add_custom_target(
        build-iso
        ${GRUBMKRESCUE_PATH} -o boot.iso -v ${CMAKE_BINARY_DIR}/staging
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        DEPENDS ../Shared/grub.cfg
        COMMENT "Building a boot ISO"
)

function(add_file_iso file target)
    file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/staging/${target})
    file(COPY ${file} DESTINATION ${CMAKE_BINARY_DIR}/staging/${target})
endfunction()

function(add_target_output_iso target target_dir)
    add_custom_command(
            TARGET ${target} POST_BUILD VERBATIM
            COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:${target}>" ${CMAKE_BINARY_DIR}/staging/${target_dir}
    )

    add_dependencies(build-iso ${target})
endfunction()
