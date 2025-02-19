// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (C) 2015 Samsung Electronics Co., Ltd.
 * Copyright (C) 2024 ???
 *
 * Common Clock Framework support for Exynos7870.
 */

#include <linux/clk.h>
#include <linux/clk-provider.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/platform_device.h>

#include <dt-bindings/clock/exynos7870.h>

#include "clk.h"
#include "clk-exynos-arm64.h"

/* ---- CMU_MIF -------------------------------------------------------------*/

/* Register Offset definitions for CMU_MIF (0x10460000) */
#define PLL_LOCKTIME_MEM_PLL								0x0000
#define PLL_LOCKTIME_MEDIA_PLL								0x0020
#define PLL_LOCKTIME_BUS_PLL								0x0040
#define PLL_CON0_MEM_PLL								0x0100
#define PLL_CON0_MEDIA_PLL								0x0120
#define PLL_CON0_BUS_PLL								0x0140
#define CLK_CON_GAT_MIF_MUXGATE_MEM_PLL							0x0200
#define CLK_CON_MUX_MIF_MUX_MEM_PLL							0x0200
#define CLK_CON_GAT_MIF_MUXGATE_MEDIA_PLL						0x0204
#define CLK_CON_MUX_MIF_MUX_MEDIA_PLL							0x0204
#define CLK_CON_GAT_MIF_MUXGATE_BUS_PLL							0x0208
#define CLK_CON_MUX_MIF_MUX_BUS_PLL							0x0208
#define CLK_CON_GAT_MUXGATE_CLK_MIF_BUSD						0x0220
#define CLK_CON_MUX_MUX_CLK_MIF_BUSD							0x0220
#define CLK_CON_GAT_MIF_MUXGATE_CLKCMU_ISP_VRA						0x0264
#define CLK_CON_MUX_MIF_MUX_CLKCMU_ISP_VRA						0x0264
#define CLK_CON_GAT_MIF_MUXGATE_CLKCMU_ISP_CAM						0x0268
#define CLK_CON_MUX_MIF_MUX_CLKCMU_ISP_CAM						0x0268
#define CLK_CON_GAT_MIF_MUXGATE_CLKCMU_ISP_ISP						0x026c
#define CLK_CON_MUX_MIF_MUX_CLKCMU_ISP_ISP						0x026c
#define CLK_CON_GAT_MIF_MUXGATE_CLKCMU_DISPAUD_BUS					0x0270
#define CLK_CON_MUX_MIF_MUX_CLKCMU_DISPAUD_BUS						0x0270
#define CLK_CON_GAT_MIF_MUXGATE_CLKCMU_DISPAUD_DECON_INT_VCLK				0x0274
#define CLK_CON_MUX_MIF_MUX_CLKCMU_DISPAUD_DECON_INT_VCLK				0x0274
#define CLK_CON_GAT_MIF_MUXGATE_CLKCMU_DISPAUD_DECON_INT_ECLK				0x0278
#define CLK_CON_MUX_MIF_MUX_CLKCMU_DISPAUD_DECON_INT_ECLK				0x0278
#define CLK_CON_GAT_MIF_MUXGATE_CLKCMU_MFCMSCL_MSCL					0x027c
#define CLK_CON_MUX_MIF_MUX_CLKCMU_MFCMSCL_MSCL						0x027c
#define CLK_CON_GAT_MIF_MUXGATE_CLKCMU_MFCMSCL_MFC					0x0280
#define CLK_CON_MUX_MIF_MUX_CLKCMU_MFCMSCL_MFC						0x0280
#define CLK_CON_GAT_MIF_MUXGATE_CLKCMU_FSYS_BUS						0x0284
#define CLK_CON_MUX_MIF_MUX_CLKCMU_FSYS_BUS						0x0284
#define CLK_CON_GAT_MIF_MUXGATE_CLKCMU_FSYS_MMC0					0x0288
#define CLK_CON_MUX_MIF_MUX_CLKCMU_FSYS_MMC0						0x0288
#define CLK_CON_GAT_MIF_MUXGATE_CLKCMU_FSYS_MMC1					0x028c
#define CLK_CON_MUX_MIF_MUX_CLKCMU_FSYS_MMC1						0x028c
#define CLK_CON_GAT_MIF_MUXGATE_CLKCMU_FSYS_MMC2					0x0290
#define CLK_CON_MUX_MIF_MUX_CLKCMU_FSYS_MMC2						0x0290
#define CLK_CON_GAT_MIF_MUXGATE_CLKCMU_FSYS_USB20DRD_REFCLK				0x029c
#define CLK_CON_MUX_MIF_MUX_CLKCMU_FSYS_USB20DRD_REFCLK					0x029c
#define CLK_CON_GAT_MIF_MUXGATE_CLKCMU_PERI_BUS						0x02a0
#define CLK_CON_MUX_MIF_MUX_CLKCMU_PERI_BUS						0x02a0
#define CLK_CON_GAT_MIF_MUXGATE_CLKCMU_PERI_UART_BTWIFIFM				0x02a4
#define CLK_CON_MUX_MIF_MUX_CLKCMU_PERI_UART_BTWIFIFM					0x02a4
#define CLK_CON_GAT_MIF_MUXGATE_CLKCMU_PERI_UART_DEBUG					0x02a8
#define CLK_CON_MUX_MIF_MUX_CLKCMU_PERI_UART_DEBUG					0x02a8
#define CLK_CON_GAT_MIF_MUXGATE_CLKCMU_PERI_UART_SENSOR					0x02ac
#define CLK_CON_MUX_MIF_MUX_CLKCMU_PERI_UART_SENSOR					0x02ac
#define CLK_CON_GAT_MIF_MUXGATE_CLKCMU_PERI_SPI_FRONTFROM				0x02b0
#define CLK_CON_MUX_MIF_MUX_CLKCMU_PERI_SPI_FRONTFROM					0x02b0
#define CLK_CON_GAT_MIF_MUXGATE_CLKCMU_PERI_SPI_REARFROM				0x02b4
#define CLK_CON_MUX_MIF_MUX_CLKCMU_PERI_SPI_REARFROM					0x02b4
#define CLK_CON_GAT_MIF_MUXGATE_CLKCMU_PERI_SPI_ESE					0x02b8
#define CLK_CON_MUX_MIF_MUX_CLKCMU_PERI_SPI_ESE						0x02b8
#define CLK_CON_GAT_MIF_MUXGATE_CLKCMU_PERI_SPI_VOICEPROCESSOR				0x02bc
#define CLK_CON_MUX_MIF_MUX_CLKCMU_PERI_SPI_VOICEPROCESSOR				0x02bc
#define CLK_CON_GAT_MIF_MUXGATE_CLKCMU_PERI_SPI_SENSORHUB				0x02c0
#define CLK_CON_MUX_MIF_MUX_CLKCMU_PERI_SPI_SENSORHUB					0x02c0
#define CLK_CON_GAT_MIF_MUXGATE_CLKCMU_ISP_SENSOR0					0x02c4
#define CLK_CON_MUX_MIF_MUX_CLKCMU_ISP_SENSOR0						0x02c4
#define CLK_CON_GAT_MIF_MUXGATE_CLKCMU_ISP_SENSOR1					0x02c8
#define CLK_CON_MUX_MIF_MUX_CLKCMU_ISP_SENSOR1						0x02c8
#define CLK_CON_GAT_MIF_MUXGATE_CLKCMU_ISP_SENSOR2					0x02cc
#define CLK_CON_MUX_MIF_MUX_CLKCMU_ISP_SENSOR2						0x02cc
#define CLK_CON_DIV_DIV_CLK_MIF_BUSD							0x0420
#define CLK_CON_DIV_DIV_CLK_MIF_APB							0x0424
#define CLK_CON_DIV_DIV_CLK_MIF_HSI2C							0x0430
#define CLK_CON_DIV_MIF_DIV_CLKCMU_G3D_SWITCH						0x0460
#define CLK_CON_DIV_MIF_DIV_CLKCMU_ISP_VRA						0x0464
#define CLK_CON_DIV_MIF_DIV_CLKCMU_ISP_CAM						0x0468
#define CLK_CON_DIV_MIF_DIV_CLKCMU_ISP_ISP						0x046c
#define CLK_CON_DIV_MIF_DIV_CLKCMU_DISPAUD_BUS						0x0470
#define CLK_CON_DIV_MIF_DIV_CLKCMU_DISPAUD_DECON_INT_VCLK				0x0474
#define CLK_CON_DIV_MIF_DIV_CLKCMU_DISPAUD_DECON_INT_ECLK				0x0478
#define CLK_CON_DIV_MIF_DIV_CLKCMU_MFCMSCL_MSCL						0x047c
#define CLK_CON_DIV_MIF_DIV_CLKCMU_MFCMSCL_MFC						0x0480
#define CLK_CON_DIV_MIF_DIV_CLKCMU_FSYS_BUS						0x0484
#define CLK_CON_DIV_MIF_DIV_CLKCMU_FSYS_MMC0						0x0488
#define CLK_CON_DIV_MIF_DIV_CLKCMU_FSYS_MMC1						0x048c
#define CLK_CON_DIV_MIF_DIV_CLKCMU_FSYS_MMC2						0x0490
#define CLK_CON_DIV_MIF_DIV_CLKCMU_FSYS_USB20DRD_REFCLK					0x049c
#define CLK_CON_DIV_MIF_DIV_CLKCMU_PERI_BUS						0x04a0
#define CLK_CON_DIV_MIF_DIV_CLKCMU_PERI_UART_BTWIFIFM					0x04a4
#define CLK_CON_DIV_MIF_DIV_CLKCMU_PERI_UART_DEBUG					0x04a8
#define CLK_CON_DIV_MIF_DIV_CLKCMU_PERI_UART_SENSOR					0x04ac
#define CLK_CON_DIV_MIF_DIV_CLKCMU_PERI_SPI_FRONTFROM					0x04b0
#define CLK_CON_DIV_MIF_DIV_CLKCMU_PERI_SPI_REARFROM					0x04b4
#define CLK_CON_DIV_MIF_DIV_CLKCMU_PERI_SPI_ESE						0x04b8
#define CLK_CON_DIV_MIF_DIV_CLKCMU_PERI_SPI_VOICEPROCESSOR				0x04bc
#define CLK_CON_DIV_MIF_DIV_CLKCMU_PERI_SPI_SENSORHUB					0x04c0
#define CLK_CON_DIV_MIF_DIV_CLKCMU_ISP_SENSOR0						0x04c4
#define CLK_CON_DIV_MIF_DIV_CLKCMU_ISP_SENSOR1						0x04c8
#define CLK_CON_DIV_MIF_DIV_CLKCMU_ISP_SENSOR2						0x04cc
#define CLK_CON_GAT_GATE_CLK_MIF_UID_WRAP_ADC_IF_IPCLKPORT_I_OSC_SYS			0x080c
#define CLK_CON_GAT_GATE_CLK_MIF_UID_ASYNCAPB_HSI2C_AP_IPCLKPORT_PCLKS			0x0828
#define CLK_CON_GAT_GATE_CLK_MIF_UID_ASYNCAPB_HSI2C_CP_IPCLKPORT_PCLKS			0x0828
#define CLK_CON_GAT_GATE_CLK_MIF_UID_WRAP_ADC_IF_IPCLKPORT_PCLK_S0			0x0828
#define CLK_CON_GAT_GATE_CLK_MIF_UID_WRAP_ADC_IF_IPCLKPORT_PCLK_S1			0x0828
#define CLK_CON_GAT_GATE_CLK_MIF_UID_ASYNCAPB_HSI2C_AP_IPCLKPORT_PCLKM			0x0840
#define CLK_CON_GAT_GATE_CLK_MIF_UID_ASYNCAPB_HSI2C_CP_IPCLKPORT_PCLKM			0x0840
#define CLK_CON_GAT_GATE_CLK_MIF_UID_HSI2C_MIF_IPCLKPORT_IPCLK				0x0840
#define CLK_CON_GAT_GATE_CLK_MIF_UID_HSI2C_MIF_IPCLKPORT_ITCLK				0x0840
#define CLK_CON_GAT_GATE_CLK_MIF_UID_MODAPIF_V1P5_MIF_CP_IPCLKPORT_PCLK_HSI2C		0x0840
#define CLK_CON_GAT_GATE_CLK_MIF_UID_MODAPIF_V1P5_MIF_CP_IPCLKPORT_PCLK_HSI2C_BAT_0	0x0840
#define CLK_CON_GAT_GATE_CLK_MIF_UID_MODAPIF_V1P5_MIF_CP_IPCLKPORT_PCLK_HSI2C_BAT_1	0x0840
#define CLK_CON_GAT_MIF_GATE_CLKCMU_G3D_SWITCH						0x0860
#define CLK_CON_GAT_MIF_GATE_CLKCMU_ISP_VRA						0x0864
#define CLK_CON_GAT_MIF_GATE_CLKCMU_ISP_CAM						0x0868
#define CLK_CON_GAT_MIF_GATE_CLKCMU_ISP_ISP						0x086c
#define CLK_CON_GAT_MIF_GATE_CLKCMU_DISPAUD_BUS						0x0870
#define CLK_CON_GAT_MIF_GATE_CLKCMU_DISPAUD_DECON_INT_VCLK				0x0874
#define CLK_CON_GAT_MIF_GATE_CLKCMU_DISPAUD_DECON_INT_ECLK				0x0878
#define CLK_CON_GAT_MIF_GATE_CLKCMU_MFCMSCL_MSCL					0x087c
#define CLK_CON_GAT_MIF_GATE_CLKCMU_MFCMSCL_MFC						0x0880
#define CLK_CON_GAT_MIF_GATE_CLKCMU_FSYS_BUS						0x0884
#define CLK_CON_GAT_MIF_GATE_CLKCMU_FSYS_MMC0						0x0888
#define CLK_CON_GAT_MIF_GATE_CLKCMU_FSYS_MMC1						0x088c
#define CLK_CON_GAT_MIF_GATE_CLKCMU_FSYS_MMC2						0x0890
#define CLK_CON_GAT_MIF_GATE_CLKCMU_FSYS_USB20DRD_REFCLK				0x089c
#define CLK_CON_GAT_MIF_GATE_CLKCMU_PERI_BUS						0x08a0
#define CLK_CON_GAT_MIF_GATE_CLKCMU_PERI_UART_BTWIFIFM					0x08a4
#define CLK_CON_GAT_MIF_GATE_CLKCMU_PERI_UART_DEBUG					0x08a8
#define CLK_CON_GAT_MIF_GATE_CLKCMU_PERI_UART_SENSOR					0x08ac
#define CLK_CON_GAT_MIF_GATE_CLKCMU_PERI_SPI_FRONTFROM					0x08b0
#define CLK_CON_GAT_MIF_GATE_CLKCMU_PERI_SPI_REARFROM					0x08b4
#define CLK_CON_GAT_MIF_GATE_CLKCMU_PERI_SPI_ESE					0x08b8
#define CLK_CON_GAT_MIF_GATE_CLKCMU_PERI_SPI_VOICEPROCESSOR				0x08bc
#define CLK_CON_GAT_MIF_GATE_CLKCMU_PERI_SPI_SENSORHUB					0x08c0
#define CLK_CON_GAT_MIF_GATE_CLKCMU_ISP_SENSOR0						0x08c4
#define CLK_CON_GAT_MIF_GATE_CLKCMU_ISP_SENSOR1						0x08c8
#define CLK_CON_GAT_MIF_GATE_CLKCMU_ISP_SENSOR2						0x08cc

static const struct samsung_fixed_factor_clock mif_fixed_factor_clks[] __initconst = {
	FFACTOR(0, "ffac_mux_bus_pll_div2", "gout_muxgate_bus_pll", 1, 2, 0),
	FFACTOR(0, "ffac_mux_media_pll_div2", "gout_muxgate_media_pll", 1, 2, 0),
	FFACTOR(0, "ffac_mux_mem_pll_div2", "gout_muxgate_mem_pll", 1, 2, 0),
};

static const unsigned long mif_clk_regs[] __initconst = {
	PLL_LOCKTIME_MEM_PLL,
	PLL_LOCKTIME_MEDIA_PLL,
	PLL_LOCKTIME_BUS_PLL,
	PLL_CON0_MEM_PLL,
	PLL_CON0_MEDIA_PLL,
	PLL_CON0_BUS_PLL,
	CLK_CON_GAT_MIF_MUXGATE_MEM_PLL,
	CLK_CON_MUX_MIF_MUX_MEM_PLL,
	CLK_CON_GAT_MIF_MUXGATE_MEDIA_PLL,
	CLK_CON_MUX_MIF_MUX_MEDIA_PLL,
	CLK_CON_GAT_MIF_MUXGATE_BUS_PLL,
	CLK_CON_MUX_MIF_MUX_BUS_PLL,
	CLK_CON_GAT_MUXGATE_CLK_MIF_BUSD,
	CLK_CON_MUX_MUX_CLK_MIF_BUSD,
	CLK_CON_GAT_MIF_MUXGATE_CLKCMU_ISP_VRA,
	CLK_CON_MUX_MIF_MUX_CLKCMU_ISP_VRA,
	CLK_CON_GAT_MIF_MUXGATE_CLKCMU_ISP_CAM,
	CLK_CON_MUX_MIF_MUX_CLKCMU_ISP_CAM,
	CLK_CON_GAT_MIF_MUXGATE_CLKCMU_ISP_ISP,
	CLK_CON_MUX_MIF_MUX_CLKCMU_ISP_ISP,
	CLK_CON_GAT_MIF_MUXGATE_CLKCMU_DISPAUD_BUS,
	CLK_CON_MUX_MIF_MUX_CLKCMU_DISPAUD_BUS,
	CLK_CON_GAT_MIF_MUXGATE_CLKCMU_DISPAUD_DECON_INT_VCLK,
	CLK_CON_MUX_MIF_MUX_CLKCMU_DISPAUD_DECON_INT_VCLK,
	CLK_CON_GAT_MIF_MUXGATE_CLKCMU_DISPAUD_DECON_INT_ECLK,
	CLK_CON_MUX_MIF_MUX_CLKCMU_DISPAUD_DECON_INT_ECLK,
	CLK_CON_GAT_MIF_MUXGATE_CLKCMU_MFCMSCL_MSCL,
	CLK_CON_MUX_MIF_MUX_CLKCMU_MFCMSCL_MSCL,
	CLK_CON_GAT_MIF_MUXGATE_CLKCMU_MFCMSCL_MFC,
	CLK_CON_MUX_MIF_MUX_CLKCMU_MFCMSCL_MFC,
	CLK_CON_GAT_MIF_MUXGATE_CLKCMU_FSYS_BUS,
	CLK_CON_MUX_MIF_MUX_CLKCMU_FSYS_BUS,
	CLK_CON_GAT_MIF_MUXGATE_CLKCMU_FSYS_MMC0,
	CLK_CON_MUX_MIF_MUX_CLKCMU_FSYS_MMC0,
	CLK_CON_GAT_MIF_MUXGATE_CLKCMU_FSYS_MMC1,
	CLK_CON_MUX_MIF_MUX_CLKCMU_FSYS_MMC1,
	CLK_CON_GAT_MIF_MUXGATE_CLKCMU_FSYS_MMC2,
	CLK_CON_MUX_MIF_MUX_CLKCMU_FSYS_MMC2,
	CLK_CON_GAT_MIF_MUXGATE_CLKCMU_FSYS_USB20DRD_REFCLK,
	CLK_CON_MUX_MIF_MUX_CLKCMU_FSYS_USB20DRD_REFCLK,
	CLK_CON_GAT_MIF_MUXGATE_CLKCMU_PERI_BUS,
	CLK_CON_MUX_MIF_MUX_CLKCMU_PERI_BUS,
	CLK_CON_GAT_MIF_MUXGATE_CLKCMU_PERI_UART_BTWIFIFM,
	CLK_CON_MUX_MIF_MUX_CLKCMU_PERI_UART_BTWIFIFM,
	CLK_CON_GAT_MIF_MUXGATE_CLKCMU_PERI_UART_DEBUG,
	CLK_CON_MUX_MIF_MUX_CLKCMU_PERI_UART_DEBUG,
	CLK_CON_GAT_MIF_MUXGATE_CLKCMU_PERI_UART_SENSOR,
	CLK_CON_MUX_MIF_MUX_CLKCMU_PERI_UART_SENSOR,
	CLK_CON_GAT_MIF_MUXGATE_CLKCMU_PERI_SPI_FRONTFROM,
	CLK_CON_MUX_MIF_MUX_CLKCMU_PERI_SPI_FRONTFROM,
	CLK_CON_GAT_MIF_MUXGATE_CLKCMU_PERI_SPI_REARFROM,
	CLK_CON_MUX_MIF_MUX_CLKCMU_PERI_SPI_REARFROM,
	CLK_CON_GAT_MIF_MUXGATE_CLKCMU_PERI_SPI_ESE,
	CLK_CON_MUX_MIF_MUX_CLKCMU_PERI_SPI_ESE,
	CLK_CON_GAT_MIF_MUXGATE_CLKCMU_PERI_SPI_VOICEPROCESSOR,
	CLK_CON_MUX_MIF_MUX_CLKCMU_PERI_SPI_VOICEPROCESSOR,
	CLK_CON_GAT_MIF_MUXGATE_CLKCMU_PERI_SPI_SENSORHUB,
	CLK_CON_MUX_MIF_MUX_CLKCMU_PERI_SPI_SENSORHUB,
	CLK_CON_GAT_MIF_MUXGATE_CLKCMU_ISP_SENSOR0,
	CLK_CON_MUX_MIF_MUX_CLKCMU_ISP_SENSOR0,
	CLK_CON_GAT_MIF_MUXGATE_CLKCMU_ISP_SENSOR1,
	CLK_CON_MUX_MIF_MUX_CLKCMU_ISP_SENSOR1,
	CLK_CON_GAT_MIF_MUXGATE_CLKCMU_ISP_SENSOR2,
	CLK_CON_MUX_MIF_MUX_CLKCMU_ISP_SENSOR2,
	CLK_CON_DIV_DIV_CLK_MIF_BUSD,
	CLK_CON_DIV_DIV_CLK_MIF_APB,
	CLK_CON_DIV_DIV_CLK_MIF_HSI2C,
	CLK_CON_DIV_MIF_DIV_CLKCMU_G3D_SWITCH,
	CLK_CON_DIV_MIF_DIV_CLKCMU_ISP_VRA,
	CLK_CON_DIV_MIF_DIV_CLKCMU_ISP_CAM,
	CLK_CON_DIV_MIF_DIV_CLKCMU_ISP_ISP,
	CLK_CON_DIV_MIF_DIV_CLKCMU_DISPAUD_BUS,
	CLK_CON_DIV_MIF_DIV_CLKCMU_DISPAUD_DECON_INT_VCLK,
	CLK_CON_DIV_MIF_DIV_CLKCMU_DISPAUD_DECON_INT_ECLK,
	CLK_CON_DIV_MIF_DIV_CLKCMU_MFCMSCL_MSCL,
	CLK_CON_DIV_MIF_DIV_CLKCMU_MFCMSCL_MFC,
	CLK_CON_DIV_MIF_DIV_CLKCMU_FSYS_BUS,
	CLK_CON_DIV_MIF_DIV_CLKCMU_FSYS_MMC0,
	CLK_CON_DIV_MIF_DIV_CLKCMU_FSYS_MMC1,
	CLK_CON_DIV_MIF_DIV_CLKCMU_FSYS_MMC2,
	CLK_CON_DIV_MIF_DIV_CLKCMU_FSYS_USB20DRD_REFCLK,
	CLK_CON_DIV_MIF_DIV_CLKCMU_PERI_BUS,
	CLK_CON_DIV_MIF_DIV_CLKCMU_PERI_UART_BTWIFIFM,
	CLK_CON_DIV_MIF_DIV_CLKCMU_PERI_UART_DEBUG,
	CLK_CON_DIV_MIF_DIV_CLKCMU_PERI_UART_SENSOR,
	CLK_CON_DIV_MIF_DIV_CLKCMU_PERI_SPI_FRONTFROM,
	CLK_CON_DIV_MIF_DIV_CLKCMU_PERI_SPI_REARFROM,
	CLK_CON_DIV_MIF_DIV_CLKCMU_PERI_SPI_ESE,
	CLK_CON_DIV_MIF_DIV_CLKCMU_PERI_SPI_VOICEPROCESSOR,
	CLK_CON_DIV_MIF_DIV_CLKCMU_PERI_SPI_SENSORHUB,
	CLK_CON_DIV_MIF_DIV_CLKCMU_ISP_SENSOR0,
	CLK_CON_DIV_MIF_DIV_CLKCMU_ISP_SENSOR1,
	CLK_CON_DIV_MIF_DIV_CLKCMU_ISP_SENSOR2,
	CLK_CON_GAT_GATE_CLK_MIF_UID_WRAP_ADC_IF_IPCLKPORT_I_OSC_SYS,
	CLK_CON_GAT_GATE_CLK_MIF_UID_ASYNCAPB_HSI2C_AP_IPCLKPORT_PCLKS,
	CLK_CON_GAT_GATE_CLK_MIF_UID_ASYNCAPB_HSI2C_CP_IPCLKPORT_PCLKS,
	CLK_CON_GAT_GATE_CLK_MIF_UID_WRAP_ADC_IF_IPCLKPORT_PCLK_S0,
	CLK_CON_GAT_GATE_CLK_MIF_UID_WRAP_ADC_IF_IPCLKPORT_PCLK_S1,
	CLK_CON_GAT_GATE_CLK_MIF_UID_ASYNCAPB_HSI2C_AP_IPCLKPORT_PCLKM,
	CLK_CON_GAT_GATE_CLK_MIF_UID_ASYNCAPB_HSI2C_CP_IPCLKPORT_PCLKM,
	CLK_CON_GAT_GATE_CLK_MIF_UID_HSI2C_MIF_IPCLKPORT_IPCLK,
	CLK_CON_GAT_GATE_CLK_MIF_UID_HSI2C_MIF_IPCLKPORT_ITCLK,
	CLK_CON_GAT_GATE_CLK_MIF_UID_MODAPIF_V1P5_MIF_CP_IPCLKPORT_PCLK_HSI2C,
	CLK_CON_GAT_GATE_CLK_MIF_UID_MODAPIF_V1P5_MIF_CP_IPCLKPORT_PCLK_HSI2C_BAT_0,
	CLK_CON_GAT_GATE_CLK_MIF_UID_MODAPIF_V1P5_MIF_CP_IPCLKPORT_PCLK_HSI2C_BAT_1,
	CLK_CON_GAT_MIF_GATE_CLKCMU_G3D_SWITCH,
	CLK_CON_GAT_MIF_GATE_CLKCMU_ISP_VRA,
	CLK_CON_GAT_MIF_GATE_CLKCMU_ISP_CAM,
	CLK_CON_GAT_MIF_GATE_CLKCMU_ISP_ISP,
	CLK_CON_GAT_MIF_GATE_CLKCMU_DISPAUD_BUS,
	CLK_CON_GAT_MIF_GATE_CLKCMU_DISPAUD_DECON_INT_VCLK,
	CLK_CON_GAT_MIF_GATE_CLKCMU_DISPAUD_DECON_INT_ECLK,
	CLK_CON_GAT_MIF_GATE_CLKCMU_MFCMSCL_MSCL,
	CLK_CON_GAT_MIF_GATE_CLKCMU_MFCMSCL_MFC,
	CLK_CON_GAT_MIF_GATE_CLKCMU_FSYS_BUS,
	CLK_CON_GAT_MIF_GATE_CLKCMU_FSYS_MMC0,
	CLK_CON_GAT_MIF_GATE_CLKCMU_FSYS_MMC1,
	CLK_CON_GAT_MIF_GATE_CLKCMU_FSYS_MMC2,
	CLK_CON_GAT_MIF_GATE_CLKCMU_FSYS_USB20DRD_REFCLK,
	CLK_CON_GAT_MIF_GATE_CLKCMU_PERI_BUS,
	CLK_CON_GAT_MIF_GATE_CLKCMU_PERI_UART_BTWIFIFM,
	CLK_CON_GAT_MIF_GATE_CLKCMU_PERI_UART_DEBUG,
	CLK_CON_GAT_MIF_GATE_CLKCMU_PERI_UART_SENSOR,
	CLK_CON_GAT_MIF_GATE_CLKCMU_PERI_SPI_FRONTFROM,
	CLK_CON_GAT_MIF_GATE_CLKCMU_PERI_SPI_REARFROM,
	CLK_CON_GAT_MIF_GATE_CLKCMU_PERI_SPI_ESE,
	CLK_CON_GAT_MIF_GATE_CLKCMU_PERI_SPI_VOICEPROCESSOR,
	CLK_CON_GAT_MIF_GATE_CLKCMU_PERI_SPI_SENSORHUB,
	CLK_CON_GAT_MIF_GATE_CLKCMU_ISP_SENSOR0,
	CLK_CON_GAT_MIF_GATE_CLKCMU_ISP_SENSOR1,
	CLK_CON_GAT_MIF_GATE_CLKCMU_ISP_SENSOR2,
};

static const struct samsung_pll_clock mif_pll_clks[] __initconst = {
	PLL(pll_1417x, CLK_FOUT_BUS_PLL, "fout_bus_pll", "oscclk",
	    PLL_LOCKTIME_BUS_PLL, PLL_CON0_BUS_PLL,
	    NULL),
	PLL(pll_1417x, CLK_FOUT_MEDIA_PLL, "fout_media_pll", "oscclk",
	    PLL_LOCKTIME_MEDIA_PLL, PLL_CON0_MEDIA_PLL,
	    NULL),
	PLL(pll_1417x, CLK_FOUT_MEM_PLL, "fout_mem_pll", "oscclk",
	    PLL_LOCKTIME_MEM_PLL, PLL_CON0_MEM_PLL,
	    NULL),
};

/* List of parent clocks for Muxes in CMU_MIF */
PNAME(mout_clkcmu_dispaud_bus_p)		= { "ffac_mux_bus_pll_div2", "ffac_mux_media_pll_div2" };
PNAME(mout_clkcmu_dispaud_decon_int_eclk_p)	= { "ffac_mux_bus_pll_div2", "ffac_mux_media_pll_div2" };
PNAME(mout_clkcmu_dispaud_decon_int_vclk_p)	= { "ffac_mux_bus_pll_div2", "ffac_mux_media_pll_div2" };
PNAME(mout_clkcmu_fsys_bus_p)			= { "ffac_mux_bus_pll_div2", "ffac_mux_media_pll_div2" };
PNAME(mout_clkcmu_fsys_mmc0_p)			= { "ffac_mux_bus_pll_div2", "ffac_mux_media_pll_div2" };
PNAME(mout_clkcmu_fsys_mmc1_p)			= { "ffac_mux_bus_pll_div2", "ffac_mux_media_pll_div2" };
PNAME(mout_clkcmu_fsys_mmc2_p)			= { "ffac_mux_bus_pll_div2", "ffac_mux_media_pll_div2" };
PNAME(mout_clkcmu_fsys_usb20drd_refclk_p)	= { "ffac_mux_bus_pll_div2", "ffac_mux_media_pll_div2" };
PNAME(mout_clkcmu_isp_cam_p)			= { "ffac_mux_bus_pll_div2", "ffac_mux_media_pll_div2" };
PNAME(mout_clkcmu_isp_isp_p)			= { "ffac_mux_bus_pll_div2", "ffac_mux_media_pll_div2" };
PNAME(mout_clkcmu_isp_sensor0_p)		= { "ffac_mux_bus_pll_div2", "oscclk" };
PNAME(mout_clkcmu_isp_sensor1_p)		= { "ffac_mux_bus_pll_div2", "oscclk" };
PNAME(mout_clkcmu_isp_sensor2_p)		= { "ffac_mux_bus_pll_div2", "oscclk" };
PNAME(mout_clkcmu_isp_vra_p)			= { "ffac_mux_bus_pll_div2", "ffac_mux_media_pll_div2",
						    "gout_muxgate_bus_pll" };
PNAME(mout_clkcmu_mfcmscl_mfc_p)		= { "ffac_mux_bus_pll_div2", "ffac_mux_media_pll_div2",
						    "gout_muxgate_bus_pll" };
PNAME(mout_clkcmu_mfcmscl_mscl_p)		= { "ffac_mux_bus_pll_div2", "ffac_mux_media_pll_div2",
						    "gout_muxgate_bus_pll" };
PNAME(mout_clkcmu_peri_bus_p)			= { "ffac_mux_bus_pll_div2", "ffac_mux_media_pll_div2" };
PNAME(mout_clkcmu_peri_spi_ese_p)		= { "ffac_mux_bus_pll_div2", "oscclk" };
PNAME(mout_clkcmu_peri_spi_frontfrom_p)		= { "ffac_mux_bus_pll_div2", "oscclk" };
PNAME(mout_clkcmu_peri_spi_rearfrom_p)		= { "ffac_mux_bus_pll_div2", "oscclk" };
PNAME(mout_clkcmu_peri_spi_sensorhub_p)		= { "ffac_mux_bus_pll_div2", "oscclk" };
PNAME(mout_clkcmu_peri_spi_voiceprocessor_p)	= { "ffac_mux_bus_pll_div2", "oscclk" };
PNAME(mout_clkcmu_peri_uart_btwififm_p)		= { "ffac_mux_bus_pll_div2", "ffac_mux_media_pll_div2" };
PNAME(mout_clkcmu_peri_uart_debug_p)		= { "ffac_mux_bus_pll_div2", "ffac_mux_media_pll_div2" };
PNAME(mout_clkcmu_peri_uart_sensor_p)		= { "ffac_mux_bus_pll_div2", "ffac_mux_media_pll_div2" };
PNAME(mout_clk_mif_busd_p)			= { "ffac_mux_bus_pll_div2", "ffac_mux_media_pll_div2",
						    "ffac_mux_mem_pll_div2" };

static const struct samsung_mux_clock mif_mux_clks[] __initconst = {
	MUX(CLK_MOUT_CLKCMU_DISPAUD_BUS, "mout_clkcmu_dispaud_bus", mout_clkcmu_dispaud_bus_p,
	    CLK_CON_MUX_MIF_MUX_CLKCMU_DISPAUD_BUS, 12, 1),
	MUX(CLK_MOUT_CLKCMU_DISPAUD_DECON_INT_ECLK, "mout_clkcmu_dispaud_decon_int_eclk", mout_clkcmu_dispaud_decon_int_eclk_p,
	    CLK_CON_MUX_MIF_MUX_CLKCMU_DISPAUD_DECON_INT_ECLK, 12, 1),
	MUX(CLK_MOUT_CLKCMU_DISPAUD_DECON_INT_VCLK, "mout_clkcmu_dispaud_decon_int_vclk", mout_clkcmu_dispaud_decon_int_vclk_p,
	    CLK_CON_MUX_MIF_MUX_CLKCMU_DISPAUD_DECON_INT_VCLK, 12, 1),
	MUX(CLK_MOUT_CLKCMU_FSYS_BUS, "mout_clkcmu_fsys_bus", mout_clkcmu_fsys_bus_p,
	    CLK_CON_MUX_MIF_MUX_CLKCMU_FSYS_BUS, 12, 1),
	MUX(CLK_MOUT_CLKCMU_FSYS_MMC0, "mout_clkcmu_fsys_mmc0", mout_clkcmu_fsys_mmc0_p,
	    CLK_CON_MUX_MIF_MUX_CLKCMU_FSYS_MMC0, 12, 1),
	MUX(CLK_MOUT_CLKCMU_FSYS_MMC1, "mout_clkcmu_fsys_mmc1", mout_clkcmu_fsys_mmc1_p,
	    CLK_CON_MUX_MIF_MUX_CLKCMU_FSYS_MMC1, 12, 1),
	MUX(CLK_MOUT_CLKCMU_FSYS_MMC2, "mout_clkcmu_fsys_mmc2", mout_clkcmu_fsys_mmc2_p,
	    CLK_CON_MUX_MIF_MUX_CLKCMU_FSYS_MMC2, 12, 1),
	MUX(CLK_MOUT_CLKCMU_FSYS_USB20DRD_REFCLK, "mout_clkcmu_fsys_usb20drd_refclk", mout_clkcmu_fsys_usb20drd_refclk_p,
	    CLK_CON_MUX_MIF_MUX_CLKCMU_FSYS_USB20DRD_REFCLK, 12, 1),
	MUX(CLK_MOUT_CLKCMU_ISP_CAM, "mout_clkcmu_isp_cam", mout_clkcmu_isp_cam_p,
	    CLK_CON_MUX_MIF_MUX_CLKCMU_ISP_CAM, 12, 1),
	MUX(CLK_MOUT_CLKCMU_ISP_ISP, "mout_clkcmu_isp_isp", mout_clkcmu_isp_isp_p,
	    CLK_CON_MUX_MIF_MUX_CLKCMU_ISP_ISP, 12, 1),
	MUX(CLK_MOUT_CLKCMU_ISP_SENSOR0, "mout_clkcmu_isp_sensor0", mout_clkcmu_isp_sensor0_p,
	    CLK_CON_MUX_MIF_MUX_CLKCMU_ISP_SENSOR0, 12, 1),
	MUX(CLK_MOUT_CLKCMU_ISP_SENSOR1, "mout_clkcmu_isp_sensor1", mout_clkcmu_isp_sensor1_p,
	    CLK_CON_MUX_MIF_MUX_CLKCMU_ISP_SENSOR1, 12, 1),
	MUX(CLK_MOUT_CLKCMU_ISP_SENSOR2, "mout_clkcmu_isp_sensor2", mout_clkcmu_isp_sensor2_p,
	    CLK_CON_MUX_MIF_MUX_CLKCMU_ISP_SENSOR2, 12, 1),
	MUX(CLK_MOUT_CLKCMU_ISP_VRA, "mout_clkcmu_isp_vra", mout_clkcmu_isp_vra_p,
	    CLK_CON_MUX_MIF_MUX_CLKCMU_ISP_VRA, 12, 2),
	MUX(CLK_MOUT_CLKCMU_MFCMSCL_MFC, "mout_clkcmu_mfcmscl_mfc", mout_clkcmu_mfcmscl_mfc_p,
	    CLK_CON_MUX_MIF_MUX_CLKCMU_MFCMSCL_MFC, 12, 2),
	MUX(CLK_MOUT_CLKCMU_MFCMSCL_MSCL, "mout_clkcmu_mfcmscl_mscl", mout_clkcmu_mfcmscl_mscl_p,
	    CLK_CON_MUX_MIF_MUX_CLKCMU_MFCMSCL_MSCL, 12, 2),
	MUX(CLK_MOUT_CLKCMU_PERI_BUS, "mout_clkcmu_peri_bus", mout_clkcmu_peri_bus_p,
	    CLK_CON_MUX_MIF_MUX_CLKCMU_PERI_BUS, 12, 1),
	MUX(CLK_MOUT_CLKCMU_PERI_SPI_ESE, "mout_clkcmu_peri_spi_ese", mout_clkcmu_peri_spi_ese_p,
	    CLK_CON_MUX_MIF_MUX_CLKCMU_PERI_SPI_ESE, 12, 1),
	MUX(CLK_MOUT_CLKCMU_PERI_SPI_FRONTFROM, "mout_clkcmu_peri_spi_frontfrom", mout_clkcmu_peri_spi_frontfrom_p,
	    CLK_CON_MUX_MIF_MUX_CLKCMU_PERI_SPI_FRONTFROM, 12, 1),
	MUX(CLK_MOUT_CLKCMU_PERI_SPI_REARFROM, "mout_clkcmu_peri_spi_rearfrom", mout_clkcmu_peri_spi_rearfrom_p,
	    CLK_CON_MUX_MIF_MUX_CLKCMU_PERI_SPI_REARFROM, 12, 1),
	MUX(CLK_MOUT_CLKCMU_PERI_SPI_SENSORHUB, "mout_clkcmu_peri_spi_sensorhub", mout_clkcmu_peri_spi_sensorhub_p,
	    CLK_CON_MUX_MIF_MUX_CLKCMU_PERI_SPI_SENSORHUB, 12, 1),
	MUX(CLK_MOUT_CLKCMU_PERI_SPI_VOICEPROCESSOR, "mout_clkcmu_peri_spi_voiceprocessor", mout_clkcmu_peri_spi_voiceprocessor_p,
	    CLK_CON_MUX_MIF_MUX_CLKCMU_PERI_SPI_VOICEPROCESSOR, 12, 1),
	MUX(CLK_MOUT_CLKCMU_PERI_UART_BTWIFIFM, "mout_clkcmu_peri_uart_btwififm", mout_clkcmu_peri_uart_btwififm_p,
	    CLK_CON_MUX_MIF_MUX_CLKCMU_PERI_UART_BTWIFIFM, 12, 1),
	MUX(CLK_MOUT_CLKCMU_PERI_UART_DEBUG, "mout_clkcmu_peri_uart_debug", mout_clkcmu_peri_uart_debug_p,
	    CLK_CON_MUX_MIF_MUX_CLKCMU_PERI_UART_DEBUG, 12, 1),
	MUX(CLK_MOUT_CLKCMU_PERI_UART_SENSOR, "mout_clkcmu_peri_uart_sensor", mout_clkcmu_peri_uart_sensor_p,
	    CLK_CON_MUX_MIF_MUX_CLKCMU_PERI_UART_SENSOR, 12, 1),
	MUX(CLK_MOUT_CLK_MIF_BUSD, "mout_clk_mif_busd", mout_clk_mif_busd_p,
	    CLK_CON_MUX_MUX_CLK_MIF_BUSD, 12, 2),
};

static const struct samsung_div_clock mif_div_clks[] __initconst = {
	DIV(CLK_DOUT_CLKCMU_DISPAUD_BUS, "dout_clkcmu_dispaud_bus", "gout_muxgate_clkcmu_dispaud_bus",
	    CLK_CON_DIV_MIF_DIV_CLKCMU_DISPAUD_BUS, 0, 4),
	DIV(CLK_DOUT_CLKCMU_DISPAUD_DECON_INT_ECLK, "dout_clkcmu_dispaud_decon_int_eclk", "gout_muxgate_clkcmu_dispaud_decon_int_eclk",
	    CLK_CON_DIV_MIF_DIV_CLKCMU_DISPAUD_DECON_INT_ECLK, 0, 4),
	DIV(CLK_DOUT_CLKCMU_DISPAUD_DECON_INT_VCLK, "dout_clkcmu_dispaud_decon_int_vclk", "gout_muxgate_clkcmu_dispaud_decon_int_vclk",
	    CLK_CON_DIV_MIF_DIV_CLKCMU_DISPAUD_DECON_INT_VCLK, 0, 4),
	DIV(CLK_DOUT_CLKCMU_FSYS_BUS, "dout_clkcmu_fsys_bus", "gout_muxgate_clkcmu_fsys_bus",
	    CLK_CON_DIV_MIF_DIV_CLKCMU_FSYS_BUS, 0, 4),
	DIV(CLK_DOUT_CLKCMU_FSYS_MMC0, "dout_clkcmu_fsys_mmc0", "gout_muxgate_clkcmu_fsys_mmc0",
	    CLK_CON_DIV_MIF_DIV_CLKCMU_FSYS_MMC0, 0, 10),
	DIV(CLK_DOUT_CLKCMU_FSYS_MMC1, "dout_clkcmu_fsys_mmc1", "gout_muxgate_clkcmu_fsys_mmc1",
	    CLK_CON_DIV_MIF_DIV_CLKCMU_FSYS_MMC1, 0, 10),
	DIV(CLK_DOUT_CLKCMU_FSYS_MMC2, "dout_clkcmu_fsys_mmc2", "gout_muxgate_clkcmu_fsys_mmc2",
	    CLK_CON_DIV_MIF_DIV_CLKCMU_FSYS_MMC2, 0, 10),
	DIV(CLK_DOUT_CLKCMU_FSYS_USB20DRD_REFCLK, "dout_clkcmu_fsys_usb20drd_refclk", "gout_muxgate_clkcmu_fsys_usb20drd_refclk",
	    CLK_CON_DIV_MIF_DIV_CLKCMU_FSYS_USB20DRD_REFCLK, 0, 4),
	DIV(CLK_DOUT_CLKCMU_G3D_SWITCH, "dout_clkcmu_g3d_switch", "ffac_mux_bus_pll_div2",
	    CLK_CON_DIV_MIF_DIV_CLKCMU_G3D_SWITCH, 0, 2),
	DIV(CLK_DOUT_CLKCMU_ISP_CAM, "dout_clkcmu_isp_cam", "gout_muxgate_clkcmu_isp_cam",
	    CLK_CON_DIV_MIF_DIV_CLKCMU_ISP_CAM, 0, 4),
	DIV(CLK_DOUT_CLKCMU_ISP_ISP, "dout_clkcmu_isp_isp", "gout_muxgate_clkcmu_isp_isp",
	    CLK_CON_DIV_MIF_DIV_CLKCMU_ISP_ISP, 0, 4),
	DIV(CLK_DOUT_CLKCMU_ISP_SENSOR0, "dout_clkcmu_isp_sensor0", "gout_muxgate_clkcmu_isp_sensor0",
	    CLK_CON_DIV_MIF_DIV_CLKCMU_ISP_SENSOR0, 0, 6),
	DIV(CLK_DOUT_CLKCMU_ISP_SENSOR1, "dout_clkcmu_isp_sensor1", "gout_muxgate_clkcmu_isp_sensor1",
	    CLK_CON_DIV_MIF_DIV_CLKCMU_ISP_SENSOR1, 0, 6),
	DIV(CLK_DOUT_CLKCMU_ISP_SENSOR2, "dout_clkcmu_isp_sensor2", "gout_muxgate_clkcmu_isp_sensor2",
	    CLK_CON_DIV_MIF_DIV_CLKCMU_ISP_SENSOR2, 0, 6),
	DIV(CLK_DOUT_CLKCMU_ISP_VRA, "dout_clkcmu_isp_vra", "gout_muxgate_clkcmu_isp_vra",
	    CLK_CON_DIV_MIF_DIV_CLKCMU_ISP_VRA, 0, 4),
	DIV(CLK_DOUT_CLKCMU_MFCMSCL_MFC, "dout_clkcmu_mfcmscl_mfc", "gout_muxgate_clkcmu_mfcmscl_mfc",
	    CLK_CON_DIV_MIF_DIV_CLKCMU_MFCMSCL_MFC, 0, 4),
	DIV(CLK_DOUT_CLKCMU_MFCMSCL_MSCL, "dout_clkcmu_mfcmscl_mscl", "gout_muxgate_clkcmu_mfcmscl_mscl",
	    CLK_CON_DIV_MIF_DIV_CLKCMU_MFCMSCL_MSCL, 0, 4),
	DIV(CLK_DOUT_CLKCMU_PERI_BUS, "dout_clkcmu_peri_bus", "gout_muxgate_clkcmu_peri_bus",
	    CLK_CON_DIV_MIF_DIV_CLKCMU_PERI_BUS, 0, 4),
	DIV(CLK_DOUT_CLKCMU_PERI_SPI_ESE, "dout_clkcmu_peri_spi_ese", "gout_muxgate_clkcmu_peri_spi_ese",
	    CLK_CON_DIV_MIF_DIV_CLKCMU_PERI_SPI_ESE, 0, 6),
	DIV(CLK_DOUT_CLKCMU_PERI_SPI_FRONTFROM, "dout_clkcmu_peri_spi_frontfrom", "gout_muxgate_clkcmu_peri_spi_frontfrom",
	    CLK_CON_DIV_MIF_DIV_CLKCMU_PERI_SPI_FRONTFROM, 0, 6),
	DIV(CLK_DOUT_CLKCMU_PERI_SPI_REARFROM, "dout_clkcmu_peri_spi_rearfrom", "gout_muxgate_clkcmu_peri_spi_rearfrom",
	    CLK_CON_DIV_MIF_DIV_CLKCMU_PERI_SPI_REARFROM, 0, 6),
	DIV(CLK_DOUT_CLKCMU_PERI_SPI_SENSORHUB, "dout_clkcmu_peri_spi_sensorhub", "gout_muxgate_clkcmu_peri_spi_sensorhub",
	    CLK_CON_DIV_MIF_DIV_CLKCMU_PERI_SPI_SENSORHUB, 0, 6),
	DIV(CLK_DOUT_CLKCMU_PERI_SPI_VOICEPROCESSOR, "dout_clkcmu_peri_spi_voiceprocessor", "gout_muxgate_clkcmu_peri_spi_voiceprocessor",
	    CLK_CON_DIV_MIF_DIV_CLKCMU_PERI_SPI_VOICEPROCESSOR, 0, 6),
	DIV(CLK_DOUT_CLKCMU_PERI_UART_BTWIFIFM, "dout_clkcmu_peri_uart_btwififm", "gout_muxgate_clkcmu_peri_uart_btwififm",
	    CLK_CON_DIV_MIF_DIV_CLKCMU_PERI_UART_BTWIFIFM, 0, 4),
	DIV(CLK_DOUT_CLKCMU_PERI_UART_DEBUG, "dout_clkcmu_peri_uart_debug", "gout_muxgate_clkcmu_peri_uart_debug",
	    CLK_CON_DIV_MIF_DIV_CLKCMU_PERI_UART_DEBUG, 0, 4),
	DIV(CLK_DOUT_CLKCMU_PERI_UART_SENSOR, "dout_clkcmu_peri_uart_sensor", "gout_muxgate_clkcmu_peri_uart_sensor",
	    CLK_CON_DIV_MIF_DIV_CLKCMU_PERI_UART_SENSOR, 0, 4),
	DIV(CLK_DOUT_CLK_MIF_APB, "dout_clk_mif_apb", "dout_clk_mif_busd",
	    CLK_CON_DIV_DIV_CLK_MIF_APB, 0, 2),
	DIV(CLK_DOUT_CLK_MIF_BUSD, "dout_clk_mif_busd", "gout_muxgate_clk_mif_busd",
	    CLK_CON_DIV_DIV_CLK_MIF_BUSD, 0, 4),
	DIV(CLK_DOUT_CLK_MIF_HSI2C, "dout_clk_mif_hsi2c", "ffac_mux_media_pll_div2",
	    CLK_CON_DIV_DIV_CLK_MIF_HSI2C, 0, 4),
};

static const struct samsung_gate_clock mif_gate_clks[] __initconst = {
	GATE(CLK_GOUT_CLKCMU_DISPAUD_BUS, "gout_clkcmu_dispaud_bus", "dout_clkcmu_dispaud_bus",
	    CLK_CON_GAT_MIF_GATE_CLKCMU_DISPAUD_BUS, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLKCMU_DISPAUD_DECON_INT_ECLK, "gout_clkcmu_dispaud_decon_int_eclk", "dout_clkcmu_dispaud_decon_int_eclk",
	    CLK_CON_GAT_MIF_GATE_CLKCMU_DISPAUD_DECON_INT_ECLK, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLKCMU_DISPAUD_DECON_INT_VCLK, "gout_clkcmu_dispaud_decon_int_vclk", "dout_clkcmu_dispaud_decon_int_vclk",
	    CLK_CON_GAT_MIF_GATE_CLKCMU_DISPAUD_DECON_INT_VCLK, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLKCMU_FSYS_BUS, "gout_clkcmu_fsys_bus", "dout_clkcmu_fsys_bus",
	    CLK_CON_GAT_MIF_GATE_CLKCMU_FSYS_BUS, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLKCMU_FSYS_MMC0, "gout_clkcmu_fsys_mmc0", "dout_clkcmu_fsys_mmc0",
	    CLK_CON_GAT_MIF_GATE_CLKCMU_FSYS_MMC0, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLKCMU_FSYS_MMC1, "gout_clkcmu_fsys_mmc1", "dout_clkcmu_fsys_mmc1",
	    CLK_CON_GAT_MIF_GATE_CLKCMU_FSYS_MMC1, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLKCMU_FSYS_MMC2, "gout_clkcmu_fsys_mmc2", "dout_clkcmu_fsys_mmc2",
	    CLK_CON_GAT_MIF_GATE_CLKCMU_FSYS_MMC2, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLKCMU_FSYS_USB20DRD_REFCLK, "gout_clkcmu_fsys_usb20drd_refclk", "dout_clkcmu_fsys_usb20drd_refclk",
	    CLK_CON_GAT_MIF_GATE_CLKCMU_FSYS_USB20DRD_REFCLK, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLKCMU_G3D_SWITCH, "gout_clkcmu_g3d_switch", "dout_clkcmu_g3d_switch",
	    CLK_CON_GAT_MIF_GATE_CLKCMU_G3D_SWITCH, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLKCMU_ISP_CAM, "gout_clkcmu_isp_cam", "dout_clkcmu_isp_cam",
	    CLK_CON_GAT_MIF_GATE_CLKCMU_ISP_CAM, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLKCMU_ISP_ISP, "gout_clkcmu_isp_isp", "dout_clkcmu_isp_isp",
	    CLK_CON_GAT_MIF_GATE_CLKCMU_ISP_ISP, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLKCMU_ISP_SENSOR0, "gout_clkcmu_isp_sensor0", "dout_clkcmu_isp_sensor0",
	    CLK_CON_GAT_MIF_GATE_CLKCMU_ISP_SENSOR0, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLKCMU_ISP_SENSOR1, "gout_clkcmu_isp_sensor1", "dout_clkcmu_isp_sensor1",
	    CLK_CON_GAT_MIF_GATE_CLKCMU_ISP_SENSOR1, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLKCMU_ISP_SENSOR2, "gout_clkcmu_isp_sensor2", "dout_clkcmu_isp_sensor2",
	    CLK_CON_GAT_MIF_GATE_CLKCMU_ISP_SENSOR2, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLKCMU_ISP_VRA, "gout_clkcmu_isp_vra", "dout_clkcmu_isp_vra",
	    CLK_CON_GAT_MIF_GATE_CLKCMU_ISP_VRA, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLKCMU_MFCMSCL_MFC, "gout_clkcmu_mfcmscl_mfc", "dout_clkcmu_mfcmscl_mfc",
	    CLK_CON_GAT_MIF_GATE_CLKCMU_MFCMSCL_MFC, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLKCMU_MFCMSCL_MSCL, "gout_clkcmu_mfcmscl_mscl", "dout_clkcmu_mfcmscl_mscl",
	    CLK_CON_GAT_MIF_GATE_CLKCMU_MFCMSCL_MSCL, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLKCMU_PERI_BUS, "gout_clkcmu_peri_bus", "dout_clkcmu_peri_bus",
	    CLK_CON_GAT_MIF_GATE_CLKCMU_PERI_BUS, 0, CLK_IS_CRITICAL | CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLKCMU_PERI_SPI_ESE, "gout_clkcmu_peri_spi_ese", "dout_clkcmu_peri_spi_ese",
	    CLK_CON_GAT_MIF_GATE_CLKCMU_PERI_SPI_ESE, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLKCMU_PERI_SPI_FRONTFROM, "gout_clkcmu_peri_spi_frontfrom", "dout_clkcmu_peri_spi_frontfrom",
	    CLK_CON_GAT_MIF_GATE_CLKCMU_PERI_SPI_FRONTFROM, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLKCMU_PERI_SPI_REARFROM, "gout_clkcmu_peri_spi_rearfrom", "dout_clkcmu_peri_spi_rearfrom",
	    CLK_CON_GAT_MIF_GATE_CLKCMU_PERI_SPI_REARFROM, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLKCMU_PERI_SPI_SENSORHUB, "gout_clkcmu_peri_spi_sensorhub", "dout_clkcmu_peri_spi_sensorhub",
	    CLK_CON_GAT_MIF_GATE_CLKCMU_PERI_SPI_SENSORHUB, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLKCMU_PERI_SPI_VOICEPROCESSOR, "gout_clkcmu_peri_spi_voiceprocessor", "dout_clkcmu_peri_spi_voiceprocessor",
	    CLK_CON_GAT_MIF_GATE_CLKCMU_PERI_SPI_VOICEPROCESSOR, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLKCMU_PERI_UART_BTWIFIFM, "gout_clkcmu_peri_uart_btwififm", "dout_clkcmu_peri_uart_btwififm",
	    CLK_CON_GAT_MIF_GATE_CLKCMU_PERI_UART_BTWIFIFM, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLKCMU_PERI_UART_DEBUG, "gout_clkcmu_peri_uart_debug", "dout_clkcmu_peri_uart_debug",
	    CLK_CON_GAT_MIF_GATE_CLKCMU_PERI_UART_DEBUG, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLKCMU_PERI_UART_SENSOR, "gout_clkcmu_peri_uart_sensor", "dout_clkcmu_peri_uart_sensor",
	    CLK_CON_GAT_MIF_GATE_CLKCMU_PERI_UART_SENSOR, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_MIF_UID_ASYNCAPB_HSI2C_AP_IPCLKPORT_PCLKM, "gout_clk_mif_uid_asyncapb_hsi2c_ap_ipclkport_pclkm", "gout_clk_mif_uid_asyncapb_hsi2c_cp_ipclkport_pclkm",
	    CLK_CON_GAT_GATE_CLK_MIF_UID_ASYNCAPB_HSI2C_AP_IPCLKPORT_PCLKM, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_MIF_UID_ASYNCAPB_HSI2C_AP_IPCLKPORT_PCLKS, "gout_clk_mif_uid_asyncapb_hsi2c_ap_ipclkport_pclks", "gout_clk_mif_uid_asyncapb_hsi2c_cp_ipclkport_pclks",
	    CLK_CON_GAT_GATE_CLK_MIF_UID_ASYNCAPB_HSI2C_AP_IPCLKPORT_PCLKS, 14, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_MIF_UID_ASYNCAPB_HSI2C_CP_IPCLKPORT_PCLKM, "gout_clk_mif_uid_asyncapb_hsi2c_cp_ipclkport_pclkm", "gout_clk_mif_uid_hsi2c_mif_ipclkport_ipclk",
	    CLK_CON_GAT_GATE_CLK_MIF_UID_ASYNCAPB_HSI2C_CP_IPCLKPORT_PCLKM, 1, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_MIF_UID_ASYNCAPB_HSI2C_CP_IPCLKPORT_PCLKS, "gout_clk_mif_uid_asyncapb_hsi2c_cp_ipclkport_pclks", "dout_clk_mif_apb",
	    CLK_CON_GAT_GATE_CLK_MIF_UID_ASYNCAPB_HSI2C_CP_IPCLKPORT_PCLKS, 15, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_MIF_UID_HSI2C_MIF_IPCLKPORT_IPCLK, "gout_clk_mif_uid_hsi2c_mif_ipclkport_ipclk", "gout_clk_mif_uid_hsi2c_mif_ipclkport_itclk",
	    CLK_CON_GAT_GATE_CLK_MIF_UID_HSI2C_MIF_IPCLKPORT_IPCLK, 2, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_MIF_UID_HSI2C_MIF_IPCLKPORT_ITCLK, "gout_clk_mif_uid_hsi2c_mif_ipclkport_itclk", "gout_clk_mif_uid_modapif_v1p5_mif_cp_ipclkport_pclk_hsi2c_bat_0",
	    CLK_CON_GAT_GATE_CLK_MIF_UID_HSI2C_MIF_IPCLKPORT_ITCLK, 3, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_MIF_UID_MODAPIF_V1P5_MIF_CP_IPCLKPORT_PCLK_HSI2C, "gout_clk_mif_uid_modapif_v1p5_mif_cp_ipclkport_pclk_hsi2c", "dout_clk_mif_hsi2c",
	    CLK_CON_GAT_GATE_CLK_MIF_UID_MODAPIF_V1P5_MIF_CP_IPCLKPORT_PCLK_HSI2C, 6, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_MIF_UID_MODAPIF_V1P5_MIF_CP_IPCLKPORT_PCLK_HSI2C_BAT_0, "gout_clk_mif_uid_modapif_v1p5_mif_cp_ipclkport_pclk_hsi2c_bat_0", "gout_clk_mif_uid_modapif_v1p5_mif_cp_ipclkport_pclk_hsi2c_bat_1",
	    CLK_CON_GAT_GATE_CLK_MIF_UID_MODAPIF_V1P5_MIF_CP_IPCLKPORT_PCLK_HSI2C_BAT_0, 4, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_MIF_UID_MODAPIF_V1P5_MIF_CP_IPCLKPORT_PCLK_HSI2C_BAT_1, "gout_clk_mif_uid_modapif_v1p5_mif_cp_ipclkport_pclk_hsi2c_bat_1", "gout_clk_mif_uid_modapif_v1p5_mif_cp_ipclkport_pclk_hsi2c",
	    CLK_CON_GAT_GATE_CLK_MIF_UID_MODAPIF_V1P5_MIF_CP_IPCLKPORT_PCLK_HSI2C_BAT_1, 5, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_MIF_UID_WRAP_ADC_IF_IPCLKPORT_I_OSC_SYS, "gout_clk_mif_uid_wrap_adc_if_ipclkport_i_osc_sys", "oscclk",
	    CLK_CON_GAT_GATE_CLK_MIF_UID_WRAP_ADC_IF_IPCLKPORT_I_OSC_SYS, 3, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_MIF_UID_WRAP_ADC_IF_IPCLKPORT_PCLK_S0, "gout_clk_mif_uid_wrap_adc_if_ipclkport_pclk_s0", "gout_clk_mif_uid_wrap_adc_if_ipclkport_pclk_s1",
	    CLK_CON_GAT_GATE_CLK_MIF_UID_WRAP_ADC_IF_IPCLKPORT_PCLK_S0, 20, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_MIF_UID_WRAP_ADC_IF_IPCLKPORT_PCLK_S1, "gout_clk_mif_uid_wrap_adc_if_ipclkport_pclk_s1", "dout_clk_mif_apb",
	    CLK_CON_GAT_GATE_CLK_MIF_UID_WRAP_ADC_IF_IPCLKPORT_PCLK_S1, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_BUS_PLL, "gout_muxgate_bus_pll", "mout_bus_pll",
	    CLK_CON_GAT_MIF_MUXGATE_BUS_PLL, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_CLKCMU_DISPAUD_BUS, "gout_muxgate_clkcmu_dispaud_bus", "mout_clkcmu_dispaud_bus",
	    CLK_CON_GAT_MIF_MUXGATE_CLKCMU_DISPAUD_BUS, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_CLKCMU_DISPAUD_DECON_INT_ECLK, "gout_muxgate_clkcmu_dispaud_decon_int_eclk", "mout_clkcmu_dispaud_decon_int_eclk",
	    CLK_CON_GAT_MIF_MUXGATE_CLKCMU_DISPAUD_DECON_INT_ECLK, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_CLKCMU_DISPAUD_DECON_INT_VCLK, "gout_muxgate_clkcmu_dispaud_decon_int_vclk", "mout_clkcmu_dispaud_decon_int_vclk",
	    CLK_CON_GAT_MIF_MUXGATE_CLKCMU_DISPAUD_DECON_INT_VCLK, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_CLKCMU_FSYS_BUS, "gout_muxgate_clkcmu_fsys_bus", "mout_clkcmu_fsys_bus",
	    CLK_CON_GAT_MIF_MUXGATE_CLKCMU_FSYS_BUS, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_CLKCMU_FSYS_MMC0, "gout_muxgate_clkcmu_fsys_mmc0", "mout_clkcmu_fsys_mmc0",
	    CLK_CON_GAT_MIF_MUXGATE_CLKCMU_FSYS_MMC0, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_CLKCMU_FSYS_MMC1, "gout_muxgate_clkcmu_fsys_mmc1", "mout_clkcmu_fsys_mmc1",
	    CLK_CON_GAT_MIF_MUXGATE_CLKCMU_FSYS_MMC1, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_CLKCMU_FSYS_MMC2, "gout_muxgate_clkcmu_fsys_mmc2", "mout_clkcmu_fsys_mmc2",
	    CLK_CON_GAT_MIF_MUXGATE_CLKCMU_FSYS_MMC2, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_CLKCMU_FSYS_USB20DRD_REFCLK, "gout_muxgate_clkcmu_fsys_usb20drd_refclk", "mout_clkcmu_fsys_usb20drd_refclk",
	    CLK_CON_GAT_MIF_MUXGATE_CLKCMU_FSYS_USB20DRD_REFCLK, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_CLKCMU_ISP_CAM, "gout_muxgate_clkcmu_isp_cam", "mout_clkcmu_isp_cam",
	    CLK_CON_GAT_MIF_MUXGATE_CLKCMU_ISP_CAM, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_CLKCMU_ISP_ISP, "gout_muxgate_clkcmu_isp_isp", "mout_clkcmu_isp_isp",
	    CLK_CON_GAT_MIF_MUXGATE_CLKCMU_ISP_ISP, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_CLKCMU_ISP_SENSOR0, "gout_muxgate_clkcmu_isp_sensor0", "mout_clkcmu_isp_sensor0",
	    CLK_CON_GAT_MIF_MUXGATE_CLKCMU_ISP_SENSOR0, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_CLKCMU_ISP_SENSOR1, "gout_muxgate_clkcmu_isp_sensor1", "mout_clkcmu_isp_sensor1",
	    CLK_CON_GAT_MIF_MUXGATE_CLKCMU_ISP_SENSOR1, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_CLKCMU_ISP_SENSOR2, "gout_muxgate_clkcmu_isp_sensor2", "mout_clkcmu_isp_sensor2",
	    CLK_CON_GAT_MIF_MUXGATE_CLKCMU_ISP_SENSOR2, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_CLKCMU_ISP_VRA, "gout_muxgate_clkcmu_isp_vra", "mout_clkcmu_isp_vra",
	    CLK_CON_GAT_MIF_MUXGATE_CLKCMU_ISP_VRA, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_CLKCMU_MFCMSCL_MFC, "gout_muxgate_clkcmu_mfcmscl_mfc", "mout_clkcmu_mfcmscl_mfc",
	    CLK_CON_GAT_MIF_MUXGATE_CLKCMU_MFCMSCL_MFC, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_CLKCMU_MFCMSCL_MSCL, "gout_muxgate_clkcmu_mfcmscl_mscl", "mout_clkcmu_mfcmscl_mscl",
	    CLK_CON_GAT_MIF_MUXGATE_CLKCMU_MFCMSCL_MSCL, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_CLKCMU_PERI_BUS, "gout_muxgate_clkcmu_peri_bus", "mout_clkcmu_peri_bus",
	    CLK_CON_GAT_MIF_MUXGATE_CLKCMU_PERI_BUS, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_CLKCMU_PERI_SPI_ESE, "gout_muxgate_clkcmu_peri_spi_ese", "mout_clkcmu_peri_spi_ese",
	    CLK_CON_GAT_MIF_MUXGATE_CLKCMU_PERI_SPI_ESE, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_CLKCMU_PERI_SPI_FRONTFROM, "gout_muxgate_clkcmu_peri_spi_frontfrom", "mout_clkcmu_peri_spi_frontfrom",
	    CLK_CON_GAT_MIF_MUXGATE_CLKCMU_PERI_SPI_FRONTFROM, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_CLKCMU_PERI_SPI_REARFROM, "gout_muxgate_clkcmu_peri_spi_rearfrom", "mout_clkcmu_peri_spi_rearfrom",
	    CLK_CON_GAT_MIF_MUXGATE_CLKCMU_PERI_SPI_REARFROM, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_CLKCMU_PERI_SPI_SENSORHUB, "gout_muxgate_clkcmu_peri_spi_sensorhub", "mout_clkcmu_peri_spi_sensorhub",
	    CLK_CON_GAT_MIF_MUXGATE_CLKCMU_PERI_SPI_SENSORHUB, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_CLKCMU_PERI_SPI_VOICEPROCESSOR, "gout_muxgate_clkcmu_peri_spi_voiceprocessor", "mout_clkcmu_peri_spi_voiceprocessor",
	    CLK_CON_GAT_MIF_MUXGATE_CLKCMU_PERI_SPI_VOICEPROCESSOR, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_CLKCMU_PERI_UART_BTWIFIFM, "gout_muxgate_clkcmu_peri_uart_btwififm", "mout_clkcmu_peri_uart_btwififm",
	    CLK_CON_GAT_MIF_MUXGATE_CLKCMU_PERI_UART_BTWIFIFM, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_CLKCMU_PERI_UART_DEBUG, "gout_muxgate_clkcmu_peri_uart_debug", "mout_clkcmu_peri_uart_debug",
	    CLK_CON_GAT_MIF_MUXGATE_CLKCMU_PERI_UART_DEBUG, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_CLKCMU_PERI_UART_SENSOR, "gout_muxgate_clkcmu_peri_uart_sensor", "mout_clkcmu_peri_uart_sensor",
	    CLK_CON_GAT_MIF_MUXGATE_CLKCMU_PERI_UART_SENSOR, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_CLK_MIF_BUSD, "gout_muxgate_clk_mif_busd", "mout_clk_mif_busd",
	    CLK_CON_GAT_MUXGATE_CLK_MIF_BUSD, 21, CLK_IS_CRITICAL | CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_MEDIA_PLL, "gout_muxgate_media_pll", "mout_media_pll",
	    CLK_CON_GAT_MIF_MUXGATE_MEDIA_PLL, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_MEM_PLL, "gout_muxgate_mem_pll", "mout_mem_pll",
	    CLK_CON_GAT_MIF_MUXGATE_MEM_PLL, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_MOUT_BUS_PLL, "mout_bus_pll", "fout_bus_pll",
	    CLK_CON_MUX_MIF_MUX_BUS_PLL, 12, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_MOUT_MEDIA_PLL, "mout_media_pll", "fout_media_pll",
	    CLK_CON_MUX_MIF_MUX_MEDIA_PLL, 12, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_MOUT_MEM_PLL, "mout_mem_pll", "fout_mem_pll",
	    CLK_CON_MUX_MIF_MUX_MEM_PLL, 12, CLK_SET_RATE_PARENT, 0),
};

static const struct samsung_cmu_info mif_cmu_info __initconst = {
	.fixed_factor_clks	= mif_fixed_factor_clks,
	.nr_fixed_factor_clks	= ARRAY_SIZE(mif_pll_clks),
	.pll_clks		= mif_pll_clks,
	.nr_pll_clks		= ARRAY_SIZE(mif_pll_clks),
	.mux_clks		= mif_mux_clks,
	.nr_mux_clks		= ARRAY_SIZE(mif_mux_clks),
	.div_clks		= mif_div_clks,
	.nr_div_clks		= ARRAY_SIZE(mif_div_clks),
	.gate_clks		= mif_gate_clks,
	.nr_gate_clks		= ARRAY_SIZE(mif_gate_clks),
	.nr_clk_ids		= MIF_NR_CLK,
	.clk_regs		= mif_clk_regs,
	.nr_clk_regs		= ARRAY_SIZE(mif_clk_regs),
};

/* ---- PMU_ALIVE -----------------------------------------------------------*/

/* Register Offset definitions for PMU_ALIVE (0x10480000) */
#define CLK_CON_GAT_PMU_DEBUG_CLKOUT_DISABLE	0x0a00
#define CLK_CON_GAT_PMU_DEBUG_CLKOUT_SEL08	0x0a00
#define CLK_CON_GAT_PMU_DEBUG_CLKOUT_SEL09	0x0a00
#define CLK_CON_GAT_PMU_DEBUG_CLKOUT_SEL10	0x0a00
#define CLK_CON_GAT_PMU_DEBUG_CLKOUT_SEL11	0x0a00
#define CLK_CON_GAT_PMU_DEBUG_CLKOUT_SEL12	0x0a00

static const unsigned long pmu_alive_clk_regs[] __initconst = {
	CLK_CON_GAT_PMU_DEBUG_CLKOUT_DISABLE,
	CLK_CON_GAT_PMU_DEBUG_CLKOUT_SEL08,
	CLK_CON_GAT_PMU_DEBUG_CLKOUT_SEL09,
	CLK_CON_GAT_PMU_DEBUG_CLKOUT_SEL10,
	CLK_CON_GAT_PMU_DEBUG_CLKOUT_SEL11,
	CLK_CON_GAT_PMU_DEBUG_CLKOUT_SEL12,
};

static const struct samsung_gate_clock pmu_alive_gate_clks[] __initconst = {
	GATE(CLK_GOUT_PMU_DEBUG_CLKOUT_DISABLE, "gout_pmu_debug_clkout_disable", "oscclk",
	    CLK_CON_GAT_PMU_DEBUG_CLKOUT_DISABLE, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_PMU_DEBUG_CLKOUT_SEL08, "gout_pmu_debug_clkout_sel08", "oscclk",
	    CLK_CON_GAT_PMU_DEBUG_CLKOUT_SEL08, 8, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_PMU_DEBUG_CLKOUT_SEL09, "gout_pmu_debug_clkout_sel09", "oscclk",
	    CLK_CON_GAT_PMU_DEBUG_CLKOUT_SEL09, 9, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_PMU_DEBUG_CLKOUT_SEL10, "gout_pmu_debug_clkout_sel10", "oscclk",
	    CLK_CON_GAT_PMU_DEBUG_CLKOUT_SEL10, 10, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_PMU_DEBUG_CLKOUT_SEL11, "gout_pmu_debug_clkout_sel11", "oscclk",
	    CLK_CON_GAT_PMU_DEBUG_CLKOUT_SEL11, 11, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_PMU_DEBUG_CLKOUT_SEL12, "gout_pmu_debug_clkout_sel12", "oscclk",
	    CLK_CON_GAT_PMU_DEBUG_CLKOUT_SEL12, 12, CLK_SET_RATE_PARENT, 0),
};

static const struct samsung_cmu_info pmu_alive_cmu_info __initconst = {
	.gate_clks		= pmu_alive_gate_clks,
	.nr_gate_clks		= ARRAY_SIZE(pmu_alive_gate_clks),
	.nr_clk_ids		= PMU_ALIVE_NR_CLK,
	.clk_regs		= pmu_alive_clk_regs,
	.nr_clk_regs		= ARRAY_SIZE(pmu_alive_clk_regs),
};

/* ---- CMU_DISPAUD ---------------------------------------------------------*/

/* Register Offset definitions for CMU_DISPAUD (0x148d0000) */
#define PLL_LOCKTIME_DISP_PLL								0x0000
#define PLL_LOCKTIME_AUD_PLL								0x00c0
#define PLL_CON0_DISP_PLL								0x0100
#define PLL_CON0_AUD_PLL								0x01c0
#define CLK_CON_GAT_DISPAUD_MUXGATE_DISP_PLL						0x0200
#define CLK_CON_MUX_DISPAUD_MUX_DISP_PLL						0x0200
#define CLK_CON_GAT_DISPAUD_MUXGATE_AUD_PLL						0x0204
#define CLK_CON_MUX_DISPAUD_MUX_AUD_PLL							0x0204
#define CLK_CON_GAT_MUXGATE_CLKCMU_DISPAUD_BUS_USER					0x0210
#define CLK_CON_MUX_MUX_CLKCMU_DISPAUD_BUS_USER						0x0210
#define CLK_CON_GAT_MUXGATE_CLKCMU_DISPAUD_DECON_INT_VCLK_USER				0x0214
#define CLK_CON_MUX_MUX_CLKCMU_DISPAUD_DECON_INT_VCLK_USER				0x0214
#define CLK_CON_GAT_MUXGATE_CLKCMU_DISPAUD_DECON_INT_ECLK_USER				0x0218
#define CLK_CON_MUX_MUX_CLKCMU_DISPAUD_DECON_INT_ECLK_USER				0x0218
#define CLK_CON_GAT_MUXGATE_CLK_DISPAUD_DECON_INT_VCLK					0x021c
#define CLK_CON_MUX_MUX_CLK_DISPAUD_DECON_INT_VCLK					0x021c
#define CLK_CON_GAT_MUXGATE_CLK_DISPAUD_DECON_INT_ECLK					0x0220
#define CLK_CON_MUX_MUX_CLK_DISPAUD_DECON_INT_ECLK					0x0220
#define CLK_CON_GAT_MUXGATE_CLKPHY_DISPAUD_MIPIPHY_TXBYTECLKHS_USER			0x0224
#define CLK_CON_MUX_MUX_CLKPHY_DISPAUD_MIPIPHY_TXBYTECLKHS_USER				0x0224
#define CLK_CON_GAT_MUXGATE_CLKPHY_DISPAUD_MIPIPHY_RXCLKESC0_USER			0x0228
#define CLK_CON_MUX_MUX_CLKPHY_DISPAUD_MIPIPHY_RXCLKESC0_USER				0x0228
#define CLK_CON_GAT_MUXGATE_CLK_DISPAUD_MI2S						0x022c
#define CLK_CON_MUX_MUX_CLK_DISPAUD_MI2S						0x022c
#define CLK_CON_DIV_DIV_CLK_DISPAUD_APB							0x0400
#define CLK_CON_DIV_DIV_CLK_DISPAUD_DECON_INT_VCLK					0x0404
#define CLK_CON_DIV_DIV_CLK_DISPAUD_DECON_INT_ECLK					0x0408
#define CLK_CON_DIV_DIV_CLK_DISPAUD_MI2S						0x040c
#define CLK_CON_DIV_DIV_CLK_DISPAUD_MIXER						0x0410
#define CLK_CON_GAT_GATE_CLK_DISPAUD_UID_CLKCMU_DISPAUD_BUS				0x0810
#define CLK_CON_GAT_GATE_CLK_DISPAUD_UID_CLKCMU_DISPAUD_BUS_DISP			0x0810
#define CLK_CON_GAT_GATE_CLK_DISPAUD_UID_CLKCMU_DISPAUD_BUS_PPMU			0x0810
#define CLK_CON_GAT_GATE_CLK_DISPAUD_UID_CLK_DISPAUD_APB_AUD				0x0814
#define CLK_CON_GAT_GATE_CLK_DISPAUD_UID_CLK_DISPAUD_APB_AUD_AMP			0x0814
#define CLK_CON_GAT_GATE_CLK_DISPAUD_UID_CLK_DISPAUD_APB_DISP				0x0814
#define CLK_CON_GAT_GATE_CLK_DISPAUD_UID_DECON_IPCLKPORT_I_VCLK				0x081c
#define CLK_CON_GAT_GATE_CLK_DISPAUD_UID_DECON_IPCLKPORT_I_ECLK				0x0820
#define CLK_CON_GAT_GATE_CLK_DISPAUD_UID_MI2S_AMP_IPCLKPORT_I2SCODCLKI			0x082c
#define CLK_CON_GAT_GATE_CLK_DISPAUD_UID_MI2S_AUD_IPCLKPORT_I2SCODCLKI			0x082c
#define CLK_CON_GAT_GATE_CLK_DISPAUD_UID_MIXER_AUD_IPCLKPORT_SYSCLK			0x0830
#define CLK_CON_GAT_GATE_CLK_DISPAUD_UID_CON_DISPAUD_IPCLKPORT_I_EXT2AUD_BCK_GPIO_I2S	0x0834
#define CLK_CON_GAT_GATE_CLK_DISPAUD_UID_CON_DISPAUD_IPCLKPORT_I_AUD_I2S_BCLK_BT_IN	0x0838
#define CLK_CON_GAT_GATE_CLK_DISPAUD_UID_CON_DISPAUD_IPCLKPORT_I_CP2AUD_BCK		0x083c
#define CLK_CON_GAT_GATE_CLK_DISPAUD_UID_CON_DISPAUD_IPCLKPORT_I_AUD_I2S_BCLK_FM_IN	0x0840

static const unsigned long dispaud_clk_regs[] __initconst = {
	PLL_LOCKTIME_DISP_PLL,
	PLL_LOCKTIME_AUD_PLL,
	PLL_CON0_DISP_PLL,
	PLL_CON0_AUD_PLL,
	CLK_CON_GAT_DISPAUD_MUXGATE_DISP_PLL,
	CLK_CON_MUX_DISPAUD_MUX_DISP_PLL,
	CLK_CON_GAT_DISPAUD_MUXGATE_AUD_PLL,
	CLK_CON_MUX_DISPAUD_MUX_AUD_PLL,
	CLK_CON_GAT_MUXGATE_CLKCMU_DISPAUD_BUS_USER,
	CLK_CON_MUX_MUX_CLKCMU_DISPAUD_BUS_USER,
	CLK_CON_GAT_MUXGATE_CLKCMU_DISPAUD_DECON_INT_VCLK_USER,
	CLK_CON_MUX_MUX_CLKCMU_DISPAUD_DECON_INT_VCLK_USER,
	CLK_CON_GAT_MUXGATE_CLKCMU_DISPAUD_DECON_INT_ECLK_USER,
	CLK_CON_MUX_MUX_CLKCMU_DISPAUD_DECON_INT_ECLK_USER,
	CLK_CON_GAT_MUXGATE_CLK_DISPAUD_DECON_INT_VCLK,
	CLK_CON_MUX_MUX_CLK_DISPAUD_DECON_INT_VCLK,
	CLK_CON_GAT_MUXGATE_CLK_DISPAUD_DECON_INT_ECLK,
	CLK_CON_MUX_MUX_CLK_DISPAUD_DECON_INT_ECLK,
	CLK_CON_GAT_MUXGATE_CLKPHY_DISPAUD_MIPIPHY_TXBYTECLKHS_USER,
	CLK_CON_MUX_MUX_CLKPHY_DISPAUD_MIPIPHY_TXBYTECLKHS_USER,
	CLK_CON_GAT_MUXGATE_CLKPHY_DISPAUD_MIPIPHY_RXCLKESC0_USER,
	CLK_CON_MUX_MUX_CLKPHY_DISPAUD_MIPIPHY_RXCLKESC0_USER,
	CLK_CON_GAT_MUXGATE_CLK_DISPAUD_MI2S,
	CLK_CON_MUX_MUX_CLK_DISPAUD_MI2S,
	CLK_CON_DIV_DIV_CLK_DISPAUD_APB,
	CLK_CON_DIV_DIV_CLK_DISPAUD_DECON_INT_VCLK,
	CLK_CON_DIV_DIV_CLK_DISPAUD_DECON_INT_ECLK,
	CLK_CON_DIV_DIV_CLK_DISPAUD_MI2S,
	CLK_CON_DIV_DIV_CLK_DISPAUD_MIXER,
	CLK_CON_GAT_GATE_CLK_DISPAUD_UID_CLKCMU_DISPAUD_BUS,
	CLK_CON_GAT_GATE_CLK_DISPAUD_UID_CLKCMU_DISPAUD_BUS_DISP,
	CLK_CON_GAT_GATE_CLK_DISPAUD_UID_CLKCMU_DISPAUD_BUS_PPMU,
	CLK_CON_GAT_GATE_CLK_DISPAUD_UID_CLK_DISPAUD_APB_AUD,
	CLK_CON_GAT_GATE_CLK_DISPAUD_UID_CLK_DISPAUD_APB_AUD_AMP,
	CLK_CON_GAT_GATE_CLK_DISPAUD_UID_CLK_DISPAUD_APB_DISP,
	CLK_CON_GAT_GATE_CLK_DISPAUD_UID_DECON_IPCLKPORT_I_VCLK,
	CLK_CON_GAT_GATE_CLK_DISPAUD_UID_DECON_IPCLKPORT_I_ECLK,
	CLK_CON_GAT_GATE_CLK_DISPAUD_UID_MI2S_AMP_IPCLKPORT_I2SCODCLKI,
	CLK_CON_GAT_GATE_CLK_DISPAUD_UID_MI2S_AUD_IPCLKPORT_I2SCODCLKI,
	CLK_CON_GAT_GATE_CLK_DISPAUD_UID_MIXER_AUD_IPCLKPORT_SYSCLK,
	CLK_CON_GAT_GATE_CLK_DISPAUD_UID_CON_DISPAUD_IPCLKPORT_I_EXT2AUD_BCK_GPIO_I2S,
	CLK_CON_GAT_GATE_CLK_DISPAUD_UID_CON_DISPAUD_IPCLKPORT_I_AUD_I2S_BCLK_BT_IN,
	CLK_CON_GAT_GATE_CLK_DISPAUD_UID_CON_DISPAUD_IPCLKPORT_I_CP2AUD_BCK,
	CLK_CON_GAT_GATE_CLK_DISPAUD_UID_CON_DISPAUD_IPCLKPORT_I_AUD_I2S_BCLK_FM_IN,
};

static const struct samsung_pll_clock dispaud_pll_clks[] __initconst = {
	PLL(pll_1417x, CLK_FOUT_AUD_PLL, "fout_aud_pll", "oscclk",
	    PLL_LOCKTIME_AUD_PLL, PLL_CON0_AUD_PLL,
	    NULL),
	PLL(pll_1417x, CLK_FOUT_DISP_PLL, "fout_disp_pll", "oscclk",
	    PLL_LOCKTIME_DISP_PLL, PLL_CON0_DISP_PLL,
	    NULL),
};

/* List of parent clocks for Muxes in CMU_DISPAUD */
PNAME(mout_clkcmu_dispaud_bus_user_p)			= { "oscclk", "gout_clkcmu_dispaud_bus" };
PNAME(mout_clkcmu_dispaud_decon_int_eclk_user_p)	= { "oscclk", "gout_clkcmu_dispaud_decon_int_eclk" };
PNAME(mout_clkcmu_dispaud_decon_int_vclk_user_p)	= { "oscclk", "gout_clkcmu_dispaud_decon_int_vclk" };
PNAME(mout_clk_dispaud_decon_int_eclk_p)		= { "gout_muxgate_clkcmu_dispaud_decon_int_eclk_user", "gout_muxgate_disp_pll" };
PNAME(mout_clk_dispaud_decon_int_vclk_p)		= { "gout_muxgate_clkcmu_dispaud_decon_int_vclk_user", "gout_muxgate_disp_pll" };
PNAME(mout_clk_dispaud_mi2s_p)				= { "gout_muxgate_aud_pll", "clkio_dispaud_audiocdclk0" };

static const struct samsung_mux_clock dispaud_mux_clks[] __initconst = {
	MUX(CLK_MOUT_CLKCMU_DISPAUD_BUS_USER, "mout_clkcmu_dispaud_bus_user", mout_clkcmu_dispaud_bus_user_p,
	    CLK_CON_MUX_MUX_CLKCMU_DISPAUD_BUS_USER, 12, 1),
	MUX(CLK_MOUT_CLKCMU_DISPAUD_DECON_INT_ECLK_USER, "mout_clkcmu_dispaud_decon_int_eclk_user", mout_clkcmu_dispaud_decon_int_eclk_user_p,
	    CLK_CON_MUX_MUX_CLKCMU_DISPAUD_DECON_INT_ECLK_USER, 12, 1),
	MUX(CLK_MOUT_CLKCMU_DISPAUD_DECON_INT_VCLK_USER, "mout_clkcmu_dispaud_decon_int_vclk_user", mout_clkcmu_dispaud_decon_int_vclk_user_p,
	    CLK_CON_MUX_MUX_CLKCMU_DISPAUD_DECON_INT_VCLK_USER, 12, 1),
	MUX(CLK_MOUT_CLK_DISPAUD_DECON_INT_ECLK, "mout_clk_dispaud_decon_int_eclk", mout_clk_dispaud_decon_int_eclk_p,
	    CLK_CON_MUX_MUX_CLK_DISPAUD_DECON_INT_ECLK, 12, 1),
	MUX(CLK_MOUT_CLK_DISPAUD_DECON_INT_VCLK, "mout_clk_dispaud_decon_int_vclk", mout_clk_dispaud_decon_int_vclk_p,
	    CLK_CON_MUX_MUX_CLK_DISPAUD_DECON_INT_VCLK, 12, 1),
	MUX(CLK_MOUT_CLK_DISPAUD_MI2S, "mout_clk_dispaud_mi2s", mout_clk_dispaud_mi2s_p,
	    CLK_CON_MUX_MUX_CLK_DISPAUD_MI2S, 12, 1),
};

static const struct samsung_div_clock dispaud_div_clks[] __initconst = {
	DIV(CLK_DOUT_CLK_DISPAUD_APB, "dout_clk_dispaud_apb", "gout_muxgate_clkcmu_dispaud_bus_user",
	    CLK_CON_DIV_DIV_CLK_DISPAUD_APB, 0, 2),
	DIV(CLK_DOUT_CLK_DISPAUD_DECON_INT_ECLK, "dout_clk_dispaud_decon_int_eclk", "gout_muxgate_clk_dispaud_decon_int_eclk",
	    CLK_CON_DIV_DIV_CLK_DISPAUD_DECON_INT_ECLK, 0, 3),
	DIV(CLK_DOUT_CLK_DISPAUD_DECON_INT_VCLK, "dout_clk_dispaud_decon_int_vclk", "gout_muxgate_clk_dispaud_decon_int_vclk",
	    CLK_CON_DIV_DIV_CLK_DISPAUD_DECON_INT_VCLK, 0, 3),
	DIV(CLK_DOUT_CLK_DISPAUD_MI2S, "dout_clk_dispaud_mi2s", "gout_muxgate_clk_dispaud_mi2s",
	    CLK_CON_DIV_DIV_CLK_DISPAUD_MI2S, 0, 4),
	DIV(CLK_DOUT_CLK_DISPAUD_MIXER, "dout_clk_dispaud_mixer", "gout_muxgate_aud_pll",
	    CLK_CON_DIV_DIV_CLK_DISPAUD_MIXER, 0, 4),
};

static const struct samsung_gate_clock dispaud_gate_clks[] __initconst = {
	GATE(CLK_GOUT_CLK_DISPAUD_UID_CLKCMU_DISPAUD_BUS, "gout_clk_dispaud_uid_clkcmu_dispaud_bus", "gout_muxgate_clkcmu_dispaud_bus_user",
	    CLK_CON_GAT_GATE_CLK_DISPAUD_UID_CLKCMU_DISPAUD_BUS, 0, CLK_IS_CRITICAL | CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_DISPAUD_UID_CLKCMU_DISPAUD_BUS_DISP, "gout_clk_dispaud_uid_clkcmu_dispaud_bus_disp", "gout_muxgate_clkcmu_dispaud_bus_user",
	    CLK_CON_GAT_GATE_CLK_DISPAUD_UID_CLKCMU_DISPAUD_BUS_DISP, 2, CLK_IS_CRITICAL | CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_DISPAUD_UID_CLKCMU_DISPAUD_BUS_PPMU, "gout_clk_dispaud_uid_clkcmu_dispaud_bus_ppmu", "gout_muxgate_clkcmu_dispaud_bus_user",
	    CLK_CON_GAT_GATE_CLK_DISPAUD_UID_CLKCMU_DISPAUD_BUS_PPMU, 3, CLK_IS_CRITICAL | CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_DISPAUD_UID_CLK_DISPAUD_APB_AUD, "gout_clk_dispaud_uid_clk_dispaud_apb_aud", "dout_clk_dispaud_apb",
	    CLK_CON_GAT_GATE_CLK_DISPAUD_UID_CLK_DISPAUD_APB_AUD, 2, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_DISPAUD_UID_CLK_DISPAUD_APB_AUD_AMP, "gout_clk_dispaud_uid_clk_dispaud_apb_aud_amp", "dout_clk_dispaud_apb",
	    CLK_CON_GAT_GATE_CLK_DISPAUD_UID_CLK_DISPAUD_APB_AUD_AMP, 3, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_DISPAUD_UID_CLK_DISPAUD_APB_DISP, "gout_clk_dispaud_uid_clk_dispaud_apb_disp", "dout_clk_dispaud_apb",
	    CLK_CON_GAT_GATE_CLK_DISPAUD_UID_CLK_DISPAUD_APB_DISP, 1, CLK_IS_CRITICAL | CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_DISPAUD_UID_CON_DISPAUD_IPCLKPORT_I_AUD_I2S_BCLK_BT_IN, "gout_clk_dispaud_uid_con_dispaud_ipclkport_i_aud_i2s_bclk_bt_in", "clkio_dispaud_mixer_bclk_bt",
	    CLK_CON_GAT_GATE_CLK_DISPAUD_UID_CON_DISPAUD_IPCLKPORT_I_AUD_I2S_BCLK_BT_IN, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_DISPAUD_UID_CON_DISPAUD_IPCLKPORT_I_AUD_I2S_BCLK_FM_IN, "gout_clk_dispaud_uid_con_dispaud_ipclkport_i_aud_i2s_bclk_fm_in", "clkio_dispaud_mixer_bclk_fm",
	    CLK_CON_GAT_GATE_CLK_DISPAUD_UID_CON_DISPAUD_IPCLKPORT_I_AUD_I2S_BCLK_FM_IN, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_DISPAUD_UID_CON_DISPAUD_IPCLKPORT_I_CP2AUD_BCK, "gout_clk_dispaud_uid_con_dispaud_ipclkport_i_cp2aud_bck", "clkio_dispaud_mixer_bclk_cp",
	    CLK_CON_GAT_GATE_CLK_DISPAUD_UID_CON_DISPAUD_IPCLKPORT_I_CP2AUD_BCK, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_DISPAUD_UID_CON_DISPAUD_IPCLKPORT_I_EXT2AUD_BCK_GPIO_I2S, "gout_clk_dispaud_uid_con_dispaud_ipclkport_i_ext2aud_bck_gpio_i2s", "clkio_dispaud_mixer_sclk_ap",
	    CLK_CON_GAT_GATE_CLK_DISPAUD_UID_CON_DISPAUD_IPCLKPORT_I_EXT2AUD_BCK_GPIO_I2S, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_DISPAUD_UID_DECON_IPCLKPORT_I_ECLK, "gout_clk_dispaud_uid_decon_ipclkport_i_eclk", "dout_clk_dispaud_decon_int_eclk",
	    CLK_CON_GAT_GATE_CLK_DISPAUD_UID_DECON_IPCLKPORT_I_ECLK, 0, CLK_IS_CRITICAL | CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_DISPAUD_UID_DECON_IPCLKPORT_I_VCLK, "gout_clk_dispaud_uid_decon_ipclkport_i_vclk", "dout_clk_dispaud_decon_int_vclk",
	    CLK_CON_GAT_GATE_CLK_DISPAUD_UID_DECON_IPCLKPORT_I_VCLK, 0, CLK_IS_CRITICAL | CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_DISPAUD_UID_MI2S_AMP_IPCLKPORT_I2SCODCLKI, "gout_clk_dispaud_uid_mi2s_amp_ipclkport_i2scodclki", "dout_clk_dispaud_mi2s",
	    CLK_CON_GAT_GATE_CLK_DISPAUD_UID_MI2S_AMP_IPCLKPORT_I2SCODCLKI, 1, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_DISPAUD_UID_MI2S_AUD_IPCLKPORT_I2SCODCLKI, "gout_clk_dispaud_uid_mi2s_aud_ipclkport_i2scodclki", "dout_clk_dispaud_mi2s",
	    CLK_CON_GAT_GATE_CLK_DISPAUD_UID_MI2S_AUD_IPCLKPORT_I2SCODCLKI, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_DISPAUD_UID_MIXER_AUD_IPCLKPORT_SYSCLK, "gout_clk_dispaud_uid_mixer_aud_ipclkport_sysclk", "dout_clk_dispaud_mixer",
	    CLK_CON_GAT_GATE_CLK_DISPAUD_UID_MIXER_AUD_IPCLKPORT_SYSCLK, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_AUD_PLL, "gout_muxgate_aud_pll", "mout_aud_pll",
	    CLK_CON_GAT_DISPAUD_MUXGATE_AUD_PLL, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_CLKCMU_DISPAUD_BUS_USER, "gout_muxgate_clkcmu_dispaud_bus_user", "mout_clkcmu_dispaud_bus_user",
	    CLK_CON_GAT_MUXGATE_CLKCMU_DISPAUD_BUS_USER, 21, CLK_IS_CRITICAL | CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_CLKCMU_DISPAUD_DECON_INT_ECLK_USER, "gout_muxgate_clkcmu_dispaud_decon_int_eclk_user", "mout_clkcmu_dispaud_decon_int_eclk_user",
	    CLK_CON_GAT_MUXGATE_CLKCMU_DISPAUD_DECON_INT_ECLK_USER, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_CLKCMU_DISPAUD_DECON_INT_VCLK_USER, "gout_muxgate_clkcmu_dispaud_decon_int_vclk_user", "mout_clkcmu_dispaud_decon_int_vclk_user",
	    CLK_CON_GAT_MUXGATE_CLKCMU_DISPAUD_DECON_INT_VCLK_USER, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_CLKPHY_DISPAUD_MIPIPHY_RXCLKESC0_USER, "gout_muxgate_clkphy_dispaud_mipiphy_rxclkesc0_user", "mout_clkphy_dispaud_mipiphy_rxclkesc0_user",
	    CLK_CON_GAT_MUXGATE_CLKPHY_DISPAUD_MIPIPHY_RXCLKESC0_USER, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_CLKPHY_DISPAUD_MIPIPHY_TXBYTECLKHS_USER, "gout_muxgate_clkphy_dispaud_mipiphy_txbyteclkhs_user", "mout_clkphy_dispaud_mipiphy_txbyteclkhs_user",
	    CLK_CON_GAT_MUXGATE_CLKPHY_DISPAUD_MIPIPHY_TXBYTECLKHS_USER, 21, CLK_IS_CRITICAL | CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_CLK_DISPAUD_DECON_INT_ECLK, "gout_muxgate_clk_dispaud_decon_int_eclk", "mout_clk_dispaud_decon_int_eclk",
	    CLK_CON_GAT_MUXGATE_CLK_DISPAUD_DECON_INT_ECLK, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_CLK_DISPAUD_DECON_INT_VCLK, "gout_muxgate_clk_dispaud_decon_int_vclk", "mout_clk_dispaud_decon_int_vclk",
	    CLK_CON_GAT_MUXGATE_CLK_DISPAUD_DECON_INT_VCLK, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_CLK_DISPAUD_MI2S, "gout_muxgate_clk_dispaud_mi2s", "mout_clk_dispaud_mi2s",
	    CLK_CON_GAT_MUXGATE_CLK_DISPAUD_MI2S, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_DISP_PLL, "gout_muxgate_disp_pll", "mout_disp_pll",
	    CLK_CON_GAT_DISPAUD_MUXGATE_DISP_PLL, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_MOUT_AUD_PLL, "mout_aud_pll", "fout_aud_pll",
	    CLK_CON_MUX_DISPAUD_MUX_AUD_PLL, 12, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_MOUT_CLKPHY_DISPAUD_MIPIPHY_RXCLKESC0_USER, "mout_clkphy_dispaud_mipiphy_rxclkesc0_user", "!!MISSING!!",
	    CLK_CON_MUX_MUX_CLKPHY_DISPAUD_MIPIPHY_RXCLKESC0_USER, 12, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_MOUT_CLKPHY_DISPAUD_MIPIPHY_TXBYTECLKHS_USER, "mout_clkphy_dispaud_mipiphy_txbyteclkhs_user", "!!MISSING!!",
	    CLK_CON_MUX_MUX_CLKPHY_DISPAUD_MIPIPHY_TXBYTECLKHS_USER, 12, CLK_IS_CRITICAL | CLK_SET_RATE_PARENT, 0),
	GATE(CLK_MOUT_DISP_PLL, "mout_disp_pll", "fout_disp_pll",
	    CLK_CON_MUX_DISPAUD_MUX_DISP_PLL, 12, CLK_SET_RATE_PARENT, 0),
};

static const struct samsung_cmu_info dispaud_cmu_info __initconst = {
	.pll_clks		= dispaud_pll_clks,
	.nr_pll_clks		= ARRAY_SIZE(dispaud_pll_clks),
	.mux_clks		= dispaud_mux_clks,
	.nr_mux_clks		= ARRAY_SIZE(dispaud_mux_clks),
	.div_clks		= dispaud_div_clks,
	.nr_div_clks		= ARRAY_SIZE(dispaud_div_clks),
	.gate_clks		= dispaud_gate_clks,
	.nr_gate_clks		= ARRAY_SIZE(dispaud_gate_clks),
	.nr_clk_ids		= DISPAUD_NR_CLK,
	.clk_regs		= dispaud_clk_regs,
	.nr_clk_regs		= ARRAY_SIZE(dispaud_clk_regs),
};

/* ---- CMU_FSYS ------------------------------------------------------------*/

/* Register Offset definitions for CMU_FSYS (0x13730000) */
#define PLL_LOCKTIME_USB_PLL							0x0000
#define PLL_CON0_USB_PLL							0x0100
#define CLK_CON_GAT_FSYS_MUXGATE_USB_PLL					0x0200
#define CLK_CON_MUX_FSYS_MUX_USB_PLL						0x0200
#define CLK_CON_GAT_MUXGATE_CLKPHY_FSYS_USB20DRD_PHYCLOCK_USER			0x0230
#define CLK_CON_MUX_MUX_CLKPHY_FSYS_USB20DRD_PHYCLOCK_USER			0x0230
#define CLK_CON_GAT_GATE_CLK_FSYS_UID_BUSP3_FSYS_IPCLKPORT_HCLK			0x0804
#define CLK_CON_GAT_GATE_CLK_FSYS_UID_MMC0_IPCLKPORT_I_ACLK			0x0804
#define CLK_CON_GAT_GATE_CLK_FSYS_UID_MMC1_IPCLKPORT_I_ACLK			0x0804
#define CLK_CON_GAT_GATE_CLK_FSYS_UID_MMC2_IPCLKPORT_I_ACLK			0x0804
#define CLK_CON_GAT_GATE_CLK_FSYS_UID_PDMA0_IPCLKPORT_ACLK_PDMA0		0x0804
#define CLK_CON_GAT_GATE_CLK_FSYS_UID_PPMU_FSYS_IPCLKPORT_ACLK			0x0804
#define CLK_CON_GAT_GATE_CLK_FSYS_UID_PPMU_FSYS_IPCLKPORT_PCLK			0x0804
#define CLK_CON_GAT_GATE_CLK_FSYS_UID_SROMC_IPCLKPORT_HCLK			0x0804
#define CLK_CON_GAT_GATE_CLK_FSYS_UID_UPSIZER_BUS1_FSYS_IPCLKPORT_ACLK		0x0804
#define CLK_CON_GAT_GATE_CLK_FSYS_UID_USB20DRD_IPCLKPORT_ACLK_HSDRD		0x0804
#define CLK_CON_GAT_GATE_CLK_FSYS_UID_USB20DRD_IPCLKPORT_HCLK_USB20_CTRL	0x0804
#define CLK_CON_GAT_GATE_CLK_FSYS_UID_USB20DRD_IPCLKPORT_HSDRD_REF_CLK		0x0828

static const unsigned long fsys_clk_regs[] __initconst = {
	PLL_LOCKTIME_USB_PLL,
	PLL_CON0_USB_PLL,
	CLK_CON_GAT_FSYS_MUXGATE_USB_PLL,
	CLK_CON_MUX_FSYS_MUX_USB_PLL,
	CLK_CON_GAT_MUXGATE_CLKPHY_FSYS_USB20DRD_PHYCLOCK_USER,
	CLK_CON_MUX_MUX_CLKPHY_FSYS_USB20DRD_PHYCLOCK_USER,
	CLK_CON_GAT_GATE_CLK_FSYS_UID_BUSP3_FSYS_IPCLKPORT_HCLK,
	CLK_CON_GAT_GATE_CLK_FSYS_UID_MMC0_IPCLKPORT_I_ACLK,
	CLK_CON_GAT_GATE_CLK_FSYS_UID_MMC1_IPCLKPORT_I_ACLK,
	CLK_CON_GAT_GATE_CLK_FSYS_UID_MMC2_IPCLKPORT_I_ACLK,
	CLK_CON_GAT_GATE_CLK_FSYS_UID_PDMA0_IPCLKPORT_ACLK_PDMA0,
	CLK_CON_GAT_GATE_CLK_FSYS_UID_PPMU_FSYS_IPCLKPORT_ACLK,
	CLK_CON_GAT_GATE_CLK_FSYS_UID_PPMU_FSYS_IPCLKPORT_PCLK,
	CLK_CON_GAT_GATE_CLK_FSYS_UID_SROMC_IPCLKPORT_HCLK,
	CLK_CON_GAT_GATE_CLK_FSYS_UID_UPSIZER_BUS1_FSYS_IPCLKPORT_ACLK,
	CLK_CON_GAT_GATE_CLK_FSYS_UID_USB20DRD_IPCLKPORT_ACLK_HSDRD,
	CLK_CON_GAT_GATE_CLK_FSYS_UID_USB20DRD_IPCLKPORT_HCLK_USB20_CTRL,
	CLK_CON_GAT_GATE_CLK_FSYS_UID_USB20DRD_IPCLKPORT_HSDRD_REF_CLK,
};

static const struct samsung_pll_clock fsys_pll_clks[] __initconst = {
	PLL(pll_1417x, CLK_FOUT_USB_PLL, "fout_usb_pll", "oscclk",
	    PLL_LOCKTIME_USB_PLL, PLL_CON0_USB_PLL,
	    NULL),
};

static const struct samsung_gate_clock fsys_gate_clks[] __initconst = {
	GATE(CLK_GOUT_CLK_FSYS_UID_BUSP3_FSYS_IPCLKPORT_HCLK, "gout_clk_fsys_uid_busp3_fsys_ipclkport_hclk", "gout_clkcmu_fsys_bus",
	    CLK_CON_GAT_GATE_CLK_FSYS_UID_BUSP3_FSYS_IPCLKPORT_HCLK, 2, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_FSYS_UID_MMC0_IPCLKPORT_I_ACLK, "gout_clk_fsys_uid_mmc0_ipclkport_i_aclk", "gout_clk_fsys_uid_busp3_fsys_ipclkport_hclk",
	    CLK_CON_GAT_GATE_CLK_FSYS_UID_MMC0_IPCLKPORT_I_ACLK, 8, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_FSYS_UID_MMC1_IPCLKPORT_I_ACLK, "gout_clk_fsys_uid_mmc1_ipclkport_i_aclk", "gout_clk_fsys_uid_busp3_fsys_ipclkport_hclk",
	    CLK_CON_GAT_GATE_CLK_FSYS_UID_MMC1_IPCLKPORT_I_ACLK, 9, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_FSYS_UID_MMC2_IPCLKPORT_I_ACLK, "gout_clk_fsys_uid_mmc2_ipclkport_i_aclk", "gout_clk_fsys_uid_busp3_fsys_ipclkport_hclk",
	    CLK_CON_GAT_GATE_CLK_FSYS_UID_MMC2_IPCLKPORT_I_ACLK, 10, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_FSYS_UID_PDMA0_IPCLKPORT_ACLK_PDMA0, "gout_clk_fsys_uid_pdma0_ipclkport_aclk_pdma0", "gout_clk_fsys_uid_upsizer_bus1_fsys_ipclkport_aclk",
	    CLK_CON_GAT_GATE_CLK_FSYS_UID_PDMA0_IPCLKPORT_ACLK_PDMA0, 7, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_FSYS_UID_PPMU_FSYS_IPCLKPORT_ACLK, "gout_clk_fsys_uid_ppmu_fsys_ipclkport_aclk", "gout_clk_fsys_uid_ppmu_fsys_ipclkport_pclk",
	    CLK_CON_GAT_GATE_CLK_FSYS_UID_PPMU_FSYS_IPCLKPORT_ACLK, 17, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_FSYS_UID_PPMU_FSYS_IPCLKPORT_PCLK, "gout_clk_fsys_uid_ppmu_fsys_ipclkport_pclk", "gout_clkcmu_fsys_bus",
	    CLK_CON_GAT_GATE_CLK_FSYS_UID_PPMU_FSYS_IPCLKPORT_PCLK, 18, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_FSYS_UID_SROMC_IPCLKPORT_HCLK, "gout_clk_fsys_uid_sromc_ipclkport_hclk", "gout_clk_fsys_uid_busp3_fsys_ipclkport_hclk",
	    CLK_CON_GAT_GATE_CLK_FSYS_UID_SROMC_IPCLKPORT_HCLK, 6, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_FSYS_UID_UPSIZER_BUS1_FSYS_IPCLKPORT_ACLK, "gout_clk_fsys_uid_upsizer_bus1_fsys_ipclkport_aclk", "gout_clkcmu_fsys_bus",
	    CLK_CON_GAT_GATE_CLK_FSYS_UID_UPSIZER_BUS1_FSYS_IPCLKPORT_ACLK, 12, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_FSYS_UID_USB20DRD_IPCLKPORT_ACLK_HSDRD, "gout_clk_fsys_uid_usb20drd_ipclkport_aclk_hsdrd", "gout_clk_fsys_uid_busp3_fsys_ipclkport_hclk",
	    CLK_CON_GAT_GATE_CLK_FSYS_UID_USB20DRD_IPCLKPORT_ACLK_HSDRD, 20, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_FSYS_UID_USB20DRD_IPCLKPORT_HCLK_USB20_CTRL, "gout_clk_fsys_uid_usb20drd_ipclkport_hclk_usb20_ctrl", "gout_clk_fsys_uid_busp3_fsys_ipclkport_hclk",
	    CLK_CON_GAT_GATE_CLK_FSYS_UID_USB20DRD_IPCLKPORT_HCLK_USB20_CTRL, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_FSYS_UID_USB20DRD_IPCLKPORT_HSDRD_REF_CLK, "gout_clk_fsys_uid_usb20drd_ipclkport_hsdrd_ref_clk", "gout_clkcmu_fsys_usb20drd_refclk",
	    CLK_CON_GAT_GATE_CLK_FSYS_UID_USB20DRD_IPCLKPORT_HSDRD_REF_CLK, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_CLKPHY_FSYS_USB20DRD_PHYCLOCK_USER, "gout_muxgate_clkphy_fsys_usb20drd_phyclock_user", "mout_clkphy_fsys_usb20drd_phyclock_user",
	    CLK_CON_GAT_MUXGATE_CLKPHY_FSYS_USB20DRD_PHYCLOCK_USER, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_USB_PLL, "gout_muxgate_usb_pll", "mout_usb_pll",
	    CLK_CON_GAT_FSYS_MUXGATE_USB_PLL, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_MOUT_CLKPHY_FSYS_USB20DRD_PHYCLOCK_USER, "mout_clkphy_fsys_usb20drd_phyclock_user", "!!MISSING!!",
	    CLK_CON_MUX_MUX_CLKPHY_FSYS_USB20DRD_PHYCLOCK_USER, 12, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_MOUT_USB_PLL, "mout_usb_pll", "fout_usb_pll",
	    CLK_CON_MUX_FSYS_MUX_USB_PLL, 12, CLK_SET_RATE_PARENT, 0),
};

static const struct samsung_cmu_info fsys_cmu_info __initconst = {
	.pll_clks		= fsys_pll_clks,
	.nr_pll_clks		= ARRAY_SIZE(fsys_pll_clks),
	.gate_clks		= fsys_gate_clks,
	.nr_gate_clks		= ARRAY_SIZE(fsys_gate_clks),
	.nr_clk_ids		= FSYS_NR_CLK,
	.clk_regs		= fsys_clk_regs,
	.nr_clk_regs		= ARRAY_SIZE(fsys_clk_regs),
};

/* ---- CMU_G3D -------------------------------------------------------------*/

/* Register Offset definitions for CMU_G3D (0x11460000) */
#define PLL_LOCKTIME_G3D_PLL						0x0000
#define PLL_CON0_G3D_PLL						0x0100
#define CLK_CON_GAT_MUXGATE_G3D_PLL					0x0200
#define CLK_CON_MUX_MUX_G3D_PLL						0x0200
#define CLK_CON_GAT_MUXGATE_CLKCMU_G3D_SWITCH_USER			0x0204
#define CLK_CON_MUX_MUX_CLKCMU_G3D_SWITCH_USER				0x0204
#define CLK_CON_GAT_G3D_MUXGATE_CLK_G3D					0x0208
#define CLK_CON_MUX_G3D_MUX_CLK_G3D					0x0208
#define CLK_CON_DIV_DIV_CLK_G3D_BUS					0x0400
#define CLK_CON_DIV_DIV_CLK_G3D_APB					0x0404
#define CLK_CON_GAT_GATE_CLK_G3D_UID_ASYNCS_D0_G3D_IPCLKPORT_I_CLK	0x0804
#define CLK_CON_GAT_GATE_CLK_G3D_UID_ASYNC_G3D_P_IPCLKPORT_PCLKM	0x0804
#define CLK_CON_GAT_GATE_CLK_G3D_UID_G3D_IPCLKPORT_CLK			0x0804
#define CLK_CON_GAT_GATE_CLK_G3D_UID_PPMU_G3D_IPCLKPORT_ACLK		0x0804
#define CLK_CON_GAT_GATE_CLK_G3D_UID_QE_G3D_IPCLKPORT_ACLK		0x0804
#define CLK_CON_GAT_GATE_CLK_G3D_UID_PPMU_G3D_IPCLKPORT_PCLK		0x0808
#define CLK_CON_GAT_GATE_CLK_G3D_UID_QE_G3D_IPCLKPORT_PCLK		0x0808
#define CLK_CON_GAT_GATE_CLK_G3D_UID_SYSREG_G3D_IPCLKPORT_PCLK		0x0808

static const unsigned long g3d_clk_regs[] __initconst = {
	PLL_LOCKTIME_G3D_PLL,
	PLL_CON0_G3D_PLL,
	CLK_CON_GAT_MUXGATE_G3D_PLL,
	CLK_CON_MUX_MUX_G3D_PLL,
	CLK_CON_GAT_MUXGATE_CLKCMU_G3D_SWITCH_USER,
	CLK_CON_MUX_MUX_CLKCMU_G3D_SWITCH_USER,
	CLK_CON_GAT_G3D_MUXGATE_CLK_G3D,
	CLK_CON_MUX_G3D_MUX_CLK_G3D,
	CLK_CON_DIV_DIV_CLK_G3D_BUS,
	CLK_CON_DIV_DIV_CLK_G3D_APB,
	CLK_CON_GAT_GATE_CLK_G3D_UID_ASYNCS_D0_G3D_IPCLKPORT_I_CLK,
	CLK_CON_GAT_GATE_CLK_G3D_UID_ASYNC_G3D_P_IPCLKPORT_PCLKM,
	CLK_CON_GAT_GATE_CLK_G3D_UID_G3D_IPCLKPORT_CLK,
	CLK_CON_GAT_GATE_CLK_G3D_UID_PPMU_G3D_IPCLKPORT_ACLK,
	CLK_CON_GAT_GATE_CLK_G3D_UID_QE_G3D_IPCLKPORT_ACLK,
	CLK_CON_GAT_GATE_CLK_G3D_UID_PPMU_G3D_IPCLKPORT_PCLK,
	CLK_CON_GAT_GATE_CLK_G3D_UID_QE_G3D_IPCLKPORT_PCLK,
	CLK_CON_GAT_GATE_CLK_G3D_UID_SYSREG_G3D_IPCLKPORT_PCLK,
};

static const struct samsung_pll_clock g3d_pll_clks[] __initconst = {
	PLL(pll_1417x, CLK_FOUT_G3D_PLL, "fout_g3d_pll", "oscclk",
	    PLL_LOCKTIME_G3D_PLL, PLL_CON0_G3D_PLL,
	    NULL),
};

/* List of parent clocks for Muxes in CMU_G3D */
PNAME(mout_clkcmu_g3d_switch_user_p)	= { "oscclk", "gout_clkcmu_g3d_switch" };
PNAME(mout_clk_g3d_p)			= { "gout_muxgate_g3d_pll", "gout_muxgate_clkcmu_g3d_switch_user" };

static const struct samsung_mux_clock g3d_mux_clks[] __initconst = {
	MUX(CLK_MOUT_CLKCMU_G3D_SWITCH_USER, "mout_clkcmu_g3d_switch_user", mout_clkcmu_g3d_switch_user_p,
	    CLK_CON_MUX_MUX_CLKCMU_G3D_SWITCH_USER, 12, 1),
	MUX(CLK_MOUT_CLK_G3D, "mout_clk_g3d", mout_clk_g3d_p,
	    CLK_CON_MUX_G3D_MUX_CLK_G3D, 12, 1),
};

static const struct samsung_div_clock g3d_div_clks[] __initconst = {
	DIV(CLK_DOUT_CLK_G3D_APB, "dout_clk_g3d_apb", "dout_clk_g3d_bus",
	    CLK_CON_DIV_DIV_CLK_G3D_APB, 0, 3),
	DIV(CLK_DOUT_CLK_G3D_BUS, "dout_clk_g3d_bus", "gout_muxgate_clk_g3d",
	    CLK_CON_DIV_DIV_CLK_G3D_BUS, 0, 3),
};

static const struct samsung_gate_clock g3d_gate_clks[] __initconst = {
	GATE(CLK_GOUT_CLK_G3D_UID_ASYNCS_D0_G3D_IPCLKPORT_I_CLK, "gout_clk_g3d_uid_asyncs_d0_g3d_ipclkport_i_clk", "dout_clk_g3d_bus",
	    CLK_CON_GAT_GATE_CLK_G3D_UID_ASYNCS_D0_G3D_IPCLKPORT_I_CLK, 1, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_G3D_UID_ASYNC_G3D_P_IPCLKPORT_PCLKM, "gout_clk_g3d_uid_async_g3d_p_ipclkport_pclkm", "dout_clk_g3d_bus",
	    CLK_CON_GAT_GATE_CLK_G3D_UID_ASYNC_G3D_P_IPCLKPORT_PCLKM, 0, CLK_IS_CRITICAL | CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_G3D_UID_G3D_IPCLKPORT_CLK, "gout_clk_g3d_uid_g3d_ipclkport_clk", "dout_clk_g3d_bus",
	    CLK_CON_GAT_GATE_CLK_G3D_UID_G3D_IPCLKPORT_CLK, 6, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_G3D_UID_PPMU_G3D_IPCLKPORT_ACLK, "gout_clk_g3d_uid_ppmu_g3d_ipclkport_aclk", "dout_clk_g3d_bus",
	    CLK_CON_GAT_GATE_CLK_G3D_UID_PPMU_G3D_IPCLKPORT_ACLK, 7, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_G3D_UID_PPMU_G3D_IPCLKPORT_PCLK, "gout_clk_g3d_uid_ppmu_g3d_ipclkport_pclk", "dout_clk_g3d_apb",
	    CLK_CON_GAT_GATE_CLK_G3D_UID_PPMU_G3D_IPCLKPORT_PCLK, 4, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_G3D_UID_QE_G3D_IPCLKPORT_ACLK, "gout_clk_g3d_uid_qe_g3d_ipclkport_aclk", "dout_clk_g3d_bus",
	    CLK_CON_GAT_GATE_CLK_G3D_UID_QE_G3D_IPCLKPORT_ACLK, 8, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_G3D_UID_QE_G3D_IPCLKPORT_PCLK, "gout_clk_g3d_uid_qe_g3d_ipclkport_pclk", "dout_clk_g3d_apb",
	    CLK_CON_GAT_GATE_CLK_G3D_UID_QE_G3D_IPCLKPORT_PCLK, 5, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_G3D_UID_SYSREG_G3D_IPCLKPORT_PCLK, "gout_clk_g3d_uid_sysreg_g3d_ipclkport_pclk", "dout_clk_g3d_apb",
	    CLK_CON_GAT_GATE_CLK_G3D_UID_SYSREG_G3D_IPCLKPORT_PCLK, 6, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_CLKCMU_G3D_SWITCH_USER, "gout_muxgate_clkcmu_g3d_switch_user", "mout_clkcmu_g3d_switch_user",
	    CLK_CON_GAT_MUXGATE_CLKCMU_G3D_SWITCH_USER, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_CLK_G3D, "gout_muxgate_clk_g3d", "mout_clk_g3d",
	    CLK_CON_GAT_G3D_MUXGATE_CLK_G3D, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_G3D_PLL, "gout_muxgate_g3d_pll", "mout_g3d_pll",
	    CLK_CON_GAT_MUXGATE_G3D_PLL, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_MOUT_G3D_PLL, "mout_g3d_pll", "fout_g3d_pll",
	    CLK_CON_MUX_MUX_G3D_PLL, 12, CLK_SET_RATE_PARENT, 0),
};

static const struct samsung_cmu_info g3d_cmu_info __initconst = {
	.pll_clks		= g3d_pll_clks,
	.nr_pll_clks		= ARRAY_SIZE(g3d_pll_clks),
	.mux_clks		= g3d_mux_clks,
	.nr_mux_clks		= ARRAY_SIZE(g3d_mux_clks),
	.div_clks		= g3d_div_clks,
	.nr_div_clks		= ARRAY_SIZE(g3d_div_clks),
	.gate_clks		= g3d_gate_clks,
	.nr_gate_clks		= ARRAY_SIZE(g3d_gate_clks),
	.nr_clk_ids		= G3D_NR_CLK,
	.clk_regs		= g3d_clk_regs,
	.nr_clk_regs		= ARRAY_SIZE(g3d_clk_regs),
};

/* ---- CMU_ISP -------------------------------------------------------------*/

/* Register Offset definitions for CMU_ISP (0x144d0000) */
#define PLL_LOCKTIME_ISP_PLL					0x0000
#define PLL_CON0_ISP_PLL					0x0100
#define CLK_CON_GAT_MUXGATE_ISP_PLL				0x0200
#define CLK_CON_MUX_MUX_ISP_PLL					0x0200
#define CLK_CON_GAT_MUXGATE_CLKCMU_ISP_VRA_USER			0x0210
#define CLK_CON_MUX_MUX_CLKCMU_ISP_VRA_USER			0x0210
#define CLK_CON_GAT_MUXGATE_CLKCMU_ISP_CAM_USER			0x0214
#define CLK_CON_MUX_MUX_CLKCMU_ISP_CAM_USER			0x0214
#define CLK_CON_GAT_MUXGATE_CLKCMU_ISP_ISP_USER			0x0218
#define CLK_CON_MUX_MUX_CLKCMU_ISP_ISP_USER			0x0218
#define CLK_CON_GAT_MUXGATE_CLK_ISP_VRA				0x0220
#define CLK_CON_MUX_MUX_CLK_ISP_VRA				0x0220
#define CLK_CON_GAT_MUXGATE_CLK_ISP_CAM				0x0224
#define CLK_CON_MUX_MUX_CLK_ISP_CAM				0x0224
#define CLK_CON_GAT_MUXGATE_CLK_ISP_ISP				0x0228
#define CLK_CON_MUX_MUX_CLK_ISP_ISP				0x0228
#define CLK_CON_GAT_MUXGATE_CLK_ISP_ISPD			0x022c
#define CLK_CON_MUX_MUX_CLK_ISP_ISPD				0x022c
#define CLK_CON_GAT_MUXGATE_CLKPHY_ISP_S_RXBYTECLKHS0_S4_USER	0x0230
#define CLK_CON_MUX_MUX_CLKPHY_ISP_S_RXBYTECLKHS0_S4_USER	0x0230
#define CLK_CON_GAT_MUXGATE_CLKPHY_ISP_S_RXBYTECLKHS0_S4S_USER	0x0234
#define CLK_CON_MUX_MUX_CLKPHY_ISP_S_RXBYTECLKHS0_S4S_USER	0x0234
#define CLK_CON_DIV_DIV_CLK_ISP_APB				0x0400
#define CLK_CON_DIV_DIV_CLK_ISP_CAM_HALF			0x0404
#define CLK_CON_GAT_GATE_CLK_ISP_UID_CLK_ISP_VRA		0x0810
#define CLK_CON_GAT_GATE_CLK_ISP_UID_CLK_ISP_ISPD		0x0818
#define CLK_CON_GAT_GATE_CLK_ISP_UID_CLK_ISP_ISPD_PPMU		0x0818
#define CLK_CON_GAT_GATE_CLK_ISP_UID_CLK_ISP_CAM		0x081c
#define CLK_CON_GAT_GATE_CLK_ISP_UID_CLK_ISP_CAM_HALF		0x0820

static const unsigned long isp_clk_regs[] __initconst = {
	PLL_LOCKTIME_ISP_PLL,
	PLL_CON0_ISP_PLL,
	CLK_CON_GAT_MUXGATE_ISP_PLL,
	CLK_CON_MUX_MUX_ISP_PLL,
	CLK_CON_GAT_MUXGATE_CLKCMU_ISP_VRA_USER,
	CLK_CON_MUX_MUX_CLKCMU_ISP_VRA_USER,
	CLK_CON_GAT_MUXGATE_CLKCMU_ISP_CAM_USER,
	CLK_CON_MUX_MUX_CLKCMU_ISP_CAM_USER,
	CLK_CON_GAT_MUXGATE_CLKCMU_ISP_ISP_USER,
	CLK_CON_MUX_MUX_CLKCMU_ISP_ISP_USER,
	CLK_CON_GAT_MUXGATE_CLK_ISP_VRA,
	CLK_CON_MUX_MUX_CLK_ISP_VRA,
	CLK_CON_GAT_MUXGATE_CLK_ISP_CAM,
	CLK_CON_MUX_MUX_CLK_ISP_CAM,
	CLK_CON_GAT_MUXGATE_CLK_ISP_ISP,
	CLK_CON_MUX_MUX_CLK_ISP_ISP,
	CLK_CON_GAT_MUXGATE_CLK_ISP_ISPD,
	CLK_CON_MUX_MUX_CLK_ISP_ISPD,
	CLK_CON_GAT_MUXGATE_CLKPHY_ISP_S_RXBYTECLKHS0_S4_USER,
	CLK_CON_MUX_MUX_CLKPHY_ISP_S_RXBYTECLKHS0_S4_USER,
	CLK_CON_GAT_MUXGATE_CLKPHY_ISP_S_RXBYTECLKHS0_S4S_USER,
	CLK_CON_MUX_MUX_CLKPHY_ISP_S_RXBYTECLKHS0_S4S_USER,
	CLK_CON_DIV_DIV_CLK_ISP_APB,
	CLK_CON_DIV_DIV_CLK_ISP_CAM_HALF,
	CLK_CON_GAT_GATE_CLK_ISP_UID_CLK_ISP_VRA,
	CLK_CON_GAT_GATE_CLK_ISP_UID_CLK_ISP_ISPD,
	CLK_CON_GAT_GATE_CLK_ISP_UID_CLK_ISP_ISPD_PPMU,
	CLK_CON_GAT_GATE_CLK_ISP_UID_CLK_ISP_CAM,
	CLK_CON_GAT_GATE_CLK_ISP_UID_CLK_ISP_CAM_HALF,
};

static const struct samsung_pll_clock isp_pll_clks[] __initconst = {
	PLL(pll_1417x, CLK_FOUT_ISP_PLL, "fout_isp_pll", "oscclk",
	    PLL_LOCKTIME_ISP_PLL, PLL_CON0_ISP_PLL,
	    NULL),
};

/* List of parent clocks for Muxes in CMU_ISP */
PNAME(mout_clkcmu_isp_cam_user_p)	= { "oscclk", "gout_clkcmu_isp_cam" };
PNAME(mout_clkcmu_isp_isp_user_p)	= { "oscclk", "gout_clkcmu_isp_isp" };
PNAME(mout_clkcmu_isp_vra_user_p)	= { "oscclk", "gout_clkcmu_isp_vra" };
PNAME(mout_clk_isp_cam_p)		= { "gout_muxgate_clkcmu_isp_cam_user", "gout_muxgate_isp_pll" };
PNAME(mout_clk_isp_isp_p)		= { "gout_muxgate_clkcmu_isp_isp_user", "gout_muxgate_isp_pll" };
PNAME(mout_clk_isp_ispd_p)		= { "gout_muxgate_clk_isp_vra", "gout_muxgate_clk_isp_cam" };
PNAME(mout_clk_isp_vra_p)		= { "gout_muxgate_clkcmu_isp_vra_user", "gout_muxgate_isp_pll" };

static const struct samsung_mux_clock isp_mux_clks[] __initconst = {
	MUX(CLK_MOUT_CLKCMU_ISP_CAM_USER, "mout_clkcmu_isp_cam_user", mout_clkcmu_isp_cam_user_p,
	    CLK_CON_MUX_MUX_CLKCMU_ISP_CAM_USER, 12, 1),
	MUX(CLK_MOUT_CLKCMU_ISP_ISP_USER, "mout_clkcmu_isp_isp_user", mout_clkcmu_isp_isp_user_p,
	    CLK_CON_MUX_MUX_CLKCMU_ISP_ISP_USER, 12, 1),
	MUX(CLK_MOUT_CLKCMU_ISP_VRA_USER, "mout_clkcmu_isp_vra_user", mout_clkcmu_isp_vra_user_p,
	    CLK_CON_MUX_MUX_CLKCMU_ISP_VRA_USER, 12, 1),
	MUX(CLK_MOUT_CLK_ISP_CAM, "mout_clk_isp_cam", mout_clk_isp_cam_p,
	    CLK_CON_MUX_MUX_CLK_ISP_CAM, 12, 1),
	MUX(CLK_MOUT_CLK_ISP_ISP, "mout_clk_isp_isp", mout_clk_isp_isp_p,
	    CLK_CON_MUX_MUX_CLK_ISP_ISP, 12, 1),
	MUX(CLK_MOUT_CLK_ISP_ISPD, "mout_clk_isp_ispd", mout_clk_isp_ispd_p,
	    CLK_CON_MUX_MUX_CLK_ISP_ISPD, 12, 1),
	MUX(CLK_MOUT_CLK_ISP_VRA, "mout_clk_isp_vra", mout_clk_isp_vra_p,
	    CLK_CON_MUX_MUX_CLK_ISP_VRA, 12, 1),
};

static const struct samsung_div_clock isp_div_clks[] __initconst = {
	DIV(CLK_DOUT_CLK_ISP_APB, "dout_clk_isp_apb", "gout_muxgate_clk_isp_vra",
	    CLK_CON_DIV_DIV_CLK_ISP_APB, 0, 2),
	DIV(CLK_DOUT_CLK_ISP_CAM_HALF, "dout_clk_isp_cam_half", "gout_muxgate_clk_isp_cam",
	    CLK_CON_DIV_DIV_CLK_ISP_CAM_HALF, 0, 2),
};

static const struct samsung_gate_clock isp_gate_clks[] __initconst = {
	GATE(CLK_GOUT_CLK_ISP_UID_CLK_ISP_CAM, "gout_clk_isp_uid_clk_isp_cam", "gout_muxgate_clk_isp_cam",
	    CLK_CON_GAT_GATE_CLK_ISP_UID_CLK_ISP_CAM, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_ISP_UID_CLK_ISP_CAM_HALF, "gout_clk_isp_uid_clk_isp_cam_half", "dout_clk_isp_cam_half",
	    CLK_CON_GAT_GATE_CLK_ISP_UID_CLK_ISP_CAM_HALF, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_ISP_UID_CLK_ISP_ISPD, "gout_clk_isp_uid_clk_isp_ispd", "gout_muxgate_clk_isp_ispd",
	    CLK_CON_GAT_GATE_CLK_ISP_UID_CLK_ISP_ISPD, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_ISP_UID_CLK_ISP_ISPD_PPMU, "gout_clk_isp_uid_clk_isp_ispd_ppmu", "gout_muxgate_clk_isp_ispd",
	    CLK_CON_GAT_GATE_CLK_ISP_UID_CLK_ISP_ISPD_PPMU, 1, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_ISP_UID_CLK_ISP_VRA, "gout_clk_isp_uid_clk_isp_vra", "gout_muxgate_clk_isp_vra",
	    CLK_CON_GAT_GATE_CLK_ISP_UID_CLK_ISP_VRA, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_CLKCMU_ISP_CAM_USER, "gout_muxgate_clkcmu_isp_cam_user", "mout_clkcmu_isp_cam_user",
	    CLK_CON_GAT_MUXGATE_CLKCMU_ISP_CAM_USER, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_CLKCMU_ISP_ISP_USER, "gout_muxgate_clkcmu_isp_isp_user", "mout_clkcmu_isp_isp_user",
	    CLK_CON_GAT_MUXGATE_CLKCMU_ISP_ISP_USER, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_CLKCMU_ISP_VRA_USER, "gout_muxgate_clkcmu_isp_vra_user", "mout_clkcmu_isp_vra_user",
	    CLK_CON_GAT_MUXGATE_CLKCMU_ISP_VRA_USER, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_CLKPHY_ISP_S_RXBYTECLKHS0_S4S_USER, "gout_muxgate_clkphy_isp_s_rxbyteclkhs0_s4s_user", "mout_clkphy_isp_s_rxbyteclkhs0_s4s_user",
	    CLK_CON_GAT_MUXGATE_CLKPHY_ISP_S_RXBYTECLKHS0_S4S_USER, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_CLKPHY_ISP_S_RXBYTECLKHS0_S4_USER, "gout_muxgate_clkphy_isp_s_rxbyteclkhs0_s4_user", "mout_clkphy_isp_s_rxbyteclkhs0_s4_user",
	    CLK_CON_GAT_MUXGATE_CLKPHY_ISP_S_RXBYTECLKHS0_S4_USER, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_CLK_ISP_CAM, "gout_muxgate_clk_isp_cam", "mout_clk_isp_cam",
	    CLK_CON_GAT_MUXGATE_CLK_ISP_CAM, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_CLK_ISP_ISP, "gout_muxgate_clk_isp_isp", "mout_clk_isp_isp",
	    CLK_CON_GAT_MUXGATE_CLK_ISP_ISP, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_CLK_ISP_ISPD, "gout_muxgate_clk_isp_ispd", "mout_clk_isp_ispd",
	    CLK_CON_GAT_MUXGATE_CLK_ISP_ISPD, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_CLK_ISP_VRA, "gout_muxgate_clk_isp_vra", "mout_clk_isp_vra",
	    CLK_CON_GAT_MUXGATE_CLK_ISP_VRA, 21, CLK_IS_CRITICAL | CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_ISP_PLL, "gout_muxgate_isp_pll", "mout_isp_pll",
	    CLK_CON_GAT_MUXGATE_ISP_PLL, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_MOUT_CLKPHY_ISP_S_RXBYTECLKHS0_S4S_USER, "mout_clkphy_isp_s_rxbyteclkhs0_s4s_user", "!!MISSING!!",
	    CLK_CON_MUX_MUX_CLKPHY_ISP_S_RXBYTECLKHS0_S4S_USER, 12, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_MOUT_CLKPHY_ISP_S_RXBYTECLKHS0_S4_USER, "mout_clkphy_isp_s_rxbyteclkhs0_s4_user", "!!MISSING!!",
	    CLK_CON_MUX_MUX_CLKPHY_ISP_S_RXBYTECLKHS0_S4_USER, 12, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_MOUT_ISP_PLL, "mout_isp_pll", "fout_isp_pll",
	    CLK_CON_MUX_MUX_ISP_PLL, 12, CLK_SET_RATE_PARENT, 0),
};

static const struct samsung_cmu_info isp_cmu_info __initconst = {
	.pll_clks		= isp_pll_clks,
	.nr_pll_clks		= ARRAY_SIZE(isp_pll_clks),
	.mux_clks		= isp_mux_clks,
	.nr_mux_clks		= ARRAY_SIZE(isp_mux_clks),
	.div_clks		= isp_div_clks,
	.nr_div_clks		= ARRAY_SIZE(isp_div_clks),
	.gate_clks		= isp_gate_clks,
	.nr_gate_clks		= ARRAY_SIZE(isp_gate_clks),
	.nr_clk_ids		= ISP_NR_CLK,
	.clk_regs		= isp_clk_regs,
	.nr_clk_regs		= ARRAY_SIZE(isp_clk_regs),
};

/* ---- CMU_MFCMSCL ---------------------------------------------------------*/

/* Register Offset definitions for CMU_MFCMSCL (0x12cb0000) */
#define CLK_CON_GAT_MUXGATE_CLKCMU_MFCMSCL_MSCL_USER			0x0200
#define CLK_CON_MUX_MUX_CLKCMU_MFCMSCL_MSCL_USER			0x0200
#define CLK_CON_GAT_MUXGATE_CLKCMU_MFCMSCL_MFC_USER			0x0204
#define CLK_CON_MUX_MUX_CLKCMU_MFCMSCL_MFC_USER				0x0204
#define CLK_CON_DIV_DIV_CLK_MFCMSCL_APB					0x0400
#define CLK_CON_GAT_GATE_CLK_MFCMSCL_UID_CLKCMU_MFCMSCL_MSCL		0x0804
#define CLK_CON_GAT_GATE_CLK_MFCMSCL_UID_CLKCMU_MFCMSCL_MSCL_BI		0x0804
#define CLK_CON_GAT_GATE_CLK_MFCMSCL_UID_CLKCMU_MFCMSCL_MSCL_D		0x0804
#define CLK_CON_GAT_GATE_CLK_MFCMSCL_UID_CLKCMU_MFCMSCL_MSCL_JPEG	0x0804
#define CLK_CON_GAT_GATE_CLK_MFCMSCL_UID_CLKCMU_MFCMSCL_MSCL_POLY	0x0804
#define CLK_CON_GAT_GATE_CLK_MFCMSCL_UID_CLKCMU_MFCMSCL_MSCL_PPMU	0x0804
#define CLK_CON_GAT_GATE_CLK_MFCMSCL_UID_CLKCMU_MFCMSCL_MFC		0x0808

static const unsigned long mfcmscl_clk_regs[] __initconst = {
	CLK_CON_GAT_MUXGATE_CLKCMU_MFCMSCL_MSCL_USER,
	CLK_CON_MUX_MUX_CLKCMU_MFCMSCL_MSCL_USER,
	CLK_CON_GAT_MUXGATE_CLKCMU_MFCMSCL_MFC_USER,
	CLK_CON_MUX_MUX_CLKCMU_MFCMSCL_MFC_USER,
	CLK_CON_DIV_DIV_CLK_MFCMSCL_APB,
	CLK_CON_GAT_GATE_CLK_MFCMSCL_UID_CLKCMU_MFCMSCL_MSCL,
	CLK_CON_GAT_GATE_CLK_MFCMSCL_UID_CLKCMU_MFCMSCL_MSCL_BI,
	CLK_CON_GAT_GATE_CLK_MFCMSCL_UID_CLKCMU_MFCMSCL_MSCL_D,
	CLK_CON_GAT_GATE_CLK_MFCMSCL_UID_CLKCMU_MFCMSCL_MSCL_JPEG,
	CLK_CON_GAT_GATE_CLK_MFCMSCL_UID_CLKCMU_MFCMSCL_MSCL_POLY,
	CLK_CON_GAT_GATE_CLK_MFCMSCL_UID_CLKCMU_MFCMSCL_MSCL_PPMU,
	CLK_CON_GAT_GATE_CLK_MFCMSCL_UID_CLKCMU_MFCMSCL_MFC,
};

/* List of parent clocks for Muxes in CMU_MFCMSCL */
PNAME(mout_clkcmu_mfcmscl_mfc_user_p)		= { "oscclk", "gout_clkcmu_mfcmscl_mfc" };
PNAME(mout_clkcmu_mfcmscl_mscl_user_p)		= { "oscclk", "gout_clkcmu_mfcmscl_mscl" };

static const struct samsung_mux_clock mfcmscl_mux_clks[] __initconst = {
	MUX(CLK_MOUT_CLKCMU_MFCMSCL_MFC_USER, "mout_clkcmu_mfcmscl_mfc_user", mout_clkcmu_mfcmscl_mfc_user_p,
	    CLK_CON_MUX_MUX_CLKCMU_MFCMSCL_MFC_USER, 12, 1),
	MUX(CLK_MOUT_CLKCMU_MFCMSCL_MSCL_USER, "mout_clkcmu_mfcmscl_mscl_user", mout_clkcmu_mfcmscl_mscl_user_p,
	    CLK_CON_MUX_MUX_CLKCMU_MFCMSCL_MSCL_USER, 12, 1),
};

static const struct samsung_div_clock mfcmscl_div_clks[] __initconst = {
	DIV(CLK_DOUT_CLK_MFCMSCL_APB, "dout_clk_mfcmscl_apb", "gout_muxgate_clkcmu_mfcmscl_mscl_user",
	    CLK_CON_DIV_DIV_CLK_MFCMSCL_APB, 0, 2),
};

static const struct samsung_gate_clock mfcmscl_gate_clks[] __initconst = {
	GATE(CLK_GOUT_CLK_MFCMSCL_UID_CLKCMU_MFCMSCL_MFC, "gout_clk_mfcmscl_uid_clkcmu_mfcmscl_mfc", "gout_muxgate_clkcmu_mfcmscl_mfc_user",
	    CLK_CON_GAT_GATE_CLK_MFCMSCL_UID_CLKCMU_MFCMSCL_MFC, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_MFCMSCL_UID_CLKCMU_MFCMSCL_MSCL, "gout_clk_mfcmscl_uid_clkcmu_mfcmscl_mscl", "gout_muxgate_clkcmu_mfcmscl_mscl_user",
	    CLK_CON_GAT_GATE_CLK_MFCMSCL_UID_CLKCMU_MFCMSCL_MSCL, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_MFCMSCL_UID_CLKCMU_MFCMSCL_MSCL_BI, "gout_clk_mfcmscl_uid_clkcmu_mfcmscl_mscl_bi", "gout_clk_mfcmscl_uid_clkcmu_mfcmscl_mscl_d",
	    CLK_CON_GAT_GATE_CLK_MFCMSCL_UID_CLKCMU_MFCMSCL_MSCL_BI, 4, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_MFCMSCL_UID_CLKCMU_MFCMSCL_MSCL_D, "gout_clk_mfcmscl_uid_clkcmu_mfcmscl_mscl_d", "gout_muxgate_clkcmu_mfcmscl_mscl_user",
	    CLK_CON_GAT_GATE_CLK_MFCMSCL_UID_CLKCMU_MFCMSCL_MSCL_D, 1, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_MFCMSCL_UID_CLKCMU_MFCMSCL_MSCL_JPEG, "gout_clk_mfcmscl_uid_clkcmu_mfcmscl_mscl_jpeg", "gout_clk_mfcmscl_uid_clkcmu_mfcmscl_mscl_d",
	    CLK_CON_GAT_GATE_CLK_MFCMSCL_UID_CLKCMU_MFCMSCL_MSCL_JPEG, 2, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_MFCMSCL_UID_CLKCMU_MFCMSCL_MSCL_POLY, "gout_clk_mfcmscl_uid_clkcmu_mfcmscl_mscl_poly", "gout_clk_mfcmscl_uid_clkcmu_mfcmscl_mscl_d",
	    CLK_CON_GAT_GATE_CLK_MFCMSCL_UID_CLKCMU_MFCMSCL_MSCL_POLY, 3, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_MFCMSCL_UID_CLKCMU_MFCMSCL_MSCL_PPMU, "gout_clk_mfcmscl_uid_clkcmu_mfcmscl_mscl_ppmu", "gout_muxgate_clkcmu_mfcmscl_mscl_user",
	    CLK_CON_GAT_GATE_CLK_MFCMSCL_UID_CLKCMU_MFCMSCL_MSCL_PPMU, 5, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_CLKCMU_MFCMSCL_MFC_USER, "gout_muxgate_clkcmu_mfcmscl_mfc_user", "mout_clkcmu_mfcmscl_mfc_user",
	    CLK_CON_GAT_MUXGATE_CLKCMU_MFCMSCL_MFC_USER, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_MUXGATE_CLKCMU_MFCMSCL_MSCL_USER, "gout_muxgate_clkcmu_mfcmscl_mscl_user", "mout_clkcmu_mfcmscl_mscl_user",
	    CLK_CON_GAT_MUXGATE_CLKCMU_MFCMSCL_MSCL_USER, 21, CLK_IS_CRITICAL | CLK_SET_RATE_PARENT, 0),
};

static const struct samsung_cmu_info mfcmscl_cmu_info __initconst = {
	.mux_clks		= mfcmscl_mux_clks,
	.nr_mux_clks		= ARRAY_SIZE(mfcmscl_mux_clks),
	.div_clks		= mfcmscl_div_clks,
	.nr_div_clks		= ARRAY_SIZE(mfcmscl_div_clks),
	.gate_clks		= mfcmscl_gate_clks,
	.nr_gate_clks		= ARRAY_SIZE(mfcmscl_gate_clks),
	.nr_clk_ids		= MFCMSCL_NR_CLK,
	.clk_regs		= mfcmscl_clk_regs,
	.nr_clk_regs		= ARRAY_SIZE(mfcmscl_clk_regs),
};

/* ---- CMU_PERI ------------------------------------------------------------*/

/* Register Offset definitions for CMU_PERI (0x101f0000) */
#define CLK_CON_GAT_GATE_CLK_PERI_UID_PWM_MOTOR_IPCLKPORT_I_OSCCLK		0x0800
#define CLK_CON_GAT_GATE_CLK_PERI_UID_TMU_CPUCL0_IPCLKPORT_I_CLK		0x0800
#define CLK_CON_GAT_GATE_CLK_PERI_UID_TMU_CPUCL1_IPCLKPORT_I_CLK		0x0800
#define CLK_CON_GAT_GATE_CLK_PERI_UID_TMU_G3D_IPCLKPORT_I_CLK			0x0800
#define CLK_CON_GAT_GATE_CLK_PERI_UID_BUSP1_PERIC0_IPCLKPORT_HCLK		0x0810
#define CLK_CON_GAT_GATE_CLK_PERI_UID_GPIO_ESE_IPCLKPORT_PCLK			0x0810
#define CLK_CON_GAT_GATE_CLK_PERI_UID_GPIO_NFC_IPCLKPORT_PCLK			0x0810
#define CLK_CON_GAT_GATE_CLK_PERI_UID_GPIO_TOP_IPCLKPORT_PCLK			0x0810
#define CLK_CON_GAT_GATE_CLK_PERI_UID_GPIO_TOUCH_IPCLKPORT_PCLK			0x0810
#define CLK_CON_GAT_GATE_CLK_PERI_UID_HSI2C_DEPTHCAM_IPCLKPORT_IPCLK		0x0810
#define CLK_CON_GAT_GATE_CLK_PERI_UID_HSI2C_FRONTCAM_IPCLKPORT_IPCLK		0x0810
#define CLK_CON_GAT_GATE_CLK_PERI_UID_HSI2C_FRONTSENSOR_IPCLKPORT_IPCLK		0x0810
#define CLK_CON_GAT_GATE_CLK_PERI_UID_HSI2C_MAINCAM_IPCLKPORT_IPCLK		0x0810
#define CLK_CON_GAT_GATE_CLK_PERI_UID_HSI2C_REARAF_IPCLKPORT_IPCLK		0x0810
#define CLK_CON_GAT_GATE_CLK_PERI_UID_HSI2C_REARSENSOR_IPCLKPORT_IPCLK		0x0810
#define CLK_CON_GAT_GATE_CLK_PERI_UID_I2C_FUELGAUGE_IPCLKPORT_PCLK		0x0810
#define CLK_CON_GAT_GATE_CLK_PERI_UID_I2C_IFPMIC_IPCLKPORT_PCLK			0x0810
#define CLK_CON_GAT_GATE_CLK_PERI_UID_I2C_MUIC_IPCLKPORT_PCLK			0x0810
#define CLK_CON_GAT_GATE_CLK_PERI_UID_I2C_NFC_IPCLKPORT_PCLK			0x0810
#define CLK_CON_GAT_GATE_CLK_PERI_UID_I2C_SENSOR1_IPCLKPORT_PCLK		0x0810
#define CLK_CON_GAT_GATE_CLK_PERI_UID_I2C_SENSOR2_IPCLKPORT_PCLK		0x0810
#define CLK_CON_GAT_GATE_CLK_PERI_UID_I2C_SPKAMP_IPCLKPORT_PCLK			0x0810
#define CLK_CON_GAT_GATE_CLK_PERI_UID_I2C_TOUCHKEY_IPCLKPORT_PCLK		0x0810
#define CLK_CON_GAT_GATE_CLK_PERI_UID_I2C_TSP_IPCLKPORT_PCLK			0x0810
#define CLK_CON_GAT_GATE_CLK_PERI_UID_MCT_IPCLKPORT_PCLK			0x0810
#define CLK_CON_GAT_GATE_CLK_PERI_UID_PWM_MOTOR_IPCLKPORT_I_PCLK_S0		0x0810
#define CLK_CON_GAT_GATE_CLK_PERI_UID_SFRIF_TMU_CPUCL0_IPCLKPORT_PCLK		0x0814
#define CLK_CON_GAT_GATE_CLK_PERI_UID_SFRIF_TMU_CPUCL1_IPCLKPORT_PCLK		0x0814
#define CLK_CON_GAT_GATE_CLK_PERI_UID_SFRIF_TMU_G3D_IPCLKPORT_PCLK		0x0814
#define CLK_CON_GAT_GATE_CLK_PERI_UID_SPI_ESE_IPCLKPORT_PCLK			0x0814
#define CLK_CON_GAT_GATE_CLK_PERI_UID_SPI_FRONTFROM_IPCLKPORT_PCLK		0x0814
#define CLK_CON_GAT_GATE_CLK_PERI_UID_SPI_REARFROM_IPCLKPORT_PCLK		0x0814
#define CLK_CON_GAT_GATE_CLK_PERI_UID_SPI_SENSORHUB_IPCLKPORT_PCLK		0x0814
#define CLK_CON_GAT_GATE_CLK_PERI_UID_SPI_VOICEPROCESSOR_IPCLKPORT_PCLK		0x0814
#define CLK_CON_GAT_GATE_CLK_PERI_UID_UART_BTWIFIFM_IPCLKPORT_PCLK		0x0814
#define CLK_CON_GAT_GATE_CLK_PERI_UID_UART_DEBUG_IPCLKPORT_PCLK			0x0814
#define CLK_CON_GAT_GATE_CLK_PERI_UID_UART_SENSOR_IPCLKPORT_PCLK		0x0814
#define CLK_CON_GAT_GATE_CLK_PERI_UID_WDT_CPUCL0_IPCLKPORT_PCLK			0x0814
#define CLK_CON_GAT_GATE_CLK_PERI_UID_WDT_CPUCL1_IPCLKPORT_PCLK			0x0814
#define CLK_CON_GAT_GATE_CLK_PERI_UID_UART_BTWIFIFM_IPCLKPORT_EXT_UCLK		0x0830
#define CLK_CON_GAT_GATE_CLK_PERI_UID_UART_DEBUG_IPCLKPORT_EXT_UCLK		0x0834
#define CLK_CON_GAT_GATE_CLK_PERI_UID_UART_SENSOR_IPCLKPORT_EXT_UCLK		0x0838
#define CLK_CON_GAT_GATE_CLK_PERI_UID_SPI_FRONTFROM_IPCLKPORT_SPI_EXT_CLK	0x083c
#define CLK_CON_GAT_GATE_CLK_PERI_UID_SPI_REARFROM_IPCLKPORT_SPI_EXT_CLK	0x0840
#define CLK_CON_GAT_GATE_CLK_PERI_UID_SPI_ESE_IPCLKPORT_SPI_EXT_CLK		0x0844
#define CLK_CON_GAT_GATE_CLK_PERI_UID_SPI_VOICEPROCESSOR_IPCLKPORT_SPI_EXT_CLK	0x0848
#define CLK_CON_GAT_GATE_CLK_PERI_UID_SPI_SENSORHUB_IPCLKPORT_SPI_EXT_CLK	0x084c

static const unsigned long peri_clk_regs[] __initconst = {
	CLK_CON_GAT_GATE_CLK_PERI_UID_PWM_MOTOR_IPCLKPORT_I_OSCCLK,
	CLK_CON_GAT_GATE_CLK_PERI_UID_TMU_CPUCL0_IPCLKPORT_I_CLK,
	CLK_CON_GAT_GATE_CLK_PERI_UID_TMU_CPUCL1_IPCLKPORT_I_CLK,
	CLK_CON_GAT_GATE_CLK_PERI_UID_TMU_G3D_IPCLKPORT_I_CLK,
	CLK_CON_GAT_GATE_CLK_PERI_UID_BUSP1_PERIC0_IPCLKPORT_HCLK,
	CLK_CON_GAT_GATE_CLK_PERI_UID_GPIO_ESE_IPCLKPORT_PCLK,
	CLK_CON_GAT_GATE_CLK_PERI_UID_GPIO_NFC_IPCLKPORT_PCLK,
	CLK_CON_GAT_GATE_CLK_PERI_UID_GPIO_TOP_IPCLKPORT_PCLK,
	CLK_CON_GAT_GATE_CLK_PERI_UID_GPIO_TOUCH_IPCLKPORT_PCLK,
	CLK_CON_GAT_GATE_CLK_PERI_UID_HSI2C_DEPTHCAM_IPCLKPORT_IPCLK,
	CLK_CON_GAT_GATE_CLK_PERI_UID_HSI2C_FRONTCAM_IPCLKPORT_IPCLK,
	CLK_CON_GAT_GATE_CLK_PERI_UID_HSI2C_FRONTSENSOR_IPCLKPORT_IPCLK,
	CLK_CON_GAT_GATE_CLK_PERI_UID_HSI2C_MAINCAM_IPCLKPORT_IPCLK,
	CLK_CON_GAT_GATE_CLK_PERI_UID_HSI2C_REARAF_IPCLKPORT_IPCLK,
	CLK_CON_GAT_GATE_CLK_PERI_UID_HSI2C_REARSENSOR_IPCLKPORT_IPCLK,
	CLK_CON_GAT_GATE_CLK_PERI_UID_I2C_FUELGAUGE_IPCLKPORT_PCLK,
	CLK_CON_GAT_GATE_CLK_PERI_UID_I2C_IFPMIC_IPCLKPORT_PCLK,
	CLK_CON_GAT_GATE_CLK_PERI_UID_I2C_MUIC_IPCLKPORT_PCLK,
	CLK_CON_GAT_GATE_CLK_PERI_UID_I2C_NFC_IPCLKPORT_PCLK,
	CLK_CON_GAT_GATE_CLK_PERI_UID_I2C_SENSOR1_IPCLKPORT_PCLK,
	CLK_CON_GAT_GATE_CLK_PERI_UID_I2C_SENSOR2_IPCLKPORT_PCLK,
	CLK_CON_GAT_GATE_CLK_PERI_UID_I2C_SPKAMP_IPCLKPORT_PCLK,
	CLK_CON_GAT_GATE_CLK_PERI_UID_I2C_TOUCHKEY_IPCLKPORT_PCLK,
	CLK_CON_GAT_GATE_CLK_PERI_UID_I2C_TSP_IPCLKPORT_PCLK,
	CLK_CON_GAT_GATE_CLK_PERI_UID_MCT_IPCLKPORT_PCLK,
	CLK_CON_GAT_GATE_CLK_PERI_UID_PWM_MOTOR_IPCLKPORT_I_PCLK_S0,
	CLK_CON_GAT_GATE_CLK_PERI_UID_SFRIF_TMU_CPUCL0_IPCLKPORT_PCLK,
	CLK_CON_GAT_GATE_CLK_PERI_UID_SFRIF_TMU_CPUCL1_IPCLKPORT_PCLK,
	CLK_CON_GAT_GATE_CLK_PERI_UID_SFRIF_TMU_G3D_IPCLKPORT_PCLK,
	CLK_CON_GAT_GATE_CLK_PERI_UID_SPI_ESE_IPCLKPORT_PCLK,
	CLK_CON_GAT_GATE_CLK_PERI_UID_SPI_FRONTFROM_IPCLKPORT_PCLK,
	CLK_CON_GAT_GATE_CLK_PERI_UID_SPI_REARFROM_IPCLKPORT_PCLK,
	CLK_CON_GAT_GATE_CLK_PERI_UID_SPI_SENSORHUB_IPCLKPORT_PCLK,
	CLK_CON_GAT_GATE_CLK_PERI_UID_SPI_VOICEPROCESSOR_IPCLKPORT_PCLK,
	CLK_CON_GAT_GATE_CLK_PERI_UID_UART_BTWIFIFM_IPCLKPORT_PCLK,
	CLK_CON_GAT_GATE_CLK_PERI_UID_UART_DEBUG_IPCLKPORT_PCLK,
	CLK_CON_GAT_GATE_CLK_PERI_UID_UART_SENSOR_IPCLKPORT_PCLK,
	CLK_CON_GAT_GATE_CLK_PERI_UID_WDT_CPUCL0_IPCLKPORT_PCLK,
	CLK_CON_GAT_GATE_CLK_PERI_UID_WDT_CPUCL1_IPCLKPORT_PCLK,
	CLK_CON_GAT_GATE_CLK_PERI_UID_UART_BTWIFIFM_IPCLKPORT_EXT_UCLK,
	CLK_CON_GAT_GATE_CLK_PERI_UID_UART_DEBUG_IPCLKPORT_EXT_UCLK,
	CLK_CON_GAT_GATE_CLK_PERI_UID_UART_SENSOR_IPCLKPORT_EXT_UCLK,
	CLK_CON_GAT_GATE_CLK_PERI_UID_SPI_FRONTFROM_IPCLKPORT_SPI_EXT_CLK,
	CLK_CON_GAT_GATE_CLK_PERI_UID_SPI_REARFROM_IPCLKPORT_SPI_EXT_CLK,
	CLK_CON_GAT_GATE_CLK_PERI_UID_SPI_ESE_IPCLKPORT_SPI_EXT_CLK,
	CLK_CON_GAT_GATE_CLK_PERI_UID_SPI_VOICEPROCESSOR_IPCLKPORT_SPI_EXT_CLK,
	CLK_CON_GAT_GATE_CLK_PERI_UID_SPI_SENSORHUB_IPCLKPORT_SPI_EXT_CLK,
};

static const struct samsung_gate_clock peri_gate_clks[] __initconst = {
	GATE(CLK_GOUT_CLK_PERI_UID_BUSP1_PERIC0_IPCLKPORT_HCLK, "gout_clk_peri_uid_busp1_peric0_ipclkport_hclk", "gout_clkcmu_peri_bus",
	    CLK_CON_GAT_GATE_CLK_PERI_UID_BUSP1_PERIC0_IPCLKPORT_HCLK, 3, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_PERI_UID_GPIO_ESE_IPCLKPORT_PCLK, "gout_clk_peri_uid_gpio_ese_ipclkport_pclk", "gout_clkcmu_peri_bus",
	    CLK_CON_GAT_GATE_CLK_PERI_UID_GPIO_ESE_IPCLKPORT_PCLK, 7, CLK_IS_CRITICAL | CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_PERI_UID_GPIO_NFC_IPCLKPORT_PCLK, "gout_clk_peri_uid_gpio_nfc_ipclkport_pclk", "gout_clkcmu_peri_bus",
	    CLK_CON_GAT_GATE_CLK_PERI_UID_GPIO_NFC_IPCLKPORT_PCLK, 8, CLK_IS_CRITICAL | CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_PERI_UID_GPIO_TOP_IPCLKPORT_PCLK, "gout_clk_peri_uid_gpio_top_ipclkport_pclk", "gout_clkcmu_peri_bus",
	    CLK_CON_GAT_GATE_CLK_PERI_UID_GPIO_TOP_IPCLKPORT_PCLK, 9, CLK_IS_CRITICAL | CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_PERI_UID_GPIO_TOUCH_IPCLKPORT_PCLK, "gout_clk_peri_uid_gpio_touch_ipclkport_pclk", "gout_clkcmu_peri_bus",
	    CLK_CON_GAT_GATE_CLK_PERI_UID_GPIO_TOUCH_IPCLKPORT_PCLK, 10, CLK_IS_CRITICAL | CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_PERI_UID_HSI2C_DEPTHCAM_IPCLKPORT_IPCLK, "gout_clk_peri_uid_hsi2c_depthcam_ipclkport_ipclk", "gout_clk_peri_uid_busp1_peric0_ipclkport_hclk",
	    CLK_CON_GAT_GATE_CLK_PERI_UID_HSI2C_DEPTHCAM_IPCLKPORT_IPCLK, 14, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_PERI_UID_HSI2C_FRONTCAM_IPCLKPORT_IPCLK, "gout_clk_peri_uid_hsi2c_frontcam_ipclkport_ipclk", "gout_clkcmu_peri_bus",
	    CLK_CON_GAT_GATE_CLK_PERI_UID_HSI2C_FRONTCAM_IPCLKPORT_IPCLK, 16, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_PERI_UID_HSI2C_FRONTSENSOR_IPCLKPORT_IPCLK, "gout_clk_peri_uid_hsi2c_frontsensor_ipclkport_ipclk", "gout_clk_peri_uid_busp1_peric0_ipclkport_hclk",
	    CLK_CON_GAT_GATE_CLK_PERI_UID_HSI2C_FRONTSENSOR_IPCLKPORT_IPCLK, 13, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_PERI_UID_HSI2C_MAINCAM_IPCLKPORT_IPCLK, "gout_clk_peri_uid_hsi2c_maincam_ipclkport_ipclk", "gout_clkcmu_peri_bus",
	    CLK_CON_GAT_GATE_CLK_PERI_UID_HSI2C_MAINCAM_IPCLKPORT_IPCLK, 15, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_PERI_UID_HSI2C_REARAF_IPCLKPORT_IPCLK, "gout_clk_peri_uid_hsi2c_rearaf_ipclkport_ipclk", "gout_clk_peri_uid_busp1_peric0_ipclkport_hclk",
	    CLK_CON_GAT_GATE_CLK_PERI_UID_HSI2C_REARAF_IPCLKPORT_IPCLK, 12, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_PERI_UID_HSI2C_REARSENSOR_IPCLKPORT_IPCLK, "gout_clk_peri_uid_hsi2c_rearsensor_ipclkport_ipclk", "gout_clk_peri_uid_busp1_peric0_ipclkport_hclk",
	    CLK_CON_GAT_GATE_CLK_PERI_UID_HSI2C_REARSENSOR_IPCLKPORT_IPCLK, 11, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_PERI_UID_I2C_FUELGAUGE_IPCLKPORT_PCLK, "gout_clk_peri_uid_i2c_fuelgauge_ipclkport_pclk", "gout_clk_peri_uid_busp1_peric0_ipclkport_hclk",
	    CLK_CON_GAT_GATE_CLK_PERI_UID_I2C_FUELGAUGE_IPCLKPORT_PCLK, 21, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_PERI_UID_I2C_IFPMIC_IPCLKPORT_PCLK, "gout_clk_peri_uid_i2c_ifpmic_ipclkport_pclk", "gout_clk_peri_uid_busp1_peric0_ipclkport_hclk",
	    CLK_CON_GAT_GATE_CLK_PERI_UID_I2C_IFPMIC_IPCLKPORT_PCLK, 17, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_PERI_UID_I2C_MUIC_IPCLKPORT_PCLK, "gout_clk_peri_uid_i2c_muic_ipclkport_pclk", "gout_clk_peri_uid_busp1_peric0_ipclkport_hclk",
	    CLK_CON_GAT_GATE_CLK_PERI_UID_I2C_MUIC_IPCLKPORT_PCLK, 18, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_PERI_UID_I2C_NFC_IPCLKPORT_PCLK, "gout_clk_peri_uid_i2c_nfc_ipclkport_pclk", "gout_clk_peri_uid_busp1_peric0_ipclkport_hclk",
	    CLK_CON_GAT_GATE_CLK_PERI_UID_I2C_NFC_IPCLKPORT_PCLK, 19, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_PERI_UID_I2C_SENSOR1_IPCLKPORT_PCLK, "gout_clk_peri_uid_i2c_sensor1_ipclkport_pclk", "gout_clk_peri_uid_busp1_peric0_ipclkport_hclk",
	    CLK_CON_GAT_GATE_CLK_PERI_UID_I2C_SENSOR1_IPCLKPORT_PCLK, 24, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_PERI_UID_I2C_SENSOR2_IPCLKPORT_PCLK, "gout_clk_peri_uid_i2c_sensor2_ipclkport_pclk", "gout_clk_peri_uid_busp1_peric0_ipclkport_hclk",
	    CLK_CON_GAT_GATE_CLK_PERI_UID_I2C_SENSOR2_IPCLKPORT_PCLK, 25, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_PERI_UID_I2C_SPKAMP_IPCLKPORT_PCLK, "gout_clk_peri_uid_i2c_spkamp_ipclkport_pclk", "gout_clk_peri_uid_busp1_peric0_ipclkport_hclk",
	    CLK_CON_GAT_GATE_CLK_PERI_UID_I2C_SPKAMP_IPCLKPORT_PCLK, 20, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_PERI_UID_I2C_TOUCHKEY_IPCLKPORT_PCLK, "gout_clk_peri_uid_i2c_touchkey_ipclkport_pclk", "gout_clk_peri_uid_busp1_peric0_ipclkport_hclk",
	    CLK_CON_GAT_GATE_CLK_PERI_UID_I2C_TOUCHKEY_IPCLKPORT_PCLK, 22, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_PERI_UID_I2C_TSP_IPCLKPORT_PCLK, "gout_clk_peri_uid_i2c_tsp_ipclkport_pclk", "gout_clk_peri_uid_busp1_peric0_ipclkport_hclk",
	    CLK_CON_GAT_GATE_CLK_PERI_UID_I2C_TSP_IPCLKPORT_PCLK, 23, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_PERI_UID_MCT_IPCLKPORT_PCLK, "gout_clk_peri_uid_mct_ipclkport_pclk", "gout_clkcmu_peri_bus",
	    CLK_CON_GAT_GATE_CLK_PERI_UID_MCT_IPCLKPORT_PCLK, 26, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_PERI_UID_PWM_MOTOR_IPCLKPORT_I_OSCCLK, "gout_clk_peri_uid_pwm_motor_ipclkport_i_oscclk", "oscclk",
	    CLK_CON_GAT_GATE_CLK_PERI_UID_PWM_MOTOR_IPCLKPORT_I_OSCCLK, 2, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_PERI_UID_PWM_MOTOR_IPCLKPORT_I_PCLK_S0, "gout_clk_peri_uid_pwm_motor_ipclkport_i_pclk_s0", "gout_clkcmu_peri_bus",
	    CLK_CON_GAT_GATE_CLK_PERI_UID_PWM_MOTOR_IPCLKPORT_I_PCLK_S0, 29, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_PERI_UID_SFRIF_TMU_CPUCL0_IPCLKPORT_PCLK, "gout_clk_peri_uid_sfrif_tmu_cpucl0_ipclkport_pclk", "gout_clkcmu_peri_bus",
	    CLK_CON_GAT_GATE_CLK_PERI_UID_SFRIF_TMU_CPUCL0_IPCLKPORT_PCLK, 1, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_PERI_UID_SFRIF_TMU_CPUCL1_IPCLKPORT_PCLK, "gout_clk_peri_uid_sfrif_tmu_cpucl1_ipclkport_pclk", "gout_clkcmu_peri_bus",
	    CLK_CON_GAT_GATE_CLK_PERI_UID_SFRIF_TMU_CPUCL1_IPCLKPORT_PCLK, 2, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_PERI_UID_SFRIF_TMU_G3D_IPCLKPORT_PCLK, "gout_clk_peri_uid_sfrif_tmu_g3d_ipclkport_pclk", "gout_clkcmu_peri_bus",
	    CLK_CON_GAT_GATE_CLK_PERI_UID_SFRIF_TMU_G3D_IPCLKPORT_PCLK, 3, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_PERI_UID_SPI_ESE_IPCLKPORT_PCLK, "gout_clk_peri_uid_spi_ese_ipclkport_pclk", "gout_clkcmu_peri_bus",
	    CLK_CON_GAT_GATE_CLK_PERI_UID_SPI_ESE_IPCLKPORT_PCLK, 6, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_PERI_UID_SPI_ESE_IPCLKPORT_SPI_EXT_CLK, "gout_clk_peri_uid_spi_ese_ipclkport_spi_ext_clk", "gout_clkcmu_peri_spi_ese",
	    CLK_CON_GAT_GATE_CLK_PERI_UID_SPI_ESE_IPCLKPORT_SPI_EXT_CLK, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_PERI_UID_SPI_FRONTFROM_IPCLKPORT_PCLK, "gout_clk_peri_uid_spi_frontfrom_ipclkport_pclk", "gout_clkcmu_peri_bus",
	    CLK_CON_GAT_GATE_CLK_PERI_UID_SPI_FRONTFROM_IPCLKPORT_PCLK, 4, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_PERI_UID_SPI_FRONTFROM_IPCLKPORT_SPI_EXT_CLK, "gout_clk_peri_uid_spi_frontfrom_ipclkport_spi_ext_clk", "gout_clkcmu_peri_spi_frontfrom",
	    CLK_CON_GAT_GATE_CLK_PERI_UID_SPI_FRONTFROM_IPCLKPORT_SPI_EXT_CLK, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_PERI_UID_SPI_REARFROM_IPCLKPORT_PCLK, "gout_clk_peri_uid_spi_rearfrom_ipclkport_pclk", "gout_clkcmu_peri_bus",
	    CLK_CON_GAT_GATE_CLK_PERI_UID_SPI_REARFROM_IPCLKPORT_PCLK, 5, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_PERI_UID_SPI_REARFROM_IPCLKPORT_SPI_EXT_CLK, "gout_clk_peri_uid_spi_rearfrom_ipclkport_spi_ext_clk", "gout_clkcmu_peri_spi_rearfrom",
	    CLK_CON_GAT_GATE_CLK_PERI_UID_SPI_REARFROM_IPCLKPORT_SPI_EXT_CLK, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_PERI_UID_SPI_SENSORHUB_IPCLKPORT_PCLK, "gout_clk_peri_uid_spi_sensorhub_ipclkport_pclk", "gout_clkcmu_peri_bus",
	    CLK_CON_GAT_GATE_CLK_PERI_UID_SPI_SENSORHUB_IPCLKPORT_PCLK, 8, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_PERI_UID_SPI_SENSORHUB_IPCLKPORT_SPI_EXT_CLK, "gout_clk_peri_uid_spi_sensorhub_ipclkport_spi_ext_clk", "gout_clkcmu_peri_spi_sensorhub",
	    CLK_CON_GAT_GATE_CLK_PERI_UID_SPI_SENSORHUB_IPCLKPORT_SPI_EXT_CLK, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_PERI_UID_SPI_VOICEPROCESSOR_IPCLKPORT_PCLK, "gout_clk_peri_uid_spi_voiceprocessor_ipclkport_pclk", "gout_clkcmu_peri_bus",
	    CLK_CON_GAT_GATE_CLK_PERI_UID_SPI_VOICEPROCESSOR_IPCLKPORT_PCLK, 7, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_PERI_UID_SPI_VOICEPROCESSOR_IPCLKPORT_SPI_EXT_CLK, "gout_clk_peri_uid_spi_voiceprocessor_ipclkport_spi_ext_clk", "gout_clkcmu_peri_spi_voiceprocessor",
	    CLK_CON_GAT_GATE_CLK_PERI_UID_SPI_VOICEPROCESSOR_IPCLKPORT_SPI_EXT_CLK, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_PERI_UID_TMU_CPUCL0_IPCLKPORT_I_CLK, "gout_clk_peri_uid_tmu_cpucl0_ipclkport_i_clk", "oscclk",
	    CLK_CON_GAT_GATE_CLK_PERI_UID_TMU_CPUCL0_IPCLKPORT_I_CLK, 4, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_PERI_UID_TMU_CPUCL1_IPCLKPORT_I_CLK, "gout_clk_peri_uid_tmu_cpucl1_ipclkport_i_clk", "oscclk",
	    CLK_CON_GAT_GATE_CLK_PERI_UID_TMU_CPUCL1_IPCLKPORT_I_CLK, 5, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_PERI_UID_TMU_G3D_IPCLKPORT_I_CLK, "gout_clk_peri_uid_tmu_g3d_ipclkport_i_clk", "oscclk",
	    CLK_CON_GAT_GATE_CLK_PERI_UID_TMU_G3D_IPCLKPORT_I_CLK, 6, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_PERI_UID_UART_BTWIFIFM_IPCLKPORT_EXT_UCLK, "gout_clk_peri_uid_uart_btwififm_ipclkport_ext_uclk", "gout_clkcmu_peri_uart_btwififm",
	    CLK_CON_GAT_GATE_CLK_PERI_UID_UART_BTWIFIFM_IPCLKPORT_EXT_UCLK, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_PERI_UID_UART_BTWIFIFM_IPCLKPORT_PCLK, "gout_clk_peri_uid_uart_btwififm_ipclkport_pclk", "gout_clk_peri_uid_busp1_peric0_ipclkport_hclk",
	    CLK_CON_GAT_GATE_CLK_PERI_UID_UART_BTWIFIFM_IPCLKPORT_PCLK, 11, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_PERI_UID_UART_DEBUG_IPCLKPORT_EXT_UCLK, "gout_clk_peri_uid_uart_debug_ipclkport_ext_uclk", "gout_clkcmu_peri_uart_debug",
	    CLK_CON_GAT_GATE_CLK_PERI_UID_UART_DEBUG_IPCLKPORT_EXT_UCLK, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_PERI_UID_UART_DEBUG_IPCLKPORT_PCLK, "gout_clk_peri_uid_uart_debug_ipclkport_pclk", "gout_clk_peri_uid_busp1_peric0_ipclkport_hclk",
	    CLK_CON_GAT_GATE_CLK_PERI_UID_UART_DEBUG_IPCLKPORT_PCLK, 12, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_PERI_UID_UART_SENSOR_IPCLKPORT_EXT_UCLK, "gout_clk_peri_uid_uart_sensor_ipclkport_ext_uclk", "gout_clkcmu_peri_uart_sensor",
	    CLK_CON_GAT_GATE_CLK_PERI_UID_UART_SENSOR_IPCLKPORT_EXT_UCLK, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_PERI_UID_UART_SENSOR_IPCLKPORT_PCLK, "gout_clk_peri_uid_uart_sensor_ipclkport_pclk", "gout_clk_peri_uid_busp1_peric0_ipclkport_hclk",
	    CLK_CON_GAT_GATE_CLK_PERI_UID_UART_SENSOR_IPCLKPORT_PCLK, 10, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_PERI_UID_WDT_CPUCL0_IPCLKPORT_PCLK, "gout_clk_peri_uid_wdt_cpucl0_ipclkport_pclk", "gout_clkcmu_peri_bus",
	    CLK_CON_GAT_GATE_CLK_PERI_UID_WDT_CPUCL0_IPCLKPORT_PCLK, 13, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_GOUT_CLK_PERI_UID_WDT_CPUCL1_IPCLKPORT_PCLK, "gout_clk_peri_uid_wdt_cpucl1_ipclkport_pclk", "gout_clkcmu_peri_bus",
	    CLK_CON_GAT_GATE_CLK_PERI_UID_WDT_CPUCL1_IPCLKPORT_PCLK, 14, CLK_SET_RATE_PARENT, 0),
};

static const struct samsung_cmu_info peri_cmu_info __initconst = {
	.gate_clks		= peri_gate_clks,
	.nr_gate_clks		= ARRAY_SIZE(peri_gate_clks),
	.nr_clk_ids		= PERI_NR_CLK,
	.clk_regs		= peri_clk_regs,
	.nr_clk_regs		= ARRAY_SIZE(peri_clk_regs),
};

/* ---- platform_driver ----------------------------------------------------- */
static int __init exynos7870_cmu_probe(struct platform_device *pdev)
{
	const struct samsung_cmu_info *info;
	struct device *dev = &pdev->dev;

	info = of_device_get_match_data(dev);
	exynos_arm64_register_cmu(dev, dev->of_node, info);

	return 0;
}

static const struct of_device_id exynos7870_cmu_of_match[] = {
	{
		.compatible = "samsung,exynos7870-cmu-mif",
		.data = &mif_cmu_info,
	}, {
		.compatible = "samsung,exynos7870-cmu-pmu_alive",
		.data = &pmu_alive_cmu_info,
	}, {
		.compatible = "samsung,exynos7870-cmu-dispaud",
		.data = &dispaud_cmu_info,
	}, {
		.compatible = "samsung,exynos7870-cmu-fsys",
		.data = &fsys_cmu_info,
	}, {
		.compatible = "samsung,exynos7870-cmu-g3d",
		.data = &g3d_cmu_info,
	}, {
		.compatible = "samsung,exynos7870-cmu-isp",
		.data = &isp_cmu_info,
	}, {
		.compatible = "samsung,exynos7870-cmu-mfcmscl",
		.data = &mfcmscl_cmu_info,
	}, {
		.compatible = "samsung,exynos7870-cmu-peri",
		.data = &peri_cmu_info,
	}, {
	},
};

static struct platform_driver exynos7870_cmu_driver __refdata = {
	.driver = {
		.name = "exynos7870-cmu",
		.of_match_table = exynos7870_cmu_of_match,
		.suppress_bind_attrs = true,
	},
	.probe = exynos7870_cmu_probe,
};

static int __init exynos7870_cmu_init(void)
{
	return platform_driver_register(&exynos7870_cmu_driver);
}
core_initcall(exynos7870_cmu_init);
