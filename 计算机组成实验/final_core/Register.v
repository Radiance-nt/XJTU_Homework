`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/12/02 15:13:54
// Design Name: 
// Module Name: Register
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module Register(input clk,
input we3,//写使能-连regwrite控制信号
input [4:0] ra1,ra2,wa3,//rs,rt的地址，rd的地址
input [31:0] wd3,//写入寄存器数据输入端口
output [31:0] rd1,rd2);//rs,rt的值
reg [31:0] rf[31:0];

always @ (posedge clk)
if (we3) rf[wa3] <=wd3;
assign rd1=(ra1!=0)?rf[ra1]:0;
assign rd2=(ra2!=0)?rf[ra2]:0;

endmodule
