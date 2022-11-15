`timescale 1ns/1ns // 时间单位/精度 1G
//#在不可综合模块中使用，标识延时时间
#1 // 延时1纳秒

module tb_top ();

reg sclk, rst_n;
wire [7:0] cnt;

// 上电初始化，只用于仿真，智能对reg变量
initial begin
    sclk = 0;
    rst_n = 0;
    #100
    rst_n = 1;
end

always #10 begin
    sclk = ~sclk
end
top top_instance(
    .sclk_i     (sclk),
    .rst_n_i    (rst_n),
    .cnt_o      (cnt)
);
endmodule