library verilog;
use verilog.vl_types.all;
entity digital_show is
    port(
        clk_timer       : in     vl_logic;
        nRST            : in     vl_logic;
        disp_dat_0      : out    vl_logic_vector(3 downto 0);
        disp_dat_1      : out    vl_logic_vector(3 downto 0);
        disp_dat_2      : out    vl_logic_vector(3 downto 0);
        disp_dat_3      : out    vl_logic_vector(3 downto 0);
        disp_dat_4      : out    vl_logic_vector(3 downto 0);
        disp_dat_5      : out    vl_logic_vector(3 downto 0);
        LED             : out    vl_logic
    );
end digital_show;
