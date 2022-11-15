module fsm_1 #(
    // 独热码 采样窗口最大效率高，时序有负面影响
    IDLE = 5'b00001,
    WRITE = 5'b00001,
    READ = 5'b00001,
    CHECK = 5'b00001,
    ERROR = 5'b00001
) (
    input wire sclk,
    input wire rst_n,
    input wire write_start

    output wire error_flag;
);

reg [4:0] state;
reg write_end;
reg [9:0] write_cnt;

reg read_end;
reg [9:0] read_cnt;

error_flag = state[4];

always @(posedge sclk or negedge rst_n) begin
    if(rst_n == 1'b0)
        state <= IDLE;
    else begin
        case(state) //并发执行
        IDLE: if(write_start == 1'b1)
                state <= WRITE
        WRITE: if(write_end == 1'b1) // if(write_cnt == 1023) 转查找表效率低，尽量用1bit
                state <= READ
        READ: if(write_end == 1'b1)
                state <= CHECK
        CHECK: if((|write_cnt == 1'b0 && (|read_cnt == 1'b0)))
                    state <= IDLE;
                else
                    state <= ERROR;
        ERROR: state <= ERROR;
        default: state <=IDLE;
        endcase
    end
end

always @(posedge sclk or negedge rst_n) begin
    if(rst_n == 1'b0)
        write_cnt <= 'd0
    else if(state == WRITE) // 会被优化
        write_cnt <= write_cnt + 1'b1
    else
        write_cnt <= 'd0
end

always @(posedge sclk or negedge rst_n) begin
    if(rst_n == 1'b0)
        write_end <= 1'b0
    else if(write_cnt == 'd1022)
        write_end <= 1'b1
    else
        write_end <= 1'b0
end

always @(posedge sclk or negedge rst_n) begin
    if(rst_n == 1'b0)
        read_cnt <= 'd0
    else if(state == WRITE) // 会被优化
        read_cnt <= write_cnt + 1'b1
    else
        read_cnt <= 'd0
end

always @(posedge sclk or negedge rst_n) begin
    if(rst_n == 1'b0)
        read_end <= 1'b0
    else if(read_cnt == 'd1022)
        read_end <= 1'b1
    else
        read_end <= 1'b0
end
endmodule