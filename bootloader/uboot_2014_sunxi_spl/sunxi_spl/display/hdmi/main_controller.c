/*
 * Allwinner SoCs hdmi2.0 driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#include "main_controller.h"
#include "access.h"

static void mc_hdcp_clock_enable(hdmi_tx_dev_t *dev, u8 bit)
{
	LOG_TRACE1(bit);
	dev_write_mask(dev, MC_CLKDIS, MC_CLKDIS_HDCPCLK_DISABLE_MASK, bit);
}

void mc_cec_clock_enable(hdmi_tx_dev_t *dev, u8 bit)
{
	LOG_TRACE1(bit);
	dev_write_mask(dev, MC_CLKDIS, MC_CLKDIS_CECCLK_DISABLE_MASK, bit);
}

static void mc_colorspace_converter_clock_enable(hdmi_tx_dev_t *dev, u8 bit)
{
	LOG_TRACE1(bit);
	dev_write_mask(dev, MC_CLKDIS, MC_CLKDIS_CSCCLK_DISABLE_MASK, bit);
}

void mc_audio_sampler_clock_enable(hdmi_tx_dev_t *dev, u8 bit)
{
	LOG_TRACE1(bit);
	dev_write_mask(dev, MC_CLKDIS, MC_CLKDIS_AUDCLK_DISABLE_MASK, bit);
}

static void mc_pixel_repetition_clock_enable(hdmi_tx_dev_t *dev, u8 bit)
{
	LOG_TRACE1(bit);
	dev_write_mask(dev, MC_CLKDIS, MC_CLKDIS_PREPCLK_DISABLE_MASK, bit);
}

static void mc_tmds_clock_enable(hdmi_tx_dev_t *dev, u8 bit)
{
	LOG_TRACE1(bit);
	dev_write_mask(dev, MC_CLKDIS, MC_CLKDIS_TMDSCLK_DISABLE_MASK, bit);
}

static void mc_pixel_clock_enable(hdmi_tx_dev_t *dev, u8 bit)
{
	LOG_TRACE1(bit);
	dev_write_mask(dev, MC_CLKDIS, MC_CLKDIS_PIXELCLK_DISABLE_MASK, bit);
}

void mc_audio_i2s_reset(hdmi_tx_dev_t *dev, u8 bit)
{
	LOG_TRACE1(bit);
	dev_write_mask(dev, MC_SWRSTZREQ,
			MC_SWRSTZREQ_II2SSWRST_REQ_MASK, bit);
}


static void mc_video_feed_through_off(hdmi_tx_dev_t *dev, u8 bit)
{
	LOG_TRACE1(bit);
	dev_write_mask(dev, MC_FLOWCTRL,
				MC_FLOWCTRL_FEED_THROUGH_OFF_MASK, bit);
}

void mc_phy_reset(hdmi_tx_dev_t *dev, u8 bit)
{
	LOG_TRACE1(bit);
	/* active low */
	dev_write_mask(dev, MC_PHYRSTZ, MC_PHYRSTZ_PHYRSTZ_MASK, bit);
}

void mc_tmds_clock_reset(hdmi_tx_dev_t *dev, u8 bit)
{
	LOG_TRACE1(bit);
	dev_write_mask(dev, MC_SWRSTZREQ, MC_SWRSTZREQ_TMDSSWRST_REQ_MASK, bit);
}


void mc_enable_all_clocks(hdmi_tx_dev_t *dev)
{
	LOG_TRACE();
	mc_video_feed_through_off(dev, dev->snps_hdmi_ctrl.csc_on ? 0 : 1);
	mc_pixel_clock_enable(dev, 0);
	mc_tmds_clock_enable(dev, 0);
	mc_pixel_repetition_clock_enable(dev,
			(dev->snps_hdmi_ctrl.pixel_repetition > 0) ? 0 : 1);
	mc_colorspace_converter_clock_enable(dev, 0);
	mc_audio_sampler_clock_enable(dev,
				dev->snps_hdmi_ctrl.audio_on ? 0 : 1);
	mc_cec_clock_enable(dev, dev->snps_hdmi_ctrl.cec_on ? 0 : 1);
	mc_hdcp_clock_enable(dev, dev->snps_hdmi_ctrl.hdcp_on ? 0 : 1);
}
