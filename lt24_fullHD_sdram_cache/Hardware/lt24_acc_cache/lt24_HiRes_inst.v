	lt24_HiRes u0 (
		.accelerometer_spi_export_I2C_SDAT          (<connected-to-accelerometer_spi_export_I2C_SDAT>),          //            accelerometer_spi_export.I2C_SDAT
		.accelerometer_spi_export_I2C_SCLK          (<connected-to-accelerometer_spi_export_I2C_SCLK>),          //                                    .I2C_SCLK
		.accelerometer_spi_export_G_SENSOR_CS_N     (<connected-to-accelerometer_spi_export_G_SENSOR_CS_N>),     //                                    .G_SENSOR_CS_N
		.accelerometer_spi_export_G_SENSOR_INT      (<connected-to-accelerometer_spi_export_G_SENSOR_INT>),      //                                    .G_SENSOR_INT
		.clk_clk                                    (<connected-to-clk_clk>),                                    //                                 clk.clk
		.hex3_hex0_out_export                       (<connected-to-hex3_hex0_out_export>),                       //                       hex3_hex0_out.export
		.hex5_hex4_out_export                       (<connected-to-hex5_hex4_out_export>),                       //                       hex5_hex4_out.export
		.key_out_export                             (<connected-to-key_out_export>),                             //                             key_out.export
		.lcd_reset_n_external_connection_export     (<connected-to-lcd_reset_n_external_connection_export>),     //     lcd_reset_n_external_connection.export
		.leds_out_export                            (<connected-to-leds_out_export>),                            //                            leds_out.export
		.lt24_controller_conduit_end_cs             (<connected-to-lt24_controller_conduit_end_cs>),             //         lt24_controller_conduit_end.cs
		.lt24_controller_conduit_end_rs             (<connected-to-lt24_controller_conduit_end_rs>),             //                                    .rs
		.lt24_controller_conduit_end_rd             (<connected-to-lt24_controller_conduit_end_rd>),             //                                    .rd
		.lt24_controller_conduit_end_wr             (<connected-to-lt24_controller_conduit_end_wr>),             //                                    .wr
		.lt24_controller_conduit_end_data           (<connected-to-lt24_controller_conduit_end_data>),           //                                    .data
		.reset_reset_n                              (<connected-to-reset_reset_n>),                              //                               reset.reset_n
		.sdram_clk_clk                              (<connected-to-sdram_clk_clk>),                              //                           sdram_clk.clk
		.sdram_wire_addr                            (<connected-to-sdram_wire_addr>),                            //                          sdram_wire.addr
		.sdram_wire_ba                              (<connected-to-sdram_wire_ba>),                              //                                    .ba
		.sdram_wire_cas_n                           (<connected-to-sdram_wire_cas_n>),                           //                                    .cas_n
		.sdram_wire_cke                             (<connected-to-sdram_wire_cke>),                             //                                    .cke
		.sdram_wire_cs_n                            (<connected-to-sdram_wire_cs_n>),                            //                                    .cs_n
		.sdram_wire_dq                              (<connected-to-sdram_wire_dq>),                              //                                    .dq
		.sdram_wire_dqm                             (<connected-to-sdram_wire_dqm>),                             //                                    .dqm
		.sdram_wire_ras_n                           (<connected-to-sdram_wire_ras_n>),                           //                                    .ras_n
		.sdram_wire_we_n                            (<connected-to-sdram_wire_we_n>),                            //                                    .we_n
		.sliders_out_export                         (<connected-to-sliders_out_export>),                         //                         sliders_out.export
		.spi_external_MISO                          (<connected-to-spi_external_MISO>),                          //                        spi_external.MISO
		.spi_external_MOSI                          (<connected-to-spi_external_MOSI>),                          //                                    .MOSI
		.spi_external_SCLK                          (<connected-to-spi_external_SCLK>),                          //                                    .SCLK
		.spi_external_SS_n                          (<connected-to-spi_external_SS_n>),                          //                                    .SS_n
		.touch_busy_external_connection_export      (<connected-to-touch_busy_external_connection_export>),      //      touch_busy_external_connection.export
		.touch_pen_irq_n_external_connection_export (<connected-to-touch_pen_irq_n_external_connection_export>), // touch_pen_irq_n_external_connection.export
		.vga_output_CLK                             (<connected-to-vga_output_CLK>),                             //                          vga_output.CLK
		.vga_output_HS                              (<connected-to-vga_output_HS>),                              //                                    .HS
		.vga_output_VS                              (<connected-to-vga_output_VS>),                              //                                    .VS
		.vga_output_BLANK                           (<connected-to-vga_output_BLANK>),                           //                                    .BLANK
		.vga_output_SYNC                            (<connected-to-vga_output_SYNC>),                            //                                    .SYNC
		.vga_output_R                               (<connected-to-vga_output_R>),                               //                                    .R
		.vga_output_G                               (<connected-to-vga_output_G>),                               //                                    .G
		.vga_output_B                               (<connected-to-vga_output_B>)                                //                                    .B
	);

