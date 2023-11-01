library verilog;
use verilog.vl_types.all;
entity clock is
    port(
        clk_50MHz       : in     vl_logic;
        key_A           : in     vl_logic;
        key_B           : in     vl_logic;
        time_switch     : in     vl_logic;
        time_adj        : in     vl_logic;
        nRST            : in     vl_logic;
        disp_show_0     : out    vl_logic_vector(6 downto 0);
        disp_show_1     : out    vl_logic_vector(6 downto 0);
        disp_show_2     : out    vl_logic_vector(6 downto 0);
        disp_show_3     : out    vl_logic_vector(6 downto 0);
        disp_show_4     : out    vl_logic_vector(6 downto 0);
        disp_show_5     : out    vl_logic_vector(6 downto 0);
        disp_show_6     : out    vl_logic_vector(6 downto 0);
        LED             : out    vl_logic
    );
end clock;
