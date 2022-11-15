// https://www.bilibili.com/video/BV1xb411e7Pp?p=9 
module ex_cnt (
    input wire sclk,
    input wire rst_n,
    output wire [7:0] cnt_w
);

reg [7:0] cnt;
reg ctl_flag; // ctl_flag == 0: cnt 0->255; ctl
assign cnt_w = cnt;
//always @(posedge sclk) begin // 同步复位 xilinx
always @(posedge sclk or negedge rst_n) begin // 异步复位
    if(rst_n == 1'b0)
        cnt <= 8'd0;
    else
        cnt <= cnt + 1'b1;
end

always @(posedge sclk or negedge rst_n) begin
    if(rst_n == 1'b0)
        ctl_flag <= 1'b0;
    else if(cnt == 8'd0) // ((|cnt) == 1'b0) // 按位或
        ctl_flag <= 1'b0;
    else if(cnt == 8'd255) //((&cnt) == 1'b1)
        ctl_flag <= 1'b1;
end

endmodule