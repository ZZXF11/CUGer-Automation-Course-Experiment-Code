transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vlog -vlog01compat -work work +incdir+G:/software/FPGA13.1/FPGA13.1_example/CLOCK {G:/software/FPGA13.1/FPGA13.1_example/CLOCK/clock.v}
vlog -vlog01compat -work work +incdir+G:/software/FPGA13.1/FPGA13.1_example/CLOCK {G:/software/FPGA13.1/FPGA13.1_example/CLOCK/time_devide_timer.v}
vlog -vlog01compat -work work +incdir+G:/software/FPGA13.1/FPGA13.1_example/CLOCK {G:/software/FPGA13.1/FPGA13.1_example/CLOCK/digital_show.v}
vlog -vlog01compat -work work +incdir+G:/software/FPGA13.1/FPGA13.1_example/CLOCK {G:/software/FPGA13.1/FPGA13.1_example/CLOCK/eliminate_jitters.v}
vlog -vlog01compat -work work +incdir+G:/software/FPGA13.1/FPGA13.1_example/CLOCK {G:/software/FPGA13.1/FPGA13.1_example/CLOCK/key_time.v}
vlog -vlog01compat -work work +incdir+G:/software/FPGA13.1/FPGA13.1_example/CLOCK {G:/software/FPGA13.1/FPGA13.1_example/CLOCK/data_show.v}

vlog -vlog01compat -work work +incdir+G:/software/FPGA13.1/FPGA13.1_example/CLOCK/simulation/modelsim {G:/software/FPGA13.1/FPGA13.1_example/CLOCK/simulation/modelsim/clock.vt}

vsim -t 1ps -L altera_ver -L lpm_ver -L sgate_ver -L altera_mf_ver -L altera_lnsim_ver -L cyclonev_ver -L cyclonev_hssi_ver -L cyclonev_pcie_hip_ver -L rtl_work -L work -voptargs="+acc"  clock_vlg_tst

add wave *
view structure
view signals
run 10 sec
