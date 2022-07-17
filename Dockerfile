FROM alpine:latest
RUN apk add --no-cache clang cmake grub grub-dev grub-bios grub-efi xorriso bash lld ninja gdb alpine-sdk qemu qemu-system-x86_64 qemu-ui-gtk qemu-img ovmf mtools
RUN cp /usr/share/OVMF/OVMF_VARS.fd /tmp/QEMU_VARS.fd
USER root
ENTRYPOINT ["/bin/sh"]
