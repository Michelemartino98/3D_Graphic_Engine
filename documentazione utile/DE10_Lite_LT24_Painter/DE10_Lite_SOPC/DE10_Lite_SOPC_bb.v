
module DE10_Lite_SOPC (
	clk_clk,
	clk_sdram_clk,
	lcd_reset_n_external_connection_export,
	lt24_controller_conduit_end_cs,
	lt24_controller_conduit_end_rs,
	lt24_controller_conduit_end_rd,
	lt24_controller_conduit_end_wr,
	lt24_controller_conduit_end_data,
	pio_key_external_connection_export,
	pio_led_external_connection_export,
	pio_sw_external_connection_export,
	reset_reset_n,
	sdram_wire_addr,
	sdram_wire_ba,
	sdram_wire_cas_n,
	sdram_wire_cke,
	sdram_wire_cs_n,
	sdram_wire_dq,
	sdram_wire_dqm,
	sdram_wire_ras_n,
	sdram_wire_we_n,
	seg7_conduit_end_export,
	touch_panel_busy_external_connection_export,
	touch_panel_pen_irq_n_external_connection_export,
	touch_panel_spi_external_MISO,
	touch_panel_spi_external_MOSI,
	touch_panel_spi_external_SCLK,
	touch_panel_spi_external_SS_n,
	video_vga_controller_0_external_interface_CLK,
	video_vga_controller_0_external_interface_HS,
	video_vga_controller_0_external_interface_VS,
	video_vga_controller_0_external_interface_BLANK,
	video_vga_controller_0_external_interface_SYNC,
	video_vga_controller_0_external_interface_R,
	video_vga_controller_0_external_interface_G,
	video_vga_controller_0_external_interface_B);	

	input		clk_clk;
	output		clk_sdram_clk;
	output		lcd_reset_n_external_connection_export;
	output		lt24_controller_conduit_end_cs;
	output		lt24_controller_conduit_end_rs;
	output		lt24_controller_conduit_end_rd;
	output		lt24_controller_conduit_end_wr;
	output	[15:0]	lt24_controller_conduit_end_data;
	input	[1:0]	pio_key_external_connection_export;
	output	[9:0]	pio_led_external_connection_export;
	input	[9:0]	pio_sw_external_connection_export;
	input		reset_reset_n;
	output	[12:0]	sdram_wire_addr;
	output	[1:0]	sdram_wire_ba;
	output		sdram_wire_cas_n;
	output		sdram_wire_cke;
	output		sdram_wire_cs_n;
	inout	[15:0]	sdram_wire_dq;
	output	[1:0]	sdram_wire_dqm;
	output		sdram_wire_ras_n;
	output		sdram_wire_we_n;
	output	[47:0]	seg7_conduit_end_export;
	input		touch_panel_busy_external_connection_export;
	input		touch_panel_pen_irq_n_external_connection_export;
	input		touch_panel_spi_external_MISO;
	output		touch_panel_spi_external_MOSI;
	output		touch_panel_spi_external_SCLK;
	output		touch_panel_spi_external_SS_n;
	output		video_vga_controller_0_external_interface_CLK;
	output		video_vga_controller_0_external_interface_HS;
	output		video_vga_controller_0_external_interface_VS;
	output		video_vga_controller_0_external_interface_BLANK;
	output		video_vga_controller_0_external_interface_SYNC;
	output	[3:0]	video_vga_controller_0_external_interface_R;
	output	[3:0]	video_vga_controller_0_external_interface_G;
	output	[3:0]	video_vga_controller_0_external_interface_B;
endmodule
