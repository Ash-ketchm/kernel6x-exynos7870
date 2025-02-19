// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (C) 2015 Samsung Electronics Co., Ltd.
 * Copyright (C) 2024 ???
 *
 * Device Tree binding constants for Exynos7870 clock controller.
 */

#ifndef _DT_BINDINGS_CLOCK_EXYNOS_7870_H
#define _DT_BINDINGS_CLOCK_EXYNOS_7870_H

/* CMU_MIF */
#define CLK_FOUT_BUS_PLL							1
#define CLK_FOUT_MEDIA_PLL							2
#define CLK_FOUT_MEM_PLL							3
#define CLK_DOUT_CLKCMU_DISPAUD_BUS						4
#define CLK_DOUT_CLKCMU_DISPAUD_DECON_INT_ECLK					5
#define CLK_DOUT_CLKCMU_DISPAUD_DECON_INT_VCLK					6
#define CLK_DOUT_CLKCMU_FSYS_BUS						7
#define CLK_DOUT_CLKCMU_FSYS_MMC0						8
#define CLK_DOUT_CLKCMU_FSYS_MMC1						9
#define CLK_DOUT_CLKCMU_FSYS_MMC2						10
#define CLK_DOUT_CLKCMU_FSYS_USB20DRD_REFCLK					11
#define CLK_DOUT_CLKCMU_G3D_SWITCH						12
#define CLK_DOUT_CLKCMU_ISP_CAM							13
#define CLK_DOUT_CLKCMU_ISP_ISP							14
#define CLK_DOUT_CLKCMU_ISP_SENSOR0						15
#define CLK_DOUT_CLKCMU_ISP_SENSOR1						16
#define CLK_DOUT_CLKCMU_ISP_SENSOR2						17
#define CLK_DOUT_CLKCMU_ISP_VRA							18
#define CLK_DOUT_CLKCMU_MFCMSCL_MFC						19
#define CLK_DOUT_CLKCMU_MFCMSCL_MSCL						20
#define CLK_DOUT_CLKCMU_PERI_BUS						21
#define CLK_DOUT_CLKCMU_PERI_SPI_ESE						22
#define CLK_DOUT_CLKCMU_PERI_SPI_FRONTFROM					23
#define CLK_DOUT_CLKCMU_PERI_SPI_REARFROM					24
#define CLK_DOUT_CLKCMU_PERI_SPI_SENSORHUB					25
#define CLK_DOUT_CLKCMU_PERI_SPI_VOICEPROCESSOR					26
#define CLK_DOUT_CLKCMU_PERI_UART_BTWIFIFM					27
#define CLK_DOUT_CLKCMU_PERI_UART_DEBUG						28
#define CLK_DOUT_CLKCMU_PERI_UART_SENSOR					29
#define CLK_DOUT_CLK_MIF_APB							30
#define CLK_DOUT_CLK_MIF_BUSD							31
#define CLK_DOUT_CLK_MIF_HSI2C							32
#define CLK_FFAC_MUX_BUS_PLL_DIV2						33
#define CLK_FFAC_MUX_MEDIA_PLL_DIV2						34
#define CLK_FFAC_MUX_MEM_PLL_DIV2						35
#define CLK_GOUT_CLKCMU_DISPAUD_BUS						36
#define CLK_GOUT_CLKCMU_DISPAUD_DECON_INT_ECLK					37
#define CLK_GOUT_CLKCMU_DISPAUD_DECON_INT_VCLK					38
#define CLK_GOUT_CLKCMU_FSYS_BUS						39
#define CLK_GOUT_CLKCMU_FSYS_MMC0						40
#define CLK_GOUT_CLKCMU_FSYS_MMC1						41
#define CLK_GOUT_CLKCMU_FSYS_MMC2						42
#define CLK_GOUT_CLKCMU_FSYS_USB20DRD_REFCLK					43
#define CLK_GOUT_CLKCMU_G3D_SWITCH						44
#define CLK_GOUT_CLKCMU_ISP_CAM							45
#define CLK_GOUT_CLKCMU_ISP_ISP							46
#define CLK_GOUT_CLKCMU_ISP_SENSOR0						47
#define CLK_GOUT_CLKCMU_ISP_SENSOR1						48
#define CLK_GOUT_CLKCMU_ISP_SENSOR2						49
#define CLK_GOUT_CLKCMU_ISP_VRA							50
#define CLK_GOUT_CLKCMU_MFCMSCL_MFC						51
#define CLK_GOUT_CLKCMU_MFCMSCL_MSCL						52
#define CLK_GOUT_CLKCMU_PERI_BUS						53
#define CLK_GOUT_CLKCMU_PERI_SPI_ESE						54
#define CLK_GOUT_CLKCMU_PERI_SPI_FRONTFROM					55
#define CLK_GOUT_CLKCMU_PERI_SPI_REARFROM					56
#define CLK_GOUT_CLKCMU_PERI_SPI_SENSORHUB					57
#define CLK_GOUT_CLKCMU_PERI_SPI_VOICEPROCESSOR					58
#define CLK_GOUT_CLKCMU_PERI_UART_BTWIFIFM					59
#define CLK_GOUT_CLKCMU_PERI_UART_DEBUG						60
#define CLK_GOUT_CLKCMU_PERI_UART_SENSOR					61
#define CLK_GOUT_CLK_MIF_UID_ASYNCAPB_HSI2C_AP_IPCLKPORT_PCLKM			62
#define CLK_GOUT_CLK_MIF_UID_ASYNCAPB_HSI2C_AP_IPCLKPORT_PCLKS			63
#define CLK_GOUT_CLK_MIF_UID_ASYNCAPB_HSI2C_CP_IPCLKPORT_PCLKM			64
#define CLK_GOUT_CLK_MIF_UID_ASYNCAPB_HSI2C_CP_IPCLKPORT_PCLKS			65
#define CLK_GOUT_CLK_MIF_UID_HSI2C_MIF_IPCLKPORT_IPCLK				66
#define CLK_GOUT_CLK_MIF_UID_HSI2C_MIF_IPCLKPORT_ITCLK				67
#define CLK_GOUT_CLK_MIF_UID_MODAPIF_V1P5_MIF_CP_IPCLKPORT_PCLK_HSI2C		68
#define CLK_GOUT_CLK_MIF_UID_MODAPIF_V1P5_MIF_CP_IPCLKPORT_PCLK_HSI2C_BAT_0	69
#define CLK_GOUT_CLK_MIF_UID_MODAPIF_V1P5_MIF_CP_IPCLKPORT_PCLK_HSI2C_BAT_1	70
#define CLK_GOUT_CLK_MIF_UID_WRAP_ADC_IF_IPCLKPORT_I_OSC_SYS			71
#define CLK_GOUT_CLK_MIF_UID_WRAP_ADC_IF_IPCLKPORT_PCLK_S0			72
#define CLK_GOUT_CLK_MIF_UID_WRAP_ADC_IF_IPCLKPORT_PCLK_S1			73
#define CLK_GOUT_MUXGATE_BUS_PLL						74
#define CLK_GOUT_MUXGATE_CLKCMU_DISPAUD_BUS					75
#define CLK_GOUT_MUXGATE_CLKCMU_DISPAUD_DECON_INT_ECLK				76
#define CLK_GOUT_MUXGATE_CLKCMU_DISPAUD_DECON_INT_VCLK				77
#define CLK_GOUT_MUXGATE_CLKCMU_FSYS_BUS					78
#define CLK_GOUT_MUXGATE_CLKCMU_FSYS_MMC0					79
#define CLK_GOUT_MUXGATE_CLKCMU_FSYS_MMC1					80
#define CLK_GOUT_MUXGATE_CLKCMU_FSYS_MMC2					81
#define CLK_GOUT_MUXGATE_CLKCMU_FSYS_USB20DRD_REFCLK				82
#define CLK_GOUT_MUXGATE_CLKCMU_ISP_CAM						83
#define CLK_GOUT_MUXGATE_CLKCMU_ISP_ISP						84
#define CLK_GOUT_MUXGATE_CLKCMU_ISP_SENSOR0					85
#define CLK_GOUT_MUXGATE_CLKCMU_ISP_SENSOR1					86
#define CLK_GOUT_MUXGATE_CLKCMU_ISP_SENSOR2					87
#define CLK_GOUT_MUXGATE_CLKCMU_ISP_VRA						88
#define CLK_GOUT_MUXGATE_CLKCMU_MFCMSCL_MFC					89
#define CLK_GOUT_MUXGATE_CLKCMU_MFCMSCL_MSCL					90
#define CLK_GOUT_MUXGATE_CLKCMU_PERI_BUS					91
#define CLK_GOUT_MUXGATE_CLKCMU_PERI_SPI_ESE					92
#define CLK_GOUT_MUXGATE_CLKCMU_PERI_SPI_FRONTFROM				93
#define CLK_GOUT_MUXGATE_CLKCMU_PERI_SPI_REARFROM				94
#define CLK_GOUT_MUXGATE_CLKCMU_PERI_SPI_SENSORHUB				95
#define CLK_GOUT_MUXGATE_CLKCMU_PERI_SPI_VOICEPROCESSOR				96
#define CLK_GOUT_MUXGATE_CLKCMU_PERI_UART_BTWIFIFM				97
#define CLK_GOUT_MUXGATE_CLKCMU_PERI_UART_DEBUG					98
#define CLK_GOUT_MUXGATE_CLKCMU_PERI_UART_SENSOR				99
#define CLK_GOUT_MUXGATE_CLK_MIF_BUSD						100
#define CLK_GOUT_MUXGATE_MEDIA_PLL						101
#define CLK_GOUT_MUXGATE_MEM_PLL						102
#define CLK_MOUT_BUS_PLL							103
#define CLK_MOUT_CLKCMU_DISPAUD_BUS						104
#define CLK_MOUT_CLKCMU_DISPAUD_DECON_INT_ECLK					105
#define CLK_MOUT_CLKCMU_DISPAUD_DECON_INT_VCLK					106
#define CLK_MOUT_CLKCMU_FSYS_BUS						107
#define CLK_MOUT_CLKCMU_FSYS_MMC0						108
#define CLK_MOUT_CLKCMU_FSYS_MMC1						109
#define CLK_MOUT_CLKCMU_FSYS_MMC2						110
#define CLK_MOUT_CLKCMU_FSYS_USB20DRD_REFCLK					111
#define CLK_MOUT_CLKCMU_ISP_CAM							112
#define CLK_MOUT_CLKCMU_ISP_ISP							113
#define CLK_MOUT_CLKCMU_ISP_SENSOR0						114
#define CLK_MOUT_CLKCMU_ISP_SENSOR1						115
#define CLK_MOUT_CLKCMU_ISP_SENSOR2						116
#define CLK_MOUT_CLKCMU_ISP_VRA							117
#define CLK_MOUT_CLKCMU_MFCMSCL_MFC						118
#define CLK_MOUT_CLKCMU_MFCMSCL_MSCL						119
#define CLK_MOUT_CLKCMU_PERI_BUS						120
#define CLK_MOUT_CLKCMU_PERI_SPI_ESE						121
#define CLK_MOUT_CLKCMU_PERI_SPI_FRONTFROM					122
#define CLK_MOUT_CLKCMU_PERI_SPI_REARFROM					123
#define CLK_MOUT_CLKCMU_PERI_SPI_SENSORHUB					124
#define CLK_MOUT_CLKCMU_PERI_SPI_VOICEPROCESSOR					125
#define CLK_MOUT_CLKCMU_PERI_UART_BTWIFIFM					126
#define CLK_MOUT_CLKCMU_PERI_UART_DEBUG						127
#define CLK_MOUT_CLKCMU_PERI_UART_SENSOR					128
#define CLK_MOUT_CLK_MIF_BUSD							129
#define CLK_MOUT_MEDIA_PLL							130
#define CLK_MOUT_MEM_PLL							131
#define MIF_NR_CLK								132

/* PMU_ALIVE */
#define CLK_GOUT_PMU_DEBUG_CLKOUT_DISABLE	1
#define CLK_GOUT_PMU_DEBUG_CLKOUT_SEL08		2
#define CLK_GOUT_PMU_DEBUG_CLKOUT_SEL09		3
#define CLK_GOUT_PMU_DEBUG_CLKOUT_SEL10		4
#define CLK_GOUT_PMU_DEBUG_CLKOUT_SEL11		5
#define CLK_GOUT_PMU_DEBUG_CLKOUT_SEL12		6
#define PMU_ALIVE_NR_CLK			7

/* CMU_DISPAUD */
#define CLK_FOUT_AUD_PLL							1
#define CLK_DOUT_CLK_DISPAUD_APB						2
#define CLK_DOUT_CLK_DISPAUD_DECON_INT_ECLK					3
#define CLK_DOUT_CLK_DISPAUD_DECON_INT_VCLK					4
#define CLK_DOUT_CLK_DISPAUD_MI2S						5
#define CLK_DOUT_CLK_DISPAUD_MIXER						6
#define CLK_GOUT_CLK_DISPAUD_UID_CLKCMU_DISPAUD_BUS				7
#define CLK_GOUT_CLK_DISPAUD_UID_CLKCMU_DISPAUD_BUS_DISP			8
#define CLK_GOUT_CLK_DISPAUD_UID_CLKCMU_DISPAUD_BUS_PPMU			9
#define CLK_GOUT_CLK_DISPAUD_UID_CLK_DISPAUD_APB_AUD				10
#define CLK_GOUT_CLK_DISPAUD_UID_CLK_DISPAUD_APB_AUD_AMP			11
#define CLK_GOUT_CLK_DISPAUD_UID_CLK_DISPAUD_APB_DISP				12
#define CLK_GOUT_CLK_DISPAUD_UID_CON_DISPAUD_IPCLKPORT_I_AUD_I2S_BCLK_BT_IN	13
#define CLK_GOUT_CLK_DISPAUD_UID_CON_DISPAUD_IPCLKPORT_I_AUD_I2S_BCLK_FM_IN	14
#define CLK_GOUT_CLK_DISPAUD_UID_CON_DISPAUD_IPCLKPORT_I_CP2AUD_BCK		15
#define CLK_GOUT_CLK_DISPAUD_UID_CON_DISPAUD_IPCLKPORT_I_EXT2AUD_BCK_GPIO_I2S	16
#define CLK_GOUT_CLK_DISPAUD_UID_DECON_IPCLKPORT_I_ECLK				17
#define CLK_GOUT_CLK_DISPAUD_UID_DECON_IPCLKPORT_I_VCLK				18
#define CLK_GOUT_CLK_DISPAUD_UID_MI2S_AMP_IPCLKPORT_I2SCODCLKI			19
#define CLK_GOUT_CLK_DISPAUD_UID_MI2S_AUD_IPCLKPORT_I2SCODCLKI			20
#define CLK_GOUT_CLK_DISPAUD_UID_MIXER_AUD_IPCLKPORT_SYSCLK			21
#define CLK_GOUT_MUXGATE_AUD_PLL						22
#define CLK_GOUT_MUXGATE_CLKCMU_DISPAUD_BUS_USER				23
#define CLK_GOUT_MUXGATE_CLKCMU_DISPAUD_DECON_INT_ECLK_USER			24
#define CLK_GOUT_MUXGATE_CLKCMU_DISPAUD_DECON_INT_VCLK_USER			25
#define CLK_GOUT_MUXGATE_CLKPHY_DISPAUD_MIPIPHY_RXCLKESC0_USER			26
#define CLK_GOUT_MUXGATE_CLKPHY_DISPAUD_MIPIPHY_TXBYTECLKHS_USER		27
#define CLK_GOUT_MUXGATE_CLK_DISPAUD_DECON_INT_ECLK				28
#define CLK_GOUT_MUXGATE_CLK_DISPAUD_DECON_INT_VCLK				29
#define CLK_GOUT_MUXGATE_CLK_DISPAUD_MI2S					30
#define CLK_GOUT_MUXGATE_DISP_PLL						31
#define CLK_MOUT_AUD_PLL							32
#define CLK_MOUT_CLKCMU_DISPAUD_BUS_USER					33
#define CLK_MOUT_CLKCMU_DISPAUD_DECON_INT_ECLK_USER				34
#define CLK_MOUT_CLKCMU_DISPAUD_DECON_INT_VCLK_USER				35
#define CLK_MOUT_CLKPHY_DISPAUD_MIPIPHY_RXCLKESC0_USER				36
#define CLK_MOUT_CLKPHY_DISPAUD_MIPIPHY_TXBYTECLKHS_USER			37
#define CLK_MOUT_CLK_DISPAUD_DECON_INT_ECLK					38
#define CLK_MOUT_CLK_DISPAUD_DECON_INT_VCLK					39
#define CLK_MOUT_CLK_DISPAUD_MI2S						40
#define CLK_MOUT_DISP_PLL							41
#define CLK_FOUT_DISP_PLL							42
#define DISPAUD_NR_CLK								43

/* CMU_FSYS */
#define CLK_GOUT_CLK_FSYS_UID_BUSP3_FSYS_IPCLKPORT_HCLK			1
#define CLK_GOUT_CLK_FSYS_UID_MMC0_IPCLKPORT_I_ACLK			2
#define CLK_GOUT_CLK_FSYS_UID_MMC1_IPCLKPORT_I_ACLK			3
#define CLK_GOUT_CLK_FSYS_UID_MMC2_IPCLKPORT_I_ACLK			4
#define CLK_GOUT_CLK_FSYS_UID_PDMA0_IPCLKPORT_ACLK_PDMA0		5
#define CLK_GOUT_CLK_FSYS_UID_PPMU_FSYS_IPCLKPORT_ACLK			6
#define CLK_GOUT_CLK_FSYS_UID_PPMU_FSYS_IPCLKPORT_PCLK			7
#define CLK_GOUT_CLK_FSYS_UID_SROMC_IPCLKPORT_HCLK			8
#define CLK_GOUT_CLK_FSYS_UID_UPSIZER_BUS1_FSYS_IPCLKPORT_ACLK		9
#define CLK_GOUT_CLK_FSYS_UID_USB20DRD_IPCLKPORT_ACLK_HSDRD		10
#define CLK_GOUT_CLK_FSYS_UID_USB20DRD_IPCLKPORT_HCLK_USB20_CTRL	11
#define CLK_GOUT_CLK_FSYS_UID_USB20DRD_IPCLKPORT_HSDRD_REF_CLK		12
#define CLK_GOUT_MUXGATE_CLKPHY_FSYS_USB20DRD_PHYCLOCK_USER		13
#define CLK_GOUT_MUXGATE_USB_PLL					14
#define CLK_MOUT_CLKPHY_FSYS_USB20DRD_PHYCLOCK_USER			15
#define CLK_MOUT_USB_PLL						16
#define CLK_FOUT_USB_PLL						17
#define FSYS_NR_CLK							18

/* CMU_G3D */
#define CLK_DOUT_CLK_G3D_APB					1
#define CLK_DOUT_CLK_G3D_BUS					2
#define CLK_GOUT_CLK_G3D_UID_ASYNCS_D0_G3D_IPCLKPORT_I_CLK	3
#define CLK_GOUT_CLK_G3D_UID_ASYNC_G3D_P_IPCLKPORT_PCLKM	4
#define CLK_GOUT_CLK_G3D_UID_G3D_IPCLKPORT_CLK			5
#define CLK_GOUT_CLK_G3D_UID_PPMU_G3D_IPCLKPORT_ACLK		6
#define CLK_GOUT_CLK_G3D_UID_PPMU_G3D_IPCLKPORT_PCLK		7
#define CLK_GOUT_CLK_G3D_UID_QE_G3D_IPCLKPORT_ACLK		8
#define CLK_GOUT_CLK_G3D_UID_QE_G3D_IPCLKPORT_PCLK		9
#define CLK_GOUT_CLK_G3D_UID_SYSREG_G3D_IPCLKPORT_PCLK		10
#define CLK_GOUT_MUXGATE_CLKCMU_G3D_SWITCH_USER			11
#define CLK_GOUT_MUXGATE_CLK_G3D				12
#define CLK_GOUT_MUXGATE_G3D_PLL				13
#define CLK_MOUT_CLKCMU_G3D_SWITCH_USER				14
#define CLK_MOUT_CLK_G3D					15
#define CLK_MOUT_G3D_PLL					16
#define CLK_FOUT_G3D_PLL					17
#define G3D_NR_CLK						18

/* CMU_ISP */
#define CLK_DOUT_CLK_ISP_APB					1
#define CLK_DOUT_CLK_ISP_CAM_HALF				2
#define CLK_GOUT_CLK_ISP_UID_CLK_ISP_CAM			3
#define CLK_GOUT_CLK_ISP_UID_CLK_ISP_CAM_HALF			4
#define CLK_GOUT_CLK_ISP_UID_CLK_ISP_ISPD			5
#define CLK_GOUT_CLK_ISP_UID_CLK_ISP_ISPD_PPMU			6
#define CLK_GOUT_CLK_ISP_UID_CLK_ISP_VRA			7
#define CLK_GOUT_MUXGATE_CLKCMU_ISP_CAM_USER			8
#define CLK_GOUT_MUXGATE_CLKCMU_ISP_ISP_USER			9
#define CLK_GOUT_MUXGATE_CLKCMU_ISP_VRA_USER			10
#define CLK_GOUT_MUXGATE_CLKPHY_ISP_S_RXBYTECLKHS0_S4S_USER	11
#define CLK_GOUT_MUXGATE_CLKPHY_ISP_S_RXBYTECLKHS0_S4_USER	12
#define CLK_GOUT_MUXGATE_CLK_ISP_CAM				13
#define CLK_GOUT_MUXGATE_CLK_ISP_ISP				14
#define CLK_GOUT_MUXGATE_CLK_ISP_ISPD				15
#define CLK_GOUT_MUXGATE_CLK_ISP_VRA				16
#define CLK_GOUT_MUXGATE_ISP_PLL				17
#define CLK_MOUT_CLKCMU_ISP_CAM_USER				18
#define CLK_MOUT_CLKCMU_ISP_ISP_USER				19
#define CLK_MOUT_CLKCMU_ISP_VRA_USER				20
#define CLK_MOUT_CLKPHY_ISP_S_RXBYTECLKHS0_S4S_USER		21
#define CLK_MOUT_CLKPHY_ISP_S_RXBYTECLKHS0_S4_USER		22
#define CLK_MOUT_CLK_ISP_CAM					23
#define CLK_MOUT_CLK_ISP_ISP					24
#define CLK_MOUT_CLK_ISP_ISPD					25
#define CLK_MOUT_CLK_ISP_VRA					26
#define CLK_MOUT_ISP_PLL					27
#define CLK_FOUT_ISP_PLL					28
#define ISP_NR_CLK						29

/* CMU_MFCMSCL */
#define CLK_DOUT_CLK_MFCMSCL_APB				1
#define CLK_GOUT_CLK_MFCMSCL_UID_CLKCMU_MFCMSCL_MFC		2
#define CLK_GOUT_CLK_MFCMSCL_UID_CLKCMU_MFCMSCL_MSCL		3
#define CLK_GOUT_CLK_MFCMSCL_UID_CLKCMU_MFCMSCL_MSCL_BI		4
#define CLK_GOUT_CLK_MFCMSCL_UID_CLKCMU_MFCMSCL_MSCL_D		5
#define CLK_GOUT_CLK_MFCMSCL_UID_CLKCMU_MFCMSCL_MSCL_JPEG	6
#define CLK_GOUT_CLK_MFCMSCL_UID_CLKCMU_MFCMSCL_MSCL_POLY	7
#define CLK_GOUT_CLK_MFCMSCL_UID_CLKCMU_MFCMSCL_MSCL_PPMU	8
#define CLK_GOUT_MUXGATE_CLKCMU_MFCMSCL_MFC_USER		9
#define CLK_GOUT_MUXGATE_CLKCMU_MFCMSCL_MSCL_USER		10
#define CLK_MOUT_CLKCMU_MFCMSCL_MFC_USER			11
#define CLK_MOUT_CLKCMU_MFCMSCL_MSCL_USER			12
#define MFCMSCL_NR_CLK						13

/* CMU_PERI */
#define CLK_GOUT_CLK_PERI_UID_BUSP1_PERIC0_IPCLKPORT_HCLK		1
#define CLK_GOUT_CLK_PERI_UID_GPIO_ESE_IPCLKPORT_PCLK			2
#define CLK_GOUT_CLK_PERI_UID_GPIO_NFC_IPCLKPORT_PCLK			3
#define CLK_GOUT_CLK_PERI_UID_GPIO_TOP_IPCLKPORT_PCLK			4
#define CLK_GOUT_CLK_PERI_UID_GPIO_TOUCH_IPCLKPORT_PCLK			5
#define CLK_GOUT_CLK_PERI_UID_HSI2C_DEPTHCAM_IPCLKPORT_IPCLK		6
#define CLK_GOUT_CLK_PERI_UID_HSI2C_FRONTCAM_IPCLKPORT_IPCLK		7
#define CLK_GOUT_CLK_PERI_UID_HSI2C_FRONTSENSOR_IPCLKPORT_IPCLK		8
#define CLK_GOUT_CLK_PERI_UID_HSI2C_MAINCAM_IPCLKPORT_IPCLK		9
#define CLK_GOUT_CLK_PERI_UID_HSI2C_REARAF_IPCLKPORT_IPCLK		10
#define CLK_GOUT_CLK_PERI_UID_HSI2C_REARSENSOR_IPCLKPORT_IPCLK		11
#define CLK_GOUT_CLK_PERI_UID_I2C_FUELGAUGE_IPCLKPORT_PCLK		12
#define CLK_GOUT_CLK_PERI_UID_I2C_IFPMIC_IPCLKPORT_PCLK			13
#define CLK_GOUT_CLK_PERI_UID_I2C_MUIC_IPCLKPORT_PCLK			14
#define CLK_GOUT_CLK_PERI_UID_I2C_NFC_IPCLKPORT_PCLK			15
#define CLK_GOUT_CLK_PERI_UID_I2C_SENSOR1_IPCLKPORT_PCLK		16
#define CLK_GOUT_CLK_PERI_UID_I2C_SENSOR2_IPCLKPORT_PCLK		17
#define CLK_GOUT_CLK_PERI_UID_I2C_SPKAMP_IPCLKPORT_PCLK			18
#define CLK_GOUT_CLK_PERI_UID_I2C_TOUCHKEY_IPCLKPORT_PCLK		19
#define CLK_GOUT_CLK_PERI_UID_I2C_TSP_IPCLKPORT_PCLK			20
#define CLK_GOUT_CLK_PERI_UID_MCT_IPCLKPORT_PCLK			21
#define CLK_GOUT_CLK_PERI_UID_PWM_MOTOR_IPCLKPORT_I_OSCCLK		22
#define CLK_GOUT_CLK_PERI_UID_PWM_MOTOR_IPCLKPORT_I_PCLK_S0		23
#define CLK_GOUT_CLK_PERI_UID_SFRIF_TMU_CPUCL0_IPCLKPORT_PCLK		24
#define CLK_GOUT_CLK_PERI_UID_SFRIF_TMU_CPUCL1_IPCLKPORT_PCLK		25
#define CLK_GOUT_CLK_PERI_UID_SFRIF_TMU_G3D_IPCLKPORT_PCLK		26
#define CLK_GOUT_CLK_PERI_UID_SPI_ESE_IPCLKPORT_PCLK			27
#define CLK_GOUT_CLK_PERI_UID_SPI_ESE_IPCLKPORT_SPI_EXT_CLK		28
#define CLK_GOUT_CLK_PERI_UID_SPI_FRONTFROM_IPCLKPORT_PCLK		29
#define CLK_GOUT_CLK_PERI_UID_SPI_FRONTFROM_IPCLKPORT_SPI_EXT_CLK	30
#define CLK_GOUT_CLK_PERI_UID_SPI_REARFROM_IPCLKPORT_PCLK		31
#define CLK_GOUT_CLK_PERI_UID_SPI_REARFROM_IPCLKPORT_SPI_EXT_CLK	32
#define CLK_GOUT_CLK_PERI_UID_SPI_SENSORHUB_IPCLKPORT_PCLK		33
#define CLK_GOUT_CLK_PERI_UID_SPI_SENSORHUB_IPCLKPORT_SPI_EXT_CLK	34
#define CLK_GOUT_CLK_PERI_UID_SPI_VOICEPROCESSOR_IPCLKPORT_PCLK		35
#define CLK_GOUT_CLK_PERI_UID_SPI_VOICEPROCESSOR_IPCLKPORT_SPI_EXT_CLK	36
#define CLK_GOUT_CLK_PERI_UID_TMU_CPUCL0_IPCLKPORT_I_CLK		37
#define CLK_GOUT_CLK_PERI_UID_TMU_CPUCL1_IPCLKPORT_I_CLK		38
#define CLK_GOUT_CLK_PERI_UID_TMU_G3D_IPCLKPORT_I_CLK			39
#define CLK_GOUT_CLK_PERI_UID_UART_BTWIFIFM_IPCLKPORT_EXT_UCLK		40
#define CLK_GOUT_CLK_PERI_UID_UART_BTWIFIFM_IPCLKPORT_PCLK		41
#define CLK_GOUT_CLK_PERI_UID_UART_DEBUG_IPCLKPORT_EXT_UCLK		42
#define CLK_GOUT_CLK_PERI_UID_UART_DEBUG_IPCLKPORT_PCLK			43
#define CLK_GOUT_CLK_PERI_UID_UART_SENSOR_IPCLKPORT_EXT_UCLK		44
#define CLK_GOUT_CLK_PERI_UID_UART_SENSOR_IPCLKPORT_PCLK		45
#define CLK_GOUT_CLK_PERI_UID_WDT_CPUCL0_IPCLKPORT_PCLK			46
#define CLK_GOUT_CLK_PERI_UID_WDT_CPUCL1_IPCLKPORT_PCLK			47
#define PERI_NR_CLK							48

#endif /* _DT_BINDINGS_CLOCK_EXYNOS_7870_H */
