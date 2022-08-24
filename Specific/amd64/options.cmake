set(SHARED_COMPILE_OPTIONS ${SHARED_COMPILE_OPTIONS} -m64 -mcmodel=large -mno-red-zone -mno-sse -mno-mmx -Wall -Werror -ffreestanding)
set(SHARED_LINK_OPTIONS ${SHARED_LINK_OPTIONS} -nostdlib)

set(KERNEL_ADDITIONAL_FILES ${KERNEL_ADDITIONAL_FILES} ${CMAKE_SOURCE_DIR}/Specific/amd64/Shared/Magic.S ${CMAKE_SOURCE_DIR}/Specific/amd64/Shared/Bootstrap.S)

set(KERNEL_COMPILE_OPTIONS ${SHARED_COMPILE_OPTIONS} ${KERNEL_COMPILE_OPTIONS})
set(LIBC_COMPILE_OPTIONS ${SHARED_COMPILE_OPTIONS} ${LIBC_COMPILE_OPTIONS} -nostdinc)
set(LIBC_LOADER_COMPILE_OPTIONS ${SHARED_COMPILE_OPTIONS} ${LIBC_LOADER_COMPILE_OPTIONS} -m32 -target i686-unknown-none)

set(KERNEL_LINK_OPTIONS ${SHARED_LINK_OPTIONS} ${KERNEL_LINK_OPTIONS} -T ${CMAKE_SOURCE_DIR}/Specific/amd64/Shared/link.ld -z max-page-size=0x1000)
set(LIBC_LINK_OPTIONS ${SHARED_LINK_OPTIONS} ${LIBC_LINK_OPTIONS})
set(LIBC_LOADER_LINK_OPTIONS ${SHARED_LINK_OPTIONS} ${LIBC_LOADER_LINK_OPTIONS})

set(KERNEL_LINK_DEPENDS ${CMAKE_SOURCE_DIR}/Specific/amd64/Shared/link.ld)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_LIST_DIR}/kos-toolchain.cmake)
