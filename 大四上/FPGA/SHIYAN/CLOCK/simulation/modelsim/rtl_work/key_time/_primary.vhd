library verilog;
use verilog.vl_types.all;
entity key_time is
    port(
        key_time_adj    : in     vl_logic;
        key_time_switch : in     vl_logic;
        key_clk_timer   : in     vl_logic;
        key_o           : out    vl_logic
    );
end key_time;
