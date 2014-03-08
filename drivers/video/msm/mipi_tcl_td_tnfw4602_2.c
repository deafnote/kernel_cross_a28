/* Copyright (c) 2012, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include "msm_fb.h"
#include "mipi_dsi.h"
#include "mipi_tcl_td_tnfw4602_2.h"

static struct msm_panel_common_pdata *mipi_tcl_td_tnfw4602_2_pdata;
static struct dsi_buf tcl_td_tnfw4602_2_tx_buf;
static struct dsi_buf tcl_td_tnfw4602_2_rx_buf;

#define TCL_TD_TNFW4602_2_SLEEP_OFF_DELAY 150
#define TCL_TD_TNFW4602_2_DISPLAY_ON_DELAY 150

/* common setting */
static char exit_sleep[2] = {0x11, 0x00};
static char display_on[2] = {0x29, 0x00};
static char display_off[2] = {0x28, 0x00};
static char enter_sleep[2] = {0x10, 0x00};

static struct dsi_cmd_desc tcl_td_tnfw4602_2_display_off_cmds[] = {
	{DTYPE_DCS_WRITE, 1, 0, 0, 150, sizeof(display_off), display_off},
	{DTYPE_DCS_WRITE, 1, 0, 0, 150, sizeof(enter_sleep), enter_sleep}
};

static char video0[] = {
	0xFF, 0x80, 0x09,
	0x01,
};
static char video1[] = {
	0x00, 0x80,
};
static char video2[] = {
	0xFF, 0x80, 0x09,
};
static char video3[] = {
	0x00, 0xB4,
};
static char video4[] = {
	0xC0, 0x10,
};
static char video5[] = {
	0x00, 0x82,
};
static char video6[] = {
	0xC5, 0xA3,
};
static char video7[] = {
	0x00, 0x90,
};
static char video8[] = {
	0xC5, 0xC6, 0x76,
};
static char video9[] = {
	0x00, 0x00,
};
static char video10[] = {
	0xD8, 0x75, 0x73,
};
static char video11[] = {
	0x00, 0x00,
};
static char video12[] = {
	0xD9, 0x4E,
};
static char video13[] = {
	0x00, 0x80,
};
static char video14[] = {
	0xCE, 0x87, 0x03, 0x00,
	0x85, 0x03, 0x00, 0x86,
	0x03, 0x00, 0x84, 0x03,
	0x00,
};
static char video15[] = {
	0x00, 0xA0,
};
static char video16[] = {
	0xCE, 0x38, 0x03, 0x03,
	0x58, 0x00, 0x00, 0x00,
	0x38, 0x02, 0x03, 0x59,
	0x00, 0x00, 0x00,
};
static char video17[] = {
	0x00, 0xB0,
};
static char video18[] = {
	0xCE, 0x38, 0x01, 0x03,
	0x5A, 0x00, 0x00, 0x00,
	0x38, 0x00, 0x03, 0x5B,
	0x00, 0x00, 0x00,
};
static char video19[] = {
	0x00, 0xC0,
};
static char video20[] = {
	0xCE, 0x30, 0x00, 0x03,
	0x5C, 0x00, 0x00, 0x00,
	0x30, 0x01, 0x03, 0x5D,
	0x00, 0x00, 0x00,
};
static char video21[] = {
	0x00, 0xD0,
};
static char video22[] = {
	0xCE, 0x30, 0x02, 0x03,
	0x5E, 0x00, 0x00, 0x00,
	0x30, 0x03, 0x03, 0x5F,
	0x00, 0x00, 0x00,
};
static char video23[] = {
	0x00, 0xC7,
};
static char video24[] = {
	0xCF, 0x00,
};
static char video25[] = {
	0x00, 0xC9,
};
static char video26[] = {
	0xCF, 0x00,
};
static char video27[] = {
	0x00, 0xC4,
};

static char video28[] = {
	0xCB, 0x04, 0x04, 0x04,
	0x04, 0x04, 0x04,
};
static char video29[] = {
	0x00, 0xD9,
};
static char video30[] = {
	0xCB, 0x04, 0x04, 0x04,
	0x04, 0x04, 0x04,
};
static char video31[] = {
	0x00, 0x84,
};
static char video32[] = {
	0xCC, 0x0C, 0x0A, 0x10,
	0x0E, 0x03, 0x04,
};
static char video33[] = {
	0x00, 0x9E,
};
static char video34[] = {
	0xCC, 0x0B,
};
static char video35[] = {
	0x00, 0xA0,
};
static char video36[] = {
	0xCC, 0x09, 0x0F, 0x0D,
	0x01, 0x02,
};
static char video37[] = {
	0x00, 0xB4,
};
static char video38[] = {
	0xCC, 0x0D, 0x0F, 0x09,
	0x0B, 0x02, 0x01,
};
static char video39[] = {
	0x00, 0xCE,
};
static char video40[] = {
	0xCC, 0x0E,
};
static char video41[] = {
	0x00, 0xD0,
};
static char video42[] = {
	0xCC, 0x10, 0x0A, 0x0C,
	0x04, 0x03,
};
static char video43[] = {
	0x00, 0x00,
};
static char video44[] = {
	0xE1, 0x00, 0x0A, 0x0E,
	0x0D, 0x07, 0x18, 0x0F,
	0x0F, 0x00, 0x03, 0x02,
	0x06, 0x0E, 0x26, 0x24,
	0x1D,
};
static char video45[] = {
	0x00, 0x00,
};
static char video46[] = {
	0xE2, 0x00, 0x0A, 0x0E,
	0x0D, 0x07, 0x18, 0x0F,
	0x0F, 0x00, 0x03, 0x02,
	0x06, 0x0E, 0x26, 0x24,
	0x1D,
};
static char video47[] = {
	0x00, 0x81,
};
static char video48[] = {
	0xC1, 0x66,
};
static char video49[] = {
	0x00, 0xA1,
};
static char video50[] = {
	0xC1, 0x08,
};
static char video51[] = {
	0x00, 0x89,
};
static char video52[] = {
	0xC4, 0x08,
};
static char video53[] = {
	0x00, 0xA2,
};
static char video54[] = {
	0xC0, 0x1B, 0x00, 0x02,
};
static char video55[] = {
	0x00, 0x81,
};
static char video56[] = {
	0xC4, 0x83,
};
static char video57[] = {
	0x00, 0x92,
};
static char video58[] = {
	0xC5, 0x01,
};
static char video59[] = {
	0x00, 0xB1,
};
static char video60[] = {
	0xC5, 0xA9,
};
static char video61[] = {
	0x00, 0x92,
};
static char video62[] = {
	0xB3, 0x45,
};
static char video63[] = {
	0x00, 0x90,
};
static char video64[] = {
	0xB3, 0x02,
};
static char video65[] = {
	0x00, 0x80,
};
static char video66[] = {
	0xC0, 0x00, 0x58, 0x00,
	0x14, 0x16,
};
static char video67[] = {
	0x00, 0x80,
};
static char video68[] = {
	0xC4, 0x30,
};
static char video69[] = {
	0x00, 0x90,
};
static char video70[] = {
	0xC0, 0x00, 0x56, 0x00,
	0x00, 0x00, 0x03,
};
static char video71[] = {
	0x00, 0xA6,
};
static char video72[] = {
	0xC1, 0x00, 0x00, 0x00,
};
static char video73[] = {
	0x3A, 0x77,
};
static char video74[] = {
	0x36, 0x00,
};
static char video75[] = {
	0x20, 0x00,
};

static struct dsi_cmd_desc tcl_td_tnfw4602_2_video_display_on_cmds[] = {
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video0), video0},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video1), video1},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video2), video2},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video3), video3},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video4), video4},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video5), video5},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video6), video6},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video7), video7},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video8), video8},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video9), video9},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video10), video10},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video11), video11},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video12), video12},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video13), video13},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video14), video14},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video15), video15},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video16), video16},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video17), video17},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video18), video18},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video19), video19},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video20), video20},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video21), video21},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video22), video22},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video23), video23},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video24), video24},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video25), video25},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video26), video26},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video27), video27},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video28), video28},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video29), video29},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video30), video30},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video31), video31},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video32), video32},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video33), video33},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video34), video34},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video35), video35},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video36), video36},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video37), video37},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video38), video38},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video39), video39},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video40), video40},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video41), video41},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video42), video42},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video43), video43},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video44), video44},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video45), video45},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video46), video46},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video47), video47},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video48), video48},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video49), video49},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video50), video50},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video51), video51},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video52), video52},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video53), video53},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video54), video54},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video55), video55},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video56), video56},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video57), video57},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video58), video58},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video59), video59},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video60), video60},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video61), video61},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video62), video62},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video63), video63},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video64), video64},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video65), video65},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video66), video66},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video67), video67},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video68), video68},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video69), video69},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video70), video70},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video71), video71},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video72), video72},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video73), video73},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video74), video74},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 50, sizeof(video75), video75},

	{DTYPE_DCS_WRITE, 1, 0, 0, TCL_TD_TNFW4602_2_SLEEP_OFF_DELAY, sizeof(exit_sleep),
			exit_sleep},
	{DTYPE_DCS_WRITE, 1, 0, 0, TCL_TD_TNFW4602_2_DISPLAY_ON_DELAY, sizeof(display_on),
			display_on},
};

static int mipi_tcl_td_tnfw4602_2_lcd_on(struct platform_device *pdev)
{
	struct msm_fb_data_type *mfd;
	struct mipi_panel_info *mipi;

	mfd = platform_get_drvdata(pdev);
	if (!mfd)
		return -ENODEV;

	if (mfd->key != MFD_KEY)
		return -EINVAL;

	mipi  = &mfd->panel_info.mipi;

	if (mipi->mode == DSI_VIDEO_MODE) {
		mipi_dsi_cmds_tx(mfd, &tcl_td_tnfw4602_2_tx_buf,
			tcl_td_tnfw4602_2_video_display_on_cmds,
			ARRAY_SIZE(tcl_td_tnfw4602_2_video_display_on_cmds));
	}

	return 0;
}

static int mipi_tcl_td_tnfw4602_2_lcd_off(struct platform_device *pdev)
{
	struct msm_fb_data_type *mfd;

	pr_debug("mipi_tcl_td_tnfw4602_2_lcd_off E\n");

	mfd = platform_get_drvdata(pdev);

	if (!mfd)
		return -ENODEV;
	if (mfd->key != MFD_KEY)
		return -EINVAL;

	mipi_dsi_cmds_tx(mfd, &tcl_td_tnfw4602_2_tx_buf, tcl_td_tnfw4602_2_display_off_cmds,
			ARRAY_SIZE(tcl_td_tnfw4602_2_display_off_cmds));

	pr_debug("mipi_tcl_td_tnfw4602_2_lcd_off X\n");
	return 0;
}

static int __devinit mipi_tcl_td_tnfw4602_2_lcd_probe(struct platform_device *pdev)
{
	pr_debug("%s\n", __func__);

	if (pdev->id == 0) {
		mipi_tcl_td_tnfw4602_2_pdata = pdev->dev.platform_data;
		return 0;
	}

	msm_fb_add_device(pdev);

	return 0;
}

static struct platform_driver this_driver = {
	.probe  = mipi_tcl_td_tnfw4602_2_lcd_probe,
	.driver = {
		.name   = "mipi_tcl_td_tnfw4602_2",
	},
};

static void mipi_tcl_td_tnfw4602_2_set_backlight(struct msm_fb_data_type *mfd)
{
	int32 level;
	int max = mfd->panel_info.bl_max;
	int min = mfd->panel_info.bl_min;

	if (mipi_tcl_td_tnfw4602_2_pdata && mipi_tcl_td_tnfw4602_2_pdata->backlight_level) {
		level = mipi_tcl_td_tnfw4602_2_pdata->backlight_level(mfd->bl_level, max, min);

		if (level < 0) {
			printk("%s: backlight level control failed\n", __func__);
		}
	} else {
		printk("%s: missing baclight control function\n", __func__);
	}

	return;
}

static struct msm_fb_panel_data tcl_td_tnfw4602_2_panel_data = {
	.on	= mipi_tcl_td_tnfw4602_2_lcd_on,
	.off = mipi_tcl_td_tnfw4602_2_lcd_off,
	.set_backlight = mipi_tcl_td_tnfw4602_2_set_backlight,
};

static int ch_used[3];

static int mipi_tcl_td_tnfw4602_2_lcd_init(void)
{
	mipi_dsi_buf_alloc(&tcl_td_tnfw4602_2_tx_buf, DSI_BUF_SIZE);
	mipi_dsi_buf_alloc(&tcl_td_tnfw4602_2_rx_buf, DSI_BUF_SIZE);

	return platform_driver_register(&this_driver);
}
int mipi_tcl_td_tnfw4602_2_device_register(struct msm_panel_info *pinfo,
					u32 channel, u32 panel)
{
	struct platform_device *pdev = NULL;
	int ret;

	if ((channel >= 3) || ch_used[channel])
		return -ENODEV;

	ch_used[channel] = TRUE;

	ret = mipi_tcl_td_tnfw4602_2_lcd_init();
	if (ret) {
		pr_err("mipi_tcl_td_tnfw4602_2_lcd_init() failed with ret %u\n", ret);
		return ret;
	}

	pdev = platform_device_alloc("mipi_tcl_td_tnfw4602_2", (panel << 8)|channel);
	if (!pdev)
		return -ENOMEM;

	tcl_td_tnfw4602_2_panel_data.panel_info = *pinfo;

	ret = platform_device_add_data(pdev, &tcl_td_tnfw4602_2_panel_data,
				sizeof(tcl_td_tnfw4602_2_panel_data));
	if (ret) {
		pr_debug("%s: platform_device_add_data failed!\n", __func__);
		goto err_device_put;
	}

	ret = platform_device_add(pdev);
	if (ret) {
		pr_debug("%s: platform_device_register failed!\n", __func__);
		goto err_device_put;
	}

	return 0;

err_device_put:
	platform_device_put(pdev);
	return ret;
}
