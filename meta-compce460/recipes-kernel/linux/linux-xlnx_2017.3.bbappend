PV := "${PV}-rt"

FILESEXTRAPATHS_prepend := "${THISDIR}/linux-xlnx:"

SRC_URI_append_pynq = " \
        file://rt.cfg;sha256sum=65a5bb77ce6063c436507023b3ce0982556fae029c4edd0358e1ce421d265895 \
	https://mirrors.edge.kernel.org/pub/linux/kernel/projects/rt/4.9/patch-4.9.327-rt197.patch.xz;sha256sum=3bb34a9088a4b21080293364b03af809a991091adaa67112662ab45d831f7bda \
        "

