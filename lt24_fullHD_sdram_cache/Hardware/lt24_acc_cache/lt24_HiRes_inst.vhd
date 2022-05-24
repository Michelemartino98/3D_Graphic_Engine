	component lt24_HiRes is
		port (
			accelerometer_spi_export_I2C_SDAT          : inout std_logic                     := 'X';             -- I2C_SDAT
			accelerometer_spi_export_I2C_SCLK          : out   std_logic;                                        -- I2C_SCLK
			accelerometer_spi_export_G_SENSOR_CS_N     : out   std_logic;                                        -- G_SENSOR_CS_N
			accelerometer_spi_export_G_SENSOR_INT      : in    std_logic                     := 'X';             -- G_SENSOR_INT
			clk_clk                                    : in    std_logic                     := 'X';             -- clk
			hex3_hex0_out_export                       : out   std_logic_vector(31 downto 0);                    -- export
			hex5_hex4_out_export                       : out   std_logic_vector(15 downto 0);                    -- export
			key_out_export                             : in    std_logic_vector(1 downto 0)  := (others => 'X'); -- export
			lcd_reset_n_external_connection_export     : out   std_logic;                                        -- export
			leds_out_export                            : out   std_logic_vector(9 downto 0);                     -- export
			lt24_controller_conduit_end_cs             : out   std_logic;                                        -- cs
			lt24_controller_conduit_end_rs             : out   std_logic;                                        -- rs
			lt24_controller_conduit_end_rd             : out   std_logic;                                        -- rd
			lt24_controller_conduit_end_wr             : out   std_logic;                                        -- wr
			lt24_controller_conduit_end_data           : out   std_logic_vector(15 downto 0);                    -- data
			reset_reset_n                              : in    std_logic                     := 'X';             -- reset_n
			sdram_clk_clk                              : out   std_logic;                                        -- clk
			sdram_wire_addr                            : out   std_logic_vector(12 downto 0);                    -- addr
			sdram_wire_ba                              : out   std_logic_vector(1 downto 0);                     -- ba
			sdram_wire_cas_n                           : out   std_logic;                                        -- cas_n
			sdram_wire_cke                             : out   std_logic;                                        -- cke
			sdram_wire_cs_n                            : out   std_logic;                                        -- cs_n
			sdram_wire_dq                              : inout std_logic_vector(15 downto 0) := (others => 'X'); -- dq
			sdram_wire_dqm                             : out   std_logic_vector(1 downto 0);                     -- dqm
			sdram_wire_ras_n                           : out   std_logic;                                        -- ras_n
			sdram_wire_we_n                            : out   std_logic;                                        -- we_n
			sliders_out_export                         : in    std_logic_vector(9 downto 0)  := (others => 'X'); -- export
			spi_external_MISO                          : in    std_logic                     := 'X';             -- MISO
			spi_external_MOSI                          : out   std_logic;                                        -- MOSI
			spi_external_SCLK                          : out   std_logic;                                        -- SCLK
			spi_external_SS_n                          : out   std_logic;                                        -- SS_n
			touch_busy_external_connection_export      : in    std_logic                     := 'X';             -- export
			touch_pen_irq_n_external_connection_export : in    std_logic                     := 'X';             -- export
			vga_output_CLK                             : out   std_logic;                                        -- CLK
			vga_output_HS                              : out   std_logic;                                        -- HS
			vga_output_VS                              : out   std_logic;                                        -- VS
			vga_output_BLANK                           : out   std_logic;                                        -- BLANK
			vga_output_SYNC                            : out   std_logic;                                        -- SYNC
			vga_output_R                               : out   std_logic_vector(3 downto 0);                     -- R
			vga_output_G                               : out   std_logic_vector(3 downto 0);                     -- G
			vga_output_B                               : out   std_logic_vector(3 downto 0)                      -- B
		);
	end component lt24_HiRes;

	u0 : component lt24_HiRes
		port map (
			accelerometer_spi_export_I2C_SDAT          => CONNECTED_TO_accelerometer_spi_export_I2C_SDAT,          --            accelerometer_spi_export.I2C_SDAT
			accelerometer_spi_export_I2C_SCLK          => CONNECTED_TO_accelerometer_spi_export_I2C_SCLK,          --                                    .I2C_SCLK
			accelerometer_spi_export_G_SENSOR_CS_N     => CONNECTED_TO_accelerometer_spi_export_G_SENSOR_CS_N,     --                                    .G_SENSOR_CS_N
			accelerometer_spi_export_G_SENSOR_INT      => CONNECTED_TO_accelerometer_spi_export_G_SENSOR_INT,      --                                    .G_SENSOR_INT
			clk_clk                                    => CONNECTED_TO_clk_clk,                                    --                                 clk.clk
			hex3_hex0_out_export                       => CONNECTED_TO_hex3_hex0_out_export,                       --                       hex3_hex0_out.export
			hex5_hex4_out_export                       => CONNECTED_TO_hex5_hex4_out_export,                       --                       hex5_hex4_out.export
			key_out_export                             => CONNECTED_TO_key_out_export,                             --                             key_out.export
			lcd_reset_n_external_connection_export     => CONNECTED_TO_lcd_reset_n_external_connection_export,     --     lcd_reset_n_external_connection.export
			leds_out_export                            => CONNECTED_TO_leds_out_export,                            --                            leds_out.export
			lt24_controller_conduit_end_cs             => CONNECTED_TO_lt24_controller_conduit_end_cs,             --         lt24_controller_conduit_end.cs
			lt24_controller_conduit_end_rs             => CONNECTED_TO_lt24_controller_conduit_end_rs,             --                                    .rs
			lt24_controller_conduit_end_rd             => CONNECTED_TO_lt24_controller_conduit_end_rd,             --                                    .rd
			lt24_controller_conduit_end_wr             => CONNECTED_TO_lt24_controller_conduit_end_wr,             --                                    .wr
			lt24_controller_conduit_end_data           => CONNECTED_TO_lt24_controller_conduit_end_data,           --                                    .data
			reset_reset_n                              => CONNECTED_TO_reset_reset_n,                              --                               reset.reset_n
			sdram_clk_clk                              => CONNECTED_TO_sdram_clk_clk,                              --                           sdram_clk.clk
			sdram_wire_addr                            => CONNECTED_TO_sdram_wire_addr,                            --                          sdram_wire.addr
			sdram_wire_ba                              => CONNECTED_TO_sdram_wire_ba,                              --                                    .ba
			sdram_wire_cas_n                           => CONNECTED_TO_sdram_wire_cas_n,                           --                                    .cas_n
			sdram_wire_cke                             => CONNECTED_TO_sdram_wire_cke,                             --                                    .cke
			sdram_wire_cs_n                            => CONNECTED_TO_sdram_wire_cs_n,                            --                                    .cs_n
			sdram_wire_dq                              => CONNECTED_TO_sdram_wire_dq,                              --                                    .dq
			sdram_wire_dqm                             => CONNECTED_TO_sdram_wire_dqm,                             --                                    .dqm
			sdram_wire_ras_n                           => CONNECTED_TO_sdram_wire_ras_n,                           --                                    .ras_n
			sdram_wire_we_n                            => CONNECTED_TO_sdram_wire_we_n,                            --                                    .we_n
			sliders_out_export                         => CONNECTED_TO_sliders_out_export,                         --                         sliders_out.export
			spi_external_MISO                          => CONNECTED_TO_spi_external_MISO,                          --                        spi_external.MISO
			spi_external_MOSI                          => CONNECTED_TO_spi_external_MOSI,                          --                                    .MOSI
			spi_external_SCLK                          => CONNECTED_TO_spi_external_SCLK,                          --                                    .SCLK
			spi_external_SS_n                          => CONNECTED_TO_spi_external_SS_n,                          --                                    .SS_n
			touch_busy_external_connection_export      => CONNECTED_TO_touch_busy_external_connection_export,      --      touch_busy_external_connection.export
			touch_pen_irq_n_external_connection_export => CONNECTED_TO_touch_pen_irq_n_external_connection_export, -- touch_pen_irq_n_external_connection.export
			vga_output_CLK                             => CONNECTED_TO_vga_output_CLK,                             --                          vga_output.CLK
			vga_output_HS                              => CONNECTED_TO_vga_output_HS,                              --                                    .HS
			vga_output_VS                              => CONNECTED_TO_vga_output_VS,                              --                                    .VS
			vga_output_BLANK                           => CONNECTED_TO_vga_output_BLANK,                           --                                    .BLANK
			vga_output_SYNC                            => CONNECTED_TO_vga_output_SYNC,                            --                                    .SYNC
			vga_output_R                               => CONNECTED_TO_vga_output_R,                               --                                    .R
			vga_output_G                               => CONNECTED_TO_vga_output_G,                               --                                    .G
			vga_output_B                               => CONNECTED_TO_vga_output_B                                --                                    .B
		);

