library IEEE;
use IEEE.STD_LOGIC_1164.all;

entity gyro is

    port (
        clk_clk : in std_logic;
        reset_reset_n : in std_logic;
		  i2c_scl : inout std_logic; -- scl_pad_io
			i2c_sda : inout std_logic; -- sda_pad_io
			chip_select:out std_logic;
			alt_add :out std_logic;
			oto : out std_logic_vector(11 downto 0) -- sda_pad_io
        --pio_1_external_connection_export : in  std_logic_vector(7 downto 0)
        --unit7seg : out std_logic_vector(6 downto 0);
        --dix7seg : out std_logic_vector(6 downto 0);
        --cent7seg : out std_logic_vector(6 downto 0)
    );

       
end gyro;


architecture ARCH of gyro is
       
	component pd is
		port (
			clk_clk                             : in    std_logic                     := 'X'; -- clk
			reset_reset_n                       : in    std_logic                     := 'X';  -- reset_n
			opencores_i2c_0_export_0_scl_pad_io : inout std_logic                     := 'X'; -- scl_pad_io
			opencores_i2c_0_export_0_sda_pad_io : inout std_logic                     := 'X'; -- sda_pad_io
			pio_0_external_connection_export    : out   std_logic_vector(11 downto 0)        -- export
			
		);
	end component pd;
    
    
    begin
       --chip_select <= '1';
			--alt_add <= '0';
			U : pd port map(clk_clk,reset_reset_n,i2c_scl ,i2c_sda,oto);

    
end ;