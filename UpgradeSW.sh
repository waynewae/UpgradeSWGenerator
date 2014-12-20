adb reboot bootloader
fastboot -i 0x489 flash partition good/god/VNA-0-1560-gpt_both0.bin
fastboot -i 0x489 flash sbl1 good/god/VNA-0-1560-sbl1.mbn
fastboot -i 0x489 flash aboot good/god/VNA-0-1560-emmc_appsboot.mbn
fastboot -i 0x489 flash rpm good/god/VNA-0-1560-rpm.mbn
fastboot -i 0x489 flash tz good/god/VNA-0-1560-tz.mbn
fastboot -i 0x489 flash hwcfg good/god/VNA-0-1560-hwcfg.img
fastboot -i 0x489 flash dbi good/god/VNA-0-1560-sdi.mbn
fastboot -i 0x489 flash splash good/god/VNA-00WW-043-splash.img
fastboot -i 0x489 flash multisplash good/god/VNA-00WW-043-multi-splash.img
fastboot -i 0x489 erase DDR
fastboot -i 0x489 reboot-bootloader
fastboot -i 0x489 flash boot good/god/VNA-0-1560-0002-boot.img
fastboot -i 0x489 flash recovery good/god/VNA-0-1560-0002-recovery.img
fastboot -i 0x489 flash persist good/god/VNA-0-1560-0001-persist.img
fastboot -i 0x489 flash ftmboot good/god/VNA-0-2010-ftmboot.img
fastboot -i 0x489 flash ftmsys good/god/VNA-0-2010-ftmsys.img
fastboot -i 0x489 flash cda good/god/VNA-00WW-043-cda.img
fastboot -i 0x489 flash hidden good/god/VNA-0-0010-0001-hidden.img.ext4
fastboot -i 0x489 flash modem good/god/VNA-0-1560-NON-HLOS.bin
fastboot -i 0x489 flash system good/god/VNA-0-1560-0002-system.img
fastboot -i 0x489 flash systeminfo good/god/fver
fastboot -i 0x489 flash sutinfo good/god/VNA-00WW-001-sutinfo.img
fastboot -i 0x489 flash cust_nv good/god/VNA-039-NV_cust.mbn
fastboot -i 0x489 erase userdata
fastboot -i 0x489 erase cache
fastboot -i 0x489 reboot
