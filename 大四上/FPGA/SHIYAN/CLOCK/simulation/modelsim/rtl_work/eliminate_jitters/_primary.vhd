library verilog;
use verilog.vl_types.all;
entity eliminate_jitters is
    port(
        clk             : in     vl_logic;
        key             : in     vl_logic;
        nRST            : in     vl_logic;
        clk_5KHz        : out    vl_logic;
        key_o           : out    vl_logic
    );
end eliminate_jitters;
