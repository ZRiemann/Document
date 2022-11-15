module module_ex (
    input wire clk_a,   // must wire
    input wire rst_n,
    input wire [7:0] data_in, // default 1 bit
    output reg data_out1,
    output wire data_out2 // wire or reg
);


// 组合逻辑
// 对比符号 ==,>,< C compare
//assign data_out1 = data_in; // wire must use '=' block assign
//assign data_out1 = (data_in == 1'bl); // 'b1 1 bit // 4'b0001; 4'h1; 4'd1
//assign data_out2 = 1'b0;

//assign data_out1 = (data_in >= 8'd10);
// 三目运算符
//assign data_ob = (data_in >= 8'd10) ? 1'b1 : 1'b0;

// 时序逻辑
// reg posedge,negedge
reg reg_a;
always @(posedge clk_a or negedge rst_n) begin
    reg_a <= 1'b0 // 非阻塞赋值
end

assign data_out1 = 1'b0;

endmodule