	vga_computer u0 (
		.clk_clk          (<connected-to-clk_clk>),          //        clk.clk
		.reset_reset_n    (<connected-to-reset_reset_n>),    //      reset.reset_n
		.sdram_wire_addr  (<connected-to-sdram_wire_addr>),  // sdram_wire.addr
		.sdram_wire_ba    (<connected-to-sdram_wire_ba>),    //           .ba
		.sdram_wire_cas_n (<connected-to-sdram_wire_cas_n>), //           .cas_n
		.sdram_wire_cke   (<connected-to-sdram_wire_cke>),   //           .cke
		.sdram_wire_cs_n  (<connected-to-sdram_wire_cs_n>),  //           .cs_n
		.sdram_wire_dq    (<connected-to-sdram_wire_dq>),    //           .dq
		.sdram_wire_dqm   (<connected-to-sdram_wire_dqm>),   //           .dqm
		.sdram_wire_ras_n (<connected-to-sdram_wire_ras_n>), //           .ras_n
		.sdram_wire_we_n  (<connected-to-sdram_wire_we_n>),  //           .we_n
		.vga_output_CLK   (<connected-to-vga_output_CLK>),   // vga_output.CLK
		.vga_output_HS    (<connected-to-vga_output_HS>),    //           .HS
		.vga_output_VS    (<connected-to-vga_output_VS>),    //           .VS
		.vga_output_BLANK (<connected-to-vga_output_BLANK>), //           .BLANK
		.vga_output_SYNC  (<connected-to-vga_output_SYNC>),  //           .SYNC
		.vga_output_R     (<connected-to-vga_output_R>),     //           .R
		.vga_output_G     (<connected-to-vga_output_G>),     //           .G
		.vga_output_B     (<connected-to-vga_output_B>),     //           .B
		.sdram_clk_clk    (<connected-to-sdram_clk_clk>)     //  sdram_clk.clk
	);

