`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/12/02 15:27:33
// Design Name: 
// Module Name: maindec
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


module maindec(input [5:0] op,
output regwrite,regdst,alusrc,branch,memwrite,memtoreg,jump,
output [1:0] aluop);
reg [8:0]controls;
assign {regwrite,regdst,alusrc,branch,memwrite,
memtoreg,jump,aluop}=controls;
//寄存器写使能，目标寄存器编号（多路选择），数来自寄存器or立即数，对应BEQ指令（alu里面zero标志位为1有效），
//写内存使能信号，数据从内存还是alu来，跳转，aluop
always @(*)
    begin
    case(op)
    6'b000000: controls <=9'b110000010;//Rtype
    6'b100011: controls <=9'b101001000;//LW
    6'b101011: controls <=9'b001010000;//SW
    6'b000100: controls <=9'b000100001;//BEQ
    6'b001000: controls <=9'b101000000;//Addi
    6'b000010: controls <=9'b000000100;//J
    default: controls <=9'bxxxxxxxxx;
    endcase
    end
endmodule
