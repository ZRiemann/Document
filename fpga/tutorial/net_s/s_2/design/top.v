module moduleName (
    input wire sclk_i,
    input wire rst_n_i,
    output wire [7:0] cnt_o
);

// 模块名，（实）例化
// (接口连接列表);
ex_cnt ex_cnt_instance(
    .sclk(sclk_i),
    .rst_n(rst_n_i),
    .cnt_w(cnt_o)
);

endmodule