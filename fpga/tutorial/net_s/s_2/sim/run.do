quit -sim

vlib work

vlog ./tb_top.v
vlib ../design/*.v

vsim -voptargs=+acc work.top

add wave top_inst/ex_cnt_inst/*

run 100us
 