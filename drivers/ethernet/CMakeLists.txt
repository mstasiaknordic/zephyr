# SPDX-License-Identifier: Apache-2.0

zephyr_library()
zephyr_library_property(ALLOW_EMPTY TRUE)
zephyr_library_include_directories(${ZEPHYR_BASE}/subsys/net/l2)

zephyr_library_sources_ifdef(CONFIG_ETH_DRIVER_RAW_MODE
  eth_raw.c
  )

zephyr_library_sources_ifdef(CONFIG_ETH_GECKO
	eth_gecko.c
	phy_gecko.c
	)

zephyr_library_sources_ifdef(CONFIG_ETH_XLNX_GEM
	eth_xlnx_gem.c
	phy_xlnx_gem.c
	)

zephyr_library_sources_ifdef(CONFIG_ETH_DWMAC		eth_dwmac.c)
zephyr_library_sources_ifdef(CONFIG_ETH_DWMAC_STM32H7X	eth_dwmac_stm32h7x.c)
zephyr_library_sources_ifdef(CONFIG_ETH_DWMAC_MMU	eth_dwmac_mmu.c)

zephyr_library_sources_ifdef(CONFIG_ETH_E1000		eth_e1000.c)
zephyr_library_sources_ifdef(CONFIG_ETH_ENC28J60	eth_enc28j60.c)
zephyr_library_sources_ifdef(CONFIG_ETH_ENC424J600	eth_enc424j600.c)
zephyr_library_sources_ifdef(CONFIG_ETH_ESP32		eth_esp32.c)
zephyr_library_sources_ifdef(CONFIG_ETH_LITEX_LITEETH	eth_litex_liteeth.c)
zephyr_library_sources_ifdef(CONFIG_ETH_SMSC911X	eth_smsc911x.c)
zephyr_library_sources_ifdef(CONFIG_ETH_STELLARIS	eth_stellaris.c)
zephyr_library_sources_ifdef(CONFIG_ETH_STM32_HAL	eth_stm32_hal.c)
zephyr_library_sources_ifdef(CONFIG_ETH_W5500		eth_w5500.c)
zephyr_library_sources_ifdef(CONFIG_ETH_SAM_GMAC	eth_sam_gmac.c)
zephyr_library_sources_ifdef(CONFIG_ETH_CYCLONEV	eth_cyclonev.c)
zephyr_library_sources_ifdef(CONFIG_SLIP_TAP		eth_slip_tap.c)
zephyr_library_sources_ifdef(CONFIG_ETH_SMSC91X		eth_smsc91x.c)
zephyr_library_sources_ifdef(CONFIG_ETH_IVSHMEM 	eth_ivshmem.c eth_ivshmem_queue.c)
zephyr_library_sources_ifdef(CONFIG_ETH_ADIN2111	eth_adin2111.c)
zephyr_library_sources_ifdef(CONFIG_ETH_LAN865X	        eth_lan865x.c oa_tc6.c)
zephyr_library_sources_ifdef(CONFIG_ETH_XMC4XXX		eth_xmc4xxx.c)
zephyr_library_sources_ifdef(CONFIG_ETH_TEST		eth_test.c)
zephyr_library_sources_ifdef(CONFIG_ETH_RENESAS_RA	eth_renesas_ra.c)
zephyr_library_sources_ifdef(CONFIG_ETH_LAN9250		eth_lan9250.c)
zephyr_library_sources_ifdef(CONFIG_ETH_SY1XX		eth_sensry_sy1xx_mac.c)
zephyr_library_sources_ifdef(CONFIG_ETH_NXP_ENET	eth_nxp_enet.c)
zephyr_library_sources_ifdef(CONFIG_ETH_XILINX_AXIENET	eth_xilinx_axienet.c)

if(CONFIG_ETH_NXP_S32_NETC)
  zephyr_library_sources(eth_nxp_s32_netc.c)
  zephyr_library_sources_ifdef(CONFIG_DT_HAS_NXP_S32_NETC_PSI_ENABLED	eth_nxp_s32_netc_psi.c)
  zephyr_library_sources_ifdef(CONFIG_DT_HAS_NXP_S32_NETC_VSI_ENABLED	eth_nxp_s32_netc_vsi.c)
endif()

zephyr_library_sources_ifdef(CONFIG_ETH_NXP_S32_GMAC	eth_nxp_s32_gmac.c)
zephyr_library_sources_ifdef(CONFIG_ETH_NUMAKER		eth_numaker.c)

if(CONFIG_ETH_NATIVE_TAP)
  zephyr_library_sources(eth_native_tap.c)
  target_sources(native_simulator INTERFACE eth_native_tap_adapt.c)
endif()

add_subdirectory(dsa)
add_subdirectory(phy)
add_subdirectory(eth_nxp_enet_qos)
add_subdirectory(nxp_imx_netc)
add_subdirectory(dwc_xgmac)
add_subdirectory(intel)
