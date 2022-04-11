	component DE10_Lite_SOPC is
		port (
			clk_clk                                          : in    std_logic                     := 'X';             -- clk
			clk_sdram_clk                                    : out   std_logic;                                        -- clk
			lcd_reset_n_external_connection_export           : out   std_logic;                                        -- export
			lt24_controller_conduit_end_cs                   : out   std_logic;                                        -- cs
			lt24_controller_conduit_end_rs                   : out   std_logic;                                        -- rs
			lt24_controller_conduit_end_rd                   : out   std_logic;                                        -- rd
			lt24_controller_conduit_end_wr                   : out   std_logic;                                        -- wr
			lt24_controller_conduit_end_data                 : out   std_logic_vector(15 downto 0);                    -- data
			pio_key_external_connection_export               : in    std_logic_vector(1 downto 0)  := (others => 'X'); -- export
			pio_led_external_connection_export               : out   std_logic_vector(9 downto 0);                     -- export
			pio_sw_external_connection_export                : in    std_logic_vector(9 downto 0)  := (others => 'X'); -- export
			reset_reset_n                                    : in    std_logic                     := 'X';             -- reset_n
			sdram_wire_addr                                  : out   std_logic_vector(12 downto 0);                    -- addr
			sdram_wire_ba                                    : out   std_logic_vector(1 downto 0);                     -- ba
			sdram_wire_cas_n                                 : out   std_logic;                                        -- cas_n
			sdram_wire_cke                                   : out   std_logic;                                        -- cke
			sdram_wire_cs_n                                  : out   std_logic;                                        -- cs_n
			sdram_wire_dq                                    : inout std_logic_vector(15 downto 0) := (others => 'X'); -- dq
			sdram_wire_dqm                                   : out   std_logic_vector(1 downto 0);                     -- dqm
			sdram_wire_ras_n                                 : out   std_logic;                                        -- ras_n
			sdram_wire_we_n                                  : out   std_logic;                                        -- we_n
			seg7_conduit_end_export                          : out   std_logic_vector(47 downto 0);                    -- export
			touch_panel_busy_external_connection_export      : in    std_logic                     := 'X';             -- export
			touch_panel_pen_irq_n_external_connection_export : in    std_logic                     := 'X';             -- export
			touch_panel_spi_external_MISO                    : in    std_logic                     := 'X';             -- MISO
			touch_panel_spi_external_MOSI                    : out   std_logic;                                        -- MOSI
			touch_panel_spi_external_SCLK                    : out   std_logic;                                        -- SCLK
			touch_panel_spi_external_SS_n                    : out   std_logic;                                        -- SS_n
			video_vga_controller_0_external_interface_CLK    : out   std_logic;                                        -- CLK
			video_vga_controller_0_external_interface_HS     : out   std_logic;                                        -- HS
			video_vga_controller_0_external_interface_VS     : out   std_logic;                                        -- VS
			video_vga_controller_0_external_interface_BLANK  : out   std_logic;                                        -- BLANK
			video_vga_controller_0_external_interface_SYNC   : out   std_logic;                                        -- SYNC
			video_vga_controller_0_external_interface_R      : out   std_logic_vector(3 downto 0);                     -- R
			video_vga_controller_0_external_interface_G      : out   std_logic_vector(3 downto 0);                     -- G
			video_vga_controller_0_external_interface_B      : out   std_logic_vector(3 downto 0)                      -- B
		);
	end component DE10_Lite_SOPC;

	u0 : component DE10_Lite_SOPC
		port map (
			clk_clk                                          => CONNECTED_TO_clk_clk,                                          --                                       clk.clk
			clk_sdram_clk                                    => CONNECTED_TO_clk_sdram_clk,                                    --                                 clk_sdram.clk
			lcd_reset_n_external_connection_export           => CONNECTED_TO_lcd_reset_n_external_connection_export,           --           lcd_reset_n_external_connection.export
			lt24_controller_conduit_end_cs                   => CONNECTED_TO_lt24_controller_conduit_end_cs,                   --               lt24_controller_conduit_end.cs
			lt24_controller_conduit_end_rs                   => CONNECTED_TO_lt24_controller_conduit_end_rs,                   --                                          .rs
			lt24_controller_conduit_end_rd                   => CONNECTED_TO_lt24_controller_conduit_end_rd,                   --                                          .rd
			lt24_controller_conduit_end_wr                   => CONNECTED_TO_lt24_controller_conduit_end_wr,                   --                                          .wr
			lt24_controller_conduit_end_data                 => CONNECTED_TO_lt24_controller_conduit_end_data,                 --                                          .data
			pio_key_external_connection_export               => CONNECTED_TO_pio_key_external_connection_export,               --               pio_key_external_connection.export
			pio_led_external_connection_export               => CONNECTED_TO_pio_led_external_connection_export,               --               pio_led_external_connection.export
			pio_sw_external_connection_export                => CONNECTED_TO_pio_sw_external_connection_export,                --                pio_sw_external_connection.export
			reset_reset_n                                    => CONNECTED_TO_reset_reset_n,                                    --                                     reset.reset_n
			sdram_wire_addr                                  => CONNECTED_TO_sdram_wire_addr,                                  --                                sdram_wire.addr
			sdram_wire_ba                                    => CONNECTED_TO_sdram_wire_ba,                                    --                                          .ba
			sdram_wire_cas_n                                 => CONNECTED_TO_sdram_wire_cas_n,                                 --                                          .cas_n
			sdram_wire_cke                                   => CONNECTED_TO_sdram_wire_cke,                                   --                                          .cke
			sdram_wire_cs_n                                  => CONNECTED_TO_sdram_wire_cs_n,                                  --                                          .cs_n
			sdram_wire_dq                                    => CONNECTED_TO_sdram_wire_dq,                                    --                                          .dq
			sdram_wire_dqm                                   => CONNECTED_TO_sdram_wire_dqm,                                   --                                          .dqm
			sdram_wire_ras_n                                 => CONNECTED_TO_sdram_wire_ras_n,                                 --                                          .ras_n
			sdram_wire_we_n                                  => CONNECTED_TO_sdram_wire_we_n,                                  --                                          .we_n
			seg7_conduit_end_export                          => CONNECTED_TO_seg7_conduit_end_export,                          --                          seg7_conduit_end.export
			touch_panel_busy_external_connection_export      => CONNECTED_TO_touch_panel_busy_external_connection_export,      --      touch_panel_busy_external_connection.export
			touch_panel_pen_irq_n_external_connection_export => CONNECTED_TO_touch_panel_pen_irq_n_external_connection_export, -- touch_panel_pen_irq_n_external_connection.export
			touch_panel_spi_external_MISO                    => CONNECTED_TO_touch_panel_spi_external_MISO,                    --                  touch_panel_spi_external.MISO
			touch_panel_spi_external_MOSI                    => CONNECTED_TO_touch_panel_spi_external_MOSI,                    --                                          .MOSI
			touch_panel_spi_external_SCLK                    => CONNECTED_TO_touch_panel_spi_external_SCLK,                    --                                          .SCLK
			touch_panel_spi_external_SS_n                    => CONNECTED_TO_touch_panel_spi_external_SS_n,                    --                                          .SS_n
			video_vga_controller_0_external_interface_CLK    => CONNECTED_TO_video_vga_controller_0_external_interface_CLK,    -- video_vga_controller_0_external_interface.CLK
			video_vga_controller_0_external_interface_HS     => CONNECTED_TO_video_vga_controller_0_external_interface_HS,     --                                          .HS
			video_vga_controller_0_external_interface_VS     => CONNECTED_TO_video_vga_controller_0_external_interface_VS,     --                                          .VS
			video_vga_controller_0_external_interface_BLANK  => CONNECTED_TO_video_vga_controller_0_external_interface_BLANK,  --                                          .BLANK
			video_vga_controller_0_external_interface_SYNC   => CONNECTED_TO_video_vga_controller_0_external_interface_SYNC,   --                                          .SYNC
			video_vga_controller_0_external_interface_R      => CONNECTED_TO_video_vga_controller_0_external_interface_R,      --                                          .R
			video_vga_controller_0_external_interface_G      => CONNECTED_TO_video_vga_controller_0_external_interface_G,      --                                          .G
			video_vga_controller_0_external_interface_B      => CONNECTED_TO_video_vga_controller_0_external_interface_B       --                                          .B
		);

