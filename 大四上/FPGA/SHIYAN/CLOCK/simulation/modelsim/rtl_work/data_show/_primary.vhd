library verilog;
use verilog.vl_types.all;
entity data_show is
    port(
        disp_dat        : in     vl_logic_vector(3 downto 0);
        disp_show       : out    vl_logic_vector(6 downto 0)
    );
end data_show;
