library verilog;
use verilog.vl_types.all;
entity time_devide_timer is
    port(
        clk             : in     vl_logic;
        switch_1        : in     vl_logic;
        switch_2        : in     vl_logic;
        clk_timer       : out    vl_logic
    );
end time_devide_timer;
