
module lt24_HiRes (
	accelerometer_spi_export_I2C_SDAT,
	accelerometer_spi_export_I2C_SCLK,
	accelerometer_spi_export_G_SENSOR_CS_N,
	accelerometer_spi_export_G_SENSOR_INT,
	clk_clk,
	hex3_hex0_out_export,
	hex5_hex4_out_export,
	key_out_export,
	lcd_reset_n_external_connection_export,
	leds_out_export,
	lt24_controller_conduit_end_cs,
	lt24_controller_conduit_end_rs,
	lt24_controller_conduit_end_rd,
	lt24_controller_conduit_end_wr,
	lt24_controller_conduit_end_data,
	reset_reset_n,
	sdram_clk_clk,
	sdram_wire_addr,
	sdram_wire_ba,
	sdram_wire_cas_n,
	sdram_wire_cke,
	sdram_wire_cs_n,
	sdram_wire_dq,
	sdram_wire_dqm,
	sdram_wire_ras_n,
	sdram_wire_we_n,
	sliders_out_export,
	spi_external_MISO,
	spi_external_MOSI,
	spi_external_SCLK,
	spi_external_SS_n,
	touch_busy_external_connection_export,
	touch_pen_irq_n_external_connection_export,
	vga_output_CLK,
	vga_output_HS,
	vga_output_VS,
	vga_output_BLANK,
	vga_output_SYNC,
	vga_output_R,
	vga_output_G,
	vga_output_B);	

	inout		accelerometer_spi_export_I2C_SDAT;
	output		accelerometer_spi_export_I2C_SCLK;
	output		accelerometer_spi_export_G_SENSOR_CS_N;
	input		accelerometer_spi_export_G_SENSOR_INT;
	input		clk_clk;
	output	[31:0]	hex3_hex0_out_export;
	output	[15:0]	hex5_hex4_out_export;
	input	[1:0]	key_out_export;
	output		lcd_reset_n_external_connection_export;
	output	[9:0]	leds_out_export;
	output		lt24_controller_conduit_end_cs;
	output		lt24_controller_conduit_end_rs;
	output		lt24_controller_conduit_end_rd;
	output		lt24_controller_conduit_end_wr;
	output	[15:0]	lt24_controller_conduit_end_data;
	input		reset_reset_n;
	output		sdram_clk_clk;
	output	[12:0]	sdram_wire_addr;
	output	[1:0]	sdram_wire_ba;
	output		sdram_wire_cas_n;
	output		sdram_wire_cke;
	output		sdram_wire_cs_n;
	inout	[15:0]	sdram_wire_dq;
	output	[1:0]	sdram_wire_dqm;
	output		sdram_wire_ras_n;
	output		sdram_wire_we_n;
	input	[9:0]	sliders_out_export;
	input		spi_external_MISO;
	output		spi_external_MOSI;
	output		spi_external_SCLK;
	output		spi_external_SS_n;
	input		touch_busy_external_connection_export;
	input		touch_pen_irq_n_external_connection_export;
	output		vga_output_CLK;
	output		vga_output_HS;
	output		vga_output_VS;
	output		vga_output_BLANK;
	output		vga_output_SYNC;
	output	[3:0]	vga_output_R;
	output	[3:0]	vga_output_G;
	output	[3:0]	vga_output_B;
endmodule
