
module vga_computer (
	clk_clk,
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
	vga_output_CLK,
	vga_output_HS,
	vga_output_VS,
	vga_output_BLANK,
	vga_output_SYNC,
	vga_output_R,
	vga_output_G,
	vga_output_B);	

	input		clk_clk;
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
	output		vga_output_CLK;
	output		vga_output_HS;
	output		vga_output_VS;
	output		vga_output_BLANK;
	output		vga_output_SYNC;
	output	[3:0]	vga_output_R;
	output	[3:0]	vga_output_G;
	output	[3:0]	vga_output_B;
endmodule
